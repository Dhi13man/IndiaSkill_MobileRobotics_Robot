#include "..\interfaces\bluetooth_interface.hpp"
#include "..\interfaces\2N_wheel_drive_interface.hpp"

// <summary>
/// @file test_controller.hpp
/// @brief This file contains the BluetoothInterface class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class BluetoothController
/// @brief This class is used to test the various interfaces of the Robot for quick debugging and fault detection.
///
/// @details The Robot is controlled according to various test logic using the 
/// [NDualWheelDriveInterface] class to control the motors and [BluetoothInterface] to test Bluetooth communication.
class TestController {
private:
    BluetoothInterface* bluetooth;
    
    NDualWheelDriveInterface* fourWheelDrive;

    LifterInterface* lifter;

    String status;

public:
    /// @brief Constuctor initializing the [TestController] Class.
    /// @param fourWheelDrive [NDualWheelDriveInterface] object controlling the motors.
    /// @return [TestController] object
    TestController(BluetoothInterface* bluetooth, NDualWheelDriveInterface* fourWheelDrive) {
        this->fourWheelDrive = fourWheelDrive;
        this->bluetooth = bluetooth;

        // Check if Bluetooth interface is initialized and ready.
        if (this->bluetooth->getStatus() != "ready") {
            const String error = "Bluetooth is not ready. Status: ";
            Serial.println(error);
            // throw error;
        }
        status = "ready";
    }

    /// @brief Constuctor initializing the [TestController] Class.
    /// @param fourWheelDrive [NDualWheelDriveInterface] object controlling the motors.
    /// @param lifter [LifterInterface] object controlling the lifter.
    /// @return [TestController] object
    TestController(BluetoothInterface* bluetooth, NDualWheelDriveInterface* fourWheelDrive, LifterInterface* lifter) {
        this->bluetooth = bluetooth;
        this->fourWheelDrive = fourWheelDrive;
        this->lifter = lifter;

        // Check if Bluetooth interface is initialized and ready.
        if (this->bluetooth->getStatus() != "ready") {
            const String error = "Bluetooth is not ready. Status: ";
            Serial.println(error);
            // throw error;
        }
        status = "ready";
    }

    /// Unit test for the [NDualWheelDriveInterface] class. 
    /// Tests the motors by sending movement commands to the bot.
    ///
    /// @param speed [int] speed of the motors.
    /// @param verbose [bool] if true, prints the status of the motors after each command.
    void motorsTest(int speed = 255, bool verbose=false) {
        if (verbose) Serial.println("Running Motor Unit Tests at speed: " + String(speed));
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
        Serial.println();
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
        Serial.println();
        delay(200);
    }

    /// Unit test for the [LifterInterface] class.
    /// Tests the lifter by sending movement commands to the lifter.
    ///
    /// @param verbose [bool] if true, prints the status of the lifter after each command.
    void lifterTest(bool verbose=false) {
        if (verbose) { Serial.println("Running Lifter Unit Tests!"); }
        lifter->moveDown();
        if (verbose) { lifter->getStatus(verbose); }
        delay(1000);
        lifter->stop();
        if (verbose) { lifter->getStatus(verbose); }
        delay(5000);
    }

    /// Runs all defined unit tests in [TestController].
    ///
    /// @param verbose [bool] if true, prints the status of the motors after each command.
    void runTests(bool verbose=false) {
        motorsTest(255, verbose);
        bluetoothTest(verbose);
        lifterTest(verbose);
    }
}; 