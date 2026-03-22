#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <unistd.h>

class Printer;

class Connection {
public:
    Connection(const Connection& connection) = delete;

    Connection& operator=(const Connection& connection) = delete;

    virtual ~Connection();

protected:
    Connection();

    int _fd;

private:
    void _write(const std::string& buf) const;
    void _write(const unsigned char& ch) const;

    friend Printer;
};

#endif //CONNECTION_H
