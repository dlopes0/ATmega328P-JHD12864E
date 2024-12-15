#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

#include <util/delay.h>

#include "jhd12864e.h"

void write_operation(uint16_t op)
{
    // Set I/O
    DDRD |= (1 << 2); // E,    PD2 (set to OUTPUT)
    DDRB |= (1 << 5); // R/W,  PB5 (set to OUTPUT)
    DDRC |= (1 << 0); // CS1B, PC0 (set to OUTPUT)
    DDRC |= (1 << 1); // CS2B, PC1 (set to OUTPUT)
    DDRC |= (1 << 2); // CS3,  PC2 (set to OUTPUT)
    DDRC |= (1 << 3); // RS,   PC3 (set to OUTPUT)
    DDRD |= (1 << 5); // DB0,  PD5 (set to OUTPUT)
    DDRD |= (1 << 6); // DB1,  PD6 (set to OUTPUT)
    DDRD |= (1 << 7); // DB2,  PD7 (set to OUTPUT)
    DDRB |= (1 << 0); // DB3,  PB0 (set to OUTPUT)
    DDRB |= (1 << 1); // DB4,  PB1 (set to OUTPUT)
    DDRB |= (1 << 2); // DB5,  PB2 (set to OUTPUT)
    DDRB |= (1 << 3); // DB6,  PB3 (set to OUTPUT)
    DDRB |= (1 << 4); // DB7,  PB4 (set to OUTPUT)

    // Initialization
    PORTD |=  (1 << 2); // E, PD2   (set to HIGH)
    PORTB |=  (1 << 5); // R/W, PB5 (set to HIGH)
    PORTC |=  (1 << 0); // CS1B, PC0 (set to HIGH)
    PORTC |=  (1 << 1); // CS2B, PC1 (set to HIGH)
    PORTC &= ~(1 << 2); // CS3, PC2 (set to LOW)
    PORTC &= ~(1 << 3); // RS, PC3 (set to LOW)
    PORTD &= ~(1 << 5); // DB0,  PD5 (set to LOW)
    PORTD &= ~(1 << 6); // DB1,  PD6 (set to LOW)
    PORTD &= ~(1 << 7); // DB2,  PD7 (set to LOW)
    PORTB &= ~(1 << 0); // DB3,  PB0 (set to LOW)
    PORTB &= ~(1 << 1); // DB4,  PB1 (set to LOW)
    PORTB &= ~(1 << 2); // DB5,  PB2 (set to LOW)
    PORTB &= ~(1 << 3); // DB6,  PB3 (set to LOW)
    PORTB &= ~(1 << 4); // DB7,  PB4 (set to LOW)

    _delay_us(T_WIDTH);

    PORTD &= ~(1 << 2); // E, PD2 (set to LOW)

    _delay_us(T_WIDTH/2);

    PORTB &= ~(1 << 5); // R/W, PB5 (set to LOW)
    PORTC &= ~(1 << 0); // CS1B, PC0 (set to LOW)
    PORTC &= ~(1 << 1); // CS2B, PC1 (set to LOW)
    PORTC |=  (1 << 2); // CS3, PC2 (set to HIGH)
    PORTC |=  (1 << 3); // RS, PC3 (set to HIGH)

    _delay_us(T_WIDTH/2);

    PORTD |=  (1 << 2); // E, PD2   (set to HIGH)

    _delay_us(T_WIDTH/2);

    if ((op & 0x0001) == 0x0001)
        PORTD |=  (1 << 5); // DB0,  PD5 (set to HIGH)
    else
        PORTD &= ~(1 << 5); // DB0,  PD5 (set to LOW)

    if ((op & 0x0002) == 0x0002)
        PORTD |=  (1 << 6); // DB1,  PD6 (set to HIGH)
    else
        PORTD &= ~(1 << 6); // DB1,  PD6 (set to LOW)

    if ((op & 0x0004) == 0x0004)
        PORTD |=  (1 << 7); // DB2,  PD7 (set to HIGH)
    else
        PORTD &= ~(1 << 7); // DB2,  PD7 (set to LOW)

    if ((op & 0x0008) == 0x0008)
        PORTB |=  (1 << 0); // DB3,  PB0 (set to HIGH)
    else
        PORTB &= ~(1 << 0); // DB3,  PB0 (set to LOW)

    if ((op & 0x0010) == 0x0010)
        PORTB |=  (1 << 1); // DB4,  PB1 (set to HIGH)
    else
        PORTB &= ~(1 << 1); // DB4,  PB1 (set to LOW)

    if ((op & 0x0020) == 0x0020)
        PORTB |=  (1 << 2); // DB5,  PB2 (set to HIGH)
    else
        PORTB &= ~(1 << 2); // DB5,  PB2 (set to LOW)

    if ((op & 0x0030) == 0x0030)
        PORTB |=  (1 << 3); // DB6,  PB3 (set to HIGH)
    else
        PORTB &= ~(1 << 3); // DB6,  PB3 (set to LOW)

    if ((op & 0x0040) == 0x0040)
        PORTB |=  (1 << 4); // DB7,  PB4 (set to HIGH)
    else
        PORTB &= ~(1 << 4); // DB7,  PB4 (set to LOW)

    _delay_us(T_WIDTH/2);

    PORTD &= ~(1 << 2); // E, PD2 (set to LOW)

    _delay_us(T_WIDTH/2);

    // Back to default
    PORTB |=  (1 << 5); // R/W, PB5 (set to HIGH)
    PORTC |=  (1 << 0); // CS1B, PC0 (set to HIGH)
    PORTC |=  (1 << 1); // CS2B, PC1 (set to HIGH)
    PORTC &= ~(1 << 2); // CS3, PC2 (set to LOW)
    PORTC &= ~(1 << 3); // RS, PC3 (set to LOW)
    PORTD &= ~(1 << 5); // DB0,  PD5 (set to LOW)
    PORTD &= ~(1 << 6); // DB1,  PD6 (set to LOW)
    PORTD &= ~(1 << 7); // DB2,  PD7 (set to LOW)
    PORTB &= ~(1 << 0); // DB3,  PB0 (set to LOW)
    PORTB &= ~(1 << 1); // DB4,  PB1 (set to LOW)
    PORTB &= ~(1 << 2); // DB5,  PB2 (set to LOW)
    PORTB &= ~(1 << 3); // DB6,  PB3 (set to LOW)
    PORTB &= ~(1 << 4); // DB7,  PB4 (set to LOW)

    _delay_us(T_WIDTH/2);

    PORTD |=  (1 << 2); // E, PD2   (set to HIGH)
}

