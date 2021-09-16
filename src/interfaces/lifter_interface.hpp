#pragma once
#include "motordriver_interfaces.hpp"

/// <summary>
/// @file lifter_interface.hpp
/// @brief This file contains the [LifterInterface] class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class LifterInterface
/// @brief This class is used to control the lifter claw of the Robot.
///
/// @details Initialized with a [MotorDriverInterface] object, which represents the motor driver controlling
/// the lifter motor.
class LifterInterface {
private:

    MotorDriverInterface *motorDriver;

    String status;

public:
    /// @brief Constuctor initializing the [LifterInterface] Class.
    /// @param motorDrive Motor driver Interface object used to move the lifter claw up and down.
    /// @return [LifterInterface] object
    LifterInterface(MotorDriverInterface *motorDriver) {
        this->motorDriver = motorDriver;
        status = "Ready";
    }

    /// MOVEMENT FUNCTION --> Move Claw Up
    /// @param speed Speed of the left movement. Range: 0-255. Default: 255
    void moveUp(int speed=255){
        motorDriver->forward(speed);
        status = "Claw Up!";
    }

    /// MOVEMENT FUNCTIONS --> Move Claw Down
    /// @param speed Speed of the right movement. Range: 0-255. Default: 255
    void moveDown(int speed=255){
        motorDriver->backward(speed);
        status = "Claw Down!";
    }

    /// MOVEMENT FUNCTIONS --> Stop
    void stop(){
        motorDriver->stop();
        status = "Stopped!";
    }

    /// GETTER FUNCTION --> Status
    /// @param verbose [bool] if true, prints the status of the lifer claw in Serial.
    /// @return [String] containing the status of the Lifter Claw system.
    String getStatus(bool verbose=false){
        if(verbose) Serial.println(status);
        return status;
    }
};
