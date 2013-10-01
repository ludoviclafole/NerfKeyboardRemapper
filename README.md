NerfKeyboardRemapper
====================

Project on arduino to remap HID keyboard on a usb hub to a computer to simulate a choosen mapping from another one.

extracted informations from the web :

= Report : =

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

= Modifiers : =

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
