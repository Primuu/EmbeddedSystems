#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <xc.h>
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
                    .messageLine1 = "Explorer 16 Demo" ,
                    .messageLine2 = "Press S3 to cont" ,
                    .messageTime = "Time 00: 00: 00 " ,
                    .messageADC = " Pot = 0.00 Vdc "
} ;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void delay(unsigned int ms) {
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

int grey(int value) {
    return value ^ (value >> 1);
}

int bcd(int value) {
    return ((value/10) << 4 | (value%10));
}

int generator() {
    srand(TMR1);
    int config = 115;
    double x = (double)rand() / RAND_MAX;
    return (int)(sin(2 * M_PI * x) * 32 + 32) % config;
}

void change_subfunction(int* selected_subfunction) {
    if (BUTTON_IsPressed( BUTTON_S3 )) {
        (*selected_subfunction) += 1;
        if ((*selected_subfunction) == 10) {
            (*selected_subfunction) = 1;
        }
    }
    if (BUTTON_IsPressed( BUTTON_S6 )) {
        (*selected_subfunction) -= 1;
        if ((*selected_subfunction) == 0){
            (*selected_subfunction) = 9;
        }
    }
}

int main ( void )
{
    /* Call the System Intialize routine*/
    SYS_Initialize ( ) ;
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;
    ADC_SetConfiguration ( ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT ) ;
    
    unsigned char display = 0;
    int selected_subfunction = 1;

    while ( 1 )
    {
        // 8 bit counter 0-255
        display = 0;
        while(selected_subfunction == 1){
            LATA = display;
            display++;
            delay(300);
            
            if (display == 255) {
                display = 0;
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
        
        // 8 bit counter 255-0
        display = 255;
        while(selected_subfunction == 2){
            LATA = display;
            display--;
            delay(300);
            
            if (display == 0) {
                display = 255;
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
        
        // Grey counter 0-255
        display = 0;
        while(selected_subfunction == 3){
            LATA = grey(display);
            display++;
            delay(300);
            
            if (display == 255) {
                display = 0;
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
        
        // Grey counter 255-0
        display = 255;
        while(selected_subfunction == 4){
            LATA = grey(display);
            display--;
            delay(300);
            
            if (display == 0) {
                display = 255;
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
        
        // BCD counter 0-99
        display = 0;
        while(selected_subfunction == 5){
            LATA = bcd(display);
            display++;
            delay(300);
            
            if (display == 99) {
                display = 0;
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
        
        // BCD counter 0-99
        display = 99;
        while(selected_subfunction == 6){
            LATA = bcd(display);
            display--;
            delay(300);
            
            if (display == 0) {
                display = 99;
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
        
        // 3-bit snake
        display = 7;
        while(selected_subfunction == 7){
            int i = 0;
            for (i = 0; i < 5; i++){
                LATA = display;
                display <<= 1;
                delay(300);
            }
            
            for (i = 0; i < 5; i++){
                LATA = display;
                display >>= 1;
                delay(300);
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
       
        // Queue
        int num_leds_to_enable = 7;
        int led_on = 1;
        int leds_already_in_queue = 0;
        
        while(selected_subfunction == 8){
            for(int i = 0; i < num_leds_to_enable; i++){
                LATA = led_on + leds_already_in_queue;
                led_on <<= 1;
                delay(300);
            }
            
            leds_already_in_queue += led_on;
            LATA = leds_already_in_queue;
            delay(300);
            
            led_on = 1;
            num_leds_to_enable--;
            
            if(num_leds_to_enable == -1){ 
                num_leds_to_enable = 7;
                leds_already_in_queue = 0;
            }
            
            if (BUTTON_IsPressed( BUTTON_S3 ) || BUTTON_IsPressed( BUTTON_S6 )) {
                change_subfunction(&selected_subfunction);
            }
        }
        
        // Random number generator
        while (selected_subfunction == 9) {
            delay(250);
            LATA = generator();
        }

    }
    
}
