/*
 * File:   Uart_driver.h
 * Author: Preethi
 *
 * Created on 8 December, 2021, 2:09 AM
 */


#define FOSC_4000
#define TX RC6
#define RX RC7

//#define FOSC_2000
#ifdef FOSC_4000
#define SPBRG_9600 25
#define SPBRG_2400 103
#define SPBRG_1200 207

#elif defined (FOSC_2000)
#define SPBRG_9600 23
#define SPBRG_2400 95
#define SPBRG_1200 191

#else
#error "error is present"
#endif

#define RECEIVE_BUFFER 20

#define UART_9BIT_MODE (1<<6)
#define UART_8BIT_MODE (0<<6)
#define UART_ASYNC_MODE (0<<4)
#define UART_TX_ENABLE (1<<5)
#define UART_TX_DISABLE (0<<5)
#define UART_SENDB (1<<3)
#define UART_SENDB_END (0<<3)
#define UART_BRGH (1<<2)

#define UART_CREN_ENABLE (1<<4)
#define UART_CREN_DISABLE (0<<4)
#define UART_ADDEN_ENABLE (1<<3)
#define UART_ADDEN_DISABLE (0<<3)

void delay_uart(int ms);
void uart_sendB(int a);
void uart_mode(int a);
void uart_Cren(int a);
void uart_adden (int a);
void uart_initialize();
void transmit_data(char a);
void transmit_string(char *a);
char receive_data();
char* receive_string(char a);
void uart_baudrate(int a);





        