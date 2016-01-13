# BeMAP - Arduino tools

> These instructions has been tested on Debian 8.

You have to have the arduino IDE installed in your computer. Check the https://www.arduino.cc/en/Main/Software to know how to install it.

After that, you should add the arduino path to the ```/path/to/bemap/arduino/global.conf``` file. You can check how to do it on [bemap/arduino/global.conf.template][global_conf_template].

## BeMAP Arduino Enviroment

You can use your favourite text editor (sublime, atom...) for editing the code and the terminal for compile and upload the code to the board.

## Upload a program
There is the arduino blink example for testing.

Check the `/path/to/bemap/arduino/Blink/arduino.conf` file. Here, it's specified the board and the usb port for uploading the code.
```
board=arduino:avr:mega:cpu=atmega2560
port=/dev/ttyUSB0
```
Change it if it's necessary.

```sh
$ cd /path/to/bemap/arduino
$ ./compile.py Blink
```
*Blink* is the dirname.

[global_conf_template]: <https://github.com/bemap/bemap/blob/master/arduino/global.conf.template>
