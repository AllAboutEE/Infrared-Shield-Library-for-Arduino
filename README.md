# Infared Remote Control Shield for Arduino Development Board

![Infrared remote control shield for Arduino](https://raw.github.com/AllAboutEE/Infrared-Shield-for-Arduino/master/Hardware/Arduino-Infrared-Shield-Remote-Control-Angle-View.jpg)

### Examples

The example sketches are located in the "exapmles" folder, they include:

* All-in-one: TV, Fan, Xbox One media control - Let's you control various devices
* XboxOne media remote - simulates the [XboxOne infrared media remote](http://www.xbox.com/en-US/xbox-one/accessories/controllers/media-remote), but not for playing games (can only be used to navigate XboxOne content)
* TV - simulates a control for a [Hisense TV model 50K610GWN](http://global.hisense.com/product/northa/tv/led/K610/201401/t20140117_86826.htm)
* Fan - simulates a control for a [Lasko fan model u35102](http://www.laskoproducts.com/oscillating-high-velocity-fan-with-remote-control-model-u35102/)
* Lightbulb - simulates the control for an [RGB light bulb](http://www.amazon.com/SUPERNIGHT-Standard-Changing-Dimmable-Decoration/dp/B00CEOSGRY/ref=sr_1_sc_1?ie=UTF8&qid=1431819498&sr=8-1-spell&keywords=rgb+ir+light+bolb)
* Decoder examples so you can make your own!

## Compatibility:

* These software libraries are only compatible with Arduino Uno R3, and Arduino Mega 2560 R3. The shield might be comptabile with other software libraries for other Arduino boards if and only if the libraries support a receiver on digital pin 4, and a transmitter on digital pin 9.

* The Arduino board you use needs to have the two I2C pins SCL and SDA above the AREF pin. See photos [Uno Front](http://www.arduino.cc/en/uploads/Main/ArduinoUno_R3_Front.jpg), and [Uno Back](http://www.arduino.cc/en/uploads/Main/ArduinoUno_R3_Back.jpg) for reference.

## Hardware
See [Infrared Shield for Arduino](https://github.com/AllAboutEE/Infrared-Shield-for-Arduino) for specs, schematics, etc.

## Software Library
The library we developed for this shield is a fork from the [most popular IR shield library](https://github.com/shirriff/Arduino-IRremote).

### Installation/Setup
[Download the latest release ZIP file from this page](https://github.com/AllAboutEE/Arduino-Infrared-Shield-Library/releases), extract the contents and put them in the Arduino "libraries" folder.

### How To Decode/Receive IR Signals

    To decode infrared (IR) signals from any control:

1. Upload example "IRrecvDump" to your Arduino board.
2. Open the serial monitor with the settings "No line ending" and "9600 baud"
3. Send an IR signal to the receiver:
  * Point the control you are trying to decode to the shield's receiver
  * Press a key on the control you are trying to decode

You will see an output similar to the following in the serial monitor window:

    Decoded NEC: FF609F (32 bits)
    Raw (68): -16246 8950 -4500 600 -550 550 -600 500 -600 550 -550 600 -550 550 -550 550 -600 550 -550 550 -1700 550 -1650 600 -1700 550 -1700 550 -1650 600 -1700 550 -1650 600 -1650 600 -550 600 -1650 600 -1650 550 -600 550 -550 600 -550 550 -550 550 -600 550 -1650 600 -550 550 -600 500 -1700 600 -1650 600 -1650 550 -1700 600 -1650 600 

The first line in the output is the decoded IR code and protocol (if it was recognized).
The second line in the output is the raw signal. This might be the only line you see if the IR shield did not identify a specific IR protocol. This raw output needs some cleaning (we'll show you how to use it below).

### Raw Codes

Some remote controls you decode might not use any standard IR protocol, in this case you will only receive a raw code that will look similar to the following:

    Raw (68): -16246 8950 -4500 600 -550 550 -600 500 -600 550 -550 600 -550 550 -550 550 -600 550 -550 550 -1700 550 -1650 600 -1700 550 -1700 550 -1650 600 -1700 550 -1650 600 -1650 600 -550 600 -1650 600 -1650 550 -600 550 -550 600 -550 550 -550 550 -600 550 -1650 600 -550 550 -600 500 -1700 600 -1650 600 -1650 550 -1700 600 -1650 600 
    
This raw code needs some cleaning however:

1. Copy and paste the code into a text editor like notepad
2. Delete the first element, in this case "-16246"
3. Remove the negative signs e.g. -550 will become 550, -600 will become 600

The raw code should now look like this for the example above:

    Raw (68):  8950 4500 600 550 550 600 500 600 550 550 600 550 550 550 550 600 550 550 550 1700 550 1650 600 1700 550 1700 550 1650 600 1700 550 1650 600 1650 600 550 600 1650 600 1650 550 600 550 550 600 550 550 550 550 600 550 1650 600 550 550 600 500 1700 600 1650 600 1650 550 1700 600 1650 600 

Each element respresents a high or low pulse in micro-seconds. The code starts with a high pulse then alternates to low, then high again and so on. It is ready to be used, continue reading below.

## How To Send IR Signals

Note: For a complete code example see example "TV_XboxOne_Fan_Control".

Let's assume you have the following IR decoded output:

    Decoded NEC: FF609F (32 bits)
    Raw (68):  8950 4500 600 550 550 600 500 600 550 550 600 550 550 550 550 600 550 550 550 1700 550 1650 600 1700 550 1700 550 1650 600 1700 550 1650 600 1650 600 550 600 1650 600 1650 550 600 550 550 600 550 550 550 550 600 550 1650 600 550 550 600 500 1700 600 1650 600 1650 550 1700 600 1650 600 

### Assign a signal to a button

You can use the recognized protol code:

```cpp
    irControl.setButtonCode(
      IRControl::buttonY, // assign the code to button Y
      IRControl::NEC, // IR protocol
      0xFF609F, // infrared code
      32 // length of ir code
    );
```

The available protocols are:

    	NEC
    	SONY
    	RC5
    	RC6
    	DISH
    	SENDSHARPRAW
    	SAMSUNG
    	RAW

Or you can use the raw code. First, make an array from the raw code:

    unsigned int raw_code[] = {8950,4500,600,550,550,600,500,600,550,550,600,550,550,550,550,600,550,550,550,1700,550,1650,600,1700,550,1700,550,1650,600,1700,550,1650,600,1650,600,550,600,1650,600,1650,550,600,550,550,600,550,550,550,550,600,550,1650,600,550,550,600,500,1700,600,1650,600,1650,550,1700,600,1650,600};
           
Now assign the array to a button:
```cpp
    // configure Z button
     irControl.setButtonRawCode(
       IRControl::buttonZ, // assign the code to button z
       raw_code, // array name
       sizeof(raw_code)/sizeof(raw_code[0]) // length of ir code
    );
```

### Send Signals Automatically i.e. Without Needing a Button Press

See example [Send_Without_Button_Press](https://github.com/AllAboutEE/Infrared-Shield-Library-for-Arduino/blob/master/examples/Send_Without_Button_Press/Send_Without_Button_Press.ino)
