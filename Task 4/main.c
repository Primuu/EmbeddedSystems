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


void Update_POWER_TIME (int, int) ;
void SYS_Initialize ( void ) ;
extern void ConvertADCVoltage ( unsigned int  ) ;
extern void Hex2Dec ( unsigned char ) ;


APP_DATA appData = {
                    .messageLine1 = "Moc:        800W" ,
                    .messageLine2 = "Czas:      00:00" 
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

    int powerState = 0;
    int secondsLeft = 0;
    int working = 0;

    /* Call the System Intialize routine*/
    SYS_Initialize ( ) ;

    /* Display welcome message */
    LCD_PutString ( (char*) &appData.messageLine1[0] , sizeof (appData.messageLine1 ) - 1  ) ;
    LCD_PutString ( (char*) &appData.messageLine2[0] , sizeof (appData.messageLine2 ) - 1  ) ;

    /*Initialize Timer*/
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;

    /*Initialize ADC configure it as 10 bit interrupt driven mode*/
    ADC_SetConfiguration ( ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT ) ;

    /* Infinite Loop */
    while ( 1 )
    {

        // Add power
        if (BUTTON_IsPressed( BUTTON_S3 )) {
            if (powerState < 3) {
              powerState++;
            }
            else {
              powerState = 0;
            }
          Update_POWER_TIME (powerState, secondsLeft);
          delay1s();
        }

        // Add time 
        if (BUTTON_IsPressed( BUTTON_S6 )) {
          secondsLeft = secondsLeft + 30;
          Update_POWER_TIME (powerState, secondsLeft);
          delay1s();
        }

        // Start/Stop - button may not work
        // Comment LED_Enable ( LED_D10 ) ;
        if (BUTTON_IsPressed( BUTTON_S5 )) {
          if (working == 0) {
            working = 1;
          }
          else if (working == 1) {
            working = 0;
          }
          delay1s();
        }

        // Reset
        if (BUTTON_IsPressed( BUTTON_S4 )) {
          powerState = 0;
          secondsLeft = 0;
          Update_POWER_TIME (powerState, secondsLeft);
          delay1s();
        }

        if (working == 1) {
            if (secondsLeft > 0) {
                secondsLeft = secondsLeft - 1;
                Update_POWER_TIME (powerState, secondsLeft);
            }
          if (secondsLeft == 0) {
            working = 0;
          }
          delay1s();
        }

    }
}

void Update_POWER_TIME (int powerState, int secondsLeft)
{

    // ***** P O W E R *************************************************

    char powerChar = '8';
    char powerChar2 = '0';

    if (powerState == 1) {
      powerChar = '6';
    }
    if (powerState == 2) {
      powerChar = '3';
      powerChar2 = '5';
    }
    if (powerState == 3) {
      powerChar = '2';
    }

    LCD_PutChar ( 'M' ) ;
    LCD_PutChar ( 'o' ) ;
    LCD_PutChar ( 'c' ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;

    LCD_PutChar ( powerChar ) ;
    LCD_PutChar ( powerChar2 ) ;
  
    LCD_PutChar ( '0' ) ;
    LCD_PutChar ( 'W' ) ;

    // ***** T I M E **************************************************

    int tensMinutes = (secondsLeft / 60) / 10;
    int onesMinutes = (secondsLeft / 60) % 10;
    int tensSeconds = (secondsLeft % 60) / 10;
    int onesSeconds = (secondsLeft % 60) % 10;

    LCD_PutChar ( 'C' ) ;
    LCD_PutChar ( 'z' ) ;
    LCD_PutChar ( 'a' ) ;
    LCD_PutChar ( 's' ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;

    LCD_PutChar(tensMinutes + '0');
    LCD_PutChar(onesMinutes + '0');
    LCD_PutChar(':');
    LCD_PutChar(tensSeconds + '0');
    LCD_PutChar(onesSeconds + '0');

}
