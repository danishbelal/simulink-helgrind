/*
 * File: SlowGain.h
 *
 * Code generated for Simulink model 'SlowGain'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Tue Feb 16 09:30:32 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SlowGain_h_
#define RTW_HEADER_SlowGain_h_
#ifndef SlowGain_COMMON_INCLUDES_
#define SlowGain_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* SlowGain_COMMON_INCLUDES_ */

#include "SlowGain_types.h"

/* Real-time Model Data Structure */
struct tag_RTM_SlowGain_T {
  const char_T **errorStatus;
};

typedef struct {
  RT_MODEL_SlowGain_T rtm;
} MdlrefDW_SlowGain_T;

/* Model reference registration function */
extern void SlowGain_initialize(const char_T **rt_errorStatus,
  RT_MODEL_SlowGain_T *const SlowGain_M);
extern void SlowGain(const real_T *rtu_Input, real_T *rty_Out1);

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
 * '<Root>' : 'SlowGain'
 */
#endif                                 /* RTW_HEADER_SlowGain_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
