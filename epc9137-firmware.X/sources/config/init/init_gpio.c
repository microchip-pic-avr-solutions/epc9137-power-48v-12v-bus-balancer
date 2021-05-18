/*
 * File:   init_gpio.c
 * Author: M91406
 *
 * Created on July 8, 2019, 6:26 PM
 */


#include <xc.h>
#include "config/init/init_gpio.h"

volatile uint16_t init_gpio(void) {
    
    volatile uint16_t retval=1;
    
    // Reset all analog inputs to be Digital I/Os
//    ANSELA = 0x0000;
//    ANSELB = 0x0000;
    LATA = 0;
//    LATB = (1 << 8);
    LATB = (1 << 3);
    LATC = 0;
    
    //all inputs are for ADC or the enable line, 1=input, 0=output
    TRISA = (1 << 3);//0b1011;
    TRISB = (1 << 4) | (1 << 8) | (1 << 9) | (1 << 2) | (1 << 7) | (0b1); //
//    TRISB = (1 << 2) | (1 << 9);//(1 << 0) | (1 << 4) | (1 << 9) | (1 << 7);
    TRISC = 0b111;

    //set analog pins to free others to be digital
    ANSELA = (1 << 3);//0b1011;
    ANSELB = (1 << 8) | (1 << 9) | (1 << 2) | (1 << 7) | (0b1);
    // RB8 (AN10) Vdc1, RB9 (AN11) Vsns1, RB2 (AN1/ANA0) Isns1, RB7 (AN2) Isns2, RB0 (AN5) t1
    ANSELC = 0b111;
    
    
    // Initialize debugging Pins
    DBGPIN_1_INIT;
    DBGPIN_2_INIT;
    DBGPIN_3_INIT;

    // Map PWM4H/L outputs to pins RB8/9
    // ToDo: Move hard-coded peripheral and pin assignments to hardware abstraction layer files
//    _LATB8 = 0;
//    _TRISB8 = 0;
//    _LATB9 = 0;
//    _TRISB9 = 0;
//    _TRISB5 = 0;
//    _TRISB6 = 1;
    
    __builtin_write_RPCON(0x0000); // unlock PPS
    RPOR3bits.RP38R = 0x0022;    //RB6->PWM:PWM4H
    RPOR2bits.RP37R = 0x0023;    //RB5->PWM:PWM4L    
    RPOR1bits.RP35R = 0x0001;    //RB3->UART1:U1TX
    RPINR18bits.U1RXR = 0x0024;    //RB4->UART1:U1RX  
    __builtin_write_RPCON(0x0800); // lock PPS
    
    return(retval);
}
