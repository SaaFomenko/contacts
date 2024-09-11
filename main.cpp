#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <sstream>


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
    try 
    {
        const std::string conn_str = file_to_str("connect.txt");
 
        Contacts db(conn_str);
 
        // Создание базы данных и добавление данных.
        db.addData("create_tb.sql");
        db.addData("add_data.sql");
        db.addData("prepare_query.sql");
 
        // Добавление клиента
        db.addClient("Иван", "Иванов", "ivan@example.com");
 
        // Добавление телефона для клиента
        db.addPhoneNumber(1, "+123456789");
 
        // Обновление данных о клиенте
        db.updateClient(1, "Иван", "Иванов", "ivan_new@example.com");
 
        // Удаление телефона
        db.deletePhoneNumber(1, "+123456789");
 
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