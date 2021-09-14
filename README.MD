# IndiaSkill_MobileRobotics_Robot

Advanced Object-Oriented code to run a 4 wheel hybrid autonomous/Bluetooth-Controlled robot to perform tasks given across the various levels of IndiaSkills Mobile Robotics Event, 2021.

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
- **controllers**
  - **4wheel_drive_controller.cpp**
  - **bluetooth_controller.cpp**
  - **motordriver_controllers.cpp**
  - **autonomous_controller.cpp**

## Project Details

1. **Main.cpp**: Main file for the project.
2. **controllers**: Folder containing all the controllers interfacing with the hardware.
   1. **4wheel_drive_controller.cpp**: Contains a `FourWheelDriveController` Class which uses 2 `MotorDriverController` Class (defined in `motordriver_controllers.cpp`) objects to run the 4 wheeled bot as needed.

   2. **bluetooth_controller.cpp**: Contains a `BluetoothController` Class that interfaces with the HC05 Hardware to communicate using Bluetooth and control the robot using the Four Wheel Drive Controller (`FourWheelDriveController` Class Object defined in `4wheel_drive_controller.cpp`).

   3. **motordriver_controllers.cpp**: Contains a `MotorDriverController` Class Template that is extended by specific Motor Driver classes like `L298Controller` to interface with the H-Bridge Hardware, to control the motors.

   4. **autonomous_controller.cpp**: `AutonomousController` Class uses the `FourWheelDriveController` Class Object to run the robot in autonomous mode for a specific autonomous round of the competition.

## Project Dependencies

The libraries and external dependencies used to quickly make this project happen are:

1. **[Arduino](https://www.arduino.cc/)** C++ SDK
2. **[SoftwareSerial Arduino Library](https://www.arduino.cc/en/Reference.SoftwareSerial)**, for HC05 Serial Communication from whatever pins we want.
3. **[C++ STL](https://en.cppreference.com/w/cpp/header/cstddef)**

---

### Open Source Notice

    This is an open source project. Feel free to use, modify and distribute the entirety, or any part of the code either on its own, or as a template.

Would love to be credited [@dhi13man](https://www.github.com/dhi13man) though. :)
