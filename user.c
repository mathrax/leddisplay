/* 
 * File:   user.c
 * Author: MATHRAX
 *
 * Created on December 3, 2016, 4:14 PM
 */
#include <plib.h>
#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "ledmatrix_ws2812.h"

unsigned char dataPos;
unsigned char myData[2];
unsigned char lastData;

unsigned char red[1024];
unsigned char blu[1024];
unsigned char grn[1024];

unsigned char myRed;
unsigned char myGrn;
unsigned char myBlu;


void InitUart1() {

    TRIS_TX1 = 0;
    TRIS_RX1 = 1;

    // Create a UART TX/RX Pin
    SYSKEY = 0xAA996655; // Write Key1 to SYSKEY
    SYSKEY = 0x556699AA; // Write Key2 to SYSKEY

    U1RXRbits.U1RXR = 0b0100; //U1RX -- RB2
    RPB3Rbits.RPB3R = 0b0001; // U1TX -- RB3

    SYSKEY = 0; // Locks the pin Configurations

    U1MODE = 0;
    U1STA = 0;

    U1MODEbits.BRGH = 0; //16xbaud
    U1BRG = (FCY / (16 * 9600)) - 1;

    U1MODEbits.RTSMD = 1; //No flow control

    U1MODEbits.PDSEL = 0; //8bit noParuty
    U1MODEbits.STSEL = 0; //Stpbit 1

    U1STAbits.UTXEN = 0; //Tx disnable
    U1STAbits.URXEN = 1; //Rx enable

    U1MODEbits.UEN = 0; //NO CTS  & NO RTS
    U1MODEbits.ON = 1;

    IFS1bits.U1RXIF = 0;
    IEC1bits.U1RXIE = 1;

    IPC8bits.U1IP = 4; //Interrupts Priority

}


void setPattern(const unsigned char* ptn, unsigned char div) {
    unsigned char x, y;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {

            myRed = ptn[x + y * 16] >> div;
            myGrn = ptn[256 + x + y * 16] >> div;
            myBlu = ptn[512 + x + y * 16] >> div;

            setPixelColor((x * 2) + (y * 64), myRed, myGrn, myBlu);
            setPixelColor((x * 2) + (y * 64) + 1, myRed, myGrn, myBlu);
            setPixelColor(63 + (y * 64) - (x * 2), myRed, myGrn, myBlu);
            setPixelColor(63 + (y * 64) - (x * 2 + 1), myRed, myGrn, myBlu);
        }
    }
}

void setPixelColor(unsigned int pixel, unsigned char r, unsigned char g, unsigned char b) {

    red[pixel] = r;
    grn[pixel] = g;
    blu[pixel] = b;
}

void show() {
    unsigned int i;

    INTDisableInterrupts();

    neopixel_pin = 0;
    for (i = 0; i < 5000; i++) {
        Nop();
    }

    for (i = 0; i < 1024; i++) {
        //Bit7
        if (grn[i] & 0b10000000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit6
        if (grn[i] & 0b01000000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit5
        if (grn[i] & 0b00100000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit4
        if (grn[i] & 0b00010000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit3
        if (grn[i] & 0b00001000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit2
        if (grn[i] & 0b00000100) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit1
        if (grn[i] & 0b00000010) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }
        //Bit0
        if (grn[i] & 0b00000001) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }


        //Bit7
        if (red[i] & 0b10000000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit6
        if (red[i] & 0b01000000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit5
        if (red[i] & 0b00100000) {
            neopixel_pin = 1;
            Neopixel700us();
            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit4
        if (red[i] & 0b00010000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit3
        if (red[i] & 0b00001000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit2
        if (red[i] & 0b00000100) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit1
        if (red[i] & 0b00000010) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }
        //Bit0
        if (red[i] & 0b00000001) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }






        //Bit7
        if (blu[i] & 0b10000000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit6
        if (blu[i] & 0b01000000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit5
        if (blu[i] & 0b00100000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit4
        if (blu[i] & 0b00010000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit3
        if (blu[i] & 0b00001000) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit2
        if (blu[i] & 0b00000100) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }

        //Bit1
        if (blu[i] & 0b00000010) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {
            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }
        //Bit0
        if (blu[i] & 0b00000001) {
            neopixel_pin = 1;
            Neopixel700us();

            neopixel_pin = 0;
            Neopixel600us();

        } else {

            neopixel_pin = 1;
            Neopixel350us();
            neopixel_pin = 0;
            Neopixel700us();

        }
    }

    INTEnableInterrupts();

}

void deletePattern() {
    int i;
    for (i = 0; i < 1024; i++) {

        red[i] = 0;
        grn[i] = 0;
        blu[i] = 0;
    }
}

void resetAnimation() {
    int i = 0;

    for (i = 0; i < 1024; i++) {
        red[i] = 0;
        grn[i] = 0;
        blu[i] = 0;
    }
    frameCount = 0;
    aCnt = 0;

}

