#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include "Centre.h"
#include "Connection.h"
#include "Device.h"
#include "Package.h"
#include "memtrace.h"





Package Device::Call(int Phone_number){
        Package response = server->Establish_connection(this, Phone_number);
        if ((conn = response.connection) != NULL){ //connection beallítasa
            std::stringstream ss;
            ss <<"A kapcsolat letrejott "<<this->Phone_number<<" es "<<Phone_number<<" kozott.";
            response.message = ss.str();
            std::cout<<"A kapcsolat letrejott "<<this->Phone_number<<" es "<<Phone_number<<" kozott."<<std::endl;
            return response;
        }
        else{
            std::cout<<response.message<<std::endl;
            return response;
        }
}

void Device::Initiate_Abort(){
    if (conn != NULL){
        conn->Abort(this);
        delete conn;
        conn = NULL;
    }
    else
        throw std::out_of_range("Nem letezo kapcsolat");
}

void Device::Send_message(std::string message_str){
    if(conn != NULL){
        Package message(NULL, message_str.c_str());
        conn->Forward_message(this, message);
    }
    else
        throw std::out_of_range("Nem lehet uzenetet kuldeni nincs kapcsolat!!!");
}

void Connection::Forward_message(Device* dev, Package message){
    if(dev == transmitter){
        receiver->Get_message(message);
    }
    else if (dev == receiver){
        transmitter->Get_message(message);
    }
}

void Device::Get_message(Package message){
    std::cout<<Phone_number<<" uzenetet kapott: "<<message.message<<std::endl;
}

Package Centre::Establish_connection(Device* dev1, int number){
            Device* dev2 = NULL;
            for (int i = 0; i < device_count; i++){ //Keresés telefonszám alapján
                if(Database[i]->get_number() == number)
                    dev2 = Database[i];
            }
            if (dev1 == dev2){
                throw std::out_of_range("Sajat iranyba torteno hivas!!!");
            }
            else if (dev2 == NULL){
                return Package(NULL, "Ezen a szamon elofizeto nem kapcsolhato.");
            }
            else if (dev2->Busy()){
                return Package(NULL, "A szam foglalt.");
            }
            else{
                Connection* connect_dev1_dev2 = new Connection(dev1, dev2);
                dev2->Answer(connect_dev1_dev2);
                return Package(connect_dev1_dev2, "");
            }
}

 void Centre::add_device(Device& new_device){
        if (device_count < device_MAX_size){
            Database[device_count++] = &new_device;
            new_device.ConnecttoServer(this, 10000000 + device_count);
        }
        else
            throw std::out_of_range("Kozpont tulterhelve: Database");
}

void Centre::list_devices(){
        for (int i = 0; i < device_count; i++)
            std::cout<<(*Database[i]).get_number()<<std::endl;
}


void Connection::Abort(Device* initiator){
        if(initiator == transmitter){
            receiver->Abort();
        }
        else if(initiator == receiver){
            transmitter->Abort();
        }
        else
            throw std::out_of_range("hibas kapcsolat: Connection/Abort()");
}
