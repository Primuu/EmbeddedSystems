#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "app.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************


void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void ConvertADCVoltage ( unsigned int  ) ;
extern void Hex2Dec ( unsigned char ) ;


APP_DATA appData = {
                    .message1Line1 = "  Wybierz czas: " ,
                    .message1Line2 = "                " ,

                    .message2 = "     5 minut    " ,
                    .message3 = "    3 minuty    " ,
                    .message4 = "    1 minuta    " ,

                    .messagePlayer1TimeEndLine1 = "Gracz 1 przegral" ,
                    .messagePlayer2TimeEndLine1 = "Gracz 2 przegral" ,
                    .messagePlayerTimeEndLine2 = "  koniec czasu  " 

} ;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void delay1s() {
    unsigned int i;
    unsigned char j;

    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 200; j++) {
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
        }
    }
}

int main ( void )
{

    int time = 0;
    int secondsLeft1 = 0;
    int secondsLeft2 = 0;

    int gameOn = 0;

    int player1Turn = 0;
    int player2Turn = 0;

    /* Call the System Intialize routine*/
    SYS_Initialize ( ) ;

    /* Display welcome message */
    LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
    LCD_PutString ( (char*) &appData.message1Line2[0] , sizeof (appData.message1Line2 ) - 1  ) ;

    /*Initialize Timer*/
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;

    /*Initialize ADC configure it as 10 bit interrupt driven mode*/
    ADC_SetConfiguration ( ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT ) ;
    
    /* Infinite Loop */
    while ( 1 )
    {

        float percent = (appData.adones - '0') + (appData.adtens - '0') * 0.1f + (appData.adhunds - '0') * 0.01f;
        percent = percent * 100 / 3.30f;

        if (gameOn == 0) {
            if(percent < 33) {
            time = 60;
            LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
            LCD_PutString ( (char*) &appData.message4[0] , sizeof (appData.message4 ) - 1  ) ;
          }

          if(percent => 33 && percent < 67) {
            time = 180;
            LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
            LCD_PutString ( (char*) &appData.message3[0] , sizeof (appData.message3 ) - 1  ) ;
          }

          if(percent => 67) {
            time = 300;
            LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
            LCD_PutString ( (char*) &appData.message2[0] , sizeof (appData.message2 ) - 1  ) ;
          }
        } 

        // Start player 1
        if (BUTTON_IsPressed( BUTTON_S3 )) {
          if (gameOn == 0) {
            secondsLeft1 = time;
            secondsLeft2 = time;
          }

          gameOn = 1;

          player2Turn = 1;
          player1Turn = 0;

          Update_TIME (secondsLeft1, secondsLeft2);
          delay1s();
        }

        // Start player 2
        if (BUTTON_IsPressed( BUTTON_S6 )) {
          if (gameOn == 0) {
            secondsLeft1 = time;
            secondsLeft2 = time;
          }

          gameOn = 1;

          player1Turn = 1;
          player2Turn = 0;

          Update_TIME (secondsLeft1, secondsLeft2);
          delay1s();
        }

        // Timer
        if (gameOn == 1) {

          if (player1Turn == 1) {
            secondsLeft1 = secondsLeft1 - 1;
            Update_TIME (secondsLeft1, secondsLeft2);
            delay1s();
          }

          if (player2Turn == 1) {
            secondsLeft2 = secondsLeft2 - 1;
            Update_TIME (secondsLeft1, secondsLeft2);
            delay1s();
          }


          if(secondsLeft1 == 0){
              LCD_PutString ( (char*) &appData.messagePlayer1TimeEndLine1[0] , sizeof (appData.messagePlayer1TimeEndLine1 ) - 1  ) ;
              LCD_PutString ( (char*) &appData.messagePlayerTimeEndLine2[0] , sizeof (appData.messagePlayerTimeEndLine2 ) - 1  ) ;
              delay1s();
              delay1s();
              delay1s();
              delay1s();
              delay1s();
              delay1s();
              time = 0;
              secondsLeft1 = 0;
              secondsLeft2 = 0;
              gameOn = 0;
              player1Turn = 0;
              player2Turn = 0;
          }

          if(secondsLeft2 == 0){
              LCD_PutString ( (char*) &appData.messagePlayer2TimeEndLine1[0] , sizeof (appData.messagePlayer2TimeEndLine1 ) - 1  ) ;
              LCD_PutString ( (char*) &appData.messagePlayerTimeEndLine2[0] , sizeof (appData.messagePlayerTimeEndLine2 ) - 1  ) ;
              delay1s();
              delay1s();
              delay1s();
              delay1s();
              delay1s();
              delay1s();
              time = 0;
              secondsLeft1 = 0;
              secondsLeft2 = 0;
              gameOn = 0;
              player1Turn = 0;
              player2Turn = 0;
          }

        }

    } 
}

void Update_TIME (int secondsLeft1, int secondsLeft2)
{
    LCD_PutChar ( 'G' ) ;
    LCD_PutChar ( 'r' ) ;
    LCD_PutChar ( 'a' ) ;
    LCD_PutChar ( 'c' ) ;
    LCD_PutChar ( 'z' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( '1' ) ;

    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;

    LCD_PutChar ( 'G' ) ;
    LCD_PutChar ( 'r' ) ;
    LCD_PutChar ( 'a' ) ;
    LCD_PutChar ( 'c' ) ;
    LCD_PutChar ( 'z' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( '2' ) ;

// ***** T I M E **************************************************

    int onesMinutesPlayer1 = (secondsLeft1 / 60) % 10;
    int tensSecondsPlayer1 = (secondsLeft1 % 60) / 10;
    int onesSecondsPlayer1 = (secondsLeft1 % 60) % 10;

    int onesMinutesPlayer2 = (secondsLeft2 / 60) % 10;
    int tensSecondsPlayer2 = (secondsLeft2 % 60) / 10;
    int onesSecondsPlayer2 = (secondsLeft2 % 60) % 10;

    LCD_PutChar(onesMinutesPlayer1 + '0');
    LCD_PutChar(':');
    LCD_PutChar(tensSecondsPlayer1 + '0');
    LCD_PutChar(onesSecondsPlayer1 + '0');

    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;

    LCD_PutChar(onesMinutesPlayer2 + '0');
    LCD_PutChar(':');
    LCD_PutChar(tensSecondsPlayer2 + '0');
    LCD_PutChar(onesSecondsPlayer2 + '0');

}
