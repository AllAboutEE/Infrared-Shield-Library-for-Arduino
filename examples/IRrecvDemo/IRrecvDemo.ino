/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
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

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
