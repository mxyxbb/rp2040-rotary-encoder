This is a device driver library for the RP2040 to read a rotary encoder,
e.g. <https://www.adafruit.com/product/377>

# Wiring

If the side with the three pins is facing you, with the shaft up, then
the pins are A, C, B.

![picture of encoder pins](doc/encoder-pins.png)


Knob1 connection
```
Pico GPIO | Knob pin
----------+--------------------------
GPIO 21   | A
GND       | C (center on 3-pin side)
GPIO 20   | B
----------+----------+--------------------------
GND       | either pin on 2-pin side
GPIO 2    | other pin on 2-pin side
----------+----------+--------------------------
```
Knob2 connection
```
Pico GPIO | Knob pin
----------+--------------------------
GPIO 17   | A
GND       | C (center on 3-pin side)
GPIO 18   | B
----------+----------+--------------------------
GND       | either pin on 2-pin side
Not Connected | other pin on 2-pin side
----------+----------+--------------------------
```