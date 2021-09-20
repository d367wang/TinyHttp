#include "task.h"
#include <unistd.h>

void HttpConn::run() {
    size_t n = read(_fd, _read_buf, BUF_SIZE);

}
