/*
 * File: Gain.h
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

#ifndef RTW_HEADER_Gain_h_
#define RTW_HEADER_Gain_h_
#ifndef Gain_COMMON_INCLUDES_
#define Gain_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Gain_COMMON_INCLUDES_ */

#include "Gain_types.h"

/* Real-time Model Data Structure */
struct tag_RTM_Gain_T {
  const char_T **errorStatus;
};

typedef struct {
  RT_MODEL_Gain_T rtm;
} MdlrefDW_Gain_T;

/* Model reference registration function */
extern void Gain_initialize(const char_T **rt_errorStatus, RT_MODEL_Gain_T *
  const Gain_M);
extern void Gain(const real_T *rtu_Input, real_T *rty_Out1);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Gain'
 */
#endif                                 /* RTW_HEADER_Gain_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
