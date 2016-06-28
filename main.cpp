#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdexcept>
#include "Device.h"
#include "Centre.h"
#include "Connection.h"
#include "Package.h"
#include "tests.h"
#include "memtrace.h"



int main(void)
{
    try{
    Device samsungA6, iphone6s, lgSpirit, sonyxperiae1;
    Centre Relay_1(20);
    Relay_1.add_device(samsungA6);
    Relay_1.add_device(iphone6s);
    Relay_1.add_device(lgSpirit);
    Relay_1.add_device(sonyxperiae1);
    std::cout<<"Keszulekek:"<<std::endl;
    Relay_1.list_devices();
    samsungA6.Call(121);
    samsungA6.Call(10000003);
    iphone6s.Call(10000003);
    lgSpirit.Initiate_Abort();
    iphone6s.Call(10000003);
    sonyxperiae1.Call(10000001);
    sonyxperiae1.Send_message("Szia cica van gazdad?");
    samsungA6.Send_message("nincs miau");
    iphone6s.Send_message("Segitunk! Ne hagyja el a gepjarmuvet! Ha elfogy az uzemanyaga, uljon at masik gepjarmube! Belugyminiszterium");
    lgSpirit.Send_message("Error: invalid conditions");
    }
    catch(std::exception& e){
        std::cerr<<std::endl<<"HIBA----->"<<e.what();
    }
    return 0;
}
