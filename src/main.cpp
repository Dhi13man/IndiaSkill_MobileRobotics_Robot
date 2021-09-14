#include "controllers\bluetooth_controller.h"
#include "controllers\autonomous_controller.h"

enum ControlMode {
    BLUETOOTH,
    AUTONOMOUS,
    HYBRID
};

// Define Control Mode
ControlMode controlMode = BLUETOOTH;

// Define Controllers
BluetoothController *bluetoothController;
AutonomousController *autonomousController;

void setup() {
  Serial.begin(9600);
  // Set up Motor Drivers
  L298NInterface *frontL298N = new L298NInterface(2, 3, 4, 5, 6, 7);
  L298NInterface *backL298N = new L298NInterface(8, 9, 10, 11, 12, 13);
  // Set up 4-wheel, 2 motor driver drive interface
  FourWheelDriveInterface *fourWheelDrive = new FourWheelDriveInterface(frontL298N, backL298N);

  // Setup based on Control Mode.
  if (controlMode == BLUETOOTH || controlMode == HYBRID) {
    // Set up Bluetooth Interface
    BluetoothInterface *bluetooth = new BluetoothInterface(14, 15);
    bluetoothController = new BluetoothController(bluetooth, fourWheelDrive);
  }
  
  if (controlMode == AUTONOMOUS || controlMode == HYBRID) {
    // Set up Autonomous Controller
    autonomousController = new AutonomousController(fourWheelDrive);
  }
}

void loop() {
  // Run based on Control Mode.
  switch (controlMode) {
    case BLUETOOTH:
      // Validate if BluetoothController is set up.
      if (bluetoothController == NULL) {
        Serial.println("Bluetooth Controller is NULL");
        setup();
      }
      // Act using Bluetooth Controller logic.
      bluetoothController->step();
      break;

    case AUTONOMOUS:
      // Validate if BluetoothController is set up.
      if (autonomousController == NULL) {
        Serial.println("Autonomous+ Controller is NULL");
        setup();
      }
      // Act using Autonomous Controller logic.
      autonomousController->step();
      break;

    case HYBRID:
      // Validate if BluetoothController is set up.
      if (bluetoothController == NULL) {
        Serial.println("Bluetooth Controller is NULL");
        setup();
      }
      // Act using Bluetooth Controller logic.
      bluetoothController->step();
      break;
      // do things


    default:
      Serial.println("Invalid Control Mode");
  }
}