#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

#pragma execution_character_set( "utf-8")


const std::string file_to_str(const std::string& path_file)
{
    std::ifstream file(path_file);
     if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path_file);
    }
 
    const std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return str;
}

class Contacts {
private:
    pqxx::connection conn;

public:
    Contacts(const std::string& connectionString) : conn(connectionString) {}

    void addData(const std::string& path_sql_file) {
        const std::string sql = file_to_str(path_sql_file);
      
        pqxx::work txn(conn);
        txn.exec(sql);
        txn.commit();
    }
    
    void addClient(const std::string& name, const std::string& surname, const std::string& email) {
        pqxx::work txn(conn);
        txn.exec_prepared("insert_person", name, surname, email);
        txn.commit();
    }

    void addPhoneNumber(int person_id, const std::string& number) {
        pqxx::work txn(conn);
        txn.exec_prepared("insert_phone", number, person_id);
        txn.commit();
    }

    void updateClient(int person_id, const std::string& name, const std::string& surname, const std::string& email) {
        pqxx::work txn(conn);
        txn.exec_prepared("update_person", name, surname, email, person_id);
        txn.commit();
    }

    void deletePhoneNumber(int person_id, const std::string& number) {
        pqxx::work txn(conn);
        txn.exec_prepared("delete_phone", number, person_id);
        txn.commit();
    }

    void deleteClient(int person_id) {
        pqxx::work txn(conn);
        txn.exec_prepared("delete_person", person_id);
        txn.commit();
    }

    pqxx::result findClient(const std::string& name, const std::string& surname, const std::string& email, const std::string& number) {
        pqxx::work txn(conn);
        pqxx::result res;

        res = txn.exec_prepared("find_person", name, surname, email);
        if (res.empty()) {
            res = txn.exec_prepared("find_phone", number);
        }

        return res;
    }
};

// Пример использования
int main() {
    
    //setlocale(LC_ALL, "Russian");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try 
    {
        const std::string conn_str = file_to_str("connect.txt");
 
        Contacts db(conn_str);
 
        // Создание базы данных и добавление данных.
        db.addData("create_tb.sql");
        db.addData("add_data.sql");
        db.addData("prepare_query.sql");

        enum quest
        {
            exit,
            find,
            add
        };
        int number_quest = 0;
        bool valid_request = false;
        do
        {
            std::cout << "Здравствуйте, вы получили доступ к базе клиентов." << '\n';

            std::cout << "Обновить или удалить данные клиентов вы сможете в меню "
                         "\"Найти клиента\"." << '\n';

            std::cout << "1. Найти клиента." << '\n';
            std::cout << "2. Добавть нового клиента." << '\n';
            std::cout << "0. Выйти из программы.";
            std::cout << "Введите номер действия: ";
            std::cin >> number_quest;

            if (number_quest == quest::exit) return 0;

            valid_request = (
                number_quest == quest::exit ||
                number_quest == quest::find 
            );
        } while (!valid_request);

        std::string name = "";
        std::string surname = "";
        std::string email = "";
        std::string telephone = "";

        if (number_quest == quest::add)
        {
            std::cout << "Имя: ";
            std::cin >> name;
            std::cout << "Фамилия: ";
            std::cin >> surname;
            std::cout << "Электронная почта: ";
            std::cin >> email;
            std::cout << "Телефон: ";
            std::cin >> telephone;
        }
 
        // Добавление клиента
        db.addClient("Иван", "Иванов", "ivan@example.com");
 
        // Добавление телефона для клиента
        db.addPhoneNumber(11, "+123456789");
 
        // Обновление данных о клиенте
        db.updateClient(11, "Иван", "Иванов", "ivan_new@example.com");
 
        // Удаление телефона
        db.deletePhoneNumber(9, "+123456789");
 
        // Удаление клиента
        db.deleteClient(1);
 
        // Поиск клиента
        auto res = db.findClient("Иван", "Иванов", "ivan_new@example.com", "+123456789");
        for (const auto& row: res) {
            std::cout << "Найдена запись: " << row[0].as<std::string>() << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Error list: " << e.what() << '\n'; 
    }

    return 0;
}