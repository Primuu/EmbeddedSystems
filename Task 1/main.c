#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "app.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3





#include <p24fj128ga010.h>

//Konfiguracja dla Explorer 16 z progr. icd2
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI)

#define SCALE 308L






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

void led_on(int led_number) {
    if (led_number == 3) {
        LED_On(LED_D3);
    }
    if (led_number == 4) {
        LED_On(LED_D4);
    }
    if (led_number == 5) {
        LED_On(LED_D5);
    }
    if (led_number == 6) {
        LED_On(LED_D6);
    }
    if (led_number == 7) {
        LED_On(LED_D7);
    }
    if (led_number == 8) {
        LED_On(LED_D8);
    }
    if (led_number == 9) {
        LED_On(LED_D9);
    }
}

void led_off(int led_number) {
    if (led_number == 3) {
        LED_Off(LED_D3);
    }
    if (led_number == 4) {
        LED_Off(LED_D4);
    }
    if (led_number == 5) {
        LED_Off(LED_D5);
    }
    if (led_number == 6) {
        LED_Off(LED_D6);
    }
    if (led_number == 7) {
        LED_Off(LED_D7);
    }
    if (led_number == 8) {
        LED_Off(LED_D8);
    }
    if (led_number == 9) {
        LED_Off(LED_D9);
    }
}

