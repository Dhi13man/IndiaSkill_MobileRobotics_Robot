# IndiaSkill_MobileRobotics_Robot

Advanced Object-Oriented code to run a 4 wheel hybrid autonomous/Bluetooth-Serial-Controlled robot to perform tasks given across the various levels of IndiaSkills Mobile Robotics Event, 2021.

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
  - **4wheel_drive_interface.h**
  - **bluetooth_interface.h**
  - **motordriver_interfaces.h**
- **controllers**
  - **autonomous_controller.h**
  - **bluetooth_controller.h**
  - **test_controller.h**

## Project Details

1. **Main.cpp:** Main file for the project.
2. **interfaces:** Folder containing all the interfaces interfacing with the hardware.
   1. **4wheel_drive_interface.h:** Contains a `FourWheelDriveInterface` Class which uses 2 `MotorDriverInterface` Class (defined in `motordriver_interfaces.cpp`) objects to run the 4 wheeled bot as needed.

   2. **bluetooth_interface.h:** Contains a `BluetoothInterface` Class that interfaces with the HC05 Hardware to communicate using Bluetooth HC05 Module to send and recieve Serial messages.

   3. **motordriver_interfaces.h:** Contains a `MotorDriverInterface` Class Template that is extended by specific Motor Driver classes like `L298NInterface` to interface with the H-Bridge Hardware, to control the motors.

3. **controllers:** Folder containing all the controllers responsible for controlling the robot (the brains of the operation).
   1. **autonomous_controller.h**: Contains a `AutonomousController` Class that uses a `FourWheelDriveInterface` Class Object to run the robot in autonomous mode for a specific autonomous round of the competition.

   2. **bluetooth_controller.h:** Contains a `BluetoothController` Class that uses the `BluetoothInterface` Class object to communicate using Bluetooth and control the robot using a Four Wheel Drive Interface (`FourWheelDriveInterface` defined in `4wheel_drive_interface.cpp`) Class Object.

   3. **test_controller.h:** Contains a `TestController` Class that uses the `BluetoothInterface` Class object to communicate using Bluetooth and `FourWheelDriveInterface` Class Object to run the robot and perform various unit tests, to quickly and efficiently verify the working of the Interfaces.

## Project Dependencies

The libraries and external dependencies used to quickly make this project happen are:

1. **[Arduino](https://www.arduino.cc/)** C++ SDK
2. **[SoftwareSerial Arduino Library](https://www.arduino.cc/en/Reference.SoftwareSerial)**, for HC05 Serial Communication from whatever pins we want.
3. **[C++ STL](https://en.cppreference.com/w/cpp/header/cstddef)**

---

### Open Source Notice

    This is an open source project. Feel free to use, modify and distribute the entirety, or any part of the code either on its own, or as a template.

Would love to be credited [@dhi13man](https://www.github.com/dhi13man) though. :)
