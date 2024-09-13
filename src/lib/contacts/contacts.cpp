#include "contacts.h"


Contacts::Contacts(const std::string& connect_str) : 
    conn(connect_str)
{}

Contacts::~Contacts()
{}

void Contacts::addData(const std::string& path_sql_file)
{

}

void Contacts::addContact(Contact& obj)
{

}

void Contacts::addTelphone(size_t person_id, const std::string& telephone)
{

}

void Contacts::updateContact(size_t person_id, Contact& obj)
{

}

void Contacts::delTelehone(size_t telephone_id)
{

}

void Contacts::delContact(size_t person_id)
{

}

pqxx::result Contacts::findContacts(Contact& obj)
{
    
}
