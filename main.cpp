//#include "lib/contacts/contacts.h"
//#include "lib/my_db/my_db.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

class DatabaseManager {
private:
    pqxx::connection conn;

public:
    DatabaseManager(const std::string& connectionString) : conn(connectionString) {}

    void createTables() {
        std::ifstream file("create_tb.sql");
        std::string sql((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
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
    DatabaseManager db("dbname=mydb user=myuser password=mypass");

    // Создание таблиц
    db.createTables();

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

    return 0;
}