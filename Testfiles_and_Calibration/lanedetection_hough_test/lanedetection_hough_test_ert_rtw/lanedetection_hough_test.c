/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_hough_test.c
 *
 * Code generated for Simulink model 'lanedetection_hough_test'.
 *
 * Model version                  : 1.28
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Wed Apr 10 14:46:09 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "lanedetection_hough_test.h"
#include "lanedetection_hough_test_private.h"
#include "lanedetection_hough_test_dt.h"

/* Block signals (default storage) */
B_lanedetection_hough_test_T lanedetection_hough_test_B;

/* Block states (default storage) */
DW_lanedetection_hough_test_T lanedetection_hough_test_DW;

/* Real-time model */
RT_MODEL_lanedetection_hough__T lanedetection_hough_test_M_;
RT_MODEL_lanedetection_hough__T *const lanedetection_hough_test_M =
  &lanedetection_hough_test_M_;

/* Forward declaration for local functions */
static void SystemProp_matlabCodegenSetAnyP(codertarget_linux_blocks_SDLV_T *obj,
  boolean_T value);
static void lanedetectio_SystemCore_release(const
  codertarget_linux_blocks_SDLV_T *obj);
static void lanedetection_SystemCore_delete(const
  codertarget_linux_blocks_SDLV_T *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_linux_blocks_SDLV_T *obj);
void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Lo;
  uint32_T in0Hi;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
  absIn1 = in1 < 0 ? ~(uint32_T)in1 + 1U : (uint32_T)in1;
  in0Hi = absIn0 >> 16U;
  in0Lo = absIn0 & 65535U;
  in1Hi = absIn1 >> 16U;
  absIn0 = absIn1 & 65535U;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0U;
  in0Lo = (productLoHi << /*MW:OvBitwiseOk*/ 16U) + /*MW:OvCarryOk*/ absIn0;
  if (in0Lo < absIn0) {
    absIn1 = 1U;
  }

  absIn0 = in0Lo;
  in0Lo += /*MW:OvCarryOk*/ productHiLo << /*MW:OvBitwiseOk*/ 16U;
  if (in0Lo < absIn0) {
    absIn1++;
  }

  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
    absIn1;
  if (!((in0 == 0) || ((in1 == 0) || ((in0 > 0) == (in1 > 0))))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_loSR(int32_T a, int32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  u32_clo = u32_chi << /*MW:OvBitwiseOk*/ (32U - aShift) | u32_clo >> aShift;
  return (int32_T)u32_clo;
}

int32_T div_repeat_s32_floor(int32_T numerator, int32_T denominator, uint32_T
  nRepeatSub)
{
  int32_T quotient;
  uint32_T absNumerator;
  uint32_T absDenominator;
  if (denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;

    /* Divide by zero handler */
  } else {
    absNumerator = numerator < 0 ? ~(uint32_T)numerator + 1U : (uint32_T)
      numerator;
    absDenominator = denominator < 0 ? ~(uint32_T)denominator + 1U : (uint32_T)
      denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -(int32_T)div_nzp_repeat_u32_ceiling(absNumerator,
        absDenominator, nRepeatSub);
    } else {
      quotient = (int32_T)div_nzp_repeat_u32(absNumerator, absDenominator,
        nRepeatSub);
    }
  }

  return quotient;
}

uint32_T div_nzp_repeat_u32_ceiling(uint32_T numerator, uint32_T denominator,
  uint32_T nRepeatSub)
{
  uint32_T quotient;
  uint32_T iRepeatSub;
  boolean_T numeratorExtraBit;
  quotient = numerator / denominator;
  numerator %= denominator;
  for (iRepeatSub = 0U; iRepeatSub < nRepeatSub; iRepeatSub++) {
    numeratorExtraBit = (numerator >= 2147483648U);
    numerator <<= 1U;
    quotient <<= 1U;
    if (numeratorExtraBit || (numerator >= denominator)) {
      quotient++;
      numerator -= denominator;
    }
  }

  if (numerator > 0U) {
    quotient++;
  }

  return quotient;
}

uint32_T div_nzp_repeat_u32(uint32_T numerator, uint32_T denominator, uint32_T
  nRepeatSub)
{
  uint32_T quotient;
  uint32_T iRepeatSub;
  boolean_T numeratorExtraBit;
  quotient = numerator / denominator;
  numerator %= denominator;
  for (iRepeatSub = 0U; iRepeatSub < nRepeatSub; iRepeatSub++) {
    numeratorExtraBit = (numerator >= 2147483648U);
    numerator <<= 1U;
    quotient <<= 1U;
    if (numeratorExtraBit || (numerator >= denominator)) {
      quotient++;
      numerator -= denominator;
    }
  }

  return quotient;
}

int32_T div_s32_floor(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T absNumerator;
  uint32_T absDenominator;
  uint32_T tempAbsQuotient;
  boolean_T quotientNeedsNegation;
  if (denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;

    /* Divide by zero handler */
  } else {
    absNumerator = numerator < 0 ? ~(uint32_T)numerator + 1U : (uint32_T)
      numerator;
    absDenominator = denominator < 0 ? ~(uint32_T)denominator + 1U : (uint32_T)
      denominator;
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }
    }

    quotient = quotientNeedsNegation ? -(int32_T)tempAbsQuotient : (int32_T)
      tempAbsQuotient;
  }

  return quotient;
}

int16_T rt_sqrt_Us32En14_Ys16E_tOJnWsQ0(int32_T u)
{
  int16_T y;
  int16_T tmp01_y;
  int16_T shiftMask;
  int32_T iBit;

  /* Fixed-Point Sqrt Computation by the bisection method. */
  if (u > 0) {
    y = 0;
    shiftMask = 16384;
    for (iBit = 0; iBit < 15; iBit++) {
      tmp01_y = (int16_T)(y | shiftMask);
      if (tmp01_y * tmp01_y <= u) {
        y = tmp01_y;
      }

      shiftMask = (int16_T)((uint32_T)shiftMask >> 1U);
    }
  } else {
    y = 0;
  }

  return y;
}

static void SystemProp_matlabCodegenSetAnyP(codertarget_linux_blocks_SDLV_T *obj,
  boolean_T value)
{
  /* Start for MATLABSystem: '<S2>/MATLAB System' */
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetectio_SystemCore_release(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S2>/MATLAB System' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SDL_videoDisplayTerminate(0, 0);
  }

  /* End of Start for MATLABSystem: '<S2>/MATLAB System' */
}

static void lanedetection_SystemCore_delete(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S2>/MATLAB System' */
  lanedetectio_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S2>/MATLAB System' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAnyP(obj, true);
    lanedetection_SystemCore_delete(obj);
  }

  /* End of Start for MATLABSystem: '<S2>/MATLAB System' */
}

