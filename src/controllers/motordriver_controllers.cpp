#include <Arduino.h>

/// <summary>
/// @file motordriver_controller.cpp
/// @brief Motor driver controller
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14


/// Template class for all motor driver controller Classes.
class MotorDriverController {
protected:
    String status;

public:
    /// MOVEMENT FUNCTION --> Left
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    virtual void smoothLeft(int speed);

    /// MOVEMENT FUNCTIONS --> Right
    /// @param speed Speed of the left motor. Range: 0-255. Default: 255
    virtual void smoothRight(int speed);

    /// MOVEMENT FUNCTIONS --> On-Spot Left
    /// @param speed Speed of the right motor forward and left motor reversed. Range: 0-255. Default: 255
    virtual void hardLeft(int speed);

    /// MOVEMENT FUNCTIONS --> On-Spot Right
    /// @param speed Speed of the left motor forward and right motor reversed. Range: 0-255. Default: 255
    virtual void hardRight(int speed);

    /// MOVEMENT FUNCTIONS --> Forward
    /// @param speed Speed of both motors. Range: 0-255. Default: 255
    virtual void forward(int speed);
    
    /// MOVEMENT FUNCTIONS --> Backward
    /// @param speed Speed of both motors in reverse. Range: 0-255. Default: 255
    virtual void backward(int speed);

    /// MOVEMENT FUNCTIONS --> Stop
    virtual void stop();

    /// GETTER FUNCTION --> Status
    /// @return [String] status of the Motor Driver.
    /// @param verbose [bool] if true, prints the status of the motor driver in Serial.
    virtual String getStatus(bool verbose = false) {
        if (verbose) Serial.println(status);
        return status;
    }
};


/// @class L298Controller
/// @brief Class that is solely responsible for controlling a L298N Motor driver.
///
/// @details Initialize with [leftForwardPin, leftBackwardPin, rightForwardPin, rightBackwardPin]
/// [enableLeftPin, enableRightPin] are optional for speed control.
class L298Controller : public MotorDriverController {
private:
    int lmf, lmb, rmf, rmb;

    int enl, enr;

    String status;

public:
    /// @brief Constuctor initializing the L298Controller.
    /// @param leftForwardPin Pin for left motor forward direction
    /// @param leftBackwardPin Pin for left motor backward direction
    /// @param rightForwardPin Pin for right motor forward direction
    /// @param rightBackwardPin Pin for right motor backward direction
    /// @param enableLeftPin Pin for left motor speed control.
    /// @param enableRightPin Pin for right motor speed control.
    /// @return L298Controller object
    L298Controller(
        int leftForwardPin = 10,
        int leftBackwardPin = 9,
        int rightForwardPin = 8,
        int rightBackwardPin = 7,
        int enableLeftPin = 6,
        int enableRightPin = 5
    ) {
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
        pinMode(enl, OUTPUT);
        pinMode(enr, OUTPUT);
        // Status of Bot: Ready!
        status = "Ready";
    }

    /// MOVEMENT FUNCTION --> Left
    /// @param speed Speed of the right motor. Range: 0-255. Default: 255
    void smoothLeft(int speed = 255) override {
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 0);
        digitalWrite(rmf, 1);
        digitalWrite(rmb, 0);
        analogWrite(enr, speed);
        status = "Moving Smooth Left!";
    }

    /// MOVEMENT FUNCTIONS --> Right
    /// @param speed Speed of the left motor. Range: 0-255. Default: 255
    void smoothRight(int speed = 255) override {
        digitalWrite(lmf, 1);
        digitalWrite(lmb, 0);
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 0);
        analogWrite(enl, speed);
        status = "Moving Smooth Right!";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Left
    /// @param speed Speed of the right motor forward and left motor reversed. Range: 0-255. Default: 255
    void hardLeft(int speed = 255) override {
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 1);
        digitalWrite(rmf, 1);
        digitalWrite(rmb, 0);
        analogWrite(enl, speed);
        analogWrite(enr, speed);
        status = "Moving Hard Left!";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Right
    /// @param speed Speed of the left motor forward and right motor reversed. Range: 0-255. Default: 255
    void hardRight(int speed = 255) override {
        digitalWrite(lmf, 1);
        digitalWrite(lmb, 0);
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 1);
        analogWrite(enl, speed);
        analogWrite(enr, speed);
        status = "Moving Hard Right!";
    }

    /// MOVEMENT FUNCTIONS --> Forward
    /// @param speed Speed of both motors. Range: 0-255. Default: 255
    void forward(int speed = 255) override {
        digitalWrite(lmf, 1);
        digitalWrite(lmb, 0);
        digitalWrite(rmf, 1);
        digitalWrite(rmb, 0);
        analogWrite(enl, speed);
        analogWrite(enr, speed);
        status = "Moving Forward!";
    }

    /// MOVEMENT FUNCTIONS --> Backward
    /// @param speed Speed of both motors in reverse. Range: 0-255. Default: 255
    void backward(int speed = 255) override {
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 1);
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 1);
        status = "Moving Backward!";
    }

    /// MOVEMENT FUNCTIONS --> Stop
    void stop() override {
        digitalWrite(lmf, 0);
        digitalWrite(lmb, 0);
        digitalWrite(rmf, 0);
        digitalWrite(rmb, 0);
        analogWrite(enl, 0);
        analogWrite(enr, 0);
        status = "Stopped!";
    }
};
