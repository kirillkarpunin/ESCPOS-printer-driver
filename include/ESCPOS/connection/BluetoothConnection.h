#ifndef BLUETOOTHCONNECTION_H
#define BLUETOOTHCONNECTION_H

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <cstring>
#include <format>
#include <sys/socket.h>
#include <unistd.h>

#include "ESCPOS/connection/Connection.h"

class BluetoothConnection final : public Connection {
public:
    explicit BluetoothConnection(const std::string& mac_address_str);

    BluetoothConnection(const BluetoothConnection& connection) = delete;

    BluetoothConnection& operator=(const BluetoothConnection& connection) = delete;

private:
    sockaddr_rc addr{};
};

#endif //BLUETOOTHCONNECTION_H
