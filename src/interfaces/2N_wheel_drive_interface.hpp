#pragma once
#include "motordriver_interfaces.hpp"

/// <summary>
/// @file 2N_wheel_drive_interface.hpp
/// @brief This file contains the [NDualWheelDriveInterface] class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class NDualWheelDriveInterface
/// @brief This class is used to control the 2N wheel drive robot being controlled using N Motor Drivers, 
// each controlling 2 Motors.
///
/// @details Initialized with an array of [drivers] objects, which represents the motor
/// drivers used to control the robot and the [numberOfMotorDrivers], which CAN NOT exceed [MAX_NUMBER_OF_MOTOR_DRIVERS].
class NDualWheelDriveInterface {
public:
    static const int MAX_NUMBER_OF_MOTOR_DRIVERS = 10;

private:
    int numberOfMotorDrivers;

    MotorDriverInterface *drivers[MAX_NUMBER_OF_MOTOR_DRIVERS];

    String status;

public:
    /// @brief Constuctor initializing the [NDualWheelDriveInterface] Class.
    /// @param numberOfMotorDrivers Number of [MotorDriverInterface] objects, each meant to control 2 motors of the robot.
    /// @param drivers Array of [MotorDriverInterface] objects, each meant to control 2 motors of the robot. 
    /// Can Have a MAXIMUM of [MAX_NUMBER_OF_MOTOR_DRIVERS] drivers. Any more will be ignored.
    /// @return [NDualWheelDriveInterface] object
    NDualWheelDriveInterface(int numberOfMotorDrivers, MotorDriverInterface *drivers[]) {
        this->numberOfMotorDrivers = numberOfMotorDrivers;
        for (int i = 0; i < min(numberOfMotorDrivers, MAX_NUMBER_OF_MOTOR_DRIVERS); i++) {
            this->drivers[i] = drivers[i]; 
        }
        status = "Ready";
    }

    /// MOVEMENT FUNCTION --> Left
    /// @param speed Speed of the left movement. Range: 0-255. Default: 255
    void smoothLeft(int speed=255){
        for (int i = 0; i < numberOfMotorDrivers; i++)
            drivers[i]->smoothLeft(speed);
        status = "Moving Smooth Left!";
    }

    /// MOVEMENT FUNCTIONS --> Right
    /// @param speed Speed of the right movement. Range: 0-255. Default: 255
    void smoothRight(int speed=255){
        for (int i = 0; i < numberOfMotorDrivers; i++)
            drivers[i]->smoothRight(speed);
        status = "Moving Smooth Right!";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Left
    /// @param speed Speed of the left movement. Range: 0-255. Default: 255
    void hardLeft(int speed=255){
        for (int i = 0; i < numberOfMotorDrivers; i++)
            drivers[i]->hardLeft(speed);
        status = "Moving Hard Left!";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Right
    /// @param speed Speed of the right movement. Range: 0-255. Default: 255
    void hardRight(int speed=255){
        for (int i = 0; i < numberOfMotorDrivers; i++)
            drivers[i]->hardRight(speed);
        status = "Moving Hard Right!";
    }

    /// MOVEMENT FUNCTIONS --> Forward
    /// @param speed Speed of the forward movement. Range: 0-255. Default: 255
    void forward(int speed=255){
        for (int i = 0; i < numberOfMotorDrivers; i++)
            drivers[i]->forward(speed);
        status = "Moving Forward!";
    }

    /// MOVEMENT FUNCTIONS --> Back
    /// @param speed Speed of the reverse/backwards movement. Range: 0-255. Default: 255
    void backward(int speed=255){
        for (int i = 0; i < numberOfMotorDrivers; i++)
            drivers[i]->backward(speed);
        status = "Moving Backward!";
    }

    /// MOVEMENT FUNCTIONS --> Stop
    void stop(){
        for (int i = 0; i < numberOfMotorDrivers; i++)
            drivers[i]->stop();
        status = "Stopped!";
    }

    /// GETTER FUNCTION --> Status
    /// @param verbose [bool] if true, prints the status of the 2N wheel bot in Serial.
    /// @return [String] containing the status of the 2N wheel bot system.
    String getStatus(bool verbose=false){
        String fullStatus = String(numberOfMotorDrivers) + " Wheel Drive System Status: " + status;
        for (int i = 0; i < numberOfMotorDrivers; i++) {
            fullStatus += ", " + String(i + 1) + ": " + drivers[i]->getStatus(false);
        }
        if(verbose) Serial.println(fullStatus);
        return fullStatus;
    }
};
