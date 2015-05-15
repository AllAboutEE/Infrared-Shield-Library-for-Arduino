/*
 * IRremote
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.htm http://arcfn.com
 * Edited by Mitra to add new controller SANYO
 *
 * Interrupt code based on NECIRrcv by Joe Knapp
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
 * Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
 *
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
* LG added by Darryl Smith (based on the JVC protocol)
 */

#ifndef ALLABOUTEE_DECODER_RESULTS_H
#define ALLABOUTEE_DECODER_RESULTS_H

// The following are compile-time library options.
// If you change them, recompile the library.
// If DEBUG is defined, a lot of debugging output will be printed during decoding.
// TEST must be defined for the IRtest unittests to work.  It will make some
// methods virtual, which will be slightly slower, which is why it is optional.
// #define DEBUG
// #define TEST

// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100


    // Results returned from the decoder
    class decoder_results {
    public:
      int decode_type; // NEC, SONY, RC5, UNKNOWN
      union { // This is used for decoding Panasonic and Sharp data
        unsigned int panasonicAddress;
        unsigned int sharpAddress;
      };
      unsigned long value; // Decoded value
      int bits; // Number of bits in decoded value
      volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
      int rawlen; // Number of records in rawbuf.
    };




#endif
