/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_rgb_data.c
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
  5U,

  /* Mask Parameter: DrawShapes_color
   * Referenced by: '<Root>/Draw Shapes'
   */
  { 255U, 0U, 0U },

  /* Computed Parameter: Threshold_Value
   * Referenced by: '<Root>/Threshold'
   */
  60U
};

/* Constant parameters (default storage) */
const ConstP_lanedetection_rgb_T lanedetection_rgb_ConstP = {
  /* Computed Parameter: HoughLines_SINE_TABLE_RTP
   * Referenced by: '<Root>/Hough Lines'
   */
  { -8192, -8191, -8187, -8181, -8172, -8161, -8147, -8131, -8112, -8091, -8068,
    -8041, -8013, -7982, -7949, -7913, -7875, -7834, -7791, -7746, -7698, -7648,
    -7595, -7541, -7484, -7424, -7363, -7299, -7233, -7165, -7094, -7022, -6947,
    -6870, -6791, -6710, -6627, -6542, -6455, -6366, -6275, -6183, -6088, -5991,
    -5893, -5793, -5691, -5587, -5482, -5374, -5266, -5155, -5043, -4930, -4815,
    -4699, -4581, -4462, -4341, -4219, -4096, -3972, -3846, -3719, -3591, -3462,
    -3332, -3201, -3069, -2936, -2802, -2667, -2531, -2395, -2258, -2120, -1982,
    -1843, -1703, -1563, -1423, -1282, -1140, -998, -856, -714, -571, -429, -286,
    -143, 0 },

  /* Computed Parameter: HoughTransform_SINE_TABLE_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  { -16384, -16382, -16374, -16362, -16344, -16322, -16294, -16262, -16225,
    -16182, -16135, -16083, -16026, -15964, -15897, -15826, -15749, -15668,
    -15582, -15491, -15396, -15296, -15191, -15082, -14968, -14849, -14726,
    -14598, -14466, -14330, -14189, -14044, -13894, -13741, -13583, -13421,
    -13255, -13085, -12911, -12733, -12551, -12365, -12176, -11982, -11786,
    -11585, -11381, -11174, -10963, -10749, -10531, -10311, -10087, -9860, -9630,
    -9397, -9162, -8923, -8682, -8438, -8192, -7943, -7692, -7438, -7182, -6924,
    -6664, -6402, -6138, -5872, -5604, -5334, -5063, -4790, -4516, -4240, -3964,
    -3686, -3406, -3126, -2845, -2563, -2280, -1997, -1713, -1428, -1143, -857,
    -572, -286, 0 },

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
