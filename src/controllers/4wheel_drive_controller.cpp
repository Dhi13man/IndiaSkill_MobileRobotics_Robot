#include "motordriver_controller.cpp"

/// <summary>
/// @file 4wheel_drive_controller.cpp
/// @brief This file contains the 4wheel_drive_controller class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class FourWheelDriveController
/// @brief This class is used to control the 4 wheel drive robot being controlled using 2 L298 Motor Drivers.
///
/// @details Initialized with [frontMotorDriver, backMotorDriver] that control the 2 wheels on the front and
/// the two wheels on the back of the robot respectively.
class FourWheelDriveController {
private:
    L298Controller frontDriver, backDriver;

    String status;

public:
    /// @brief Constuctor initializing the FourWheelDriveController.
    /// @param frontMotorDriver L298Controller object that is meant to control the front wheels of the robot.
    /// @param backMotorDriver L298Controller object that is meant to control the back wheels of the robot.
    /// @return L298Controller object
    FourWheelDriveController(L298Controller &frontMotorDriver, L298Controller &backMotorDriver) {
        frontDriver = frontMotorDriver;
        backDriver = backMotorDriver;
        status = "Ready";
    }

    /// MOVEMENT FUNCTION --> Left
    /// @param speed Speed of the left movement. Range: 0-255. Default: 255
    void smoothLeft(int speed=255){
        frontDriver.smoothLeft(speed);
        backDriver.smoothLeft(speed);
        status = "Moving Smooth Left!";
    }

    /// MOVEMENT FUNCTIONS --> Right
    /// @param speed Speed of the right movement. Range: 0-255. Default: 255
    void smoothRight(int speed=255){
        frontDriver.smoothRight(speed);
        backDriver.smoothRight(speed);
        status = "Moving Smooth Right!";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Left
    /// @param speed Speed of the left movement. Range: 0-255. Default: 255
    void hardLeft(int speed=255){
        frontDriver.hardLeft(speed);
        backDriver.hardLeft(speed);
        status = "Moving Hard Left!";
    }

    /// MOVEMENT FUNCTIONS --> On-Spot Right
    /// @param speed Speed of the right movement. Range: 0-255. Default: 255
    void hardRight(int speed=255){
        frontDriver.hardRight(speed);
        backDriver.hardRight(speed);
        status = "Moving Hard Right!";
    }

    /// MOVEMENT FUNCTIONS --> Forward
    /// @param speed Speed of the forward movement. Range: 0-255. Default: 255
    void forward(int speed=255){
        frontDriver.forward(speed);
        backDriver.forward(speed);
        status = "Moving Forward!";
    }

    /// MOVEMENT FUNCTIONS --> Back
    /// @param speed Speed of the reverse/backwards movement. Range: 0-255. Default: 255
    void back(int speed=255){
        frontDriver.back(speed);
        backDriver.back(speed);
        status = "Moving Backward!";
    }

    /// MOVEMENT FUNCTIONS --> Stop
    void stop(){
        frontDriver.stop();
        backDriver.stop();
        status = "Stopped!";
    }

    /// GETTER FUNCTION --> Status
    /// @param verbose [bool] if true, prints the status of the 4 wheel bot in Serial.
    /// @return String containing the status of the 4 wheel bot system.
    String getStatus(bool verbose=false){
        String fullStatus = "4 Wheel Drive System Status: " + status;
        fullStatus += ", Front Left Motor Status: " + frontDriver.getStatus(verbose=false);
        fullStatus += ", Front Right Motor Status: " + backDriver.getStatus(verbose=false);
        if(verbose) Serial.println(fullStatus);
        return fullStatus;
    }
};