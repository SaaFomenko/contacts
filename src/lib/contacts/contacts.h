#ifndef CONTACTS_H
#define CONTACTS_H

#include <pqxx/pqxx>
#include <string>
#include <vector>

// namespace my
// {
    struct Contact
    {
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
            void addClient(const std::string& name, const std::string& surname, const std::string& email); 
    };
//}

#endif