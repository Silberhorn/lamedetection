/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection.h
 *
 * Code generated for Simulink model 'lanedetection'.
 *
 * Model version                  : 1.117
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Mar 28 11:45:22 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_lanedetection_h_
#define RTW_HEADER_lanedetection_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef lanedetection_COMMON_INCLUDES_
# define lanedetection_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "MW_SCI.h"
#include "MW_SDL_video_display.h"
#include "v4l2_capture.h"
#endif                                 /* lanedetection_COMMON_INCLUDES_ */

#include "lanedetection_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T x_data[4800];
  real_T y_data[4800];
  real_T rtb_imgOUT_m[4800];
  real_T dv0[4800];
  int32_T i_data[4800];
  int8_T j_data[4800];
  uint8_T imgOUT[4800];                /* '<Root>/MATLAB Function1' */
  uint8_T pln2[2400];
  uint8_T pln3[2400];
  real_T xx_data[160];
  real_T b_y_data[160];
  int32_T b_data[160];
  int32_T c_data[30];
  uint8_T TxDataLocChar[8];
  real_T Add;                          /* '<Root>/Add' */
  uint8_T V4L2VideoCapture_o1[19200];  /* '<Root>/V4L2 Video Capture' */
  uint8_T V4L2VideoCapture_o2[9600];   /* '<Root>/V4L2 Video Capture' */
  uint8_T V4L2VideoCapture_o3[9600];   /* '<Root>/V4L2 Video Capture' */
  uint8_T Resize1[2400];               /* '<Root>/Resize1' */
  uint8_T Resize2[2400];               /* '<Root>/Resize2' */
  uint8_T imgEdge[4800];               /* '<Root>/MATLAB Function' */
  real_T xCenter;
  real_T yCenter;
  real_T maxval;
  real_T minval;
  int32_T idx;
  int32_T ii;
  int32_T jj;
} B_lanedetection_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T Resize2_IntBuffer[4800];     /* '<Root>/Resize2' */
  uint8_T Resize1_IntBuffer[4800];     /* '<Root>/Resize1' */
  uint8_T Resize1_LineBuffer[160];     /* '<Root>/Resize1' */
  codertarget_linux_blocks_SDLV_T obj; /* '<S3>/MATLAB System' */
  codertarget_raspi_internal_SC_T obj_n;/* '<Root>/Serial Write' */
} DW_lanedetection_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<Root>/Resize1'
   *   '<Root>/Resize2'
   */
  int32_T pooled2[320];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<Root>/Resize1'
   *   '<Root>/Resize2'
   */
  int8_T pooled5[320];

  /* Expression: devName
   * Referenced by: '<Root>/V4L2 Video Capture'
   */
  uint8_T V4L2VideoCapture_p1[12];
} ConstP_lanedetection_T;

/* Parameters (default storage) */
struct P_lanedetection_T_ {
  real_T Gain_Gain;                    /* Expression: 0.005
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 90
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_lanedetection_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_lanedetection_T lanedetection_P;

/* Block signals (default storage) */
extern B_lanedetection_T lanedetection_B;

/* Block states (default storage) */
extern DW_lanedetection_T lanedetection_DW;

/* Constant parameters (default storage) */
extern const ConstP_lanedetection_T lanedetection_ConstP;

/* Model entry point functions */
extern void lanedetection_initialize(void);
extern void lanedetection_step(void);
extern void lanedetection_terminate(void);

/* Real-time Model object */
extern RT_MODEL_lanedetection_T *const lanedetection_M;

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
 * '<Root>' : 'lanedetection'
 * '<S1>'   : 'lanedetection/MATLAB Function'
 * '<S2>'   : 'lanedetection/MATLAB Function1'
 * '<S3>'   : 'lanedetection/SDL Video Display'
 */
#endif                                 /* RTW_HEADER_lanedetection_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
