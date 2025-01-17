#pragma once
#include <vector>
#include <unordered_map>
#include "Worker.h"
#include "Service.h"
#include "Msg.h"

class Worker;
class Sunnet
{
public:
    // 单个实例，全局唯一
    static Sunnet* inst;

    // 服务列表
    unordered_map<uint32_t, shared_ptr<Service>> services;
    uint32_t maxId = 0; // 最大ID
    pthread_rwlock_t servicesLock;  // 读写锁

public:
    // 构造函数
    Sunnet();
    // 初始化并开始
    void Start();
    // 等待运行
    void Wait();

    // 增删服务
    uint32_t NewService(shared_ptr<string> type);
    void KillService(uint32_t id);  // 仅限服务自己调用

    // 发送消息
    void Send(uint32_t toId, shared_ptr<BaseMsg> msg);
    // 全局队列操作
    shared_ptr<Service> PopGlobalQueue();
    void PushGlobalQueue(shared_ptr<Service> srv);
    // 创建消息
    shared_ptr<BaseMsg> MakeMsg(uint32_t source, char *buff, int len);

private:
    int WORKER_NUM = 3;             // 工作线程数
    vector<Worker*> workers;        // worker对象
    vector<thread*> workerThreads;  // 线程
    // 全局队列
    queue<shared_ptr<Service>> globalQueue;
    int globalLen = 0; // 队列长度
    pthread_spinlock_t globalLock; // 锁

private:
    // 开启工作线程
    void StartWorker();

    // 获取服务
    shared_ptr<Service> GetService(uint32_t id);
};