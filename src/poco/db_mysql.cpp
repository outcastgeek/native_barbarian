//
// Created by outcastgeek on 3/18/17.
//

// Checkout: https://pocoproject.org/docs/00200-DataUserManual.html

#include "Poco/Data/RecordSet.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/MySQL/Connector.h"
#include <vector>
#include <iostream>

using namespace Poco::Data::Keywords;
using Poco::Data::RecordSet;
using Poco::Data::Session;
using Poco::Data::Statement;

struct Person
{
    std::string name;
    std::string address;
    int         age;
};

int main(int argc, char** argv)
{
    // register MySQL connector
    Poco::Data::MySQL::Connector::registerConnector();

    // create a session
    Session session("MySQL", "host=127.0.0.1;port=3416;user=apps;password=appspass;db=Apps_Admin_Prod;compress=true;auto-connect=true;secure-auth=true");

    // drop sample table, if it exists
    session << "DROP TABLE IF EXISTS Person", now;

    // (re)create table
    session << "CREATE TABLE Person (Name VARCHAR(30), Address VARCHAR, Age INTEGER(3))", now;

    // insert some rows
    Person person =
            {
                    "Bart Simpson",
                    "Springfield",
                    12
            };

    Statement insert(session);
    insert << "INSERT INTO Person VALUES(?, ?, ?)",
            use(person.name),
            use(person.address),
            use(person.age);

    insert.execute();

    person.name    = "Lisa Simpson";
    person.address = "Springfield";
    person.age     = 10;

    insert.execute();

    // a simple query
    Statement select(session);
    select << "SELECT Name, Address, Age FROM Person",
            into(person.name),
            into(person.address),
            into(person.age),
            range(0, 1); //  iterate over result set one row at a time

    while (!select.done())
    {
        select.execute();
        std::cout << person.name << " " << person.address << " " << person.age << std::endl;
    }

    // a simple query
    Statement select2(session);
    select2 << "SELECT * FROM Person";
    select2.execute();

    // create a RecordSet
    RecordSet rs(select2);
    std::size_t cols = rs.columnCount();

    // print all column names
    for (std::size_t col = 0; col < cols; ++col)
    {
        std::cout << rs.columnName(col) << std::endl;
    }

    // iterate over all rows and columns
    bool more = rs.moveFirst();
    while (more)
    {
        for (std::size_t col = 0; col < cols; ++col)
        {
            std::cout << rs[col].convert<std::string>() << " ";
        }
        std::cout << std::endl;
        more = rs.moveNext();
    }

    return 0;
}
