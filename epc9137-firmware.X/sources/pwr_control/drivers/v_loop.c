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
 * Date/Time:           4/27/2021 3:51:36 PM
 * ********************************************************************************/

#include "./pwr_control/drivers/v_loop.h"

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
 * through extern declarations in header file v_loop.h
 * ********************************************************************************/

volatile struct V_LOOP_CONTROL_LOOP_COEFFICIENTS_s __attribute__((space(xmemory), near)) v_loop_coefficients; // A/B-Coefficients
volatile uint16_t v_loop_ACoefficients_size = (sizeof(v_loop_coefficients.ACoefficients)/sizeof(v_loop_coefficients.ACoefficients[0])); // A-coefficient array size
volatile uint16_t v_loop_BCoefficients_size = (sizeof(v_loop_coefficients.BCoefficients)/sizeof(v_loop_coefficients.BCoefficients[0])); // B-coefficient array size

volatile struct V_LOOP_CONTROL_LOOP_HISTORIES_s __attribute__((space(ymemory), far)) v_loop_histories; // Control/Error Histories
volatile uint16_t v_loop_ControlHistory_size = (sizeof(v_loop_histories.ControlHistory)/sizeof(v_loop_histories.ControlHistory[0])); // Control history array size
volatile uint16_t v_loop_ErrorHistory_size = (sizeof(v_loop_histories.ErrorHistory)/sizeof(v_loop_histories.ErrorHistory[0])); // Error history array size

/* *********************************************************************************
 * Pole&Zero Placement:
 * *********************************************************************************
 *
 *    fP0:    80 Hz
 *    fP1:    45000 Hz
 *    fZ1:    250 Hz
 *
 * *********************************************************************************
 * Filter Coefficients and Parameters:
 * ********************************************************************************/
volatile int32_t v_loop_ACoefficients [2] =
{
    0x00007823, // Coefficient A1 will be multiplied with controller output u(n-1)
    0x000007DE  // Coefficient A2 will be multiplied with controller output u(n-2)
};

volatile int32_t v_loop_BCoefficients [3] =
{
    0x00005781, // Coefficient B0 will be multiplied with error input e(n-0)
    0x00000118, // Coefficient B1 will be multiplied with error input e(n-1)
    0x0000A998  // Coefficient B2 will be multiplied with error input e(n-2)
};

// Coefficient normalization factors
volatile int16_t v_loop_pre_scaler = 3;
volatile int16_t v_loop_post_shift_A = 0;
volatile int16_t v_loop_post_shift_B = 2;
volatile fractional v_loop_post_scaler = 0x0000;

// P-Term Coefficient for Plant Measurements
volatile int16_t v_loop_pterm_factor = 0x54D6;
volatile int16_t v_loop_pterm_scaler = 0x0000;


// User-defined NPNZ16b_t controller data object
volatile struct NPNZ16b_s v_loop; // user-controller data object

/* ********************************************************************************/

/*!v_loop_Init()
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
 * arrays and number normalization settings of the v_loop controller
 * object.
 *
 * PLEASE NOTE:
 * This routine DOES NOT initialize the complete controller object.
 * User-defined settings such as pointers to the control reference, source and
 * target registers, output minima and maxima and further, design-dependent
 * settings, need to be specified in user code.
 * ********************************************************************************/
volatile uint16_t v_loop_Initialize(volatile struct NPNZ16b_s* controller)
{
    volatile uint16_t i=0;

    // Initialize controller data structure at runtime with pre-defined default values
    controller->status.value = NPNZ16_CONTROL_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))
    
    controller->Filter.ptrACoefficients = &v_loop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
    controller->Filter.ptrBCoefficients = &v_loop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
    controller->Filter.ptrControlHistory = &v_loop_histories.ControlHistory[0]; // initialize pointer to control history array
    controller->Filter.ptrErrorHistory = &v_loop_histories.ErrorHistory[0]; // initialize pointer to error history array
    controller->Filter.normPostShiftA = v_loop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
    controller->Filter.normPostShiftB = v_loop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
    controller->Filter.normPostScaler = v_loop_post_scaler; // initialize control output value normalization scaling factor
    controller->Filter.normPreShift = v_loop_pre_scaler; // initialize A-coefficients/single bit-shift scaler
    
    controller->Filter.ACoefficientsArraySize = v_loop_ACoefficients_size; // initialize A-coefficients array size
    controller->Filter.BCoefficientsArraySize = v_loop_BCoefficients_size; // initialize A-coefficients array size
    controller->Filter.ControlHistoryArraySize = v_loop_ControlHistory_size; // initialize control history array size
    controller->Filter.ErrorHistoryArraySize = v_loop_ErrorHistory_size; // initialize error history array size
    
    
    // Load default set of A-coefficients from user RAM into X-Space controller A-array
    for(i=0; i<controller->Filter.ACoefficientsArraySize; i++)
    {
        v_loop_coefficients.ACoefficients[i] = v_loop_ACoefficients[i];
    }

    // Load default set of B-coefficients from user RAM into X-Space controller B-array
    for(i=0; i<controller->Filter.BCoefficientsArraySize; i++)
    {
        v_loop_coefficients.BCoefficients[i] = v_loop_BCoefficients[i];
    }

    // Clear error and control histories of the 3P3Z controller
    v_loop_Reset(&v_loop);
    
    // Load P-Term factor and scaler into data structure
    controller->Filter.PTermFactor = v_loop_pterm_factor;;
    controller->Filter.PTermScaler = v_loop_pterm_scaler;
    
    return(1);
}


//**********************************************************************************
// Download latest version of this tool here: https://areiter128.github.io/DCLD
//**********************************************************************************

