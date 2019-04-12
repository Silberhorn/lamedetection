/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_rgb.h
 *
 * Code generated for Simulink model 'lanedetection_rgb'.
 *
 * Model version                  : 1.327
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Apr 11 16:04:23 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_lanedetection_rgb_h_
#define RTW_HEADER_lanedetection_rgb_h_
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef lanedetection_rgb_COMMON_INCLUDES_
# define lanedetection_rgb_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "MW_SDL_video_display.h"
#include "v4l2_capture.h"
#endif                                 /* lanedetection_rgb_COMMON_INCLUDES_ */

#include "lanedetection_rgb_types.h"

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
  uint8_T V4L2VideoCapture_o2[76800];  /* '<Root>/V4L2 Video Capture' */
  uint8_T V4L2VideoCapture_o3[76800];  /* '<Root>/V4L2 Video Capture' */
  uint8_T DrawShapes_o1[22120];        /* '<Root>/Draw Shapes' */
  uint8_T DrawShapes_o2[22120];        /* '<Root>/Draw Shapes' */
  uint8_T DrawShapes_o3[22120];        /* '<Root>/Draw Shapes' */
  uint8_T pln2[22120];
  uint8_T pln3[22120];
  uint8_T ColorSpaceConversion[22120];
  int32_T HoughTransform_o2[180];      /* '<Root>/Hough Transform' */
  int32_T HoughTransform_o3[217];      /* '<Root>/Hough Transform' */
  int32_T HoughLines[8];               /* '<Root>/Hough Lines' */
  uint16_T HoughTransform_o1[39060];   /* '<Root>/Hough Transform' */
  uint8_T V4L2VideoCapture_o1[76800];  /* '<Root>/V4L2 Video Capture' */
  boolean_T Transpose[22120];          /* '<Root>/Transpose' */
  boolean_T EdgeDetection[22120];      /* '<Root>/Edge Detection' */
  int16_T tmpOutRC[4];
  uint32_T Submatrix1[2];              /* '<Root>/Submatrix1' */
  uint32_T Submatrix[2];               /* '<Root>/Submatrix' */
  uint32_T FindLocalMaxima_o1[2];
  int32_T col;
  int32_T firstRow;
  int32_T lastRow;
  int32_T lastRowOut;
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
  int32_T imgCol;
  int32_T imgRow;
} B_lanedetection_rgb_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T DrawShapes_DW_PixCount[316]; /* '<Root>/Draw Shapes' */
  int32_T DrawShapes_DW_Polygon[72];   /* '<Root>/Draw Shapes' */
  int32_T DrawShapes_DW_Points[16];    /* '<Root>/Draw Shapes' */
  codertarget_linux_blocks_SDLV_T obj; /* '<S4>/MATLAB System' */
  int32_T EdgeDetection_VO_DW[2];      /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HO_DW[2];      /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOU_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOD_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOL_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOR_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOU_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOD_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOL_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOR_DW[2];     /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOUL_DW[2];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOLL_DW[2];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOUR_DW[2];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_VOLR_DW[2];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOUL_DW[2];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOLL_DW[2];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOUR_DW[2];    /* '<Root>/Edge Detection' */
  int32_T EdgeDetection_HOLR_DW[2];    /* '<Root>/Edge Detection' */
  uint16_T FindLocalMaxima_TEMP_IN_DWORKS[39060];/* '<Root>/Find Local Maxima' */
  uint8_T ColorSpaceConversion_DWORK1[22120];/* '<Root>/Color Space  Conversion' */
} DW_lanedetection_rgb_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: HoughLines_SINE_TABLE_RTP
   * Referenced by: '<Root>/Hough Lines'
   */
  int16_T HoughLines_SINE_TABLE_RTP[91];

  /* Computed Parameter: HoughTransform_SINE_TABLE_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  int16_T HoughTransform_SINE_TABLE_RTP[91];

  /* Expression: devName
   * Referenced by: '<Root>/V4L2 Video Capture'
   */
  uint8_T V4L2VideoCapture_p1[12];
} ConstP_lanedetection_rgb_T;

/* Parameters (default storage) */
struct P_lanedetection_rgb_T_ {
  int32_T DrawShapes_lineWidth;        /* Mask Parameter: DrawShapes_lineWidth
                                        * Referenced by: '<Root>/Draw Shapes'
                                        */
  uint16_T FindLocalMaxima_threshold;  /* Mask Parameter: FindLocalMaxima_threshold
                                        * Referenced by: '<Root>/Find Local Maxima'
                                        */
  uint8_T DrawShapes_color[3];         /* Mask Parameter: DrawShapes_color
                                        * Referenced by: '<Root>/Draw Shapes'
                                        */
  uint8_T Threshold_Value;             /* Computed Parameter: Threshold_Value
                                        * Referenced by: '<Root>/Threshold'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_lanedetection_rgb_T {
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
extern P_lanedetection_rgb_T lanedetection_rgb_P;

/* Block signals (default storage) */
extern B_lanedetection_rgb_T lanedetection_rgb_B;

/* Block states (default storage) */
extern DW_lanedetection_rgb_T lanedetection_rgb_DW;

/* Constant parameters (default storage) */
extern const ConstP_lanedetection_rgb_T lanedetection_rgb_ConstP;

/* Model entry point functions */
extern void lanedetection_rgb_initialize(void);
extern void lanedetection_rgb_step(void);
extern void lanedetection_rgb_terminate(void);

/* Real-time Model object */
extern RT_MODEL_lanedetection_rgb_T *const lanedetection_rgb_M;

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
 * '<Root>' : 'lanedetection_rgb'
 * '<S1>'   : 'lanedetection_rgb/MATLAB Function2'
 * '<S2>'   : 'lanedetection_rgb/MATLAB Function3'
 * '<S3>'   : 'lanedetection_rgb/MATLAB Function4'
 * '<S4>'   : 'lanedetection_rgb/SDL Video Display'
 */
#endif                                 /* RTW_HEADER_lanedetection_rgb_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
