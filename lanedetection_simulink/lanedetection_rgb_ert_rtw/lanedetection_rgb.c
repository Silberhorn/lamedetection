/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_rgb.c
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
#include "lanedetection_rgb_dt.h"

/* Block signals (default storage) */
B_lanedetection_rgb_T lanedetection_rgb_B;

/* Block states (default storage) */
DW_lanedetection_rgb_T lanedetection_rgb_DW;

/* Real-time model */
RT_MODEL_lanedetection_rgb_T lanedetection_rgb_M_;
RT_MODEL_lanedetection_rgb_T *const lanedetection_rgb_M = &lanedetection_rgb_M_;

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
  /* Start for MATLABSystem: '<S1>/MATLAB System' */
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetectio_SystemCore_release(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S1>/MATLAB System' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SDL_videoDisplayTerminate(0, 0);
  }

  /* End of Start for MATLABSystem: '<S1>/MATLAB System' */
}

static void lanedetection_SystemCore_delete(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S1>/MATLAB System' */
  lanedetectio_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S1>/MATLAB System' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAnyP(obj, true);
    lanedetection_SystemCore_delete(obj);
  }

  /* End of Start for MATLABSystem: '<S1>/MATLAB System' */
}

/* Model step function */
void lanedetection_rgb_step(void)
{
  int8_T idxTmpArray[2];
  int32_T q2;
  int32_T q1;
  real32_T maxValue;
  int32_T imgCol;
  int32_T imgRow;
  int32_T m;
  boolean_T b4;
  boolean_T b3;
  boolean_T b2;
  boolean_T b1;
  int8_T accumOne;
  int8_T accumTwo;
  int8_T accumFour;
  int8_T accumThree;
  int32_T imgIdx;
  int32_T acc1_idx_5;
  int32_T acc4_idx_0;
  int32_T edgeTmp_tmp;
  int32_T DrawShapes_DW_Polygon_tmp;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_rgb_ConstP.V4L2VideoCapture_p1,
                        lanedetection_rgb_B.V4L2VideoCapture_o1,
                        lanedetection_rgb_B.V4L2VideoCapture_o2,
                        lanedetection_rgb_B.V4L2VideoCapture_o3);

  /* MATLAB Function: '<Root>/img_ROI' */
  for (q2 = 0; q2 < 70; q2++) {
    memcpy(&lanedetection_rgb_B.rOUT[q2 * 316],
           &lanedetection_rgb_B.V4L2VideoCapture_o1[q2 * 320 + 30402], 316U *
           sizeof(uint8_T));
  }

  for (q2 = 0; q2 < 70; q2++) {
    memcpy(&lanedetection_rgb_B.gOUT[q2 * 316],
           &lanedetection_rgb_B.V4L2VideoCapture_o2[q2 * 320 + 30402], 316U *
           sizeof(uint8_T));
  }

  for (q2 = 0; q2 < 70; q2++) {
    memcpy(&lanedetection_rgb_B.bOUT[q2 * 316],
           &lanedetection_rgb_B.V4L2VideoCapture_o3[q2 * 320 + 30402], 316U *
           sizeof(uint8_T));
  }

  /* End of MATLAB Function: '<Root>/img_ROI' */

  /* S-Function (svipcolorconv): '<Root>/Color Space  Conversion' */
  for (imgCol = 0; imgCol < 22120; imgCol++) {
    lanedetection_rgb_B.ColorSpaceConversion[imgCol] = (uint8_T)
      ((((lanedetection_rgb_B.rOUT[imgCol] * 19595U +
          lanedetection_rgb_B.gOUT[imgCol] * 38470U) +
         lanedetection_rgb_B.bOUT[imgCol] * 7471U) + 32768U) >> 16);
  }

  /* End of S-Function (svipcolorconv): '<Root>/Color Space  Conversion' */

  /* S-Function (svipedge): '<Root>/Edge Detection' incorporates:
   *  Constant: '<Root>/Threshold'
   */
  for (imgCol = 0; imgCol < 68; imgCol++) {
    for (imgRow = 0; imgRow < 314; imgRow++) {
      accumOne = 0;
      accumTwo = 0;
      imgIdx = ((imgCol + 1) * 316 + imgRow) + 1;
      for (m = 0; m < 6; m++) {
        accumOne += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
          lanedetection_rgb_DW.EdgeDetection_VO_DW[m]] *
          lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
        accumTwo += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
          lanedetection_rgb_DW.EdgeDetection_HO_DW[m]] *
          lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
      }

      lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[imgIdx] = (int8_T)
        (((accumOne * accumOne) << 8) >> 8);
      lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[imgIdx] = (int8_T)
        (((accumTwo * accumTwo) << 8) >> 8);
    }
  }

  for (imgCol = 0; imgCol < 68; imgCol++) {
    accumOne = 0;
    accumTwo = 0;
    accumThree = 0;
    accumFour = 0;
    imgRow = (imgCol + 1) * 316;
    imgIdx = (imgCol + 1) * 316 + 315;
    for (m = 0; m < 6; m++) {
      accumOne += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[imgRow +
        lanedetection_rgb_DW.EdgeDetection_HOU_DW[m]] *
        lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
      accumTwo += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
        lanedetection_rgb_DW.EdgeDetection_HOD_DW[m]] *
        lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
      accumThree += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[imgRow +
        lanedetection_rgb_DW.EdgeDetection_VOU_DW[m]] *
        lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
      accumFour += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
        lanedetection_rgb_DW.EdgeDetection_VOD_DW[m]] *
        lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
    }

    lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[imgRow] = (int8_T)
      (((accumThree * accumThree) << 8) >> 8);
    lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[imgRow] = (int8_T)
      (((accumOne * accumOne) << 8) >> 8);
    lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[imgIdx] = (int8_T)
      (((accumFour * accumFour) << 8) >> 8);
    lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[imgIdx] = (int8_T)
      (((accumTwo * accumTwo) << 8) >> 8);
  }

  for (imgRow = 0; imgRow < 314; imgRow++) {
    accumOne = 0;
    accumTwo = 0;
    accumThree = 0;
    accumFour = 0;
    for (m = 0; m < 6; m++) {
      accumOne += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[(imgRow +
        lanedetection_rgb_DW.EdgeDetection_VOL_DW[m]) + 1] *
        lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
      accumTwo += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[(imgRow +
        lanedetection_rgb_DW.EdgeDetection_VOR_DW[m]) + 21805] *
        lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
      accumThree += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[(imgRow
        + lanedetection_rgb_DW.EdgeDetection_HOL_DW[m]) + 1] *
        lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
      accumFour += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[(imgRow +
        lanedetection_rgb_DW.EdgeDetection_HOR_DW[m]) + 21805] *
        lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
    }

    lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[imgRow + 1] = (int8_T)
      (((accumOne * accumOne) << 8) >> 8);
    lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[imgRow + 1] = (int8_T)
      (((accumThree * accumThree) << 8) >> 8);
    lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[21805 + imgRow] = (int8_T)
      (((accumTwo * accumTwo) << 8) >> 8);
    lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[21805 + imgRow] = (int8_T)
      (((accumFour * accumFour) << 8) >> 8);
  }

  accumOne = 0;
  accumTwo = 0;
  accumThree = 0;
  accumFour = 0;
  for (m = 0; m < 6; m++) {
    accumOne += (int8_T)
      (((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_DW.EdgeDetection_VOUL_DW
         [m]] * lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
    accumTwo += (int8_T)
      (((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_DW.EdgeDetection_HOUL_DW
         [m]] * lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
    accumThree += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[315 +
      lanedetection_rgb_DW.EdgeDetection_VOLL_DW[m]] *
      lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
    accumFour += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[315 +
      lanedetection_rgb_DW.EdgeDetection_HOLL_DW[m]] *
      lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
  }

  lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[0] = (int8_T)(((accumOne *
    accumOne) << 8) >> 8);
  lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[0] = (int8_T)(((accumTwo *
    accumTwo) << 8) >> 8);
  lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[315] = (int8_T)(((accumThree *
    accumThree) << 8) >> 8);
  lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[315] = (int8_T)(((accumFour *
    accumFour) << 8) >> 8);
  accumOne = 0;
  accumTwo = 0;
  accumThree = 0;
  accumFour = 0;
  for (m = 0; m < 6; m++) {
    accumOne += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[21804 +
      lanedetection_rgb_DW.EdgeDetection_VOUR_DW[m]] *
      lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
    accumTwo += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[21804 +
      lanedetection_rgb_DW.EdgeDetection_HOUR_DW[m]] *
      lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
    accumThree += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[22119 +
      lanedetection_rgb_DW.EdgeDetection_VOLR_DW[m]] *
      lanedetection_rgb_ConstP.EdgeDetection_VC_RTP[m]) << 1) >> 8);
    accumFour += (int8_T)(((lanedetection_rgb_B.ColorSpaceConversion[22119 +
      lanedetection_rgb_DW.EdgeDetection_HOLR_DW[m]] *
      lanedetection_rgb_ConstP.EdgeDetection_HC_RTP[m]) << 1) >> 8);
  }

  lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[21804] = (int8_T)(((accumOne *
    accumOne) << 8) >> 8);
  lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[21804] = (int8_T)(((accumTwo *
    accumTwo) << 8) >> 8);
  lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[22119] = (int8_T)
    (((accumThree * accumThree) << 8) >> 8);
  lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[22119] = (int8_T)(((accumFour
    * accumFour) << 8) >> 8);
  for (m = 0; m < 22120; m++) {
    lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m] =
      lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[m];
    lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m] +=
      lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[m];
  }

  accumOne = (int8_T)(((int32_T)((uint32_T)lanedetection_rgb_P.Threshold_Value *
    lanedetection_rgb_P.Threshold_Value) << 8) >> 8);
  for (imgCol = 0; imgCol < 70; imgCol++) {
    for (imgRow = 0; imgRow < 316; imgRow++) {
      m = imgCol * 316 + imgRow;
      b1 = true;
      b2 = true;
      b3 = true;
      b4 = true;
      if (imgCol != 0) {
        b1 = (lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m - 316] <=
              lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m]);
      }

      if (imgCol != 69) {
        b2 = (lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m] >
              lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m + 316]);
      }

      if (imgRow != 0) {
        b3 = (lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m - 1] <=
              lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m]);
      }

      if (imgRow != 315) {
        b4 = (lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m] >
              lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m + 1]);
      }

      lanedetection_rgb_B.EdgeDetection[m] =
        ((lanedetection_rgb_DW.EdgeDetection_GRAD_SUM_DW[m] > accumOne) &&
         (((lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[m] >=
            lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[m]) && b1 && b2) ||
          ((lanedetection_rgb_DW.EdgeDetection_GH_SQUARED_DW[m] >=
            lanedetection_rgb_DW.EdgeDetection_GV_SQUARED_DW[m]) && b3 && b4)));
    }
  }

  /* End of S-Function (svipedge): '<Root>/Edge Detection' */

  /* Math: '<Root>/Transpose' */
  for (q2 = 0; q2 < 316; q2++) {
    for (imgCol = 0; imgCol < 70; imgCol++) {
      lanedetection_rgb_B.Transpose[imgCol + 70 * q2] =
        lanedetection_rgb_B.EdgeDetection[316 * imgCol + q2];
    }
  }

  /* End of Math: '<Root>/Transpose' */

  /* S-Function (sviphough): '<Root>/Hough Transform' */
  MWVIP_Hough_R(&lanedetection_rgb_B.EdgeDetection[0],
                &lanedetection_rgb_B.HoughTransform_o1[0],
                &lanedetection_rgb_ConstP.HoughTransform_SINE_TABLE_RTP[0],
                &lanedetection_rgb_ConstP.HoughTransform_FIRSTRHO_RTP, 316, 70,
                163, 46);

  /* S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */
  m = 0;
  b1 = false;
  for (imgCol = 0; imgCol < 14670; imgCol++) {
    lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol] =
      lanedetection_rgb_B.HoughTransform_o1[imgCol];
  }

  lanedetection_rgb_B.FindLocalMaxima_o1[0] = 0.0F;
  lanedetection_rgb_B.FindLocalMaxima_o1[1] = 0.0F;
  lanedetection_rgb_B.FindLocalMaxima_o1[2] = 0.0F;
  lanedetection_rgb_B.FindLocalMaxima_o1[3] = 0.0F;
  while (!b1) {
    imgRow = 0;
    maxValue = lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[0];
    for (imgCol = 0; imgCol < 14670; imgCol++) {
      if (lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol] > maxValue)
      {
        imgRow = imgCol;
        maxValue = lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol];
      }
    }

    imgIdx = imgRow % 163;
    imgCol = imgRow / 163;
    if (lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgRow] >=
        lanedetection_rgb_P.FindLocalMaxima_threshold) {
      lanedetection_rgb_B.FindLocalMaxima_o1[m] = 1.0F + (real32_T)imgCol;
      lanedetection_rgb_B.FindLocalMaxima_o1[2U + m] = (real32_T)(1 + imgIdx);
      m++;
      if (m == 2) {
        b1 = true;
      }

      imgRow = imgIdx - 22;
      if (!(imgRow > 0)) {
        imgRow = 0;
      }

      imgIdx += 22;
      if (!(imgIdx < 162)) {
        imgIdx = 162;
      }

      q1 = imgCol - 12;
      q2 = imgCol + 12;
      if (!((q1 < 0) || (q2 > 89))) {
        while (q1 <= q2) {
          lanedetection_rgb_B.jRowsIn = q1 * 163;
          for (imgCol = imgRow; imgCol <= imgIdx; imgCol++) {
            lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol +
              lanedetection_rgb_B.jRowsIn] = 0.0F;
          }

          q1++;
        }
      } else {
        if (q1 < 0) {
          lanedetection_rgb_B.idxRow2 = q1;
          while (lanedetection_rgb_B.idxRow2 <= q2) {
            if (lanedetection_rgb_B.idxRow2 < 0) {
              lanedetection_rgb_B.jRowsIn = (lanedetection_rgb_B.idxRow2 + 90) *
                163 + 162;
              for (imgCol = imgRow; imgCol <= imgIdx; imgCol++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lanedetection_rgb_B.jRowsIn
                  - imgCol] = 0.0F;
              }
            } else {
              lanedetection_rgb_B.jRowsIn = lanedetection_rgb_B.idxRow2 * 163;
              for (imgCol = imgRow; imgCol <= imgIdx; imgCol++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol +
                  lanedetection_rgb_B.jRowsIn] = 0.0F;
              }
            }

            lanedetection_rgb_B.idxRow2++;
          }
        }

        if (q2 > 89) {
          lanedetection_rgb_B.idxRow2 = q1;
          while (lanedetection_rgb_B.idxRow2 <= q2) {
            if (lanedetection_rgb_B.idxRow2 > 89) {
              lanedetection_rgb_B.jRowsIn = (lanedetection_rgb_B.idxRow2 - 90) *
                163 + 162;
              for (imgCol = imgRow; imgCol <= imgIdx; imgCol++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lanedetection_rgb_B.jRowsIn
                  - imgCol] = 0.0F;
              }
            } else {
              lanedetection_rgb_B.jRowsIn = lanedetection_rgb_B.idxRow2 * 163;
              for (imgCol = imgRow; imgCol <= imgIdx; imgCol++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol +
                  lanedetection_rgb_B.jRowsIn] = 0.0F;
              }
            }

            lanedetection_rgb_B.idxRow2++;
          }
        }
      }
    } else {
      b1 = true;
    }
  }

  lanedetection_rgb_B.FindLocalMaxima_o2 = (real32_T)m;

  /* End of S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix1' */
  lanedetection_rgb_B.Submatrix1[0] = lanedetection_rgb_B.FindLocalMaxima_o1[0];
  lanedetection_rgb_B.Submatrix1[1] = lanedetection_rgb_B.FindLocalMaxima_o1[1];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_rgb_B.Submatrix[0] = lanedetection_rgb_B.FindLocalMaxima_o1[2];
  lanedetection_rgb_B.Submatrix[1] = lanedetection_rgb_B.FindLocalMaxima_o1[3];

  /* S-Function (sviphoughlines): '<Root>/Hough Lines' incorporates:
   *  Selector: '<Root>/Selector'
   *  Selector: '<Root>/Selector1'
   */
  imgCol = 0;
  maxValue = (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
              lanedetection_rgb_B.Submatrix[0] - 1] + 1.1920929E-7F) /
    ((real32_T)cos(lanedetection_rgb_B.HoughTransform_o2[(int32_T)
                   lanedetection_rgb_B.Submatrix1[0] - 1]) + 1.1920929E-7F);

  /* part-1: top horizontal axis */
  lanedetection_rgb_B.tmpRound = (real32_T)floor(maxValue + 0.5F);
  if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
       69.0F)) {
    lanedetection_rgb_B.tmpOutRC[0U] = 0;
    if (lanedetection_rgb_B.tmpRound >= 0.5F) {
      lanedetection_rgb_B.tmpOutRC[1U] = (int32_T)(real32_T)floor
        (lanedetection_rgb_B.tmpRound + 0.5F);
    } else {
      lanedetection_rgb_B.tmpOutRC[1U] = (int32_T)(lanedetection_rgb_B.tmpRound *
        0.0F);
    }

    imgCol = 1;
  }

  lanedetection_rgb_B.y2 = (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
    lanedetection_rgb_B.Submatrix[0] - 1] + 1.1920929E-7F) / ((real32_T)sin
    (lanedetection_rgb_B.HoughTransform_o2[(int32_T)
     lanedetection_rgb_B.Submatrix1[0] - 1]) + 1.1920929E-7F);

  /* part-2: left vertical axis */
  lanedetection_rgb_B.tmpRound = (real32_T)floor(lanedetection_rgb_B.y2 + 0.5F);
  if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
       315.0F)) {
    if (lanedetection_rgb_B.tmpRound >= 0.5F) {
      lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
        (lanedetection_rgb_B.tmpRound + 0.5F);
    } else {
      lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)
        (lanedetection_rgb_B.tmpRound * 0.0F);
    }

    lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = 0;
    imgCol++;
  }

  /* part-3: Right vertical axis */
  if (imgCol < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - 69.0F) *
      (lanedetection_rgb_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         315.0F)) {
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
          (lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = 69;
      imgCol++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (imgCol < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_rgb_B.y2 * 315.0F) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         69.0F)) {
      lanedetection_rgb_B.tmpOutRC[imgCol << 1] = 315;
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)(real32_T)
          floor(lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      imgCol++;
    }
  }

  if (imgCol < 2) {
    lanedetection_rgb_B.tmpOutRC[0U] = -1;
    lanedetection_rgb_B.tmpOutRC[1U] = -1;
    lanedetection_rgb_B.tmpOutRC[2U] = -1;
    lanedetection_rgb_B.tmpOutRC[3U] = -1;
  }

  lanedetection_rgb_B.HoughLines[0] = lanedetection_rgb_B.tmpOutRC[1] + 1;
  lanedetection_rgb_B.HoughLines[2] = lanedetection_rgb_B.tmpOutRC[0] + 1;
  lanedetection_rgb_B.HoughLines[4] = lanedetection_rgb_B.tmpOutRC[3] + 1;
  lanedetection_rgb_B.HoughLines[6] = lanedetection_rgb_B.tmpOutRC[2] + 1;
  imgCol = 0;
  maxValue = (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
              lanedetection_rgb_B.Submatrix[1] - 1] + 1.1920929E-7F) /
    ((real32_T)cos(lanedetection_rgb_B.HoughTransform_o2[(int32_T)
                   lanedetection_rgb_B.Submatrix1[1] - 1]) + 1.1920929E-7F);

  /* part-1: top horizontal axis */
  lanedetection_rgb_B.tmpRound = (real32_T)floor(maxValue + 0.5F);
  if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
       69.0F)) {
    lanedetection_rgb_B.tmpOutRC[0U] = 0;
    if (lanedetection_rgb_B.tmpRound >= 0.5F) {
      lanedetection_rgb_B.tmpOutRC[1U] = (int32_T)(real32_T)floor
        (lanedetection_rgb_B.tmpRound + 0.5F);
    } else {
      lanedetection_rgb_B.tmpOutRC[1U] = (int32_T)(lanedetection_rgb_B.tmpRound *
        0.0F);
    }

    imgCol = 1;
  }

  lanedetection_rgb_B.y2 = (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
    lanedetection_rgb_B.Submatrix[1] - 1] + 1.1920929E-7F) / ((real32_T)sin
    (lanedetection_rgb_B.HoughTransform_o2[(int32_T)
     lanedetection_rgb_B.Submatrix1[1] - 1]) + 1.1920929E-7F);

  /* part-2: left vertical axis */
  lanedetection_rgb_B.tmpRound = (real32_T)floor(lanedetection_rgb_B.y2 + 0.5F);
  if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
       315.0F)) {
    if (lanedetection_rgb_B.tmpRound >= 0.5F) {
      lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
        (lanedetection_rgb_B.tmpRound + 0.5F);
    } else {
      lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)
        (lanedetection_rgb_B.tmpRound * 0.0F);
    }

    lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = 0;
    imgCol++;
  }

  /* part-3: Right vertical axis */
  if (imgCol < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - 69.0F) *
      (lanedetection_rgb_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         315.0F)) {
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
          (lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[imgCol << 1] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = 69;
      imgCol++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (imgCol < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_rgb_B.y2 * 315.0F) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         69.0F)) {
      lanedetection_rgb_B.tmpOutRC[imgCol << 1] = 315;
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)(real32_T)
          floor(lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      imgCol++;
    }
  }

  if (imgCol < 2) {
    lanedetection_rgb_B.tmpOutRC[0U] = -1;
    lanedetection_rgb_B.tmpOutRC[1U] = -1;
    lanedetection_rgb_B.tmpOutRC[2U] = -1;
    lanedetection_rgb_B.tmpOutRC[3U] = -1;
  }

  lanedetection_rgb_B.HoughLines[1] = lanedetection_rgb_B.tmpOutRC[1] + 1;
  lanedetection_rgb_B.HoughLines[3] = lanedetection_rgb_B.tmpOutRC[0] + 1;
  lanedetection_rgb_B.HoughLines[5] = lanedetection_rgb_B.tmpOutRC[3] + 1;
  lanedetection_rgb_B.HoughLines[7] = lanedetection_rgb_B.tmpOutRC[2] + 1;

  /* End of S-Function (sviphoughlines): '<Root>/Hough Lines' */

  /* S-Function (svipdrawshapes): '<Root>/Draw Shapes' */
  if (lanedetection_rgb_P.DrawShapes_lineWidth == 1) {
    /* Compute output for unity line width
     */
    /* Copy the image from input to output. */
    memcpy(&lanedetection_rgb_B.DrawShapes_o1[0], &lanedetection_rgb_B.rOUT[0],
           22120U * sizeof(uint8_T));
    memcpy(&lanedetection_rgb_B.DrawShapes_o2[0], &lanedetection_rgb_B.gOUT[0],
           22120U * sizeof(uint8_T));
    memcpy(&lanedetection_rgb_B.DrawShapes_o3[0], &lanedetection_rgb_B.bOUT[0],
           22120U * sizeof(uint8_T));

    /* Update view port. */
    for (imgCol = 0; imgCol < 2; imgCol++) {
      q2 = lanedetection_rgb_B.HoughLines[imgCol + 2] - 1;
      lanedetection_rgb_B.jRowsIn = lanedetection_rgb_B.HoughLines[imgCol] - 1;
      acc4_idx_0 = lanedetection_rgb_B.HoughLines[imgCol + 6] - 1;
      acc1_idx_5 = lanedetection_rgb_B.HoughLines[4 + imgCol] - 1;
      if ((acc4_idx_0 != q2) || (acc1_idx_5 != lanedetection_rgb_B.jRowsIn)) {
        b2 = false;

        /* Find the visible portion of a line. */
        b3 = false;
        b4 = false;
        b1 = false;
        m = q2;
        imgIdx = lanedetection_rgb_B.jRowsIn;
        imgRow = acc4_idx_0;
        q1 = acc1_idx_5;
        while (!b1) {
          lanedetection_rgb_B.numUniquePix = 0;
          lanedetection_rgb_B.loc = 0;

          /* Determine viewport violations. */
          if (m < 0) {
            lanedetection_rgb_B.numUniquePix = 4;
          } else {
            if (m > 315) {
              lanedetection_rgb_B.numUniquePix = 8;
            }
          }

          if (imgRow < 0) {
            lanedetection_rgb_B.loc = 4;
          } else {
            if (imgRow > 315) {
              lanedetection_rgb_B.loc = 8;
            }
          }

          if (imgIdx < 0) {
            lanedetection_rgb_B.numUniquePix |= 1U;
          } else {
            if (imgIdx > 69) {
              lanedetection_rgb_B.numUniquePix |= 2U;
            }
          }

          if (q1 < 0) {
            lanedetection_rgb_B.loc |= 1U;
          } else {
            if (q1 > 69) {
              lanedetection_rgb_B.loc |= 2U;
            }
          }

          if (!(((uint32_T)lanedetection_rgb_B.numUniquePix |
                 lanedetection_rgb_B.loc) != 0U)) {
            /* Line falls completely within bounds. */
            b1 = true;
            b2 = true;
          } else if (((uint32_T)lanedetection_rgb_B.numUniquePix &
                      lanedetection_rgb_B.loc) != 0U) {
            /* Line falls completely out of bounds. */
            b1 = true;
            b2 = false;
          } else if ((uint32_T)lanedetection_rgb_B.numUniquePix != 0U) {
            /* Clip 1st point; if it's in-bounds, clip 2nd point. */
            if (b3) {
              m = q2;
              imgIdx = lanedetection_rgb_B.jRowsIn;
            }

            lanedetection_rgb_B.idxCol1 = imgRow - m;
            lanedetection_rgb_B.idxCol2 = q1 - imgIdx;
            if ((lanedetection_rgb_B.idxCol1 > 1073741824) ||
                (lanedetection_rgb_B.idxCol1 < -1073741824) ||
                ((lanedetection_rgb_B.idxCol2 > 1073741824) ||
                 (lanedetection_rgb_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              b1 = true;
              b2 = false;
              b3 = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_rgb_B.numUniquePix = -m *
                lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                imgIdx += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              m = 0;
              b3 = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_rgb_B.numUniquePix = (315 - m) *
                lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                imgIdx += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              m = 315;
              b3 = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_rgb_B.numUniquePix = -imgIdx *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                m += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                    lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                m -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                    lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              imgIdx = 0;
              b3 = true;
            } else {
              /* Violated CMax. */
              lanedetection_rgb_B.numUniquePix = (69 - imgIdx) *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                m += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                    lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                m -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                    lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              imgIdx = 69;
              b3 = true;
            }
          } else {
            /* Clip the 2nd point. */
            if (b4) {
              imgRow = acc4_idx_0;
              q1 = acc1_idx_5;
            }

            lanedetection_rgb_B.idxCol1 = imgRow - m;
            lanedetection_rgb_B.idxCol2 = q1 - imgIdx;
            if ((lanedetection_rgb_B.idxCol1 > 1073741824) ||
                (lanedetection_rgb_B.idxCol1 < -1073741824) ||
                ((lanedetection_rgb_B.idxCol2 > 1073741824) ||
                 (lanedetection_rgb_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              b1 = true;
              b2 = false;
              b4 = true;
            } else if ((lanedetection_rgb_B.loc & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_rgb_B.numUniquePix = -imgRow *
                lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                q1 += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                q1 -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              imgRow = 0;
              b4 = true;
            } else if ((lanedetection_rgb_B.loc & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_rgb_B.numUniquePix = (315 - imgRow) *
                lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                q1 += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                q1 -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              imgRow = 315;
              b4 = true;
            } else if ((lanedetection_rgb_B.loc & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_rgb_B.numUniquePix = -q1 *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                imgRow += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                imgRow -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              q1 = 0;
              b4 = true;
            } else {
              /* Violated CMax. */
              lanedetection_rgb_B.numUniquePix = (69 - q1) *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                b1 = true;
                b2 = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                imgRow += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                imgRow -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              q1 = 69;
              b4 = true;
            }
          }
        }

        if (b2) {
          /* Draw a line using Bresenham algorithm. */
          /* Initialize the Bresenham algorithm. */
          if (imgRow >= m) {
            q2 = imgRow - m;
          } else {
            q2 = m - imgRow;
          }

          if (q1 >= imgIdx) {
            lanedetection_rgb_B.jRowsIn = q1 - imgIdx;
          } else {
            lanedetection_rgb_B.jRowsIn = imgIdx - q1;
          }

          if (q2 > lanedetection_rgb_B.jRowsIn) {
            q2 = 1;
            lanedetection_rgb_B.jRowsIn = 316;
          } else {
            q2 = 316;
            lanedetection_rgb_B.jRowsIn = 1;
            acc4_idx_0 = m;
            m = imgIdx;
            imgIdx = acc4_idx_0;
            acc4_idx_0 = imgRow;
            imgRow = q1;
            q1 = acc4_idx_0;
          }

          if (m > imgRow) {
            acc4_idx_0 = m;
            m = imgRow;
            imgRow = acc4_idx_0;
            acc4_idx_0 = imgIdx;
            imgIdx = q1;
            q1 = acc4_idx_0;
          }

          acc4_idx_0 = imgRow - m;
          if (imgIdx <= q1) {
            acc1_idx_5 = 1;
            q1 -= imgIdx;
          } else {
            acc1_idx_5 = -1;
            q1 = imgIdx - q1;
          }

          lanedetection_rgb_B.idxCol1 = -((acc4_idx_0 + 1) >> 1);
          imgIdx = m * q2 + imgIdx * lanedetection_rgb_B.jRowsIn;
          lanedetection_rgb_B.jRowsIn = acc1_idx_5 * lanedetection_rgb_B.jRowsIn
            + q2;
          b1 = (m <= imgRow);
          while (b1) {
            lanedetection_rgb_B.DrawShapes_o1[imgIdx] =
              lanedetection_rgb_P.DrawShapes_color[0];
            lanedetection_rgb_B.DrawShapes_o2[imgIdx] =
              lanedetection_rgb_P.DrawShapes_color[1];
            lanedetection_rgb_B.DrawShapes_o3[imgIdx] =
              lanedetection_rgb_P.DrawShapes_color[2];

            /* Compute the next location using Bresenham algorithm. */
            /* Move to the next pixel location. */
            lanedetection_rgb_B.idxCol1 += q1;
            if (lanedetection_rgb_B.idxCol1 >= 0) {
              lanedetection_rgb_B.idxCol1 -= acc4_idx_0;
              imgIdx += lanedetection_rgb_B.jRowsIn;
            } else {
              imgIdx += q2;
            }

            m++;
            b1 = (m <= imgRow);
          }
        }
      }
    }
  } else {
    /* Compute output for non-unity line width
     */
    /* Copy the image from input to output. */
    memcpy(&lanedetection_rgb_B.DrawShapes_o1[0], &lanedetection_rgb_B.rOUT[0],
           22120U * sizeof(uint8_T));
    memcpy(&lanedetection_rgb_B.DrawShapes_o2[0], &lanedetection_rgb_B.gOUT[0],
           22120U * sizeof(uint8_T));
    memcpy(&lanedetection_rgb_B.DrawShapes_o3[0], &lanedetection_rgb_B.bOUT[0],
           22120U * sizeof(uint8_T));

    /* Update view port. */
    /* ProcessStep-start-1
     */
    if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
      /* convertLinePts2PolygonPts
       */
      imgCol = lanedetection_rgb_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      m = lanedetection_rgb_B.HoughLines[2] - lanedetection_rgb_B.HoughLines[6];
      imgRow = lanedetection_rgb_B.HoughLines[0] -
        lanedetection_rgb_B.HoughLines[4];
      if (imgRow == 0) {
        q1 = 0;
        imgIdx = 1;
        q2 = ((lanedetection_rgb_B.HoughLines[0] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[0] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[2] - 1) << 14;
      } else if (m == 0) {
        imgIdx = 2;
        q1 = 0;
        q2 = ((lanedetection_rgb_B.HoughLines[2] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[2] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[0] - 1) << 14;
      } else {
        imgIdx = 0;
        q1 = div_repeat_s32_floor(m << 14, imgRow << 14, 14U);
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[2] - 1) <<
          14) - mul_s32_loSR((lanedetection_rgb_B.HoughLines[0] - 1) << 14, q1,
                             14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgRow << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((m * m + imgRow *
          imgRow) << 14) << 7, 14U), 14U);
        q2 = lanedetection_rgb_B.jRowsIn + acc4_idx_0;
        lanedetection_rgb_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[0] - 1)
          << 14, q1, 14U) + ((lanedetection_rgb_B.HoughLines[2] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (imgIdx == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((q2 & 8192U) != 0U) +
          (q2 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[2] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[12] =
          ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_rgb_B.jRowsIn >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[14] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
      } else {
        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[2] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[2] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        }

        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[14] =
            ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_rgb_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_rgb_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) + lanedetection_rgb_B.jRowsIn;
          lanedetection_rgb_DW.DrawShapes_DW_Points[14] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
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
      if (imgRow == 0) {
        q1 = 0;
        imgIdx = 1;
        q2 = ((lanedetection_rgb_B.HoughLines[0] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[0] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[6] - 1) << 14;
      } else if (m == 0) {
        imgIdx = 2;
        q1 = 0;
        q2 = ((lanedetection_rgb_B.HoughLines[2] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[2] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[4] - 1) << 14;
      } else {
        imgIdx = 0;
        q1 = div_repeat_s32_floor(m << 14, imgRow << 14, 14U);
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[2] - 1) <<
          14) - mul_s32_loSR((lanedetection_rgb_B.HoughLines[0] - 1) << 14, q1,
                             14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgRow << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((m * m + imgRow *
          imgRow) << 14) << 7, 14U), 14U);
        q2 = lanedetection_rgb_B.jRowsIn + acc4_idx_0;
        lanedetection_rgb_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[4] - 1)
          << 14, q1, 14U) + ((lanedetection_rgb_B.HoughLines[6] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (imgIdx == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((q2 & 8192U) != 0U) +
          (q2 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[6] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[8] =
          ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_rgb_B.jRowsIn >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[10] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
      } else {
        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[6] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[6] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        }

        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[10] =
            ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_rgb_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_rgb_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) + lanedetection_rgb_B.jRowsIn;
          lanedetection_rgb_DW.DrawShapes_DW_Points[10] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      imgCol = lanedetection_rgb_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      m = lanedetection_rgb_B.HoughLines[3] - lanedetection_rgb_B.HoughLines[7];
      imgRow = lanedetection_rgb_B.HoughLines[1] -
        lanedetection_rgb_B.HoughLines[5];
      if (imgRow == 0) {
        q1 = 0;
        imgIdx = 1;
        q2 = ((lanedetection_rgb_B.HoughLines[1] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[1] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[3] - 1) << 14;
      } else if (m == 0) {
        imgIdx = 2;
        q1 = 0;
        q2 = ((lanedetection_rgb_B.HoughLines[3] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[3] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[1] - 1) << 14;
      } else {
        imgIdx = 0;
        q1 = div_repeat_s32_floor(m << 14, imgRow << 14, 14U);
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[3] - 1) <<
          14) - mul_s32_loSR((lanedetection_rgb_B.HoughLines[1] - 1) << 14, q1,
                             14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgRow << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((m * m + imgRow *
          imgRow) << 14) << 7, 14U), 14U);
        q2 = lanedetection_rgb_B.jRowsIn + acc4_idx_0;
        lanedetection_rgb_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[1] - 1)
          << 14, q1, 14U) + ((lanedetection_rgb_B.HoughLines[3] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (imgIdx == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((q2 & 8192U) != 0U) +
          (q2 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[3] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[13] =
          ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_rgb_B.jRowsIn >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[15] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
      } else {
        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[3] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[3] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        }

        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[15] =
            ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_rgb_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_rgb_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) + lanedetection_rgb_B.jRowsIn;
          lanedetection_rgb_DW.DrawShapes_DW_Points[15] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
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
      if (imgRow == 0) {
        q1 = 0;
        imgIdx = 1;
        q2 = ((lanedetection_rgb_B.HoughLines[1] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[1] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[7] - 1) << 14;
      } else if (m == 0) {
        imgIdx = 2;
        q1 = 0;
        q2 = ((lanedetection_rgb_B.HoughLines[3] - imgCol) - 1) << 14;
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[3] +
          imgCol) - 1) << 14;
        acc4_idx_0 = (lanedetection_rgb_B.HoughLines[5] - 1) << 14;
      } else {
        imgIdx = 0;
        q1 = div_repeat_s32_floor(m << 14, imgRow << 14, 14U);
        lanedetection_rgb_B.jRowsIn = ((lanedetection_rgb_B.HoughLines[3] - 1) <<
          14) - mul_s32_loSR((lanedetection_rgb_B.HoughLines[1] - 1) << 14, q1,
                             14U);
        acc4_idx_0 = div_repeat_s32_floor(imgCol << 14, div_repeat_s32_floor
          (imgRow << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((m * m + imgRow *
          imgRow) << 14) << 7, 14U), 14U);
        q2 = lanedetection_rgb_B.jRowsIn + acc4_idx_0;
        lanedetection_rgb_B.jRowsIn -= acc4_idx_0;
        acc4_idx_0 = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[5] - 1)
          << 14, q1, 14U) + ((lanedetection_rgb_B.HoughLines[7] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (imgIdx == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((q2 & 8192U) != 0U) +
          (q2 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[7] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[9] =
          ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
          (lanedetection_rgb_B.jRowsIn >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[11] = ((acc4_idx_0 & 8192U) !=
          0U) + (acc4_idx_0 >> 14);
      } else {
        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[7] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 - q2, q1,
            14U), mul_s32_loSR(q1, q1, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 += mul_s32_loSR(q1, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[7] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        }

        if (imgIdx == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((acc4_idx_0 & 8192U)
            != 0U) + (acc4_idx_0 >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[11] =
            ((lanedetection_rgb_B.jRowsIn & 8192U) != 0U) +
            (lanedetection_rgb_B.jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(acc4_idx_0 -
            lanedetection_rgb_B.jRowsIn, q1, 14U), mul_s32_loSR(q1, q1, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          q2 = mul_s32_loSR(q1, acc1_idx_5, 14U) + lanedetection_rgb_B.jRowsIn;
          lanedetection_rgb_DW.DrawShapes_DW_Points[11] = ((q2 & 8192U) != 0U) +
            (q2 >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
    }

    /* ProcessStep-after poly points-1
     */
    m = 2;

    /* just before call for cgpolygon
     */
    if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
      /* just before call for cgpolygon-2
       */
      m = 4;
    }

    imgRow = m << 1;

    /* Reset scanline states. */
    imgIdx = 0;
    q1 = 0;
    idxTmpArray[0U] = (int8_T)(m - 1);
    b2 = true;
    while (b2) {
      /* Initialize the scanline. */
      /* Convert polygon vertices to boundaries. */
      q2 = 0;
      lanedetection_rgb_B.jRowsIn = imgIdx;
      acc4_idx_0 = imgIdx;

      /* start for loop
       */
      acc1_idx_5 = (((idxTmpArray[0] << 1) + 1) << 1) + q1;
      lanedetection_rgb_B.idxCol1 = (idxTmpArray[0] << 2) + q1;
      lanedetection_rgb_B.idxTmp = idxTmpArray[0];
      lanedetection_rgb_B.idxCol2 = ((idxTmpArray[0] - 1) << 2) + q1;
      lanedetection_rgb_B.numUniquePix = m;
      if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];

        /* getLoc-1
         */
        imgCol =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];

        /* getLoc-2
         */
        imgCol = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];
      }

      while ((lanedetection_rgb_B.idxCol2 >= 0) && (lanedetection_rgb_B.loc - 1 ==
              imgCol - 1)) {
        lanedetection_rgb_B.idxTmp--;
        lanedetection_rgb_B.idxCol2 = ((lanedetection_rgb_B.idxTmp - 1) << 2) +
          q1;
        lanedetection_rgb_B.numUniquePix--;
        if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          imgCol =
            lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];
        } else {
          /* getLoc-2
           */
          imgCol = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];
        }
      }

      if (lanedetection_rgb_B.idxCol2 < 0) {
        lanedetection_rgb_B.idxCol2 = 0;
      }

      if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];

        /* getLoc-1
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];

        /* getLoc-2
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];
      }

      b1 = (lanedetection_rgb_B.loc_m - 1 > lanedetection_rgb_B.loc - 1);
      lanedetection_rgb_B.idxRow2 = 2 + q1;
      lanedetection_rgb_B.idxCol2 = q1;
      b3 = false;
      if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_rgb_B.loc = lanedetection_rgb_DW.DrawShapes_DW_Points[q1];

        /* getLoc-1
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];
      } else {
        /* getLoc-2
         */
        lanedetection_rgb_B.loc = lanedetection_rgb_B.HoughLines[q1];

        /* getLoc-2
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];
      }

      for (imgCol = 0; imgCol < lanedetection_rgb_B.numUniquePix; imgCol++) {
        if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          lanedetection_rgb_B.idxTmp =
            lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];

          /* getLoc-1
           */
          lanedetection_rgb_B.numActiveEdge =
            lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];
        } else {
          /* getLoc-2
           */
          lanedetection_rgb_B.idxTmp =
            lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];

          /* getLoc-2
           */
          lanedetection_rgb_B.numActiveEdge =
            lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];
        }

        if (lanedetection_rgb_B.numActiveEdge - 1 != lanedetection_rgb_B.idxTmp
            - 1) {
          if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_rgb_B.idxTmp =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_rgb_B.numActiveEdge =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];
          } else {
            /* getLoc-2
             */
            lanedetection_rgb_B.idxTmp =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_rgb_B.numActiveEdge =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];
          }

          if (lanedetection_rgb_B.numActiveEdge - 1 < lanedetection_rgb_B.idxTmp
              - 1) {
            b2 = false;
          } else {
            b2 = true;
            lanedetection_rgb_B.idxTmp = acc1_idx_5;
            acc1_idx_5 = lanedetection_rgb_B.idxRow2;
            lanedetection_rgb_B.idxRow2 = lanedetection_rgb_B.idxTmp;
            lanedetection_rgb_B.idxTmp = lanedetection_rgb_B.idxCol1;
            lanedetection_rgb_B.idxCol1 = lanedetection_rgb_B.idxCol2;
            lanedetection_rgb_B.idxCol2 = lanedetection_rgb_B.idxTmp;
          }

          if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_rgb_B.idxTmp =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_rgb_B.numActiveEdge =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxRow2];

            /* getLoc-1
             */
            lanedetection_rgb_B.idxNew =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];

            /* getLoc-1
             */
            lanedetection_rgb_B.idxOld =
              lanedetection_rgb_DW.DrawShapes_DW_Points[acc1_idx_5];
          } else {
            /* getLoc-2
             */
            lanedetection_rgb_B.idxTmp =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_rgb_B.numActiveEdge =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxRow2];

            /* getLoc-2
             */
            lanedetection_rgb_B.idxNew =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];

            /* getLoc-2
             */
            lanedetection_rgb_B.idxOld =
              lanedetection_rgb_B.HoughLines[acc1_idx_5];
          }

          /* Initialize a Bresenham line. */
          edgeTmp_tmp = lanedetection_rgb_B.idxTmp - lanedetection_rgb_B.idxNew;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0] = 0;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 1] =
            lanedetection_rgb_B.idxOld - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 2] =
            lanedetection_rgb_B.idxNew - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 3] =
            lanedetection_rgb_B.idxTmp - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6] = 0;
          if (lanedetection_rgb_B.numActiveEdge - 1 >=
              lanedetection_rgb_B.idxOld - 1) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] =
              lanedetection_rgb_B.numActiveEdge - lanedetection_rgb_B.idxOld;
          } else {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] =
              lanedetection_rgb_B.idxOld - lanedetection_rgb_B.numActiveEdge;
          }

          while (lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] >= 0)
          {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6]++;
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] -=
              edgeTmp_tmp;
          }

          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5] =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6] - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 7] =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8] +
            edgeTmp_tmp;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 4] =
            edgeTmp_tmp - (lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0
                           + 7] << 1);
          if (lanedetection_rgb_B.idxOld - 1 > lanedetection_rgb_B.numActiveEdge
              - 1) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5] =
              -lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5];
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6] =
              -lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6];
          }

          if ((!b1) && (!b2)) {
            /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 2]++;
            if ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0] << 1) >
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 4]) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 8];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 1] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 6];
            } else {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 7];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 1] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 5];
            }
          } else {
            if (b1 && b2) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 3]--;
            }
          }

          b1 = b2;
          if (!b3) {
            /* Merge two Bresenham lines. */
            b3 = false;
            if ((lanedetection_rgb_B.jRowsIn != acc4_idx_0) &&
                ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                  + 5] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0
                  + 5]) &&
                 (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                  + 6] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0
                  + 6]) &&
                 (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                  + 7] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0
                  + 7]) &&
                 (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                  + 8] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0
                  + 8]))) {
              if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                  + 3] + 1 ==
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 2]) {
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                  + 3] = lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 +
                  3];
                b3 = true;
              } else {
                if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 3] +
                    1 ==
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                    + 2]) {
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                    + 1] = lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0
                    + 1];
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                    + 2] = lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0
                    + 2];
                  b3 = true;
                }
              }
            }

            if (!b3) {
              lanedetection_rgb_B.jRowsIn = acc4_idx_0;
              q2++;
            }
          } else {
            lanedetection_rgb_B.jRowsIn = acc4_idx_0;
            q2++;
          }

          acc4_idx_0 = lanedetection_rgb_B.jRowsIn + 9;
          if (!b2) {
            acc1_idx_5 = lanedetection_rgb_B.idxRow2;
            lanedetection_rgb_B.idxCol1 = lanedetection_rgb_B.idxCol2;
          }

          lanedetection_rgb_B.idxRow2 = acc1_idx_5 + 4;
          lanedetection_rgb_B.idxCol2 = lanedetection_rgb_B.idxCol1 + 4;
          b3 = false;
        } else {
          b3 = true;
          acc1_idx_5 = lanedetection_rgb_B.idxRow2;
          lanedetection_rgb_B.idxCol1 = lanedetection_rgb_B.idxCol2;
          lanedetection_rgb_B.idxRow2 += 4;
          lanedetection_rgb_B.idxCol2 += 4;
        }
      }

      if (!(lanedetection_rgb_B.loc_m - 1 == lanedetection_rgb_B.loc - 1)) {
        /* Merge two Bresenham lines. */
        b1 = false;
        if ((imgIdx != lanedetection_rgb_B.jRowsIn) &&
            ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 5] ==
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
              + 5]) && (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 6] ==
                        lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                        + 6]) &&
             (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 7] ==
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
              + 7]) && (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 8] ==
                        lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                        + 8]))) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 3] + 1 ==
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
              + 2]) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 3] =
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
              + 3];
            b1 = true;
          } else {
            if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                + 3] + 1 == lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx +
                2]) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 1] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                + 1];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 2] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.jRowsIn
                + 2];
              b1 = true;
            }
          }
        }

        if (b1) {
          q2--;
          acc4_idx_0 -= 9;
        }
      }

      /* Set all other edges to invalid. */
      for (imgCol = q2; imgCol < m; imgCol++) {
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 2] = 1;
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc4_idx_0 + 3] = 0;
        acc4_idx_0 += 9;
      }

      /* Sort the boundaries of the polygon. */
      b2 = true;
      while (b2) {
        lanedetection_rgb_B.idxNew = imgIdx;
        lanedetection_rgb_B.idxOld = imgIdx + 9;
        b2 = false;
        for (imgCol = 1; imgCol < q2; imgCol++) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
              + 2] >
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
              + 2]) {
            b2 = true;
            for (lanedetection_rgb_B.idxRow2 = 0; lanedetection_rgb_B.idxRow2 <
                 9; lanedetection_rgb_B.idxRow2++) {
              edgeTmp_tmp = lanedetection_rgb_B.idxNew +
                lanedetection_rgb_B.idxRow2;
              lanedetection_rgb_B.edgeTmp =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_rgb_B.idxOld +
                lanedetection_rgb_B.idxRow2;
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                = lanedetection_rgb_B.edgeTmp;
            }
          }

          lanedetection_rgb_B.idxNew = lanedetection_rgb_B.idxOld;
          lanedetection_rgb_B.idxOld += 9;
        }
      }

      /* Find out the last column of the polygon. */
      acc1_idx_5 = imgIdx + 3;
      lanedetection_rgb_B.jRowsIn =
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 3];
      for (imgCol = 1; imgCol < q2; imgCol++) {
        acc1_idx_5 += 9;
        if (lanedetection_rgb_B.jRowsIn <
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc1_idx_5]) {
          lanedetection_rgb_B.jRowsIn =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc1_idx_5];
        }
      }

      acc4_idx_0 = lanedetection_rgb_B.jRowsIn;
      if (lanedetection_rgb_B.jRowsIn > 69) {
        acc4_idx_0 = 69;
      }

      /* Find out the first column of the polygon. */
      acc1_idx_5 = imgIdx + 2;
      lanedetection_rgb_B.jRowsIn =
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 2];
      for (imgCol = 1; imgCol < q2; imgCol++) {
        acc1_idx_5 += 9;
        if (lanedetection_rgb_B.jRowsIn >
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc1_idx_5]) {
          lanedetection_rgb_B.jRowsIn =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[acc1_idx_5];
        }
      }

      if (lanedetection_rgb_B.jRowsIn < 0) {
        lanedetection_rgb_B.jRowsIn = 0;
      }

      /* Move to the next column and find out boundaries of the polygon at this column. */
      lanedetection_rgb_B.idxNew = imgIdx;
      lanedetection_rgb_B.idxOld = imgIdx;
      acc1_idx_5 = imgIdx;
      lanedetection_rgb_B.idxCol1 = 0;
      lanedetection_rgb_B.numActiveEdge = 0;
      for (imgCol = 0; imgCol < q2; imgCol++) {
        /* Find out the valid boundaries and bring them to the latest column. */
        if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
            + 3] >= lanedetection_rgb_B.jRowsIn) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
              + 2] <= lanedetection_rgb_B.jRowsIn) {
            while
                (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                 + 2] < lanedetection_rgb_B.jRowsIn) {
              /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                + 2]++;
              if ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld]
                   << 1) >
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 4]) {
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld]
                  +=
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 8];
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 1] +=
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 6];
              } else {
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld]
                  +=
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 7];
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 1] +=
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 5];
              }
            }

            acc1_idx_5 += 9;
            lanedetection_rgb_B.numActiveEdge++;
          }

          if (lanedetection_rgb_B.idxOld != lanedetection_rgb_B.idxNew) {
            for (lanedetection_rgb_B.idxRow2 = 0; lanedetection_rgb_B.idxRow2 <
                 9; lanedetection_rgb_B.idxRow2++) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
                + lanedetection_rgb_B.idxRow2] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                + lanedetection_rgb_B.idxRow2];
            }
          }

          lanedetection_rgb_B.idxNew += 9;
          lanedetection_rgb_B.idxCol1++;
        }

        lanedetection_rgb_B.idxOld += 9;
      }

      /* Sort the boundaries of the polygon according to row values. */
      /* Sort the boundaries of the polygon. */
      b2 = true;
      while (b2) {
        lanedetection_rgb_B.idxNew = imgIdx;
        lanedetection_rgb_B.idxOld = imgIdx + 9;
        b2 = false;
        for (imgCol = 1; imgCol < lanedetection_rgb_B.numActiveEdge; imgCol++) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
              + 1] >
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
              + 1]) {
            b2 = true;
            for (lanedetection_rgb_B.idxRow2 = 0; lanedetection_rgb_B.idxRow2 <
                 9; lanedetection_rgb_B.idxRow2++) {
              edgeTmp_tmp = lanedetection_rgb_B.idxNew +
                lanedetection_rgb_B.idxRow2;
              lanedetection_rgb_B.edgeTmp =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_rgb_B.idxOld +
                lanedetection_rgb_B.idxRow2;
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                = lanedetection_rgb_B.edgeTmp;
            }
          }

          lanedetection_rgb_B.idxNew = lanedetection_rgb_B.idxOld;
          lanedetection_rgb_B.idxOld += 9;
        }
      }

      q2 = imgIdx;
      lanedetection_rgb_B.idxCol2 = lanedetection_rgb_B.jRowsIn + 1;
      lanedetection_rgb_B.numUniquePix = 0;
      lanedetection_rgb_B.idxRow2 = 0;
      lanedetection_rgb_B.numActiveEdge = -1;
      b2 = (0 <= acc4_idx_0);
      while (b2) {
        /* Get a string of pixels */
        b3 = false;
        b1 = (lanedetection_rgb_B.idxRow2 != 0);
        lanedetection_rgb_B.idxTmp = lanedetection_rgb_B.numUniquePix;
        if ((lanedetection_rgb_B.numUniquePix >= lanedetection_rgb_B.jRowsIn) &&
            (lanedetection_rgb_B.numUniquePix <= acc4_idx_0)) {
          if (q2 < acc1_idx_5) {
            imgCol = lanedetection_rgb_DW.DrawShapes_DW_Polygon[q2 + 1];
            q2 += 9;
            if ((imgCol == lanedetection_rgb_B.numActiveEdge) && (q2 <
                 acc1_idx_5)) {
              lanedetection_rgb_B.loc =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[q2 + 1];
              b2 = (q2 < acc1_idx_5);
              while (b2 && (imgCol == lanedetection_rgb_B.loc)) {
                b3 = true;
                imgCol = lanedetection_rgb_DW.DrawShapes_DW_Polygon[q2 + 1];
                q2 += 9;
                b2 = (q2 < acc1_idx_5);
                if (b2) {
                  lanedetection_rgb_B.loc =
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[q2 + 1];
                }
              }

              if (!b2) {
                b3 = false;
              }
            }

            if (lanedetection_rgb_B.idxRow2 != 0) {
              lanedetection_rgb_B.loc = lanedetection_rgb_B.numActiveEdge;
              if (imgCol <= 315) {
                lanedetection_rgb_B.loc_m = imgCol;
                lanedetection_rgb_B.numActiveEdge = imgCol;
              } else {
                lanedetection_rgb_B.loc_m = 315;
                lanedetection_rgb_B.numActiveEdge = 315;
              }
            } else {
              lanedetection_rgb_B.loc = lanedetection_rgb_B.numActiveEdge + 1;
              if ((imgCol > 0) && (imgCol <= 315)) {
                lanedetection_rgb_B.loc_m = imgCol - 1;
                lanedetection_rgb_B.numActiveEdge = imgCol;
              } else if (imgCol <= 0) {
                lanedetection_rgb_B.loc_m = -1;
                lanedetection_rgb_B.numActiveEdge = 0;
              } else {
                lanedetection_rgb_B.loc_m = 315;
                lanedetection_rgb_B.numActiveEdge = 316;
              }
            }

            if (!b3) {
              lanedetection_rgb_B.idxRow2 = !(lanedetection_rgb_B.idxRow2 != 0);
            }
          } else {
            /* Reset states and move to the next column. */
            b1 = false;
            lanedetection_rgb_B.loc = lanedetection_rgb_B.numActiveEdge + 1;
            lanedetection_rgb_B.loc_m = 315;

            /* Move to the next column and find out boundaries of the polygon at this column. */
            lanedetection_rgb_B.idxNew = imgIdx;
            lanedetection_rgb_B.idxOld = imgIdx;
            acc1_idx_5 = imgIdx;
            q2 = 0;
            lanedetection_rgb_B.numActiveEdge = 0;
            for (imgCol = 0; imgCol < lanedetection_rgb_B.idxCol1; imgCol++) {
              /* Find out the valid boundaries and bring them to the latest column. */
              if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 3] >= lanedetection_rgb_B.idxCol2) {
                if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                    + 2] <= lanedetection_rgb_B.idxCol2) {
                  while
                      (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                       + 2] < lanedetection_rgb_B.idxCol2) {
                    /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                      + 2]++;
                    if ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld]
                         << 1) >
                        lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                        + 4]) {
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld]
                        +=
                        lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                        + 8];
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                        + 1] +=
                        lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                        + 6];
                    } else {
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld]
                        +=
                        lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                        + 7];
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                        + 1] +=
                        lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                        + 5];
                    }
                  }

                  acc1_idx_5 += 9;
                  lanedetection_rgb_B.numActiveEdge++;
                }

                if (lanedetection_rgb_B.idxOld != lanedetection_rgb_B.idxNew) {
                  for (lanedetection_rgb_B.idxRow2 = 0;
                       lanedetection_rgb_B.idxRow2 < 9;
                       lanedetection_rgb_B.idxRow2++) {
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
                      + lanedetection_rgb_B.idxRow2] =
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                      + lanedetection_rgb_B.idxRow2];
                  }
                }

                lanedetection_rgb_B.idxNew += 9;
                q2++;
              }

              lanedetection_rgb_B.idxOld += 9;
            }

            lanedetection_rgb_B.idxCol1 = q2;

            /* Sort the boundaries of the polygon according to row values. */
            /* Sort the boundaries of the polygon. */
            b2 = true;
            while (b2) {
              lanedetection_rgb_B.idxNew = imgIdx;
              lanedetection_rgb_B.idxOld = imgIdx + 9;
              b2 = false;
              for (imgCol = 1; imgCol < lanedetection_rgb_B.numActiveEdge;
                   imgCol++) {
                if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
                    + 1] >
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                    + 1]) {
                  b2 = true;
                  for (lanedetection_rgb_B.idxRow2 = 0;
                       lanedetection_rgb_B.idxRow2 < 9;
                       lanedetection_rgb_B.idxRow2++) {
                    edgeTmp_tmp = lanedetection_rgb_B.idxNew +
                      lanedetection_rgb_B.idxRow2;
                    lanedetection_rgb_B.edgeTmp =
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
                    DrawShapes_DW_Polygon_tmp = lanedetection_rgb_B.idxOld +
                      lanedetection_rgb_B.idxRow2;
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                      = lanedetection_rgb_B.edgeTmp;
                  }
                }

                lanedetection_rgb_B.idxNew = lanedetection_rgb_B.idxOld;
                lanedetection_rgb_B.idxOld += 9;
              }
            }

            q2 = imgIdx;
            lanedetection_rgb_B.idxCol2++;
            lanedetection_rgb_B.idxRow2 = 0;
            lanedetection_rgb_B.numActiveEdge = -1;
            lanedetection_rgb_B.numUniquePix++;
          }
        } else {
          lanedetection_rgb_B.loc = 0;
          lanedetection_rgb_B.loc_m = 315;
          lanedetection_rgb_B.numUniquePix++;
        }

        if (lanedetection_rgb_B.loc < 0) {
          lanedetection_rgb_B.loc = 0;
        }

        if (lanedetection_rgb_B.loc_m < lanedetection_rgb_B.loc) {
          lanedetection_rgb_B.loc_m = lanedetection_rgb_B.loc - 1;
        }

        if (b1) {
          lanedetection_rgb_B.idxTmp = lanedetection_rgb_B.idxTmp * 316 +
            lanedetection_rgb_B.loc;
          lanedetection_rgb_B.idxNew = 1;
          if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
            lanedetection_rgb_B.idxNew = 0;
          }

          lanedetection_rgb_B.idxOld = lanedetection_rgb_B.idxTmp;
          for (imgCol = lanedetection_rgb_B.loc; imgCol <=
               lanedetection_rgb_B.loc_m; imgCol++) {
            if (lanedetection_rgb_B.idxNew != 0) {
              lanedetection_rgb_B.DrawShapes_o1[lanedetection_rgb_B.idxOld] =
                (uint8_T)(((int32_T)((uint32_T)
                lanedetection_rgb_B.DrawShapes_o1[lanedetection_rgb_B.idxOld] *
                lanedetection_rgb_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_rgb_B.DrawShapes_o1[lanedetection_rgb_B.idxOld] =
                (uint8_T)((uint32_T)
                          lanedetection_rgb_B.DrawShapes_o1[lanedetection_rgb_B.idxOld]
                          + lanedetection_rgb_P.DrawShapes_color[0]);
            } else {
              lanedetection_rgb_B.DrawShapes_o1[lanedetection_rgb_B.idxOld] =
                lanedetection_rgb_P.DrawShapes_color[0];
            }

            lanedetection_rgb_B.idxOld++;
          }

          lanedetection_rgb_B.idxNew = 1;
          if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
            lanedetection_rgb_B.idxNew = 0;
          }

          lanedetection_rgb_B.idxOld = lanedetection_rgb_B.idxTmp;
          for (imgCol = lanedetection_rgb_B.loc; imgCol <=
               lanedetection_rgb_B.loc_m; imgCol++) {
            if (lanedetection_rgb_B.idxNew != 0) {
              lanedetection_rgb_B.DrawShapes_o2[lanedetection_rgb_B.idxOld] =
                (uint8_T)(((int32_T)((uint32_T)
                lanedetection_rgb_B.DrawShapes_o2[lanedetection_rgb_B.idxOld] *
                lanedetection_rgb_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_rgb_B.DrawShapes_o2[lanedetection_rgb_B.idxOld] =
                (uint8_T)((uint32_T)
                          lanedetection_rgb_B.DrawShapes_o2[lanedetection_rgb_B.idxOld]
                          + lanedetection_rgb_P.DrawShapes_color[1]);
            } else {
              lanedetection_rgb_B.DrawShapes_o2[lanedetection_rgb_B.idxOld] =
                lanedetection_rgb_P.DrawShapes_color[1];
            }

            lanedetection_rgb_B.idxOld++;
          }

          lanedetection_rgb_B.idxNew = 1;
          if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
            lanedetection_rgb_B.idxNew = 0;
          }

          while (lanedetection_rgb_B.loc <= lanedetection_rgb_B.loc_m) {
            if (lanedetection_rgb_B.idxNew != 0) {
              lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.idxTmp] =
                (uint8_T)(((int32_T)((uint32_T)
                lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.idxTmp] *
                lanedetection_rgb_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.idxTmp] =
                (uint8_T)((uint32_T)
                          lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.idxTmp]
                          + lanedetection_rgb_P.DrawShapes_color[2]);
            } else {
              lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.idxTmp] =
                lanedetection_rgb_P.DrawShapes_color[2];
            }

            lanedetection_rgb_B.idxTmp++;
            lanedetection_rgb_B.loc++;
          }
        }

        b2 = (lanedetection_rgb_B.numUniquePix <= acc4_idx_0);
      }

      /* Move to the next polygon. */
      imgIdx += m * 9;
      if (q1 >= div_s32_floor(imgRow, m) - 1) {
        q1 = 0;
      } else {
        q1++;
      }

      b2 = (imgIdx < (m << 1) * 9);
    }
  }

  /* End of S-Function (svipdrawshapes): '<Root>/Draw Shapes' */
  /* Start for MATLABSystem: '<S1>/MATLAB System' */
  memcpy(&lanedetection_rgb_B.rOUT[0], &lanedetection_rgb_B.DrawShapes_o1[0],
         22120U * sizeof(uint8_T));
  memcpy(&lanedetection_rgb_B.gOUT[0], &lanedetection_rgb_B.DrawShapes_o2[0],
         22120U * sizeof(uint8_T));
  memcpy(&lanedetection_rgb_B.bOUT[0], &lanedetection_rgb_B.DrawShapes_o3[0],
         22120U * sizeof(uint8_T));
  MW_SDL_videoDisplayOutput(lanedetection_rgb_B.rOUT, lanedetection_rgb_B.gOUT,
    lanedetection_rgb_B.bOUT);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.1s, 0.0s] */
    rtExtModeUpload(0, lanedetection_rgb_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
    if ((rtmGetTFinal(lanedetection_rgb_M)!=-1) &&
        !((rtmGetTFinal(lanedetection_rgb_M)-
           lanedetection_rgb_M->Timing.taskTime0) >
          lanedetection_rgb_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(lanedetection_rgb_M, "Simulation finished");
    }

    if (rtmGetStopRequested(lanedetection_rgb_M)) {
      rtmSetErrorStatus(lanedetection_rgb_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  lanedetection_rgb_M->Timing.taskTime0 =
    (++lanedetection_rgb_M->Timing.clockTick0) *
    lanedetection_rgb_M->Timing.stepSize0;
}

/* Model initialize function */
void lanedetection_rgb_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)lanedetection_rgb_M, 0,
                sizeof(RT_MODEL_lanedetection_rgb_T));
  rtmSetTFinal(lanedetection_rgb_M, -1);
  lanedetection_rgb_M->Timing.stepSize0 = 0.1;

  /* External mode info */
  lanedetection_rgb_M->Sizes.checksums[0] = (789728495U);
  lanedetection_rgb_M->Sizes.checksums[1] = (1332862887U);
  lanedetection_rgb_M->Sizes.checksums[2] = (169420035U);
  lanedetection_rgb_M->Sizes.checksums[3] = (3905022596U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    lanedetection_rgb_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lanedetection_rgb_M->extModeInfo,
      &lanedetection_rgb_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lanedetection_rgb_M->extModeInfo,
                        lanedetection_rgb_M->Sizes.checksums);
    rteiSetTPtr(lanedetection_rgb_M->extModeInfo, rtmGetTPtr(lanedetection_rgb_M));
  }

  /* block I/O */
  (void) memset(((void *) &lanedetection_rgb_B), 0,
                sizeof(B_lanedetection_rgb_T));

  {
    lanedetection_rgb_B.HoughTransform_o2[0] = -1.57079637F;
    lanedetection_rgb_B.HoughTransform_o2[1] = -1.53588974F;
    lanedetection_rgb_B.HoughTransform_o2[2] = -1.50098312F;
    lanedetection_rgb_B.HoughTransform_o2[3] = -1.46607661F;
    lanedetection_rgb_B.HoughTransform_o2[4] = -1.43117F;
    lanedetection_rgb_B.HoughTransform_o2[5] = -1.39626336F;
    lanedetection_rgb_B.HoughTransform_o2[6] = -1.36135685F;
    lanedetection_rgb_B.HoughTransform_o2[7] = -1.32645023F;
    lanedetection_rgb_B.HoughTransform_o2[8] = -1.2915436F;
    lanedetection_rgb_B.HoughTransform_o2[9] = -1.2566371F;
    lanedetection_rgb_B.HoughTransform_o2[10] = -1.22173047F;
    lanedetection_rgb_B.HoughTransform_o2[11] = -1.18682384F;
    lanedetection_rgb_B.HoughTransform_o2[12] = -1.15191734F;
    lanedetection_rgb_B.HoughTransform_o2[13] = -1.11701071F;
    lanedetection_rgb_B.HoughTransform_o2[14] = -1.08210409F;
    lanedetection_rgb_B.HoughTransform_o2[15] = -1.04719758F;
    lanedetection_rgb_B.HoughTransform_o2[16] = -1.01229095F;
    lanedetection_rgb_B.HoughTransform_o2[17] = -0.977384388F;
    lanedetection_rgb_B.HoughTransform_o2[18] = -0.942477822F;
    lanedetection_rgb_B.HoughTransform_o2[19] = -0.907571197F;
    lanedetection_rgb_B.HoughTransform_o2[20] = -0.87266463F;
    lanedetection_rgb_B.HoughTransform_o2[21] = -0.837758064F;
    lanedetection_rgb_B.HoughTransform_o2[22] = -0.802851439F;
    lanedetection_rgb_B.HoughTransform_o2[23] = -0.767944872F;
    lanedetection_rgb_B.HoughTransform_o2[24] = -0.733038306F;
    lanedetection_rgb_B.HoughTransform_o2[25] = -0.69813168F;
    lanedetection_rgb_B.HoughTransform_o2[26] = -0.663225114F;
    lanedetection_rgb_B.HoughTransform_o2[27] = -0.628318548F;
    lanedetection_rgb_B.HoughTransform_o2[28] = -0.593411922F;
    lanedetection_rgb_B.HoughTransform_o2[29] = -0.558505356F;
    lanedetection_rgb_B.HoughTransform_o2[30] = -0.52359879F;
    lanedetection_rgb_B.HoughTransform_o2[31] = -0.488692194F;
    lanedetection_rgb_B.HoughTransform_o2[32] = -0.453785598F;
    lanedetection_rgb_B.HoughTransform_o2[33] = -0.418879032F;
    lanedetection_rgb_B.HoughTransform_o2[34] = -0.383972436F;
    lanedetection_rgb_B.HoughTransform_o2[35] = -0.34906584F;
    lanedetection_rgb_B.HoughTransform_o2[36] = -0.314159274F;
    lanedetection_rgb_B.HoughTransform_o2[37] = -0.279252678F;
    lanedetection_rgb_B.HoughTransform_o2[38] = -0.244346097F;
    lanedetection_rgb_B.HoughTransform_o2[39] = -0.209439516F;
    lanedetection_rgb_B.HoughTransform_o2[40] = -0.17453292F;
    lanedetection_rgb_B.HoughTransform_o2[41] = -0.139626339F;
    lanedetection_rgb_B.HoughTransform_o2[42] = -0.104719758F;
    lanedetection_rgb_B.HoughTransform_o2[43] = -0.0698131695F;
    lanedetection_rgb_B.HoughTransform_o2[44] = -0.0349065848F;
    lanedetection_rgb_B.HoughTransform_o2[45] = 0.0F;
    lanedetection_rgb_B.HoughTransform_o2[46] = 0.0349065848F;
    lanedetection_rgb_B.HoughTransform_o2[47] = 0.0698131695F;
    lanedetection_rgb_B.HoughTransform_o2[48] = 0.104719758F;
    lanedetection_rgb_B.HoughTransform_o2[49] = 0.139626339F;
    lanedetection_rgb_B.HoughTransform_o2[50] = 0.17453292F;
    lanedetection_rgb_B.HoughTransform_o2[51] = 0.209439516F;
    lanedetection_rgb_B.HoughTransform_o2[52] = 0.244346097F;
    lanedetection_rgb_B.HoughTransform_o2[53] = 0.279252678F;
    lanedetection_rgb_B.HoughTransform_o2[54] = 0.314159274F;
    lanedetection_rgb_B.HoughTransform_o2[55] = 0.34906584F;
    lanedetection_rgb_B.HoughTransform_o2[56] = 0.383972436F;
    lanedetection_rgb_B.HoughTransform_o2[57] = 0.418879032F;
    lanedetection_rgb_B.HoughTransform_o2[58] = 0.453785598F;
    lanedetection_rgb_B.HoughTransform_o2[59] = 0.488692194F;
    lanedetection_rgb_B.HoughTransform_o2[60] = 0.52359879F;
    lanedetection_rgb_B.HoughTransform_o2[61] = 0.558505356F;
    lanedetection_rgb_B.HoughTransform_o2[62] = 0.593411922F;
    lanedetection_rgb_B.HoughTransform_o2[63] = 0.628318548F;
    lanedetection_rgb_B.HoughTransform_o2[64] = 0.663225114F;
    lanedetection_rgb_B.HoughTransform_o2[65] = 0.69813168F;
    lanedetection_rgb_B.HoughTransform_o2[66] = 0.733038306F;
    lanedetection_rgb_B.HoughTransform_o2[67] = 0.767944872F;
    lanedetection_rgb_B.HoughTransform_o2[68] = 0.802851439F;
    lanedetection_rgb_B.HoughTransform_o2[69] = 0.837758064F;
    lanedetection_rgb_B.HoughTransform_o2[70] = 0.87266463F;
    lanedetection_rgb_B.HoughTransform_o2[71] = 0.907571197F;
    lanedetection_rgb_B.HoughTransform_o2[72] = 0.942477822F;
    lanedetection_rgb_B.HoughTransform_o2[73] = 0.977384388F;
    lanedetection_rgb_B.HoughTransform_o2[74] = 1.01229095F;
    lanedetection_rgb_B.HoughTransform_o2[75] = 1.04719758F;
    lanedetection_rgb_B.HoughTransform_o2[76] = 1.08210409F;
    lanedetection_rgb_B.HoughTransform_o2[77] = 1.11701071F;
    lanedetection_rgb_B.HoughTransform_o2[78] = 1.15191734F;
    lanedetection_rgb_B.HoughTransform_o2[79] = 1.18682384F;
    lanedetection_rgb_B.HoughTransform_o2[80] = 1.22173047F;
    lanedetection_rgb_B.HoughTransform_o2[81] = 1.2566371F;
    lanedetection_rgb_B.HoughTransform_o2[82] = 1.2915436F;
    lanedetection_rgb_B.HoughTransform_o2[83] = 1.32645023F;
    lanedetection_rgb_B.HoughTransform_o2[84] = 1.36135685F;
    lanedetection_rgb_B.HoughTransform_o2[85] = 1.39626336F;
    lanedetection_rgb_B.HoughTransform_o2[86] = 1.43117F;
    lanedetection_rgb_B.HoughTransform_o2[87] = 1.46607661F;
    lanedetection_rgb_B.HoughTransform_o2[88] = 1.50098312F;
    lanedetection_rgb_B.HoughTransform_o2[89] = 1.53588974F;
    lanedetection_rgb_B.HoughTransform_o3[0] = -324.0F;
    lanedetection_rgb_B.HoughTransform_o3[1] = -320.0F;
    lanedetection_rgb_B.HoughTransform_o3[2] = -316.0F;
    lanedetection_rgb_B.HoughTransform_o3[3] = -312.0F;
    lanedetection_rgb_B.HoughTransform_o3[4] = -308.0F;
    lanedetection_rgb_B.HoughTransform_o3[5] = -304.0F;
    lanedetection_rgb_B.HoughTransform_o3[6] = -300.0F;
    lanedetection_rgb_B.HoughTransform_o3[7] = -296.0F;
    lanedetection_rgb_B.HoughTransform_o3[8] = -292.0F;
    lanedetection_rgb_B.HoughTransform_o3[9] = -288.0F;
    lanedetection_rgb_B.HoughTransform_o3[10] = -284.0F;
    lanedetection_rgb_B.HoughTransform_o3[11] = -280.0F;
    lanedetection_rgb_B.HoughTransform_o3[12] = -276.0F;
    lanedetection_rgb_B.HoughTransform_o3[13] = -272.0F;
    lanedetection_rgb_B.HoughTransform_o3[14] = -268.0F;
    lanedetection_rgb_B.HoughTransform_o3[15] = -264.0F;
    lanedetection_rgb_B.HoughTransform_o3[16] = -260.0F;
    lanedetection_rgb_B.HoughTransform_o3[17] = -256.0F;
    lanedetection_rgb_B.HoughTransform_o3[18] = -252.0F;
    lanedetection_rgb_B.HoughTransform_o3[19] = -248.0F;
    lanedetection_rgb_B.HoughTransform_o3[20] = -244.0F;
    lanedetection_rgb_B.HoughTransform_o3[21] = -240.0F;
    lanedetection_rgb_B.HoughTransform_o3[22] = -236.0F;
    lanedetection_rgb_B.HoughTransform_o3[23] = -232.0F;
    lanedetection_rgb_B.HoughTransform_o3[24] = -228.0F;
    lanedetection_rgb_B.HoughTransform_o3[25] = -224.0F;
    lanedetection_rgb_B.HoughTransform_o3[26] = -220.0F;
    lanedetection_rgb_B.HoughTransform_o3[27] = -216.0F;
    lanedetection_rgb_B.HoughTransform_o3[28] = -212.0F;
    lanedetection_rgb_B.HoughTransform_o3[29] = -208.0F;
    lanedetection_rgb_B.HoughTransform_o3[30] = -204.0F;
    lanedetection_rgb_B.HoughTransform_o3[31] = -200.0F;
    lanedetection_rgb_B.HoughTransform_o3[32] = -196.0F;
    lanedetection_rgb_B.HoughTransform_o3[33] = -192.0F;
    lanedetection_rgb_B.HoughTransform_o3[34] = -188.0F;
    lanedetection_rgb_B.HoughTransform_o3[35] = -184.0F;
    lanedetection_rgb_B.HoughTransform_o3[36] = -180.0F;
    lanedetection_rgb_B.HoughTransform_o3[37] = -176.0F;
    lanedetection_rgb_B.HoughTransform_o3[38] = -172.0F;
    lanedetection_rgb_B.HoughTransform_o3[39] = -168.0F;
    lanedetection_rgb_B.HoughTransform_o3[40] = -164.0F;
    lanedetection_rgb_B.HoughTransform_o3[41] = -160.0F;
    lanedetection_rgb_B.HoughTransform_o3[42] = -156.0F;
    lanedetection_rgb_B.HoughTransform_o3[43] = -152.0F;
    lanedetection_rgb_B.HoughTransform_o3[44] = -148.0F;
    lanedetection_rgb_B.HoughTransform_o3[45] = -144.0F;
    lanedetection_rgb_B.HoughTransform_o3[46] = -140.0F;
    lanedetection_rgb_B.HoughTransform_o3[47] = -136.0F;
    lanedetection_rgb_B.HoughTransform_o3[48] = -132.0F;
    lanedetection_rgb_B.HoughTransform_o3[49] = -128.0F;
    lanedetection_rgb_B.HoughTransform_o3[50] = -124.0F;
    lanedetection_rgb_B.HoughTransform_o3[51] = -120.0F;
    lanedetection_rgb_B.HoughTransform_o3[52] = -116.0F;
    lanedetection_rgb_B.HoughTransform_o3[53] = -112.0F;
    lanedetection_rgb_B.HoughTransform_o3[54] = -108.0F;
    lanedetection_rgb_B.HoughTransform_o3[55] = -104.0F;
    lanedetection_rgb_B.HoughTransform_o3[56] = -100.0F;
    lanedetection_rgb_B.HoughTransform_o3[57] = -96.0F;
    lanedetection_rgb_B.HoughTransform_o3[58] = -92.0F;
    lanedetection_rgb_B.HoughTransform_o3[59] = -88.0F;
    lanedetection_rgb_B.HoughTransform_o3[60] = -84.0F;
    lanedetection_rgb_B.HoughTransform_o3[61] = -80.0F;
    lanedetection_rgb_B.HoughTransform_o3[62] = -76.0F;
    lanedetection_rgb_B.HoughTransform_o3[63] = -72.0F;
    lanedetection_rgb_B.HoughTransform_o3[64] = -68.0F;
    lanedetection_rgb_B.HoughTransform_o3[65] = -64.0F;
    lanedetection_rgb_B.HoughTransform_o3[66] = -60.0F;
    lanedetection_rgb_B.HoughTransform_o3[67] = -56.0F;
    lanedetection_rgb_B.HoughTransform_o3[68] = -52.0F;
    lanedetection_rgb_B.HoughTransform_o3[69] = -48.0F;
    lanedetection_rgb_B.HoughTransform_o3[70] = -44.0F;
    lanedetection_rgb_B.HoughTransform_o3[71] = -40.0F;
    lanedetection_rgb_B.HoughTransform_o3[72] = -36.0F;
    lanedetection_rgb_B.HoughTransform_o3[73] = -32.0F;
    lanedetection_rgb_B.HoughTransform_o3[74] = -28.0F;
    lanedetection_rgb_B.HoughTransform_o3[75] = -24.0F;
    lanedetection_rgb_B.HoughTransform_o3[76] = -20.0F;
    lanedetection_rgb_B.HoughTransform_o3[77] = -16.0F;
    lanedetection_rgb_B.HoughTransform_o3[78] = -12.0F;
    lanedetection_rgb_B.HoughTransform_o3[79] = -8.0F;
    lanedetection_rgb_B.HoughTransform_o3[80] = -4.0F;
    lanedetection_rgb_B.HoughTransform_o3[81] = 0.0F;
    lanedetection_rgb_B.HoughTransform_o3[82] = 4.0F;
    lanedetection_rgb_B.HoughTransform_o3[83] = 8.0F;
    lanedetection_rgb_B.HoughTransform_o3[84] = 12.0F;
    lanedetection_rgb_B.HoughTransform_o3[85] = 16.0F;
    lanedetection_rgb_B.HoughTransform_o3[86] = 20.0F;
    lanedetection_rgb_B.HoughTransform_o3[87] = 24.0F;
    lanedetection_rgb_B.HoughTransform_o3[88] = 28.0F;
    lanedetection_rgb_B.HoughTransform_o3[89] = 32.0F;
    lanedetection_rgb_B.HoughTransform_o3[90] = 36.0F;
    lanedetection_rgb_B.HoughTransform_o3[91] = 40.0F;
    lanedetection_rgb_B.HoughTransform_o3[92] = 44.0F;
    lanedetection_rgb_B.HoughTransform_o3[93] = 48.0F;
    lanedetection_rgb_B.HoughTransform_o3[94] = 52.0F;
    lanedetection_rgb_B.HoughTransform_o3[95] = 56.0F;
    lanedetection_rgb_B.HoughTransform_o3[96] = 60.0F;
    lanedetection_rgb_B.HoughTransform_o3[97] = 64.0F;
    lanedetection_rgb_B.HoughTransform_o3[98] = 68.0F;
    lanedetection_rgb_B.HoughTransform_o3[99] = 72.0F;
    lanedetection_rgb_B.HoughTransform_o3[100] = 76.0F;
    lanedetection_rgb_B.HoughTransform_o3[101] = 80.0F;
    lanedetection_rgb_B.HoughTransform_o3[102] = 84.0F;
    lanedetection_rgb_B.HoughTransform_o3[103] = 88.0F;
    lanedetection_rgb_B.HoughTransform_o3[104] = 92.0F;
    lanedetection_rgb_B.HoughTransform_o3[105] = 96.0F;
    lanedetection_rgb_B.HoughTransform_o3[106] = 100.0F;
    lanedetection_rgb_B.HoughTransform_o3[107] = 104.0F;
    lanedetection_rgb_B.HoughTransform_o3[108] = 108.0F;
    lanedetection_rgb_B.HoughTransform_o3[109] = 112.0F;
    lanedetection_rgb_B.HoughTransform_o3[110] = 116.0F;
    lanedetection_rgb_B.HoughTransform_o3[111] = 120.0F;
    lanedetection_rgb_B.HoughTransform_o3[112] = 124.0F;
    lanedetection_rgb_B.HoughTransform_o3[113] = 128.0F;
    lanedetection_rgb_B.HoughTransform_o3[114] = 132.0F;
    lanedetection_rgb_B.HoughTransform_o3[115] = 136.0F;
    lanedetection_rgb_B.HoughTransform_o3[116] = 140.0F;
    lanedetection_rgb_B.HoughTransform_o3[117] = 144.0F;
    lanedetection_rgb_B.HoughTransform_o3[118] = 148.0F;
    lanedetection_rgb_B.HoughTransform_o3[119] = 152.0F;
    lanedetection_rgb_B.HoughTransform_o3[120] = 156.0F;
    lanedetection_rgb_B.HoughTransform_o3[121] = 160.0F;
    lanedetection_rgb_B.HoughTransform_o3[122] = 164.0F;
    lanedetection_rgb_B.HoughTransform_o3[123] = 168.0F;
    lanedetection_rgb_B.HoughTransform_o3[124] = 172.0F;
    lanedetection_rgb_B.HoughTransform_o3[125] = 176.0F;
    lanedetection_rgb_B.HoughTransform_o3[126] = 180.0F;
    lanedetection_rgb_B.HoughTransform_o3[127] = 184.0F;
    lanedetection_rgb_B.HoughTransform_o3[128] = 188.0F;
    lanedetection_rgb_B.HoughTransform_o3[129] = 192.0F;
    lanedetection_rgb_B.HoughTransform_o3[130] = 196.0F;
    lanedetection_rgb_B.HoughTransform_o3[131] = 200.0F;
    lanedetection_rgb_B.HoughTransform_o3[132] = 204.0F;
    lanedetection_rgb_B.HoughTransform_o3[133] = 208.0F;
    lanedetection_rgb_B.HoughTransform_o3[134] = 212.0F;
    lanedetection_rgb_B.HoughTransform_o3[135] = 216.0F;
    lanedetection_rgb_B.HoughTransform_o3[136] = 220.0F;
    lanedetection_rgb_B.HoughTransform_o3[137] = 224.0F;
    lanedetection_rgb_B.HoughTransform_o3[138] = 228.0F;
    lanedetection_rgb_B.HoughTransform_o3[139] = 232.0F;
    lanedetection_rgb_B.HoughTransform_o3[140] = 236.0F;
    lanedetection_rgb_B.HoughTransform_o3[141] = 240.0F;
    lanedetection_rgb_B.HoughTransform_o3[142] = 244.0F;
    lanedetection_rgb_B.HoughTransform_o3[143] = 248.0F;
    lanedetection_rgb_B.HoughTransform_o3[144] = 252.0F;
    lanedetection_rgb_B.HoughTransform_o3[145] = 256.0F;
    lanedetection_rgb_B.HoughTransform_o3[146] = 260.0F;
    lanedetection_rgb_B.HoughTransform_o3[147] = 264.0F;
    lanedetection_rgb_B.HoughTransform_o3[148] = 268.0F;
    lanedetection_rgb_B.HoughTransform_o3[149] = 272.0F;
    lanedetection_rgb_B.HoughTransform_o3[150] = 276.0F;
    lanedetection_rgb_B.HoughTransform_o3[151] = 280.0F;
    lanedetection_rgb_B.HoughTransform_o3[152] = 284.0F;
    lanedetection_rgb_B.HoughTransform_o3[153] = 288.0F;
    lanedetection_rgb_B.HoughTransform_o3[154] = 292.0F;
    lanedetection_rgb_B.HoughTransform_o3[155] = 296.0F;
    lanedetection_rgb_B.HoughTransform_o3[156] = 300.0F;
    lanedetection_rgb_B.HoughTransform_o3[157] = 304.0F;
    lanedetection_rgb_B.HoughTransform_o3[158] = 308.0F;
    lanedetection_rgb_B.HoughTransform_o3[159] = 312.0F;
    lanedetection_rgb_B.HoughTransform_o3[160] = 316.0F;
    lanedetection_rgb_B.HoughTransform_o3[161] = 320.0F;
    lanedetection_rgb_B.HoughTransform_o3[162] = 324.0F;
  }

  /* states (dwork) */
  (void) memset((void *)&lanedetection_rgb_DW, 0,
                sizeof(DW_lanedetection_rgb_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lanedetection_rgb_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    int32_T nonZeroIdx;
    int32_T EdgeDetection_VO_DW_tmp;

    /* Start for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
    MW_videoCaptureInit(lanedetection_rgb_ConstP.V4L2VideoCapture_p1, 0, 0, 0, 0,
                        320U, 240U, 2U, 2U, 1U, 0.1);

    /* Start for S-Function (svipedge): '<Root>/Edge Detection' */
    for (nonZeroIdx = 0; nonZeroIdx < 6; nonZeroIdx++) {
      EdgeDetection_VO_DW_tmp =
        lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] * 316 +
        lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx];
      lanedetection_rgb_DW.EdgeDetection_VO_DW[nonZeroIdx] =
        EdgeDetection_VO_DW_tmp;
      if (lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx] > 0) {
        lanedetection_rgb_DW.EdgeDetection_VOU_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_VOD_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] * 316;
      } else {
        lanedetection_rgb_DW.EdgeDetection_VOU_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] * 316;
        lanedetection_rgb_DW.EdgeDetection_VOD_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
      }

      if (lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] > 0) {
        lanedetection_rgb_DW.EdgeDetection_VOL_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_VOR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx];
      } else {
        lanedetection_rgb_DW.EdgeDetection_VOL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx];
        lanedetection_rgb_DW.EdgeDetection_VOR_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx] < 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] < 0)) {
        lanedetection_rgb_DW.EdgeDetection_VOUL_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_VOLR_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_VOLL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx];
        lanedetection_rgb_DW.EdgeDetection_VOUR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] * 316;
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx] >= 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] < 0)) {
        lanedetection_rgb_DW.EdgeDetection_VOLL_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_VOUR_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_VOUL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx];
        lanedetection_rgb_DW.EdgeDetection_VOLR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] * 316;
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx] < 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] >= 0)) {
        lanedetection_rgb_DW.EdgeDetection_VOUR_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_VOLL_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_VOUL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] * 316;
        lanedetection_rgb_DW.EdgeDetection_VOLR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx];
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx] >= 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] >= 0)) {
        lanedetection_rgb_DW.EdgeDetection_VOLR_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_VOUL_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_VOLL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VRO_RTP[nonZeroIdx] * 316;
        lanedetection_rgb_DW.EdgeDetection_VOUR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_VCO_RTP[nonZeroIdx];
      }

      EdgeDetection_VO_DW_tmp =
        lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] * 316 +
        lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx];
      lanedetection_rgb_DW.EdgeDetection_HO_DW[nonZeroIdx] =
        EdgeDetection_VO_DW_tmp;
      if (lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx] > 0) {
        lanedetection_rgb_DW.EdgeDetection_HOU_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_HOD_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] * 316;
      } else {
        lanedetection_rgb_DW.EdgeDetection_HOU_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] * 316;
        lanedetection_rgb_DW.EdgeDetection_HOD_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
      }

      if (lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] > 0) {
        lanedetection_rgb_DW.EdgeDetection_HOL_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_HOR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx];
      } else {
        lanedetection_rgb_DW.EdgeDetection_HOL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx];
        lanedetection_rgb_DW.EdgeDetection_HOR_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx] < 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] < 0)) {
        lanedetection_rgb_DW.EdgeDetection_HOUL_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_HOLR_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_HOLL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx];
        lanedetection_rgb_DW.EdgeDetection_HOUR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] * 316;
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx] >= 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] < 0)) {
        lanedetection_rgb_DW.EdgeDetection_HOLL_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_HOUR_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_HOUL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx];
        lanedetection_rgb_DW.EdgeDetection_HOLR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] * 316;
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx] < 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] >= 0)) {
        lanedetection_rgb_DW.EdgeDetection_HOUR_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_HOLL_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_HOUL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] * 316;
        lanedetection_rgb_DW.EdgeDetection_HOLR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx];
      }

      if ((lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx] >= 0) &&
          (lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] >= 0)) {
        lanedetection_rgb_DW.EdgeDetection_HOLR_DW[nonZeroIdx] = 0;
        lanedetection_rgb_DW.EdgeDetection_HOUL_DW[nonZeroIdx] =
          EdgeDetection_VO_DW_tmp;
        lanedetection_rgb_DW.EdgeDetection_HOLL_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HRO_RTP[nonZeroIdx] * 316;
        lanedetection_rgb_DW.EdgeDetection_HOUR_DW[nonZeroIdx] =
          lanedetection_rgb_ConstP.EdgeDetection_HCO_RTP[nonZeroIdx];
      }
    }

    /* End of Start for S-Function (svipedge): '<Root>/Edge Detection' */
    /* Start for MATLABSystem: '<S1>/MATLAB System' */
    lanedetection_rgb_DW.obj.matlabCodegenIsDeleted = true;
    lanedetection_rgb_DW.obj.isInitialized = 0;
    lanedetection_rgb_DW.obj.matlabCodegenIsDeleted = false;
    lanedetection_rgb_DW.obj.isSetupComplete = false;
    lanedetection_rgb_DW.obj.isInitialized = 1;
    lanedetection_rgb_DW.obj.PixelFormatEnum = 1;
    MW_SDL_videoDisplayInit(lanedetection_rgb_DW.obj.PixelFormatEnum, 1, 1,
      316.0, 70.0);
    lanedetection_rgb_DW.obj.isSetupComplete = true;

    /* End of Start for SubSystem: '<Root>/SDL Video Display' */
  }
}

/* Model terminate function */
void lanedetection_rgb_terminate(void)
{
  /* Terminate for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureTerminate(lanedetection_rgb_ConstP.V4L2VideoCapture_p1);

  /* Terminate for MATLABSystem: '<S1>/MATLAB System' */
  matlabCodegenHandle_matlabCodeg(&lanedetection_rgb_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/SDL Video Display' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
