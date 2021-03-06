/* *********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.10.501
 * *********************************************************************************
 * 2p2z controller function declarations and compensation filter coefficients
 * derived for following operating conditions:
 * *********************************************************************************
 *
 *  Controller Type:    2P2Z - Basic Current Mode Compensator
 *  Sampling Frequency: 125000 Hz
 *  Fixed Point Format: Q15
 *  Scaling Mode:       3 - Dual Bit-Shift Scaling
 *  Input Gain:         1
 *
 * *********************************************************************************
 * CGS Version:         2.0.13
 * CGS Date:            07/30/2020
 * *********************************************************************************
 * User:                Yuanzhe
 * Date/Time:           4/27/2021 3:47:16 PM
 * ********************************************************************************/

#include "./pwr_control/drivers/i_loop_1.h"

/* *********************************************************************************
 * Data Arrays:
 * This source file declares the default parameters of the z-domain compensation
 * filter. The NPNZ16b_t data structure contains two pointers to A- and B-
 * coefficient arrays and two pointers to control and error history arrays.
 *
 * For optimized data processing during DSP computations, these arrays must be
 * located in specific memory locations (X-space for coefficient arrays and
 * Y-space for control and error history arrays).
 *
 * The following declarations are used to define the array data contents, their
 * length and memory location. These declarations are made publicly accessible
 * through extern declarations in header file i_loop_1.h
 * ********************************************************************************/

volatile struct I_LOOP_1_CONTROL_LOOP_COEFFICIENTS_s __attribute__((space(xmemory), near)) i_loop_1_coefficients; // A/B-Coefficients
volatile uint16_t i_loop_1_ACoefficients_size = (sizeof(i_loop_1_coefficients.ACoefficients)/sizeof(i_loop_1_coefficients.ACoefficients[0])); // A-coefficient array size
volatile uint16_t i_loop_1_BCoefficients_size = (sizeof(i_loop_1_coefficients.BCoefficients)/sizeof(i_loop_1_coefficients.BCoefficients[0])); // B-coefficient array size

volatile struct I_LOOP_1_CONTROL_LOOP_HISTORIES_s __attribute__((space(ymemory), far)) i_loop_1_histories; // Control/Error Histories
volatile uint16_t i_loop_1_ControlHistory_size = (sizeof(i_loop_1_histories.ControlHistory)/sizeof(i_loop_1_histories.ControlHistory[0])); // Control history array size
volatile uint16_t i_loop_1_ErrorHistory_size = (sizeof(i_loop_1_histories.ErrorHistory)/sizeof(i_loop_1_histories.ErrorHistory[0])); // Error history array size

/* *********************************************************************************
 * Pole&Zero Placement:
 * *********************************************************************************
 *
 *    fP0:    500 Hz
 *    fP1:    75000 Hz
 *    fZ1:    2500 Hz
 *
 * *********************************************************************************
 * Filter Coefficients and Parameters:
 * ********************************************************************************/
volatile int32_t i_loop_1_ACoefficients [2] =
{
    0x000058BD, // Coefficient A1 will be multiplied with controller output u(n-1)
    0x00002744  // Coefficient A2 will be multiplied with controller output u(n-2)
};

volatile int32_t i_loop_1_BCoefficients [3] =
{
    0x0000471C, // Coefficient B0 will be multiplied with error input e(n-0)
    0x00000869, // Coefficient B1 will be multiplied with error input e(n-1)
    0x0000C14D  // Coefficient B2 will be multiplied with error input e(n-2)
};

// Coefficient normalization factors
volatile int16_t i_loop_1_pre_scaler = 3;
volatile int16_t i_loop_1_post_shift_A = 0;
volatile int16_t i_loop_1_post_shift_B = 2;
volatile fractional i_loop_1_post_scaler = 0x0000;


// User-defined NPNZ16b_t controller data object
volatile struct NPNZ16b_s i_loop_1; // user-controller data object

/* ********************************************************************************/

/*!i_loop_1_Init()
 * *********************************************************************************
 * Summary: Initializes controller coefficient arrays and normalization
 *
 * Parameters:
 *     - struct NPNZ16b_s* controller
 *
 * Returns:
 *     - uint16_t:  0->failure
 *                  1->success

 * Description:
 * This function needs to be called from user code once to initialize coefficient
 * arrays and number normalization settings of the i_loop_1 controller
 * object.
 *
 * PLEASE NOTE:
 * This routine DOES NOT initialize the complete controller object.
 * User-defined settings such as pointers to the control reference, source and
 * target registers, output minima and maxima and further, design-dependent
 * settings, need to be specified in user code.
 * ********************************************************************************/
volatile uint16_t i_loop_1_Initialize(volatile struct NPNZ16b_s* controller)
{
    volatile uint16_t i=0;

    // Initialize controller data structure at runtime with pre-defined default values
    controller->status.value = NPNZ16_CONTROL_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))
    
    controller->Filter.ptrACoefficients = &i_loop_1_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
    controller->Filter.ptrBCoefficients = &i_loop_1_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
    controller->Filter.ptrControlHistory = &i_loop_1_histories.ControlHistory[0]; // initialize pointer to control history array
    controller->Filter.ptrErrorHistory = &i_loop_1_histories.ErrorHistory[0]; // initialize pointer to error history array
    controller->Filter.normPostShiftA = i_loop_1_post_shift_A; // initialize A-coefficients/single bit-shift scaler
    controller->Filter.normPostShiftB = i_loop_1_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
    controller->Filter.normPostScaler = i_loop_1_post_scaler; // initialize control output value normalization scaling factor
    controller->Filter.normPreShift = i_loop_1_pre_scaler; // initialize A-coefficients/single bit-shift scaler
    
    controller->Filter.ACoefficientsArraySize = i_loop_1_ACoefficients_size; // initialize A-coefficients array size
    controller->Filter.BCoefficientsArraySize = i_loop_1_BCoefficients_size; // initialize A-coefficients array size
    controller->Filter.ControlHistoryArraySize = i_loop_1_ControlHistory_size; // initialize control history array size
    controller->Filter.ErrorHistoryArraySize = i_loop_1_ErrorHistory_size; // initialize error history array size
    
    
    // Load default set of A-coefficients from user RAM into X-Space controller A-array
    for(i=0; i<controller->Filter.ACoefficientsArraySize; i++)
    {
        i_loop_1_coefficients.ACoefficients[i] = i_loop_1_ACoefficients[i];
    }

    // Load default set of B-coefficients from user RAM into X-Space controller B-array
    for(i=0; i<controller->Filter.BCoefficientsArraySize; i++)
    {
        i_loop_1_coefficients.BCoefficients[i] = i_loop_1_BCoefficients[i];
    }

    // Clear error and control histories of the 3P3Z controller
    i_loop_1_Reset(&i_loop_1);
    
    return(1);
}


//**********************************************************************************
// Download latest version of this tool here: https://areiter128.github.io/DCLD
//**********************************************************************************

