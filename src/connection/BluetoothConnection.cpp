#include "ESCPOS/connection/BluetoothConnection.h"

BluetoothConnection::BluetoothConnection(const std::string& mac_address_str) {
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = 1;

    if (str2ba(mac_address_str.c_str(), &addr.rc_bdaddr) < 0) {
        throw std::runtime_error(
            std::format("Invalid MAC address: {}", mac_address_str)
        );
    }

    _fd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    if (_fd < 0) {
        throw std::runtime_error(
            std::format("Unable to open socket: {}", std::strerror(errno))
        );
    }

    if (connect(_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        close(_fd);
        throw std::runtime_error(
            std::format("Unable to connect ({})", mac_address_str)
        );
    }
}

