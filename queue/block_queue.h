#ifndef TINYHTTP_BLOCKQUEUE_H
#define TINYHTTP_BLOCKQUEUE_H

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

/**
 *  1. thread-safe
 *  2. block when popping from a empty queue
 */
template<typename T>
class BlockQueue {
    queue<T> _queue;
    mutex _mtx;
    condition_variable _cond;

public:
    void push(const T& log) {
        _mtx.lock();
        _queue.push(log);
        _mtx.unlock();
        _cond.notify_all();
    }

    T pop() {
        while (1) {
            unique_lock<mutex> queue_lock(_mtx);
            _cond.wait(queue_lock);
            if (!_queue.empty()) {
                T log = _queue.front();
                _queue.pop();
                queue_lock.unlock();
                return log;
            }
        }
    }

};

#endif //TINYHTTP_BLOCKQUEUE_H
