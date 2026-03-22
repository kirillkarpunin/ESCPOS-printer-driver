#include "ESCPOS/connection/ComPortConnection.h"

ComPortConnection::ComPortConnection(const std::string& path) {
    _fd = open(path.c_str(), O_WRONLY);

    if (_fd < 0) {
        throw std::runtime_error(
            std::format("Unable to open comport ({}): {}", path, std::strerror(errno))
        );
    }
}
