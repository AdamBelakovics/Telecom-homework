#include <cstdlib>
#include "tests.h"
#include "Device.h"
#include "Centre.h"
#include "Connection.h"
#include "Package.h"
#include "gtest_lite.h"
#include "memtrace.h"



void test_1_basics(){
TEST(Telecom, Device_construct) {
    Device telo;
    EXPECT_EQ(0, telo.get_number());
 } END

TEST(Telecom, Is_Busy) {
    Device telo;
    EXPECT_EQ(false, telo.Busy());
 } END

TEST(Telecom, add_device) {
    Device telo;
    Centre Relay_1(2);
    Relay_1.add_device(telo);
    EXPECT_EQ(telo.get_number(), 10000001);
 } END

TEST(Telecom, Too_much_devices) {
    Device telo;
    Centre Relay_1(2);
    Relay_1.add_device(telo);
    Relay_1.add_device(telo);
    EXPECT_THROW(Relay_1.add_device(telo), std::out_of_range);
 } END
}

void test_2_Call(){
TEST(Telecom, Non_valid_Call) {
    Device samsungA6;
    Centre Relay_1(20);
    Relay_1.add_device(samsungA6);
    std::string str = "Ezen a szamon elofizeto nem kapcsolhato.";
    EXPECT_STR_EQ(samsungA6.Call(121).message.c_str(), str.c_str());
} END

TEST(Telecom, Valid_Call) {
    Device samsungA6;
    Device iphone6s;
    Centre Relay_1(20);
    Relay_1.add_device(samsungA6);
    Relay_1.add_device(iphone6s);
    std::string message = samsungA6.Call(10000002).message;
    std::string str = "A kapcsolat letrejott 10000001 es 10000002 kozott.";
    std::cout<<std::endl;
    EXPECT_STR_EQ(message.c_str(), str.c_str());
} END

TEST(Telecom, Check_Busy) {
    Device samsungA6;
    Device iphone6s;
    Device lgspirit;
    Centre Relay_1(20);
    Relay_1.add_device(samsungA6);
    Relay_1.add_device(iphone6s);
    Relay_1.add_device(lgspirit);
    samsungA6.Call(10000002);
    std::string message = lgspirit.Call(10000002).message;
    std::string str = "A szam foglalt.";
    std::cout<<std::endl;
    EXPECT_STR_EQ(message.c_str(), str.c_str());
} END

TEST(Telecom, Check_Abort_receiver) {
    Device samsungA6;
    Device lgspirit;
    Centre Relay_1(20);
    Relay_1.add_device(samsungA6);
    Relay_1.add_device(lgspirit);
    samsungA6.Call(10000002);
    lgspirit.Initiate_Abort();
    bool busy = lgspirit.Busy();
    std::cout<<std::endl;
    EXPECT_EQ(busy , 0);

} END

TEST(Telecom, Check_Abort_transmitter) {
    Device samsungA6;
    Device lgspirit;
    Centre Relay_1(20);
    Relay_1.add_device(samsungA6);
    Relay_1.add_device(lgspirit);
    samsungA6.Call(10000002);
    samsungA6.Initiate_Abort();
    bool busy = samsungA6.Busy();
    std::cout<<std::endl;
    EXPECT_EQ(busy, 0);
} END


}


