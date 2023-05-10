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
                    .message1Line1 = "                " ,
                    .message1Line2 = "                " ,
                    
                    .message2Line1 = "      UWAGA     " ,
                    .message2Line2 = "    MIESOZERCO  " ,
                    
                    .message3Line1 = " jestes glodny? " ,
                    .message3Line2 = "  nowe burgery  " ,
                    
                    .message4Line1 = " JESTES GLODNY? " ,
                    .message4Line2 = "! NOWE BURGERY !" ,     
                    
                    .message5Line1 = "   Real-Burgir  " ,
                    .message5Line2 = "    ZAPRASZA    " ,
                    
                    .message6Line1 = " * * * * * * *  " ,
                    .message6Line2 = "* * * * * * * * " ,   
} ;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void delay(int ms) {
    unsigned int i;
    unsigned char j;

    for (i = 0; i < ms; i++) {
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

    /* Call the System Intialize routine*/
    SYS_Initialize ( ) ;
    
    /*Initialize Timer*/
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;

    /*Initialize ADC configure it as 10 bit interrupt driven mode*/
    ADC_SetConfiguration ( ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT ) ;

    while ( 1 )
    {
        
        LCD_PutString ( (char*) &appData.message2Line1[0] , sizeof (appData.message2Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message2Line2[0] , sizeof (appData.message2Line2 ) - 1  ) ;
    
        delay(1000);
        
// *****************************************************************************
// *****************************************************************************
        
        LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message1Line2[0] , sizeof (appData.message1Line2 ) - 1  ) ;
        
        delay(400);
        
        LCD_PutString ( (char*) &appData.message2Line1[0] , sizeof (appData.message2Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message2Line2[0] , sizeof (appData.message2Line2 ) - 1  ) ;
    
        delay(400);
        
        LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message1Line2[0] , sizeof (appData.message1Line2 ) - 1  ) ;
        
        delay(300);
        
        LCD_PutString ( (char*) &appData.message2Line1[0] , sizeof (appData.message2Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message2Line2[0] , sizeof (appData.message2Line2 ) - 1  ) ;
    
        delay(300);
        
        LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message1Line2[0] , sizeof (appData.message1Line2 ) - 1  ) ;
        
        delay(200);
        
        LCD_PutString ( (char*) &appData.message2Line1[0] , sizeof (appData.message2Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message2Line2[0] , sizeof (appData.message2Line2 ) - 1  ) ;
    
        delay(200);
        
// *****************************************************************************
// *****************************************************************************
        
        LCD_PutString ( (char*) &appData.message3Line1[0] , sizeof (appData.message3Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message3Line2[0] , sizeof (appData.message3Line2 ) - 1  ) ;
        
        delay(1500);
        
        LCD_PutString ( (char*) &appData.message4Line1[0] , sizeof (appData.message4Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message4Line2[0] , sizeof (appData.message4Line2 ) - 1  ) ;
        
        delay(2000);
        
// *****************************************************************************
// *****************************************************************************       
        
        LCD_PutString ( (char*) &appData.message5Line1[0] , sizeof (appData.message5Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message5Line2[0] , sizeof (appData.message5Line2 ) - 1  ) ;
        
        delay(2000);

// *****************************************************************************
// *****************************************************************************
        
        LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message1Line2[0] , sizeof (appData.message1Line2 ) - 1  ) ;
        
        delay(400);
        
        LCD_PutString ( (char*) &appData.message5Line1[0] , sizeof (appData.message5Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message5Line2[0] , sizeof (appData.message5Line2 ) - 1  ) ;
    
        delay(400);
        
        LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message1Line2[0] , sizeof (appData.message1Line2 ) - 1  ) ;
        
        delay(300);
        
        LCD_PutString ( (char*) &appData.message5Line1[0] , sizeof (appData.message5Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message5Line2[0] , sizeof (appData.message5Line2 ) - 1  ) ;
    
        delay(300);
        
        LCD_PutString ( (char*) &appData.message1Line1[0] , sizeof (appData.message1Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message1Line2[0] , sizeof (appData.message1Line2 ) - 1  ) ;
        
        delay(200);
        
        LCD_PutString ( (char*) &appData.message5Line1[0] , sizeof (appData.message5Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message5Line2[0] , sizeof (appData.message5Line2 ) - 1  ) ;
    
        delay(200);
        
// *****************************************************************************
// *****************************************************************************
        
        LCD_PutString ( (char*) &appData.message6Line1[0] , sizeof (appData.message6Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message6Line2[0] , sizeof (appData.message6Line2 ) - 1  ) ;
        
        delay(800);
        
        LCD_PutString ( (char*) &appData.message6Line2[0] , sizeof (appData.message6Line2 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message6Line1[0] , sizeof (appData.message6Line1 ) - 1  ) ;
    
        delay(600);
        
        LCD_PutString ( (char*) &appData.message6Line1[0] , sizeof (appData.message6Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message6Line2[0] , sizeof (appData.message6Line2 ) - 1  ) ;
        
        delay(400);
        
        LCD_PutString ( (char*) &appData.message6Line2[0] , sizeof (appData.message6Line2 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message6Line1[0] , sizeof (appData.message6Line1 ) - 1  ) ;
    
        delay(300);
        
        LCD_PutString ( (char*) &appData.message6Line1[0] , sizeof (appData.message6Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message6Line2[0] , sizeof (appData.message6Line2 ) - 1  ) ;
        
        delay(200);
        
        LCD_PutString ( (char*) &appData.message6Line2[0] , sizeof (appData.message6Line2 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message6Line1[0] , sizeof (appData.message6Line1 ) - 1  ) ;
    
        delay(100);
        
        LCD_PutString ( (char*) &appData.message6Line1[0] , sizeof (appData.message6Line1 ) - 1  ) ;
        LCD_PutString ( (char*) &appData.message6Line2[0] , sizeof (appData.message6Line2 ) - 1  ) ;
        
    }
}
