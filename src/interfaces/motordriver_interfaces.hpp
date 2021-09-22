#pragma once

#include <Arduino.h>

/// <summary>
/// @file motordriver_interface.hpp
/// @brief Motor driver Interfaces
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// Template class for all motor driver based Classes.
class MotorDriverInterface {
protected:
    String status;

public:
    /// PRIMITIVE MOVEMENT -> Left Motor Forward. MUST be Overridden.
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    virtual void leftMotorForward(int speed) = 0;

    /// PRIMITIVE MOVEMENT -> Left Motor Backward. MUST be Overridden.
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    virtual void leftMotorBackward(int speed) = 0;

    /// PRIMITIVE MOVEMENT -> Right Motor Forward. MUST be Overridden.
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    virtual void rightMotorForward(int speed) = 0;

    /// PRIMITIVE MOVEMENT -> Right Motor Backward. MUST be Overridden.
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    virtual void rightMotorBackward(int speed) = 0;

    // PRIMITIVE MOVEMENT -> Left Motor completely stopped. MUST be Overridden.
    virtual void leftMotorStop() = 0;

    // PRIMITIVE MOVEMENT -> Right Motor completely stopped. MUST be Overridden.
    virtual void rightMotorStop() = 0;

    /// MOVEMENT FUNCTION --> Left
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    virtual void smoothLeft(int speed) {
        rightMotorForward(speed);
        leftMotorStop();
        status = "smooth_left";
    }

    /// MOVEMENT FUNCTIONS --> Right
    /// @param speed Speed of the left motor. Range: 0-255. Default: 255
    virtual void smoothRight(int speed) {
        leftMotorForward(speed);
        rightMotorStop();
        status = "smooth_right";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Left
    /// @param speed Speed of the right motor forward and left motor reversed. Range: 0-255. Default: 255
    virtual void hardLeft(int speed) {
        rightMotorForward(speed);
        leftMotorBackward(speed);
        status = "hard_left";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Right
    /// @param speed Speed of the left motor forward and right motor reversed. Range: 0-255. Default: 255
    virtual void hardRight(int speed) {
        leftMotorForward(speed);
        rightMotorBackward(speed);
        status = "hard_right";
    }

    /// MOVEMENT FUNCTIONS --> Forward
    /// @param speed Speed of both motors. Range: 0-255. Default: 255
    virtual void forward(int speed) { 
        leftMotorForward(speed);
        rightMotorForward(speed);
        status = "forward";
    }
    
    /// MOVEMENT FUNCTIONS --> Backward
    /// @param speed Speed of both motors in reverse. Range: 0-255. Default: 255
    virtual void backward(int speed) {
        leftMotorBackward(speed);
        rightMotorBackward(speed);
        status = "backward";
    }

    /// MOVEMENT FUNCTIONS --> Stop
    virtual void stop() {
        leftMotorStop();
        rightMotorStop();
        status = "stop";
    }

    /// GETTER FUNCTION --> Status
    /// @return [String] status of the Motor Driver.
    /// @param verbose [bool] if true, prints the status of the motor driver in Serial.
    virtual String getStatus(bool verbose = false) {
        if (verbose) Serial.println(status);
        return status;
    }
};


/// @class L298NInterface
/// @brief Class that is solely responsible for controlling a L298N Motor driver.
///
/// @details Initialize with [leftForwardPin, leftBackwardPin, rightForwardPin, rightBackwardPin]
/// [enableLeftPin, enableRightPin] are optional for speed control.
class L298NInterface : public MotorDriverInterface {
private:
    int lmf, lmb, rmf, rmb;

    int enl, enr;

public:
    /// @brief Constuctor initializing the [L298NInterface].
    /// @param leftForwardPin Pin for left motor forward direction
    /// @param leftBackwardPin Pin for left motor backward direction
    /// @param rightForwardPin Pin for right motor forward direction
    /// @param rightBackwardPin Pin for right motor backward direction
    /// @param enableLeftPin Pin for left motor speed control. Default -1 (Speed control Disabled)
    /// @param enableRightPin Pin for right motor speed control. Default -1 (Speed control Disabled)
    /// @return [L298NInterface] object
    L298NInterface(
        int leftForwardPin,
        int leftBackwardPin,
        int rightForwardPin,
        int rightBackwardPin,
        int enableLeftPin=-1,
        int enableRightPin=-1
    ) {
        if (enableLeftPin == -1) Serial.println("Left Motor Speed Control pin not set up!");
        if (enableRightPin == -1) Serial.println("Right Motor Speed Control pin not set up!");
        // Set pin numbers
        lmf = leftForwardPin;
        lmb = leftBackwardPin;
        rmf = rightForwardPin;
        rmb = rightBackwardPin;
        enl = enableLeftPin;
        enr = enableRightPin;
        // Set pin as output
        pinMode(lmf, OUTPUT);
        pinMode(lmb, OUTPUT);
        pinMode(rmf, OUTPUT);
        pinMode(rmb, OUTPUT);
        if (enl != -1) pinMode(enl, OUTPUT);
        if (enr != -1) pinMode(enr, OUTPUT);
        // Status of Bot: Ready!
        status = "ready";
    }

    /// PRIMITIVE MOVEMENT -> Left Motor Stop.
    void leftMotorStop() override {
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 0);
    }

    /// PRIMITIVE MOVEMENT -> Right Motor Stop.
    void rightMotorStop() override {
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 0);
    }

    /// PRIMITIVE MOVEMENT -> Left Motor Forward
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    void leftMotorForward(int speed) override {
        digitalWrite(lmf, 1);
        digitalWrite(lmb, 0);
        if (enl != -1) analogWrite(enl, speed);
    }

    /// PRIMITIVE MOVEMENT -> Left Motor Backward
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    void leftMotorBackward(int speed) override {
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 1);
        if (enl != -1) analogWrite(enl, speed);
    }

    /// PRIMITIVE MOVEMENT -> Right Motor Forward
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    void rightMotorForward(int speed) override {
        digitalWrite(rmf, 1);
        digitalWrite(rmb, 0);
        if (enr != -1) analogWrite(enr, speed);
    }

    /// PRIMITIVE MOVEMENT -> Right Motor Backward
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    void rightMotorBackward(int speed) override {
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 1);
        if (enr != -1) analogWrite(enr, speed);
    }
};
