/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: dc_motor_pid.h
 *
 * Code generated for Simulink model 'dc_motor_pid'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Sat Jun 13 13:59:24 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef dc_motor_pid_h_
#define dc_motor_pid_h_
#ifndef dc_motor_pid_COMMON_INCLUDES_
#define dc_motor_pid_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* dc_motor_pid_COMMON_INCLUDES_ */

#include "dc_motor_pid_types.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T FilterCoefficient;            /* '<S39>/Filter Coefficient' */
  real_T Sum;                          /* '<S45>/Sum' */
  real_T IntegralGain;                 /* '<S33>/Integral Gain' */
} B_dc_motor_pid_T;

/* Continuous states (default storage) */
typedef struct {
  real_T TF_motor_CSTATE[2];           /* '<Root>/TF_motor' */
  real_T Filter_CSTATE;                /* '<S31>/Filter' */
  real_T Integrator_CSTATE;            /* '<S36>/Integrator' */
} X_dc_motor_pid_T;

/* State derivatives (default storage) */
typedef struct {
  real_T TF_motor_CSTATE[2];           /* '<Root>/TF_motor' */
  real_T Filter_CSTATE;                /* '<S31>/Filter' */
  real_T Integrator_CSTATE;            /* '<S36>/Integrator' */
} XDot_dc_motor_pid_T;

/* State disabled  */
typedef struct {
  boolean_T TF_motor_CSTATE[2];        /* '<Root>/TF_motor' */
  boolean_T Filter_CSTATE;             /* '<S31>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S36>/Integrator' */
} XDis_dc_motor_pid_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_dc_motor_pid_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_dc_motor_pid_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_dc_motor_pid_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[4];
  real_T odeF[4][4];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_dc_motor_pid_T dc_motor_pid_B;

/* Continuous states (default storage) */
extern X_dc_motor_pid_T dc_motor_pid_X;

/* Disabled states (default storage) */
extern XDis_dc_motor_pid_T dc_motor_pid_XDis;

/* Model entry point functions */
extern void dc_motor_pid_initialize(void);
extern void dc_motor_pid_step(void);
extern void dc_motor_pid_terminate(void);

/* Real-time Model object */
extern RT_MODEL_dc_motor_pid_T *const dc_motor_pid_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<S41>/Proportional Gain' : Eliminated nontunable gain of 1
 */

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
 * '<Root>' : 'dc_motor_pid'
 * '<S1>'   : 'dc_motor_pid/PID'
 * '<S2>'   : 'dc_motor_pid/PID/Anti-windup'
 * '<S3>'   : 'dc_motor_pid/PID/D Gain'
 * '<S4>'   : 'dc_motor_pid/PID/External Derivative'
 * '<S5>'   : 'dc_motor_pid/PID/Filter'
 * '<S6>'   : 'dc_motor_pid/PID/Filter ICs'
 * '<S7>'   : 'dc_motor_pid/PID/I Gain'
 * '<S8>'   : 'dc_motor_pid/PID/Ideal P Gain'
 * '<S9>'   : 'dc_motor_pid/PID/Ideal P Gain Fdbk'
 * '<S10>'  : 'dc_motor_pid/PID/Integrator'
 * '<S11>'  : 'dc_motor_pid/PID/Integrator ICs'
 * '<S12>'  : 'dc_motor_pid/PID/N Copy'
 * '<S13>'  : 'dc_motor_pid/PID/N Gain'
 * '<S14>'  : 'dc_motor_pid/PID/P Copy'
 * '<S15>'  : 'dc_motor_pid/PID/Parallel P Gain'
 * '<S16>'  : 'dc_motor_pid/PID/Reset Signal'
 * '<S17>'  : 'dc_motor_pid/PID/Saturation'
 * '<S18>'  : 'dc_motor_pid/PID/Saturation Fdbk'
 * '<S19>'  : 'dc_motor_pid/PID/Sum'
 * '<S20>'  : 'dc_motor_pid/PID/Sum Fdbk'
 * '<S21>'  : 'dc_motor_pid/PID/Tracking Mode'
 * '<S22>'  : 'dc_motor_pid/PID/Tracking Mode Sum'
 * '<S23>'  : 'dc_motor_pid/PID/Tsamp - Integral'
 * '<S24>'  : 'dc_motor_pid/PID/Tsamp - Ngain'
 * '<S25>'  : 'dc_motor_pid/PID/postSat Signal'
 * '<S26>'  : 'dc_motor_pid/PID/preInt Signal'
 * '<S27>'  : 'dc_motor_pid/PID/preSat Signal'
 * '<S28>'  : 'dc_motor_pid/PID/Anti-windup/Passthrough'
 * '<S29>'  : 'dc_motor_pid/PID/D Gain/Internal Parameters'
 * '<S30>'  : 'dc_motor_pid/PID/External Derivative/Error'
 * '<S31>'  : 'dc_motor_pid/PID/Filter/Cont. Filter'
 * '<S32>'  : 'dc_motor_pid/PID/Filter ICs/Internal IC - Filter'
 * '<S33>'  : 'dc_motor_pid/PID/I Gain/Internal Parameters'
 * '<S34>'  : 'dc_motor_pid/PID/Ideal P Gain/Passthrough'
 * '<S35>'  : 'dc_motor_pid/PID/Ideal P Gain Fdbk/Disabled'
 * '<S36>'  : 'dc_motor_pid/PID/Integrator/Continuous'
 * '<S37>'  : 'dc_motor_pid/PID/Integrator ICs/Internal IC'
 * '<S38>'  : 'dc_motor_pid/PID/N Copy/Disabled'
 * '<S39>'  : 'dc_motor_pid/PID/N Gain/Internal Parameters'
 * '<S40>'  : 'dc_motor_pid/PID/P Copy/Disabled'
 * '<S41>'  : 'dc_motor_pid/PID/Parallel P Gain/Internal Parameters'
 * '<S42>'  : 'dc_motor_pid/PID/Reset Signal/Disabled'
 * '<S43>'  : 'dc_motor_pid/PID/Saturation/Passthrough'
 * '<S44>'  : 'dc_motor_pid/PID/Saturation Fdbk/Disabled'
 * '<S45>'  : 'dc_motor_pid/PID/Sum/Sum_PID'
 * '<S46>'  : 'dc_motor_pid/PID/Sum Fdbk/Disabled'
 * '<S47>'  : 'dc_motor_pid/PID/Tracking Mode/Disabled'
 * '<S48>'  : 'dc_motor_pid/PID/Tracking Mode Sum/Passthrough'
 * '<S49>'  : 'dc_motor_pid/PID/Tsamp - Integral/TsSignalSpecification'
 * '<S50>'  : 'dc_motor_pid/PID/Tsamp - Ngain/Passthrough'
 * '<S51>'  : 'dc_motor_pid/PID/postSat Signal/Forward_Path'
 * '<S52>'  : 'dc_motor_pid/PID/preInt Signal/Internal PreInt'
 * '<S53>'  : 'dc_motor_pid/PID/preSat Signal/Forward_Path'
 */
#endif                                 /* dc_motor_pid_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
