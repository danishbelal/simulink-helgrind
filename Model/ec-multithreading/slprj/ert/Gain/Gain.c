/*
 * File: Gain.c
 *
 * Code generated for Simulink model 'Gain'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Tue Feb 16 09:30:25 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Gain.h"
#include "Gain_private.h"

/* Output and update for referenced model: 'Gain' */
void Gain(const real_T *rtu_Input, real_T *rty_Out1)
{
  /* Gain: '<Root>/Gain' */
  *rty_Out1 = *rtu_Input;
}

/* Model initialize function */
void Gain_initialize(const char_T **rt_errorStatus, RT_MODEL_Gain_T *const
                     Gain_M)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(Gain_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
