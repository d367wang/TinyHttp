#include "log.h"
#include <fstream>

Logger* Logger::getInstantce() {
    static Logger logger;
    return &logger;
}

ostream& operator<<(ostream& os, LogLevel level) {
    switch (level) {
        case LogLevel::ERROR:
            os << "ERROR"; break;
        case LogLevel::WARNING:
            os << "WARNING"; break;
        case LogLevel::INFO:
            os << "INFO"; break;
        default:
            os << "DEBUG";
    }
    return os;
}

ostream& operator<<(ostream& os, LogMsg log) {
    os << ctime(&log._time) << "  -  " << log._level << " :  " << log._msg;
    return os;
}

void Logger::error(string&& msg) {
    _log_queue.push(LogMsg{move(msg), LogLevel::ERROR});
}

void Logger::warn(string&& msg) {
    LogMsg log(move(msg), LogLevel::WARNING);
    _log_queue.push(log);
}

void Logger::info(string&& msg) {
    LogMsg log(move(msg), LogLevel::INFO);
    _log_queue.push(log);

}
void Logger::debug(string&& msg) {
    LogMsg log(move(msg), LogLevel::DEBUG);
    _log_queue.push(log);
}

// only one consumer, don't need sync
void* Logger::write_log() {
    ofstream file;
    while (true) {
//        getInstantce()->_log_file_lock.lock();
//        file.open(getInstantce()->_log_file_path, ios::app);
//        file << getInstantce()->_log_queue.pop() << endl;
//        file.close();

        cout << getInstantce()->_log_queue.pop() << endl;
//        getInstantce()->_log_file_lock.unlock();
    }

}

void Logger::init() {
    unique_ptr<thread> log_thread(new thread(write_log));
    _log_thread = move(log_thread);
}

void Logger::finish() {
    _log_thread->join();
}
