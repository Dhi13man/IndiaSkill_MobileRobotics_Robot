#include "..\interfaces\2N_wheel_drive_interface.hpp"
#include "..\interfaces\lifter_interface.hpp"

// <summary>
/// @file autonomous_controller.hpp
/// @brief This file contains the AutonomousController class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class AutonomousController
/// @brief This class is used to control the Robot via programmed logic.
///
/// @details The Robot is controlled according to the logic coded for autonomous driving,
/// using the [NDualWheelDriveInterface] class to control the motors.
///
/// Messy code because messy incomplete logic. Pardon.
class AutonomousController {
private:
    NDualWheelDriveInterface* fourWheelDrive;

    LifterInterface* lifter;

    String status;

    int leftIRPin, rightIRPin;

    size_t init;

    /// Function using IR, says if detecting white
    bool isWhite(int irPin) {
    if(digitalRead(irPin))
        return false;
    else return true;
    }


public:
    /// @brief Constuctor initializing the [AutonomousController] Class.
    /// @param fourWheelDrive [NDualWheelDriveInterface] object controlling the motors.
    /// @return [AutonomousController] object
    AutonomousController(NDualWheelDriveInterface* fourWheelDrive) {
        this->fourWheelDrive = fourWheelDrive;
        status = "ready";
    }

    /// @brief Constuctor initializing the [AutonomousController] Class.
    /// @param fourWheelDrive [NDualWheelDriveInterface] object controlling the motors.
    /// @param lifter [LifterInterface] object controlling the lifter.
    /// @return [AutonomousController] object
    AutonomousController(
        NDualWheelDriveInterface* fourWheelDrive,
        LifterInterface* lifter,
        int leftIRPin,
        int rightIRPin
    ) {
        this->fourWheelDrive = fourWheelDrive;
        this->lifter = lifter;
        // Senses Set up
        pinMode(leftIRPin, INPUT);
        pinMode(rightIRPin, INPUT);
        this->leftIRPin = leftIRPin;
        this->rightIRPin = rightIRPin;
        // Power Ground Rail
        pinMode(51, OUTPUT);
        pinMode(47, OUTPUT);
        pinMode(49, OUTPUT);
        digitalWrite(51, 0);
        digitalWrite(47, 1);
        digitalWrite(49, 1);

        init = millis();

        // Set up senses
        status = "ready";
    }

    void lineFollow() {
        if(isWhite(leftIRPin) && isWhite(rightIRPin))
            fourWheelDrive->forward(150);
        if(isWhite(leftIRPin) && !isWhite(rightIRPin))
            fourWheelDrive->hardLeft(150);
        if(!isWhite(leftIRPin) && isWhite(rightIRPin))
            fourWheelDrive->hardRight(150);
        if(!isWhite(leftIRPin) && !isWhite(rightIRPin))
            fourWheelDrive->stop();
    }

    void step(bool verbose = false) {
        if (millis() - init <= 4000) 
            lineFollow();
        else {
            if (!isWhite(rightIRPin)) {
                fourWheelDrive->stop();
                lifter->moveDown();
                delay(2000);
                lifter->stop();
                fourWheelDrive->forward(150);
                delay(2000);
                fourWheelDrive->stop();
                lifter->moveUp();
                delay(4000);
                lifter->stop();
                while (isWhite(rightIRPin)) fourWheelDrive->backward(150);
                fourWheelDrive->stop();
            }   
        }
        if (verbose) fourWheelDrive->getStatus(true);
    }
};