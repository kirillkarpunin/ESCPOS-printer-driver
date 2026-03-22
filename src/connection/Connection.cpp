#include "ESCPOS/connection/Connection.h"

Connection::Connection(): _fd(-1) {}

void Connection::_write(const std::string& buf) const {
    write(_fd, buf.data(), buf.length());
}

void Connection::_write(const unsigned char& ch) const {
    write(_fd, &ch, 1);
}

Connection::~Connection() {
    close(_fd);
}
