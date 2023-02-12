# ATtiny13BinaryWatches

Simple Binary Watches with 4 LED(1/5, 2/10, 4/20, 8/40), it mean 5 minute accuracy indicate.

# How it's work?

Every 0.5 sec CPU wake up and increase milliseconds value and come sleep mode(4 uA). 

If you press button "SHOWTIME();" it show hours and minutes(0.5 seconds per value) in binary mode in 4 LEDs.

Source code(for Arduino IDE - "t13B Watches.ino") here:

https://github.com/techn0man1ac/ATtiny13BinaryWatches/tree/main/t13BinWatches

It's project full open source(PCB and code).

# 3D model PCB:
PCB Up side:

![PCB Up](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/PCBUpATtiny13BinaryWatches.png)

PCB Down side:

![PCB Down side](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/PCBDownATtiny13BinaryWatches.png)

PCB size 27 mm in diameter(size little biger CR2032 battery):

![PCB Down](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/Imgs/PCBSizesATtiny13BinaryWatches.png)

# PCB home page:

https://oshwlab.com/raznie.podelki/attiny13binarywatches

# Schematic:

It's have simple schematic, there are 11 components in total:

![PCB Down](https://raw.githubusercontent.com/techn0man1ac/ATtiny13BinaryWatches/main/PCB/Schematic/Schematic_ATtiny13BinaryWatches_2023-02-12.png)

I use CPU internal resistor for LED's.

# Gerber files and 3D model:

https://github.com/techn0man1ac/ATtiny13BinaryWatches/tree/main/PCB

