#include "leds.h"
#include "lcd.h"
#include "adc.h"
#include "buttons.h"
#include "timer_1ms.h"
#include "print_lcd.h"

// *****************************************************************************
// *****************************************************************************
// Section: Demo Variables and Functions
// *****************************************************************************
// *****************************************************************************

/* Demo Variables and Functions Data Structure
  Summary:
    Defines the data required by the demo in a data structure
  Description:
    This data structure defines the data required by the Explorer 16 Demo
 Remarks:
    None.
*/

typedef struct
{
    /* Variables used by Timer module */
    volatile unsigned char hours ;
    volatile unsigned char minutes ;
    volatile unsigned char seconds ;
    volatile unsigned char hunds ;
    volatile unsigned char tens ;
    volatile unsigned char ones ;
    volatile unsigned char rtc_lcd_update ;
    
    /* variables used in raw ADC data to hex */
    volatile unsigned char adones ;
    volatile unsigned char adtens ;
    volatile unsigned char adhunds ;
    volatile unsigned char adthous ;
    volatile unsigned int  temp1 ;
    volatile unsigned char adc_lcd_update ;

    /*arrays used for Explorer 16 LCD display*/
    char message1Line1[18] ;
    char message1Line2[18] ;
    char message2Line1[18] ;
    char message2Line2[18] ;
    char message3Line1[18] ;
    char message3Line2[18] ;
    char message4Line1[18] ;
    char message4Line2[18] ;
    char message5Line1[18] ;
    char message5Line2[18] ;
    char message6Line1[18] ;
    char message6Line2[18] ;

} APP_DATA ;

extern APP_DATA appData ;
