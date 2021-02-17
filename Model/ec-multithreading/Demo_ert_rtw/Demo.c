/*
 * File: Demo.c
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

#include "Demo.h"
#include "Demo_private.h"

/* Tasks */
RT_MODEL_Demo_T task_M_[2];
RT_MODEL_Demo_T *task_M[2];

/* Exported block signals */
real_T In1;                            /* '<Root>/Input' */
real_T In2;                            /* '<Root>/Input1' */
real_T ResultSignal;                   /* '<Root>/Result' */
real_T PG;                             /* '<Root>/PostGain' */
real_T O1;                             /* '<S2>/Sum' */

/* Block signals (default storage) */
B_Demo_T Demo_B;

/* Block states (default storage) */
DW_Demo_T Demo_DW;

/* Real-time model */
static RT_MODEL_Demo_T Demo_M_;
RT_MODEL_Demo_T *const Demo_M = &Demo_M_;

/*   This function updates active task counters and model execution time. */
void AdvanceTaskCounters(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Demo_M->Timing.TaskCounters.TID[1])++;
  if ((Demo_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.01s, 0.0s] */
    Demo_M->Timing.TaskCounters.TID[1] = 0;
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.001, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
}

/* OutputUpdate for Task: Gain_Normal */
void Gain_Normal_step(void)            /* Sample time: [0.001s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_PreGain;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.001s, 0.0s] to Sample time: [0.01s, 0.0s]  */
  task_M[0]->Timing.RateInteraction.b_TID0_1 = (task_M[0]
    ->Timing.RateInteraction.TID0_1 == 0);
  (task_M[0]->Timing.RateInteraction.TID0_1)++;
  if ((task_M[0]->Timing.RateInteraction.TID0_1) > 9) {
    task_M[0]->Timing.RateInteraction.TID0_1 = 0;
  }

  /* ModelReference: '<Root>/PreGain' incorporates:
   *  Inport: '<Root>/Input'
   */
  Gain(&In1, &rtb_PreGain);

  /* RateTransition: '<Root>/RT_In' */
  if (task_M[0]->Timing.RateInteraction.TID0_1 == 1) {
    Demo_DW.RT_In_RdBufIdx = (int8_T)(Demo_DW.RT_In_RdBufIdx == 0);
  }

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  Demo_B.DiscreteTimeIntegrator = Demo_DW.DiscreteTimeIntegrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  RateTransition: '<Root>/RT_In'
   *  Sum: '<S1>/Sum'
   */
  Demo_DW.DiscreteTimeIntegrator_DSTATE +=
    (Demo_DW.RT_In_Buf[Demo_DW.RT_In_RdBufIdx] + rtb_PreGain) * 0.001;

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* ModelReference: '<Root>/PostGain' */
  Gain(&Demo_B.DiscreteTimeIntegrator, &PG);

  /* RateTransition: '<Root>/RT_Post' */
  if (task_M[0]->Timing.RateInteraction.TID0_1 == 1) {
    Demo_DW.RT_Post_RdBufIdx = (int8_T)(Demo_DW.RT_Post_RdBufIdx == 0);
  }

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem1' */
  /* Sum: '<S2>/Sum' incorporates:
   *  RateTransition: '<Root>/RT_Post'
   */
  O1 = Demo_DW.RT_Post_Buf[Demo_DW.RT_Post_RdBufIdx] + PG;

  /* End of Outputs for SubSystem: '<Root>/Subsystem1' */

  /* Outport: '<Root>/Result' */
  ResultSignal = O1;

  /* RateTransition: '<Root>/RT_Pre' */
  if (task_M[0]->Timing.RateInteraction.TID0_1 == 1) {
    Demo_DW.RT_Pre_WrBufIdx = (int8_T)(Demo_DW.RT_Pre_WrBufIdx == 0);
  }

  Demo_DW.RT_Pre_Buf[Demo_DW.RT_Pre_WrBufIdx] = Demo_B.DiscreteTimeIntegrator;

  /* End of RateTransition: '<Root>/RT_Pre' */
}

/* OutputUpdate for Task: Gain_Slow */
void Gain_Slow_step(void)              /* Sample time: [0.01s, 0.0s] */
{
  /* ModelReference: '<Root>/PreSlowGain' incorporates:
   *  Inport: '<Root>/Input1'
   */
  SlowGain(&In2, &Demo_B.PreSlowGain);

  /* RateTransition: '<Root>/RT_Pre' */
  Demo_DW.RT_Pre_RdBufIdx = (int8_T)(Demo_DW.RT_Pre_RdBufIdx == 0);

  /* RateTransition: '<Root>/RT_Pre' */
  Demo_B.RT_Pre = Demo_DW.RT_Pre_Buf[Demo_DW.RT_Pre_RdBufIdx];

  /* ModelReference: '<Root>/PreSlowGain1' */
  SlowGain(&Demo_B.RT_Pre, &Demo_B.PreSlowGain1);

  /* RateTransition: '<Root>/RT_Post' */
  Demo_DW.RT_Post_WrBufIdx = (int8_T)(Demo_DW.RT_Post_WrBufIdx == 0);
  Demo_DW.RT_Post_Buf[Demo_DW.RT_Post_WrBufIdx] = Demo_B.PreSlowGain1;

  /* RateTransition: '<Root>/RT_In' */
  Demo_DW.RT_In_WrBufIdx = (int8_T)(Demo_DW.RT_In_WrBufIdx == 0);
  Demo_DW.RT_In_Buf[Demo_DW.RT_In_WrBufIdx] = Demo_B.PreSlowGain;
}

void Demo_step(int_T tid)
{
  switch (tid) {
   case 0 :
    Gain_Normal_step();
    break;

   case 1 :
    Gain_Slow_step();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void Demo_initialize(void)
{
  /* Registration code */
  {
    /* user code (registration function declaration) */
    int_T tIdx;
    for (tIdx = 0; tIdx < 2; tIdx++) {
      task_M[tIdx] = &task_M_[tIdx];

      /* initialize real-time model */
      (void) memset((void *) task_M[tIdx], 0,
                    sizeof(RT_MODEL_Demo_T));
    }
  }

  /* Model Initialize function for ModelReference Block: '<Root>/PostGain' */
  Gain_initialize(rtmGetErrorStatusPointer(Demo_M),
                  &(Demo_DW.PostGain_InstanceData.rtm));

  /* Model Initialize function for ModelReference Block: '<Root>/PreGain' */
  Gain_initialize(rtmGetErrorStatusPointer(Demo_M),
                  &(Demo_DW.PreGain_InstanceData.rtm));

  /* Model Initialize function for ModelReference Block: '<Root>/PreSlowGain' */
  SlowGain_initialize(rtmGetErrorStatusPointer(Demo_M),
                      &(Demo_DW.PreSlowGain_InstanceData.rtm));

  /* Model Initialize function for ModelReference Block: '<Root>/PreSlowGain1' */
  SlowGain_initialize(rtmGetErrorStatusPointer(Demo_M),
                      &(Demo_DW.PreSlowGain1_InstanceData.rtm));

  /* InitializeConditions for RateTransition: '<Root>/RT_In' */
  Demo_DW.RT_In_RdBufIdx = 1;

  /* InitializeConditions for RateTransition: '<Root>/RT_Post' */
  Demo_DW.RT_Post_RdBufIdx = 1;

  /* InitializeConditions for RateTransition: '<Root>/RT_Pre' */
  Demo_DW.RT_Pre_RdBufIdx = 1;
}

/* Model terminate function */
void Demo_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
