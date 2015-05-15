/*************************************************** 
  This is a library for the MCP23008 i2c port expander

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
#include <avr/pgmspace.h>
#include "Adafruit_MCP23008.h"


////////////////////////////////////////////////////////////////////////////////
// RTC_DS1307 implementation

void Adafruit_MCP23008::begin(uint8_t addr) {
  if (addr > 7) {
    addr = 7;
  }
  i2caddr = addr;

  Wire.begin();

  // set defaults!
  Wire.beginTransmission(MCP23008_ADDRESS | i2caddr);
#if ARDUINO >= 100
  Wire.write((byte)MCP23008_IODIR);
  Wire.write((byte)0xFF);  // all inputs
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);
  Wire.write((byte)0x00);	
#else
  Wire.send(MCP23008_IODIR);
  Wire.send(0xFF);  // all inputs
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.send(0x00);
  Wire.send(0x00);	
#endif
  Wire.endTransmission();

}

void Adafruit_MCP23008::begin(void) {
  begin(0);
}

void Adafruit_MCP23008::pinMode(uint8_t p, uint8_t d) {
  uint8_t iodir;
  

  // only 8 bits!
  if (p > 7)
    return;
	
  //Setting a bit in the IODIR register makes the corresponding pin an INPUT,
  //and clearing a bit makes the corresponding pin an OUTPUT
  iodir = read8(MCP23008_IODIR);

  // set the pin and direction
  if (d == INPUT) {
    iodir |= 1 << p; 
  } else {
    iodir &= ~(1 << p);
  }

  // write the new IODIR
  write8(MCP23008_IODIR, iodir);
}

uint8_t Adafruit_MCP23008::readGPIO(void) {
  // read the current GPIO input 
  return read8(MCP23008_GPIO);
}

void Adafruit_MCP23008::writeGPIO(uint8_t gpio) {
  write8(MCP23008_GPIO, gpio);
}

void Adafruit_MCP23008::interruptMode(uint8_t p, uint8_t d){
  uint8_t inten;
  

  // only 8 bits!
  if (p > 7)
    return;
  
  //If a bit is set on the GPINTEN register, the corresponding pin is enabled for
  //interrupt-on-change. The DEFVAL and INTCON registers must also be configured
  inten = read8(MCP23008_GPINTEN);

  // set the pin and direction
  if (d == LOW) {
    inten &= ~(1 << p);
  } else {
    inten |= 1 << p; 
  }

  // write the new INTEN
  write8(MCP23008_GPINTEN, inten);
}

void Adafruit_MCP23008::writeDEFVAL(uint8_t defval){
	
	//The default comparison value is configured in the DEFVAL register. If enabled
	//to compare against the DEFVAL register, an opposite value on the 
	//associated pin will cause an interrupt to occur.
	if(defval > 0xFF)
		return;
	write8(MCP23008_DEFVAL, defval);
}

void Adafruit_MCP23008::writeINTCON(uint8_t val){
	
	//If a bit is set on the INTCON register, the corresponding I/O pin is compared
	//against the associated bit in the DEFVAL register. If a bit is cleared, the
	//corresponding I/O pin is compared against the previous value.
	if(val > 0xFF){
		val = 0xFF;
	}
	
	write8(MCP23008_INTCON, val);
}

uint8_t Adafruit_MCP23008::readINTF(void){
	 return read8(MCP23008_INTF);
}

uint8_t Adafruit_MCP23008::readINTCAP(void){
	
	//The INTCAP register captures the GPIO port value at the time the interrupt occurred.
	//the register is updated on when an interrupt occurs, and will remain unchanged until
	//the interrupt is cleared via a read of INTCAP or GPIO
	return read8(MCP23008_INTCAP);
}

void Adafruit_MCP23008::writeIOCON(uint8_t val){
	if(val > 0xFF){
		val = 0xFF;
	}
			
	write8(MCP23008_IOCON, val);
}

void Adafruit_MCP23008::writeIOCON_INTPOL(uint8_t val){
	uint8_t iocon;
	iocon = read8(MCP23008_IOCON);
	 
	if(val == 0){
		iocon = iocon & ~(1<<1);
	}else{
		iocon = iocon | (1<<1);
		}
	 
	writeIOCON(iocon);
}

void Adafruit_MCP23008::digitalWrite(uint8_t p, uint8_t d) {
  uint8_t gpio;
  
  // only 8 bits!
  if (p > 7)
    return;

  // read the current GPIO output latches
  gpio = readGPIO();

  // set the pin and direction
  if (d == HIGH) {
    gpio |= 1 << p; 
  } else {
    gpio &= ~(1 << p);
  }

  // write the new GPIO
  writeGPIO(gpio);
}

void Adafruit_MCP23008::pullUp(uint8_t p, uint8_t d) {
  uint8_t gppu;
  
  // only 8 bits!
  if (p > 7)
    return;

  //If a bit is set in the GPPU register, and the corresponding pin is configured
  //as an INPUT, the pull-up resistor for that pin is enabled.
  gppu = read8(MCP23008_GPPU);
  // set the pin and direction
  if (d == HIGH) {
    gppu |= 1 << p; 
  } else {
    gppu &= ~(1 << p);
  }
  // write the new GPIO
  write8(MCP23008_GPPU, gppu);
}

uint8_t Adafruit_MCP23008::digitalRead(uint8_t p) {
  // only 8 bits!
  if (p > 7)
    return 0;

  // read the current GPIO
  return (readGPIO() >> p) & 0x1;
}

uint8_t Adafruit_MCP23008::read8(uint8_t addr) {
  Wire.beginTransmission(MCP23008_ADDRESS | i2caddr);
#if ARDUINO >= 100
  Wire.write((byte)addr);	
#else
  Wire.send(addr);	
#endif
  Wire.endTransmission();
  Wire.requestFrom(MCP23008_ADDRESS | i2caddr, 1);

#if ARDUINO >= 100
  return Wire.read();
#else
  return Wire.receive();
#endif
}

void Adafruit_MCP23008::write8(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(MCP23008_ADDRESS | i2caddr);
#if ARDUINO >= 100
  Wire.write((byte)addr);
  Wire.write((byte)data);
#else
  Wire.send(addr);	
  Wire.send(data);
#endif
  Wire.endTransmission();
}
