/*
 * IRremote: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */
#include <Wire.h>
#include <AllAboutEE_IRControl.h>
#include <AllAboutEE_decoder_results.h>
#include <AllAboutEE_IRrecv.h>

using namespace AllAboutEE;

int RECV_PIN = 3;

IRrecv irrecv(RECV_PIN);

decoder_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void output(decoder_results *results);

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    output(&results);
    irrecv.resume(); // Receive the next value
  }
}
void output(decoder_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  } 
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  } 
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  } 
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {	
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->panasonicAddress,HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
     Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
     Serial.print("Decoded JVC: ");
  
  }

  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
}