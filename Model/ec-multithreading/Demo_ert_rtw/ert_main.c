/*
 * File: ert_main.c
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

#include <windows.h>
#include <process.h>
#include <processthreadsapi.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "Demo.h"                      /* Model's header file */
#include "rtwtypes.h"
#define CHECK_STATUS(status,fcn)       if (status != 0) {fprintf(stderr, "Call to %s returned error status (%d).\n", (fcn),(status)); perror((fcn)); fflush(stderr); exit(EXIT_FAILURE);}

typedef struct {
  HANDLE threadHandle;
  unsigned threadID;
  int_T index;
  HANDLE startEvent;
  HANDLE stopEvent;
  LONG exitFlag;
} ThreadInfo;

ThreadInfo periodicThread[2];
ThreadInfo periodicTriggerThread[1];
int threadPriority[4] = { THREAD_PRIORITY_ABOVE_NORMAL,
  THREAD_PRIORITY_NORMAL,
  THREAD_PRIORITY_BELOW_NORMAL,
  THREAD_PRIORITY_LOWEST };

HANDLE quitEvent = NULL;
BOOL OnCtrlHandler(DWORD ctrl)
{
  /* Unused argument */
  (void)(ctrl);
  SetEvent(quitEvent);
  return true;
}

unsigned __stdcall GainTaskScheduler(void *arg)
{
  volatile boolean_T noErr;
  DWORD waitResult;
  HANDLE orTimer;
  LARGE_INTEGER orDueTime;
  int_T i;

  /* Unused argument */
  (void)(arg);
  int_T taskCounters[2] = { 0, 0 };

  int_T taskTicks[2] = { 1, 10 };

  int_T taskId[2] = { 0, 1 };

  noErr = (rtmGetErrorStatus(Demo_M) == (NULL));
  orTimer = CreateWaitableTimer(NULL, false, NULL);
  orDueTime.QuadPart = (LONGLONG)(0.001 * 1e7 * -1);
  while (noErr) {
    /* Check for Ctrl+C event */
    waitResult = WaitForSingleObject(quitEvent, 0);
    if ((waitResult == WAIT_OBJECT_0) || (waitResult == WAIT_FAILED)) {
      /* The quitEvent is set or the wait failed */
      noErr = false;
      continue;
    }

    CHECK_STATUS(SetWaitableTimer(orTimer, &orDueTime, 0, NULL, NULL, false) ==
                 false, "SetWaitableTimer");
    for (i = 0; i < 2; i++) {
      if (taskCounters[i] == 0) {
        waitResult = WaitForSingleObject(periodicThread[taskId[i]].stopEvent, 0);
        if (waitResult == WAIT_TIMEOUT) {
          printf("Overrun - rate for periodic task %d too fast.\n", taskId[i]);
          WaitForSingleObject(periodicThread[taskId[i]].stopEvent, INFINITE);
        }
      }
    }

    noErr = (rtmGetErrorStatus(Demo_M) == (NULL));
    if (noErr) {
      for (i = 0; i <2; i++) {
        if (taskCounters[i] == 0) {
          SetEvent(periodicThread[taskId[i]].startEvent);
        }
      }

      for (i = 0; i <2; i++) {
        taskCounters[i]++;
        if (taskCounters[i] > (taskTicks[i]-1)) {
          taskCounters[i] = 0;
        }
      }
    } else {
      for (i = 0; i < 2; i++) {
        if (taskCounters[i] != 0) {
          WaitForSingleObject(periodicThread[taskId[i]].stopEvent,INFINITE);
        }
      }
    }

    if (WaitForSingleObject(orTimer, 0) == WAIT_OBJECT_0) {
      printf("Overrun - periodic trigger 0 base rate too fast.\n");
    }
  }                                    /* while */

  for (i = 0; i < 2; i++) {
    InterlockedIncrement(&periodicThread[taskId[i]].exitFlag);
    SetEvent(periodicThread[taskId[i]].startEvent);
  }

  _endthreadex(0);
  return 0;
}

unsigned __stdcall periodicTask(void *arg)
{
  DWORD waitResult;
  ThreadInfo* info = (ThreadInfo*)arg;
  volatile boolean_T noErr = true;
  while (noErr) {
    waitResult = WaitForSingleObject(info->startEvent,INFINITE);
    if ((waitResult != WAIT_OBJECT_0) || info->exitFlag) {
      /* Wait failed or exitFlag is set */
      noErr = false;
      continue;
    }

    Demo_step(info->index);

    /* Get model outputs here */
    SetEvent(info->stopEvent);
  }

  _endthreadex(0);
  return 0;
}

