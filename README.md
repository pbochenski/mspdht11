# mspdht11
this is a port of adafruits dht11 library for arduino (https://github.com/adafruit/DHT-sensor-library).
Ported to support msp430 processors. It does not use any timer but uses delay_cycles() to synchronize with dht11.
Tested on msp430g2553

usage:
1. set your clock speed in dht11.h
2. set your port and pin where you've connected sensor
3. run dth11_read() to read data from sensor. It takes char[2] as a parameter and returns humidity in output[0] and tempreture in output[1].

