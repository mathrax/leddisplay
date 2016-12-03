/* 
 * File:   user.h
 * Author: MATHRAX
 *
 * Created on December 3, 2016, 4:15 PM
 */

// SYSCLK = 40 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK  = 40 MHz
#define SYSCLK  40000000L                      //
#define FCY          SYSCLK
#define SYSCLKdiv10MHz    (SYSCLK/10000000)    //
#define GetSystemClock()       (SYSCLK)




//VALUE

#define neopixel_pin      LATBbits.LATB9
#define TRIS_TX1                TRISBbits.TRISB3
#define TRIS_RX1                TRISBbits.TRISB2

extern unsigned char red[1024];
extern unsigned char blu[1024];
extern unsigned char grn[1024];

extern unsigned char myRed;
extern unsigned char myGrn;
extern unsigned char myBlu;

extern unsigned char aCnt;
extern unsigned char frameCount;
extern unsigned char firstReset;

extern unsigned char dataPos;
extern unsigned char myData[2];
extern unsigned char lastData;

/******************************************************************************/
/* User Function Prototypes                                                    /
/******************************************************************************/


void InitUart1(void);
void setPixelColor(unsigned int pixel, unsigned char r, unsigned char g, unsigned char b);
void show(void);
void deletePattern(void);
void resetAnimation(void);