int main(int argc, char *argv[])
{
  int i, j;
  SYSTEM_INFO sysinfo;
  DWORD_PTR processMask;
  DWORD_PTR systemMask;
  DWORD_PTR threadMask;
  int coreAffinity[2][1];
  int numCores;
  int priority[2];

  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  priority[0] = threadPriority[0];
  coreAffinity[0][0] = 1;
  priority[1] = threadPriority[1];
  coreAffinity[1][0] = 1;
  CHECK_STATUS(SetConsoleCtrlHandler((PHANDLER_ROUTINE)OnCtrlHandler, true) ==
               false, "SetConsoleCtrlHandler");
  printf("**starting the model**\n");
  fflush(stdout);

  /* Initialize model */
  Demo_initialize();
  rtmSetErrorStatus(Demo_M, 0);

  /* Set the priority of the main thread */
  CHECK_STATUS(SetThreadPriority(GetCurrentThread(),
    THREAD_PRIORITY_TIME_CRITICAL) == false, "SetThreadPriority");

  /* Create & initialize events used for thread synchronization */
  quitEvent = CreateEvent(NULL, true, false, NULL);
  CHECK_STATUS(quitEvent == NULL,"CreateEvent");
  GetSystemInfo(&sysinfo);
  numCores = sysinfo.dwNumberOfProcessors;
  CHECK_STATUS(GetProcessAffinityMask(GetCurrentProcess(), &processMask,
    &systemMask) == false, "GetProcessAffinityMask");

  /* Create periodic threads */
  for (i = 0; i < 2; i++) {
    periodicThread[i].index = (int_T) i;
    periodicThread[i].exitFlag = 0;

    /* Create the events that will be used by the thread */
    periodicThread[i].startEvent = CreateEvent(NULL, false, false, NULL);
    CHECK_STATUS(periodicThread[i].startEvent == NULL, "CreateEvent");
    periodicThread[i].stopEvent = CreateEvent(NULL, false, true, NULL);
    CHECK_STATUS(periodicThread[i].stopEvent == NULL, "CreateStopEventEvent");

    /* Create the thread in suspended mode */
    periodicThread[i].threadHandle = (HANDLE)_beginthreadex(NULL, 0,
      &periodicTask, &periodicThread[i], CREATE_SUSPENDED, &periodicThread[i].
      threadID);
    CHECK_STATUS(periodicThread[i].threadID == 0,"_beginthreadex");

    /* Set the thread priority */
    CHECK_STATUS(SetThreadPriority(periodicThread[i].threadHandle, priority[i]) ==
                 false, "SetThreadPriority");

    /* Create the thread mask */
    threadMask = 0;
    for (j = 0; j < 1; j++) {
      if ((coreAffinity[i][j] >= 0) && (coreAffinity[i][j] < numCores)) {
        /* Set the (coreAffinity[i][j]+1)th rightmost bit in threadMask */
        threadMask |= (1 << coreAffinity[i][j]);
      }
    }

    /* Set the core affinity */
    if (threadMask != 0) {
      CHECK_STATUS(SetThreadAffinityMask(periodicThread[i].threadHandle,
        threadMask) == 0, "SetThreadAffinityMask");
    }

    /* Start the thread */
    CHECK_STATUS(ResumeThread(periodicThread[i].threadHandle) == -1,
                 "ResumeThread");
  }

  /* Create periodic trigger threads */
  {
    periodicTriggerThread[0].index = 0;
    periodicTriggerThread[0].exitFlag = 0;
    periodicTriggerThread[0].startEvent = NULL;
    periodicTriggerThread[0].stopEvent = NULL;

    /* Create the thread in suspended mode */
    periodicTriggerThread[0].threadHandle = (HANDLE)_beginthreadex(NULL, 0,
      &GainTaskScheduler, NULL, CREATE_SUSPENDED, &periodicTriggerThread[0].
      threadID);
    CHECK_STATUS(periodicTriggerThread[0].threadHandle == 0,"_beginthreadex");

    /* Set the periodic trigger thread priority */
    CHECK_STATUS(SetThreadPriority(periodicTriggerThread[0].threadHandle,
      THREAD_PRIORITY_HIGHEST) == false, "SetThreadPriority");

    /* Start the periodic trigger thread */
    CHECK_STATUS(ResumeThread(periodicTriggerThread[0].threadHandle) == -1,
                 "ResumeThread");
  }

  /* Wait for a stopping condition. */
  for (i = 0; i < 1; i++) {
    WaitForSingleObject(periodicTriggerThread[i].threadHandle, INFINITE);
  }

  /* Clean up */
  for (i = 0; i< 1; i++) {
    if (periodicTriggerThread[i].threadHandle != NULL) {
      CloseHandle(periodicTriggerThread[i].threadHandle);
    }
  }

  if (quitEvent != NULL) {
    CloseHandle(quitEvent);
  }

  for (i = 0; i < 2; i++) {
    if (periodicThread[i].startEvent != NULL) {
      CloseHandle(periodicThread[i].startEvent);
    }

    if (periodicThread[i].stopEvent != NULL) {
      CloseHandle(periodicThread[i].stopEvent);
    }

    if (periodicThread[i].threadHandle != NULL) {
      CloseHandle(periodicThread[i].threadHandle);
    }
  }

  printf("**stopping the model**\n");
  fflush(stdout);
  if (rtmGetErrorStatus(Demo_M) != NULL) {
    fprintf(stderr, "\n**%s**\n", rtmGetErrorStatus(Demo_M));
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  Demo_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