/* Model step function */
void lanedetection_hough_test_step(void)
{
  boolean_T visited2;
  boolean_T isMore;
  boolean_T prevEdgeIsVertical;
  int8_T idxTmpArray[2];
  boolean_T done;
  int32_T q2;
  int32_T q1;
  int32_T p;
  real32_T maxValue;
  int8_T threshSquared;
  int8_T accumFour;
  int8_T accumThree;
  int8_T accumTwo;
  int8_T accumOne;
  int32_T imgRow;
  int32_T imgCol;
  int32_T imgIdx;
  int32_T acc1_idx_5;
  int32_T acc4_idx_0;
  int32_T edgeTmp_tmp;
  int32_T DrawShapes_DW_Polygon_tmp;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_hough_test_ConstP.V4L2VideoCapture_p1,
                        lanedetection_hough_test_B.V4L2VideoCapture_o1,
                        lanedetection_hough_test_B.V4L2VideoCapture_o2,
                        lanedetection_hough_test_B.V4L2VideoCapture_o3);

  /* S-Function (svipcolorconv): '<Root>/Color Space  Conversion' */
  for (imgCol = 0; imgCol < 19200; imgCol++) {
    lanedetection_hough_test_B.acc =
      ((lanedetection_hough_test_B.V4L2VideoCapture_o1[imgCol] * 19595U +
        lanedetection_hough_test_B.V4L2VideoCapture_o2[imgCol] * 38470U) +
       lanedetection_hough_test_B.V4L2VideoCapture_o3[imgCol] * 7471U) + 32768U;
    lanedetection_hough_test_B.acc >>= 16;
    lanedetection_hough_test_B.ColorSpaceConversion[imgCol] = (uint8_T)
      lanedetection_hough_test_B.acc;
  }

  /* End of S-Function (svipcolorconv): '<Root>/Color Space  Conversion' */

  /* S-Function (svipedge): '<Root>/Edge Detection' incorporates:
   *  Constant: '<Root>/Threshold'
   */
  threshSquared = (int8_T)(((int32_T)((uint32_T)
    lanedetection_hough_test_P.Threshold_Value *
    lanedetection_hough_test_P.Threshold_Value) << 8) >> 8);
  for (imgCol = 0; imgCol < 118; imgCol++) {
    for (imgRow = 0; imgRow < 158; imgRow++) {
      imgIdx = ((imgCol + 1) * 160 + imgRow) + 1;
      accumOne = (int8_T)((int8_T)
                          ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
                            + lanedetection_hough_test_DW.EdgeDetection_VO_DW[0]]
                            << 7) >> 8) +
                          ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
                            + lanedetection_hough_test_DW.EdgeDetection_VO_DW[1]]
                            * -128) >> 8));
      accumTwo = (int8_T)((int8_T)
                          ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
                            + lanedetection_hough_test_DW.EdgeDetection_HO_DW[0]]
                            * -128) >> 8) +
                          ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
                            + lanedetection_hough_test_DW.EdgeDetection_HO_DW[1]]
                            << 7) >> 8));
      lanedetection_hough_test_B.EdgeDetection[imgIdx] = ((int8_T)((int8_T)
        (((accumOne * accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) <<
        8) >> 8)) > threshSquared);
    }
  }

  for (imgCol = 0; imgCol < 118; imgCol++) {
    imgRow = (imgCol + 1) * 160;
    imgIdx = (imgCol + 1) * 160 + 159;
    accumOne = (int8_T)((int8_T)
                        ((lanedetection_hough_test_B.ColorSpaceConversion[imgRow
                          + lanedetection_hough_test_DW.EdgeDetection_HOU_DW[0]]
                          * -128) >> 8) +
                        ((lanedetection_hough_test_B.ColorSpaceConversion[imgRow
                          + lanedetection_hough_test_DW.EdgeDetection_HOU_DW[1]]
                          << 7) >> 8));
    accumTwo = (int8_T)((int8_T)
                        ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
                          + lanedetection_hough_test_DW.EdgeDetection_HOD_DW[0]]
                          * -128) >> 8) +
                        ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
                          + lanedetection_hough_test_DW.EdgeDetection_HOD_DW[1]]
                          << 7) >> 8));
    accumThree = (int8_T)((int8_T)
                          ((lanedetection_hough_test_B.ColorSpaceConversion[imgRow
      + lanedetection_hough_test_DW.EdgeDetection_VOU_DW[0]] << 7) >> 8) +
                          ((lanedetection_hough_test_B.ColorSpaceConversion[imgRow
      + lanedetection_hough_test_DW.EdgeDetection_VOU_DW[1]] * -128) >> 8));
    accumFour = (int8_T)((int8_T)
                         ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
      + lanedetection_hough_test_DW.EdgeDetection_VOD_DW[0]] << 7) >> 8) +
                         ((lanedetection_hough_test_B.ColorSpaceConversion[imgIdx
      + lanedetection_hough_test_DW.EdgeDetection_VOD_DW[1]] * -128) >> 8));
    lanedetection_hough_test_B.EdgeDetection[imgRow] = ((int8_T)((int8_T)
      (((accumOne * accumOne) << 8) >> 8) + (int8_T)(((accumThree * accumThree) <<
      8) >> 8)) > threshSquared);
    lanedetection_hough_test_B.EdgeDetection[imgIdx] = ((int8_T)((int8_T)
      (((accumTwo * accumTwo) << 8) >> 8) + (int8_T)(((accumFour * accumFour) <<
      8) >> 8)) > threshSquared);
  }

  for (imgRow = 0; imgRow < 158; imgRow++) {
    accumOne = (int8_T)((int8_T)
                        ((lanedetection_hough_test_B.ColorSpaceConversion
                          [(imgRow +
      lanedetection_hough_test_DW.EdgeDetection_VOL_DW[0]) + 1] << 7) >> 8) +
                        ((lanedetection_hough_test_B.ColorSpaceConversion
                          [(imgRow +
      lanedetection_hough_test_DW.EdgeDetection_VOL_DW[1]) + 1] * -128) >> 8));
    accumTwo = (int8_T)((int8_T)
                        ((lanedetection_hough_test_B.ColorSpaceConversion
                          [(imgRow +
      lanedetection_hough_test_DW.EdgeDetection_VOR_DW[0]) + 19041] << 7) >> 8)
                        + ((lanedetection_hough_test_B.ColorSpaceConversion
      [(imgRow + lanedetection_hough_test_DW.EdgeDetection_VOR_DW[1]) + 19041] *
      -128) >> 8));
    accumThree = (int8_T)((int8_T)
                          ((lanedetection_hough_test_B.ColorSpaceConversion
      [(imgRow + lanedetection_hough_test_DW.EdgeDetection_HOL_DW[0]) + 1] *
      -128) >> 8) + ((lanedetection_hough_test_B.ColorSpaceConversion[(imgRow +
      lanedetection_hough_test_DW.EdgeDetection_HOL_DW[1]) + 1] << 7) >> 8));
    accumFour = (int8_T)((int8_T)
                         ((lanedetection_hough_test_B.ColorSpaceConversion
      [(imgRow + lanedetection_hough_test_DW.EdgeDetection_HOR_DW[0]) + 19041] *
      -128) >> 8) + ((lanedetection_hough_test_B.ColorSpaceConversion[(imgRow +
      lanedetection_hough_test_DW.EdgeDetection_HOR_DW[1]) + 19041] << 7) >> 8));
    lanedetection_hough_test_B.EdgeDetection[imgRow + 1] = ((int8_T)((int8_T)
      (((accumOne * accumOne) << 8) >> 8) + (int8_T)(((accumThree * accumThree) <<
      8) >> 8)) > threshSquared);
    lanedetection_hough_test_B.EdgeDetection[19041 + imgRow] = ((int8_T)((int8_T)
      (((accumTwo * accumTwo) << 8) >> 8) + (int8_T)(((accumFour * accumFour) <<
      8) >> 8)) > threshSquared);
  }

  accumOne = (int8_T)((int8_T)
                      ((lanedetection_hough_test_B.ColorSpaceConversion[lanedetection_hough_test_DW.EdgeDetection_VOUL_DW
                        [0]] << 7) >> 8) +
                      ((lanedetection_hough_test_B.ColorSpaceConversion[lanedetection_hough_test_DW.EdgeDetection_VOUL_DW
                        [1]] * -128) >> 8));
  accumTwo = (int8_T)((int8_T)
                      ((lanedetection_hough_test_B.ColorSpaceConversion[lanedetection_hough_test_DW.EdgeDetection_HOUL_DW
                        [0]] * -128) >> 8) +
                      ((lanedetection_hough_test_B.ColorSpaceConversion[lanedetection_hough_test_DW.EdgeDetection_HOUL_DW
                        [1]] << 7) >> 8));
  accumThree = (int8_T)((int8_T)
                        ((lanedetection_hough_test_B.ColorSpaceConversion[159 +
    lanedetection_hough_test_DW.EdgeDetection_VOLL_DW[0]] << 7) >> 8) +
                        ((lanedetection_hough_test_B.ColorSpaceConversion[159 +
    lanedetection_hough_test_DW.EdgeDetection_VOLL_DW[1]] * -128) >> 8));
  accumFour = (int8_T)((int8_T)
                       ((lanedetection_hough_test_B.ColorSpaceConversion[159 +
    lanedetection_hough_test_DW.EdgeDetection_HOLL_DW[0]] * -128) >> 8) +
                       ((lanedetection_hough_test_B.ColorSpaceConversion[159 +
    lanedetection_hough_test_DW.EdgeDetection_HOLL_DW[1]] << 7) >> 8));
  lanedetection_hough_test_B.EdgeDetection[0] = ((int8_T)((int8_T)(((accumOne *
    accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >> 8)) >
    threshSquared);
  lanedetection_hough_test_B.EdgeDetection[159] = ((int8_T)((int8_T)
    (((accumThree * accumThree) << 8) >> 8) + (int8_T)(((accumFour * accumFour) <<
    8) >> 8)) > threshSquared);
  accumOne = (int8_T)((int8_T)((lanedetection_hough_test_B.ColorSpaceConversion
    [19040 + lanedetection_hough_test_DW.EdgeDetection_VOUR_DW[0]] << 7) >> 8) +
                      ((lanedetection_hough_test_B.ColorSpaceConversion[19040 +
                        lanedetection_hough_test_DW.EdgeDetection_VOUR_DW[1]] *
                        -128) >> 8));
  accumTwo = (int8_T)((int8_T)((lanedetection_hough_test_B.ColorSpaceConversion
    [19040 + lanedetection_hough_test_DW.EdgeDetection_HOUR_DW[0]] * -128) >> 8)
                      + ((lanedetection_hough_test_B.ColorSpaceConversion[19040
    + lanedetection_hough_test_DW.EdgeDetection_HOUR_DW[1]] << 7) >> 8));
  accumThree = (int8_T)((int8_T)
                        ((lanedetection_hough_test_B.ColorSpaceConversion[19199
    + lanedetection_hough_test_DW.EdgeDetection_VOLR_DW[0]] << 7) >> 8) +
                        ((lanedetection_hough_test_B.ColorSpaceConversion[19199
    + lanedetection_hough_test_DW.EdgeDetection_VOLR_DW[1]] * -128) >> 8));
  accumFour = (int8_T)((int8_T)
                       ((lanedetection_hough_test_B.ColorSpaceConversion[19199 +
    lanedetection_hough_test_DW.EdgeDetection_HOLR_DW[0]] * -128) >> 8) +
                       ((lanedetection_hough_test_B.ColorSpaceConversion[19199 +
    lanedetection_hough_test_DW.EdgeDetection_HOLR_DW[1]] << 7) >> 8));
  lanedetection_hough_test_B.EdgeDetection[19040] = ((int8_T)((int8_T)
    (((accumOne * accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >>
    8)) > threshSquared);
  lanedetection_hough_test_B.EdgeDetection[19199] = ((int8_T)((int8_T)
    (((accumThree * accumThree) << 8) >> 8) + (int8_T)(((accumFour * accumFour) <<
    8) >> 8)) > threshSquared);

  /* End of S-Function (svipedge): '<Root>/Edge Detection' */

  /* S-Function (sviphough): '<Root>/Hough Transform' */
  MWVIP_Hough_R(&lanedetection_hough_test_B.EdgeDetection[0],
                &lanedetection_hough_test_B.HoughTransform_o1[0],
                &lanedetection_hough_test_ConstP.HoughTransform_SINE_TABLE_RTP[0],
                &lanedetection_hough_test_ConstP.HoughTransform_FIRSTRHO_RTP,
                160, 120, 399, 91);

  /* Math: '<Root>/Transpose' */
  for (q2 = 0; q2 < 160; q2++) {
    for (imgCol = 0; imgCol < 120; imgCol++) {
      lanedetection_hough_test_B.Transpose[imgCol + 120 * q2] =
        lanedetection_hough_test_B.EdgeDetection[160 * imgCol + q2];
    }
  }

  /* End of Math: '<Root>/Transpose' */

  /* S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */
  imgRow = 0;
  done = false;
  for (imgCol = 0; imgCol < 71820; imgCol++) {
    lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol] =
      lanedetection_hough_test_B.HoughTransform_o1[imgCol];
  }

  lanedetection_hough_test_B.FindLocalMaxima_o1[0] = 0U;
  lanedetection_hough_test_B.FindLocalMaxima_o1[1] = 0U;
  while (!done) {
    imgIdx = 0;
    maxValue = lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[0];
    for (imgCol = 0; imgCol < 71820; imgCol++) {
      if (lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol] >
          maxValue) {
        imgIdx = imgCol;
        maxValue =
          lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol];
      }
    }

    p = imgIdx % 399;
    imgCol = imgIdx / 399;
    if (lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgIdx] >=
        lanedetection_hough_test_P.FindLocalMaxima_threshold) {
      lanedetection_hough_test_B.FindLocalMaxima_o1[imgRow] = (uint32_T)(1 +
        imgCol);
      lanedetection_hough_test_B.FindLocalMaxima_o1[1U + imgRow] = (uint32_T)(1
        + p);
      imgRow++;
      if (imgRow == 1) {
        done = true;
      }

      imgIdx = p - 2;
      if (!(imgIdx > 0)) {
        imgIdx = 0;
      }

      p += 2;
      if (!(p < 398)) {
        p = 398;
      }

      q1 = imgCol - 3;
      q2 = imgCol + 3;
      if (!((q1 < 0) || (q2 > 179))) {
        while (q1 <= q2) {
          lanedetection_hough_test_B.jRowsIn = q1 * 399;
          for (imgCol = imgIdx; imgCol <= p; imgCol++) {
            lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol +
              lanedetection_hough_test_B.jRowsIn] = 0.0F;
          }

          q1++;
        }
      } else {
        if (q1 < 0) {
          lanedetection_hough_test_B.idxRow2 = q1;
          while (lanedetection_hough_test_B.idxRow2 <= q2) {
            if (lanedetection_hough_test_B.idxRow2 < 0) {
              lanedetection_hough_test_B.jRowsIn =
                (lanedetection_hough_test_B.idxRow2 + 180) * 399 + 398;
              for (imgCol = imgIdx; imgCol <= p; imgCol++) {
                lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[lanedetection_hough_test_B.jRowsIn
                  - imgCol] = 0.0F;
              }
            } else {
              lanedetection_hough_test_B.jRowsIn =
                lanedetection_hough_test_B.idxRow2 * 399;
              for (imgCol = imgIdx; imgCol <= p; imgCol++) {
                lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol
                  + lanedetection_hough_test_B.jRowsIn] = 0.0F;
              }
            }

            lanedetection_hough_test_B.idxRow2++;
          }
        }

        if (q2 > 179) {
          lanedetection_hough_test_B.idxRow2 = q1;
          while (lanedetection_hough_test_B.idxRow2 <= q2) {
            if (lanedetection_hough_test_B.idxRow2 > 179) {
              lanedetection_hough_test_B.jRowsIn =
                (lanedetection_hough_test_B.idxRow2 - 180) * 399 + 398;
              for (imgCol = imgIdx; imgCol <= p; imgCol++) {
                lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[lanedetection_hough_test_B.jRowsIn
                  - imgCol] = 0.0F;
              }
            } else {
              lanedetection_hough_test_B.jRowsIn =
                lanedetection_hough_test_B.idxRow2 * 399;
              for (imgCol = imgIdx; imgCol <= p; imgCol++) {
                lanedetection_hough_test_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol
                  + lanedetection_hough_test_B.jRowsIn] = 0.0F;
              }
            }

            lanedetection_hough_test_B.idxRow2++;
          }
        }
      }
    } else {
      done = true;
    }
  }

  /* End of S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix1' */
  lanedetection_hough_test_B.Submatrix1[0] =
    lanedetection_hough_test_B.FindLocalMaxima_o1[0];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_hough_test_B.Submatrix[0] =
    lanedetection_hough_test_B.FindLocalMaxima_o1[0];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix1' */
  lanedetection_hough_test_B.Submatrix1[1] =
    lanedetection_hough_test_B.FindLocalMaxima_o1[1];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_hough_test_B.Submatrix[1] =
    lanedetection_hough_test_B.FindLocalMaxima_o1[1];

  /* S-Function (sviphoughlines): '<Root>/Hough Lines' incorporates:
   *  Selector: '<Root>/Selector'
   *  Selector: '<Root>/Selector1'
   */
  imgCol = 0;
  maxValue = (lanedetection_hough_test_B.HoughTransform_o3[(int32_T)
              lanedetection_hough_test_B.Submatrix[0] - 1] + 1.1920929E-7F) /
    ((real32_T)cos(lanedetection_hough_test_B.HoughTransform_o2[(int32_T)
                   lanedetection_hough_test_B.Submatrix1[0] - 1]) +
     1.1920929E-7F);

  /* part-1: top horizontal axis */
  lanedetection_hough_test_B.tmpRound = (real32_T)floor(maxValue + 0.5F);
  if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
      (lanedetection_hough_test_B.tmpRound <= 119.0F)) {
    lanedetection_hough_test_B.tmpOutRC[0U] = 0;
    if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
      lanedetection_hough_test_B.tmpOutRC[1U] = (int32_T)(real32_T)floor
        (lanedetection_hough_test_B.tmpRound + 0.5F);
    } else {
      lanedetection_hough_test_B.tmpOutRC[1U] = (int32_T)
        (lanedetection_hough_test_B.tmpRound * 0.0F);
    }

    imgCol = 1;
  }

  lanedetection_hough_test_B.y2 = (lanedetection_hough_test_B.HoughTransform_o3
    [(int32_T)lanedetection_hough_test_B.Submatrix[0] - 1] + 1.1920929E-7F) /
    ((real32_T)sin(lanedetection_hough_test_B.HoughTransform_o2[(int32_T)
                   lanedetection_hough_test_B.Submatrix1[0] - 1]) +
     1.1920929E-7F);

  /* part-2: left vertical axis */
  lanedetection_hough_test_B.tmpRound = (real32_T)floor
    (lanedetection_hough_test_B.y2 + 0.5F);
  if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
      (lanedetection_hough_test_B.tmpRound <= 159.0F)) {
    if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
      lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)
        floor(lanedetection_hough_test_B.tmpRound + 0.5F);
    } else {
      lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)
        (lanedetection_hough_test_B.tmpRound * 0.0F);
    }

    lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = 0;
    imgCol++;
  }

  /* part-3: Right vertical axis */
  if (imgCol < 2) {
    lanedetection_hough_test_B.tmpRound = (real32_T)floor((maxValue - 119.0F) *
      (lanedetection_hough_test_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
        (lanedetection_hough_test_B.tmpRound <= 159.0F)) {
      if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
        lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)
          floor(lanedetection_hough_test_B.tmpRound + 0.5F);
      } else {
        lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)
          (lanedetection_hough_test_B.tmpRound * 0.0F);
      }

      lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = 119;
      imgCol++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (imgCol < 2) {
    lanedetection_hough_test_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_hough_test_B.y2 * 159.0F) + 0.5F);
    if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
        (lanedetection_hough_test_B.tmpRound <= 119.0F)) {
      lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = 159;
      if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
        lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (real32_T)floor(lanedetection_hough_test_B.tmpRound + 0.5F);
      } else {
        lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (lanedetection_hough_test_B.tmpRound * 0.0F);
      }

      imgCol++;
    }
  }

  if (imgCol < 2) {
    lanedetection_hough_test_B.tmpOutRC[0U] = -1;
    lanedetection_hough_test_B.tmpOutRC[1U] = -1;
    lanedetection_hough_test_B.tmpOutRC[2U] = -1;
    lanedetection_hough_test_B.tmpOutRC[3U] = -1;
  }

  lanedetection_hough_test_B.HoughLines[0] =
    lanedetection_hough_test_B.tmpOutRC[1] + 1;
  lanedetection_hough_test_B.HoughLines[2] =
    lanedetection_hough_test_B.tmpOutRC[0] + 1;
  lanedetection_hough_test_B.HoughLines[4] =
    lanedetection_hough_test_B.tmpOutRC[3] + 1;
  lanedetection_hough_test_B.HoughLines[6] =
    lanedetection_hough_test_B.tmpOutRC[2] + 1;
  imgCol = 0;
  maxValue = (lanedetection_hough_test_B.HoughTransform_o3[(int32_T)
              lanedetection_hough_test_B.Submatrix[1] - 1] + 1.1920929E-7F) /
    ((real32_T)cos(lanedetection_hough_test_B.HoughTransform_o2[(int32_T)
                   lanedetection_hough_test_B.Submatrix1[1] - 1]) +
     1.1920929E-7F);

  /* part-1: top horizontal axis */
  lanedetection_hough_test_B.tmpRound = (real32_T)floor(maxValue + 0.5F);
  if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
      (lanedetection_hough_test_B.tmpRound <= 119.0F)) {
    lanedetection_hough_test_B.tmpOutRC[0U] = 0;
    if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
      lanedetection_hough_test_B.tmpOutRC[1U] = (int32_T)(real32_T)floor
        (lanedetection_hough_test_B.tmpRound + 0.5F);
    } else {
      lanedetection_hough_test_B.tmpOutRC[1U] = (int32_T)
        (lanedetection_hough_test_B.tmpRound * 0.0F);
    }

    imgCol = 1;
  }

  lanedetection_hough_test_B.y2 = (lanedetection_hough_test_B.HoughTransform_o3
    [(int32_T)lanedetection_hough_test_B.Submatrix[1] - 1] + 1.1920929E-7F) /
    ((real32_T)sin(lanedetection_hough_test_B.HoughTransform_o2[(int32_T)
                   lanedetection_hough_test_B.Submatrix1[1] - 1]) +
     1.1920929E-7F);

  /* part-2: left vertical axis */
  lanedetection_hough_test_B.tmpRound = (real32_T)floor
    (lanedetection_hough_test_B.y2 + 0.5F);
  if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
      (lanedetection_hough_test_B.tmpRound <= 159.0F)) {
    if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
      lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)
        floor(lanedetection_hough_test_B.tmpRound + 0.5F);
    } else {
      lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)
        (lanedetection_hough_test_B.tmpRound * 0.0F);
    }

    lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = 0;
    imgCol++;
  }

  /* part-3: Right vertical axis */
  if (imgCol < 2) {
    lanedetection_hough_test_B.tmpRound = (real32_T)floor((maxValue - 119.0F) *
      (lanedetection_hough_test_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
        (lanedetection_hough_test_B.tmpRound <= 159.0F)) {
      if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
        lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)
          floor(lanedetection_hough_test_B.tmpRound + 0.5F);
      } else {
        lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = (int32_T)
          (lanedetection_hough_test_B.tmpRound * 0.0F);
      }

      lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = 119;
      imgCol++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (imgCol < 2) {
    lanedetection_hough_test_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_hough_test_B.y2 * 159.0F) + 0.5F);
    if ((lanedetection_hough_test_B.tmpRound >= 0.0F) &&
        (lanedetection_hough_test_B.tmpRound <= 119.0F)) {
      lanedetection_hough_test_B.tmpOutRC[imgCol << 1] = 159;
      if (lanedetection_hough_test_B.tmpRound >= 0.5F) {
        lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (real32_T)floor(lanedetection_hough_test_B.tmpRound + 0.5F);
      } else {
        lanedetection_hough_test_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (lanedetection_hough_test_B.tmpRound * 0.0F);
      }

      imgCol++;
    }
  }

  if (imgCol < 2) {
    lanedetection_hough_test_B.tmpOutRC[0U] = -1;
    lanedetection_hough_test_B.tmpOutRC[1U] = -1;
    lanedetection_hough_test_B.tmpOutRC[2U] = -1;
    lanedetection_hough_test_B.tmpOutRC[3U] = -1;
  }

  lanedetection_hough_test_B.HoughLines[1] =
    lanedetection_hough_test_B.tmpOutRC[1] + 1;
  lanedetection_hough_test_B.HoughLines[3] =
    lanedetection_hough_test_B.tmpOutRC[0] + 1;
  lanedetection_hough_test_B.HoughLines[5] =
    lanedetection_hough_test_B.tmpOutRC[3] + 1;
  lanedetection_hough_test_B.HoughLines[7] =
    lanedetection_hough_test_B.tmpOutRC[2] + 1;

  /* End of S-Function (sviphoughlines): '<Root>/Hough Lines' */

  /* S-Function (svipdrawshapes): '<Root>/Draw Shapes' */
  if (lanedetection_hough_test_P.DrawShapes_lineWidth == 1) {
    /* Compute output for unity line width
     */
    /* Copy the image from input to output. */
    memcpy(&lanedetection_hough_test_B.DrawShapes_o1[0],
           &lanedetection_hough_test_B.V4L2VideoCapture_o1[0], 19200U * sizeof
           (uint8_T));
    memcpy(&lanedetection_hough_test_B.DrawShapes_o2[0],
           &lanedetection_hough_test_B.V4L2VideoCapture_o2[0], 19200U * sizeof
           (uint8_T));
    memcpy(&lanedetection_hough_test_B.DrawShapes_o3[0],
           &lanedetection_hough_test_B.V4L2VideoCapture_o3[0], 19200U * sizeof
           (uint8_T));

    /* Update view port. */
    for (imgCol = 0; imgCol < 2; imgCol++) {
      q2 = lanedetection_hough_test_B.HoughLines[imgCol + 2] - 1;
      lanedetection_hough_test_B.jRowsIn =
        lanedetection_hough_test_B.HoughLines[imgCol] - 1;
      acc4_idx_0 = lanedetection_hough_test_B.HoughLines[imgCol + 6] - 1;
      acc1_idx_5 = lanedetection_hough_test_B.HoughLines[4 + imgCol] - 1;
      if ((acc4_idx_0 != q2) || (acc1_idx_5 !=
           lanedetection_hough_test_B.jRowsIn)) {
        isMore = false;

        /* Find the visible portion of a line. */
        prevEdgeIsVertical = false;
        visited2 = false;
        done = false;
        imgRow = q2;
        p = lanedetection_hough_test_B.jRowsIn;
        imgIdx = acc4_idx_0;
        q1 = acc1_idx_5;
        while (!done) {
          lanedetection_hough_test_B.numUniquePix = 0;
          lanedetection_hough_test_B.loc = 0;

          /* Determine viewport violations. */
          if (imgRow < 0) {
            lanedetection_hough_test_B.numUniquePix = 4;
          } else {
            if (imgRow > 159) {
              lanedetection_hough_test_B.numUniquePix = 8;
            }
          }

          if (imgIdx < 0) {
            lanedetection_hough_test_B.loc = 4;
          } else {
            if (imgIdx > 159) {
              lanedetection_hough_test_B.loc = 8;
            }
          }

          if (p < 0) {
            lanedetection_hough_test_B.numUniquePix |= 1U;
          } else {
            if (p > 119) {
              lanedetection_hough_test_B.numUniquePix |= 2U;
            }
          }

          if (q1 < 0) {
            lanedetection_hough_test_B.loc |= 1U;
          } else {
            if (q1 > 119) {
              lanedetection_hough_test_B.loc |= 2U;
            }
          }

          if (!(((uint32_T)lanedetection_hough_test_B.numUniquePix |
                 lanedetection_hough_test_B.loc) != 0U)) {
            /* Line falls completely within bounds. */
            done = true;
            isMore = true;
          } else if (((uint32_T)lanedetection_hough_test_B.numUniquePix &
                      lanedetection_hough_test_B.loc) != 0U) {
            /* Line falls completely out of bounds. */
            done = true;
            isMore = false;
          } else if ((uint32_T)lanedetection_hough_test_B.numUniquePix != 0U) {
            /* Clip 1st point; if it's in-bounds, clip 2nd point. */
            if (prevEdgeIsVertical) {
              imgRow = q2;
              p = lanedetection_hough_test_B.jRowsIn;
            }

            lanedetection_hough_test_B.idxCol1 = imgIdx - imgRow;
            lanedetection_hough_test_B.idxCol2 = q1 - p;
            if ((lanedetection_hough_test_B.idxCol1 > 1073741824) ||
                (lanedetection_hough_test_B.idxCol1 < -1073741824) ||
                ((lanedetection_hough_test_B.idxCol2 > 1073741824) ||
                 (lanedetection_hough_test_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              done = true;
              isMore = false;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_hough_test_B.numUniquePix & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_hough_test_B.numUniquePix = -imgRow *
                lanedetection_hough_test_B.idxCol2;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol1 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol1 < 0))) {
                p += (div_s32_floor(lanedetection_hough_test_B.numUniquePix << 1,
                                    lanedetection_hough_test_B.idxCol1) + 1) >>
                  1;
              } else {
                p -= (div_s32_floor(-lanedetection_hough_test_B.numUniquePix <<
                                    1, lanedetection_hough_test_B.idxCol1) + 1) >>
                  1;
              }

              imgRow = 0;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_hough_test_B.numUniquePix & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_hough_test_B.numUniquePix = (159 - imgRow) *
                lanedetection_hough_test_B.idxCol2;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol1 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol1 < 0))) {
                p += (div_s32_floor(lanedetection_hough_test_B.numUniquePix << 1,
                                    lanedetection_hough_test_B.idxCol1) + 1) >>
                  1;
              } else {
                p -= (div_s32_floor(-lanedetection_hough_test_B.numUniquePix <<
                                    1, lanedetection_hough_test_B.idxCol1) + 1) >>
                  1;
              }

              imgRow = 159;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_hough_test_B.numUniquePix & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_hough_test_B.numUniquePix = -p *
                lanedetection_hough_test_B.idxCol1;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol2 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol2 < 0))) {
                imgRow += (div_s32_floor(lanedetection_hough_test_B.numUniquePix
                            << 1, lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              } else {
                imgRow -= (div_s32_floor
                           (-lanedetection_hough_test_B.numUniquePix << 1,
                            lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              }

              p = 0;
              prevEdgeIsVertical = true;
            } else {
              /* Violated CMax. */
              lanedetection_hough_test_B.numUniquePix = (119 - p) *
                lanedetection_hough_test_B.idxCol1;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol2 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol2 < 0))) {
                imgRow += (div_s32_floor(lanedetection_hough_test_B.numUniquePix
                            << 1, lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              } else {
                imgRow -= (div_s32_floor
                           (-lanedetection_hough_test_B.numUniquePix << 1,
                            lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              }

              p = 119;
              prevEdgeIsVertical = true;
            }
          } else {
            /* Clip the 2nd point. */
            if (visited2) {
              imgIdx = acc4_idx_0;
              q1 = acc1_idx_5;
            }

            lanedetection_hough_test_B.idxCol1 = imgIdx - imgRow;
            lanedetection_hough_test_B.idxCol2 = q1 - p;
            if ((lanedetection_hough_test_B.idxCol1 > 1073741824) ||
                (lanedetection_hough_test_B.idxCol1 < -1073741824) ||
                ((lanedetection_hough_test_B.idxCol2 > 1073741824) ||
                 (lanedetection_hough_test_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              done = true;
              isMore = false;
              visited2 = true;
            } else if ((lanedetection_hough_test_B.loc & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_hough_test_B.numUniquePix = -imgIdx *
                lanedetection_hough_test_B.idxCol2;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol1 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol1 < 0))) {
                q1 += (div_s32_floor(lanedetection_hough_test_B.numUniquePix <<
                                     1, lanedetection_hough_test_B.idxCol1) + 1)
                  >> 1;
              } else {
                q1 -= (div_s32_floor(-lanedetection_hough_test_B.numUniquePix <<
                                     1, lanedetection_hough_test_B.idxCol1) + 1)
                  >> 1;
              }

              imgIdx = 0;
              visited2 = true;
            } else if ((lanedetection_hough_test_B.loc & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_hough_test_B.numUniquePix = (159 - imgIdx) *
                lanedetection_hough_test_B.idxCol2;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol1 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol1 < 0))) {
                q1 += (div_s32_floor(lanedetection_hough_test_B.numUniquePix <<
                                     1, lanedetection_hough_test_B.idxCol1) + 1)
                  >> 1;
              } else {
                q1 -= (div_s32_floor(-lanedetection_hough_test_B.numUniquePix <<
                                     1, lanedetection_hough_test_B.idxCol1) + 1)
                  >> 1;
              }

              imgIdx = 159;
              visited2 = true;
            } else if ((lanedetection_hough_test_B.loc & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_hough_test_B.numUniquePix = -q1 *
                lanedetection_hough_test_B.idxCol1;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol2 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol2 < 0))) {
                imgIdx += (div_s32_floor(lanedetection_hough_test_B.numUniquePix
                            << 1, lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor
                           (-lanedetection_hough_test_B.numUniquePix << 1,
                            lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              }

              q1 = 0;
              visited2 = true;
            } else {
              /* Violated CMax. */
              lanedetection_hough_test_B.numUniquePix = (119 - q1) *
                lanedetection_hough_test_B.idxCol1;
              if ((lanedetection_hough_test_B.numUniquePix > 1073741824) ||
                  (lanedetection_hough_test_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_hough_test_B.numUniquePix >= 0) &&
                          (lanedetection_hough_test_B.idxCol2 >= 0)) ||
                         ((lanedetection_hough_test_B.numUniquePix < 0) &&
                          (lanedetection_hough_test_B.idxCol2 < 0))) {
                imgIdx += (div_s32_floor(lanedetection_hough_test_B.numUniquePix
                            << 1, lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor
                           (-lanedetection_hough_test_B.numUniquePix << 1,
                            lanedetection_hough_test_B.idxCol2) + 1) >> 1;
              }

              q1 = 119;
              visited2 = true;
            }
          }
        }

        if (isMore) {
          /* Draw a line using Bresenham algorithm. */
          /* Initialize the Bresenham algorithm. */
          if (imgIdx >= imgRow) {
            q2 = imgIdx - imgRow;
          } else {
            q2 = imgRow - imgIdx;
          }

          if (q1 >= p) {
            lanedetection_hough_test_B.jRowsIn = q1 - p;
          } else {
            lanedetection_hough_test_B.jRowsIn = p - q1;
          }

          if (q2 > lanedetection_hough_test_B.jRowsIn) {
            q2 = 1;
            lanedetection_hough_test_B.jRowsIn = 160;
          } else {
            q2 = 160;
            lanedetection_hough_test_B.jRowsIn = 1;
            acc4_idx_0 = imgRow;
            imgRow = p;
            p = acc4_idx_0;
            acc4_idx_0 = imgIdx;
            imgIdx = q1;
            q1 = acc4_idx_0;
          }

          if (imgRow > imgIdx) {
            acc4_idx_0 = imgRow;
            imgRow = imgIdx;
            imgIdx = acc4_idx_0;
            acc4_idx_0 = p;
            p = q1;
            q1 = acc4_idx_0;
          }

          acc4_idx_0 = imgIdx - imgRow;
          if (p <= q1) {
            acc1_idx_5 = 1;
            q1 -= p;
          } else {
            acc1_idx_5 = -1;
            q1 = p - q1;
          }

          lanedetection_hough_test_B.idxCol1 = -((acc4_idx_0 + 1) >> 1);
          p = imgRow * q2 + p * lanedetection_hough_test_B.jRowsIn;
          lanedetection_hough_test_B.jRowsIn = acc1_idx_5 *
            lanedetection_hough_test_B.jRowsIn + q2;
          done = (imgRow <= imgIdx);
          while (done) {
            lanedetection_hough_test_B.DrawShapes_o1[p] =
              lanedetection_hough_test_P.DrawShapes_color[0];
            lanedetection_hough_test_B.DrawShapes_o2[p] =
              lanedetection_hough_test_P.DrawShapes_color[1];
            lanedetection_hough_test_B.DrawShapes_o3[p] =
              lanedetection_hough_test_P.DrawShapes_color[2];

            /* Compute the next location using Bresenham algorithm. */
            /* Move to the next pixel location. */
            lanedetection_hough_test_B.idxCol1 += q1;
            if (lanedetection_hough_test_B.idxCol1 >= 0) {
              lanedetection_hough_test_B.idxCol1 -= acc4_idx_0;
              p += lanedetection_hough_test_B.jRowsIn;
            } else {
              p += q2;
            }

            imgRow++;
            done = (imgRow <= imgIdx);
          }
        }
      }
    }
  } else {
    /* Compute output for non-unity line width
     */
    /* Copy the image from input to output. */
    memcpy(&lanedetection_hough_test_B.DrawShapes_o1[0],
           &lanedetection_hough_test_B.V4L2VideoCapture_o1[0], 19200U * sizeof
           (uint8_T));
    memcpy(&lanedetection_hough_test_B.DrawShapes_o2[0],
           &lanedetection_hough_test_B.V4L2VideoCapture_o2[0], 19200U * sizeof
           (uint8_T));
    memcpy(&lanedetection_hough_test_B.DrawShapes_o3[0],
           &lanedetection_hough_test_B.V4L2VideoCapture_o3[0], 19200U * sizeof
           (uint8_T));

    /* Update view port. */
    /* ProcessStep-start-1
     */
    if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
      /* convertLinePts2PolygonPts
       */
      imgCol = lanedetection_hough_test_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      imgRow = lanedetection_hough_test_B.HoughLines[2] -
        lanedetection_hough_test_B.HoughLines[6];
      imgIdx = lanedetection_hough_test_B.HoughLines[0] -
        lanedetection_hough_test_B.HoughLines[4];
      if (imgIdx == 0) {
        q1 = 0;
        p = 1;
        q2 = ((lanedetection_hough_test_B.HoughLines[0] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[0] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[2] - 1) << 14;
      } else if (imgRow == 0) {
        p = 2;
        q1 = 0;
        q2 = ((lanedetection_hough_test_B.HoughLines[2] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[2] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[0] - 1) << 14;
      } else {
        p = 0;
        q1 = div_repeat_s32_floor(imgRow << 14, imgIdx << 14, 14U);
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_hough_test_B.HoughLines[0] - 1) << 14, q1, 14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgRow * imgRow +
          imgIdx * imgIdx) << 14) << 7, 14U), 14U);
        q2 = lanedetection_hough_test_B.jRowsIn + acc4_idx_0;
        lanedetection_hough_test_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor
          ((lanedetection_hough_test_B.HoughLines[0] - 1) << 14, q1, 14U) +
          ((lanedetection_hough_test_B.HoughLines[2] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (p == 1) {
        lanedetection_hough_test_DW.DrawShapes_DW_Points[0] = ((q2 & 8192U) !=
          0U) + (q2 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[2] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[12] =
          ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_hough_test_B.jRowsIn >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[14] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
      } else {
        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[0] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[2] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[0] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[2] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        }

        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[12] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[14] =
            ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_hough_test_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_hough_test_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1,
            14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[12] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) +
            lanedetection_hough_test_B.jRowsIn;
          lanedetection_hough_test_DW.DrawShapes_DW_Points[14] = ((q2 & 8192U)
            != 0U) + (q2 >> 14);
        }
      }

      /* findPointOfIntersectionNormal-2
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      /* getLineParams-2
       */
      /* getLineParams-main fcn
       */
      if (imgIdx == 0) {
        q1 = 0;
        p = 1;
        q2 = ((lanedetection_hough_test_B.HoughLines[0] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[0] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[6] - 1) << 14;
      } else if (imgRow == 0) {
        p = 2;
        q1 = 0;
        q2 = ((lanedetection_hough_test_B.HoughLines[2] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[2] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[4] - 1) << 14;
      } else {
        p = 0;
        q1 = div_repeat_s32_floor(imgRow << 14, imgIdx << 14, 14U);
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_hough_test_B.HoughLines[0] - 1) << 14, q1, 14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgRow * imgRow +
          imgIdx * imgIdx) << 14) << 7, 14U), 14U);
        q2 = lanedetection_hough_test_B.jRowsIn + acc4_idx_0;
        lanedetection_hough_test_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor
          ((lanedetection_hough_test_B.HoughLines[4] - 1) << 14, q1, 14U) +
          ((lanedetection_hough_test_B.HoughLines[6] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (p == 1) {
        lanedetection_hough_test_DW.DrawShapes_DW_Points[4] = ((q2 & 8192U) !=
          0U) + (q2 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[6] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[8] =
          ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_hough_test_B.jRowsIn >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[10] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
      } else {
        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[4] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[6] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[4] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[6] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        }

        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[8] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[10] =
            ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_hough_test_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_hough_test_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1,
            14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[8] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) +
            lanedetection_hough_test_B.jRowsIn;
          lanedetection_hough_test_DW.DrawShapes_DW_Points[10] = ((q2 & 8192U)
            != 0U) + (q2 >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      imgCol = lanedetection_hough_test_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      imgRow = lanedetection_hough_test_B.HoughLines[3] -
        lanedetection_hough_test_B.HoughLines[7];
      imgIdx = lanedetection_hough_test_B.HoughLines[1] -
        lanedetection_hough_test_B.HoughLines[5];
      if (imgIdx == 0) {
        q1 = 0;
        p = 1;
        q2 = ((lanedetection_hough_test_B.HoughLines[1] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[1] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[3] - 1) << 14;
      } else if (imgRow == 0) {
        p = 2;
        q1 = 0;
        q2 = ((lanedetection_hough_test_B.HoughLines[3] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[3] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[1] - 1) << 14;
      } else {
        p = 0;
        q1 = div_repeat_s32_floor(imgRow << 14, imgIdx << 14, 14U);
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_hough_test_B.HoughLines[1] - 1) << 14, q1, 14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgRow * imgRow +
          imgIdx * imgIdx) << 14) << 7, 14U), 14U);
        q2 = lanedetection_hough_test_B.jRowsIn + acc4_idx_0;
        lanedetection_hough_test_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor
          ((lanedetection_hough_test_B.HoughLines[1] - 1) << 14, q1, 14U) +
          ((lanedetection_hough_test_B.HoughLines[3] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (p == 1) {
        lanedetection_hough_test_DW.DrawShapes_DW_Points[1] = ((q2 & 8192U) !=
          0U) + (q2 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[3] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[13] =
          ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_hough_test_B.jRowsIn >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[15] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
      } else {
        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[1] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[3] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[1] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[3] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        }

        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[13] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[15] =
            ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_hough_test_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_hough_test_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1,
            14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[13] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) +
            lanedetection_hough_test_B.jRowsIn;
          lanedetection_hough_test_DW.DrawShapes_DW_Points[15] = ((q2 & 8192U)
            != 0U) + (q2 >> 14);
        }
      }

      /* findPointOfIntersectionNormal-2
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      /* getLineParams-2
       */
      /* getLineParams-main fcn
       */
      if (imgIdx == 0) {
        q1 = 0;
        p = 1;
        q2 = ((lanedetection_hough_test_B.HoughLines[1] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[1] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[7] - 1) << 14;
      } else if (imgRow == 0) {
        p = 2;
        q1 = 0;
        q2 = ((lanedetection_hough_test_B.HoughLines[3] - imgCol) - 1) << 14;
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[3] + imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_hough_test_B.HoughLines[5] - 1) << 14;
      } else {
        p = 0;
        q1 = div_repeat_s32_floor(imgRow << 14, imgIdx << 14, 14U);
        lanedetection_hough_test_B.jRowsIn =
          ((lanedetection_hough_test_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_hough_test_B.HoughLines[1] - 1) << 14, q1, 14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgRow * imgRow +
          imgIdx * imgIdx) << 14) << 7, 14U), 14U);
        q2 = lanedetection_hough_test_B.jRowsIn + acc4_idx_0;
        lanedetection_hough_test_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor
          ((lanedetection_hough_test_B.HoughLines[5] - 1) << 14, q1, 14U) +
          ((lanedetection_hough_test_B.HoughLines[7] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (p == 1) {
        lanedetection_hough_test_DW.DrawShapes_DW_Points[5] = ((q2 & 8192U) !=
          0U) + (q2 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[7] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[9] =
          ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_hough_test_B.jRowsIn >> 14);
        lanedetection_hough_test_DW.DrawShapes_DW_Points[11] = ((acc4_idx_0 &
          8192U) != 0U) + (acc4_idx_0 >> 14);
      } else {
        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[5] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[7] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[5] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[7] = ((q2 & 8192U) !=
            0U) + (q2 >> 14);
        }

        if (p == 2) {
          lanedetection_hough_test_DW.DrawShapes_DW_Points[9] = ((acc4_idx_0 &
            8192U) != 0U) + (acc4_idx_0 >> 14);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[11] =
            ((lanedetection_hough_test_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_hough_test_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_hough_test_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1,
            14U) + 16384, 14U);
          lanedetection_hough_test_DW.DrawShapes_DW_Points[9] = ((acc1_idx_5 &
            8192U) != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) +
            lanedetection_hough_test_B.jRowsIn;
          lanedetection_hough_test_DW.DrawShapes_DW_Points[11] = ((q2 & 8192U)
            != 0U) + (q2 >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
    }

    /* ProcessStep-after poly points-1
     */
    imgRow = 2;

    /* just before call for cgpolygon
     */
    if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
      /* just before call for cgpolygon-2
       */
      imgRow = 4;
    }

    imgIdx = imgRow << 1;

    /* Reset scanline states. */
    p = 0;
    q1 = 0;
    idxTmpArray[0U] = (int8_T)(imgRow - 1);
    isMore = true;
    while (isMore) {
      /* Initialize the scanline. */
      /* Convert polygon vertices to boundaries. */
      q2 = 0;
      lanedetection_hough_test_B.jRowsIn = p;
      acc4_idx_0 = p;

      /* start for loop
       */
      acc1_idx_5 = (((idxTmpArray[0] << 1) + 1) << 1) + q1;
      lanedetection_hough_test_B.idxCol1 = (idxTmpArray[0] << 2) + q1;
      lanedetection_hough_test_B.idxTmp = idxTmpArray[0];
      lanedetection_hough_test_B.idxCol2 = ((idxTmpArray[0] - 1) << 2) + q1;
      lanedetection_hough_test_B.numUniquePix = imgRow;
      if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_hough_test_B.loc =
          lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol1];

        /* getLoc-1
         */
        imgCol =
          lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_hough_test_B.loc =
          lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol1];

        /* getLoc-2
         */
        imgCol =
          lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol2];
      }

      while ((lanedetection_hough_test_B.idxCol2 >= 0) &&
             (lanedetection_hough_test_B.loc - 1 == imgCol - 1)) {
        lanedetection_hough_test_B.idxTmp--;
        lanedetection_hough_test_B.idxCol2 = ((lanedetection_hough_test_B.idxTmp
          - 1) << 2) + q1;
        lanedetection_hough_test_B.numUniquePix--;
        if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          imgCol =
            lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol2];
        } else {
          /* getLoc-2
           */
          imgCol =
            lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol2];
        }
      }

      if (lanedetection_hough_test_B.idxCol2 < 0) {
        lanedetection_hough_test_B.idxCol2 = 0;
      }

      if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_hough_test_B.loc =
          lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol1];

        /* getLoc-1
         */
        lanedetection_hough_test_B.loc_m =
          lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_hough_test_B.loc =
          lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol1];

        /* getLoc-2
         */
        lanedetection_hough_test_B.loc_m =
          lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol2];
      }

      done = (lanedetection_hough_test_B.loc_m - 1 >
              lanedetection_hough_test_B.loc - 1);
      lanedetection_hough_test_B.idxRow2 = 2 + q1;
      lanedetection_hough_test_B.idxCol2 = q1;
      prevEdgeIsVertical = false;
      if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_hough_test_B.loc =
          lanedetection_hough_test_DW.DrawShapes_DW_Points[q1];

        /* getLoc-1
         */
        lanedetection_hough_test_B.loc_m =
          lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol1];
      } else {
        /* getLoc-2
         */
        lanedetection_hough_test_B.loc =
          lanedetection_hough_test_B.HoughLines[q1];

        /* getLoc-2
         */
        lanedetection_hough_test_B.loc_m =
          lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol1];
      }

      for (imgCol = 0; imgCol < lanedetection_hough_test_B.numUniquePix; imgCol
           ++) {
        if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          lanedetection_hough_test_B.idxTmp =
            lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol2];

          /* getLoc-1
           */
          lanedetection_hough_test_B.numActiveEdge =
            lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol1];
        } else {
          /* getLoc-2
           */
          lanedetection_hough_test_B.idxTmp =
            lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol2];

          /* getLoc-2
           */
          lanedetection_hough_test_B.numActiveEdge =
            lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol1];
        }

        if (lanedetection_hough_test_B.numActiveEdge - 1 !=
            lanedetection_hough_test_B.idxTmp - 1) {
          if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_hough_test_B.idxTmp =
              lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_hough_test_B.numActiveEdge =
              lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol1];
          } else {
            /* getLoc-2
             */
            lanedetection_hough_test_B.idxTmp =
              lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_hough_test_B.numActiveEdge =
              lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol1];
          }

          if (lanedetection_hough_test_B.numActiveEdge - 1 <
              lanedetection_hough_test_B.idxTmp - 1) {
            isMore = false;
          } else {
            isMore = true;
            lanedetection_hough_test_B.idxTmp = acc1_idx_5;
            acc1_idx_5 = lanedetection_hough_test_B.idxRow2;
            lanedetection_hough_test_B.idxRow2 =
              lanedetection_hough_test_B.idxTmp;
            lanedetection_hough_test_B.idxTmp =
              lanedetection_hough_test_B.idxCol1;
            lanedetection_hough_test_B.idxCol1 =
              lanedetection_hough_test_B.idxCol2;
            lanedetection_hough_test_B.idxCol2 =
              lanedetection_hough_test_B.idxTmp;
          }

          if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_hough_test_B.idxTmp =
              lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_hough_test_B.numActiveEdge =
              lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxRow2];

            /* getLoc-1
             */
            lanedetection_hough_test_B.idxNew =
              lanedetection_hough_test_DW.DrawShapes_DW_Points[lanedetection_hough_test_B.idxCol1];

            /* getLoc-1
             */
            lanedetection_hough_test_B.idxOld =
              lanedetection_hough_test_DW.DrawShapes_DW_Points[acc1_idx_5];
          } else {
            /* getLoc-2
             */
            lanedetection_hough_test_B.idxTmp =
              lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_hough_test_B.numActiveEdge =
              lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxRow2];

            /* getLoc-2
             */
            lanedetection_hough_test_B.idxNew =
              lanedetection_hough_test_B.HoughLines[lanedetection_hough_test_B.idxCol1];

            /* getLoc-2
             */
            lanedetection_hough_test_B.idxOld =
              lanedetection_hough_test_B.HoughLines[acc1_idx_5];
          }

          /* Initialize a Bresenham line. */
          edgeTmp_tmp = lanedetection_hough_test_B.idxTmp -
            lanedetection_hough_test_B.idxNew;
          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0] = 0;
          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 1] =
            lanedetection_hough_test_B.idxOld - 1;
          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 2] =
            lanedetection_hough_test_B.idxNew - 1;
          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 3] =
            lanedetection_hough_test_B.idxTmp - 1;
          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6] = 0;
          if (lanedetection_hough_test_B.numActiveEdge - 1 >=
              lanedetection_hough_test_B.idxOld - 1) {
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] =
              lanedetection_hough_test_B.numActiveEdge -
              lanedetection_hough_test_B.idxOld;
          } else {
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] =
              lanedetection_hough_test_B.idxOld -
              lanedetection_hough_test_B.numActiveEdge;
          }

          while (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                 8] >= 0) {
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6]++;
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] -=
              edgeTmp_tmp;
          }

          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5] =
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6] -
            1;
          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 7] =
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] +
            edgeTmp_tmp;
          lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 4] =
            edgeTmp_tmp -
            (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 7] <<
             1);
          if (lanedetection_hough_test_B.idxOld - 1 >
              lanedetection_hough_test_B.numActiveEdge - 1) {
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5] =
              -lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5];
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6] =
              -lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6];
          }

          if ((!done) && (!isMore)) {
            /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 2]++;
            if ((lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0] <<
                 1) >
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 4])
            {
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0] +=
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8];
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 1] +=
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6];
            } else {
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0] +=
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 7];
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 1] +=
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5];
            }
          } else {
            if (done && isMore) {
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 3]
                --;
            }
          }

          done = isMore;
          if (!prevEdgeIsVertical) {
            /* Merge two Bresenham lines. */
            prevEdgeIsVertical = false;
            if ((lanedetection_hough_test_B.jRowsIn != acc4_idx_0) &&
                ((lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                  + 5] ==
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                  5]) &&
                 (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                  + 6] ==
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                  6]) &&
                 (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                  + 7] ==
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                  7]) &&
                 (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                  + 8] ==
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                  8]))) {
              if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                  + 3] + 1 ==
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                  2]) {
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                  + 3] =
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                  3];
                prevEdgeIsVertical = true;
              } else {
                if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0
                    + 3] + 1 ==
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                    + 2]) {
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                    + 1] =
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0
                    + 1];
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                    + 2] =
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0
                    + 2];
                  prevEdgeIsVertical = true;
                }
              }
            }

            if (!prevEdgeIsVertical) {
              lanedetection_hough_test_B.jRowsIn = acc4_idx_0;
              q2++;
            }
          } else {
            lanedetection_hough_test_B.jRowsIn = acc4_idx_0;
            q2++;
          }

          acc4_idx_0 = lanedetection_hough_test_B.jRowsIn + 9;
          if (!isMore) {
            acc1_idx_5 = lanedetection_hough_test_B.idxRow2;
            lanedetection_hough_test_B.idxCol1 =
              lanedetection_hough_test_B.idxCol2;
          }

          lanedetection_hough_test_B.idxRow2 = acc1_idx_5 + 4;
          lanedetection_hough_test_B.idxCol2 =
            lanedetection_hough_test_B.idxCol1 + 4;
          prevEdgeIsVertical = false;
        } else {
          prevEdgeIsVertical = true;
          acc1_idx_5 = lanedetection_hough_test_B.idxRow2;
          lanedetection_hough_test_B.idxCol1 =
            lanedetection_hough_test_B.idxCol2;
          lanedetection_hough_test_B.idxRow2 += 4;
          lanedetection_hough_test_B.idxCol2 += 4;
        }
      }

      if (!(lanedetection_hough_test_B.loc_m - 1 ==
            lanedetection_hough_test_B.loc - 1)) {
        /* Merge two Bresenham lines. */
        done = false;
        if ((p != lanedetection_hough_test_B.jRowsIn) &&
            ((lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 5] ==
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
              + 5]) && (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 6]
                        ==
                        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                        + 6]) &&
             (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 7] ==
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
              + 7]) && (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 8]
                        ==
                        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                        + 8]))) {
          if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 3] + 1 ==
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
              + 2]) {
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 3] =
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
              + 3];
            done = true;
          } else {
            if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                + 3] + 1 == lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p
                + 2]) {
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 1] =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                + 1];
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 2] =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.jRowsIn
                + 2];
              done = true;
            }
          }
        }

        if (done) {
          q2--;
          acc4_idx_0 -= 9;
        }
      }

      /* Set all other edges to invalid. */
      for (imgCol = q2; imgCol < imgRow; imgCol++) {
        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 2] = 1;
        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 3] = 0;
        acc4_idx_0 += 9;
      }

      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_hough_test_B.idxNew = p;
        lanedetection_hough_test_B.idxOld = p + 9;
        isMore = false;
        for (imgCol = 1; imgCol < q2; imgCol++) {
          if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxNew
              + 2] >
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
              + 2]) {
            isMore = true;
            for (lanedetection_hough_test_B.idxRow2 = 0;
                 lanedetection_hough_test_B.idxRow2 < 9;
                 lanedetection_hough_test_B.idxRow2++) {
              edgeTmp_tmp = lanedetection_hough_test_B.idxNew +
                lanedetection_hough_test_B.idxRow2;
              lanedetection_hough_test_B.edgeTmp =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_hough_test_B.idxOld +
                lanedetection_hough_test_B.idxRow2;
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                = lanedetection_hough_test_B.edgeTmp;
            }
          }

          lanedetection_hough_test_B.idxNew = lanedetection_hough_test_B.idxOld;
          lanedetection_hough_test_B.idxOld += 9;
        }
      }

      /* Find out the last column of the polygon. */
      acc1_idx_5 = p + 3;
      lanedetection_hough_test_B.jRowsIn =
        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 3];
      for (imgCol = 1; imgCol < q2; imgCol++) {
        acc1_idx_5 += 9;
        if (lanedetection_hough_test_B.jRowsIn <
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc1_idx_5]) {
          lanedetection_hough_test_B.jRowsIn =
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc1_idx_5];
        }
      }

      acc4_idx_0 = lanedetection_hough_test_B.jRowsIn;
      if (lanedetection_hough_test_B.jRowsIn > 119) {
        acc4_idx_0 = 119;
      }

      /* Find out the first column of the polygon. */
      acc1_idx_5 = p + 2;
      lanedetection_hough_test_B.jRowsIn =
        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[p + 2];
      for (imgCol = 1; imgCol < q2; imgCol++) {
        acc1_idx_5 += 9;
        if (lanedetection_hough_test_B.jRowsIn >
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc1_idx_5]) {
          lanedetection_hough_test_B.jRowsIn =
            lanedetection_hough_test_DW.DrawShapes_DW_Polygon[acc1_idx_5];
        }
      }

      if (lanedetection_hough_test_B.jRowsIn < 0) {
        lanedetection_hough_test_B.jRowsIn = 0;
      }

      /* Move to the next column and find out boundaries of the polygon at this column. */
      lanedetection_hough_test_B.idxNew = p;
      lanedetection_hough_test_B.idxOld = p;
      acc1_idx_5 = p;
      lanedetection_hough_test_B.idxCol1 = 0;
      lanedetection_hough_test_B.numActiveEdge = 0;
      for (imgCol = 0; imgCol < q2; imgCol++) {
        /* Find out the valid boundaries and bring them to the latest column. */
        if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
            + 3] >= lanedetection_hough_test_B.jRowsIn) {
          if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
              + 2] <= lanedetection_hough_test_B.jRowsIn) {
            while
                (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                 + 2] < lanedetection_hough_test_B.jRowsIn) {
              /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                + 2]++;
              if ((lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld]
                   << 1) >
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 4]) {
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld]
                  +=
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 8];
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 1] +=
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 6];
              } else {
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld]
                  +=
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 7];
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 1] +=
                  lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 5];
              }
            }

            acc1_idx_5 += 9;
            lanedetection_hough_test_B.numActiveEdge++;
          }

          if (lanedetection_hough_test_B.idxOld !=
              lanedetection_hough_test_B.idxNew) {
            for (lanedetection_hough_test_B.idxRow2 = 0;
                 lanedetection_hough_test_B.idxRow2 < 9;
                 lanedetection_hough_test_B.idxRow2++) {
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxNew
                + lanedetection_hough_test_B.idxRow2] =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                + lanedetection_hough_test_B.idxRow2];
            }
          }

          lanedetection_hough_test_B.idxNew += 9;
          lanedetection_hough_test_B.idxCol1++;
        }

        lanedetection_hough_test_B.idxOld += 9;
      }

      /* Sort the boundaries of the polygon according to row values. */
      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_hough_test_B.idxNew = p;
        lanedetection_hough_test_B.idxOld = p + 9;
        isMore = false;
        for (imgCol = 1; imgCol < lanedetection_hough_test_B.numActiveEdge;
             imgCol++) {
          if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxNew
              + 1] >
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
              + 1]) {
            isMore = true;
            for (lanedetection_hough_test_B.idxRow2 = 0;
                 lanedetection_hough_test_B.idxRow2 < 9;
                 lanedetection_hough_test_B.idxRow2++) {
              edgeTmp_tmp = lanedetection_hough_test_B.idxNew +
                lanedetection_hough_test_B.idxRow2;
              lanedetection_hough_test_B.edgeTmp =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_hough_test_B.idxOld +
                lanedetection_hough_test_B.idxRow2;
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_hough_test_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                = lanedetection_hough_test_B.edgeTmp;
            }
          }

          lanedetection_hough_test_B.idxNew = lanedetection_hough_test_B.idxOld;
          lanedetection_hough_test_B.idxOld += 9;
        }
      }

      q2 = p;
      lanedetection_hough_test_B.idxCol2 = lanedetection_hough_test_B.jRowsIn +
        1;
      lanedetection_hough_test_B.numUniquePix = 0;
      lanedetection_hough_test_B.idxRow2 = 0;
      lanedetection_hough_test_B.numActiveEdge = -1;
      isMore = (0 <= acc4_idx_0);
      while (isMore) {
        /* Get a string of pixels */
        prevEdgeIsVertical = false;
        done = (lanedetection_hough_test_B.idxRow2 != 0);
        lanedetection_hough_test_B.idxTmp =
          lanedetection_hough_test_B.numUniquePix;
        if ((lanedetection_hough_test_B.numUniquePix >=
             lanedetection_hough_test_B.jRowsIn) &&
            (lanedetection_hough_test_B.numUniquePix <= acc4_idx_0)) {
          if (q2 < acc1_idx_5) {
            imgCol = lanedetection_hough_test_DW.DrawShapes_DW_Polygon[q2 + 1];
            q2 += 9;
            if ((imgCol == lanedetection_hough_test_B.numActiveEdge) && (q2 <
                 acc1_idx_5)) {
              lanedetection_hough_test_B.loc =
                lanedetection_hough_test_DW.DrawShapes_DW_Polygon[q2 + 1];
              isMore = (q2 < acc1_idx_5);
              while (isMore && (imgCol == lanedetection_hough_test_B.loc)) {
                prevEdgeIsVertical = true;
                imgCol = lanedetection_hough_test_DW.DrawShapes_DW_Polygon[q2 +
                  1];
                q2 += 9;
                isMore = (q2 < acc1_idx_5);
                if (isMore) {
                  lanedetection_hough_test_B.loc =
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[q2 + 1];
                }
              }

              if (!isMore) {
                prevEdgeIsVertical = false;
              }
            }

            if (lanedetection_hough_test_B.idxRow2 != 0) {
              lanedetection_hough_test_B.loc =
                lanedetection_hough_test_B.numActiveEdge;
              if (imgCol <= 159) {
                lanedetection_hough_test_B.loc_m = imgCol;
                lanedetection_hough_test_B.numActiveEdge = imgCol;
              } else {
                lanedetection_hough_test_B.loc_m = 159;
                lanedetection_hough_test_B.numActiveEdge = 159;
              }
            } else {
              lanedetection_hough_test_B.loc =
                lanedetection_hough_test_B.numActiveEdge + 1;
              if ((imgCol > 0) && (imgCol <= 159)) {
                lanedetection_hough_test_B.loc_m = imgCol - 1;
                lanedetection_hough_test_B.numActiveEdge = imgCol;
              } else if (imgCol <= 0) {
                lanedetection_hough_test_B.loc_m = -1;
                lanedetection_hough_test_B.numActiveEdge = 0;
              } else {
                lanedetection_hough_test_B.loc_m = 159;
                lanedetection_hough_test_B.numActiveEdge = 160;
              }
            }

            if (!prevEdgeIsVertical) {
              lanedetection_hough_test_B.idxRow2 =
                !(lanedetection_hough_test_B.idxRow2 != 0);
            }
          } else {
            /* Reset states and move to the next column. */
            done = false;
            lanedetection_hough_test_B.loc =
              lanedetection_hough_test_B.numActiveEdge + 1;
            lanedetection_hough_test_B.loc_m = 159;

            /* Move to the next column and find out boundaries of the polygon at this column. */
            lanedetection_hough_test_B.idxNew = p;
            lanedetection_hough_test_B.idxOld = p;
            acc1_idx_5 = p;
            q2 = 0;
            lanedetection_hough_test_B.numActiveEdge = 0;
            for (imgCol = 0; imgCol < lanedetection_hough_test_B.idxCol1; imgCol
                 ++) {
              /* Find out the valid boundaries and bring them to the latest column. */
              if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                  + 3] >= lanedetection_hough_test_B.idxCol2) {
                if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                    + 2] <= lanedetection_hough_test_B.idxCol2) {
                  while
                      (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                       + 2] < lanedetection_hough_test_B.idxCol2) {
                    /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                      + 2]++;
                    if ((lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld]
                         << 1) >
                        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                        + 4]) {
                      lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld]
                        +=
                        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                        + 8];
                      lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                        + 1] +=
                        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                        + 6];
                    } else {
                      lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld]
                        +=
                        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                        + 7];
                      lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                        + 1] +=
                        lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                        + 5];
                    }
                  }

                  acc1_idx_5 += 9;
                  lanedetection_hough_test_B.numActiveEdge++;
                }

                if (lanedetection_hough_test_B.idxOld !=
                    lanedetection_hough_test_B.idxNew) {
                  for (lanedetection_hough_test_B.idxRow2 = 0;
                       lanedetection_hough_test_B.idxRow2 < 9;
                       lanedetection_hough_test_B.idxRow2++) {
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxNew
                      + lanedetection_hough_test_B.idxRow2] =
                      lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                      + lanedetection_hough_test_B.idxRow2];
                  }
                }

                lanedetection_hough_test_B.idxNew += 9;
                q2++;
              }

              lanedetection_hough_test_B.idxOld += 9;
            }

            lanedetection_hough_test_B.idxCol1 = q2;

            /* Sort the boundaries of the polygon according to row values. */
            /* Sort the boundaries of the polygon. */
            isMore = true;
            while (isMore) {
              lanedetection_hough_test_B.idxNew = p;
              lanedetection_hough_test_B.idxOld = p + 9;
              isMore = false;
              for (imgCol = 1; imgCol < lanedetection_hough_test_B.numActiveEdge;
                   imgCol++) {
                if (lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxNew
                    + 1] >
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[lanedetection_hough_test_B.idxOld
                    + 1]) {
                  isMore = true;
                  for (lanedetection_hough_test_B.idxRow2 = 0;
                       lanedetection_hough_test_B.idxRow2 < 9;
                       lanedetection_hough_test_B.idxRow2++) {
                    edgeTmp_tmp = lanedetection_hough_test_B.idxNew +
                      lanedetection_hough_test_B.idxRow2;
                    lanedetection_hough_test_B.edgeTmp =
                      lanedetection_hough_test_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
                    DrawShapes_DW_Polygon_tmp =
                      lanedetection_hough_test_B.idxOld +
                      lanedetection_hough_test_B.idxRow2;
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[edgeTmp_tmp]
                      =
                      lanedetection_hough_test_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
                    lanedetection_hough_test_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                      = lanedetection_hough_test_B.edgeTmp;
                  }
                }

                lanedetection_hough_test_B.idxNew =
                  lanedetection_hough_test_B.idxOld;
                lanedetection_hough_test_B.idxOld += 9;
              }
            }

            q2 = p;
            lanedetection_hough_test_B.idxCol2++;
            lanedetection_hough_test_B.idxRow2 = 0;
            lanedetection_hough_test_B.numActiveEdge = -1;
            lanedetection_hough_test_B.numUniquePix++;
          }
        } else {
          lanedetection_hough_test_B.loc = 0;
          lanedetection_hough_test_B.loc_m = 159;
          lanedetection_hough_test_B.numUniquePix++;
        }

        if (lanedetection_hough_test_B.loc < 0) {
          lanedetection_hough_test_B.loc = 0;
        }

        if (lanedetection_hough_test_B.loc_m < lanedetection_hough_test_B.loc) {
          lanedetection_hough_test_B.loc_m = lanedetection_hough_test_B.loc - 1;
        }

        if (done) {
          lanedetection_hough_test_B.idxTmp = lanedetection_hough_test_B.idxTmp *
            160 + lanedetection_hough_test_B.loc;
          lanedetection_hough_test_B.idxNew = 1;
          if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
            lanedetection_hough_test_B.idxNew = 0;
          }

          lanedetection_hough_test_B.idxOld = lanedetection_hough_test_B.idxTmp;
          for (imgCol = lanedetection_hough_test_B.loc; imgCol <=
               lanedetection_hough_test_B.loc_m; imgCol++) {
            if (lanedetection_hough_test_B.idxNew != 0) {
              lanedetection_hough_test_B.DrawShapes_o1[lanedetection_hough_test_B.idxOld]
                = (uint8_T)(((int32_T)((uint32_T)
                lanedetection_hough_test_B.DrawShapes_o1[lanedetection_hough_test_B.idxOld]
                * lanedetection_hough_test_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_hough_test_B.DrawShapes_o1[lanedetection_hough_test_B.idxOld]
                = (uint8_T)((uint32_T)
                            lanedetection_hough_test_B.DrawShapes_o1[lanedetection_hough_test_B.idxOld]
                            + lanedetection_hough_test_P.DrawShapes_color[0]);
            } else {
              lanedetection_hough_test_B.DrawShapes_o1[lanedetection_hough_test_B.idxOld]
                = lanedetection_hough_test_P.DrawShapes_color[0];
            }

            lanedetection_hough_test_B.idxOld++;
          }

          lanedetection_hough_test_B.idxNew = 1;
          if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
            lanedetection_hough_test_B.idxNew = 0;
          }

          lanedetection_hough_test_B.idxOld = lanedetection_hough_test_B.idxTmp;
          for (imgCol = lanedetection_hough_test_B.loc; imgCol <=
               lanedetection_hough_test_B.loc_m; imgCol++) {
            if (lanedetection_hough_test_B.idxNew != 0) {
              lanedetection_hough_test_B.DrawShapes_o2[lanedetection_hough_test_B.idxOld]
                = (uint8_T)(((int32_T)((uint32_T)
                lanedetection_hough_test_B.DrawShapes_o2[lanedetection_hough_test_B.idxOld]
                * lanedetection_hough_test_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_hough_test_B.DrawShapes_o2[lanedetection_hough_test_B.idxOld]
                = (uint8_T)((uint32_T)
                            lanedetection_hough_test_B.DrawShapes_o2[lanedetection_hough_test_B.idxOld]
                            + lanedetection_hough_test_P.DrawShapes_color[1]);
            } else {
              lanedetection_hough_test_B.DrawShapes_o2[lanedetection_hough_test_B.idxOld]
                = lanedetection_hough_test_P.DrawShapes_color[1];
            }

            lanedetection_hough_test_B.idxOld++;
          }

          lanedetection_hough_test_B.idxNew = 1;
          if (lanedetection_hough_test_P.DrawShapes_lineWidth > 1) {
            lanedetection_hough_test_B.idxNew = 0;
          }

          while (lanedetection_hough_test_B.loc <=
                 lanedetection_hough_test_B.loc_m) {
            if (lanedetection_hough_test_B.idxNew != 0) {
              lanedetection_hough_test_B.DrawShapes_o3[lanedetection_hough_test_B.idxTmp]
                = (uint8_T)(((int32_T)((uint32_T)
                lanedetection_hough_test_B.DrawShapes_o3[lanedetection_hough_test_B.idxTmp]
                * lanedetection_hough_test_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_hough_test_B.DrawShapes_o3[lanedetection_hough_test_B.idxTmp]
                = (uint8_T)((uint32_T)
                            lanedetection_hough_test_B.DrawShapes_o3[lanedetection_hough_test_B.idxTmp]
                            + lanedetection_hough_test_P.DrawShapes_color[2]);
            } else {
              lanedetection_hough_test_B.DrawShapes_o3[lanedetection_hough_test_B.idxTmp]
                = lanedetection_hough_test_P.DrawShapes_color[2];
            }

            lanedetection_hough_test_B.idxTmp++;
            lanedetection_hough_test_B.loc++;
          }
        }

        isMore = (lanedetection_hough_test_B.numUniquePix <= acc4_idx_0);
      }

      /* Move to the next polygon. */
      p += imgRow * 9;
      if (q1 >= div_s32_floor(imgIdx, imgRow) - 1) {
        q1 = 0;
      } else {
        q1++;
      }

      isMore = (p < (imgRow << 1) * 9);
    }
  }

  /* End of S-Function (svipdrawshapes): '<Root>/Draw Shapes' */
  /* Start for MATLABSystem: '<S2>/MATLAB System' */
  memcpy(&lanedetection_hough_test_B.ColorSpaceConversion[0],
         &lanedetection_hough_test_B.DrawShapes_o1[0], 19200U * sizeof(uint8_T));
  memcpy(&lanedetection_hough_test_B.pln2[0],
         &lanedetection_hough_test_B.DrawShapes_o2[0], 19200U * sizeof(uint8_T));
  memcpy(&lanedetection_hough_test_B.pln3[0],
         &lanedetection_hough_test_B.DrawShapes_o3[0], 19200U * sizeof(uint8_T));
  MW_SDL_videoDisplayOutput(lanedetection_hough_test_B.ColorSpaceConversion,
    lanedetection_hough_test_B.pln2, lanedetection_hough_test_B.pln3);

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Selector: '<Root>/Selector'
   */
  lanedetection_hough_test_B.y[0] =
    lanedetection_hough_test_B.HoughTransform_o2[(int32_T)
    lanedetection_hough_test_B.Submatrix1[0] - 1];
  lanedetection_hough_test_B.y[1] =
    lanedetection_hough_test_B.HoughTransform_o2[(int32_T)
    lanedetection_hough_test_B.Submatrix1[1] - 1];

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.033333333333333333s, 0.0s] */
    rtExtModeUpload(0, lanedetection_hough_test_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.033333333333333333s, 0.0s] */
    if ((rtmGetTFinal(lanedetection_hough_test_M)!=-1) &&
        !((rtmGetTFinal(lanedetection_hough_test_M)-
           lanedetection_hough_test_M->Timing.taskTime0) >
          lanedetection_hough_test_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(lanedetection_hough_test_M, "Simulation finished");
    }

    if (rtmGetStopRequested(lanedetection_hough_test_M)) {
      rtmSetErrorStatus(lanedetection_hough_test_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  lanedetection_hough_test_M->Timing.taskTime0 =
    (++lanedetection_hough_test_M->Timing.clockTick0) *
    lanedetection_hough_test_M->Timing.stepSize0;
}

/* Model initialize function */
void lanedetection_hough_test_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)lanedetection_hough_test_M, 0,
                sizeof(RT_MODEL_lanedetection_hough__T));
  rtmSetTFinal(lanedetection_hough_test_M, -1);
  lanedetection_hough_test_M->Timing.stepSize0 = 0.033333333333333333;

  /* External mode info */
  lanedetection_hough_test_M->Sizes.checksums[0] = (2678345690U);
  lanedetection_hough_test_M->Sizes.checksums[1] = (3169495138U);
  lanedetection_hough_test_M->Sizes.checksums[2] = (618768905U);
  lanedetection_hough_test_M->Sizes.checksums[3] = (3299884535U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    lanedetection_hough_test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lanedetection_hough_test_M->extModeInfo,
      &lanedetection_hough_test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lanedetection_hough_test_M->extModeInfo,
                        lanedetection_hough_test_M->Sizes.checksums);
    rteiSetTPtr(lanedetection_hough_test_M->extModeInfo, rtmGetTPtr
                (lanedetection_hough_test_M));
  }

  /* block I/O */
  (void) memset(((void *) &lanedetection_hough_test_B), 0,
                sizeof(B_lanedetection_hough_test_T));

  {
    lanedetection_hough_test_B.HoughTransform_o2[0] = -1.57079637F;
    lanedetection_hough_test_B.HoughTransform_o2[1] = -1.55334306F;
    lanedetection_hough_test_B.HoughTransform_o2[2] = -1.53588974F;
    lanedetection_hough_test_B.HoughTransform_o2[3] = -1.51843643F;
    lanedetection_hough_test_B.HoughTransform_o2[4] = -1.50098312F;
    lanedetection_hough_test_B.HoughTransform_o2[5] = -1.48352981F;
    lanedetection_hough_test_B.HoughTransform_o2[6] = -1.46607661F;
    lanedetection_hough_test_B.HoughTransform_o2[7] = -1.4486233F;
    lanedetection_hough_test_B.HoughTransform_o2[8] = -1.43117F;
    lanedetection_hough_test_B.HoughTransform_o2[9] = -1.41371667F;
    lanedetection_hough_test_B.HoughTransform_o2[10] = -1.39626336F;
    lanedetection_hough_test_B.HoughTransform_o2[11] = -1.37881017F;
    lanedetection_hough_test_B.HoughTransform_o2[12] = -1.36135685F;
    lanedetection_hough_test_B.HoughTransform_o2[13] = -1.34390354F;
    lanedetection_hough_test_B.HoughTransform_o2[14] = -1.32645023F;
    lanedetection_hough_test_B.HoughTransform_o2[15] = -1.30899692F;
    lanedetection_hough_test_B.HoughTransform_o2[16] = -1.2915436F;
    lanedetection_hough_test_B.HoughTransform_o2[17] = -1.27409041F;
    lanedetection_hough_test_B.HoughTransform_o2[18] = -1.2566371F;
    lanedetection_hough_test_B.HoughTransform_o2[19] = -1.23918378F;
    lanedetection_hough_test_B.HoughTransform_o2[20] = -1.22173047F;
    lanedetection_hough_test_B.HoughTransform_o2[21] = -1.20427716F;
    lanedetection_hough_test_B.HoughTransform_o2[22] = -1.18682384F;
    lanedetection_hough_test_B.HoughTransform_o2[23] = -1.16937065F;
    lanedetection_hough_test_B.HoughTransform_o2[24] = -1.15191734F;
    lanedetection_hough_test_B.HoughTransform_o2[25] = -1.13446403F;
    lanedetection_hough_test_B.HoughTransform_o2[26] = -1.11701071F;
    lanedetection_hough_test_B.HoughTransform_o2[27] = -1.0995574F;
    lanedetection_hough_test_B.HoughTransform_o2[28] = -1.08210409F;
    lanedetection_hough_test_B.HoughTransform_o2[29] = -1.06465089F;
    lanedetection_hough_test_B.HoughTransform_o2[30] = -1.04719758F;
    lanedetection_hough_test_B.HoughTransform_o2[31] = -1.02974427F;
    lanedetection_hough_test_B.HoughTransform_o2[32] = -1.01229095F;
    lanedetection_hough_test_B.HoughTransform_o2[33] = -0.994837701F;
    lanedetection_hough_test_B.HoughTransform_o2[34] = -0.977384388F;
    lanedetection_hough_test_B.HoughTransform_o2[35] = -0.959931076F;
    lanedetection_hough_test_B.HoughTransform_o2[36] = -0.942477822F;
    lanedetection_hough_test_B.HoughTransform_o2[37] = -0.925024509F;
    lanedetection_hough_test_B.HoughTransform_o2[38] = -0.907571197F;
    lanedetection_hough_test_B.HoughTransform_o2[39] = -0.890117943F;
    lanedetection_hough_test_B.HoughTransform_o2[40] = -0.87266463F;
    lanedetection_hough_test_B.HoughTransform_o2[41] = -0.855211318F;
    lanedetection_hough_test_B.HoughTransform_o2[42] = -0.837758064F;
    lanedetection_hough_test_B.HoughTransform_o2[43] = -0.820304751F;
    lanedetection_hough_test_B.HoughTransform_o2[44] = -0.802851439F;
    lanedetection_hough_test_B.HoughTransform_o2[45] = -0.785398185F;
    lanedetection_hough_test_B.HoughTransform_o2[46] = -0.767944872F;
    lanedetection_hough_test_B.HoughTransform_o2[47] = -0.75049156F;
    lanedetection_hough_test_B.HoughTransform_o2[48] = -0.733038306F;
    lanedetection_hough_test_B.HoughTransform_o2[49] = -0.715585F;
    lanedetection_hough_test_B.HoughTransform_o2[50] = -0.69813168F;
    lanedetection_hough_test_B.HoughTransform_o2[51] = -0.680678427F;
    lanedetection_hough_test_B.HoughTransform_o2[52] = -0.663225114F;
    lanedetection_hough_test_B.HoughTransform_o2[53] = -0.645771801F;
    lanedetection_hough_test_B.HoughTransform_o2[54] = -0.628318548F;
    lanedetection_hough_test_B.HoughTransform_o2[55] = -0.610865235F;
    lanedetection_hough_test_B.HoughTransform_o2[56] = -0.593411922F;
    lanedetection_hough_test_B.HoughTransform_o2[57] = -0.575958669F;
    lanedetection_hough_test_B.HoughTransform_o2[58] = -0.558505356F;
    lanedetection_hough_test_B.HoughTransform_o2[59] = -0.541052043F;
    lanedetection_hough_test_B.HoughTransform_o2[60] = -0.52359879F;
    lanedetection_hough_test_B.HoughTransform_o2[61] = -0.506145477F;
    lanedetection_hough_test_B.HoughTransform_o2[62] = -0.488692194F;
    lanedetection_hough_test_B.HoughTransform_o2[63] = -0.471238911F;
    lanedetection_hough_test_B.HoughTransform_o2[64] = -0.453785598F;
    lanedetection_hough_test_B.HoughTransform_o2[65] = -0.436332315F;
    lanedetection_hough_test_B.HoughTransform_o2[66] = -0.418879032F;
    lanedetection_hough_test_B.HoughTransform_o2[67] = -0.401425719F;
    lanedetection_hough_test_B.HoughTransform_o2[68] = -0.383972436F;
    lanedetection_hough_test_B.HoughTransform_o2[69] = -0.366519153F;
    lanedetection_hough_test_B.HoughTransform_o2[70] = -0.34906584F;
    lanedetection_hough_test_B.HoughTransform_o2[71] = -0.331612557F;
    lanedetection_hough_test_B.HoughTransform_o2[72] = -0.314159274F;
    lanedetection_hough_test_B.HoughTransform_o2[73] = -0.296705961F;
    lanedetection_hough_test_B.HoughTransform_o2[74] = -0.279252678F;
    lanedetection_hough_test_B.HoughTransform_o2[75] = -0.261799395F;
    lanedetection_hough_test_B.HoughTransform_o2[76] = -0.244346097F;
    lanedetection_hough_test_B.HoughTransform_o2[77] = -0.226892799F;
    lanedetection_hough_test_B.HoughTransform_o2[78] = -0.209439516F;
    lanedetection_hough_test_B.HoughTransform_o2[79] = -0.191986218F;
    lanedetection_hough_test_B.HoughTransform_o2[80] = -0.17453292F;
    lanedetection_hough_test_B.HoughTransform_o2[81] = -0.157079637F;
    lanedetection_hough_test_B.HoughTransform_o2[82] = -0.139626339F;
    lanedetection_hough_test_B.HoughTransform_o2[83] = -0.122173049F;
    lanedetection_hough_test_B.HoughTransform_o2[84] = -0.104719758F;
    lanedetection_hough_test_B.HoughTransform_o2[85] = -0.0872664601F;
    lanedetection_hough_test_B.HoughTransform_o2[86] = -0.0698131695F;
    lanedetection_hough_test_B.HoughTransform_o2[87] = -0.052359879F;
    lanedetection_hough_test_B.HoughTransform_o2[88] = -0.0349065848F;
    lanedetection_hough_test_B.HoughTransform_o2[89] = -0.0174532924F;
    lanedetection_hough_test_B.HoughTransform_o2[90] = 0.0F;
    lanedetection_hough_test_B.HoughTransform_o2[91] = 0.0174532924F;
    lanedetection_hough_test_B.HoughTransform_o2[92] = 0.0349065848F;
    lanedetection_hough_test_B.HoughTransform_o2[93] = 0.052359879F;
    lanedetection_hough_test_B.HoughTransform_o2[94] = 0.0698131695F;
    lanedetection_hough_test_B.HoughTransform_o2[95] = 0.0872664601F;
    lanedetection_hough_test_B.HoughTransform_o2[96] = 0.104719758F;
    lanedetection_hough_test_B.HoughTransform_o2[97] = 0.122173049F;
    lanedetection_hough_test_B.HoughTransform_o2[98] = 0.139626339F;
    lanedetection_hough_test_B.HoughTransform_o2[99] = 0.157079637F;
    lanedetection_hough_test_B.HoughTransform_o2[100] = 0.17453292F;
    lanedetection_hough_test_B.HoughTransform_o2[101] = 0.191986218F;
    lanedetection_hough_test_B.HoughTransform_o2[102] = 0.209439516F;
    lanedetection_hough_test_B.HoughTransform_o2[103] = 0.226892799F;
    lanedetection_hough_test_B.HoughTransform_o2[104] = 0.244346097F;
    lanedetection_hough_test_B.HoughTransform_o2[105] = 0.261799395F;
    lanedetection_hough_test_B.HoughTransform_o2[106] = 0.279252678F;
    lanedetection_hough_test_B.HoughTransform_o2[107] = 0.296705961F;
    lanedetection_hough_test_B.HoughTransform_o2[108] = 0.314159274F;
    lanedetection_hough_test_B.HoughTransform_o2[109] = 0.331612557F;
    lanedetection_hough_test_B.HoughTransform_o2[110] = 0.34906584F;
    lanedetection_hough_test_B.HoughTransform_o2[111] = 0.366519153F;
    lanedetection_hough_test_B.HoughTransform_o2[112] = 0.383972436F;
    lanedetection_hough_test_B.HoughTransform_o2[113] = 0.401425719F;
    lanedetection_hough_test_B.HoughTransform_o2[114] = 0.418879032F;
    lanedetection_hough_test_B.HoughTransform_o2[115] = 0.436332315F;
    lanedetection_hough_test_B.HoughTransform_o2[116] = 0.453785598F;
    lanedetection_hough_test_B.HoughTransform_o2[117] = 0.471238911F;
    lanedetection_hough_test_B.HoughTransform_o2[118] = 0.488692194F;
    lanedetection_hough_test_B.HoughTransform_o2[119] = 0.506145477F;
    lanedetection_hough_test_B.HoughTransform_o2[120] = 0.52359879F;
    lanedetection_hough_test_B.HoughTransform_o2[121] = 0.541052043F;
    lanedetection_hough_test_B.HoughTransform_o2[122] = 0.558505356F;
    lanedetection_hough_test_B.HoughTransform_o2[123] = 0.575958669F;
    lanedetection_hough_test_B.HoughTransform_o2[124] = 0.593411922F;
    lanedetection_hough_test_B.HoughTransform_o2[125] = 0.610865235F;
    lanedetection_hough_test_B.HoughTransform_o2[126] = 0.628318548F;
    lanedetection_hough_test_B.HoughTransform_o2[127] = 0.645771801F;
    lanedetection_hough_test_B.HoughTransform_o2[128] = 0.663225114F;
    lanedetection_hough_test_B.HoughTransform_o2[129] = 0.680678427F;
    lanedetection_hough_test_B.HoughTransform_o2[130] = 0.69813168F;
    lanedetection_hough_test_B.HoughTransform_o2[131] = 0.715585F;
    lanedetection_hough_test_B.HoughTransform_o2[132] = 0.733038306F;
    lanedetection_hough_test_B.HoughTransform_o2[133] = 0.75049156F;
    lanedetection_hough_test_B.HoughTransform_o2[134] = 0.767944872F;
    lanedetection_hough_test_B.HoughTransform_o2[135] = 0.785398185F;
    lanedetection_hough_test_B.HoughTransform_o2[136] = 0.802851439F;
    lanedetection_hough_test_B.HoughTransform_o2[137] = 0.820304751F;
    lanedetection_hough_test_B.HoughTransform_o2[138] = 0.837758064F;
    lanedetection_hough_test_B.HoughTransform_o2[139] = 0.855211318F;
    lanedetection_hough_test_B.HoughTransform_o2[140] = 0.87266463F;
    lanedetection_hough_test_B.HoughTransform_o2[141] = 0.890117943F;
    lanedetection_hough_test_B.HoughTransform_o2[142] = 0.907571197F;
    lanedetection_hough_test_B.HoughTransform_o2[143] = 0.925024509F;
    lanedetection_hough_test_B.HoughTransform_o2[144] = 0.942477822F;
    lanedetection_hough_test_B.HoughTransform_o2[145] = 0.959931076F;
    lanedetection_hough_test_B.HoughTransform_o2[146] = 0.977384388F;
    lanedetection_hough_test_B.HoughTransform_o2[147] = 0.994837701F;
    lanedetection_hough_test_B.HoughTransform_o2[148] = 1.01229095F;
    lanedetection_hough_test_B.HoughTransform_o2[149] = 1.02974427F;
    lanedetection_hough_test_B.HoughTransform_o2[150] = 1.04719758F;
    lanedetection_hough_test_B.HoughTransform_o2[151] = 1.06465089F;
    lanedetection_hough_test_B.HoughTransform_o2[152] = 1.08210409F;
    lanedetection_hough_test_B.HoughTransform_o2[153] = 1.0995574F;
    lanedetection_hough_test_B.HoughTransform_o2[154] = 1.11701071F;
    lanedetection_hough_test_B.HoughTransform_o2[155] = 1.13446403F;
    lanedetection_hough_test_B.HoughTransform_o2[156] = 1.15191734F;
    lanedetection_hough_test_B.HoughTransform_o2[157] = 1.16937065F;
    lanedetection_hough_test_B.HoughTransform_o2[158] = 1.18682384F;
    lanedetection_hough_test_B.HoughTransform_o2[159] = 1.20427716F;
    lanedetection_hough_test_B.HoughTransform_o2[160] = 1.22173047F;
    lanedetection_hough_test_B.HoughTransform_o2[161] = 1.23918378F;
    lanedetection_hough_test_B.HoughTransform_o2[162] = 1.2566371F;
    lanedetection_hough_test_B.HoughTransform_o2[163] = 1.27409041F;
    lanedetection_hough_test_B.HoughTransform_o2[164] = 1.2915436F;
    lanedetection_hough_test_B.HoughTransform_o2[165] = 1.30899692F;
    lanedetection_hough_test_B.HoughTransform_o2[166] = 1.32645023F;
    lanedetection_hough_test_B.HoughTransform_o2[167] = 1.34390354F;
    lanedetection_hough_test_B.HoughTransform_o2[168] = 1.36135685F;
    lanedetection_hough_test_B.HoughTransform_o2[169] = 1.37881017F;
    lanedetection_hough_test_B.HoughTransform_o2[170] = 1.39626336F;
    lanedetection_hough_test_B.HoughTransform_o2[171] = 1.41371667F;
    lanedetection_hough_test_B.HoughTransform_o2[172] = 1.43117F;
    lanedetection_hough_test_B.HoughTransform_o2[173] = 1.4486233F;
    lanedetection_hough_test_B.HoughTransform_o2[174] = 1.46607661F;
    lanedetection_hough_test_B.HoughTransform_o2[175] = 1.48352981F;
    lanedetection_hough_test_B.HoughTransform_o2[176] = 1.50098312F;
    lanedetection_hough_test_B.HoughTransform_o2[177] = 1.51843643F;
    lanedetection_hough_test_B.HoughTransform_o2[178] = 1.53588974F;
    lanedetection_hough_test_B.HoughTransform_o2[179] = 1.55334306F;
    lanedetection_hough_test_B.HoughTransform_o3[0] = -199.0F;
    lanedetection_hough_test_B.HoughTransform_o3[1] = -198.0F;
    lanedetection_hough_test_B.HoughTransform_o3[2] = -197.0F;
    lanedetection_hough_test_B.HoughTransform_o3[3] = -196.0F;
    lanedetection_hough_test_B.HoughTransform_o3[4] = -195.0F;
    lanedetection_hough_test_B.HoughTransform_o3[5] = -194.0F;
    lanedetection_hough_test_B.HoughTransform_o3[6] = -193.0F;
    lanedetection_hough_test_B.HoughTransform_o3[7] = -192.0F;
    lanedetection_hough_test_B.HoughTransform_o3[8] = -191.0F;
    lanedetection_hough_test_B.HoughTransform_o3[9] = -190.0F;
    lanedetection_hough_test_B.HoughTransform_o3[10] = -189.0F;
    lanedetection_hough_test_B.HoughTransform_o3[11] = -188.0F;
    lanedetection_hough_test_B.HoughTransform_o3[12] = -187.0F;
    lanedetection_hough_test_B.HoughTransform_o3[13] = -186.0F;
    lanedetection_hough_test_B.HoughTransform_o3[14] = -185.0F;
    lanedetection_hough_test_B.HoughTransform_o3[15] = -184.0F;
    lanedetection_hough_test_B.HoughTransform_o3[16] = -183.0F;
    lanedetection_hough_test_B.HoughTransform_o3[17] = -182.0F;
    lanedetection_hough_test_B.HoughTransform_o3[18] = -181.0F;
    lanedetection_hough_test_B.HoughTransform_o3[19] = -180.0F;
    lanedetection_hough_test_B.HoughTransform_o3[20] = -179.0F;
    lanedetection_hough_test_B.HoughTransform_o3[21] = -178.0F;
    lanedetection_hough_test_B.HoughTransform_o3[22] = -177.0F;
    lanedetection_hough_test_B.HoughTransform_o3[23] = -176.0F;
    lanedetection_hough_test_B.HoughTransform_o3[24] = -175.0F;
    lanedetection_hough_test_B.HoughTransform_o3[25] = -174.0F;
    lanedetection_hough_test_B.HoughTransform_o3[26] = -173.0F;
    lanedetection_hough_test_B.HoughTransform_o3[27] = -172.0F;
    lanedetection_hough_test_B.HoughTransform_o3[28] = -171.0F;
    lanedetection_hough_test_B.HoughTransform_o3[29] = -170.0F;
    lanedetection_hough_test_B.HoughTransform_o3[30] = -169.0F;
    lanedetection_hough_test_B.HoughTransform_o3[31] = -168.0F;
    lanedetection_hough_test_B.HoughTransform_o3[32] = -167.0F;
    lanedetection_hough_test_B.HoughTransform_o3[33] = -166.0F;
    lanedetection_hough_test_B.HoughTransform_o3[34] = -165.0F;
    lanedetection_hough_test_B.HoughTransform_o3[35] = -164.0F;
    lanedetection_hough_test_B.HoughTransform_o3[36] = -163.0F;
    lanedetection_hough_test_B.HoughTransform_o3[37] = -162.0F;
    lanedetection_hough_test_B.HoughTransform_o3[38] = -161.0F;
    lanedetection_hough_test_B.HoughTransform_o3[39] = -160.0F;
    lanedetection_hough_test_B.HoughTransform_o3[40] = -159.0F;
    lanedetection_hough_test_B.HoughTransform_o3[41] = -158.0F;
    lanedetection_hough_test_B.HoughTransform_o3[42] = -157.0F;
    lanedetection_hough_test_B.HoughTransform_o3[43] = -156.0F;
    lanedetection_hough_test_B.HoughTransform_o3[44] = -155.0F;
    lanedetection_hough_test_B.HoughTransform_o3[45] = -154.0F;
    lanedetection_hough_test_B.HoughTransform_o3[46] = -153.0F;
    lanedetection_hough_test_B.HoughTransform_o3[47] = -152.0F;
    lanedetection_hough_test_B.HoughTransform_o3[48] = -151.0F;
    lanedetection_hough_test_B.HoughTransform_o3[49] = -150.0F;
    lanedetection_hough_test_B.HoughTransform_o3[50] = -149.0F;
    lanedetection_hough_test_B.HoughTransform_o3[51] = -148.0F;
    lanedetection_hough_test_B.HoughTransform_o3[52] = -147.0F;
    lanedetection_hough_test_B.HoughTransform_o3[53] = -146.0F;
    lanedetection_hough_test_B.HoughTransform_o3[54] = -145.0F;
    lanedetection_hough_test_B.HoughTransform_o3[55] = -144.0F;
    lanedetection_hough_test_B.HoughTransform_o3[56] = -143.0F;
    lanedetection_hough_test_B.HoughTransform_o3[57] = -142.0F;
    lanedetection_hough_test_B.HoughTransform_o3[58] = -141.0F;
    lanedetection_hough_test_B.HoughTransform_o3[59] = -140.0F;
    lanedetection_hough_test_B.HoughTransform_o3[60] = -139.0F;
    lanedetection_hough_test_B.HoughTransform_o3[61] = -138.0F;
    lanedetection_hough_test_B.HoughTransform_o3[62] = -137.0F;
    lanedetection_hough_test_B.HoughTransform_o3[63] = -136.0F;
    lanedetection_hough_test_B.HoughTransform_o3[64] = -135.0F;
    lanedetection_hough_test_B.HoughTransform_o3[65] = -134.0F;
    lanedetection_hough_test_B.HoughTransform_o3[66] = -133.0F;
    lanedetection_hough_test_B.HoughTransform_o3[67] = -132.0F;
    lanedetection_hough_test_B.HoughTransform_o3[68] = -131.0F;
    lanedetection_hough_test_B.HoughTransform_o3[69] = -130.0F;
    lanedetection_hough_test_B.HoughTransform_o3[70] = -129.0F;
    lanedetection_hough_test_B.HoughTransform_o3[71] = -128.0F;
    lanedetection_hough_test_B.HoughTransform_o3[72] = -127.0F;
    lanedetection_hough_test_B.HoughTransform_o3[73] = -126.0F;
    lanedetection_hough_test_B.HoughTransform_o3[74] = -125.0F;
    lanedetection_hough_test_B.HoughTransform_o3[75] = -124.0F;
    lanedetection_hough_test_B.HoughTransform_o3[76] = -123.0F;
    lanedetection_hough_test_B.HoughTransform_o3[77] = -122.0F;
    lanedetection_hough_test_B.HoughTransform_o3[78] = -121.0F;
    lanedetection_hough_test_B.HoughTransform_o3[79] = -120.0F;
    lanedetection_hough_test_B.HoughTransform_o3[80] = -119.0F;
    lanedetection_hough_test_B.HoughTransform_o3[81] = -118.0F;
    lanedetection_hough_test_B.HoughTransform_o3[82] = -117.0F;
    lanedetection_hough_test_B.HoughTransform_o3[83] = -116.0F;
    lanedetection_hough_test_B.HoughTransform_o3[84] = -115.0F;
    lanedetection_hough_test_B.HoughTransform_o3[85] = -114.0F;
    lanedetection_hough_test_B.HoughTransform_o3[86] = -113.0F;
    lanedetection_hough_test_B.HoughTransform_o3[87] = -112.0F;
    lanedetection_hough_test_B.HoughTransform_o3[88] = -111.0F;
    lanedetection_hough_test_B.HoughTransform_o3[89] = -110.0F;
    lanedetection_hough_test_B.HoughTransform_o3[90] = -109.0F;
    lanedetection_hough_test_B.HoughTransform_o3[91] = -108.0F;
    lanedetection_hough_test_B.HoughTransform_o3[92] = -107.0F;
    lanedetection_hough_test_B.HoughTransform_o3[93] = -106.0F;
    lanedetection_hough_test_B.HoughTransform_o3[94] = -105.0F;
    lanedetection_hough_test_B.HoughTransform_o3[95] = -104.0F;
    lanedetection_hough_test_B.HoughTransform_o3[96] = -103.0F;
    lanedetection_hough_test_B.HoughTransform_o3[97] = -102.0F;
    lanedetection_hough_test_B.HoughTransform_o3[98] = -101.0F;
    lanedetection_hough_test_B.HoughTransform_o3[99] = -100.0F;
    lanedetection_hough_test_B.HoughTransform_o3[100] = -99.0F;
    lanedetection_hough_test_B.HoughTransform_o3[101] = -98.0F;
    lanedetection_hough_test_B.HoughTransform_o3[102] = -97.0F;
    lanedetection_hough_test_B.HoughTransform_o3[103] = -96.0F;
    lanedetection_hough_test_B.HoughTransform_o3[104] = -95.0F;
    lanedetection_hough_test_B.HoughTransform_o3[105] = -94.0F;
    lanedetection_hough_test_B.HoughTransform_o3[106] = -93.0F;
    lanedetection_hough_test_B.HoughTransform_o3[107] = -92.0F;
    lanedetection_hough_test_B.HoughTransform_o3[108] = -91.0F;
    lanedetection_hough_test_B.HoughTransform_o3[109] = -90.0F;
    lanedetection_hough_test_B.HoughTransform_o3[110] = -89.0F;
    lanedetection_hough_test_B.HoughTransform_o3[111] = -88.0F;
    lanedetection_hough_test_B.HoughTransform_o3[112] = -87.0F;
    lanedetection_hough_test_B.HoughTransform_o3[113] = -86.0F;
    lanedetection_hough_test_B.HoughTransform_o3[114] = -85.0F;
    lanedetection_hough_test_B.HoughTransform_o3[115] = -84.0F;
    lanedetection_hough_test_B.HoughTransform_o3[116] = -83.0F;
    lanedetection_hough_test_B.HoughTransform_o3[117] = -82.0F;
    lanedetection_hough_test_B.HoughTransform_o3[118] = -81.0F;
    lanedetection_hough_test_B.HoughTransform_o3[119] = -80.0F;
    lanedetection_hough_test_B.HoughTransform_o3[120] = -79.0F;
    lanedetection_hough_test_B.HoughTransform_o3[121] = -78.0F;
    lanedetection_hough_test_B.HoughTransform_o3[122] = -77.0F;
    lanedetection_hough_test_B.HoughTransform_o3[123] = -76.0F;
    lanedetection_hough_test_B.HoughTransform_o3[124] = -75.0F;
    lanedetection_hough_test_B.HoughTransform_o3[125] = -74.0F;
    lanedetection_hough_test_B.HoughTransform_o3[126] = -73.0F;
    lanedetection_hough_test_B.HoughTransform_o3[127] = -72.0F;
    lanedetection_hough_test_B.HoughTransform_o3[128] = -71.0F;
    lanedetection_hough_test_B.HoughTransform_o3[129] = -70.0F;
    lanedetection_hough_test_B.HoughTransform_o3[130] = -69.0F;
    lanedetection_hough_test_B.HoughTransform_o3[131] = -68.0F;
    lanedetection_hough_test_B.HoughTransform_o3[132] = -67.0F;
    lanedetection_hough_test_B.HoughTransform_o3[133] = -66.0F;
    lanedetection_hough_test_B.HoughTransform_o3[134] = -65.0F;
    lanedetection_hough_test_B.HoughTransform_o3[135] = -64.0F;
    lanedetection_hough_test_B.HoughTransform_o3[136] = -63.0F;
    lanedetection_hough_test_B.HoughTransform_o3[137] = -62.0F;
    lanedetection_hough_test_B.HoughTransform_o3[138] = -61.0F;
    lanedetection_hough_test_B.HoughTransform_o3[139] = -60.0F;
    lanedetection_hough_test_B.HoughTransform_o3[140] = -59.0F;
    lanedetection_hough_test_B.HoughTransform_o3[141] = -58.0F;
    lanedetection_hough_test_B.HoughTransform_o3[142] = -57.0F;
    lanedetection_hough_test_B.HoughTransform_o3[143] = -56.0F;
    lanedetection_hough_test_B.HoughTransform_o3[144] = -55.0F;
    lanedetection_hough_test_B.HoughTransform_o3[145] = -54.0F;
    lanedetection_hough_test_B.HoughTransform_o3[146] = -53.0F;
    lanedetection_hough_test_B.HoughTransform_o3[147] = -52.0F;
    lanedetection_hough_test_B.HoughTransform_o3[148] = -51.0F;
    lanedetection_hough_test_B.HoughTransform_o3[149] = -50.0F;
    lanedetection_hough_test_B.HoughTransform_o3[150] = -49.0F;
    lanedetection_hough_test_B.HoughTransform_o3[151] = -48.0F;
    lanedetection_hough_test_B.HoughTransform_o3[152] = -47.0F;
    lanedetection_hough_test_B.HoughTransform_o3[153] = -46.0F;
    lanedetection_hough_test_B.HoughTransform_o3[154] = -45.0F;
    lanedetection_hough_test_B.HoughTransform_o3[155] = -44.0F;
    lanedetection_hough_test_B.HoughTransform_o3[156] = -43.0F;
    lanedetection_hough_test_B.HoughTransform_o3[157] = -42.0F;
    lanedetection_hough_test_B.HoughTransform_o3[158] = -41.0F;
    lanedetection_hough_test_B.HoughTransform_o3[159] = -40.0F;
    lanedetection_hough_test_B.HoughTransform_o3[160] = -39.0F;
    lanedetection_hough_test_B.HoughTransform_o3[161] = -38.0F;
    lanedetection_hough_test_B.HoughTransform_o3[162] = -37.0F;
    lanedetection_hough_test_B.HoughTransform_o3[163] = -36.0F;
    lanedetection_hough_test_B.HoughTransform_o3[164] = -35.0F;
    lanedetection_hough_test_B.HoughTransform_o3[165] = -34.0F;
    lanedetection_hough_test_B.HoughTransform_o3[166] = -33.0F;
    lanedetection_hough_test_B.HoughTransform_o3[167] = -32.0F;
    lanedetection_hough_test_B.HoughTransform_o3[168] = -31.0F;
    lanedetection_hough_test_B.HoughTransform_o3[169] = -30.0F;
    lanedetection_hough_test_B.HoughTransform_o3[170] = -29.0F;
    lanedetection_hough_test_B.HoughTransform_o3[171] = -28.0F;
    lanedetection_hough_test_B.HoughTransform_o3[172] = -27.0F;
    lanedetection_hough_test_B.HoughTransform_o3[173] = -26.0F;
    lanedetection_hough_test_B.HoughTransform_o3[174] = -25.0F;
    lanedetection_hough_test_B.HoughTransform_o3[175] = -24.0F;
    lanedetection_hough_test_B.HoughTransform_o3[176] = -23.0F;
    lanedetection_hough_test_B.HoughTransform_o3[177] = -22.0F;
    lanedetection_hough_test_B.HoughTransform_o3[178] = -21.0F;
    lanedetection_hough_test_B.HoughTransform_o3[179] = -20.0F;
    lanedetection_hough_test_B.HoughTransform_o3[180] = -19.0F;
    lanedetection_hough_test_B.HoughTransform_o3[181] = -18.0F;
    lanedetection_hough_test_B.HoughTransform_o3[182] = -17.0F;
    lanedetection_hough_test_B.HoughTransform_o3[183] = -16.0F;
    lanedetection_hough_test_B.HoughTransform_o3[184] = -15.0F;
    lanedetection_hough_test_B.HoughTransform_o3[185] = -14.0F;
    lanedetection_hough_test_B.HoughTransform_o3[186] = -13.0F;
    lanedetection_hough_test_B.HoughTransform_o3[187] = -12.0F;
    lanedetection_hough_test_B.HoughTransform_o3[188] = -11.0F;
    lanedetection_hough_test_B.HoughTransform_o3[189] = -10.0F;
    lanedetection_hough_test_B.HoughTransform_o3[190] = -9.0F;
    lanedetection_hough_test_B.HoughTransform_o3[191] = -8.0F;
    lanedetection_hough_test_B.HoughTransform_o3[192] = -7.0F;
    lanedetection_hough_test_B.HoughTransform_o3[193] = -6.0F;
    lanedetection_hough_test_B.HoughTransform_o3[194] = -5.0F;
    lanedetection_hough_test_B.HoughTransform_o3[195] = -4.0F;
    lanedetection_hough_test_B.HoughTransform_o3[196] = -3.0F;
    lanedetection_hough_test_B.HoughTransform_o3[197] = -2.0F;
    lanedetection_hough_test_B.HoughTransform_o3[198] = -1.0F;
    lanedetection_hough_test_B.HoughTransform_o3[199] = 0.0F;
    lanedetection_hough_test_B.HoughTransform_o3[200] = 1.0F;
    lanedetection_hough_test_B.HoughTransform_o3[201] = 2.0F;
    lanedetection_hough_test_B.HoughTransform_o3[202] = 3.0F;
    lanedetection_hough_test_B.HoughTransform_o3[203] = 4.0F;
    lanedetection_hough_test_B.HoughTransform_o3[204] = 5.0F;
    lanedetection_hough_test_B.HoughTransform_o3[205] = 6.0F;
    lanedetection_hough_test_B.HoughTransform_o3[206] = 7.0F;
    lanedetection_hough_test_B.HoughTransform_o3[207] = 8.0F;
    lanedetection_hough_test_B.HoughTransform_o3[208] = 9.0F;
    lanedetection_hough_test_B.HoughTransform_o3[209] = 10.0F;
    lanedetection_hough_test_B.HoughTransform_o3[210] = 11.0F;
    lanedetection_hough_test_B.HoughTransform_o3[211] = 12.0F;
    lanedetection_hough_test_B.HoughTransform_o3[212] = 13.0F;
    lanedetection_hough_test_B.HoughTransform_o3[213] = 14.0F;
    lanedetection_hough_test_B.HoughTransform_o3[214] = 15.0F;
    lanedetection_hough_test_B.HoughTransform_o3[215] = 16.0F;
    lanedetection_hough_test_B.HoughTransform_o3[216] = 17.0F;
    lanedetection_hough_test_B.HoughTransform_o3[217] = 18.0F;
    lanedetection_hough_test_B.HoughTransform_o3[218] = 19.0F;
    lanedetection_hough_test_B.HoughTransform_o3[219] = 20.0F;
    lanedetection_hough_test_B.HoughTransform_o3[220] = 21.0F;
    lanedetection_hough_test_B.HoughTransform_o3[221] = 22.0F;
    lanedetection_hough_test_B.HoughTransform_o3[222] = 23.0F;
    lanedetection_hough_test_B.HoughTransform_o3[223] = 24.0F;
    lanedetection_hough_test_B.HoughTransform_o3[224] = 25.0F;
    lanedetection_hough_test_B.HoughTransform_o3[225] = 26.0F;
    lanedetection_hough_test_B.HoughTransform_o3[226] = 27.0F;
    lanedetection_hough_test_B.HoughTransform_o3[227] = 28.0F;
    lanedetection_hough_test_B.HoughTransform_o3[228] = 29.0F;
    lanedetection_hough_test_B.HoughTransform_o3[229] = 30.0F;
    lanedetection_hough_test_B.HoughTransform_o3[230] = 31.0F;
    lanedetection_hough_test_B.HoughTransform_o3[231] = 32.0F;
    lanedetection_hough_test_B.HoughTransform_o3[232] = 33.0F;
    lanedetection_hough_test_B.HoughTransform_o3[233] = 34.0F;
    lanedetection_hough_test_B.HoughTransform_o3[234] = 35.0F;
    lanedetection_hough_test_B.HoughTransform_o3[235] = 36.0F;
    lanedetection_hough_test_B.HoughTransform_o3[236] = 37.0F;
    lanedetection_hough_test_B.HoughTransform_o3[237] = 38.0F;
    lanedetection_hough_test_B.HoughTransform_o3[238] = 39.0F;
    lanedetection_hough_test_B.HoughTransform_o3[239] = 40.0F;
    lanedetection_hough_test_B.HoughTransform_o3[240] = 41.0F;
    lanedetection_hough_test_B.HoughTransform_o3[241] = 42.0F;
    lanedetection_hough_test_B.HoughTransform_o3[242] = 43.0F;
    lanedetection_hough_test_B.HoughTransform_o3[243] = 44.0F;
    lanedetection_hough_test_B.HoughTransform_o3[244] = 45.0F;
    lanedetection_hough_test_B.HoughTransform_o3[245] = 46.0F;
    lanedetection_hough_test_B.HoughTransform_o3[246] = 47.0F;
    lanedetection_hough_test_B.HoughTransform_o3[247] = 48.0F;
    lanedetection_hough_test_B.HoughTransform_o3[248] = 49.0F;
    lanedetection_hough_test_B.HoughTransform_o3[249] = 50.0F;
    lanedetection_hough_test_B.HoughTransform_o3[250] = 51.0F;
    lanedetection_hough_test_B.HoughTransform_o3[251] = 52.0F;
    lanedetection_hough_test_B.HoughTransform_o3[252] = 53.0F;
    lanedetection_hough_test_B.HoughTransform_o3[253] = 54.0F;
    lanedetection_hough_test_B.HoughTransform_o3[254] = 55.0F;
    lanedetection_hough_test_B.HoughTransform_o3[255] = 56.0F;
    lanedetection_hough_test_B.HoughTransform_o3[256] = 57.0F;
    lanedetection_hough_test_B.HoughTransform_o3[257] = 58.0F;
    lanedetection_hough_test_B.HoughTransform_o3[258] = 59.0F;
    lanedetection_hough_test_B.HoughTransform_o3[259] = 60.0F;
    lanedetection_hough_test_B.HoughTransform_o3[260] = 61.0F;
    lanedetection_hough_test_B.HoughTransform_o3[261] = 62.0F;
    lanedetection_hough_test_B.HoughTransform_o3[262] = 63.0F;
    lanedetection_hough_test_B.HoughTransform_o3[263] = 64.0F;
    lanedetection_hough_test_B.HoughTransform_o3[264] = 65.0F;
    lanedetection_hough_test_B.HoughTransform_o3[265] = 66.0F;
    lanedetection_hough_test_B.HoughTransform_o3[266] = 67.0F;
    lanedetection_hough_test_B.HoughTransform_o3[267] = 68.0F;
    lanedetection_hough_test_B.HoughTransform_o3[268] = 69.0F;
    lanedetection_hough_test_B.HoughTransform_o3[269] = 70.0F;
    lanedetection_hough_test_B.HoughTransform_o3[270] = 71.0F;
    lanedetection_hough_test_B.HoughTransform_o3[271] = 72.0F;
    lanedetection_hough_test_B.HoughTransform_o3[272] = 73.0F;
    lanedetection_hough_test_B.HoughTransform_o3[273] = 74.0F;
    lanedetection_hough_test_B.HoughTransform_o3[274] = 75.0F;
    lanedetection_hough_test_B.HoughTransform_o3[275] = 76.0F;
    lanedetection_hough_test_B.HoughTransform_o3[276] = 77.0F;
    lanedetection_hough_test_B.HoughTransform_o3[277] = 78.0F;
    lanedetection_hough_test_B.HoughTransform_o3[278] = 79.0F;
    lanedetection_hough_test_B.HoughTransform_o3[279] = 80.0F;
    lanedetection_hough_test_B.HoughTransform_o3[280] = 81.0F;
    lanedetection_hough_test_B.HoughTransform_o3[281] = 82.0F;
    lanedetection_hough_test_B.HoughTransform_o3[282] = 83.0F;
    lanedetection_hough_test_B.HoughTransform_o3[283] = 84.0F;
    lanedetection_hough_test_B.HoughTransform_o3[284] = 85.0F;
    lanedetection_hough_test_B.HoughTransform_o3[285] = 86.0F;
    lanedetection_hough_test_B.HoughTransform_o3[286] = 87.0F;
    lanedetection_hough_test_B.HoughTransform_o3[287] = 88.0F;
    lanedetection_hough_test_B.HoughTransform_o3[288] = 89.0F;
    lanedetection_hough_test_B.HoughTransform_o3[289] = 90.0F;
    lanedetection_hough_test_B.HoughTransform_o3[290] = 91.0F;
    lanedetection_hough_test_B.HoughTransform_o3[291] = 92.0F;
    lanedetection_hough_test_B.HoughTransform_o3[292] = 93.0F;
    lanedetection_hough_test_B.HoughTransform_o3[293] = 94.0F;
    lanedetection_hough_test_B.HoughTransform_o3[294] = 95.0F;
    lanedetection_hough_test_B.HoughTransform_o3[295] = 96.0F;
    lanedetection_hough_test_B.HoughTransform_o3[296] = 97.0F;
    lanedetection_hough_test_B.HoughTransform_o3[297] = 98.0F;
    lanedetection_hough_test_B.HoughTransform_o3[298] = 99.0F;
    lanedetection_hough_test_B.HoughTransform_o3[299] = 100.0F;
    lanedetection_hough_test_B.HoughTransform_o3[300] = 101.0F;
    lanedetection_hough_test_B.HoughTransform_o3[301] = 102.0F;
    lanedetection_hough_test_B.HoughTransform_o3[302] = 103.0F;
    lanedetection_hough_test_B.HoughTransform_o3[303] = 104.0F;
    lanedetection_hough_test_B.HoughTransform_o3[304] = 105.0F;
    lanedetection_hough_test_B.HoughTransform_o3[305] = 106.0F;
    lanedetection_hough_test_B.HoughTransform_o3[306] = 107.0F;
    lanedetection_hough_test_B.HoughTransform_o3[307] = 108.0F;
    lanedetection_hough_test_B.HoughTransform_o3[308] = 109.0F;
    lanedetection_hough_test_B.HoughTransform_o3[309] = 110.0F;
    lanedetection_hough_test_B.HoughTransform_o3[310] = 111.0F;
    lanedetection_hough_test_B.HoughTransform_o3[311] = 112.0F;
    lanedetection_hough_test_B.HoughTransform_o3[312] = 113.0F;
    lanedetection_hough_test_B.HoughTransform_o3[313] = 114.0F;
    lanedetection_hough_test_B.HoughTransform_o3[314] = 115.0F;
    lanedetection_hough_test_B.HoughTransform_o3[315] = 116.0F;
    lanedetection_hough_test_B.HoughTransform_o3[316] = 117.0F;
    lanedetection_hough_test_B.HoughTransform_o3[317] = 118.0F;
    lanedetection_hough_test_B.HoughTransform_o3[318] = 119.0F;
    lanedetection_hough_test_B.HoughTransform_o3[319] = 120.0F;
    lanedetection_hough_test_B.HoughTransform_o3[320] = 121.0F;
    lanedetection_hough_test_B.HoughTransform_o3[321] = 122.0F;
    lanedetection_hough_test_B.HoughTransform_o3[322] = 123.0F;
    lanedetection_hough_test_B.HoughTransform_o3[323] = 124.0F;
    lanedetection_hough_test_B.HoughTransform_o3[324] = 125.0F;
    lanedetection_hough_test_B.HoughTransform_o3[325] = 126.0F;
    lanedetection_hough_test_B.HoughTransform_o3[326] = 127.0F;
    lanedetection_hough_test_B.HoughTransform_o3[327] = 128.0F;
    lanedetection_hough_test_B.HoughTransform_o3[328] = 129.0F;
    lanedetection_hough_test_B.HoughTransform_o3[329] = 130.0F;
    lanedetection_hough_test_B.HoughTransform_o3[330] = 131.0F;
    lanedetection_hough_test_B.HoughTransform_o3[331] = 132.0F;
    lanedetection_hough_test_B.HoughTransform_o3[332] = 133.0F;
    lanedetection_hough_test_B.HoughTransform_o3[333] = 134.0F;
    lanedetection_hough_test_B.HoughTransform_o3[334] = 135.0F;
    lanedetection_hough_test_B.HoughTransform_o3[335] = 136.0F;
    lanedetection_hough_test_B.HoughTransform_o3[336] = 137.0F;
    lanedetection_hough_test_B.HoughTransform_o3[337] = 138.0F;
    lanedetection_hough_test_B.HoughTransform_o3[338] = 139.0F;
    lanedetection_hough_test_B.HoughTransform_o3[339] = 140.0F;
    lanedetection_hough_test_B.HoughTransform_o3[340] = 141.0F;
    lanedetection_hough_test_B.HoughTransform_o3[341] = 142.0F;
    lanedetection_hough_test_B.HoughTransform_o3[342] = 143.0F;
    lanedetection_hough_test_B.HoughTransform_o3[343] = 144.0F;
    lanedetection_hough_test_B.HoughTransform_o3[344] = 145.0F;
    lanedetection_hough_test_B.HoughTransform_o3[345] = 146.0F;
    lanedetection_hough_test_B.HoughTransform_o3[346] = 147.0F;
    lanedetection_hough_test_B.HoughTransform_o3[347] = 148.0F;
    lanedetection_hough_test_B.HoughTransform_o3[348] = 149.0F;
    lanedetection_hough_test_B.HoughTransform_o3[349] = 150.0F;
    lanedetection_hough_test_B.HoughTransform_o3[350] = 151.0F;
    lanedetection_hough_test_B.HoughTransform_o3[351] = 152.0F;
    lanedetection_hough_test_B.HoughTransform_o3[352] = 153.0F;
    lanedetection_hough_test_B.HoughTransform_o3[353] = 154.0F;
    lanedetection_hough_test_B.HoughTransform_o3[354] = 155.0F;
    lanedetection_hough_test_B.HoughTransform_o3[355] = 156.0F;
    lanedetection_hough_test_B.HoughTransform_o3[356] = 157.0F;
    lanedetection_hough_test_B.HoughTransform_o3[357] = 158.0F;
    lanedetection_hough_test_B.HoughTransform_o3[358] = 159.0F;
    lanedetection_hough_test_B.HoughTransform_o3[359] = 160.0F;
    lanedetection_hough_test_B.HoughTransform_o3[360] = 161.0F;
    lanedetection_hough_test_B.HoughTransform_o3[361] = 162.0F;
    lanedetection_hough_test_B.HoughTransform_o3[362] = 163.0F;
    lanedetection_hough_test_B.HoughTransform_o3[363] = 164.0F;
    lanedetection_hough_test_B.HoughTransform_o3[364] = 165.0F;
    lanedetection_hough_test_B.HoughTransform_o3[365] = 166.0F;
    lanedetection_hough_test_B.HoughTransform_o3[366] = 167.0F;
    lanedetection_hough_test_B.HoughTransform_o3[367] = 168.0F;
    lanedetection_hough_test_B.HoughTransform_o3[368] = 169.0F;
    lanedetection_hough_test_B.HoughTransform_o3[369] = 170.0F;
    lanedetection_hough_test_B.HoughTransform_o3[370] = 171.0F;
    lanedetection_hough_test_B.HoughTransform_o3[371] = 172.0F;
    lanedetection_hough_test_B.HoughTransform_o3[372] = 173.0F;
    lanedetection_hough_test_B.HoughTransform_o3[373] = 174.0F;
    lanedetection_hough_test_B.HoughTransform_o3[374] = 175.0F;
    lanedetection_hough_test_B.HoughTransform_o3[375] = 176.0F;
    lanedetection_hough_test_B.HoughTransform_o3[376] = 177.0F;
    lanedetection_hough_test_B.HoughTransform_o3[377] = 178.0F;
    lanedetection_hough_test_B.HoughTransform_o3[378] = 179.0F;
    lanedetection_hough_test_B.HoughTransform_o3[379] = 180.0F;
    lanedetection_hough_test_B.HoughTransform_o3[380] = 181.0F;
    lanedetection_hough_test_B.HoughTransform_o3[381] = 182.0F;
    lanedetection_hough_test_B.HoughTransform_o3[382] = 183.0F;
    lanedetection_hough_test_B.HoughTransform_o3[383] = 184.0F;
    lanedetection_hough_test_B.HoughTransform_o3[384] = 185.0F;
    lanedetection_hough_test_B.HoughTransform_o3[385] = 186.0F;
    lanedetection_hough_test_B.HoughTransform_o3[386] = 187.0F;
    lanedetection_hough_test_B.HoughTransform_o3[387] = 188.0F;
    lanedetection_hough_test_B.HoughTransform_o3[388] = 189.0F;
    lanedetection_hough_test_B.HoughTransform_o3[389] = 190.0F;
    lanedetection_hough_test_B.HoughTransform_o3[390] = 191.0F;
    lanedetection_hough_test_B.HoughTransform_o3[391] = 192.0F;
    lanedetection_hough_test_B.HoughTransform_o3[392] = 193.0F;
    lanedetection_hough_test_B.HoughTransform_o3[393] = 194.0F;
    lanedetection_hough_test_B.HoughTransform_o3[394] = 195.0F;
    lanedetection_hough_test_B.HoughTransform_o3[395] = 196.0F;
    lanedetection_hough_test_B.HoughTransform_o3[396] = 197.0F;
    lanedetection_hough_test_B.HoughTransform_o3[397] = 198.0F;
    lanedetection_hough_test_B.HoughTransform_o3[398] = 199.0F;
  }

  /* states (dwork) */
  (void) memset((void *)&lanedetection_hough_test_DW, 0,
                sizeof(DW_lanedetection_hough_test_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lanedetection_hough_test_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Start for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureInit(lanedetection_hough_test_ConstP.V4L2VideoCapture_p1, 0, 0,
                      0, 0, 160U, 120U, 2U, 2U, 1U, 0.033333333333333333);

  /* Start for S-Function (svipedge): '<Root>/Edge Detection' */
  lanedetection_hough_test_DW.EdgeDetection_VO_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOU_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOD_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOL_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOR_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOLR_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOUL_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOLL_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOUR_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_HO_DW[0] = 1;
  lanedetection_hough_test_DW.EdgeDetection_HOU_DW[0] = 1;
  lanedetection_hough_test_DW.EdgeDetection_HOD_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_HOL_DW[0] = 1;
  lanedetection_hough_test_DW.EdgeDetection_HOR_DW[0] = 1;
  lanedetection_hough_test_DW.EdgeDetection_HOLR_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_HOUL_DW[0] = 1;
  lanedetection_hough_test_DW.EdgeDetection_HOLL_DW[0] = 0;
  lanedetection_hough_test_DW.EdgeDetection_HOUR_DW[0] = 1;
  lanedetection_hough_test_DW.EdgeDetection_VO_DW[1] = 161;
  lanedetection_hough_test_DW.EdgeDetection_VOU_DW[1] = 161;
  lanedetection_hough_test_DW.EdgeDetection_VOD_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_VOL_DW[1] = 161;
  lanedetection_hough_test_DW.EdgeDetection_VOR_DW[1] = 1;
  lanedetection_hough_test_DW.EdgeDetection_VOLR_DW[1] = 0;
  lanedetection_hough_test_DW.EdgeDetection_VOUL_DW[1] = 161;
  lanedetection_hough_test_DW.EdgeDetection_VOLL_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_VOUR_DW[1] = 1;
  lanedetection_hough_test_DW.EdgeDetection_HO_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_HOU_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_HOD_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_HOL_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_HOR_DW[1] = 0;
  lanedetection_hough_test_DW.EdgeDetection_HOLR_DW[1] = 0;
  lanedetection_hough_test_DW.EdgeDetection_HOUL_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_HOLL_DW[1] = 160;
  lanedetection_hough_test_DW.EdgeDetection_HOUR_DW[1] = 0;

  /* Start for MATLABSystem: '<S2>/MATLAB System' */
  lanedetection_hough_test_DW.obj.matlabCodegenIsDeleted = true;
  lanedetection_hough_test_DW.obj.isInitialized = 0;
  lanedetection_hough_test_DW.obj.matlabCodegenIsDeleted = false;
  lanedetection_hough_test_DW.obj.isSetupComplete = false;
  lanedetection_hough_test_DW.obj.isInitialized = 1;
  lanedetection_hough_test_DW.obj.PixelFormatEnum = 1;
  MW_SDL_videoDisplayInit(lanedetection_hough_test_DW.obj.PixelFormatEnum, 1, 1,
    160.0, 120.0);
  lanedetection_hough_test_DW.obj.isSetupComplete = true;

  /* End of Start for SubSystem: '<Root>/SDL Video Display' */
}

/* Model terminate function */
void lanedetection_hough_test_terminate(void)
{
  /* Terminate for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureTerminate(lanedetection_hough_test_ConstP.V4L2VideoCapture_p1);

  /* Terminate for MATLABSystem: '<S2>/MATLAB System' */
  matlabCodegenHandle_matlabCodeg(&lanedetection_hough_test_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/SDL Video Display' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
