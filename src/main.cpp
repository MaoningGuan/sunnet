#include <iostream>
#include "Sunnet.h"
using namespace std;

int main()
{
    new Sunnet();
    Sunnet::inst->Start();
    // 开启系统后的一些逻辑
    Sunnet::inst->Wait();
    return 0;
}