uint16_t read_operation()
{
    uint16_t op = 0x0000;

    // Set I/O
    DDRD |=  (1 << 2); // E,    PD2 (set to OUTPUT)
    DDRB |=  (1 << 5); // R/W,  PB5 (set to OUTPUT)
    DDRC |=  (1 << 0); // CS1B, PC0 (set to OUTPUT)
    DDRC |=  (1 << 1); // CS2B, PC1 (set to OUTPUT)
    DDRC |=  (1 << 2); // CS3,  PC2 (set to OUTPUT)
    DDRC |=  (1 << 3); // RS,   PC3 (set to OUTPUT)
    DDRD &= ~(1 << 5); // DB0,  PD5 (set to INPUT)
    DDRD &= ~(1 << 6); // DB1,  PD6 (set to INPUT)
    DDRD &= ~(1 << 7); // DB2,  PD7 (set to INPUT)
    DDRB &= ~(1 << 0); // DB3,  PB0 (set to INPUT)
    DDRB &= ~(1 << 1); // DB4,  PB1 (set to INPUT)
    DDRB &= ~(1 << 2); // DB5,  PB2 (set to INPUT)
    DDRB &= ~(1 << 3); // DB6,  PB3 (set to INPUT)
    DDRB &= ~(1 << 4); // DB7,  PB4 (set to INPUT)

    // Initialization
    PORTD |=  (1 << 2); // E, PD2   (set to HIGH)
    PORTB &= ~(1 << 5); // R/W, PB5 (set to LOW)
    PORTC |=  (1 << 0); // CS1B, PC0 (set to HIGH)
    PORTC |=  (1 << 1); // CS2B, PC1 (set to HIGH)
    PORTC &= ~(1 << 2); // CS3, PC2 (set to LOW)
    PORTC &= ~(1 << 3); // RS, PC3 (set to LOW)

    _delay_us(T_WIDTH);

    PORTD &= ~(1 << 2); // E, PD2 (set to LOW)

    _delay_us(T_WIDTH/2);

    PORTB |=  (1 << 5); // R/W, PB5 (set to HIGH)
    PORTC &= ~(1 << 0); // CS1B, PC0 (set to LOW)
    PORTC &= ~(1 << 1); // CS2B, PC1 (set to LOW)
    PORTC |=  (1 << 2); // CS3, PC2 (set to HIGH)
    PORTC |=  (1 << 3); // RS, PC3 (set to HIGH)

    _delay_us(T_WIDTH/2);

    PORTD |=  (1 << 2); // E, PD2   (set to HIGH)

    _delay_us(T_WIDTH/2);

    if (PIND & (1 << 5)) // DB0,  PD5 (is HIGH?)
        op |= 0x0001;
    if (PIND & (1 << 6)) // DB1,  PD6 (is HIGH?)
        op |= 0x0002;
    if (PIND & (1 << 7)) // DB2,  PD7 (is HIGH?)
        op |= 0x0004;
    if (PINB & (1 << 0)) // DB3,  PB0 (is HIGH?)
        op |= 0x0008;
    if (PINB & (1 << 1)) // DB4,  PB1 (is HIGH?)
        op |= 0x0010;
    if (PINB & (1 << 2)) // DB5,  PB2 (is HIGH?)
        op |= 0x0020;
    if (PINB & (1 << 3)) // DB6,  PB3 (is HIGH?)
        op |= 0x0030;
    if (PINB & (1 << 4)) // DB7,  PB4 (is HIGH?)
        op |= 0x0040;

    PORTD &= ~(1 << 2); // E, PD2 (set to LOW)

    _delay_us(T_WIDTH/2);

    // Back to default
    PORTB &= ~(1 << 5); // R/W, PB5 (set to HIGH)
    PORTC |=  (1 << 0); // CS1B, PC0 (set to HIGH)
    PORTC |=  (1 << 1); // CS2B, PC1 (set to HIGH)
    PORTC &= ~(1 << 2); // CS3, PC2 (set to LOW)
    PORTC &= ~(1 << 3); // RS, PC3 (set to LOW)
    PORTD &= ~(1 << 5); // DB0,  PD5 (set to LOW)
    PORTD &= ~(1 << 6); // DB1,  PD6 (set to LOW)
    PORTD &= ~(1 << 7); // DB2,  PD7 (set to LOW)
    PORTB &= ~(1 << 0); // DB3,  PB0 (set to LOW)
    PORTB &= ~(1 << 1); // DB4,  PB1 (set to LOW)
    PORTB &= ~(1 << 2); // DB5,  PB2 (set to LOW)
    PORTB &= ~(1 << 3); // DB6,  PB3 (set to LOW)
    PORTB &= ~(1 << 4); // DB7,  PB4 (set to LOW)

    return op;
}

