/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: dc_motor_pid.c
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

#include "dc_motor_pid.h"
#include "rtwtypes.h"
#include "dc_motor_pid_private.h"

/* Block signals (default storage) */
B_dc_motor_pid_T dc_motor_pid_B;

/* Continuous states */
X_dc_motor_pid_T dc_motor_pid_X;

/* Disabled State Vector */
XDis_dc_motor_pid_T dc_motor_pid_XDis;

/* Real-time model */
static RT_MODEL_dc_motor_pid_T dc_motor_pid_M_;
RT_MODEL_dc_motor_pid_T *const dc_motor_pid_M = &dc_motor_pid_M_;

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  dc_motor_pid_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  dc_motor_pid_step();
  dc_motor_pid_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  dc_motor_pid_step();
  dc_motor_pid_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  dc_motor_pid_step();
  dc_motor_pid_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void dc_motor_pid_step(void)
{
  real_T rtb_Sum;
  if (rtmIsMajorTimeStep(dc_motor_pid_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&dc_motor_pid_M->solverInfo,
                          ((dc_motor_pid_M->Timing.clockTick0+1)*
      dc_motor_pid_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(dc_motor_pid_M)) {
    dc_motor_pid_M->Timing.t[0] = rtsiGetT(&dc_motor_pid_M->solverInfo);
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Step: '<Root>/Step'
   *  TransferFcn: '<Root>/TF_motor'
   */
  rtb_Sum = (real_T)!(dc_motor_pid_M->Timing.t[0] < 1.0) - (0.0 *
    dc_motor_pid_X.TF_motor_CSTATE[0] + 2.0 * dc_motor_pid_X.TF_motor_CSTATE[1]);

  /* Gain: '<S39>/Filter Coefficient' incorporates:
   *  Gain: '<S29>/Derivative Gain'
   *  Integrator: '<S31>/Filter'
   *  Sum: '<S31>/SumD'
   */
  dc_motor_pid_B.FilterCoefficient = (0.05 * rtb_Sum -
    dc_motor_pid_X.Filter_CSTATE) * 100.0;

  /* Sum: '<S45>/Sum' incorporates:
   *  Integrator: '<S36>/Integrator'
   */
  dc_motor_pid_B.Sum = (rtb_Sum + dc_motor_pid_X.Integrator_CSTATE) +
    dc_motor_pid_B.FilterCoefficient;

  /* Gain: '<S33>/Integral Gain' */
  dc_motor_pid_B.IntegralGain = 0.5 * rtb_Sum;
  if (rtmIsMajorTimeStep(dc_motor_pid_M)) {
    rt_ertODEUpdateContinuousStates(&dc_motor_pid_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++dc_motor_pid_M->Timing.clockTick0;
    dc_motor_pid_M->Timing.t[0] = rtsiGetSolverStopTime
      (&dc_motor_pid_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      dc_motor_pid_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void dc_motor_pid_derivatives(void)
{
  XDot_dc_motor_pid_T *_rtXdot;
  _rtXdot = ((XDot_dc_motor_pid_T *) dc_motor_pid_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/TF_motor' */
  _rtXdot->TF_motor_CSTATE[0] = -12.0 * dc_motor_pid_X.TF_motor_CSTATE[0];
  _rtXdot->TF_motor_CSTATE[0] += -20.0 * dc_motor_pid_X.TF_motor_CSTATE[1];
  _rtXdot->TF_motor_CSTATE[1] = dc_motor_pid_X.TF_motor_CSTATE[0];
  _rtXdot->TF_motor_CSTATE[0] += dc_motor_pid_B.Sum;

  /* Derivatives for Integrator: '<S31>/Filter' */
  _rtXdot->Filter_CSTATE = dc_motor_pid_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S36>/Integrator' */
  _rtXdot->Integrator_CSTATE = dc_motor_pid_B.IntegralGain;
}

/* Model initialize function */
void dc_motor_pid_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&dc_motor_pid_M->solverInfo,
                          &dc_motor_pid_M->Timing.simTimeStep);
    rtsiSetTPtr(&dc_motor_pid_M->solverInfo, &rtmGetTPtr(dc_motor_pid_M));
    rtsiSetStepSizePtr(&dc_motor_pid_M->solverInfo,
                       &dc_motor_pid_M->Timing.stepSize0);
    rtsiSetdXPtr(&dc_motor_pid_M->solverInfo, &dc_motor_pid_M->derivs);
    rtsiSetContStatesPtr(&dc_motor_pid_M->solverInfo, (real_T **)
                         &dc_motor_pid_M->contStates);
    rtsiSetNumContStatesPtr(&dc_motor_pid_M->solverInfo,
      &dc_motor_pid_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&dc_motor_pid_M->solverInfo,
      &dc_motor_pid_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&dc_motor_pid_M->solverInfo,
      &dc_motor_pid_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&dc_motor_pid_M->solverInfo,
      &dc_motor_pid_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&dc_motor_pid_M->solverInfo, (boolean_T**)
      &dc_motor_pid_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&dc_motor_pid_M->solverInfo, (&rtmGetErrorStatus
      (dc_motor_pid_M)));
    rtsiSetRTModelPtr(&dc_motor_pid_M->solverInfo, dc_motor_pid_M);
  }

  rtsiSetSimTimeStep(&dc_motor_pid_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&dc_motor_pid_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&dc_motor_pid_M->solverInfo, false);
  dc_motor_pid_M->intgData.y = dc_motor_pid_M->odeY;
  dc_motor_pid_M->intgData.f[0] = dc_motor_pid_M->odeF[0];
  dc_motor_pid_M->intgData.f[1] = dc_motor_pid_M->odeF[1];
  dc_motor_pid_M->intgData.f[2] = dc_motor_pid_M->odeF[2];
  dc_motor_pid_M->intgData.f[3] = dc_motor_pid_M->odeF[3];
  dc_motor_pid_M->contStates = ((X_dc_motor_pid_T *) &dc_motor_pid_X);
  dc_motor_pid_M->contStateDisabled = ((XDis_dc_motor_pid_T *)
    &dc_motor_pid_XDis);
  dc_motor_pid_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&dc_motor_pid_M->solverInfo, (void *)
                    &dc_motor_pid_M->intgData);
  rtsiSetSolverName(&dc_motor_pid_M->solverInfo,"ode4");
  rtmSetTPtr(dc_motor_pid_M, &dc_motor_pid_M->Timing.tArray[0]);
  dc_motor_pid_M->Timing.stepSize0 = 0.001;

  /* InitializeConditions for TransferFcn: '<Root>/TF_motor' */
  dc_motor_pid_X.TF_motor_CSTATE[0] = 0.0;
  dc_motor_pid_X.TF_motor_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S31>/Filter' */
  dc_motor_pid_X.Filter_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S36>/Integrator' */
  dc_motor_pid_X.Integrator_CSTATE = 0.0;
}

/* Model terminate function */
void dc_motor_pid_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
