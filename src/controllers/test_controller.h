#include "..\interfaces\bluetooth_interface.h"
#include "..\interfaces\4wheel_drive_interface.h"

// <summary>
/// @file test_controller.cpp
/// @brief This file contains the BluetoothInterface class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class BluetoothController
/// @brief This class is used to control the Robot via programmed logic.
///
/// @details The Robot is controlled according to various test logic using the 
/// [FourWheelDriveInterface] class to control the motors and [BluetoothInterface] to test Bluetooth communication.
class TestController {
private:
    BluetoothInterface* bluetooth;
    
    FourWheelDriveInterface* fourWheelDrive;

    String status;

public:
    /// @brief Constuctor initializing the [TestController] Class.
    /// @param fourWheelDrive [FourWheelDriveInterface] object controlling the motors.
    /// @return [TestController] object
    TestController(BluetoothInterface* bluetooth, FourWheelDriveInterface* fourWheelDrive) {
        this->fourWheelDrive = fourWheelDrive;
        this->bluetooth = bluetooth;

        // Check if Bluetooth interface is initialized and ready.
        if (this->bluetooth->getStatus() != "Ready") {
            const String error = "Bluetooth is not ready. Status: ";
            Serial.println(error);
            // throw error;
        }
        status = "Ready";
    }

    /// Unit test for the [FourWheelDriveInterface] class. 
    /// Tests the motors by sending movement commands to the bot.
    ///
    /// @param speed [int] speed of the motors.
    /// @param verbose [bool] if true, prints the status of the motors after each command.
    void motorsTest(int speed = 255, bool verbose=false) {
        if (verbose) { Serial.println("Running Motor Unit Tests at speed: " + speed); }
        fourWheelDrive->forward(speed);
        fourWheelDrive->getStatus(verbose);
        delay(2000);
        fourWheelDrive->backward(speed);
        fourWheelDrive->getStatus(verbose);
        delay(2000);
        fourWheelDrive->smoothLeft(speed);
        fourWheelDrive->getStatus(verbose);
        delay(2000);
        fourWheelDrive->hardRight(speed);
        fourWheelDrive->getStatus(verbose);
        delay(2000);
    }

    /// Unit test for the [BluetoothInterface] class.
    /// Tests the Bluetooth communication by sending and receiving messages using the Interface.
    ///
    /// @param verbose [bool] if true, prints the status of the motors after each command.
    void bluetoothTest(bool verbose=false) {
        if (verbose) { Serial.println("Running Bluetooth Unit Tests!"); }
        // Send message over Bluetooth.
        bluetooth->send("Send Test!");
        if (verbose) { Serial.println("Sent: Send Test!"); }
        // Receive message from Bluetooth.
        String message = bluetooth->receiveString();
        if (verbose) { Serial.println("Received: " + message); }
    }

    /// Runs all unit tests.
    ///
    /// @param verbose [bool] if true, prints the status of the motors after each command.
    void runTests(bool verbose=false) {
        motorsTest(255, verbose);
        bluetoothTest(verbose);
    }
}; 