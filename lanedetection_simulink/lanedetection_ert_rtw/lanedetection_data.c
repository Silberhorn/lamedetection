/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_data.c
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

#include "lanedetection.h"
#include "lanedetection_private.h"

/* Block parameters (default storage) */
P_lanedetection_T lanedetection_P = {
  /* Mask Parameter: DrawShapes_lineWidth
   * Referenced by: '<Root>/Draw Shapes'
   */
  1,

  /* Mask Parameter: FindLocalMaxima_threshold
   * Referenced by: '<Root>/Find Local Maxima'
   */
  10.0F,

  /* Computed Parameter: Threshold_Value
   * Referenced by: '<Root>/Threshold'
   */
  60U,

  /* Computed Parameter: DrawShapes_RTP_FILLCOLOR
   * Referenced by: '<Root>/Draw Shapes'
   */
  { 0U, 255U, 0U }
};

/* Constant parameters (default storage) */
const ConstP_lanedetection_T lanedetection_ConstP = {
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

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<Root>/Resize2'
   *   '<Root>/Resize3'
   */
  { 0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39,
    41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77,
    79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 101, 103, 105, 107, 109, 111,
    113, 115, 117, 119, 121, 123, 125, 127, 129, 131, 133, 135, 137, 139, 141,
    143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171,
    173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201,
    203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231,
    233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255, 257, 259, 261,
    263, 265, 267, 269, 271, 273, 275, 277, 279, 281, 283, 285, 287, 289, 291,
    293, 295, 297, 299, 301, 303, 305, 307, 309, 311, 313, 315, 317, 0, 2, 4, 6,
    8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44,
    46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82,
    84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116,
    118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146,
    148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176,
    178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206,
    208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236,
    238, 240, 242, 244, 246, 248, 250, 252, 254, 256, 258, 260, 262, 264, 266,
    268, 270, 272, 274, 276, 278, 280, 282, 284, 286, 288, 290, 292, 294, 296,
    298, 300, 302, 304, 306, 308, 310, 312, 314, 316, 318, 1, 3, 5, 7, 9, 11, 13,
    15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51,
    53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89,
    91, 93, 95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121,
    123, 125, 127, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151,
    153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181,
    183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211,
    213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241,
    243, 245, 247, 249, 251, 253, 255, 257, 259, 261, 263, 265, 267, 269, 271,
    273, 275, 277, 279, 281, 283, 285, 287, 289, 291, 293, 295, 297, 299, 301,
    303, 305, 307, 309, 311, 313, 315, 317, 319, 2, 4, 6, 8, 10, 12, 14, 16, 18,
    20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56,
    58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94,
    96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126,
    128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156,
    158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186,
    188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216,
    218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246,
    248, 250, 252, 254, 256, 258, 260, 262, 264, 266, 268, 270, 272, 274, 276,
    278, 280, 282, 284, 286, 288, 290, 292, 294, 296, 298, 300, 302, 304, 306,
    308, 310, 312, 314, 316, 318, 319 },

  /* Computed Parameter: HoughTransform_SINE_TABLE_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  { -1.0F, -0.99984771F, -0.999390841F, -0.99862951F, -0.997564077F,
    -0.99619472F, -0.994521916F, -0.992546141F, -0.990268052F, -0.987688363F,
    -0.98480773F, -0.981627166F, -0.978147626F, -0.974370062F, -0.970295727F,
    -0.965925813F, -0.96126169F, -0.956304729F, -0.95105654F, -0.945518553F,
    -0.939692616F, -0.933580399F, -0.927183867F, -0.920504868F, -0.91354543F,
    -0.906307817F, -0.898794055F, -0.891006529F, -0.882947564F, -0.874619722F,
    -0.866025388F, -0.857167304F, -0.848048091F, -0.838670552F, -0.829037547F,
    -0.819152057F, -0.809017F, -0.798635483F, -0.788010776F, -0.777146F,
    -0.766044438F, -0.754709601F, -0.74314481F, -0.7313537F, -0.719339788F,
    -0.707106769F, -0.694658399F, -0.681998372F, -0.669130623F, -0.656059F,
    -0.642787635F, -0.629320383F, -0.615661502F, -0.601815045F, -0.587785244F,
    -0.57357645F, -0.559192896F, -0.544639051F, -0.529919267F, -0.515038073F,
    -0.5F, -0.484809607F, -0.469471574F, -0.453990489F, -0.438371152F,
    -0.42261827F, -0.406736642F, -0.390731126F, -0.37460658F, -0.35836795F,
    -0.342020154F, -0.325568169F, -0.309017F, -0.29237169F, -0.275637358F,
    -0.258819044F, -0.241921902F, -0.224951059F, -0.207911685F, -0.190809F,
    -0.173648179F, -0.156434461F, -0.139173105F, -0.121869341F, -0.104528464F,
    -0.0871557444F, -0.0697564706F, -0.0523359552F, -0.0348994955F,
    -0.0174524058F, 0.0F },

  /* Computed Parameter: HoughTransform_FIRSTRHO_RTP
   * Referenced by: '<Root>/Hough Transform'
   */
  -335.0F,

  /* Computed Parameter: EdgeDetection_VC_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { 16, 32, 16, -16, -32, -16 },

  /* Computed Parameter: EdgeDetection_HC_RTP
   * Referenced by: '<Root>/Edge Detection'
   */
  { 16, -16, 32, -32, 16, -16 },

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<Root>/Resize2'
   *   '<Root>/Resize3'
   */
  { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 },

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
