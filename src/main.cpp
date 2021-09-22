#include "controllers\bluetooth_controller.hpp"
#include "controllers\autonomous_controller.hpp"
#include "controllers\test_controller.hpp"

/// The Control Mode types available to be used by the Robot.
enum ControlModes {
    AUTONOMOUS,
    BLUETOOTH,
    HYBRID,
    TEST
};

// Define Control Mode
const ControlModes controlMode = ControlModes::BLUETOOTH;

// Define Controllers
BluetoothController *bluetoothController;
AutonomousController *autonomousController;
TestController *testController;

/// Booleans to determine whether debug information should be printed.
const bool printSerialDebug = false;
const bool printBluetoothDebug = false;

void setup() {
  Serial.begin(9600);
  // Set up 4-wheel, 2 motor-driver drive interface
  L298NInterface *frontL298N = new L298NInterface(2, 3, 4, 5, 6, 7);
  L298NInterface *backL298N = new L298NInterface(14, 15, 16, 17, 18, 19);
  MotorDriverInterface *motorDrivers[] = {frontL298N, backL298N};
  NDualWheelDriveInterface *nDualWheelDrive = new NDualWheelDriveInterface(2, motorDrivers);

  // Set up 1 motor-driver Lifter interface
  L298NInterface *clawL298N = new L298NInterface(8, 9, 10, 11);
  LifterInterface *lifter = new LifterInterface(clawL298N);

  // Set up Bluetooth communication interface
  BluetoothInterface *bluetooth = new BluetoothInterface(53, 52);

  // Setup based on Control Mode.
  switch (controlMode) {
    case ControlModes::AUTONOMOUS:
      autonomousController = new AutonomousController(nDualWheelDrive, lifter, 12, 13);
      delete bluetooth; // Bluetoooth not needed in Autonomouos Control Mode.
      break;

    case ControlModes::BLUETOOTH:
      bluetoothController = new BluetoothController(bluetooth, nDualWheelDrive, lifter);
      break;

    case ControlModes::HYBRID:
      autonomousController = new AutonomousController(nDualWheelDrive, lifter, 13, 12);
      bluetoothController = new BluetoothController(bluetooth, nDualWheelDrive, lifter);
      break;

    case ControlModes::TEST:
      testController = new TestController(bluetooth, nDualWheelDrive);
      break;
  }
}

void loop() {
  // Run based on Control Mode.
  switch (controlMode) {
    case ControlModes::AUTONOMOUS:
      // Validate if BluetoothController is set up.
      if (autonomousController == NULL) {
        Serial.println("Autonomous+ Controller is NULL");
        setup();
      }
      // Act using Autonomous Controller logic.
      autonomousController->step1(printSerialDebug);
      // autonomousController->step2(printSerialDebug);
      break;

    case ControlModes::BLUETOOTH:
      // Validate if BluetoothController is set up.
      if (bluetoothController == NULL) {
        Serial.println("Bluetooth Controller is NULL");
        setup();
      }
      // Act using Bluetooth Controller logic.
      bluetoothController->step(printSerialDebug, printBluetoothDebug);
      break;

    case ControlModes::HYBRID:
      // Validate if BluetoothController is set up.
      if (bluetoothController == NULL) {
        Serial.println("Bluetooth Controller is NULL");
        setup();
      }
      // Act using Bluetooth Controller logic.
      bluetoothController->step(printSerialDebug, printBluetoothDebug);
      // Act using Autonomous Controller logic.
      break;

    case ControlModes::TEST:
      // Validate if BluetoothController is set up.
      if (testController == NULL) {
        Serial.println("Test Controller is NULL");
        setup();
      }
      // Run Tests using Test Controller logic.
      testController->runTests(printSerialDebug);
      // testController->motorsTest(255, printSerialDebug);
      // testController->motorsTest(0, printSerialDebug);
      //testController->motorsTest(125, printSerialDebug);
      // testController->bluetoothTest(printSerialDebug);
      // testController->lifterTest(printSerialDebug);
      break;

    default:
      Serial.println("Invalid Control Mode: " + String(controlMode));
  }
}