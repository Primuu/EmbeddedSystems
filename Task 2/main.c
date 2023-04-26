#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

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
                    .messageLine1 = "   Thermometer  " ,
                    .messageLine2 = "   Turn on S3   " ,
                    .messageTime = "   Thermometer  " ,
                    .messageADC = "Temp =  0.00 st "
} ;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void extract_digits(double number, char *tens, char *ones, char *decimal, char *hundredths) {
    double integer;
    double fractional = modf(number, &integer);
    
    int digit = (int)integer % 10;
    *ones = digit + '0';
    
    digit = (int)integer / 10;
    *tens = (digit < 1) ? ' ' : (digit + '0');
    
    digit = (int)floor(fractional * 10);
    *decimal = digit + '0';
    
    digit = (int)floor(fractional * 100) % 10;
    *hundredths = digit + '0';
}

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

int alarm(int state) {
    if (state == 1 || state == 2 || state == 3) {
        LATA = 16;
        delay1s();
        LATA = 0;
        return state++;
    }
    return 4;
}

int main ( void )
{
    double alarm_temp = 26;
    int state = 1;
    
    /* Call the System Intialize routine*/
    SYS_Initialize ( ) ;

    /* Display welcome message */
    LCD_PutString ( (char*) &appData.messageLine1[0] , sizeof (appData.messageLine1 ) - 1  ) ;
    LCD_PutString ( (char*) &appData.messageLine2[0] , sizeof (appData.messageLine2 ) - 1  ) ;

    /* wait here until switch S3 is pressed */
    while (!BUTTON_IsPressed ( BUTTON_S3 )) ;

    /*Initialize Timer*/
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;

    /*Initialize ADC configure it as 10 bit interrupt driven mode*/
    ADC_SetConfiguration ( ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT ) ;
    
    /* Display initial ADC and Timer messages */
    LCD_PutString ( (char*) &appData.messageTime[0] , sizeof (appData.messageTime ) - 1 ) ;
    LCD_PutString ( (char*) &appData.messageADC[0] , sizeof (appData.messageADC ) - 1 ) ;

    /* Infinite Loop */
    while ( 1 )
    {

        appData.temp1 = ADC_Read10bit(ADC_CHANNEL_TEMPERATURE_SENSOR);
        ConvertADCVoltage (appData.temp1);
        double voltage = (appData.adones - '0') + (appData.adtens - '0') * 0.1 + (appData.adhunds - '0') * 0.01;
        double temperature = (voltage - 0.1) * 100 - 40;
        char tens, ones, decimal, hundredths;

        extract_digits(temperature, &tens, &ones, &decimal, &hundredths);
        
        
        
        if (temperature >= alarm_temp) {
            if (state == 1 || state == 2 || state == 3) {
                LATA = 16;
                delay1s();
                LATA = 0;
                delay1s();
                state++; 
            }
            if (state == 4) {
                LATA = 255;
            }
        }
        else {
            state = 1;
            LATA = 0;
            delay1s();
        }
        
        
        
        
        if (BUTTON_IsPressed( BUTTON_S6 )) {
            state = 1;
            LATA = 0;
            delay1s();
        }
        
        

        /* check if time to update LCD with Timer data */
        if ( appData.rtc_lcd_update )
        {
            Hex2Dec ( appData.hours ) ;
            Update_LCD ( ) ;
            appData.rtc_lcd_update = 0 ;

            /* check if time to update LCD with ADC data */
            if ( appData.adc_lcd_update )
            {

                ConvertADCVoltage ( appData.temp1 ) ;
                LCD_PutChar ( 'T' ) ;
                LCD_PutChar ( 'e' ) ;
                LCD_PutChar ( 'm' ) ;
                LCD_PutChar ( 'p' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( '=' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( tens ) ;
                LCD_PutChar ( ones ) ;
                LCD_PutChar ( '.' ) ;
                LCD_PutChar ( decimal ) ;
                LCD_PutChar ( hundredths ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( 's' ) ;
                LCD_PutChar ( 't' ) ;
                LCD_PutChar ( ' ' ) ;
                appData.adc_lcd_update = 0 ;
            }

        }
  
    } ;
    
}
/*******************************************************************************
  Function:
   void Update_LCD( void )
  Summary:
    Function to update LCD
  Description:
    This function will update the time on the LCD
  Precondition:
    None.
  Parameters:
    None.
  Returns:
    None.
  Remarks:
 */
/******************************************************************************/
void Update_LCD ( void )
{
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( 'T' ) ;
    LCD_PutChar ( 'h' ) ;
    LCD_PutChar ( 'e' ) ;
    LCD_PutChar ( 'r' ) ;
    LCD_PutChar ( 'm' ) ;
    LCD_PutChar ( 'o' ) ;
    LCD_PutChar ( 'm' ) ;
    LCD_PutChar ( 'e' ) ;
    LCD_PutChar ( 't' ) ;
    LCD_PutChar ( 'e' ) ;
    LCD_PutChar ( 'r' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( ' ' ) ;
}

/*******************************************************************************
  Function:
   void ConvertADCVoltage ( unsigned int )
  Summary:
    Function to convert ADC data into volts
  Description:
     This is the file for the Explorer 16 Dem that converts raw 10 bit ADC data
    to volts suitable for the LCD display
  Precondition:
    None.
  Parameters:
    None.
  Returns:
    None.
  Remarks:
 */
/******************************************************************************/

void ConvertADCVoltage ( unsigned int adc_conv_data )
{
    /* reset values */
    appData.adones = 0 ;
    appData.adtens = 0 ;
    appData.adhunds = 0 ;
    appData.adthous = 0 ;

    while ( adc_conv_data > 0 )
    {
        /* test for 1 volt or greater */
        if ( adc_conv_data > ( ONE_VOLT - 1 ) )
        {
            /* increment 1 volt counter */
            appData.adones++ ;

            /* subtract 1 volt */
            adc_conv_data -= ONE_VOLT ;
        }


            /* test for 0.1 volt */
        else if ( adc_conv_data > ( ONE_TENTH_VOLT - 1 ) )
        {
            /* increment tenths */
            if ( appData.adtens < 9 )
            {
                appData.adtens++ ;
            }
            else
            {
                /* tenths has rolled over */
                appData.adones++ ;

                /* so increment ones and reset tenths */
                appData.adtens = 0 ;
            }

            adc_conv_data -= ONE_TENTH_VOLT ;
        }

            /* test for 0.01 volt */
        else if ( adc_conv_data > ( ONE_HUNDREDTH_VOLT - 1 ) )
        {
            /* increment hundredths */
            if ( appData.adhunds < 9 )
            {
                appData.adhunds++ ;
            }
            else
            {
                /* hundredths has rolled over */
                appData.adtens++ ;

                /* so increment tenths and reset hundredths */
                appData.adhunds = 0 ;
            }

            adc_conv_data -= ONE_HUNDREDTH_VOLT ;
        }

        else if ( adc_conv_data <= ( ONE_HUNDREDTH_VOLT - 1 ) )
        {
            appData.adthous++ ;
            adc_conv_data -- ;
        }
    }

    appData.adones += 0x30 ;
    appData.adtens += 0x30 ;
    appData.adhunds += 0x30 ;
    appData.adthous += 0x30 ;
}

/*******************************************************************************
  Function:
   void Hex2Dec ( unsigned char )
  Summary:
    Explorer 16 Demo Hex to Decimal Conversion File
  Description:
     This is the file for the Explorer 16 Dem that converts the hexadecimal data
    into decimal format.
  Precondition:
    None.
  Parameters:
    None.
  Returns:
    None.
  Remarks:
 */
/******************************************************************************/

void Hex2Dec ( unsigned char count )
{
    /* reset values */
    appData.hunds = 0 ;
    appData.tens  = 0 ;
    appData.ones = 0 ;

    while ( count >= 10 )
    {

        if ( count >= 200 )
        {
            count -= 200 ;
            appData.hunds = 0x02 ;
        }

        if (count >= 100)
        {
            count -= 100 ;
            appData.hunds++ ;
        }

        if (count >= 10 )
        {
            count -= 10 ;
            appData.tens++ ;
        }
    }

    appData.ones = count ;
}
