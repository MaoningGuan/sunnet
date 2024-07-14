#include <iostream>
#include "Sunnet.h"
using namespace std;

Sunnet* Sunnet::inst;
Sunnet::Sunnet()
{
    inst = this;
}

// 开启系统
void Sunnet::Start()
{
    cout << "Hello Sunnet" << endl;
    // 开启Worker
    StartWorker();
}

// 开启worker线程
void Sunnet::StartWorker()
{
    for (int i = 0; i < WORKER_NUM; i++)
    {
        cout << "start worker thread" << i << endl;
        // 创建线程对象
        Worker* worker = new Worker();
        worker->id = i;
        worker->eachNum = 2 << i;
        // 创建线程
        thread* wt = new thread(*worker);
        // 添加到数组
        workers.push_back(worker);
        workerThreads.push_back(wt);
    }

}

void Sunnet::Wait()
{
    if (workerThreads[0]) {
        workerThreads[0]->join();
    }

}