#include <plib.h>
#include <stdlib.h>

#include "./user.h"
#include "./ledmatrix_ws2812.h"

#include "./animation_data/pattern.h"
#include "./animation_data/animationA.h"
#include "./animation_data/animationB.h" //BROKEN
#include "./animation_data/animationD.h" //NOAMRL BLINK
#include "./animation_data/animationF.h"
#include "./animation_data/animationJ.h" //WAVE
#include "./animation_data/animationL.h" //HANABI
//#include "./animation_data/suika.h"
#include "./animation_data/sleep_heart.h" //SLEEP HEART
//#include "./animation_data/star.h" //STAR
//#include "./animation_data/garapiko17.h" //KAERU,ONPU,KARASU
//#include "./animation_data/patolamp_hasami.h" //KAMIFUBUKI,JAJAN
//#include "./animation_data/cho2.h" //
//#include "./animation_data/chulip.h" //
//#include "./animation_data/heart_20160810.h" //
//#include "./animation_data/pencil.h" //
//#include "./animation_data/leaf_20160830.h" //
#include "./animation_data/doripon.h"
#include "./animation_data/hoshinoki.h"


unsigned char aCnt;
unsigned char frameCount;
unsigned char firstReset;


void __ISR(_UART_1_VECTOR, IPL4) U1RXHandler(void) {
    unsigned char RcvData;
    IFS1bits.U1RXIF = 0;
    RcvData = getcUART1();
    if (RcvData == 255) {
        dataPos = 0;
    } else {
        if (
                RcvData == 'X' || RcvData == 'G'
                || RcvData == 'O' || RcvData == 'P'

                || RcvData == 'U' || RcvData == 'D'
                || RcvData == 'L' || RcvData == 'R'

                || RcvData == 'g' //STK-L LEFT
                || RcvData == 'h' //STK-L RIGHT
                || RcvData == 'i' //STK-L UP
                || RcvData == 'j'

                || RcvData == 'k' //STK-R LEFT
                || RcvData == 'l' //STK-R RIGHT
                || RcvData == 'm' //STK-R UP
                || RcvData == 'n' //STK-R DOWN


                || RcvData == 'a' //L1
                || RcvData == 'b' //R1
                || RcvData == 'c' //L2
                || RcvData == 'd' //R2
                ) {

            if (lastData != RcvData) {
                myData[dataPos] = RcvData;

                if (RcvData == 'k' || RcvData == 'l' || RcvData == 'h' || RcvData == 'i' || RcvData == 'g'
                        || RcvData == 'U' || RcvData == 'D' || RcvData == 'L' || RcvData == 'R'
                        || RcvData == 'X'

                        || RcvData == 'm' //STK-R UP
                        || RcvData == 'n' //STK-R DOWN
                        ) {
                    frameCount = 0;
                    aCnt = 0;
                } else {
                    deletePattern();
                }
            }
            dataPos++;

            if (dataPos >= 2)dataPos = 0;
        }
    }
    lastData = myData[0];
}

