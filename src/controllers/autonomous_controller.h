#include "..\interfaces\2N_wheel_drive_interface.h"

// <summary>
/// @file autonomous_controller.h
/// @brief This file contains the AutonomousController class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class AutonomousController
/// @brief This class is used to control the Robot via programmed logic.
///
/// @details The Robot is controlled according to the logic coded for autonomous driving,
/// using the [NDualWheelDriveInterface] class to control the motors.
class AutonomousController {
private:
    NDualWheelDriveInterface* fourWheelDrive;

    String status;

public:
    /// @brief Constuctor initializing the [AutonomousController] Class.
    /// @param fourWheelDrive [NDualWheelDriveInterface] object controlling the motors.
    /// @return [AutonomousController] object
    AutonomousController(NDualWheelDriveInterface* fourWheelDrive) {
        this->fourWheelDrive = fourWheelDrive;
        status = "Ready";
    }

    void step(bool verbose = false) {
        
    }
};