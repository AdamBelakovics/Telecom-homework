#ifndef PACKAGE_H_INCLUDED
#define PACKAGE_H_INCLUDED
#include "header.h"

struct Package{
    Connection* connection;
    std::string message;
    Package(Connection* connection, const char* message): connection(connection), message(message){};
};

#endif // PACKAGE_H_INCLUDED
