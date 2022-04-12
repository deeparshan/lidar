# directTimeOfFlight LiDAR Sensor

# TfLuna
### A C library for the Benewake TFLuna LiDAR device using the I2C communication interface. 
Since it uses I2C communication, the two wire library (TWI) is utilized. I found c program for twi.h that helps the Wire.h library of Arduino, for programmers to connect to the Arduino via it's I2C communication. However, there wasn't any existing c library for the TfLuna but I was able to reference a c++ program that built its Arduino library. The links to each of them are below: <br>
[Two Wire c Library](https://github.com/arduino/ArduinoCore-avr/blob/master/libraries/Wire/src/utility/twi.c "twi.c")<br>
[TfLuna's c++ Library](https://github.com/budryerson/TFLuna-I2C/blob/master/src/TFLI2C.cpp "TfLI2C.cpp")<br>
Additionally, the LCD library used in ECE 387 is also implemented to observe the output.

In **I2C** mode, the TFMini-Plus functions as an I2C slave device.  The default address is `0x10` (16 decimal), but is user-programable by sending the `Set_I2C_Addr` command and a parameter in the range of `0x07` to `0x77` (7 to 119).  The new address requires a `Soft_Reset` command to take effect.

# Wiring Diagram
The wiring for the TfLuna is fairly simple. It requires its Tx and Rx ports be connected to SDA and SCL on the Arduino. 
![Wiring Diagram](https://github.com/deeparshan/lidar/blob/main/Wiring_diagram.png)

# C Functions
The `getData( dist, flux, temp, addr)` function passes back three, signed, 16-bit measurement data values and sends an unsigned, 8-bit I2C address in the range of `0x08` to `0x77` (8 to 119).  A correct `addr` value must always be sent.  If the function completes without error, it returns 'True' and sets the public, one-byte 'status' code to zero.  Otherwise, it returns 'False' and sets the 'status' code to a library defined error code.

Measurement data values are passed-back in three, 16-bit, signed integer variables:
<br />&nbsp;&nbsp;&#8211;&nbsp; `dist` Distance to target in centimeters. Range: 0 - 1200
<br />&nbsp;&nbsp;&#8211;&nbsp; `flux` Strength or quality of return signal or error. Range: -1, 0 - 32767
<br />&nbsp;&nbsp;&#8211;&nbsp; `temp` Temperature in hundreths of degrees Celsius. Range: -25.00°C to 125.00°C

# Contents
1. libLCD - contains library funtion for the LCD module. <br> 
..* HD44780.c 
..* HD44780.h 
..* HD44780_Setting.h
3. 
4. 
