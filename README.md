# ATtiny13BinaryWatches

![PCB in real life](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/ATtiny13BinaryClock.jpg)

Simple Binary Watches with 4 LED(1/5, 2/10, 4/20, 8/40), it mean 5 minute accuracy indicate.

![PCB battery](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/Back.jpg)

# Video demonstration:

https://youtu.be/qP_2BFFjp1M

# How it's work?

Every 0.5 sec CPU wake up(cycle iteration time 200 nS) and increase milliseconds value and come sleep mode(4 uA). 

If you press button "SHOWTIME();" it show hours and minutes(0.5 seconds per value) in binary mode in 4 LEDs.

# 3D model PCB:
PCB Up side:

![PCB Up](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/PCBUpATtiny13BinaryWatches.png)

PCB Down side:

![PCB Down side](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/PCBDownATtiny13BinaryWatches.png)

PCB size 27 mm in diameter(size little biger CR2032 battery):

![PCB Down](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/PCBSizesATtiny13BinaryWatches.png)

# PCB home page:

https://oshwlab.com/raznie.podelki/attiny13binarywatches

# How to flash

![AVR ISP programmer pinout](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/b00d6590e63a067a6244c02c785c1a703c8272ea/Imgs/AVR_ISP.png)

Here is pinout for AVR ISP programmer - MOSI ATtiny13 -> MISO programer(Digital Pin 11), MISO->MOSI(Digital Pin 12), SCK->SCK(Digital Pin 13) RES->Reset(Digital Pin 10). How to flash ATtiny13 with Arduino:

https://www.hackster.io/taunoerik/programming-attiny13-with-arduino-uno-07beba

![FLASH](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/FLASH.png)

ATtiny13 core selections:

- Board: ATtiny 13

- BOD: BOD Disabled

- Clock: 1.2 MHz internal osc.

- Compiler LTO: Enable

- Port: (Your Arduino port)

- Programmer: Arduino as ISP

![Arduino IDE](https://github.com/techn0man1ac/ATtiny13BinaryWatches/blob/82cb183568d90e219ba5d9926f93f70cab1a7d6e/Imgs/ArduinoIDE.png)

Source code(for Arduino IDE - "t13B Watches.ino") here:

https://github.com/techn0man1ac/ATtiny13BinaryWatches/tree/main/t13BinWatches

It's project full open source(PCB and code).

# Schematic:

It's have simple schematic, there are 15 components in total:

![Schematic clock](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/PCB/Schematic/Schematic_ATtiny13BinaryWatches_2023-08-30.png)

# Gerber files and 3D model:

https://github.com/techn0man1ac/ATtiny13BinaryWatches/tree/main/PCB

