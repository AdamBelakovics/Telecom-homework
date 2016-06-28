#ifndef CENTRE_H_INCLUDED
#define CENTRE_H_INCLUDED
#include <stdexcept>
#include <iostream>
#include "header.h"


class Centre{
    Device** Database; //device-ok tárolása
    int device_MAX_size;
    int device_count;

public:
    Centre(int siz = 20){
        Database = new Device*[siz];
        device_MAX_size = siz;
        device_count = 0;

    }
    void add_device(Device& new_device);
    void list_devices();
    Package Establish_connection(Device* dev1, int number);
    ~Centre(){
        delete[] Database;
    }
};


#endif // CENTRE_H_INCLUDED
