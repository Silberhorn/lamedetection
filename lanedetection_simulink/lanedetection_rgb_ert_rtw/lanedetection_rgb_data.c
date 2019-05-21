/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_rgb_data.c
 *
 * Code generated for Simulink model 'lanedetection_rgb'.
 *
 * Model version                  : 1.508
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Apr 12 17:03:12 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "lanedetection_rgb.h"
#include "lanedetection_rgb_private.h"

/* Block parameters (default storage) */
P_lanedetection_rgb_T lanedetection_rgb_P = {
  /* Mask Parameter: DrawShapes_lineWidth
   * Referenced by: '<Root>/Draw Shapes'
   */
  2,

  /* Mask Parameter: FindLocalMaxima_threshold
   * Referenced by: '<Root>/Find Local Maxima'
   */
  20.0F,

  /* Mask Parameter: DrawShapes_color
   * Referenced by: '<Root>/Draw Shapes'
   */
  { 255U, 0U, 0U },

  /* Computed Parameter: Threshold_Value
   * Referenced by: '<Root>/Threshold'
   */
  40U
};

/* Constant parameters (default storage) */
const ConstP_lanedetection_rgb_T lanedetection_rgb_ConstP = {
  /* Computed Parameter: EdgeDetection_VRO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { -1, -1, -1, 1, 1, 1 },

  /* Computed Parameter: EdgeDetection_VCO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { -1, 0, 1, -1, 0, 1 },

  /* Computed Parameter: EdgeDetection_HRO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { -1, -1, 0, 0, 1, 1 },

  /* Computed Parameter: EdgeDetection_HCO_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { -1, 1, -1, 1, -1, 1 },

  /* Computed Parameter: HoughTransform_SINE_TABLE_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  { -1.0F, -0.999390841F, -0.997564077F, -0.994521916F, -0.990268052F,
    -0.98480773F, -0.978147626F, -0.970295727F, -0.96126169F, -0.95105654F,
    -0.939692616F, -0.927183867F, -0.91354543F, -0.898794055F, -0.882947564F,
    -0.866025388F, -0.848048091F, -0.829037547F, -0.809017F, -0.788010776F,
    -0.766044438F, -0.74314481F, -0.719339788F, -0.694658399F, -0.669130623F,
    -0.642787635F, -0.615661502F, -0.587785244F, -0.559192896F, -0.529919267F,
    -0.5F, -0.469471574F, -0.438371152F, -0.406736642F, -0.37460658F,
    -0.342020154F, -0.309017F, -0.275637358F, -0.241921902F, -0.207911685F,
    -0.173648179F, -0.139173105F, -0.104528464F, -0.0697564706F, -0.0348994955F,
    0.0F },

  /* Computed Parameter: HoughTransform_FIRSTRHO_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  -324.0F,

  /* Computed Parameter: EdgeDetection_VC_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { 16, 32, 16, -16, -32, -16 },

  /* Computed Parameter: EdgeDetection_HC_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { 16, -16, 32, -32, 16, -16 },

  /* Expression: devName
   * Referenced by: '<Root>/V4L2 Video Capture'
   */
  { 47U, 100U, 101U, 118U, 47U, 118U, 105U, 100U, 101U, 111U, 48U, 0U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
