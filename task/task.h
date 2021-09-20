#ifndef TINYHTTP_TASK_H
#define TINYHTTP_TASK_H

#include <queue>
#include "block_queue.h"

#define BUF_SIZE 1024

class Task {
public:
    virtual void run() = 0;
};

class IOBuffer : {
    vector<char> _buf;
    int _pos;
    static int cnt;
public:
    IOBuffer(int size = 1024) : _buf(size), _pos(0) {}
};

class HttpConn : public Task {
    int _fd;
    IOBuffer _read_buf;
    IOBuffer _write_buf;
public:
    void run();
};

#endif //TINYHTTP_TASK_H