int main(void) {
    unsigned int i;

    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();
    INTEnableInterrupts();

    ANSELA = 0x0000; // all digital pins
    ANSELB = 0x0000;

    TRISB = 0;
    TRISA = 0;

    InitUart1();

    resetAnimation();

    while (1) {
        frameCount++;
        switch (myData[0]) {

            default:
                myData[0] = 0;
                deletePattern();
                break;

                //UP
            case 'U':

                //                setPattern(pencil_sample, 1);
                myData[0] = 0;
                deletePattern();
                break;

                //DOWN
                //HANABI
            case 'D':
                if (frameCount % 3 == 0) {
                    frameCount = 0;
                    aCnt++;
                    if (aCnt >= sizeof (hanabi_frame) / sizeof (unsigned char)) {
                        aCnt = sizeof (hanabi_frame) / sizeof (unsigned char) - 1;
                        myData[0] = 0;
                        deletePattern();
                    }
                }
                setPattern(hanabi[hanabi_frame[aCnt]], 2);
                break;


                //LEFT
                //NORMAL BLINK
            case 'L':
                if (frameCount % 16 == 0) {
                    frameCount = 0;
                    aCnt++;
                    if (aCnt >= sizeof (normal_frame) / sizeof (unsigned char)) {
                        aCnt = 0;
                    }
                }
                setPattern(normal[normal_frame[aCnt]], 1);
                break;

                //RIGHT 
                //BROKEN BLINK
            case 'R':
                if (frameCount % 3 == 0) {
                    frameCount = 0;

                    aCnt++;
                    if (aCnt >= sizeof (broken_frame) / sizeof (unsigned char)) {
                        aCnt = 0;
                    }
                }
                setPattern(broken[broken_frame[aCnt]], 1);
                break;

                //BATSU
                //DELETE
            case 'X':
                myData[0] = 0;
                deletePattern();
                break;

                //SANKAKU
                //BATSU
            case 'G':
                setPattern(batsu, 1);
                break;

                //MARU
            case 'O':
                //HATENA?
                setPattern(hatena, 1);
                break;

                //SIKAKU
            case 'P':
                //BREAK HEART
                setPattern(break_heart, 1);
                break;

                //STK-L LEFT
            case 'g':
                //nothing
                 myData[0] = 0;
                deletePattern();

                break;
                //STK-L RIGHT
                //ENERGY
            case 'h':
                if (frameCount % 4 == 0) {
                    frameCount = 0;
                    aCnt++;
                    if (aCnt >= sizeof (frameA_1) / sizeof (unsigned char)) {
                        aCnt = sizeof (frameA_1) / sizeof (unsigned char) - 1;
                    }
                }
                setPattern(animationA[frameA_1[aCnt]], 2);
                break;

                //STK-L UP
                //START UP
            case 'i':
                if (frameCount % 4 == 0) {
                    frameCount = 0;
                    aCnt++;
                    if (aCnt >= sizeof (startup_frame) / sizeof (unsigned char)) {
                        aCnt = sizeof (startup_frame) / sizeof (unsigned char) - 1;
                        myData[0] = 0;
                        deletePattern();
                    }
                }
                setPattern(startup[startup_frame[aCnt]], 2);
                break;

                //STK-L DOWN
            case 'j':

                myData[0] = 0;
                deletePattern();

                break;

                //STK-R LEFT
            case 'k':
                //SLEEPHEART
                if (frameCount % 5 == 0) {
                    aCnt++;
                    if (aCnt >= sizeof (frameSleepHeart_2) / sizeof (unsigned char)) {
                        aCnt = sizeof (frameSleepHeart_2) / sizeof (unsigned char) - 1;
                    }
                }
                setPattern(sleep_heart[frameSleepHeart_2[aCnt]], 1);
                break;

                //STK-R RIGHT
            case 'l':
                //SLEEPHEART
                if (frameCount % 5 == 0) {
                    aCnt++;
                    if (aCnt >= sizeof (frameSleepHeart_1) / sizeof (unsigned char)) {
                        aCnt = sizeof (frameSleepHeart_1) / sizeof (unsigned char) - 1;
                    }
                }
                setPattern(sleep_heart[frameSleepHeart_1[aCnt]], 1);
                break;

                //STK-R UP
            case 'm':
                //hoshinoki
                if (frameCount % 4 == 0) {
                    frameCount = 0;
                    aCnt++;
                    if (aCnt >= sizeof (frame_hoshinoki) / sizeof (unsigned char)) {
                        aCnt = sizeof (frame_hoshinoki) / sizeof (unsigned char) - 1;
                        myData[0] = 0;
                        deletePattern();
                    }
                }
                setPattern(hoshinoki[frame_hoshinoki[aCnt]], 2);

                break;

                //STK-R DOWN
            case 'n':
                //doripon
                if (frameCount % 3 == 0) {
                    frameCount = 0;
                    aCnt++;
                    if (aCnt >= sizeof (frame_doripon) / sizeof (unsigned char)) {
                        aCnt = sizeof (frame_doripon) / sizeof (unsigned char) - 1;
                    }
                }
                setPattern(doripon[frame_doripon[aCnt]], 3);

                break;
        }

        show();


    }
}

