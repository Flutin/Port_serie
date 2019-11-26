#include <avr/io.h>
#include <util/delay.h>

#define FOSC 16000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define BLINK_DELAY_MS 5000

void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_Init(unsigned int ubrr);
void Move_interrupts(void);

int main(void)
{
    
    USART_Init(MYUBRR);

    DDRB |= _BV(DDB5); //déclare le pin en sortie
    Move_interrupts();
    //attachInterrupt(0, Move_interrupts, CHANGE);

}

void USART_Init(unsigned int ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /*Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)))              //n = numero de port
    ;
    /* Put data into buffer, sends the data */
    UDR0 = data;                                //n = numero de port
}

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)))               //n = numero de port
    ;
    /* Get and return received data from buffer */
    return UDR0;                                //n = numero de port
}

void Move_interrupts(void)
{
    while(1){
    if(USART_Receive() =='A')
       {
           PORTB |= _BV(PORTB5);
           _delay_ms(BLINK_DELAY_MS);
       }
       else if(USART_Receive() =='E')
       {
            PORTB &= ~_BV(PORTB5);
            _delay_ms(BLINK_DELAY_MS);
       }
    }
}