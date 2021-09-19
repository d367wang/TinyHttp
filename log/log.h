#ifndef TINYHTTP_LOG_H
#define TINYHTTP_LOG_H

#include <iostream>
#include <queue>
#include <ctime>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "block_queue.h"

using namespace std;

enum class LogLevel {
    ERROR, WARNING, INFO, DEBUG
};

class Logger;

class LogMsg {
    string _msg;
    LogLevel _level;
    time_t _time;
    string _sender;
    LogMsg(string&& msg, LogLevel level) : _msg(move(msg)), _level(level) {
        _time = time(0);
    }

    friend class Logger;
    friend ostream& operator<<(ostream& os, LogMsg log);
};


class Logger {
private:
    string _log_file_path;
    mutex _log_file_lock;
    BlockQueue<LogMsg> _log_queue;
    unique_ptr<thread> _log_thread;
    Logger() {}
public:
    static Logger* getInstantce();
    void error(string&& msg);
    void warn(string&& msg);
    void info(string&& msg);
    void debug(string&& msg);
    void init();

private:
    static void* write_log();
};

#endif //TINYHTTP_LOG_H
