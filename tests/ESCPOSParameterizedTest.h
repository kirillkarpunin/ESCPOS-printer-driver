#ifndef ESCPOS_ESCPOSPARAMETERIZEDTEST_H
#define ESCPOS_ESCPOSPARAMETERIZEDTEST_H

#include "gtest/gtest.h"

#include "ESCPOS/connection/Connection.h"
#include "ESCPOS/printer/Printer.h"

enum class ConnectionType {
    WIRED,
    BLUETOOTH
};

const auto connections = ::testing::Values(
    ConnectionType::WIRED,
    ConnectionType::BLUETOOTH
);

class ESCPOSParameterizedTest : public ::testing::TestWithParam<ConnectionType> {
protected:
    std::unique_ptr<Connection> connection;
    std::unique_ptr<Printer> printer;

    std::string current_test_name;

    void SetUp() override;

    void TearDown() override;
};

#endif //ESCPOS_ESCPOSPARAMETERIZEDTEST_H
