/**
 * @brief Sends an NEC protocol IR signal without the use of any
 * buttons every 10 seconds. 
 *  
 * @author AllAboutEE
 *  
 * @date 05/17/2015 
 */

#include <Wire.h>
#include <AllAboutEE_IRsend.h>

using namespace AllAboutEE;

#define IR_CODE 0x20DF40BF


IRsend irsend;

void setup()
{

}

void loop()
{
    irsend.sendNEC(IR_CODE,32); // 32 is the number of IR bits in the code.
    delay(10000);
}


