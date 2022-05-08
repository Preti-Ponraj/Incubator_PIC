/*
 * File:   Uart_driver.c
 * Author: Preethi
 *
 * Created on 8 December, 2021, 2:09 AM
 */


#include <xc.h>
#include "Uart_driver.h"
void delay_uart(int ms)
{
    int i,j;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<500;j++);   
    }
}
void uart_sendB(int a)
{
    switch(a)
    {
        case 1:
            TXSTA=(TXSTA& (~UART_SENDB))|UART_SENDB;
            break;
        case 0:
            TXSTA=(TXSTA& (~UART_SENDB))|UART_SENDB_END;
    }
}
void uart_mode(int a)
{
    switch(a)
    {
        case 8:
            TXSTA=(TXSTA& (~UART_9BIT_MODE))|UART_8BIT_MODE;
            RCSTA=(RCSTA& (~UART_9BIT_MODE))|UART_8BIT_MODE;
            break;
        case 9:
            TXSTA=(TXSTA& (~UART_9BIT_MODE))|UART_9BIT_MODE;
            RCSTA=(RCSTA& (~UART_9BIT_MODE))|UART_9BIT_MODE;
            break;
            
    }
}
void uart_Cren(int a)
{
    switch(a)
    {
        case 0:
            RCSTA=(RCSTA& (~UART_CREN_ENABLE))|UART_CREN_DISABLE;
            break;
        case 1:
            RCSTA=(RCSTA& (~UART_CREN_ENABLE))|UART_CREN_ENABLE;
            break;
    }
}

void uart_adden (int a)
{
    switch(a)
    {
        case 0:
            RCSTA=(RCSTA& (~UART_ADDEN_ENABLE))|UART_ADDEN_DISABLE;
            break;
        case 1:
            RCSTA=(RCSTA& (~UART_ADDEN_ENABLE))|UART_ADDEN_ENABLE;
            break;
            
    }
}
void uart_initialize()
{
    /*TXSTA=(0<<0)|(0<<1)|UART_ASYNC_MODE|UART_TX_ENABLE|UART_BRGH;
    RCSTA=(1<<7)|(1<<4);   
    BAUDCTL=0x00;*/
    TXSTA=0x24;
    RCSTA=0x90;
    SPBRG=25;
  
}

void transmit_data(char a)
{
    TXREG=a;
    while(TXIF==0);
    TXIF=0;
}
void transmit_string(char *a)
{
    while(*a!='\0')
    {
        transmit_data(*a);
        a++;
    }
}
char receive_data()
{
    char a;
    while(RCIF==0);
    a=RCREG;
    RCIF=0;
    return a;
}
char* receive_string(char a)
{
    int i;
    char b[RECEIVE_BUFFER];
    for(i=0;i<RECEIVE_BUFFER;i++)
    {
        b[i]=receive_data();
        if(b[i]==a)
        {
            break;
        }
    }
    return b;
}
void uart_baudrate(int a)
{   
    switch(a)
    {
        case 9600:
            SPBRG=SPBRG_9600;
            break;
        case 2400:
            SPBRG=SPBRG_2400;
            break;
        case 1200:
            SPBRG=SPBRG_1200;
            break;
    }
    
}


