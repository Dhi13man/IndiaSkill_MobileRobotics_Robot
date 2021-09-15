#include "controllers\bluetooth_controller.h"
#include "controllers\autonomous_controller.h"
#include "controllers\test_controller.h"

/// The Control types available to be used by the Robot.
enum ControlMode {
    AUTONOMOUS,
    BLUETOOTH,
    HYBRID,
    TEST
};

// Define Control Mode
const ControlMode controlMode = ControlMode::BLUETOOTH;

// Define Controllers
BluetoothController *bluetoothController;
AutonomousController *autonomousController;
TestController *testController;

/// Boolaeans to determine whether debug information should be printed.
const bool printSerialDebug = false;
const bool printBluetoothDebug = false;

void setup() {
  Serial.begin(9600);
  // Set up Motor Drivers
  L298NInterface *frontL298N = new L298NInterface(2, 3, 4, 5, 6, 7);
  L298NInterface *backL298N = new L298NInterface(8, 9, 10, 11, 12, 13);
  // Set up 4-wheel, 2 motor driver drive interface
  FourWheelDriveInterface *fourWheelDrive = new FourWheelDriveInterface(frontL298N, backL298N);
  // Set up Bluetooth communication interface
  BluetoothInterface *bluetooth = new BluetoothInterface(50, 51);

  // Setup based on Control Mode.
  switch (controlMode) {
    case ControlMode::AUTONOMOUS:
      autonomousController = new AutonomousController(fourWheelDrive);
      delete bluetooth;
      break;

    case ControlMode::BLUETOOTH:
      bluetoothController = new BluetoothController(bluetooth, fourWheelDrive);
      break;

    case ControlMode::HYBRID:
      autonomousController = new AutonomousController(fourWheelDrive);
      bluetoothController = new BluetoothController(bluetooth, fourWheelDrive);
      break;

    case ControlMode::TEST:
      testController = new TestController(bluetooth, fourWheelDrive);
      break;
  }
}

void loop() {
  // Run based on Control Mode.
  switch (controlMode) {
    case ControlMode::AUTONOMOUS:
      // Validate if BluetoothController is set up.
      if (autonomousController == NULL) {
        Serial.println("Autonomous+ Controller is NULL");
        setup();
      }
      // Act using Autonomous Controller logic.
      autonomousController->step(printSerialDebug);
      break;

    case ControlMode::BLUETOOTH:
      // Validate if BluetoothController is set up.
      if (bluetoothController == NULL) {
        Serial.println("Bluetooth Controller is NULL");
        setup();
      }
      // Act using Bluetooth Controller logic.
      bluetoothController->step(printSerialDebug, printBluetoothDebug);
      break;

    case ControlMode::HYBRID:
      // Validate if BluetoothController is set up.
      if (bluetoothController == NULL) {
        Serial.println("Bluetooth Controller is NULL");
        setup();
      }
      // Act using Bluetooth Controller logic.
      bluetoothController->step(printSerialDebug, printBluetoothDebug);
      // Act using Autonomous Controller logic.
      break;

    case ControlMode::TEST:
      // Validate if BluetoothController is set up.
      if (testController == NULL) {
        Serial.println("Test Controller is NULL");
        setup();
      }
      // Run Tests using Test Controller logic.
      testController->runTests(printSerialDebug);
      // testController->motorsTest(255, printSerialDebug);
      // testController->motorsTest(0, printSerialDebug);
      // testController->motorsTest(127, printSerialDebug);
      // testController->bluetoothTest(printSerialDebug);
      break;

    default:
      Serial.println("Invalid Control Mode: " + controlMode);
  }
}