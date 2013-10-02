NerfKeyboardRemapper
====================

Project on arduino to remap HID keyboard on a usb hub to a computer to simulate a choosen mapping from another one.

extracted informations from the web :

### Report :

| byte |  value      |
|:----:|:------------|
| 0    | modifiers   |
| 1    | 0x00 FIXED  |
| 2    | key 0 value |
| 3    | key 1 value |
| 4    | key 2 value |
| 5    | key 3 value |
| 6    | key 4 value |
| 7    | key 5 value |

### Modifiers :

| bit | KEY     |
|:---:|---------|
|  0  | L CTRL  |
|  1  | L SHIFT |
|  2  | L ALT   |
|  3  | L GUI   |
|  4  | R CTRL  |
|  5  | R SHIFT |
|  6  | R ALT   |
|  7  | R GUI   |

### Reprogram Arduino :

* http://arduino.cc/en/Hacking/DFUProgramming8U2
* http://forums.adafruit.com/viewtopic.php?f=25&t=25146 && http://academic.cleardefinition.com/2012/07/31/using-dfu-programmer-with-an-arduino-uno-r3/

### Prepare Arduino AT16U2 reprog

```
 wget http://sourceforge.net/projects/dfu-programmer/files/dfu-programmer/0.6.2/dfu-programmer-0.6.2.tar.gz
 tar xzf dfu-programmer-0.6.2.tar.gz
 cd dfu-programmer-0.6.2
 ./bootstrap.sh
 ./configure
 make
 sudo make install
```

#### INSTALLED ^^

### switch arduino from arduino to keyboard (and revert)

```
 ./toKeyboard.sh
```

```
 ./toArduino.sh
```