void delay(int ms)
{
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

void fun1(int d) {
    int bin[7] = {0, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i <= 255; i++){
        int x = i;
        for(int j = 6; j >= 0; j--)
        {   
            bin[j] = x % 2;
            x = x /2;
        }
        for(int y = 3; y <= 9; y++)
        {
            if(bin[9 - y] == 1){
                led_on(y);
            }
            else led_off(y);
        }
        delay(d);
    }
}

void fun2(int d) {
    int bin[7] = {1, 1, 1, 1, 1, 1, 1};
    for(int i = 255; i >= 0; i--){
        int x = i;
        for(int j = 6; j >= 0; j--)
        {   
            bin[j] = x % 2;
            x = x /2;
        }
        for(int y = 3; y <= 9; y++)
        {
            if(bin[9 - y] == 1){
                led_on(y);
            }
            else led_off(y);
        }
        delay(d);
    }
}


// OTHER VERSION WORKING WITH BUTTONS SWITCH

unsigned int fun1(unsigned int counter) {
	return counter = counter + 1;
}

unsigned int fun2(unsigned int counter) {
	return counter = counter - 1;
}

unsigned int fun34(unsigned int counter) {
	return counter ^(counter>>1);
}

unsigned int fun56(unsigned int counter) {
	int result = 0;
	int ten = counter / 10;
	int one = counter % 10;
	ten = ten << 4;
	result = ten | one;
	return result;
}

unsigned int fun7(unsigned int counter) {
	static int direction = 1;
	if(direction == 1) {
		counter = counter<<1;
	}
	if(direction == 0) {
		counter = counter>>1;
	}

	if(counter == 224) {
		direction = 0;
	}
	if(counter == 7){
		direction = 1;
	}
	return counter;
}

unsigned int fun8() {
	static int stop = 128;
	static int queue = 1;
	unsigned int counter = 0;
	static int delay = 0;

	if(counter == 255) {
		counter = 1;
		queue = 1;
		delay = 0;
		stop = 128;
	}
	if(queue > stop) {
        delay = delay | stop;
		queue = 1;
        counter = delay | queue;
		stop = stop >> 1;
		if(stop == 0) {
            stop = 128;
            delay = 0;
		}
	}
    counter = delay | queue;
	queue = queue << 1;

	return counter;
}


int k_bit(int n, int k)
{
     return (n>>k)&1; // Sprawdz przesuniety bit za pomoca AND
}

int funct9(int result)// 6 bitowy generator liczb pseudolosowych oparty o konfigurację 1110011
{
 int n, k1,k2,rand;
 n=result;
 k1=k_bit(n, 0); // k1=0bit liczby n
 k2=k_bit(n, 1); // k2=2bit liczby n
 k1=k1^k2; // wynik XOR(k1,k2)
 k2=k_bit(n, 4); // k2=4bit liczby n
 k1=k1^k2; // wynik XOR(k1,k2)
 k2=k_bit(n, 5); // k2=5bit liczby n
 k1=k1^k2; // wynik XOR(k1,k2)
 n=n>>1; // n= n przesuniete o 1bit w prawo
 rand=k1<<5; // rand= k1 przesuniete o 5bitow w lewo
 n=rand|n; // n= operacja OR(rand, n)
 result = n; 
 return result; //zwraca zawartosc n
}

int main ( void )
{


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


    LED_Enable(LED_D3);
    LED_Enable(LED_D4);
    LED_Enable(LED_D5);
    LED_Enable(LED_D6);
    LED_Enable(LED_D7);
    LED_Enable(LED_D8);
    LED_Enable(LED_D9);
    LED_Enable(LED_D10);





    unsigned long i;
    unsigned char display=0; //zmienna odpowiedzialna za wyświetlanie
    unsigned int przelacznik=0; //zmienna odpowiedzialna za przełączanie podprogramów
    unsigned int acctual=0; //zmienna która zawiera aktualną liczbe wyswietlania
    unsigned int snake=7; //zmienna odpowiedzialna za wężyk, równa 7 ponieważ 7 w binarnych to 111
    unsigned int prng=1; // zmienna odpowiedzialna za generator liczb pseudolosowych




    /* Infinite Loop */
    while ( 1 )
    {

    //    fun1(250);
    //    fun2();



	if (PORTDbits.RD13 == 0){//sprawdz czy przycisk zostal użyty
		if(przelacznik == 9){//przy ostatnim podprogramie gdy kliknie sie przycisk RD13 uruchamia podprogram 0 
			przelacznik=0;
		}
		else{
	    	przelacznik=przelacznik+1;// po klinieciu przycisku RD13 uruchamia kolejny podprogram
		}
	}
	else if(PORTDbits.RD6 == 0){//sprawdz czy przycisk zostal użyty
	    if(przelacznik == -1){//przy pierwszym podprogramie gdy kliknie sie przycisk RD6 uruchamia podprogram 8
			przelacznik=8;
		}
		else{
			przelacznik=przelacznik-1;// po klinieciu przycisku RD6 uruchamia poprzedni podprogram
		}
	}

	// Ustawienie podprogramów:
	if (przelacznik==0){ // 1. 8 bitowy licznik binarny zliczający w górę (0...255)
		display=funct1(display);// wczytanie funkcji do wyswietlenia
		acctual = display;// zapisanie aktualnej wyswietlanej liczby
	}
	else if (przelacznik==1){ // 2. 8 bitowy licznik binarny zliczający w dół (255...0)
		display=funct2(display);// wczytanie funkcji do wyswietlenia
		acctual = display;// zapisanie aktualnej wyswietlanej liczby
	}
	else if (przelacznik==2){ // 3. 8 bitowy licznik w kodzie Graya zliczający w górę (repr. 0...255)
		display=funct34(acctual++);// wczytanie funkcji do wyswietlenia z ostatnia wyswietlana wartoscia ktora jest zwiekszana o 1
		acctual = display;// zapisanie aktualnej wyswietlanej liczby
	}
	else if (przelacznik==3){ // 4. 8 bitowy licznik w kodzie Graya zliczający w dół (repr. 255...0)
		display=funct34(acctual--);// wczytanie funkcji do wyswietlenia z ostatnia wyswietlana wartoscia ktora jest zmniejszana o 1
		acctual = display;// zapisanie aktualnej wyswietlanej liczby
	}
	else if (przelacznik==4){ // 5. 2x4 bitowy licznik w kodzie BCD zliczający w górę (0...99)
		if(acctual >=100){ //restart acctual do 0 gdy jest >= 100
				acctual = 0;
		}
		display=funct56(acctual++);// wczytanie funkcji do wyswietlenia z ostatnia wyswietlana wartoscia ktora jest zwiekszana o 1
	}
	else if (przelacznik==5){ // 6. 2x4 bitowy licznik w kodzie BCD zliczający w dół (99...0)
		if(acctual <=0){//restart acctual do 99 gdy jest <= 0
				acctual = 99;
		}
		display=funct56(acctual--);// wczytanie funkcji do wyswietlenia z ostatnia wyswietlana wartoscia ktora jest zmniejszana o 1
	}
	else if (przelacznik==6){ // 7. 3 bitowy wężyk poruszający się lewo-prawo
		display=snake;// wczytanie zmiennej snake do wyswietlania
		snake=funct7(snake++);// zapis do zmiennej snake funkcji z wartoscia snake zwiekszajacą sie o 1
	}
	else if (przelacznik==7){ // 8 .Kolejka
		display=funct8(); //wyswietlenie funkcji
	}
	else if (przelacznik==8){ // 9. 6 bitowy generator liczb pseudolosowych oparty o konfigurację 1110011
		display=prng; // display pobiera wartosc zmiennej prng
    	display = funct9(prng);// wczytanie funkcji do wyswietlenia z wartoscia prng
    	if(prng>=63)//reatrt zmiennej prng do 0 gdy jest wieksza równa 63
    	{
        prng=0;
    	}
    	prng=display;//wczytanie wyswietlanej wartosci do prng
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
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( 'P' ) ;
                LCD_PutChar ( 'o' ) ;
                LCD_PutChar ( 't' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( '=' ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( appData.adones ) ;
                LCD_PutChar ( '.' ) ;
                LCD_PutChar ( appData.adtens ) ;
                LCD_PutChar ( appData.adhunds ) ;
                LCD_PutChar ( ' ' ) ;
                LCD_PutChar ( 'V' ) ;
                LCD_PutChar ( 'd' ) ;
                LCD_PutChar ( 'c' ) ;
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
    LCD_PutChar ( 'T' ) ;
    LCD_PutChar ( 'i' ) ;
    LCD_PutChar ( 'm' ) ;
    LCD_PutChar ( 'e' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.minutes ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.seconds ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

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