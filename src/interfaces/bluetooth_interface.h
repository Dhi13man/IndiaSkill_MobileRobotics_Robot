#include <Arduino.h>
#include <SoftwareSerial.h>

// <summary>
/// @file bluetooth_interface.cpp
/// @brief This file contains the BluetoothInterface class.
/// @author Dhiman Seal
/// @version 1.0
/// @date 2021-09-14

/// @class BluetoothInterface
/// @brief This class is used to Send and Receive data from the HC05 Bluetooth module.
///
/// @details Initialized with [rx] and [tx] receiver and transmitter pins that help utilize Serial 
/// Communication to transfer messages between the Robot and the controlling application.
///
/// The SoftwareSerial library has the following known limitations:
///   - If using multiple software serial ports, only one can receive data at a time.
///   - Not all pins on the Mega and Mega 2560 support change interrupts, so only the following can be used for RX: 
///     10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69).
///   - Not all pins on the Leonardo and Micro support change interrupts, so only the following can be used for RX:
///     8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
///   - On Arduino or Genuino 101 the current maximum RX speed is 57600bps
///   - On Arduino or Genuino 101 RX doesn't work on Pin 13 
class BluetoothInterface {
private:
    SoftwareSerial *serial;

    String status;

public:
    /// @brief Initializes a new instance of the [BluetoothInterface] class.
    /// @param rx The Serial receiver pin.
    /// @param tx The Serial transmitter pin.
    /// @param baud The baud rate of the serial communication. Default is 9600.
    /// @return [BluetoothInterface] instance.
    BluetoothInterface(int rx, int tx, int baud=9600) {
        serial = new SoftwareSerial(rx, tx);
        serial->begin(baud);
        status = "Ready";
    }

    /// @brief Sends a message to the HC05 Bluetooth module.
    /// @param message The message to be sent.
    void send(String message) {
        serial->println(message);
    }

    /// @brief Receives a direct integer message from the HC05 Bluetooth module.
    /// @return [int] The message received. -1 if nothing is received.
    int receiveInt() {
        int message = -1;
        if (serial->available()) {
            message = serial->read();
        }
        return message;
    }

    /// @brief Receives a character message from the HC05 Bluetooth module.
    /// @return [char] The message received. '\0' if nothing is received.
    char receiveChar() {
        char message = '\0';
        if (serial->available()) {
            message = (char) serial->read();
        }
        return message;
    }

    /// @brief Receives a String message from the HC05 Bluetooth module.
    /// @return [String] The message received. "" if nothing is received.
    String receiveString() {
        String message = "";
        while (serial->available()) {
            message += (char) serial->read();
        }
        return message;
    }

    /// @brief Gets the status of the BluetoothInterface.
    /// @param verbose [bool] if true, prints the status of the 4 wheel bot in Serial.
    /// @return [String] The status of the BluetoothInterface.
    String getStatus(bool verbose=false) {
        if (verbose) Serial.println(status);
        return status;
    }
};
