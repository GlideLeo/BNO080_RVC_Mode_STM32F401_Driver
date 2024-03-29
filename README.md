# BNO080_RVC_Mode_STM32F401_Driver
[![LICENSE](https://img.shields.io/badge/license-Anti%20996-blue.svg)](https://github.com/996icu/996.ICU/blob/master/LICENSE)

## Description
* This is a BNO080 STM32 driver when BNO080 is set to UART-RVC mode, the demo code is generated by STM32 CubeMX and the .ioc file is included in the demo,open the .ioc file, you can find some IO settings etc.
* Driver source file is in the "BNO080_RVC_Driver" folder.(Yep! Very simple actually)

## How to use 
* Make sure the KeilMDK software has been installed, then open "BNO080_RVC.uvprojx" file you will see the whole project.

![](https://github.com/JassyL/BNO080_RVC_Mode_STM32F401_Driver/blob/master/photos/pic3.jpg)

* I use UART1 to connect the BNO080 moduel,  UART2 used to support printf, you mat need a USB2TTL moduel to attach UART2 pins.

* **Confirm that your module has been set to UART-RVC mode**, otherwise you will not receive data.Detailed information can be referred to BNO080 datasheet(In the "doc" folder). For example, it's very esay to set RVC mode with this purple moduel, connect two pads of PS0,that's all I need to do.
![](https://github.com/JassyL/BNO080_RVC_Mode_STM32F401_Driver/blob/master/photos/pic4.jpg)

* Open any serial debugging assistant, set baud rate 115200.

![](https://github.com/JassyL/BNO080_RVC_Mode_STM32F401_Driver/blob/master/photos/pic2.jpg)

![](https://github.com/JassyL/BNO080_RVC_Mode_STM32F401_Driver/blob/master/photos/pic1.jpg)

## License
* Anti 996 License Version 1.0
