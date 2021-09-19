#include "log.h"
#include <chrono>
#include <thread>

using namespace std;

int main() {

    Logger* logger = Logger::getInstantce();
    logger->init();
    for (int i = 0; i < 5; i++) {
        logger->info("Hello world");

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    logger->finish();
    return 0;
}