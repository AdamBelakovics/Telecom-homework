#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED
#include <stdexcept>
#include "header.h"

class Connection{
    Device* transmitter;
    Device* receiver;
public:
    Connection(Device* device1, Device* device2){
        transmitter = device1;
        receiver = device2;
    }
    void Abort(Device* initiator);
    void Forward_message(Device* dev, Package message);
};



#endif // CONNECTION_H_INCLUDED
