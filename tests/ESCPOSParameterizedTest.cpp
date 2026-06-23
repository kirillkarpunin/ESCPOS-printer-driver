#include "ESCPOSParameterizedTest.h"

#include "ESCPOS/connection/BluetoothConnection.h"
#include "ESCPOS/connection/ComPortConnection.h"

void ESCPOSParameterizedTest::SetUp() {
    ConnectionType type = GetParam();

    if (type == ConnectionType::USB) {
        const char* path = std::getenv("PRINTER_USB_PATH");

        if (!path) {
            GTEST_SKIP() << "PRINTER_USB_PATH not set";
        }

        connection = std::make_unique<ComPortConnection>(path);
    } else if (type == ConnectionType::BLUETOOTH) {
        const char* mac_address_str = std::getenv("PRINTER_BT_ADDRESS");

        if (!mac_address_str) {
            GTEST_SKIP() << "PRINTER_BT_ADDRESS not set";
        }

        connection = std::make_unique<BluetoothConnection>(mac_address_str);
    }

    ASSERT_FALSE(connection == nullptr) << "Failed to set up connection";

    printer = std::make_unique<Printer>(*connection);
    printer->initialize();

    const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
    current_test_name = test_info->name();

    printer->print(std::format("\n[{}]", current_test_name));
}

void ESCPOSParameterizedTest::TearDown() {
    if (printer) {
        printer.reset();
    }

    if (connection) {
        connection.reset();
    }

    if (!current_test_name.empty()) {
        current_test_name.clear();
    }
}