#ifndef CONTACTS_H
#define CONTACTS_H

#include <pqxx/pqxx>
#include <string>
#include <vector>


struct Contacts 
{
    size_t person_id;
    const std::string name;
    const std::string surname;
    const std::string email;
    std::vector<const std::string> telephone;
};

class Contacts
{
    private:
        pqxx::connection conn;

    public:
        Contacts(const std::string& connect_str);
        virtual ~Contacts();

        void addData(const std::string& path_sql_file);
        void addContact(Contact& obj);
        void addTelphone(size_t person_id, const std::string& telephone);
        void updateContact(size_t person_id, Contact& obj);
        void delTelehone(size_t telephone_id);
        void delContact(size_t person_id);
        pqxx::result findContacts(Contact& obj);
};

#endif