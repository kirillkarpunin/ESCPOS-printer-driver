#ifndef COMPORTCONNECTION_H
#define COMPORTCONNECTION_H

#include <cstring>
#include <fcntl.h>
#include <format>

#include "ESCPOS/connection/Connection.h"

class ComPortConnection final : public Connection {
public:
    explicit ComPortConnection(const std::string& path);

    ComPortConnection(const ComPortConnection& connection) = delete;

    ComPortConnection& operator=(const ComPortConnection& connection) = delete;
};

#endif //COMPORTCONNECTION_H
