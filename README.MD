# IndiaSkill_MobileRobotics_Robot

Advanced Object-Oriented code to run a 4-wheel hybrid autonomous/Bluetooth-Serial-Controlled robot to perform tasks given across the various levels of IndiaSkills Mobile Robotics Event, 2021.

## Hardware Components

The Robot's Hardware components associated with the project includes:

1. **Arduino Mega 2560 Microcontroller**
2. **L298N Motor Drivers**
3. **HC05 Bluetooth Module**
4. **DC Motors** (Specific type cannot be disclosed)
5. **Wires, Battery and other Basic Electronic Components**
6. **Chassis and Mechanical Structure**

## Project Structure

- **main.cpp**
- **interfaces**
  - **2N_wheel_drive_interface.hpp**
  - **bluetooth_interface.hpp**
  - **motordriver_interfaces.hpp**
  - **lifter_interface.hpp**
- **controllers**
  - **autonomous_controller.hpp**
  - **bluetooth_controller.hpp**
  - **test_controller.hpp**

## Project Details

1. **Main.cpp:** Main file for the project. Utilizes `ControlModes` enum to determine whether control needs to be done via Autonomous (`ControlModes::AUTONOMOUS`), Bluetooth(`ControlModes::BLUETOOTH`), Hybrid(`ControlModes::HYBRID`) or Test(`ControlModes::TEST`) mode using Switch cases.
Then, required Interfaces and Controller is initialized and the robot is operated using the Controller methods accordingly.

2. **interfaces:** Folder containing all the interfaces interfacing with the hardware.
   1. **2N_wheel_drive_interface.hpp:** Contains a `NDualWheelDriveInterface` Class which uses N `MotorDriverInterface` Classes (defined in `motordriver_interfaces.cpp`) objects to run the 2N wheeled bot, as needed.

   2. **bluetooth_interface.hpp:** Contains a `BluetoothInterface` Class that interfaces with the HC05 Hardware to communicate using Bluetooth HC05 Module to send and recieve Serial messages.

   3. **motordriver_interfaces.hpp:** Contains a `MotorDriverInterface` Class Template that is extended by specific Motor Driver classes like `L298NInterface` to interface with the H-Bridge Hardware, to control the motors.

   4. **lifter_interface.hpp:** Contains a `LifterInterface` Class that interfaces with the Lifter Motor Driver to control the lifter using the Hardware Rack and Pinion Gear system.

3. **controllers:** Folder containing all the controllers responsible for controlling the robot (the brains of the operation).
   1. **autonomous_controller.hpp**: Contains a `AutonomousController` Class that uses a `NDualWheelDriveInterface` Class Object to run the robot in autonomous mode for a specific autonomous round of the competition.

   2. **bluetooth_controller.hpp:** Contains a `BluetoothController` Class that uses the `BluetoothInterface` Class object to communicate using Bluetooth and control the robot using a Four Wheel Drive Interface (`NDualWheelDriveInterface` defined in `2N_wheel_drive_interface.cpp`) Class Object.

   3. **test_controller.hpp:** Contains a `TestController` Class that uses all the Interface Class objects to run the various systems of the robot, and perform various unit tests, to quickly and efficiently verify the working of the Interfaces.

## Project Dependencies

The libraries and external dependencies used to quickly make this project happen are:

1. **[Arduino](https://www.arduino.cc/)** C++ SDK
2. **[SoftwareSerial Arduino Library](https://www.arduino.cc/en/Reference.SoftwareSerial)**, for HC05 Serial Communication from whatever pins we want.
3. **[C++ STL](https://en.cppreference.com/w/cpp/header/cstddef)**

---

### Open Source Notice

    This is an open source project. Feel free to use, modify and distribute the entirety, or any part of the code either on its own, or as a template.

Would love to be credited [@dhi13man](https://www.github.com/dhi13man) though. :)
