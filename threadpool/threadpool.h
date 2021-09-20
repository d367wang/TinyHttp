#ifndef TINYHTTP_THREADPOOL_H
#define TINYHTTP_THREADPOOL_H

#include <thread>
using namespace std;

template<int NTHREAD>
class ThreadPool {
private:
    unique_ptr<thread> worker[NTHREAD];
    static ThreadPool* _inst;
    ThreadPool() {}
public:
    ThreadPool* getInstance() {
        static ThreadPool<NTHREAD> threadPool;
        return &threadPool;
    }

    void init() {
        for (int i = 0; i < NTHREAD; i++) {
            worker[i] = unique_ptr<thread>(new thread(func));
        }
    }

    static
};

#endif //TINYHTTP_THREADPOOL_H
