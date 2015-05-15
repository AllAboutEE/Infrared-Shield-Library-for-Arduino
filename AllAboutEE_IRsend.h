#ifndef AllAboutEE_IRsend_h
#define AllAboutEE_IRsend_h

#ifdef TEST
#define VIRTUAL virtual
#else
#define VIRTUAL
#endif

namespace AllAboutEE
{
    class IRsend
    {
    public:
        IRsend() {}
        void sendNEC(unsigned long data, int nbits);
        void sendSony(unsigned long data, int nbits);
        // Neither Sanyo nor Mitsubishi send is implemented yet
        //  void sendSanyo(unsigned long data, int nbits);
        //  void sendMitsubishi(unsigned long data, int nbits);
        void sendRaw(unsigned int buf[], int len, int hz);
        void sendRC5(unsigned long data, int nbits);
        void sendRC6(unsigned long data, int nbits);
        void sendDISH(unsigned long data, int nbits);
        void sendSharp(unsigned int address, unsigned int command);
        void sendSharpRaw(unsigned long data, int nbits);
        void sendPanasonic(unsigned int address, unsigned long data);
        void sendJVC(unsigned long data, int nbits, int repeat); // *Note instead of sending the REPEAT constant if you want the JVC repeat signal sent, send the original code value and change the repeat argument from 0 to 1. JVC protocol repeats by skipping the header NOT by sending a separate code value like NEC does.
        // private:
        void sendSAMSUNG(unsigned long data, int nbits);
        void enableIROut(int khz);
        VIRTUAL void mark(int usec);
        VIRTUAL void space(int usec);
    };
}


// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100

#endif
