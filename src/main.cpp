#include <iostream>
#include "Sunnet.h"
using namespace std;

const int MAX_SERVICES_NUM = 2;

void test()
{
    auto pingType = make_shared<string>("ping");
    uint32_t services[MAX_SERVICES_NUM] = {0};
    uint32_t pong = Sunnet::inst->NewService(pingType);
    for (size_t i = 0; i < MAX_SERVICES_NUM; i++) {
        uint32_t ping = Sunnet::inst->NewService(pingType);
        auto msg = Sunnet::inst->MakeMsg(ping, new char[6]{'h', 'e', 'l', 'l', 'o', '\0'}, 6);
        Sunnet::inst->Send(pong, msg);
    }
}

int main()
{
    new Sunnet();
    Sunnet::inst->Start();
    // 开启系统后的一些逻辑
    test();
    Sunnet::inst->Wait();
    return 0;
}