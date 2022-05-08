#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/
//#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
//#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



#include<xc.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"Lcd_16x2_Driver.h"
//#include"Uart_driver.h"

#define a_lm35 RA0 
#define a_humidity RA1 
#define a_ldr RA2 
#define a_motor RA3
#define bulb  RD0
#define fan RD1 
#define delay_need 1
#define delay_count delay_need*60*2


int hum,temp,light,voltage,volt,h_voltage;
int out_temp,out_humidity;
char temperature[4],intensity[10],humidity[10];


void gsm_msg();

void transmit_data(char a)
{
    TXREG=a;
    while(TXIF==0);
    TXIF=0;
}
void transmit_string(char *a)
{
    while(*a)
    {
        TXREG=*a;
        a++;
        while(TXIF==0);
        TXIF=0;
    }
}

int count=0,flag=1;

char adc(char input)
{
    int a,b,output;
    ADCON0=input;
    ADCON1=0x80;
    delay(50);
    GO=1;
    while(GO==1);
   
    
    a=ADRESL;
    b=ADRESH;
    
   
    output = (b<<8)|a;
    return output;   
}

void timer1_config()
{
    T1CON=0x31;
    INTCON=0xc0;
    PIE1=0x01;
}

void __interrupt() timer()
{
    count++;
    TMR1IF=0;
 
    if(count>delay_count)
    { 
        RA3=1;
        delay(100);
        
       // delay(1);
        count=0;
    }
    RA3=0;
    
}


void main()
{
    
    PORTA=0x00;
    TRISA=0x07;
    ANSEL=0x07;
    PORTD=0x00;
    TRISD=0x00;
    PORTB=0x00;
    TRISB=0x00;
    ANSELH=0x00;
    PORTC=0x00;
    TRISC=0x80;
    PORTE=0x00;
    TRISE=0x00;
    TXSTA=0x24;
    RCSTA=0x90;
    SPBRG=25;
    lcd_initialize();
    //lcd_clear();
    //uart_initialize();
    //uart_baudrate(9600);
    timer1_config();
    
    while(1)
    {
    temp=adc(0x01);
    voltage=temp*48; //(5/1023=0.0048V converted to integer converted to mV)
    out_temp=voltage/100; //10mV/degreeCelsius
    digit_split_a(temperature,out_temp);
    
    if(out_temp<=35) 
    {
        bulb=1;
    }
    if(bulb==1 && out_temp<40)
    {
        bulb=1;
    }
    if(out_temp>40)
    {
        bulb=0;
    }
    
    //transmit_data(0x0d);
    hum=adc(0x05);
    h_voltage=hum*5;      
    //out_humidity=h_voltage/100;
    out_humidity=(int)(((90*h_voltage)/5)/100); 
    digit_split_a(humidity,out_humidity);
    
    light=adc(0x09);
    digit_split_a(intensity,light);
    
    //lcd_clear();
   
    
    gsm_msg();
    lcd_position(0,0);
    lcd_string(temperature);
    lcd_position(1,0);
    lcd_string("C");
    //lcd_clear();
    
    lcd_position(0,5);
    lcd_string(humidity);
    lcd_position(1,5);
    lcd_string("RH");
    
    
    lcd_position(0,12);
    lcd_string(intensity);
    lcd_position(1,12);
    lcd_string("lux");
    
    lcd_clear();
    
     if(out_humidity>40)
    {
        fan=1;
    }
    else
    {
        fan=0;
    }
    
    
    
    if(intensity<200 && out_temp<30)
     {
       if(flag==1)
        {
        
        int i=0;
        lcd_clear();
        lcd_position(1,0);
        //lcd_string("LIGHT GOT REPAIRED");
        lcd_clear();
        //GSM code
        gsm_msg();
        }
       else
       {
        flag=1;
       }
    }
    }
       
}

    void gsm_msg()
    {
        
        transmit_string("AT");
        transmit_data(0x0D);
        transmit_data(0x0A);
        delay(1000);
        transmit_string("AT+CMGF=1");
        transmit_data(0x0d);
        transmit_data(0x0A);
        delay(1000);
        transmit_string("AT+CMGS=\"+919786329004\"");   
        transmit_data(0x0d);
        transmit_data(0x0A);
        delay(1000);
        /*transmit_string("LIGHT GOT REPAIRED");
        transmit_data(0x0d);
        transmit_data(0x0A);*/
        transmit_string("TEMP:");
        transmit_data(0x0d);
        transmit_data(0x0A);
        delay(1000);
        transmit_string(temperature);
        transmit_data(0x0d);
        transmit_data(0x0A);
        delay(1000);
        transmit_string("Deg_Celsius");
        transmit_data(0x0d);
        transmit_data(0x0A);
        delay(1000);
        transmit_string("HUMIDITY:");
        transmit_string(humidity);
        delay(1000);
        transmit_string("RH");
        transmit_data(0x0D);
        transmit_data(0x0A);
        delay(1000);
        transmit_data(0x1A);
        delay(1000);
        flag=0;
        }
    
    
       
     
     
    
   
 