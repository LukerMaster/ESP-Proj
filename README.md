# ESP32 - Car Screen Simulation

Simple school project that uses ESP32 and ILI9341 screen to do various input and output operations on a simulated car. Also creates a simple web server that allows users to see the current measurements outside of the ILI9431, and opens a small JSON API for access of other programs.


## Current setup to recreate the project requires:
- ESP32
- ILI9431 Screen (currently touchscreen is unused)
- Analog Stick (At least 1 axis of movement, HW-504 used originally)
- DS18B20 One-Wire Thermometer (HW-506 used originally)
- Photoresistor (HW-486 used originally)

### Connection
Connections to data pins of inputs and outputs and ESP32 GPIO pins are currently described in Configuration.h file and can be freely changed to suit your board better. Any other connections are just ILI9431 LED pin -> 3.3V and all the Vcc and GND pins of inputs and outputs are connected to one main rail from the ESP32 3.3V pin in parallel.

### Notes
- Keep in mind to add 4.7kOhm resistor between 3.3V pin and data line pin of One-Wire thermometer.
- IF you want to change the default pin setup defined in Configuration.h - do NOT use any of the ADC2 pins for IO operations if you want to use WiFi. Default pin setup does not have this issue (Tested on ESP32 DevKitV1).
