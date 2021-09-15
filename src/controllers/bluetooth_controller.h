#include "..\interfaces\bluetooth_interface.h"
#include "..\interfaces\4wheel_drive_interface.h"

// <summary>
/// @file bluetooth_controller.cpp
/// @brief This file contains the BluetoothController class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class BluetoothController
/// @brief This class is used to control the Robot via Bluetooth.
///
/// @details BluetoothController facilitates the control of the Robot according to the messages
/// received by the [BlueToothInterface], using the [FourWheelDriveInterface] class to control the motors.
class BluetoothController {
private:
    BluetoothInterface* bluetooth;

    FourWheelDriveInterface* fourWheelDrive;

    String status;

public:
    /// @brief Constuctor initializing the [BluetoothController] Class.
    /// @param bluetooth [BluetoothInterface] object receiving messages over Bluetooth using the HC05 Software Serial.
    /// @param fourWheelDrive [FourWheelDriveInterface] object controlling the motors.
    /// @return [BluetoothController] object
    BluetoothController(BluetoothInterface* bluetooth, FourWheelDriveInterface* fourWheelDrive) {
        this->bluetooth = bluetooth;
        this->fourWheelDrive = fourWheelDrive;
        
        // Check if Bluetooth interface is initialized and ready.
        if (this->bluetooth->getStatus() != "Ready") {
            const String error = "Bluetooth is not ready. Status: ";
            Serial.println(error);
            // throw error;
        }
        status = "Ready";
    }

    /// @brief One Step of the Robot when it is to be controlled over Bluetooth. This function is called
    /// to control the Robot.
    /// @param verbose [bool] if true, the function prints the command received and status of the Robot over Serial Monitor.
    /// @param verboseBluetooth [bool] if true, the function sends the status of the Robot over Bluetooth.
    void step(bool verbose=false, bool verboseBluetooth=false) {
        char command = bluetooth->receiveChar();
        switch (command) {
            case 'w':
                fourWheelDrive->forward();
                break;

            case 's':
                fourWheelDrive->backward();
                break;
            
            case 'a':
                fourWheelDrive->smoothLeft();
                break;
            
            case 'd':
                fourWheelDrive->smoothRight();
                break;
            
            case 'q':
                fourWheelDrive->hardLeft();
                break;

            case 'e':
                fourWheelDrive->hardRight();
                break;
            
            case ' ':
                fourWheelDrive->stop();
                break;
        }
        
        // Keep track of the status and print it if verbose is true
        status = fourWheelDrive->getStatus();
        delay(300);
        fourWheelDrive->stop();

        if (verbose) {
            Serial.print("Command: " + String(command));
            Serial.println("\tStatus: " + status);
        }
        // Send the status over Bluetooth if verboseBluetooth is true
        if (verboseBluetooth) {
            bluetooth->send(status);
        }
    }
};
