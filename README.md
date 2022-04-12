# directTimeOfFlight LiDAR Sensor

# TfLuna
### A C library for the Benewake TFLuna LiDAR device using the I2C communication interface. 
Since it uses I2C communication, the two wire library (TWI) is utilized. I found c program for twi.h that helps the Wire.h library of Arduino, for programmers to connect to the Arduino via it's I2C communication. However, there wasn't any existing c library for the TfLuna but I was able to reference a c++ program that built its Arduino library. The links to each of them are below:
[Two Wire c Library](https://github.com/arduino/ArduinoCore-avr/blob/master/libraries/Wire/src/utility/twi.c "twi.c")
[TfLuna's c++ Library](https://github.com/budryerson/TFLuna-I2C/blob/master/src/TFLI2C.cpp "TfLI2C.cpp")
Additionally, the LCD library used in ECE 387 is also implemented to observe the output.

In **I2C** mode, the TFMini-Plus functions as an I2C slave device.  The default address is `0x10` (16 decimal), but is user-programable by sending the `Set_I2C_Addr` command and a parameter in the range of `0x07` to `0x77` (7 to 119).  The new address requires a `Soft_Reset` command to take effect.  A `Hard_Reset` command (Restore Factory Settings) will reset the device to the default address of `0x10`.

Some commands that modify internal parameters are processed within 1 millisecond.  But some commands that require the MCU to communicate with other chips may take several milliseconds.  And some commands that erase the flash memory of the MCU, such as `Save_Settings` and `Hard_Reset`, may take several hundred milliseconds.

Frame-rate and most other parameter changes should be followed by a `Save_Settings` command or the values may be lost when power is removed.  With the TFLuna, commands are available to examine the value of various device paramters such as frame rate, trigger mode, power mode, threshold values, internal timer, error and production code.

# Wiring Diagram
The connection for 
![Wiring Diagram](https://github.com/deeparshan/lidar/blob/main/Wiring_diagram.png)
