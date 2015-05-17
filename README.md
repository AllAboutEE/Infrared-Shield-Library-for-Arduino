# Infared Remote Control Shield for Arduino Development Board

![Infrared remote control shield for Arduino](https://raw.github.com/AllAboutEE/Infrared-Shield-for-Arduino/master/Hardware/Arduino-Infrared-Shield-Remote-Control-Angle-View.jpg)

## Software Library
The library we developed for this shield is a fork from the [most popular IR shield library](https://github.com/shirriff/Arduino-IRremote).

### Installation/Setup
[Download the latest release ZIP file from this page](https://github.com/AllAboutEE/Arduino-Infrared-Shield-Library/releases), extract the contents and put them in the Arduino "libraries" folder.

### Examples

* All-in-one: TV, Fan, Xbox One media control - Let's you control various devices
* XboxOne media remote - Works like an [XboxOne infrared media remote](http://www.xbox.com/en-US/xbox-one/accessories/controllers/media-remote), but not for playing games (can only be used to navigate XboxOne content)
* TV - Remote control for a [Hisense TV model 50K610GWN](http://global.hisense.com/product/northa/tv/led/K610/201401/t20140117_86826.htm)
* Fan - Remote control for [Lasko fan model u35102](http://www.laskoproducts.com/oscillating-high-velocity-fan-with-remote-control-model-u35102/)
* Lightbulb - Remote control for [RGB light bulb](http://www.amazon.com/SUPERNIGHT-Standard-Changing-Dimmable-Decoration/dp/B00CEOSGRY/ref=sr_1_sc_1?ie=UTF8&qid=1431819498&sr=8-1-spell&keywords=rgb+ir+light+bolb)

## Hardware

### Basic Connections

* Receives IR signal on digital pin 4
* Transmits IR signal through digital pin 9
* Reads buttons through I2C port


### Specs

* Transmit Range: 
* Receive Range:
