/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   epc9137_R40_hwdescr.h
 * Author: M91406
 * Comments: EPC9137 Bi-Directional Reference Design Hardware Descriptor header file
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef EPC9137_R40_HARDWARE_DESCRIPTOR_H
#define	EPC9137_R40_HARDWARE_DESCRIPTOR_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types
#include <math.h> // include standard math functoins library


/*!Microcontroller Abstraction
 * *************************************************************************************************
 * Summary:
 * Global defines for device specific parameters
 * 
 * Description:
 * This section is used to define device specific parameters like ADC reference and
 * resolution. Pre-compiler macros are used to translate physical values into binary 
 * (integer) numbers to be written to SFRs
 * 
 * *************************************************************************************************/
#define CPU_FREQUENCY       (float)100000000.0  // CPU frequency in [Hz]
#define CPU_TCY             (float)(1.0/CPU_FREQUENCY) // Instruction period

// ADC(DAC Reference and Resolution Settings    
#define ADC_REF             (float)3.300 // ADC reference voltage in V
#define ADC_RES             (float)12.0  // ADC resolution in [bit]
#define ADC_GRAN            (float)(ADC_REF / pow(2.0, ADC_RES)) // ADC granularity in [V/tick]
#define ADC_VALUE_MAX       (uint16_t) (pow(2.0, ADC_RES) - 1.0)
    
// PWM/ADC Clock Settings    
#define PWM_CLOCK_FREQUENCY (float)4.0e+9   // PWM Clock Frequency in [Hz]
#define PWM_CLOCK_PERIOD    (float)(1.0/PWM_CLOCK_FREQUENCY) // PWM Clock Period in [sec]
    
/*!State Machine Settings
 * *************************************************************************************************
 * Summary:
 * Global defines for state-machine specific parameters
 * 
 * Description:
 * This section is used to define state-machine settings such as the main execution call interval. 
 * Pre-compiler macros are used to translate physical values into binary (integer) numbers to be 
 * written to SFRs and variables.
 * 
 * *************************************************************************************************/
#define MAIN_EXECUTION_PERIOD   (float)100.0e-6     // main state machine pace period in [sec]
#define MAIN_EXEC_PER           (uint16_t)((CPU_FREQUENCY * MAIN_EXECUTION_PERIOD)-1)

    
/*!Hardware Abstraction
 * *************************************************************************************************
 * Summary:
 * Global defines for hardware specific parameters
 * 
 * Description:
 * This section is used to define hardware specific parameters such as output voltage dividers,
 * reference levels or feedback gains. Pre-compiler macros are used to translate physical  
 * values into binary (integer) numbers to be written to SFRs
 * 
 * *************************************************************************************************/

#ifdef __EPC9137_R40__
    
    // Device Pin #1 on EPC9528
    #define DBGPIN_1_SET	{ _LATC4 = 1; }
    #define DBGPIN_1_CLEAR	{ _LATC4 = 0; }
    #define DBGPIN_1_TOGGLE	{ _LATC4 ^= 1; }
    #define DBGPIN_1_INIT	{ _LATC4 = 0; _TRISC4 = 0; }

    // Device Pin #2 on EPC9528
    #define DBGPIN_2_SET	{ _LATC5 = 1; }
    #define DBGPIN_2_CLEAR	{ _LATC5 = 0; }
    #define DBGPIN_2_TOGGLE	{ _LATC5 ^= 1; }
    #define DBGPIN_2_INIT	{ _LATC5 = 0; _TRISC5 = 0; }

    // Device Pin #25 on EPC9528
    #define DBGPIN_3_SET	{ _LATB10 = 1; }
    #define DBGPIN_3_CLEAR	{ _LATB10 = 0; }
    #define DBGPIN_3_TOGGLE	{ _LATB10 ^= 1; }
    #define DBGPIN_3_INIT	{ _LATB10 = 0; _TRISB10 = 0; }

    // Device Pin #14 on EPC9528
    #define PWRGOOD_PORT    0   // GPIO port declaration where 0=A, 1=B, 2=C, etc.
    #define PWRGOOD_PIN     1   // GPIO port pin declaration where 0=Rx0, 1=Rx1, 2=Rx3, etc.
    #define PWRGOOD_SET     { _LATA1 = 1; }
    #define PWRGOOD_CLEAR	{ _LATA1 = 0; }
    #define PWRGOOD_TOGGLE	{ _LATA1 ^= 1; }
    #define PWRGOOD_INIT	{ _ANSELA1 = 0; _LATA1 = 0; _TRISA1 = 0; }
    
#endif

/*!Power Control Parameter Declaration
 * *************************************************************************************************
 * Summary:
 * Global defines for Buck Converter Power Control parameters
 * 
 * Description:
 * This section is used to define hardware specific parameters such as output voltage dividers,
 * reference levels or feedback gains. Pre-compiler macros are used to translate physical  
 * values into binary (integer) numbers to be written to SFRs
 * 
 * *************************************************************************************************/

#define SWITCHING_FREQUENCY     (float)250.0e+3   // Switching frequency in [Hz]
#define SWITCHING_PERIOD        (float)(1.0/SWITCHING_FREQUENCY)    // Switching period in [sec]
#define SWITCHING_PHASE_SHIFT   (float)0.0        // Phase Shift of PWM output in [sec]

// ToDo: Remove -> dead times are set below    
//#define SWITCHING_LEB           (float)120.0e-9 // Leading Edge Blanking in [sec]
//#define SWITCHING_DEAD_TIME_LE  (float)40.0e-9    // Leading Edge Dead Time in [sec]
//#define SWITCHING_DEAD_TIME_FE  (float)20.0e-9    // Falling Edge Dead Time in [sec]

/* CUSTOM RUNTIME OPTIONS */
#define PLANT_MEASUREMENT   false

    
/*!Fundamental PWM Settings
 * *************************************************************************************************
 * Summary:
 * Global defines for PWM settings of DV330101
 * 
 * Description:
 * This section defines fundamental PWM settings required for the low-voltage interleaved boost
 * PFC development board. These settings are determined by hardware. User-selectable settings 
 * are made on application layer level (e.g. in apl.h), outside this header file.
 * 
 * Pre-compiler macros are used to convert physical values into binary (integer) numbers to 
 * be written to SFRs
 * 
 * *************************************************************************************************/

#define BUCK_NO_OF_PHASES              2U     // Number of power converter phases of this design
    
#define BUCK_PWM_DUTY_CYCLE_MIN        (float)0.010 // ~1.0% On Time 
#define BUCK_PWM_DUTY_CYCLE_MAX        (float)0.600 // ~80% On Time 
#define BUCK_LEADING_EDGE_BLANKING     (float)120.0e-9 // Leading Edge Blanking in [sec]
#define BUCK_DEAD_TIME_LEADING_EDGE    (float)10.0e-9 // Leading Edge Dead Time in [sec]
#define BUCK_DEAD_TIME_FALLING_EDGE    (float)10.0e-9 // Falling Edge Dead Time in [sec]

// PWM Phase #1 Configuration
#define BUCK_PWM1_CHANNEL              1U // PWM Instance Index (e.g. 1=PWM1, 2=PWM2, etc.)
#define BUCK_PWM1_GPIO_INSTANCE        1U // Number indicating device port, where 0=A, 1=B, 2=C, etc.
#define BUCK_PWM1_GPIO_PORT_PINH       14U // Port Pin Number
#define BUCK_PWM1_GPIO_PORT_PINL       15U // Port Pin Number
    
#define BUCK_PWM1_PDC                   PG1DC    // PWM Instance Duty Cycle Register
#define BUCK_PWM1H_TRIS                 _TRISB14 // Device Port TRIS register
#define BUCK_PWM1H_WR                   _LATB14  // Device Pin WRITE
#define BUCK_PWM1H_RD                   _RB14    // Device Pin READ
#define BUCK_PWM1L_TRIS                 _TRISB15 // Device Port TRIS register
#define BUCK_PWM1L_WR                   _LATB15  // Device Pin WRITE
#define BUCK_PWM1L_RD                   _RB15    // Device Pin READ

#define _BUCK_PWM1_Interrupt            _PWM1Interrupt // PWM Interrupt Service Routine label
#define BUCK_PWM1_IF                    _PWM1IF  // PWM Interrupt Flag Bit
#define BUCK_PWM1_IE                    _PWM1IE  // PWM Interrupt Enable Bit
#define BUCK_PWM1_IP                    _PWM1IP  // PWM Interrupt Priority
#define BUCK_PWM1_TRGSRC_TRG1           0b00100  // PWM Trigger #1 Trigger Source of this channel
#define BUCK_PWM1_TRGSRC_TRG2           0b00101  // PWM Trigger #2 Trigger Source of this channel
#define BUCK_PWM1_PGxTRIGA              PG1TRIGA // PWM trigger register A
#define BUCK_PWM1_PGxTRIGB              PG1TRIGB // PWM trigger register B
#define BUCK_PWM1_PGxTRIGC              PG1TRIGC // PWM trigger register C
    
#define BUCK_PWM1_ADTR1OFS              0U // ADC Trigger 1 Offset:  0...31
#define BUCK_PWM1_ADTR1PS               1U // ADC Trigger 1 Postscaler: 0...31

// PWM Phase #2 Configuration
#define BUCK_PWM2_CHANNEL               4U    // PWM Instance Index (e.g. 1=PWM1, 2=PWM2, etc.)
#define BUCK_PWM2_GPIO_INSTANCE         1U // Number indicating device port, where 0=A, 1=B, 2=C, etc.
#define BUCK_PWM2_GPIO_PORT_PINH        6U // Port Pin Number
#define BUCK_PWM2_GPIO_PORT_PINL        5U // Port Pin Number

#define BUCK_PWM2_PDC                   PG4DC    // PWM Instance Duty Cycle Register
#define BUCK_PWM2H_TRIS                 _TRISB6  // Device Port TRIS register
#define BUCK_PWM2H_WR                   _LATB6   // Device Pin WRITE
#define BUCK_PWM2H_RD                   _RB6     // Device Pin READ
#define BUCK_PWM2L_TRIS                 _TRISB5  // Device Port TRIS register
#define BUCK_PWM2L_WR                   _LATB5   // Device Pin WRITE
#define BUCK_PWM2L_RD                   _RB5     // Device Pin READ
    
#define _BUCK_PWM2_Interrupt            _PWM4Interrupt // PWM Interrupt Serivice Routine label
#define BUCK_PWM2_IF                    _PWM4IF        // PWM Interrupt Flag Bit
#define BUCK_PWM2_IE                    _PWM4IE        // PWM Interrupt Enable Bit
#define BUCK_PWM2_IP                    _PWM4IP        // PWM Interrupt Priority
#define BUCK_PWM2_TRGSRC_TRG1           0b01010  // PWM2 Trigger #1 Trigger Source of this channel
#define BUCK_PWM2_TRGSRC_TRG2           0b01011  // PWM2 Trigger #2 Trigger Source of this channel
#define BUCK_PWM2_PGxTRIGA              PG4TRIGA // PWM2 trigger register A
#define BUCK_PWM2_PGxTRIGB              PG4TRIGB // PWM2 trigger register B
#define BUCK_PWM2_PGxTRIGC              PG4TRIGC // PWM2 trigger register C

#define BUCK_PWM2_ADTR1OFS              0U // ADC Trigger 1 Offset:  0...31
#define BUCK_PWM2_ADTR1PS               1U // ADC Trigger 1 Postscaler: 0...31
    
#define BUCK_PWM_MASTER_SOCS            0b0001  // PWM1 provides Master Trigger
    
// ~~~ conversion macros ~~~~~~~~~~~~~~~~~~~~~~~~~
#define BUCK_SWITCHING_PERIOD      (float)(1.0/SWITCHING_FREQUENCY)   // Switching period in [sec]
#define BUCK_PWM_PERIOD            (uint16_t)(float)(BUCK_SWITCHING_PERIOD / PWM_CLOCK_PERIOD)
#define BUCK_PWM_PHASE_SHIFT       (uint16_t)((float)BUCK_PWM_PERIOD / (float)BUCK_NO_OF_PHASES)      
#define BUCK_PWM_DC_MIN            (uint16_t)(BUCK_PWM_DUTY_CYCLE_MIN * (float)BUCK_PWM_PERIOD) // This sets the minimum duty cycle
#define BUCK_PWM_DC_MAX            (uint16_t)(BUCK_PWM_DUTY_CYCLE_MAX * (float)BUCK_PWM_PERIOD) // This sets the maximum duty cycle
#define BUCK_LEB_PERIOD            (uint16_t)(BUCK_LEADING_EDGE_BLANKING / (float)PWM_CLOCK_PERIOD) // Leading Edge Blanking = n x PWM resolution (here: 50 x 2ns = 100ns)
#define BUCK_PWM_DEAD_TIME_LE      (uint16_t)(BUCK_DEAD_TIME_LEADING_EDGE / (float)PWM_CLOCK_PERIOD) // Rising edge dead time [tick = 250ps]
#define BUCK_PWM_DEAD_TIME_FE      (uint16_t)(BUCK_DEAD_TIME_FALLING_EDGE / (float)PWM_CLOCK_PERIOD) // Falling edge dead time [tick = 250ps]
// ~~~ conversion macros end ~~~~~~~~~~~~~~~~~~~~~


    
/*!Input Voltage Feedback
 * *************************************************************************************************
 * Summary: Declaration of input voltage limits and nominal operating points
 * 
 * Description:
 * 
 * *************************************************************************************************/
    
#define BUCK_VIN_MINIMUM        (float)20.000   // Minimum input voltage
#define BUCK_VIN_NOMINAL        (float)48.000   // Nominal input voltage
#define BUCK_VIN_MAXIMUM        (float)60.500   // Maximum input voltage

#define BUCK_VIN_UNDER_VOLTAGE  (float)19.50    // Under Voltage Lock Out Cut Off
#define BUCK_VIN_OVER_VOLTAGE   (float)61.00    // Over Voltage Lock Out Cut Off
#define BUCK_VIN_HYSTERESIS     (float)1.500    // UVLO/OVLO Hysteresis
    
#define BUCK_VIN_R1             (float)(100.0)  // Upper voltage divider resistor in kOhm
#define BUCK_VIN_R2             (float)(5.360)  // Lower voltage divider resistor in kOhm
#define BUCK_VIN_FEEDBACK_GAIN  (float)((BUCK_VIN_R2) / (BUCK_VIN_R1 + BUCK_VIN_R2))
    
#define BUCK_VIN_FEEDBACK_OFFSET    (float)(0.0)
#define BUCK_VIN_ADC_TRG_DELAY      (float)(120.0e-9) // ADC trigger delay in [sec]
    
// ~ conversion macros ~~~~~~~~~~~~~~~~~~~~~
    
#define BUCK_VIN_MIN            (uint16_t)(BUCK_VIN_MINIMUM * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN)   // Minimum input voltage
#define BUCK_VIN_NOM            (uint16_t)(BUCK_VIN_NOMINAL * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN)   // Nominal input voltage
#define BUCK_VIN_MAX            (uint16_t)(BUCK_VIN_MAXIMUM * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN)   // Maximum input voltage
#define BUCK_VIN_HYST           (uint16_t)(BUCK_VIN_HYSTERESIS * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN)  // Over Voltage LOck Out voltage    
#define BUCK_VIN_UVLO_TRIP      (uint16_t)(BUCK_VIN_UNDER_VOLTAGE * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN) // Under Voltage LOck Out voltage
#define BUCK_VIN_UVLO_RELEASE   (uint16_t)((BUCK_VIN_UNDER_VOLTAGE + BUCK_VIN_HYSTERESIS) * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN) // Under Voltage LOck Out voltage
#define BUCK_VIN_OVLO_TRIP      (uint16_t)(BUCK_VIN_OVER_VOLTAGE * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN)  // Over Voltage LOck Out voltage
#define BUCK_VIN_OVLO_RELEASE   (uint16_t)((BUCK_VIN_OVER_VOLTAGE - BUCK_VIN_HYSTERESIS) * BUCK_VIN_FEEDBACK_GAIN / ADC_GRAN)  // Over Voltage LOck Out voltage
#define BUCK_VIN_ADC_TRGDLY     (uint16_t)(BUCK_VIN_ADC_TRG_DELAY / PWM_CLOCK_PERIOD) // Input voltage ADC trigger delay
#define BUCK_VIN_OFFSET         (uint16_t)(BUCK_VIN_FEEDBACK_OFFSET / ADC_GRAN) // Input voltage feedback offset

#define BUCK_VIN_NORM_INV_G     (float)(1.0/BUCK_VIN_FEEDBACK_GAIN) // Inverted feedback gain required for value normalization
#define BUCK_VIN_NORM_SCALER    (int16_t)(ceil(log(BUCK_VIN_NORM_INV_G)) + 1) // VIN normalization  
#define BUCK_VIN_NORM_FACTOR    (int16_t)((BUCK_VIN_NORM_INV_G / pow(2.0, BUCK_VIN_NORM_SCALER)) * (pow(2.0, 15)-1)) // VIN normalization factor scaled in Q15

#define BUCK_VIN_RANGE_MAX     (float)(ADC_REF * BUCK_VIN_NORM_INV_G)
    
// ~ conversion macros end ~~~~~~~~~~~~~~~~~
    
#define _BUCK_VIN_ADCInterrupt  _ADCAN10Interrupt   
#define _BUCK_VIN_ADCISR_IF     _ADCAN10IF

#define BUCK_VIN_ANSEL          _ANSELB8    // GPIO analog function mode enable bit
#define BUCK_VIN_ADCCORE        8           // 0=Dedicated Core #0, 1=Dedicated Core #1, 8=Shared ADC Core
#define BUCK_VIN_ADCIN          10           // Analog input number (e.g. '5' for 'AN5')
#define BUCK_VIN_ADCBUF         ADCBUF10     // ADC input buffer of this ADC channel
#define BUCK_VIN_ADCTRIG        PG1TRIGA    // Register used for trigger placement
#define BUCK_VIN_TRGSRC         BUCK_PWM1_TRGSRC_TRG1 // PWM1 (=PG2) Trigger 2 via PGxTRIGB

/*!Output Voltage Feedback
 * *************************************************************************************************
 * Summary:
 * 
 * Description:
 * 
 * *************************************************************************************************/

// Feedback Declarations
#define BUCK_VOUT_NOMINAL           (float)12.70   // Nominal output voltage
#define BUCK_VOUT_TOLERANCE_MAX     (float)0.800   // Output voltage tolerance [+/-]
#define BUCK_VOUT_TOLERANCE_MIN     (float)0.300   // Output voltage tolerance [+/-]
    
#define BUCK_VOUT_DIV_R1            (float)(100.00) // Upper voltage divider resistor in kOhm
#define BUCK_VOUT_DIV_R2            (float)(5.360) // Lower voltage divider resistor in kOhm
#define BUCK_VOUT_FEEDBACK_GAIN     (float)((BUCK_VOUT_DIV_R2) / (BUCK_VOUT_DIV_R1 + BUCK_VOUT_DIV_R2))
#define BUCK_VOUT_FEEDBACK_OFFSET   (float)(0.0)
#define BUCK_VOUT_ADC_TRG_DELAY     (float)(0.0e-9) // Trigger delay in [sec]

// Peripheral Assignments
#define BUCK_VOUT_ANSEL             _ANSELB9    // GPIO analog function mode enable bit
#define BUCK_VOUT_ADCCORE           8           // 0=Dedicated Core #0, 1=Dedicated Core #1, 8=Shared ADC Core
#define BUCK_VOUT_ADCIN             11           // Analog input number (e.g. '5' for 'AN5')
#define BUCK_VOUT_ADCBUF            ADCBUF11     // ADC input buffer of this ADC channel
#define BUCK_VOUT_ADCTRIG           PG1TRIGA    // Register used for trigger placement
#define BUCK_VOUT_TRGSRC            BUCK_PWM1_TRGSRC_TRG1 // PWM1 (=PG2) Trigger 1 via PGxTRIGA
    
// ~ conversion macros ~~~~~~~~~~~~~~~~~~~~~

#define BUCK_VOUT_REF           (uint16_t)(BUCK_VOUT_NOMINAL * BUCK_VOUT_FEEDBACK_GAIN / ADC_GRAN)
#define BUCK_VOUT_NOM           BUCK_VOUT_REF
#define BUCK_VOUT_DEV_TRIP      (uint16_t)(BUCK_VOUT_TOLERANCE_MAX * BUCK_VOUT_FEEDBACK_GAIN / ADC_GRAN)
#define BUCK_VOUT_DEV_RELEASE   (uint16_t)(BUCK_VOUT_TOLERANCE_MIN * BUCK_VOUT_FEEDBACK_GAIN / ADC_GRAN)
#define BUCK_VOUT_OFFSET        (uint16_t)(BUCK_VOUT_FEEDBACK_OFFSET / ADC_GRAN)
#define BUCK_VOUT_ADC_TRGDLY    (uint16_t)(BUCK_VOUT_ADC_TRG_DELAY / PWM_CLOCK_PERIOD)

#define BUCK_VOUT_NORM_INV_G    (float)(1.0/BUCK_VOUT_FEEDBACK_GAIN) // Inverted feedback gain required for value normalization
#define BUCK_VOUT_NORM_SCALER   (int16_t)(ceil(log(BUCK_VOUT_NORM_INV_G)) + 1) // VOUT normalization  
#define BUCK_VOUT_NORM_FACTOR   (int16_t)((BUCK_VOUT_NORM_INV_G / pow(2.0, BUCK_VOUT_NORM_SCALER)) * (pow(2.0, 15)-1)) // VOUT normalization factor scaled in Q15

#define BUCK_VOUT_RANGE_MAX     (float)(ADC_REF * BUCK_VOUT_NORM_INV_G)
    
// ~ conversion macros end ~~~~~~~~~~~~~~~~~

/*!Ideal Duty Cycle
 * *************************************************************************************************
 * Summary:
 * 
 * Description:
 * 
 * *************************************************************************************************/
#define BUCK_NORM_IDEAL_DC(x, y) (float)(((float)x/(float)y)*(((float)BUCK_VOUT_NORM_FACTOR/(float)BUCK_VIN_NORM_FACTOR)*pow(2, (BUCK_VOUT_NORM_SCALER-BUCK_VIN_NORM_SCALER))))

/*!Phase Current Feedback
 * *************************************************************************************************
 * Summary:
 * 
 * Description:
 * 
 * *************************************************************************************************/

#define BUCK_ISNS_NEED_CALIBRATION  false                // Flag indicating that current feedback needs calibration
    
// Feedback Declarations
#define BUCK_ISNS_FEEDBACK_GAIN     (float) 0.010       // Current Gain in V/A
#define BUCK_ISNS_MAXIMUM           (float) 148.0       // absolute total maximum output current (average)
#define BUCK_ISNS_RELEASE           (float) 140.0       // current reset level after over current event
#define BUCK_ISNS_REFERENCE         (float) 5.00       // output current reference (average) for each phase
#define BUCK_ISNS_REFERENCE_MAX     (float) 74.00       // output current reference maximum value (average) for each phase
#define BUCK_ISNS_COMMON_MODE_LIMIT (float)  3.5       // phase current sense common mode voltage minimum 
    
#define BUCK_ISNS1_ADC_TRG_DELAY    (float) 716.0e-9    // ADC trigger delay for current sense in [sec]
#define BUCK_ISNS2_ADC_TRG_DELAY    (float) 700.0e-9    // ADC trigger delay for current sense in [sec]    

#define BUCK_ISNS1_FEEDBACK_OFFSET  (float) 1.547       // current sense #1 feedback offset (average)
#define BUCK_ISNS2_FEEDBACK_OFFSET  (float) 1.547       // current sense #2 feedback offset (average)
    
// Peripheral Assignments
#define _BUCK_ISNS1_ADCInterrupt    _ADCAN1Interrupt   
#define _BUCK_ISNS1_ADCISR_IF       _ADCAN1IF

#define BUCK_ISNS1_ANSEL            _ANSELB2    // GPIO analog function mode enable bit
#define BUCK_ISNS1_ADCCORE          1           // 0=Dedicated Core #0, 1=Dedicated Core #1, 2=Shared ADC Core
#define BUCK_ISNS1_ADCIN            1           // Analog input number (e.g. '5' for 'AN5')
#define BUCK_ISNS1_ADCBUF           ADCBUF1     // ADC input buffer of this ADC channel
#define BUCK_ISNS1_ADCTRIG          PG1TRIGA    // Register used for trigger placement
#define BUCK_ISNS1_TRGSRC           BUCK_PWM1_TRGSRC_TRG1 // PWM1 (=PG1) Trigger 2 via PGxTRIGB

#define _BUCK_ISNS2_ADCInterrupt    _ADCAN2Interrupt   
#define _BUCK_ISNS2_ADCISR_IF       _ADCAN2IF

#define BUCK_ISNS2_ANSEL            _ANSELB7    // GPIO analog function mode enable bit
#define BUCK_ISNS2_ADCCORE          8           // 0=Dedicated Core #0, 1=Dedicated Core #1, 2=Shared ADC Core
#define BUCK_ISNS2_ADCIN            2           // Analog input number (e.g. '5' for 'AN5')
#define BUCK_ISNS2_ADCBUF           ADCBUF2     // ADC input buffer of this ADC channel
#define BUCK_ISNS2_ADCTRIG          PG4TRIGA    // Register used for trigger placement
#define BUCK_ISNS2_TRGSRC           BUCK_PWM2_TRGSRC_TRG1 // PWM2 (=PG4) Trigger 2 via PGxTRIGB

// ~ conversion macros ~~~~~~~~~~~~~~~~~~~~~

#define BUCK_ISNS_OCL           (uint16_t)((BUCK_ISNS_MAXIMUM * BUCK_ISNS_FEEDBACK_GAIN + BUCK_ISNS1_FEEDBACK_OFFSET + BUCK_ISNS2_FEEDBACK_OFFSET) / ADC_GRAN)  // Over Current Limit
#define BUCK_ISNS_OCL_RELEASE   (uint16_t)((BUCK_ISNS_RELEASE * BUCK_ISNS_FEEDBACK_GAIN + BUCK_ISNS1_FEEDBACK_OFFSET + BUCK_ISNS2_FEEDBACK_OFFSET) / ADC_GRAN)  // Over Current Release Level
#define BUCK_ISNS_REF           (uint16_t)(BUCK_ISNS_REFERENCE * BUCK_ISNS_FEEDBACK_GAIN / ADC_GRAN)  // Output Current Reference
#define BUCK_ISNS_REF_MAX       (uint16_t)(BUCK_ISNS_REFERENCE_MAX * BUCK_ISNS_FEEDBACK_GAIN / ADC_GRAN)
#define BUCK_ISNS_CMOD_LIMIT    (uint16_t)(BUCK_ISNS_COMMON_MODE_LIMIT * BUCK_VOUT_FEEDBACK_GAIN / ADC_GRAN) ///< Common Mode Voltage Limit specifies the minimum output voltage required before the current sense feedback becomes reliable    
#define BUCK_ISNS1_OFFFSET      (uint16_t)(BUCK_ISNS1_FEEDBACK_OFFSET / ADC_GRAN)
#define BUCK_ISNS2_OFFFSET      (uint16_t)(BUCK_ISNS2_FEEDBACK_OFFSET / ADC_GRAN)
#define BUCK_ISNS1_ADC_TRGDLY   (uint16_t)(BUCK_ISNS1_ADC_TRG_DELAY / PWM_CLOCK_PERIOD)
#define BUCK_ISNS2_ADC_TRGDLY   (uint16_t)(BUCK_ISNS2_ADC_TRG_DELAY / PWM_CLOCK_PERIOD)    

#define BUCK_ISNS_NORM_INV_G    (float)(1.0/BUCK_ISNS_FEEDBACK_GAIN) // Inverted feedback gain required for value normalization
#define BUCK_ISNS_NORM_SCALER   (int16_t)(ceil(log(BUCK_ISNS_NORM_INV_G)) + 1) // ISNS normalization  
#define BUCK_ISNS_NORM_FACTOR   (int16_t)((BUCK_ISNS_NORM_INV_G / pow(2.0, BUCK_ISNS_NORM_SCALER)) * (pow(2.0, 15)-1)) // ISNS normalization factor scaled in Q15
    
// ~ conversion macros end ~~~~~~~~~~~~~~~~~

/*!Temperature Sense
 * *************************************************************************************************
 * Summary:
 * 
 * Description:
 * 
 * *************************************************************************************************/
// Feedback Declarations
#define BUCK_TEMP_FEEDBACK_GAIN     (float) 4.3194      // AD590 with 3.48k load gain
#define BUCK_TEMP_FEEDBACK_OFFSET   (float) 1179.2      // AD590 with 3.48k load offset
#define BUCK_TEMP_MAXIMUM           (float) 95.0        // maximum heatsink temperature to trip over temperature fault (deg C)
#define BUCK_TEMP_RELEASE           (float) 80.0        // temperature reset level after over temperature event

// Peripheral Assignments
#define BUCK_TEMP_ANSEL             _ANSELB0    // GPIO analog function mode enable bit
#define BUCK_TEMP_ADCCORE           8           // 0=Dedicated Core #0, 1=Dedicated Core #1, 8=Shared ADC Core
#define BUCK_TEMP_ADCIN             5           // Analog input number (e.g. '5' for 'AN5')
#define BUCK_TEMP_ADCBUF            ADCBUF5     // ADC input buffer of this ADC channel
#define BUCK_TEMP_ADCTRIG           PG4TRIGA    // Register used for trigger placement
#define BUCK_TEMP_TRGSRC            BUCK_PWM2_TRGSRC_TRG1 // PWM2 (=PG4) Trigger 1 via PGxTRIGA
    
// ~ conversion macros ~~~~~~~~~~~~~~~~~~~~~

#define BUCK_TEMP_OTL           (uint16_t)(BUCK_TEMP_MAXIMUM * BUCK_TEMP_FEEDBACK_GAIN + BUCK_TEMP_FEEDBACK_OFFSET)  // Over Temperature Limit
#define BUCK_TEMP_OTL_RELEASE   (uint16_t)(BUCK_TEMP_RELEASE * BUCK_TEMP_FEEDBACK_GAIN + BUCK_TEMP_FEEDBACK_OFFSET)  // Over Temperature Release Level    
/*!Adaptive Gain Control Feed Forward
 * *************************************************************************************************
 * Summary:
 * 
 * Description:
 * 
 * *************************************************************************************************/
    
#define BUCK_VL_MINIMUM         (float)(BUCK_VIN_UNDER_VOLTAGE - BUCK_VOUT_RANGE_MAX) // Minimum input voltage - maximum output voltate
#define BUCK_VL_NOMINAL         (float)(BUCK_VIN_NOMINAL       - BUCK_VOUT_NOMINAL) // Nominal input voltage - nominal output voltate
#define BUCK_VL_MAXIMUM         (float)(BUCK_VIN_RANGE_MAX     - 0) // Maximum input voltage - 0

#define BUCK_VIN_NORM_FCT       (float)(BUCK_VOUT_FEEDBACK_GAIN / BUCK_VIN_FEEDBACK_GAIN)   // VIN-2-VOUT Normalization Factor

// ~ conversion macros ~~~~~~~~~~~~~~~~~~~~~
    
#define BUCK_AGC_IO_NORM_SCALER (int16_t)(ceil(log(BUCK_VIN_NORM_FCT)) + 1) // Nominal VL Q15 scaler  
#define BUCK_AGC_IO_NORM_FACTOR (int16_t)((BUCK_VIN_NORM_FCT / pow(2.0, BUCK_AGC_IO_NORM_SCALER)) * (pow(2.0, 15)-1)) // Nominal VL Q15 factor 

// The AGC compare value is defined at the lowest input voltage and highest output voltage 
// (= lowest voltage across inductor)
// ToDo: Remove - min VIN turned out to be too cumbersome when tuning coefficients to nominal conditions
//#define BUCK_AGC_MEDIAN         (int16_t)((float)BUCK_VIN_UVLO_TRIP * BUCK_VIN_NORM_FCT)

// The AGC compare value is defined at nominal input voltage and output voltage 
#define BUCK_AGC_MEDIAN         (int16_t)(((float)BUCK_VIN_NOM * BUCK_VIN_NORM_FCT) - BUCK_VOUT_NOM)

#define BUCK_AGC_FACTOR_MAX     (float)(BUCK_VL_NOMINAL / BUCK_VL_MINIMUM)
#define BUCK_AGC_NOM_SCALER     (uint16_t)(ceil(log(BUCK_AGC_FACTOR_MAX)) + 1)
#define BUCK_AGC_NOM_FACTOR     (uint16_t)(0x7FFF >> BUCK_AGC_NOM_SCALER)
// ~ conversion macros end ~~~~~~~~~~~~~~~~~

/*!Startup Behavior
 * *************************************************************************************************
 * Summary:
 * Global defines for soft-start specific parameters
 * 
 * Description:
 * This section is used to define power supply startup timing setting. The soft-start sequence 
 * is part of the power controller. It allows to program specific timings for Power On Delay,
 * Ramp Period and Power Good Delay. After the startup has passed these three timing periods,
 * the power supply is ending up in "normal" operation, continuously regulating the output until 
 * a fault is detected or the operating state is changed for any other reason.
 * 
 * Pre-compiler macros are used to translate physical values into binary (integer) numbers to 
 * be written to SFRs and variables.
 * 
 * *************************************************************************************************/

// On EPC9143 Rev 4 it takes roughly 50 ms until the auxiliary power has been started
// and the controller completes self-test and peripheral configuration. After this period
// the controller starts to execute the power control state machine.
    
// This additional startup delay of ~50 ms is not considered here and needs to be taken into 
// account when adjusting startup timing.
    
#define BUCK_POWER_ON_DELAY          (float) 100e-3 // power on delay in [sec]
#define BUCK_VRAMP_PERIOD            (float) 100e-3 // ramp period in [sec]
#define BUCK_IRAMP_PERIOD            (float) 100e-3 // ramp period in [sec]
#define BUCK_POWER_GOOD_DELAY        (float) 200e-3 // power good in [sec]

// ~ conversion macros ~~~~~~~~~~~~~~~~~~~~~

#define BUCK_POD       (uint16_t)(((float)BUCK_POWER_ON_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0)
#define BUCK_VRAMP_PER (uint16_t)(((float)BUCK_VRAMP_PERIOD / (float)MAIN_EXECUTION_PERIOD)-1.0)
#define BUCK_VREF_STEP (uint16_t)((float)BUCK_VOUT_REF / (float)(BUCK_VRAMP_PER + 1.0))
#define BUCK_IRAMP_PER (uint16_t)(((float)BUCK_IRAMP_PERIOD / (float)MAIN_EXECUTION_PERIOD)-1.0)
#define BUCK_IREF_STEP (uint16_t)((float)BUCK_ISNS_REF_MAX / (float)(BUCK_VRAMP_PER + 1.0))
#define BUCK_PGD       (uint16_t)(((float)BUCK_POWER_GOOD_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0)

// ~ conversion macros end ~~~~~~~~~~~~~~~~~

    
/*!Controller Declarations
 * *************************************************************************************************
 * Summary:
 * 
 * 
 * Description:
 * 
 * 
 * *************************************************************************************************/

    
// Hardware-dependent defines
#define BUCK_VOUT_TRIG_PWM  0   // Buck VOUT control loop is called in PWM interrupt
#define BUCK_VOUT_TRIG_ADC  1   // Buck VOUT control loop is called in ADC interrupt

#define BUCK_VOUT_TRIGGER_MODE  BUCK_VOUT_TRIG_ADC
    
#if (BUCK_VOUT_TRIGGER_MODE == BUCK_VOUT_TRIG_ADC)    
  #define _BUCK_VLOOP_Interrupt     _ADCAN1Interrupt   
  #define _BUCK_VLOOP_ISR_IP        _ADCAN1IP
  #define _BUCK_VLOOP_ISR_IF        _ADCAN1IF
  #define _BUCK_VLOOP_ISR_IE        _ADCAN1IE
#elif (BUCK_VOUT_TRIGGER_MODE == BUCK_VOUT_TRIG_PWM)
  #define _BUCK_VLOOP_Interrupt     _PWM2Interrupt   
  #define _BUCK_VLOOP_ISR_IP        _PWM2IP
  #define _BUCK_VLOOP_ISR_IF        _PWM2IF
  #define _BUCK_VLOOP_ISR_IE        _PWM2IE
#endif

// Firmware version records
#define FIRMWARE_VER_NUM0   0U
#define FIRMWARE_VER_NUM1   1U
#define FIRMWARE_VER_NUM2   0U
#define FIRMWARE_RET_CKSUM  (uint8_t)( (118U + FIRMWARE_VER_NUM0 + FIRMWARE_VER_NUM1 + FIRMWARE_VER_NUM2)%256U )


#endif	/* EPC9137_R40_HARDWARE_DESCRIPTOR_H */

