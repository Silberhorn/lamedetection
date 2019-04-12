/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection.h
 *
 * Code generated for Simulink model 'lanedetection'.
 *
 * Model version                  : 1.197
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Apr 11 09:57:32 2019
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
#include <math.h>
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "MW_SDL_video_display.h"
#include "v4l2_capture.h"
#include "viphough_rt.h"
#endif                                 /* lanedetection_COMMON_INCLUDES_ */

#include "lanedetection_types.h"

/* Shared type includes */
#include "multiword_types.h"

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
  uint8_T DrawShapes_o3[76800];        /* '<Root>/Draw Shapes' */
  uint8_T DrawShapes_o2[76800];        /* '<Root>/Draw Shapes' */
  uint8_T pln2[38400];
  uint8_T pln3[38400];
  uint8_T imgOUT[32000];               /* '<Root>/MATLAB Function1' */
  int32_T HoughLines[8];               /* '<Root>/Hough Lines' */
  uint8_T V4L2VideoCapture_o1[76800];  /* '<Root>/V4L2 Video Capture' */
  uint8_T V4L2VideoCapture_o2[38400];  /* '<Root>/V4L2 Video Capture' */
  uint8_T V4L2VideoCapture_o3[38400];  /* '<Root>/V4L2 Video Capture' */
  uint8_T DrawShapes_o1[76800];        /* '<Root>/Draw Shapes' */
  uint8_T Resize2[38400];              /* '<Root>/Resize2' */
  uint8_T Resize3[38400];              /* '<Root>/Resize3' */
  uint8_T Resize[76800];               /* '<Root>/Resize' */
  uint8_T Resize1[76800];              /* '<Root>/Resize1' */
  boolean_T Transpose[32000];          /* '<Root>/Transpose' */
  boolean_T EdgeDetection[32000];      /* '<Root>/Edge Detection' */
  int32_T tmpOutRC[4];
  uint32_T Submatrix1[2];              /* '<Root>/Submatrix1' */
  uint32_T Submatrix[2];               /* '<Root>/Submatrix' */
  real32_T HoughTransform_o1[120780];  /* '<Root>/Hough Transform' */
  real32_T HoughTransform_o2[180];     /* '<Root>/Hough Transform' */
  real32_T HoughTransform_o3[671];     /* '<Root>/Hough Transform' */
  uint32_T FindLocalMaxima_o1[2];
  real32_T tmpRound;
  real32_T y2;
  int32_T acc3;
  int32_T idxCol1;
  int32_T idxRow2;
  int32_T idxCol2;
  int32_T idxTmp;
  int32_T numUniquePix;
  int32_T loc;
  int32_T loc_m;
  int32_T idxOld;
  int32_T idxNew;
  int32_T numActiveEdge;
  int32_T edgeTmp;
} B_lanedetection_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T Resize3_IntBuffer[76800];    /* '<Root>/Resize3' */
  uint8_T Resize2_IntBuffer[76800];    /* '<Root>/Resize2' */
  uint8_T Resize2_LineBuffer[320];     /* '<Root>/Resize2' */
  int32_T DrawShapes_DW_Polygon[72];   /* '<Root>/Draw Shapes' */
  uint8_T Resize_LineBuffer[160];      /* '<Root>/Resize' */
  int32_T DrawShapes_DW_Points[16];    /* '<Root>/Draw Shapes' */
  codertarget_linux_blocks_SDLV_T obj; /* '<S3>/MATLAB System' */
  real32_T FindLocalMaxima_TEMP_IN_DWORKS[120780];/* '<Root>/Find Local Maxima' */
  int32_T EdgeDetection_VO_DW[6];      /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HO_DW[6];      /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOU_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOD_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOL_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOR_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOU_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOD_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOL_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOR_DW[6];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOUL_DW[6];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOLL_DW[6];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOUR_DW[6];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOLR_DW[6];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOUL_DW[6];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOLL_DW[6];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOUR_DW[6];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOLR_DW[6];    /* '<Root>/Edge Detection' */
} DW_lanedetection_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: EdgeDetection_VRO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  int32_T EdgeDetection_VRO_RTP[6];

  /* Computed Parameter: EdgeDetection_VCO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  int32_T EdgeDetection_VCO_RTP[6];

  /* Computed Parameter: EdgeDetection_HRO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  int32_T EdgeDetection_HRO_RTP[6];

  /* Computed Parameter: EdgeDetection_HCO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  int32_T EdgeDetection_HCO_RTP[6];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<Root>/Resize2'
   *   '<Root>/Resize3'
   */
  int32_T pooled2[640];

  /* Computed Parameter: HoughTransform_SINE_TABLE_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  real32_T HoughTransform_SINE_TABLE_RTP[91];

  /* Computed Parameter: HoughTransform_FIRSTRHO_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  real32_T HoughTransform_FIRSTRHO_RTP;

  /* Computed Parameter: EdgeDetection_VC_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  int8_T EdgeDetection_VC_RTP[6];

  /* Computed Parameter: EdgeDetection_HC_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  int8_T EdgeDetection_HC_RTP[6];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<Root>/Resize2'
   *   '<Root>/Resize3'
   */
  int8_T pooled7[640];

  /* Expression: devName
   * Referenced by: '<Root>/V4L2 Video Capture'
   */
  uint8_T V4L2VideoCapture_p1[12];
} ConstP_lanedetection_T;

/* Parameters (default storage) */
struct P_lanedetection_T_ {
  int32_T DrawShapes_lineWidth;        /* Mask Parameter: DrawShapes_lineWidth
                                        * Referenced by: '<Root>/Draw Shapes'
                                        */
  real32_T FindLocalMaxima_threshold;  /* Mask Parameter: FindLocalMaxima_threshold
                                        * Referenced by: '<Root>/Find Local Maxima'
                                        */
  uint8_T Threshold_Value;             /* Computed Parameter: Threshold_Value
                                        * Referenced by: '<Root>/Threshold'
                                        */
  uint8_T DrawShapes_RTP_FILLCOLOR[3]; /* Computed Parameter: DrawShapes_RTP_FILLCOLOR
                                        * Referenced by: '<Root>/Draw Shapes'
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
