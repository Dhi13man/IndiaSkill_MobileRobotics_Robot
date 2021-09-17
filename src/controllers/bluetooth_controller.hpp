#include "..\interfaces\bluetooth_interface.hpp"
#include "..\interfaces\2N_wheel_drive_interface.hpp"
#include "..\interfaces\lifter_interface.hpp"

// <summary>
/// @file bluetooth_controller.hpp
/// @brief This file contains the BluetoothController class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class BluetoothController
/// @brief This class is used to control the Robot via Bluetooth.
///
/// @details BluetoothController facilitates the control of the Robot according to the messages
/// received by the [BlueToothInterface], using the [NDualWheelDriveInterface] class to control the motors.
class BluetoothController {
private:
    BluetoothInterface* bluetooth;

    NDualWheelDriveInterface* nDualWheelDrive;

    LifterInterface* lifter;

    int speed;

    String status;

public:
    /// @brief Constuctor initializing the [BluetoothController] Class.
    /// @param bluetooth [BluetoothInterface] object receiving messages over Bluetooth using the HC05 Software Serial.
    /// @param nDualWheelDrive [NDualWheelDriveInterface] object controlling the motors.
    /// @return [BluetoothController] object
    BluetoothController(BluetoothInterface* bluetooth, NDualWheelDriveInterface* nDualWheelDrive) {
        this->bluetooth = bluetooth;
        this->nDualWheelDrive = nDualWheelDrive;
        // Initial speed
        this->speed = 255;
        
        // Check if Bluetooth interface is initialized and ready.
        if (this->bluetooth->getStatus() != "ready") {
            const String error = "Bluetooth is not ready. Status: ";
            Serial.println(error);
            // throw error;
        }
        status = "ready";
    }

    /// @brief Constuctor initializing the [BluetoothController] Class with lifter.
    /// @param bluetooth [BluetoothInterface] object receiving messages over Bluetooth using the HC05 Software Serial.
    /// @param nDualWheelDrive [NDualWheelDriveInterface] object controlling the motors.
    /// @param lifter [LifterInterface] object controlling the lifter.
    /// @return [BluetoothController] object
    BluetoothController(BluetoothInterface* bluetooth, NDualWheelDriveInterface* nDualWheelDrive, LifterInterface* lifter) {
        this->bluetooth = bluetooth;
        this->nDualWheelDrive = nDualWheelDrive;
        this->lifter = lifter;
        // Initial speed
        this->speed = 255;
        
        // Check if Bluetooth interface is initialized and ready.
        if (this->bluetooth->getStatus() != "ready") {
            const String error = "Bluetooth is not ready. Status: ";
            Serial.println(error);
            // throw error;
        }
        status = "ready";
    }

    /// @brief One Step of the Robot when it is to be controlled over Bluetooth. This function is called
    /// to control the Robot.
    /// @param verbose [bool] if true, the function prints the command received and status of the Robot over Serial Monitor.
    /// @param verboseBluetooth [bool] if true, the function sends the status of the Robot over Bluetooth.
    void step(bool verbose=false, bool verboseBluetooth=false) {
        char command = bluetooth->receiveChar();
        // Speed parse
        if (isdigit(command)) {
            int digit = command - '0';
            speed = digit/10 * 255;
        }
        // Command Parse
        switch (command) {
            case 'Q':
                speed = 255;
                break;
                
            // Drive Direction Select
            case 'F':
                nDualWheelDrive->forward(speed);
                break;

            case 'B':
                nDualWheelDrive->backward(speed);
                break;
            
            case 'I':
                nDualWheelDrive->smoothLeft(speed);
                break;
            
            case 'G':
                nDualWheelDrive->smoothRight(speed);
                break;
            
            case 'R':
                nDualWheelDrive->hardLeft(speed);
                break;

            case 'L':
                nDualWheelDrive->hardRight(speed);
                break;
            
            case 'S':
                nDualWheelDrive->stop();
                break;
            
            // Lifter control
            case 'W':
                lifter->moveUp();
                break;

            case 'U':
                lifter->moveDown();
                break;

            case 'w': case 'u':
                lifter->stop();
                break;
        }

        // Keep track of the status and print it if verbose is true  
        if (verbose || verboseBluetooth) { 
            if (command == 'W' || command == 'U')
                status = lifter->getStatus();
            else status = nDualWheelDrive->getStatus();
        }
        if (verbose) {
            Serial.print("Command: " + String(command));
            Serial.println("; Status: " + status);
        }
        // Send the status over Bluetooth if verboseBluetooth is true
        if (verboseBluetooth) {
            bluetooth->send(status);
        }

        // To make control tactile, the Robot is stopped a while after each movement command is received.
        if (command != 'S' && command != '\0') {
            delay(40);
            nDualWheelDrive->stop();
        }
    }
};
