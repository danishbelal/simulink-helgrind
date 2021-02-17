/*
 * File: Demo.h
 *
 * Code generated for Simulink model 'Demo'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Tue Feb 16 10:14:45 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Demo_h_
#define RTW_HEADER_Demo_h_
#include <string.h>
#include <stddef.h>
#ifndef Demo_COMMON_INCLUDES_
#define Demo_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Demo_COMMON_INCLUDES_ */

#include "Demo_types.h"

/* Child system includes */
#include "Gain.h"
#include "SlowGain.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real_T PreSlowGain;                  /* '<Root>/PreSlowGain' */
  real_T PreSlowGain1;                 /* '<Root>/PreSlowGain1' */
  real_T DiscreteTimeIntegrator;       /* '<S1>/Discrete-Time Integrator' */
  real_T RT_Pre;                       /* '<Root>/RT_Pre' */
} B_Demo_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real_T RT_In_Buf[2];                 /* '<Root>/RT_In' */
  real_T RT_Post_Buf[2];               /* '<Root>/RT_Post' */
  real_T RT_Pre_Buf[2];                /* '<Root>/RT_Pre' */
  int8_T RT_In_RdBufIdx;               /* '<Root>/RT_In' */
  int8_T RT_In_WrBufIdx;               /* '<Root>/RT_In' */
  int8_T RT_Post_RdBufIdx;             /* '<Root>/RT_Post' */
  int8_T RT_Post_WrBufIdx;             /* '<Root>/RT_Post' */
  int8_T RT_Pre_RdBufIdx;              /* '<Root>/RT_Pre' */
  int8_T RT_Pre_WrBufIdx;              /* '<Root>/RT_Pre' */
  MdlrefDW_Gain_T PreGain_InstanceData;/* '<Root>/PreGain' */
  MdlrefDW_Gain_T PostGain_InstanceData;/* '<Root>/PostGain' */
  MdlrefDW_SlowGain_T PreSlowGain_InstanceData;/* '<Root>/PreSlowGain' */
  MdlrefDW_SlowGain_T PreSlowGain1_InstanceData;/* '<Root>/PreSlowGain1' */
} DW_Demo_T;

/* Real-time Model Data Structure */
struct tag_RTM_Demo_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint32_T TID[2];
    } TaskCounters;

    struct {
      uint32_T TID0_1;
      boolean_T b_TID0_1;
    } RateInteraction;
  } Timing;
};

/* Block signals (default storage) */
extern B_Demo_T Demo_B;

/* Block states (default storage) */
extern DW_Demo_T Demo_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T In1;                     /* '<Root>/Input' */
extern real_T In2;                     /* '<Root>/Input1' */
extern real_T ResultSignal;            /* '<Root>/Result' */
extern real_T PG;                      /* '<Root>/PostGain' */
extern real_T O1;                      /* '<S2>/Sum' */
extern void Demo_step(int_T tid);
extern void AdvanceTaskCounters(void);

/* Model entry point functions */
extern void Demo_initialize(void);
extern void Demo_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Demo_T *const Demo_M;

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
 * '<Root>' : 'Demo'
 * '<S1>'   : 'Demo/Subsystem'
 * '<S2>'   : 'Demo/Subsystem1'
 */
#endif                                 /* RTW_HEADER_Demo_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
