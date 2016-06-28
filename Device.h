#ifndef DEVICE_H_INCLUDED
#define DEVICE_H_INCLUDED
#include <cstdlib>
#include <string>
#include "header.h"


class Device{
    int Phone_number;
    Connection* conn;
    Centre* server;
public:
    Device():Phone_number(0), conn(NULL), server(NULL){};
    int get_number(){
        return Phone_number;
    };
    void ConnecttoServer(Centre* server, int number){
        Phone_number = number;
        this->server = server;
    };
    Package Call(int Phone_number);
    bool Busy(){// ha foglalt igaz
        return conn != NULL;
    };
    void Answer(Connection* connection){
        conn = connection;
    };
    void Initiate_Abort();
    void Abort(){
        conn = NULL;
    };
    void Send_message(std::string message);
    void Get_message(Package message);
};

#endif // DEVICE_H_INCLUDED
