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

    /// Hard coded autonomous logic to turn 180 degrees.
    /// Will only work in the specific arena by the specific robot.
    void turn180() {
        fourWheelDrive->hardLeft(185);
        delay(2450);
        fourWheelDrive->stop();
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

    /// @brief Most basic line following autonomous logic (taking on-spot turns)
    void lineFollow(int speed) {
        if(isWhite(leftIRPin) && isWhite(rightIRPin)) {
            fourWheelDrive->forward(speed);
        }
        if(isWhite(leftIRPin) && !isWhite(rightIRPin)) {
            fourWheelDrive->hardLeft(speed);
        }
        if(!isWhite(leftIRPin) && isWhite(rightIRPin)) {
            fourWheelDrive->hardRight(speed);
        }
        if(!isWhite(leftIRPin) && !isWhite(rightIRPin)) {
            fourWheelDrive->stop();
        }
    }

    /// @brief Most basic line following autonomous logic (taking smooth turns)
    void lineFollowSmooth(int speed) {
        if(isWhite(leftIRPin) && isWhite(rightIRPin)) {
            fourWheelDrive->forward(speed);
        }
        if(isWhite(leftIRPin) && !isWhite(rightIRPin)) {
            fourWheelDrive->smoothLeft(2*speed);
        }
        if(!isWhite(leftIRPin) && isWhite(rightIRPin)) {
            fourWheelDrive->smoothRight(2*speed);
        }
        if(!isWhite(leftIRPin) && !isWhite(rightIRPin)) {
            fourWheelDrive->stop();
        }
    }

    /// @brief Specific arena based logic to perform first task
    void step1(bool verbose = false) {
        if (millis() - init <= 5000) 
            lineFollow(140);
        else {
            if (!isWhite(rightIRPin)) {
                fourWheelDrive->stop();
                lifter->moveDown();
                delay(1020);
                lifter->stop();
                fourWheelDrive->forward(125);
                delay(950);
                fourWheelDrive->stop();
                lifter->moveUp();
                delay(3000);
                lifter->stop();
                fourWheelDrive->backward(255);
                delay(4200);
                turn180();

                // END PROCESS
                while (true) fourWheelDrive->stop();
            }   
        }
        if (verbose) fourWheelDrive->getStatus(true);
    }

    /// @brief Specific arena based logic to perform second task
    void step2(bool verbose = false) {
        if (millis() - init <= 15000) 
            lineFollowSmooth(95);
        else {
            if (!isWhite(leftIRPin)) {
                fourWheelDrive->stop();
                lifter->moveDown();
                delay(1020);
                lifter->stop();
                fourWheelDrive->forward(125);
                delay(950);
                fourWheelDrive->stop();
                lifter->moveUp();
                delay(3000);
                lifter->stop();
                fourWheelDrive->backward(255);
                delay(4200);

                // END PROCESS
                while (true) fourWheelDrive->stop();
            }   
        }
        if (verbose) fourWheelDrive->getStatus(true);
    }
};