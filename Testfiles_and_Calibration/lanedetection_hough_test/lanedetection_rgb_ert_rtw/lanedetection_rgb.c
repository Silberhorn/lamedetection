/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_rgb.c
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

int32_T mul_s32_sat(int32_T a, int32_T b)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  if (((int32_T)u32_chi > 0) || ((u32_chi == 0U) && (u32_clo >= 2147483648U))) {
    result = MAX_int32_T;
  } else if (((int32_T)u32_chi < -1) || (((int32_T)u32_chi == -1) && (u32_clo <
               2147483648U))) {
    result = MIN_int32_T;
  } else {
    result = (int32_T)u32_clo;
  }

  return result;
}

int32_T div_repeat_s32_sat_near(int32_T numerator, int32_T denominator, uint32_T
  nRepeatSub)
{
  int32_T quotient;
  boolean_T quotientNeedsNegation;
  uint32_T absNumerator;
  uint32_T absDenominator;
  uint32_T iRepeatSub;
  boolean_T numeratorExtraBit;
  uint32_T tempQuotient;
  boolean_T overflow;
  if (denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;

    /* Divide by zero handler */
  } else {
    absNumerator = numerator < 0 ? ~(uint32_T)numerator + 1U : (uint32_T)
      numerator;
    absDenominator = denominator < 0 ? ~(uint32_T)denominator + 1U : (uint32_T)
      denominator;
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    overflow = false;
    tempQuotient = absNumerator / absDenominator;
    absNumerator %= absDenominator;
    for (iRepeatSub = 0U; iRepeatSub < nRepeatSub; iRepeatSub++) {
      numeratorExtraBit = (absNumerator >= 2147483648U);
      absNumerator <<= 1U;
      overflow = (overflow || (tempQuotient >= 2147483648U));
      tempQuotient <<= 1U;
      if (numeratorExtraBit || (absNumerator >= absDenominator)) {
        tempQuotient++;
        absNumerator -= absDenominator;
      }
    }

    if (overflow || (tempQuotient >= MAX_uint32_T)) {
      tempQuotient = MAX_uint32_T;
    } else {
      numeratorExtraBit = (absNumerator >= 2147483648U);
      absNumerator <<= 1U;
      if (numeratorExtraBit || ((boolean_T)(quotientNeedsNegation ? absNumerator
            > absDenominator : absNumerator >= absDenominator))) {
        tempQuotient++;
      }
    }

    if (quotientNeedsNegation) {
      quotient = tempQuotient <= 2147483647U ? -(int32_T)tempQuotient :
        MIN_int32_T;
    } else {
      quotient = tempQuotient <= 2147483647U ? (int32_T)tempQuotient :
        MAX_int32_T;
    }
  }

  return quotient;
}

int32_T mul_s32_loSR_sat_near(int32_T a, int32_T b, uint32_T aShift)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  boolean_T roundup;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  roundup = ((1U << (aShift - 1U) & u32_clo) != 0U);
  u32_clo = (u32_chi << /*MW:OvBitwiseOk*/ (32U - aShift) | u32_clo >> aShift) +
    roundup;
  u32_chi = (uint32_T)(roundup && (u32_clo == 0U)) + ((int32_T)u32_chi >> aShift);
  if (((int32_T)u32_chi > 0) || ((u32_chi == 0U) && (u32_clo >= 2147483648U))) {
    result = MAX_int32_T;
  } else if (((int32_T)u32_chi < -1) || (((int32_T)u32_chi == -1) && (u32_clo <
               2147483648U))) {
    result = MIN_int32_T;
  } else {
    result = (int32_T)u32_clo;
  }

  return result;
}

int32_T mul_s32_loSR_near(int32_T a, int32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  u32_clo = ((1U << (aShift - 1U) & u32_clo) != 0U) + (u32_chi <<
    /*MW:OvBitwiseOk*/ (32U - aShift) | u32_clo >> aShift);
  return (int32_T)u32_clo;
}

/*
 * Output and update for atomic system:
 *    '<Root>/MATLAB Function2'
 *    '<Root>/MATLAB Function3'
 *    '<Root>/MATLAB Function4'
 */
void lanedetection_r_MATLABFunction2(const uint8_T rtu_imgIN[76800], uint8_T
  rty_imgOUT[22120])
{
  int32_T i;
  for (i = 0; i < 70; i++) {
    memcpy(&rty_imgOUT[i * 316], &rtu_imgIN[i * 320 + 30402], 316U * sizeof
           (uint8_T));
  }
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
  /* Start for MATLABSystem: '<S4>/MATLAB System' */
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetectio_SystemCore_release(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S4>/MATLAB System' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SDL_videoDisplayTerminate(0, 0);
  }

  /* End of Start for MATLABSystem: '<S4>/MATLAB System' */
}

static void lanedetection_SystemCore_delete(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S4>/MATLAB System' */
  lanedetectio_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S4>/MATLAB System' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAnyP(obj, true);
    lanedetection_SystemCore_delete(obj);
  }

  /* End of Start for MATLABSystem: '<S4>/MATLAB System' */
}

/* Model step function */
void lanedetection_rgb_step(void)
{
  boolean_T visited2;
  boolean_T isMore;
  boolean_T prevEdgeIsVertical;
  int8_T idxTmpArray[2];
  int8_T threshSquared;
  int8_T accumOne;
  int8_T accumTwo;
  int32_T imgIdx;
  int8_T accumThree;
  int8_T accumFour;
  int32_T j;
  int32_T thetaIdx;
  int32_T cellIdx;
  int32_T thetaIdx2;
  boolean_T done;
  uint16_T maxValue;
  int32_T q2;
  int32_T acc1_idx_5;
  int32_T edgeTmp_tmp;
  int32_T DrawShapes_DW_Polygon_tmp;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_rgb_ConstP.V4L2VideoCapture_p1,
                        lanedetection_rgb_B.V4L2VideoCapture_o1,
                        lanedetection_rgb_B.V4L2VideoCapture_o2,
                        lanedetection_rgb_B.V4L2VideoCapture_o3);

  /* MATLAB Function: '<Root>/MATLAB Function2' */
  lanedetection_r_MATLABFunction2(lanedetection_rgb_B.V4L2VideoCapture_o1,
    lanedetection_rgb_B.DrawShapes_o1);

  /* MATLAB Function: '<Root>/MATLAB Function3' */
  lanedetection_r_MATLABFunction2(lanedetection_rgb_B.V4L2VideoCapture_o2,
    lanedetection_rgb_B.DrawShapes_o2);

  /* MATLAB Function: '<Root>/MATLAB Function4' */
  lanedetection_r_MATLABFunction2(lanedetection_rgb_B.V4L2VideoCapture_o3,
    lanedetection_rgb_B.DrawShapes_o3);

  /* S-Function (svipcolorconv): '<Root>/Color Space  Conversion' */
  for (thetaIdx2 = 0; thetaIdx2 < 22120; thetaIdx2++) {
    lanedetection_rgb_B.ColorSpaceConversion[thetaIdx2] = (uint8_T)
      ((((lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] * 19595U +
          lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] * 38470U) +
         lanedetection_rgb_B.DrawShapes_o3[thetaIdx2] * 7471U) + 32768U) >> 16);
  }

  /* End of S-Function (svipcolorconv): '<Root>/Color Space  Conversion' */

  /* S-Function (svipedge): '<Root>/Edge Detection' incorporates:
   *  Constant: '<Root>/Threshold'
   */
  threshSquared = (int8_T)(((int32_T)((uint32_T)
    lanedetection_rgb_P.Threshold_Value * lanedetection_rgb_P.Threshold_Value) <<
    8) >> 8);
  for (lanedetection_rgb_B.imgCol = 0; lanedetection_rgb_B.imgCol < 68;
       lanedetection_rgb_B.imgCol++) {
    for (lanedetection_rgb_B.imgRow = 0; lanedetection_rgb_B.imgRow < 314;
         lanedetection_rgb_B.imgRow++) {
      imgIdx = ((lanedetection_rgb_B.imgCol + 1) * 316 +
                lanedetection_rgb_B.imgRow) + 1;
      accumOne = (int8_T)((int8_T)
                          ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
                            lanedetection_rgb_DW.EdgeDetection_VO_DW[0]] << 7) >>
                           8) +
                          ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
                            lanedetection_rgb_DW.EdgeDetection_VO_DW[1]] * -128)
                           >> 8));
      accumTwo = (int8_T)((int8_T)
                          ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
                            lanedetection_rgb_DW.EdgeDetection_HO_DW[0]] * -128)
                           >> 8) +
                          ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
                            lanedetection_rgb_DW.EdgeDetection_HO_DW[1]] << 7) >>
                           8));
      lanedetection_rgb_B.EdgeDetection[imgIdx] = ((int8_T)((int8_T)(((accumOne *
        accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >> 8)) >
        threshSquared);
    }
  }

  for (lanedetection_rgb_B.imgCol = 0; lanedetection_rgb_B.imgCol < 68;
       lanedetection_rgb_B.imgCol++) {
    lanedetection_rgb_B.imgRow = (lanedetection_rgb_B.imgCol + 1) * 316;
    imgIdx = (lanedetection_rgb_B.imgCol + 1) * 316 + 315;
    accumOne = (int8_T)((int8_T)
                        ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_B.imgRow
                          + lanedetection_rgb_DW.EdgeDetection_HOU_DW[0]] * -128)
                         >> 8) +
                        ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_B.imgRow
                          + lanedetection_rgb_DW.EdgeDetection_HOU_DW[1]] << 7) >>
                         8));
    accumTwo = (int8_T)((int8_T)
                        ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
                          lanedetection_rgb_DW.EdgeDetection_HOD_DW[0]] * -128) >>
                         8) + ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx
      + lanedetection_rgb_DW.EdgeDetection_HOD_DW[1]] << 7) >> 8));
    accumThree = (int8_T)((int8_T)
                          ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_B.imgRow
      + lanedetection_rgb_DW.EdgeDetection_VOU_DW[0]] << 7) >> 8) +
                          ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_B.imgRow
      + lanedetection_rgb_DW.EdgeDetection_VOU_DW[1]] * -128) >> 8));
    accumFour = (int8_T)((int8_T)
                         ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
      lanedetection_rgb_DW.EdgeDetection_VOD_DW[0]] << 7) >> 8) +
                         ((lanedetection_rgb_B.ColorSpaceConversion[imgIdx +
      lanedetection_rgb_DW.EdgeDetection_VOD_DW[1]] * -128) >> 8));
    lanedetection_rgb_B.EdgeDetection[lanedetection_rgb_B.imgRow] = ((int8_T)
      ((int8_T)(((accumOne * accumOne) << 8) >> 8) + (int8_T)(((accumThree *
      accumThree) << 8) >> 8)) > threshSquared);
    lanedetection_rgb_B.EdgeDetection[imgIdx] = ((int8_T)((int8_T)(((accumTwo *
      accumTwo) << 8) >> 8) + (int8_T)(((accumFour * accumFour) << 8) >> 8)) >
      threshSquared);
  }

  for (lanedetection_rgb_B.imgRow = 0; lanedetection_rgb_B.imgRow < 314;
       lanedetection_rgb_B.imgRow++) {
    accumOne = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_VOL_DW[0])
      + 1] << 7) >> 8) + ((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_VOL_DW[1])
      + 1] * -128) >> 8));
    accumTwo = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_VOR_DW[0])
      + 21805] << 7) >> 8) + ((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_VOR_DW[1])
      + 21805] * -128) >> 8));
    accumThree = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_HOL_DW[0])
      + 1] * -128) >> 8) + ((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_HOL_DW[1])
      + 1] << 7) >> 8));
    accumFour = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_HOR_DW[0])
      + 21805] * -128) >> 8) + ((lanedetection_rgb_B.ColorSpaceConversion
      [(lanedetection_rgb_B.imgRow + lanedetection_rgb_DW.EdgeDetection_HOR_DW[1])
      + 21805] << 7) >> 8));
    lanedetection_rgb_B.EdgeDetection[lanedetection_rgb_B.imgRow + 1] = ((int8_T)
      ((int8_T)(((accumOne * accumOne) << 8) >> 8) + (int8_T)(((accumThree *
      accumThree) << 8) >> 8)) > threshSquared);
    lanedetection_rgb_B.EdgeDetection[21805 + lanedetection_rgb_B.imgRow] =
      ((int8_T)((int8_T)(((accumTwo * accumTwo) << 8) >> 8) + (int8_T)
                (((accumFour * accumFour) << 8) >> 8)) > threshSquared);
  }

  accumOne = (int8_T)((int8_T)
                      ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_DW.EdgeDetection_VOUL_DW
                        [0]] << 7) >> 8) +
                      ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_DW.EdgeDetection_VOUL_DW
                        [1]] * -128) >> 8));
  accumTwo = (int8_T)((int8_T)
                      ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_DW.EdgeDetection_HOUL_DW
                        [0]] * -128) >> 8) +
                      ((lanedetection_rgb_B.ColorSpaceConversion[lanedetection_rgb_DW.EdgeDetection_HOUL_DW
                        [1]] << 7) >> 8));
  accumThree = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion[315 +
    lanedetection_rgb_DW.EdgeDetection_VOLL_DW[0]] << 7) >> 8) +
                        ((lanedetection_rgb_B.ColorSpaceConversion[315 +
    lanedetection_rgb_DW.EdgeDetection_VOLL_DW[1]] * -128) >> 8));
  accumFour = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion[315 +
    lanedetection_rgb_DW.EdgeDetection_HOLL_DW[0]] * -128) >> 8) +
                       ((lanedetection_rgb_B.ColorSpaceConversion[315 +
    lanedetection_rgb_DW.EdgeDetection_HOLL_DW[1]] << 7) >> 8));
  lanedetection_rgb_B.EdgeDetection[0] = ((int8_T)((int8_T)(((accumOne *
    accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >> 8)) >
    threshSquared);
  lanedetection_rgb_B.EdgeDetection[315] = ((int8_T)((int8_T)(((accumThree *
    accumThree) << 8) >> 8) + (int8_T)(((accumFour * accumFour) << 8) >> 8)) >
    threshSquared);
  accumOne = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion[21804 +
    lanedetection_rgb_DW.EdgeDetection_VOUR_DW[0]] << 7) >> 8) +
                      ((lanedetection_rgb_B.ColorSpaceConversion[21804 +
                        lanedetection_rgb_DW.EdgeDetection_VOUR_DW[1]] * -128) >>
                       8));
  accumTwo = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion[21804 +
    lanedetection_rgb_DW.EdgeDetection_HOUR_DW[0]] * -128) >> 8) +
                      ((lanedetection_rgb_B.ColorSpaceConversion[21804 +
                        lanedetection_rgb_DW.EdgeDetection_HOUR_DW[1]] << 7) >>
                       8));
  accumThree = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion[22119
    + lanedetection_rgb_DW.EdgeDetection_VOLR_DW[0]] << 7) >> 8) +
                        ((lanedetection_rgb_B.ColorSpaceConversion[22119 +
    lanedetection_rgb_DW.EdgeDetection_VOLR_DW[1]] * -128) >> 8));
  accumFour = (int8_T)((int8_T)((lanedetection_rgb_B.ColorSpaceConversion[22119
    + lanedetection_rgb_DW.EdgeDetection_HOLR_DW[0]] * -128) >> 8) +
                       ((lanedetection_rgb_B.ColorSpaceConversion[22119 +
    lanedetection_rgb_DW.EdgeDetection_HOLR_DW[1]] << 7) >> 8));
  lanedetection_rgb_B.EdgeDetection[21804] = ((int8_T)((int8_T)(((accumOne *
    accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >> 8)) >
    threshSquared);
  lanedetection_rgb_B.EdgeDetection[22119] = ((int8_T)((int8_T)(((accumThree *
    accumThree) << 8) >> 8) + (int8_T)(((accumFour * accumFour) << 8) >> 8)) >
    threshSquared);

  /* End of S-Function (svipedge): '<Root>/Edge Detection' */

  /* S-Function (sviphough): '<Root>/Hough Transform' */
  memset(&lanedetection_rgb_B.HoughTransform_o1[0], 0, 39060U * sizeof(uint16_T));
  for (lanedetection_rgb_B.imgRow = 0; lanedetection_rgb_B.imgRow < 70;
       lanedetection_rgb_B.imgRow++) {
    for (imgIdx = 0; imgIdx < 316; imgIdx++) {
      if (lanedetection_rgb_B.EdgeDetection[lanedetection_rgb_B.imgRow * 316 +
          imgIdx]) {
        for (thetaIdx = 0; thetaIdx < 91; thetaIdx++) {
          lanedetection_rgb_B.imgCol =
            -lanedetection_rgb_ConstP.HoughTransform_SINE_TABLE_RTP[90 -
            thetaIdx];
          if (lanedetection_rgb_B.imgCol > 32767) {
            lanedetection_rgb_B.imgCol = 32767;
          }

          lanedetection_rgb_B.imgCol = mul_s32_sat(lanedetection_rgb_B.imgCol,
            lanedetection_rgb_B.imgRow);
          if (lanedetection_rgb_B.imgCol > 33554431) {
            q2 = MAX_int32_T;
          } else if (lanedetection_rgb_B.imgCol <= -33554432) {
            q2 = MIN_int32_T;
          } else {
            q2 = lanedetection_rgb_B.imgCol << 6;
          }

          lanedetection_rgb_B.imgCol = mul_s32_sat
            (lanedetection_rgb_ConstP.HoughTransform_SINE_TABLE_RTP[thetaIdx],
             imgIdx);
          if (lanedetection_rgb_B.imgCol > 33554431) {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else if (lanedetection_rgb_B.imgCol <= -33554432) {
            lanedetection_rgb_B.imgCol = MIN_int32_T;
          } else {
            lanedetection_rgb_B.imgCol <<= 6;
          }

          if ((q2 < 0) && (lanedetection_rgb_B.imgCol < MIN_int32_T - q2)) {
            lanedetection_rgb_B.imgCol = MIN_int32_T;
          } else if ((q2 > 0) && (lanedetection_rgb_B.imgCol > MAX_int32_T - q2))
          {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else {
            lanedetection_rgb_B.imgCol += q2;
          }

          if (lanedetection_rgb_B.imgCol > 1807745023) {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else {
            lanedetection_rgb_B.imgCol -= -339738624;
          }

          lanedetection_rgb_B.imgCol = mul_s32_loSR_near
            (lanedetection_rgb_B.imgCol, 349525, 20U);
          cellIdx = (thetaIdx * 217 + (lanedetection_rgb_B.imgCol >> 20)) +
            ((lanedetection_rgb_B.imgCol & 524288U) != 0U);
          if (lanedetection_rgb_B.HoughTransform_o1[cellIdx] > 2047) {
            q2 = MAX_int32_T;
          } else {
            q2 = lanedetection_rgb_B.HoughTransform_o1[cellIdx] << 20;
          }

          if (q2 > 2146435071) {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else {
            lanedetection_rgb_B.imgCol = q2 + 1048576;
          }

          lanedetection_rgb_B.HoughTransform_o1[cellIdx] = (uint16_T)
            (((lanedetection_rgb_B.imgCol & 524288U) != 0U) +
             (lanedetection_rgb_B.imgCol >> 20));
        }

        thetaIdx2 = thetaIdx;
        for (j = 0; j < 180 - thetaIdx2; j++) {
          lanedetection_rgb_B.imgCol =
            -lanedetection_rgb_ConstP.HoughTransform_SINE_TABLE_RTP[j + 1];
          if (lanedetection_rgb_B.imgCol > 32767) {
            lanedetection_rgb_B.imgCol = 32767;
          }

          lanedetection_rgb_B.imgCol = mul_s32_sat(lanedetection_rgb_B.imgCol,
            lanedetection_rgb_B.imgRow);
          if (lanedetection_rgb_B.imgCol > 33554431) {
            q2 = MAX_int32_T;
          } else if (lanedetection_rgb_B.imgCol <= -33554432) {
            q2 = MIN_int32_T;
          } else {
            q2 = lanedetection_rgb_B.imgCol << 6;
          }

          lanedetection_rgb_B.imgCol =
            -lanedetection_rgb_ConstP.HoughTransform_SINE_TABLE_RTP[89 - j];
          if (lanedetection_rgb_B.imgCol > 32767) {
            lanedetection_rgb_B.imgCol = 32767;
          }

          lanedetection_rgb_B.imgCol = mul_s32_sat(lanedetection_rgb_B.imgCol,
            imgIdx);
          if (lanedetection_rgb_B.imgCol > 33554431) {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else if (lanedetection_rgb_B.imgCol <= -33554432) {
            lanedetection_rgb_B.imgCol = MIN_int32_T;
          } else {
            lanedetection_rgb_B.imgCol <<= 6;
          }

          if ((q2 < 0) && (lanedetection_rgb_B.imgCol < MIN_int32_T - q2)) {
            lanedetection_rgb_B.imgCol = MIN_int32_T;
          } else if ((q2 > 0) && (lanedetection_rgb_B.imgCol > MAX_int32_T - q2))
          {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else {
            lanedetection_rgb_B.imgCol += q2;
          }

          if (lanedetection_rgb_B.imgCol > 1807745023) {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else {
            lanedetection_rgb_B.imgCol -= -339738624;
          }

          lanedetection_rgb_B.imgCol = mul_s32_loSR_near
            (lanedetection_rgb_B.imgCol, 349525, 20U);
          cellIdx = (thetaIdx * 217 + (lanedetection_rgb_B.imgCol >> 20)) +
            ((lanedetection_rgb_B.imgCol & 524288U) != 0U);
          if (lanedetection_rgb_B.HoughTransform_o1[cellIdx] > 2047) {
            q2 = MAX_int32_T;
          } else {
            q2 = lanedetection_rgb_B.HoughTransform_o1[cellIdx] << 20;
          }

          if (q2 > 2146435071) {
            lanedetection_rgb_B.imgCol = MAX_int32_T;
          } else {
            lanedetection_rgb_B.imgCol = q2 + 1048576;
          }

          lanedetection_rgb_B.HoughTransform_o1[cellIdx] = (uint16_T)
            (((lanedetection_rgb_B.imgCol & 524288U) != 0U) +
             (lanedetection_rgb_B.imgCol >> 20));
          thetaIdx++;
        }
      }
    }
  }

  /* End of S-Function (sviphough): '<Root>/Hough Transform' */

  /* Math: '<Root>/Transpose' */
  for (lanedetection_rgb_B.imgCol = 0; lanedetection_rgb_B.imgCol < 316;
       lanedetection_rgb_B.imgCol++) {
    for (lanedetection_rgb_B.imgRow = 0; lanedetection_rgb_B.imgRow < 70;
         lanedetection_rgb_B.imgRow++) {
      lanedetection_rgb_B.Transpose[lanedetection_rgb_B.imgRow + 70 *
        lanedetection_rgb_B.imgCol] = lanedetection_rgb_B.EdgeDetection[316 *
        lanedetection_rgb_B.imgRow + lanedetection_rgb_B.imgCol];
    }
  }

  /* End of Math: '<Root>/Transpose' */

  /* S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */
  lanedetection_rgb_B.imgRow = 0;
  done = false;
  for (thetaIdx2 = 0; thetaIdx2 < 39060; thetaIdx2++) {
    lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[thetaIdx2] =
      lanedetection_rgb_B.HoughTransform_o1[thetaIdx2];
  }

  lanedetection_rgb_B.FindLocalMaxima_o1[0] = 0U;
  lanedetection_rgb_B.FindLocalMaxima_o1[1] = 0U;
  while (!done) {
    lanedetection_rgb_B.imgCol = 0;
    maxValue = lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[0];
    for (thetaIdx2 = 0; thetaIdx2 < 39060; thetaIdx2++) {
      if (lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[thetaIdx2] >
          maxValue) {
        lanedetection_rgb_B.imgCol = thetaIdx2;
        maxValue = lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[thetaIdx2];
      }
    }

    thetaIdx = lanedetection_rgb_B.imgCol % 217;
    thetaIdx2 = lanedetection_rgb_B.imgCol / 217;
    if (lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lanedetection_rgb_B.imgCol]
        >= lanedetection_rgb_P.FindLocalMaxima_threshold) {
      lanedetection_rgb_B.FindLocalMaxima_o1[lanedetection_rgb_B.imgRow] =
        (uint32_T)(1 + thetaIdx2);
      lanedetection_rgb_B.FindLocalMaxima_o1[1U + lanedetection_rgb_B.imgRow] =
        (uint32_T)(1 + thetaIdx);
      lanedetection_rgb_B.imgRow++;
      if (lanedetection_rgb_B.imgRow == 1) {
        done = true;
      }

      imgIdx = thetaIdx - 2;
      if (!(imgIdx > 0)) {
        imgIdx = 0;
      }

      thetaIdx += 2;
      if (!(thetaIdx < 216)) {
        thetaIdx = 216;
      }

      lanedetection_rgb_B.imgCol = thetaIdx2 - 3;
      q2 = thetaIdx2 + 3;
      if (!((lanedetection_rgb_B.imgCol < 0) || (q2 > 179))) {
        while (lanedetection_rgb_B.imgCol <= q2) {
          cellIdx = lanedetection_rgb_B.imgCol * 217;
          for (thetaIdx2 = imgIdx; thetaIdx2 <= thetaIdx; thetaIdx2++) {
            lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[thetaIdx2 +
              cellIdx] = 0U;
          }

          lanedetection_rgb_B.imgCol++;
        }
      } else {
        if (lanedetection_rgb_B.imgCol < 0) {
          for (j = lanedetection_rgb_B.imgCol; j <= q2; j++) {
            if (j < 0) {
              cellIdx = (j + 180) * 217 + 216;
              for (thetaIdx2 = imgIdx; thetaIdx2 <= thetaIdx; thetaIdx2++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[cellIdx -
                  thetaIdx2] = 0U;
              }
            } else {
              cellIdx = j * 217;
              for (thetaIdx2 = imgIdx; thetaIdx2 <= thetaIdx; thetaIdx2++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[thetaIdx2 +
                  cellIdx] = 0U;
              }
            }
          }
        }

        if (q2 > 179) {
          for (j = lanedetection_rgb_B.imgCol; j <= q2; j++) {
            if (j > 179) {
              cellIdx = (j - 180) * 217 + 216;
              for (thetaIdx2 = imgIdx; thetaIdx2 <= thetaIdx; thetaIdx2++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[cellIdx -
                  thetaIdx2] = 0U;
              }
            } else {
              cellIdx = j * 217;
              for (thetaIdx2 = imgIdx; thetaIdx2 <= thetaIdx; thetaIdx2++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[thetaIdx2 +
                  cellIdx] = 0U;
              }
            }
          }
        }
      }
    } else {
      done = true;
    }
  }

  /* End of S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix1' */
  lanedetection_rgb_B.Submatrix1[0] = lanedetection_rgb_B.FindLocalMaxima_o1[0];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_rgb_B.Submatrix[0] = lanedetection_rgb_B.FindLocalMaxima_o1[0];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix1' */
  lanedetection_rgb_B.Submatrix1[1] = lanedetection_rgb_B.FindLocalMaxima_o1[1];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_rgb_B.Submatrix[1] = lanedetection_rgb_B.FindLocalMaxima_o1[1];

  /* S-Function (sviphoughlines): '<Root>/Hough Lines' incorporates:
   *  Selector: '<Root>/Selector'
   *  Selector: '<Root>/Selector1'
   */
  lanedetection_rgb_B.imgRow = 0;
  lanedetection_rgb_B.imgCol = lanedetection_rgb_B.HoughTransform_o2[(int32_T)
    lanedetection_rgb_B.Submatrix1[0] - 1];
  if (lanedetection_rgb_B.HoughTransform_o2[(int32_T)
      lanedetection_rgb_B.Submatrix1[0] - 1] > 102944) {
    while (lanedetection_rgb_B.imgCol > 102944) {
      lanedetection_rgb_B.imgCol -= 205888;
    }
  } else {
    if (lanedetection_rgb_B.HoughTransform_o2[(int32_T)
        lanedetection_rgb_B.Submatrix1[0] - 1] < -102944) {
      while (lanedetection_rgb_B.imgCol < -102944) {
        lanedetection_rgb_B.imgCol += 205888;
      }
    }
  }

  if (lanedetection_rgb_B.imgCol > 2147380703) {
    lanedetection_rgb_B.imgCol = MAX_int32_T;
  } else {
    lanedetection_rgb_B.imgCol += 102944;
  }

  lanedetection_rgb_B.imgCol = div_repeat_s32_sat_near
    (lanedetection_rgb_B.imgCol, 143, 13U);
  thetaIdx = ((lanedetection_rgb_B.imgCol & 32768U) != 0U) +
    (lanedetection_rgb_B.imgCol >> 16);
  if (thetaIdx < 0) {
    thetaIdx = 0;
  } else {
    if (thetaIdx > 180) {
      thetaIdx = 180;
    }
  }

  if (thetaIdx < 91) {
    lanedetection_rgb_B.imgCol =
      -lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[90 - thetaIdx];
    if (lanedetection_rgb_B.imgCol > 32767) {
      lanedetection_rgb_B.imgCol = 32767;
    }

    lanedetection_rgb_B.imgCol <<= 3;
    if (lanedetection_rgb_B.imgCol == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[0] - 1] > 0) {
        imgIdx = MAX_int32_T;
      } else {
        imgIdx = MIN_int32_T;
      }
    } else {
      imgIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[0] - 1],
        lanedetection_rgb_B.imgCol, 16U);
    }

    if (lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[thetaIdx] == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[0] - 1] > 0) {
        thetaIdx = MAX_int32_T;
      } else {
        thetaIdx = MIN_int32_T;
      }
    } else {
      thetaIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[0] - 1],
        lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[thetaIdx], 13U);
    }
  } else {
    lanedetection_rgb_B.imgCol =
      -lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[thetaIdx - 90];
    if (lanedetection_rgb_B.imgCol > 32767) {
      lanedetection_rgb_B.imgCol = 32767;
    }

    lanedetection_rgb_B.imgCol <<= 3;
    if (lanedetection_rgb_B.imgCol == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[0] - 1] > 0) {
        imgIdx = MAX_int32_T;
      } else {
        imgIdx = MIN_int32_T;
      }
    } else {
      imgIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[0] - 1],
        lanedetection_rgb_B.imgCol, 16U);
    }

    lanedetection_rgb_B.imgCol =
      -lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[180 - thetaIdx];
    if (lanedetection_rgb_B.imgCol > 32767) {
      lanedetection_rgb_B.imgCol = 32767;
    }

    lanedetection_rgb_B.imgCol <<= 3;
    if (lanedetection_rgb_B.imgCol == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[0] - 1] > 0) {
        thetaIdx = MAX_int32_T;
      } else {
        thetaIdx = MIN_int32_T;
      }
    } else {
      thetaIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[0] - 1],
        lanedetection_rgb_B.imgCol, 16U);
    }
  }

  /* part-1: top horizontal axis */
  lanedetection_rgb_B.imgCol = ((imgIdx & 32768U) != 0U) + (imgIdx >> 16);
  if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 69)) {
    lanedetection_rgb_B.tmpOutRC[0U] = 0;
    lanedetection_rgb_B.tmpOutRC[1U] = (int16_T)lanedetection_rgb_B.imgCol;
    lanedetection_rgb_B.imgRow = 1;
  }

  /* part-2: left vertical axis */
  lanedetection_rgb_B.imgCol = ((thetaIdx & 32768U) != 0U) + (thetaIdx >> 16);
  if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 315))
  {
    lanedetection_rgb_B.tmpOutRC[lanedetection_rgb_B.imgRow << 1] = (int16_T)
      lanedetection_rgb_B.imgCol;
    lanedetection_rgb_B.tmpOutRC[1 + (lanedetection_rgb_B.imgRow << 1)] = 0;
    lanedetection_rgb_B.imgRow++;
  }

  /* part-3: Right vertical axis */
  if (lanedetection_rgb_B.imgRow < 2) {
    if ((imgIdx >= 0) && (4521984 < imgIdx - MAX_int32_T)) {
      lanedetection_rgb_B.imgCol = MAX_int32_T;
    } else if ((imgIdx < 0) && (4521984 > imgIdx - MIN_int32_T)) {
      lanedetection_rgb_B.imgCol = MIN_int32_T;
    } else {
      lanedetection_rgb_B.imgCol = imgIdx - 4521984;
    }

    if (imgIdx == 0) {
      if (thetaIdx > 0) {
        thetaIdx2 = MAX_int32_T;
      } else {
        thetaIdx2 = MIN_int32_T;
      }
    } else {
      thetaIdx2 = div_repeat_s32_sat_near(thetaIdx, imgIdx, 16U);
    }

    lanedetection_rgb_B.imgCol = mul_s32_loSR_sat_near
      (lanedetection_rgb_B.imgCol, thetaIdx2, 16U);
    lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.imgCol & 32768U) != 0U) +
      (lanedetection_rgb_B.imgCol >> 16);
    if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 315))
    {
      lanedetection_rgb_B.tmpOutRC[lanedetection_rgb_B.imgRow << 1] = (int16_T)
        lanedetection_rgb_B.imgCol;
      lanedetection_rgb_B.tmpOutRC[1 + (lanedetection_rgb_B.imgRow << 1)] = 69;
      lanedetection_rgb_B.imgRow++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (lanedetection_rgb_B.imgRow < 2) {
    if (thetaIdx == 0) {
      if (imgIdx > 0) {
        thetaIdx = MAX_int32_T;
      } else {
        thetaIdx = MIN_int32_T;
      }
    } else {
      thetaIdx = div_repeat_s32_sat_near(imgIdx, thetaIdx, 16U);
    }

    lanedetection_rgb_B.imgCol = mul_s32_sat(thetaIdx, 315);
    if ((imgIdx >= 0) && (lanedetection_rgb_B.imgCol < imgIdx - MAX_int32_T)) {
      lanedetection_rgb_B.imgCol = MAX_int32_T;
    } else if ((imgIdx < 0) && (lanedetection_rgb_B.imgCol > imgIdx -
                MIN_int32_T)) {
      lanedetection_rgb_B.imgCol = MIN_int32_T;
    } else {
      lanedetection_rgb_B.imgCol = imgIdx - lanedetection_rgb_B.imgCol;
    }

    lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.imgCol & 32768U) != 0U) +
      (lanedetection_rgb_B.imgCol >> 16);
    if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 69))
    {
      lanedetection_rgb_B.tmpOutRC[lanedetection_rgb_B.imgRow << 1] = 315;
      lanedetection_rgb_B.tmpOutRC[1 + (lanedetection_rgb_B.imgRow << 1)] =
        (int16_T)lanedetection_rgb_B.imgCol;
      lanedetection_rgb_B.imgRow++;
    }
  }

  if (lanedetection_rgb_B.imgRow < 2) {
    lanedetection_rgb_B.tmpOutRC[0U] = -1;
    lanedetection_rgb_B.tmpOutRC[1U] = -1;
    lanedetection_rgb_B.tmpOutRC[2U] = -1;
    lanedetection_rgb_B.tmpOutRC[3U] = -1;
  }

  lanedetection_rgb_B.HoughLines[0] = lanedetection_rgb_B.tmpOutRC[1] + 1;
  lanedetection_rgb_B.HoughLines[2] = lanedetection_rgb_B.tmpOutRC[0] + 1;
  lanedetection_rgb_B.HoughLines[4] = lanedetection_rgb_B.tmpOutRC[3] + 1;
  lanedetection_rgb_B.HoughLines[6] = lanedetection_rgb_B.tmpOutRC[2] + 1;
  lanedetection_rgb_B.imgRow = 0;
  lanedetection_rgb_B.imgCol = lanedetection_rgb_B.HoughTransform_o2[(int32_T)
    lanedetection_rgb_B.Submatrix1[1] - 1];
  if (lanedetection_rgb_B.HoughTransform_o2[(int32_T)
      lanedetection_rgb_B.Submatrix1[1] - 1] > 102944) {
    while (lanedetection_rgb_B.imgCol > 102944) {
      lanedetection_rgb_B.imgCol -= 205888;
    }
  } else {
    if (lanedetection_rgb_B.HoughTransform_o2[(int32_T)
        lanedetection_rgb_B.Submatrix1[1] - 1] < -102944) {
      while (lanedetection_rgb_B.imgCol < -102944) {
        lanedetection_rgb_B.imgCol += 205888;
      }
    }
  }

  if (lanedetection_rgb_B.imgCol > 2147380703) {
    lanedetection_rgb_B.imgCol = MAX_int32_T;
  } else {
    lanedetection_rgb_B.imgCol += 102944;
  }

  lanedetection_rgb_B.imgCol = div_repeat_s32_sat_near
    (lanedetection_rgb_B.imgCol, 143, 13U);
  thetaIdx = ((lanedetection_rgb_B.imgCol & 32768U) != 0U) +
    (lanedetection_rgb_B.imgCol >> 16);
  if (thetaIdx < 0) {
    thetaIdx = 0;
  } else {
    if (thetaIdx > 180) {
      thetaIdx = 180;
    }
  }

  if (thetaIdx < 91) {
    lanedetection_rgb_B.imgCol =
      -lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[90 - thetaIdx];
    if (lanedetection_rgb_B.imgCol > 32767) {
      lanedetection_rgb_B.imgCol = 32767;
    }

    lanedetection_rgb_B.imgCol <<= 3;
    if (lanedetection_rgb_B.imgCol == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[1] - 1] > 0) {
        imgIdx = MAX_int32_T;
      } else {
        imgIdx = MIN_int32_T;
      }
    } else {
      imgIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[1] - 1],
        lanedetection_rgb_B.imgCol, 16U);
    }

    if (lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[thetaIdx] == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[1] - 1] > 0) {
        thetaIdx = MAX_int32_T;
      } else {
        thetaIdx = MIN_int32_T;
      }
    } else {
      thetaIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[1] - 1],
        lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[thetaIdx], 13U);
    }
  } else {
    lanedetection_rgb_B.imgCol =
      -lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[thetaIdx - 90];
    if (lanedetection_rgb_B.imgCol > 32767) {
      lanedetection_rgb_B.imgCol = 32767;
    }

    lanedetection_rgb_B.imgCol <<= 3;
    if (lanedetection_rgb_B.imgCol == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[1] - 1] > 0) {
        imgIdx = MAX_int32_T;
      } else {
        imgIdx = MIN_int32_T;
      }
    } else {
      imgIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[1] - 1],
        lanedetection_rgb_B.imgCol, 16U);
    }

    lanedetection_rgb_B.imgCol =
      -lanedetection_rgb_ConstP.HoughLines_SINE_TABLE_RTP[180 - thetaIdx];
    if (lanedetection_rgb_B.imgCol > 32767) {
      lanedetection_rgb_B.imgCol = 32767;
    }

    lanedetection_rgb_B.imgCol <<= 3;
    if (lanedetection_rgb_B.imgCol == 0) {
      if (lanedetection_rgb_B.HoughTransform_o3[(int32_T)
          lanedetection_rgb_B.Submatrix[1] - 1] > 0) {
        thetaIdx = MAX_int32_T;
      } else {
        thetaIdx = MIN_int32_T;
      }
    } else {
      thetaIdx = div_repeat_s32_sat_near(lanedetection_rgb_B.HoughTransform_o3
        [(int32_T)lanedetection_rgb_B.Submatrix[1] - 1],
        lanedetection_rgb_B.imgCol, 16U);
    }
  }

  /* part-1: top horizontal axis */
  lanedetection_rgb_B.imgCol = ((imgIdx & 32768U) != 0U) + (imgIdx >> 16);
  if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 69)) {
    lanedetection_rgb_B.tmpOutRC[0U] = 0;
    lanedetection_rgb_B.tmpOutRC[1U] = (int16_T)lanedetection_rgb_B.imgCol;
    lanedetection_rgb_B.imgRow = 1;
  }

  /* part-2: left vertical axis */
  lanedetection_rgb_B.imgCol = ((thetaIdx & 32768U) != 0U) + (thetaIdx >> 16);
  if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 315))
  {
    lanedetection_rgb_B.tmpOutRC[lanedetection_rgb_B.imgRow << 1] = (int16_T)
      lanedetection_rgb_B.imgCol;
    lanedetection_rgb_B.tmpOutRC[1 + (lanedetection_rgb_B.imgRow << 1)] = 0;
    lanedetection_rgb_B.imgRow++;
  }

  /* part-3: Right vertical axis */
  if (lanedetection_rgb_B.imgRow < 2) {
    if ((imgIdx >= 0) && (4521984 < imgIdx - MAX_int32_T)) {
      lanedetection_rgb_B.imgCol = MAX_int32_T;
    } else if ((imgIdx < 0) && (4521984 > imgIdx - MIN_int32_T)) {
      lanedetection_rgb_B.imgCol = MIN_int32_T;
    } else {
      lanedetection_rgb_B.imgCol = imgIdx - 4521984;
    }

    if (imgIdx == 0) {
      if (thetaIdx > 0) {
        thetaIdx2 = MAX_int32_T;
      } else {
        thetaIdx2 = MIN_int32_T;
      }
    } else {
      thetaIdx2 = div_repeat_s32_sat_near(thetaIdx, imgIdx, 16U);
    }

    lanedetection_rgb_B.imgCol = mul_s32_loSR_sat_near
      (lanedetection_rgb_B.imgCol, thetaIdx2, 16U);
    lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.imgCol & 32768U) != 0U) +
      (lanedetection_rgb_B.imgCol >> 16);
    if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 315))
    {
      lanedetection_rgb_B.tmpOutRC[lanedetection_rgb_B.imgRow << 1] = (int16_T)
        lanedetection_rgb_B.imgCol;
      lanedetection_rgb_B.tmpOutRC[1 + (lanedetection_rgb_B.imgRow << 1)] = 69;
      lanedetection_rgb_B.imgRow++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (lanedetection_rgb_B.imgRow < 2) {
    if (thetaIdx == 0) {
      if (imgIdx > 0) {
        thetaIdx = MAX_int32_T;
      } else {
        thetaIdx = MIN_int32_T;
      }
    } else {
      thetaIdx = div_repeat_s32_sat_near(imgIdx, thetaIdx, 16U);
    }

    lanedetection_rgb_B.imgCol = mul_s32_sat(thetaIdx, 315);
    if ((imgIdx >= 0) && (lanedetection_rgb_B.imgCol < imgIdx - MAX_int32_T)) {
      lanedetection_rgb_B.imgCol = MAX_int32_T;
    } else if ((imgIdx < 0) && (lanedetection_rgb_B.imgCol > imgIdx -
                MIN_int32_T)) {
      lanedetection_rgb_B.imgCol = MIN_int32_T;
    } else {
      lanedetection_rgb_B.imgCol = imgIdx - lanedetection_rgb_B.imgCol;
    }

    lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.imgCol & 32768U) != 0U) +
      (lanedetection_rgb_B.imgCol >> 16);
    if ((lanedetection_rgb_B.imgCol >= 0) && (lanedetection_rgb_B.imgCol <= 69))
    {
      lanedetection_rgb_B.tmpOutRC[lanedetection_rgb_B.imgRow << 1] = 315;
      lanedetection_rgb_B.tmpOutRC[1 + (lanedetection_rgb_B.imgRow << 1)] =
        (int16_T)lanedetection_rgb_B.imgCol;
      lanedetection_rgb_B.imgRow++;
    }
  }

  if (lanedetection_rgb_B.imgRow < 2) {
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
    /* Update view port. */
    for (lanedetection_rgb_B.imgCol = 0; lanedetection_rgb_B.imgCol < 2;
         lanedetection_rgb_B.imgCol++) {
      thetaIdx = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.imgCol + 2]
        - 1;
      j = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.imgCol] - 1;
      if ((lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.imgCol + 6] - 1 !=
           thetaIdx) || (lanedetection_rgb_B.HoughLines[4 +
                         lanedetection_rgb_B.imgCol] - 1 != j)) {
        isMore = false;
        thetaIdx = (thetaIdx << 3) + 4;
        cellIdx = ((lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.imgCol +
                    6] - 1) << 3) + 4;
        j = (j << 3) + 4;
        acc1_idx_5 = ((lanedetection_rgb_B.HoughLines[4 +
                       lanedetection_rgb_B.imgCol] - 1) << 3) + 4;

        /* Find the visible portion of a line. */
        prevEdgeIsVertical = false;
        visited2 = false;
        done = false;
        lanedetection_rgb_B.imgRow = thetaIdx;
        thetaIdx2 = j;
        imgIdx = cellIdx;
        q2 = acc1_idx_5;
        while (!done) {
          lanedetection_rgb_B.numUniquePix = 0;
          lanedetection_rgb_B.loc = 0;

          /* Determine viewport violations. */
          if (lanedetection_rgb_B.imgRow < 0) {
            lanedetection_rgb_B.numUniquePix = 4;
          } else {
            if (lanedetection_rgb_B.imgRow > 2527) {
              lanedetection_rgb_B.numUniquePix = 8;
            }
          }

          if (imgIdx < 0) {
            lanedetection_rgb_B.loc = 4;
          } else {
            if (imgIdx > 2527) {
              lanedetection_rgb_B.loc = 8;
            }
          }

          if (thetaIdx2 < 0) {
            lanedetection_rgb_B.numUniquePix |= 1U;
          } else {
            if (thetaIdx2 > 559) {
              lanedetection_rgb_B.numUniquePix |= 2U;
            }
          }

          if (q2 < 0) {
            lanedetection_rgb_B.loc |= 1U;
          } else {
            if (q2 > 559) {
              lanedetection_rgb_B.loc |= 2U;
            }
          }

          if (!(((uint32_T)lanedetection_rgb_B.numUniquePix |
                 lanedetection_rgb_B.loc) != 0U)) {
            /* Line falls completely within bounds. */
            done = true;
            isMore = true;
          } else if (((uint32_T)lanedetection_rgb_B.numUniquePix &
                      lanedetection_rgb_B.loc) != 0U) {
            /* Line falls completely out of bounds. */
            done = true;
            isMore = false;
          } else if ((uint32_T)lanedetection_rgb_B.numUniquePix != 0U) {
            /* Clip 1st point; if it's in-bounds, clip 2nd point. */
            if (prevEdgeIsVertical) {
              lanedetection_rgb_B.imgRow = thetaIdx;
              thetaIdx2 = j;
            }

            lanedetection_rgb_B.idxCol1 = imgIdx - lanedetection_rgb_B.imgRow;
            lanedetection_rgb_B.idxCol2 = q2 - thetaIdx2;
            if ((lanedetection_rgb_B.idxCol1 > 1073741824) ||
                (lanedetection_rgb_B.idxCol1 < -1073741824) ||
                ((lanedetection_rgb_B.idxCol2 > 1073741824) ||
                 (lanedetection_rgb_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              done = true;
              isMore = false;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_rgb_B.numUniquePix = -lanedetection_rgb_B.imgRow *
                lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                thetaIdx2 += (div_s32_floor(lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                thetaIdx2 -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              lanedetection_rgb_B.imgRow = 0;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_rgb_B.numUniquePix = (2527 -
                lanedetection_rgb_B.imgRow) * lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                thetaIdx2 += (div_s32_floor(lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                thetaIdx2 -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              lanedetection_rgb_B.imgRow = 2527;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_rgb_B.numUniquePix = -thetaIdx2 *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                lanedetection_rgb_B.imgRow += (div_s32_floor
                  (lanedetection_rgb_B.numUniquePix << 1,
                   lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                lanedetection_rgb_B.imgRow -= (div_s32_floor
                  (-lanedetection_rgb_B.numUniquePix << 1,
                   lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              thetaIdx2 = 0;
              prevEdgeIsVertical = true;
            } else {
              /* Violated CMax. */
              lanedetection_rgb_B.numUniquePix = (559 - thetaIdx2) *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                lanedetection_rgb_B.imgRow += (div_s32_floor
                  (lanedetection_rgb_B.numUniquePix << 1,
                   lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                lanedetection_rgb_B.imgRow -= (div_s32_floor
                  (-lanedetection_rgb_B.numUniquePix << 1,
                   lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              thetaIdx2 = 559;
              prevEdgeIsVertical = true;
            }
          } else {
            /* Clip the 2nd point. */
            if (visited2) {
              imgIdx = cellIdx;
              q2 = acc1_idx_5;
            }

            lanedetection_rgb_B.idxCol1 = imgIdx - lanedetection_rgb_B.imgRow;
            lanedetection_rgb_B.idxCol2 = q2 - thetaIdx2;
            if ((lanedetection_rgb_B.idxCol1 > 1073741824) ||
                (lanedetection_rgb_B.idxCol1 < -1073741824) ||
                ((lanedetection_rgb_B.idxCol2 > 1073741824) ||
                 (lanedetection_rgb_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              done = true;
              isMore = false;
              visited2 = true;
            } else if ((lanedetection_rgb_B.loc & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_rgb_B.numUniquePix = -imgIdx *
                lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                q2 += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                q2 -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              imgIdx = 0;
              visited2 = true;
            } else if ((lanedetection_rgb_B.loc & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_rgb_B.numUniquePix = (2527 - imgIdx) *
                lanedetection_rgb_B.idxCol2;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol1 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol1 < 0))) {
                q2 += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                q2 -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              imgIdx = 2527;
              visited2 = true;
            } else if ((lanedetection_rgb_B.loc & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_rgb_B.numUniquePix = -q2 *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                imgIdx += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              q2 = 0;
              visited2 = true;
            } else {
              /* Violated CMax. */
              lanedetection_rgb_B.numUniquePix = (559 - q2) *
                lanedetection_rgb_B.idxCol1;
              if ((lanedetection_rgb_B.numUniquePix > 1073741824) ||
                  (lanedetection_rgb_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_rgb_B.numUniquePix >= 0) &&
                          (lanedetection_rgb_B.idxCol2 >= 0)) ||
                         ((lanedetection_rgb_B.numUniquePix < 0) &&
                          (lanedetection_rgb_B.idxCol2 < 0))) {
                imgIdx += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                            lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              q2 = 559;
              visited2 = true;
            }
          }
        }

        if (isMore) {
          /* Initialize the Bresenham algorithm. */
          if (imgIdx >= lanedetection_rgb_B.imgRow) {
            cellIdx = imgIdx - lanedetection_rgb_B.imgRow;
          } else {
            cellIdx = lanedetection_rgb_B.imgRow - imgIdx;
          }

          if (q2 >= thetaIdx2) {
            acc1_idx_5 = q2 - thetaIdx2;
          } else {
            acc1_idx_5 = thetaIdx2 - q2;
          }

          if (cellIdx > acc1_idx_5) {
            thetaIdx = 1;
            j = 316;
          } else {
            thetaIdx = 316;
            j = 1;
            cellIdx = lanedetection_rgb_B.imgRow;
            lanedetection_rgb_B.imgRow = thetaIdx2;
            thetaIdx2 = cellIdx;
            cellIdx = imgIdx;
            imgIdx = q2;
            q2 = cellIdx;
          }

          if (lanedetection_rgb_B.imgRow > imgIdx) {
            cellIdx = lanedetection_rgb_B.imgRow;
            lanedetection_rgb_B.imgRow = imgIdx;
            imgIdx = cellIdx;
            cellIdx = thetaIdx2;
            thetaIdx2 = q2;
            q2 = cellIdx;
          }

          cellIdx = imgIdx - lanedetection_rgb_B.imgRow;
          if (thetaIdx2 <= q2) {
            acc1_idx_5 = 1;
            lanedetection_rgb_B.idxCol1 = q2 - thetaIdx2;
          } else {
            acc1_idx_5 = -1;
            lanedetection_rgb_B.idxCol1 = thetaIdx2 - q2;
          }

          lanedetection_rgb_B.idxCol2 = thetaIdx2 - 4;
          lanedetection_rgb_B.numUniquePix = -((cellIdx + 1) >> 1);
          if (thetaIdx != 1) {
            lanedetection_rgb_B.loc = 2527;
          } else {
            lanedetection_rgb_B.loc = 559;
          }

          lanedetection_rgb_B.loc_m = lanedetection_rgb_B.imgRow >> 3;
          lanedetection_rgb_B.lastRowOut = ((lanedetection_rgb_B.loc_m + 1) << 3)
            - lanedetection_rgb_B.imgRow;
          lanedetection_rgb_B.idxRow2 = 316;
          lanedetection_rgb_B.idxTmp = 0;
          memset(&lanedetection_rgb_DW.DrawShapes_DW_PixCount[0], 0, 316U *
                 sizeof(uint8_T));
          done = (lanedetection_rgb_B.imgRow <= imgIdx);
          while (done) {
            lanedetection_rgb_B.lastRowOut--;
            lanedetection_rgb_B.col = lanedetection_rgb_B.idxCol2;

            /* Compute the next location using Bresenham algorithm. */
            /* Move to the next sub-pixel location. */
            lanedetection_rgb_B.numUniquePix += lanedetection_rgb_B.idxCol1;
            if (lanedetection_rgb_B.numUniquePix >= 0) {
              lanedetection_rgb_B.idxCol2 += acc1_idx_5;
              lanedetection_rgb_B.numUniquePix -= cellIdx;
            }

            lanedetection_rgb_B.imgRow++;
            done = (lanedetection_rgb_B.imgRow <= imgIdx);
            if (done) {
              lanedetection_rgb_B.lastRow = lanedetection_rgb_B.col + 7;
              if ((lanedetection_rgb_B.col + 7 > 0) && (lanedetection_rgb_B.col <
                   lanedetection_rgb_B.loc)) {
                if (lanedetection_rgb_B.col < 0) {
                  lanedetection_rgb_B.col = 0;
                }

                if (lanedetection_rgb_B.lastRow > lanedetection_rgb_B.loc) {
                  lanedetection_rgb_B.lastRow = lanedetection_rgb_B.loc;
                }

                q2 = lanedetection_rgb_B.col >> 3;
                thetaIdx2 = lanedetection_rgb_B.lastRow >> 3;
                if (lanedetection_rgb_B.idxRow2 > q2) {
                  lanedetection_rgb_B.idxRow2 = q2;
                }

                if (lanedetection_rgb_B.idxTmp < thetaIdx2) {
                  lanedetection_rgb_B.idxTmp = thetaIdx2;
                }

                if (thetaIdx2 > q2) {
                  lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                    (((uint32_T)((q2 + 1) << 3) +
                      lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2]) -
                     lanedetection_rgb_B.col);
                  lanedetection_rgb_DW.DrawShapes_DW_PixCount[thetaIdx2] =
                    (uint8_T)(((uint32_T)(lanedetection_rgb_B.lastRow -
                    (thetaIdx2 << 3)) +
                               lanedetection_rgb_DW.DrawShapes_DW_PixCount[thetaIdx2])
                              + 1U);
                  for (q2++; q2 < thetaIdx2; q2++) {
                    lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                      (lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] + 8U);
                  }
                } else {
                  if (thetaIdx2 == q2) {
                    lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                      (((uint32_T)(lanedetection_rgb_B.lastRow -
                                   lanedetection_rgb_B.col) +
                        lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2]) + 1U);
                  }
                }
              }
            }

            if ((lanedetection_rgb_B.lastRowOut == 0) || (!done)) {
              while (lanedetection_rgb_B.idxRow2 <= lanedetection_rgb_B.idxTmp)
              {
                thetaIdx2 = lanedetection_rgb_B.loc_m * thetaIdx +
                  lanedetection_rgb_B.idxRow2 * j;
                if (lanedetection_rgb_DW.DrawShapes_DW_PixCount[lanedetection_rgb_B.idxRow2]
                    == 64) {
                  lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] = (uint8_T)
                    ((((lanedetection_rgb_P.DrawShapes_color[0] << 14) -
                       (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] << 14)) +
                      (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] << 14)) >>
                     14);
                  lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] = (uint8_T)
                    ((((lanedetection_rgb_P.DrawShapes_color[1] << 14) -
                       (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] << 14)) +
                      (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] << 14)) >>
                     14);
                  lanedetection_rgb_B.DrawShapes_o3[thetaIdx2] = (uint8_T)
                    ((((lanedetection_rgb_P.DrawShapes_color[2] << 14) -
                       (lanedetection_rgb_B.DrawShapes_o3[thetaIdx2] << 14)) +
                      (lanedetection_rgb_B.DrawShapes_o3[thetaIdx2] << 14)) >>
                     14);
                } else {
                  lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] = (uint8_T)
                    ((((((lanedetection_rgb_P.DrawShapes_color[0] << 14) -
                         (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] << 14)) *
                        lanedetection_rgb_DW.DrawShapes_DW_PixCount[lanedetection_rgb_B.idxRow2])
                       >> 6) + (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] <<
                                14)) >> 14);
                  lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] = (uint8_T)
                    ((((((lanedetection_rgb_P.DrawShapes_color[1] << 14) -
                         (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] << 14)) *
                        lanedetection_rgb_DW.DrawShapes_DW_PixCount[lanedetection_rgb_B.idxRow2])
                       >> 6) + (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] <<
                                14)) >> 14);
                  lanedetection_rgb_B.DrawShapes_o3[thetaIdx2] = (uint8_T)
                    ((((((lanedetection_rgb_P.DrawShapes_color[2] << 14) -
                         (lanedetection_rgb_B.DrawShapes_o3[thetaIdx2] << 14)) *
                        lanedetection_rgb_DW.DrawShapes_DW_PixCount[lanedetection_rgb_B.idxRow2])
                       >> 6) + (lanedetection_rgb_B.DrawShapes_o3[thetaIdx2] <<
                                14)) >> 14);
                }

                lanedetection_rgb_DW.DrawShapes_DW_PixCount[lanedetection_rgb_B.idxRow2]
                  = 0U;
                lanedetection_rgb_B.idxRow2++;
              }

              lanedetection_rgb_B.lastRowOut = 8;
              lanedetection_rgb_B.idxRow2 = 316;
              lanedetection_rgb_B.idxTmp = 0;
              lanedetection_rgb_B.loc_m++;
            }
          }
        }
      }
    }
  } else {
    /* Compute output for non-unity line width
     */
    /* Copy the image from input to output. */
    /* Update view port. */
    /* ProcessStep-start-1
     */
    if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
      /* convertLinePts2PolygonPts
       */
      lanedetection_rgb_B.imgRow = lanedetection_rgb_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      imgIdx = lanedetection_rgb_B.HoughLines[2] -
        lanedetection_rgb_B.HoughLines[6];
      thetaIdx = lanedetection_rgb_B.HoughLines[0] -
        lanedetection_rgb_B.HoughLines[4];
      if (thetaIdx == 0) {
        q2 = 0;
        thetaIdx2 = 1;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[0] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[0] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[2] - 1) << 14;
      } else if (imgIdx == 0) {
        thetaIdx2 = 2;
        q2 = 0;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[2] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[2] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[0] - 1) << 14;
      } else {
        thetaIdx2 = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, thetaIdx << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[0] - 1) << 14, q2, 14U);
        cellIdx = div_repeat_s32_floor(lanedetection_rgb_B.imgRow << 14,
          div_repeat_s32_floor(thetaIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0
          ((imgIdx * imgIdx + thetaIdx * thetaIdx) << 14) << 7, 14U), 14U);
        lanedetection_rgb_B.imgCol = j + cellIdx;
        j -= cellIdx;
        cellIdx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[0] - 1) <<
          14, q2, 14U) + ((lanedetection_rgb_B.HoughLines[2] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (thetaIdx2 == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[0] =
          ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
          (lanedetection_rgb_B.imgCol >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[2] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((j & 8192U) != 0U) + (j
          >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[14] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
      } else {
        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[2] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx -
            lanedetection_rgb_B.imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[2] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        }

        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[14] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx - j, q2, 14U),
            mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[14] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
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
      if (thetaIdx == 0) {
        q2 = 0;
        thetaIdx2 = 1;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[0] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[0] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[6] - 1) << 14;
      } else if (imgIdx == 0) {
        thetaIdx2 = 2;
        q2 = 0;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[2] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[2] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[4] - 1) << 14;
      } else {
        thetaIdx2 = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, thetaIdx << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[0] - 1) << 14, q2, 14U);
        cellIdx = div_repeat_s32_floor(lanedetection_rgb_B.imgRow << 14,
          div_repeat_s32_floor(thetaIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0
          ((imgIdx * imgIdx + thetaIdx * thetaIdx) << 14) << 7, 14U), 14U);
        lanedetection_rgb_B.imgCol = j + cellIdx;
        j -= cellIdx;
        cellIdx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[4] - 1) <<
          14, q2, 14U) + ((lanedetection_rgb_B.HoughLines[6] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (thetaIdx2 == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[4] =
          ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
          (lanedetection_rgb_B.imgCol >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[6] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((j & 8192U) != 0U) + (j >>
          14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[10] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
      } else {
        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[6] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx -
            lanedetection_rgb_B.imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[6] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        }

        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[10] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx - j, q2, 14U),
            mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[10] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      lanedetection_rgb_B.imgRow = lanedetection_rgb_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      imgIdx = lanedetection_rgb_B.HoughLines[3] -
        lanedetection_rgb_B.HoughLines[7];
      thetaIdx = lanedetection_rgb_B.HoughLines[1] -
        lanedetection_rgb_B.HoughLines[5];
      if (thetaIdx == 0) {
        q2 = 0;
        thetaIdx2 = 1;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[1] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[1] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[3] - 1) << 14;
      } else if (imgIdx == 0) {
        thetaIdx2 = 2;
        q2 = 0;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[3] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[3] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[1] - 1) << 14;
      } else {
        thetaIdx2 = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, thetaIdx << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[1] - 1) << 14, q2, 14U);
        cellIdx = div_repeat_s32_floor(lanedetection_rgb_B.imgRow << 14,
          div_repeat_s32_floor(thetaIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0
          ((imgIdx * imgIdx + thetaIdx * thetaIdx) << 14) << 7, 14U), 14U);
        lanedetection_rgb_B.imgCol = j + cellIdx;
        j -= cellIdx;
        cellIdx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[1] - 1) <<
          14, q2, 14U) + ((lanedetection_rgb_B.HoughLines[3] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (thetaIdx2 == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[1] =
          ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
          (lanedetection_rgb_B.imgCol >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[3] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((j & 8192U) != 0U) + (j
          >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[15] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
      } else {
        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[3] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx -
            lanedetection_rgb_B.imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[3] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        }

        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[15] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx - j, q2, 14U),
            mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[15] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
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
      if (thetaIdx == 0) {
        q2 = 0;
        thetaIdx2 = 1;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[1] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[1] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[7] - 1) << 14;
      } else if (imgIdx == 0) {
        thetaIdx2 = 2;
        q2 = 0;
        lanedetection_rgb_B.imgCol = ((lanedetection_rgb_B.HoughLines[3] -
          lanedetection_rgb_B.imgRow) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[3] + lanedetection_rgb_B.imgRow) -
             1) << 14;
        cellIdx = (lanedetection_rgb_B.HoughLines[5] - 1) << 14;
      } else {
        thetaIdx2 = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, thetaIdx << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[1] - 1) << 14, q2, 14U);
        cellIdx = div_repeat_s32_floor(lanedetection_rgb_B.imgRow << 14,
          div_repeat_s32_floor(thetaIdx << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0
          ((imgIdx * imgIdx + thetaIdx * thetaIdx) << 14) << 7, 14U), 14U);
        lanedetection_rgb_B.imgCol = j + cellIdx;
        j -= cellIdx;
        cellIdx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[5] - 1) <<
          14, q2, 14U) + ((lanedetection_rgb_B.HoughLines[7] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (thetaIdx2 == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[5] =
          ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
          (lanedetection_rgb_B.imgCol >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[7] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((j & 8192U) != 0U) + (j >>
          14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[11] = ((cellIdx & 8192U) != 0U)
          + (cellIdx >> 14);
      } else {
        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[7] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx -
            lanedetection_rgb_B.imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) +
            16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[7] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        }

        if (thetaIdx2 == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((cellIdx & 8192U) !=
            0U) + (cellIdx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[11] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(cellIdx - j, q2, 14U),
            mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((acc1_idx_5 & 8192U)
            != 0U) + (acc1_idx_5 >> 14);
          lanedetection_rgb_B.imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[11] =
            ((lanedetection_rgb_B.imgCol & 8192U) != 0U) +
            (lanedetection_rgb_B.imgCol >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
    }

    /* ProcessStep-after poly points-1
     */
    lanedetection_rgb_B.imgCol = 2;

    /* just before call for cgpolygon
     */
    if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
      /* just before call for cgpolygon-2
       */
      lanedetection_rgb_B.imgCol = 4;
    }

    lanedetection_rgb_B.imgRow = lanedetection_rgb_B.imgCol << 1;
    memset(&lanedetection_rgb_DW.DrawShapes_DW_PixCount[0], 0, 316U * sizeof
           (uint8_T));

    /* Reset scanline states. */
    imgIdx = 0;
    thetaIdx = 0;
    idxTmpArray[0U] = (int8_T)(lanedetection_rgb_B.imgCol - 1);
    isMore = true;
    while (isMore) {
      /* Initialize the scanline. */
      /* Convert polygon vertices to boundaries. */
      q2 = 0;
      j = imgIdx;
      cellIdx = imgIdx;

      /* start for loop
       */
      acc1_idx_5 = (((idxTmpArray[0] << 1) + 1) << 1) + thetaIdx;
      lanedetection_rgb_B.idxCol1 = (idxTmpArray[0] << 2) + thetaIdx;
      lanedetection_rgb_B.idxTmp = idxTmpArray[0];
      lanedetection_rgb_B.idxCol2 = ((idxTmpArray[0] - 1) << 2) + thetaIdx;
      lanedetection_rgb_B.numUniquePix = lanedetection_rgb_B.imgCol;
      if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];

        /* getLoc-1
         */
        thetaIdx2 =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];

        /* getLoc-2
         */
        thetaIdx2 = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];
      }

      while ((lanedetection_rgb_B.idxCol2 >= 0) && (lanedetection_rgb_B.loc - 1 ==
              thetaIdx2 - 1)) {
        lanedetection_rgb_B.idxTmp--;
        lanedetection_rgb_B.idxCol2 = ((lanedetection_rgb_B.idxTmp - 1) << 2) +
          thetaIdx;
        lanedetection_rgb_B.numUniquePix--;
        if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          thetaIdx2 =
            lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];
        } else {
          /* getLoc-2
           */
          thetaIdx2 = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];
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

      done = (lanedetection_rgb_B.loc_m - 1 > lanedetection_rgb_B.loc - 1);
      lanedetection_rgb_B.idxRow2 = 2 + thetaIdx;
      lanedetection_rgb_B.idxCol2 = thetaIdx;
      prevEdgeIsVertical = false;
      if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_DW.DrawShapes_DW_Points[thetaIdx];

        /* getLoc-1
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];
      } else {
        /* getLoc-2
         */
        lanedetection_rgb_B.loc = lanedetection_rgb_B.HoughLines[thetaIdx];

        /* getLoc-2
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];
      }

      for (thetaIdx2 = 0; thetaIdx2 < lanedetection_rgb_B.numUniquePix;
           thetaIdx2++) {
        if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          lanedetection_rgb_B.lastRowOut =
            lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];

          /* getLoc-1
           */
          lanedetection_rgb_B.lastRow =
            lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];
        } else {
          /* getLoc-2
           */
          lanedetection_rgb_B.lastRowOut =
            lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];

          /* getLoc-2
           */
          lanedetection_rgb_B.lastRow =
            lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];
        }

        if (lanedetection_rgb_B.lastRow - 1 != lanedetection_rgb_B.lastRowOut -
            1) {
          if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_rgb_B.lastRowOut =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_rgb_B.lastRow =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];
          } else {
            /* getLoc-2
             */
            lanedetection_rgb_B.lastRowOut =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_rgb_B.lastRow =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];
          }

          if (lanedetection_rgb_B.lastRow - 1 < lanedetection_rgb_B.lastRowOut -
              1) {
            isMore = false;
          } else {
            isMore = true;
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
            lanedetection_rgb_B.lastRowOut =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_rgb_B.lastRow =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxRow2];

            /* getLoc-1
             */
            lanedetection_rgb_B.col =
              lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];

            /* getLoc-1
             */
            lanedetection_rgb_B.idxTmp =
              lanedetection_rgb_DW.DrawShapes_DW_Points[acc1_idx_5];
          } else {
            /* getLoc-2
             */
            lanedetection_rgb_B.lastRowOut =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_rgb_B.lastRow =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxRow2];

            /* getLoc-2
             */
            lanedetection_rgb_B.col =
              lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];

            /* getLoc-2
             */
            lanedetection_rgb_B.idxTmp =
              lanedetection_rgb_B.HoughLines[acc1_idx_5];
          }

          /* Initialize a Bresenham line. */
          lanedetection_rgb_B.idxTmp = ((lanedetection_rgb_B.idxTmp - 1) << 3) +
            4;
          lanedetection_rgb_B.col = ((lanedetection_rgb_B.col - 1) << 3) + 4;
          lanedetection_rgb_B.lastRow = ((lanedetection_rgb_B.lastRow - 1) << 3)
            + 4;
          lanedetection_rgb_B.lastRowOut = ((lanedetection_rgb_B.lastRowOut - 1)
            << 3) + 4;
          lanedetection_rgb_B.firstRow = lanedetection_rgb_B.lastRowOut -
            lanedetection_rgb_B.col;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx] = 0;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 1] =
            lanedetection_rgb_B.idxTmp;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 2] =
            lanedetection_rgb_B.col;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 3] =
            lanedetection_rgb_B.lastRowOut;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 6] = 0;
          if (lanedetection_rgb_B.lastRow >= lanedetection_rgb_B.idxTmp) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 8] =
              lanedetection_rgb_B.lastRow - lanedetection_rgb_B.idxTmp;
          } else {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 8] =
              lanedetection_rgb_B.idxTmp - lanedetection_rgb_B.lastRow;
          }

          while (lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 8] >= 0) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 6]++;
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 8] -=
              lanedetection_rgb_B.firstRow;
          }

          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 5] =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 6] - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 7] =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 8] +
            lanedetection_rgb_B.firstRow;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 4] =
            lanedetection_rgb_B.firstRow -
            (lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 7] << 1);
          if (lanedetection_rgb_B.idxTmp > lanedetection_rgb_B.lastRow) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 5] =
              -lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 5];
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 6] =
              -lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 6];
          }

          if ((!done) && (!isMore)) {
            /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 2]++;
            if ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx] << 1) >
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 4]) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 8];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 1] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 6];
            } else {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 7];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 1] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 5];
            }
          } else {
            if (done && isMore) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 3]--;
            }
          }

          done = isMore;
          if (!prevEdgeIsVertical) {
            /* Merge two Bresenham lines. */
            prevEdgeIsVertical = false;
            if ((j != cellIdx) && ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[j
                  + 5] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 5])
                 && (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 6] ==
                     lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 6]) &&
                 (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 7] ==
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 7]) &&
                                   (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j
                  + 8] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 8])))
            {
              if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3] + 1 ==
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 2]) {
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3] =
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 3];
                prevEdgeIsVertical = true;
              } else {
                if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 3] + 1 ==
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2]) {
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1] =
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 1];
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2] =
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 2];
                  prevEdgeIsVertical = true;
                }
              }
            }

            if (!prevEdgeIsVertical) {
              j = cellIdx;
              q2++;
            }
          } else {
            j = cellIdx;
            q2++;
          }

          cellIdx = j + 9;
          if (!isMore) {
            acc1_idx_5 = lanedetection_rgb_B.idxRow2;
            lanedetection_rgb_B.idxCol1 = lanedetection_rgb_B.idxCol2;
          }

          lanedetection_rgb_B.idxRow2 = acc1_idx_5 + 4;
          lanedetection_rgb_B.idxCol2 = lanedetection_rgb_B.idxCol1 + 4;
          prevEdgeIsVertical = false;
        } else {
          prevEdgeIsVertical = true;
          acc1_idx_5 = lanedetection_rgb_B.idxRow2;
          lanedetection_rgb_B.idxCol1 = lanedetection_rgb_B.idxCol2;
          lanedetection_rgb_B.idxRow2 += 4;
          lanedetection_rgb_B.idxCol2 += 4;
        }
      }

      if (!(lanedetection_rgb_B.loc_m - 1 == lanedetection_rgb_B.loc - 1)) {
        /* Merge two Bresenham lines. */
        done = false;
        if ((imgIdx != j) && ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx
              + 5] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 5]) &&
                              (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx
              + 6] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 6]) &&
                              (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx
              + 7] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 7]) &&
                              (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx
              + 8] == lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 8]))) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 3] + 1 ==
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2]) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 3] =
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3];
            done = true;
          } else {
            if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3] + 1 ==
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 2]) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 1] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 2] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2];
              done = true;
            }
          }
        }

        if (done) {
          q2--;
          cellIdx -= 9;
        }
      }

      /* Set all other edges to invalid. */
      for (thetaIdx2 = q2; thetaIdx2 < lanedetection_rgb_B.imgCol; thetaIdx2++)
      {
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 2] = 1;
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[cellIdx + 3] = 0;
        cellIdx += 9;
      }

      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_rgb_B.idxNew = imgIdx;
        lanedetection_rgb_B.idxOld = imgIdx + 9;
        isMore = false;
        for (thetaIdx2 = 1; thetaIdx2 < q2; thetaIdx2++) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
              + 2] >
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
              + 2]) {
            isMore = true;
            for (j = 0; j < 9; j++) {
              edgeTmp_tmp = lanedetection_rgb_B.idxNew + j;
              lanedetection_rgb_B.edgeTmp =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_rgb_B.idxOld + j;
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
      j = imgIdx + 3;
      cellIdx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 3];
      for (thetaIdx2 = 1; thetaIdx2 < q2; thetaIdx2++) {
        j += 9;
        if (cellIdx < lanedetection_rgb_DW.DrawShapes_DW_Polygon[j]) {
          cellIdx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j];
        }
      }

      acc1_idx_5 = cellIdx;
      if (cellIdx > 559) {
        acc1_idx_5 = 559;
      }

      /* Find out the first column of the polygon. */
      j = imgIdx + 2;
      cellIdx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[imgIdx + 2];
      for (thetaIdx2 = 1; thetaIdx2 < q2; thetaIdx2++) {
        j += 9;
        if (cellIdx > lanedetection_rgb_DW.DrawShapes_DW_Polygon[j]) {
          cellIdx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j];
        }
      }

      if (cellIdx < 0) {
        cellIdx = 0;
      }

      /* Move to the next column and find out boundaries of the polygon at this column. */
      lanedetection_rgb_B.idxNew = imgIdx;
      lanedetection_rgb_B.idxOld = imgIdx;
      lanedetection_rgb_B.idxCol1 = imgIdx;
      lanedetection_rgb_B.idxCol2 = 0;
      lanedetection_rgb_B.numActiveEdge = 0;
      for (thetaIdx2 = 0; thetaIdx2 < q2; thetaIdx2++) {
        /* Find out the valid boundaries and bring them to the latest column. */
        if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
            + 3] >= cellIdx) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
              + 2] <= cellIdx) {
            while
                (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                 + 2] < cellIdx) {
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

            lanedetection_rgb_B.idxCol1 += 9;
            lanedetection_rgb_B.numActiveEdge++;
          }

          if (lanedetection_rgb_B.idxOld != lanedetection_rgb_B.idxNew) {
            for (j = 0; j < 9; j++) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
                + j] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                + j];
            }
          }

          lanedetection_rgb_B.idxNew += 9;
          lanedetection_rgb_B.idxCol2++;
        }

        lanedetection_rgb_B.idxOld += 9;
      }

      /* Sort the boundaries of the polygon according to row values. */
      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_rgb_B.idxNew = imgIdx;
        lanedetection_rgb_B.idxOld = imgIdx + 9;
        isMore = false;
        for (thetaIdx2 = 1; thetaIdx2 < lanedetection_rgb_B.numActiveEdge;
             thetaIdx2++) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
              + 1] >
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
              + 1]) {
            isMore = true;
            for (j = 0; j < 9; j++) {
              edgeTmp_tmp = lanedetection_rgb_B.idxNew + j;
              lanedetection_rgb_B.edgeTmp =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_rgb_B.idxOld + j;
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

      j = imgIdx;
      lanedetection_rgb_B.numUniquePix = cellIdx + 1;
      lanedetection_rgb_B.loc = 0;
      lanedetection_rgb_B.numActiveEdge = 0;
      lanedetection_rgb_B.idxNew = -1;
      lanedetection_rgb_B.loc_m = cellIdx >> 3;
      lanedetection_rgb_B.idxRow2 = (lanedetection_rgb_B.loc_m + 1) << 3;
      lanedetection_rgb_B.idxTmp = 316;
      lanedetection_rgb_B.lastRowOut = 0;
      isMore = (0 <= acc1_idx_5);
      while (isMore) {
        /* Get a string of pixels */
        prevEdgeIsVertical = false;
        done = (lanedetection_rgb_B.numActiveEdge != 0);
        lanedetection_rgb_B.col = lanedetection_rgb_B.loc;
        if ((lanedetection_rgb_B.loc >= cellIdx) && (lanedetection_rgb_B.loc <=
             acc1_idx_5)) {
          if (j < lanedetection_rgb_B.idxCol1) {
            thetaIdx2 = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1];
            j += 9;
            if ((thetaIdx2 == lanedetection_rgb_B.idxNew) && (j <
                 lanedetection_rgb_B.idxCol1)) {
              q2 = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1];
              isMore = (j < lanedetection_rgb_B.idxCol1);
              while (isMore && (thetaIdx2 == q2)) {
                prevEdgeIsVertical = true;
                thetaIdx2 = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1];
                j += 9;
                isMore = (j < lanedetection_rgb_B.idxCol1);
                if (isMore) {
                  q2 = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1];
                }
              }

              if (!isMore) {
                prevEdgeIsVertical = false;
              }
            }

            if (lanedetection_rgb_B.numActiveEdge != 0) {
              lanedetection_rgb_B.firstRow = lanedetection_rgb_B.idxNew;
              if (thetaIdx2 <= 2527) {
                lanedetection_rgb_B.lastRow = thetaIdx2;
                lanedetection_rgb_B.idxNew = thetaIdx2;
              } else {
                lanedetection_rgb_B.lastRow = 2527;
                lanedetection_rgb_B.idxNew = 2527;
              }
            } else {
              lanedetection_rgb_B.firstRow = lanedetection_rgb_B.idxNew + 1;
              if ((thetaIdx2 > 0) && (thetaIdx2 <= 2527)) {
                lanedetection_rgb_B.lastRow = thetaIdx2 - 1;
                lanedetection_rgb_B.idxNew = thetaIdx2;
              } else if (thetaIdx2 <= 0) {
                lanedetection_rgb_B.lastRow = -1;
                lanedetection_rgb_B.idxNew = 0;
              } else {
                lanedetection_rgb_B.lastRow = 2527;
                lanedetection_rgb_B.idxNew = 2528;
              }
            }

            if (!prevEdgeIsVertical) {
              lanedetection_rgb_B.numActiveEdge =
                !(lanedetection_rgb_B.numActiveEdge != 0);
            }
          } else {
            /* Reset states and move to the next column. */
            done = false;
            lanedetection_rgb_B.firstRow = lanedetection_rgb_B.idxNew + 1;
            lanedetection_rgb_B.lastRow = 2527;

            /* Move to the next column and find out boundaries of the polygon at this column. */
            lanedetection_rgb_B.idxNew = imgIdx;
            lanedetection_rgb_B.idxOld = imgIdx;
            lanedetection_rgb_B.idxCol1 = imgIdx;
            q2 = 0;
            lanedetection_rgb_B.numActiveEdge = 0;
            for (thetaIdx2 = 0; thetaIdx2 < lanedetection_rgb_B.idxCol2;
                 thetaIdx2++) {
              /* Find out the valid boundaries and bring them to the latest column. */
              if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                  + 3] >= lanedetection_rgb_B.numUniquePix) {
                if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                    + 2] <= lanedetection_rgb_B.numUniquePix) {
                  while
                      (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                       + 2] < lanedetection_rgb_B.numUniquePix) {
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

                  lanedetection_rgb_B.idxCol1 += 9;
                  lanedetection_rgb_B.numActiveEdge++;
                }

                if (lanedetection_rgb_B.idxOld != lanedetection_rgb_B.idxNew) {
                  for (j = 0; j < 9; j++) {
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
                      + j] =
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                      + j];
                  }
                }

                lanedetection_rgb_B.idxNew += 9;
                q2++;
              }

              lanedetection_rgb_B.idxOld += 9;
            }

            lanedetection_rgb_B.idxCol2 = q2;

            /* Sort the boundaries of the polygon according to row values. */
            /* Sort the boundaries of the polygon. */
            isMore = true;
            while (isMore) {
              lanedetection_rgb_B.idxNew = imgIdx;
              lanedetection_rgb_B.idxOld = imgIdx + 9;
              isMore = false;
              for (thetaIdx2 = 1; thetaIdx2 < lanedetection_rgb_B.numActiveEdge;
                   thetaIdx2++) {
                if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxNew
                    + 1] >
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                    + 1]) {
                  isMore = true;
                  for (j = 0; j < 9; j++) {
                    edgeTmp_tmp = lanedetection_rgb_B.idxNew + j;
                    lanedetection_rgb_B.edgeTmp =
                      lanedetection_rgb_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
                    DrawShapes_DW_Polygon_tmp = lanedetection_rgb_B.idxOld + j;
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

            j = imgIdx;
            lanedetection_rgb_B.numUniquePix++;
            lanedetection_rgb_B.numActiveEdge = 0;
            lanedetection_rgb_B.idxNew = -1;
            lanedetection_rgb_B.loc++;
          }
        } else {
          lanedetection_rgb_B.firstRow = 0;
          lanedetection_rgb_B.lastRow = 2527;
          lanedetection_rgb_B.loc++;
        }

        if (lanedetection_rgb_B.firstRow < 0) {
          lanedetection_rgb_B.firstRow = 0;
        }

        if (lanedetection_rgb_B.lastRow < lanedetection_rgb_B.firstRow) {
          lanedetection_rgb_B.lastRow = lanedetection_rgb_B.firstRow - 1;
        }

        if (done && ((lanedetection_rgb_B.lastRow > 0) &&
                     (lanedetection_rgb_B.firstRow < 2527))) {
          if (lanedetection_rgb_B.lastRow > 2527) {
            lanedetection_rgb_B.lastRow = 2527;
          }

          q2 = lanedetection_rgb_B.firstRow >> 3;
          thetaIdx2 = lanedetection_rgb_B.lastRow >> 3;
          if (lanedetection_rgb_B.idxTmp > q2) {
            lanedetection_rgb_B.idxTmp = q2;
          }

          if (lanedetection_rgb_B.lastRowOut < thetaIdx2) {
            lanedetection_rgb_B.lastRowOut = thetaIdx2;
          }

          if (thetaIdx2 > q2) {
            lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
              (((uint32_T)((q2 + 1) << 3) +
                lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2]) -
               lanedetection_rgb_B.firstRow);
            lanedetection_rgb_DW.DrawShapes_DW_PixCount[thetaIdx2] = (uint8_T)
              (((uint32_T)(lanedetection_rgb_B.lastRow - (thetaIdx2 << 3)) +
                lanedetection_rgb_DW.DrawShapes_DW_PixCount[thetaIdx2]) + 1U);
            for (q2++; q2 < thetaIdx2; q2++) {
              lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                (lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] + 8U);
            }
          } else {
            if (thetaIdx2 == q2) {
              lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                (((uint32_T)(lanedetection_rgb_B.lastRow -
                             lanedetection_rgb_B.firstRow) +
                  lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2]) + 1U);
            }
          }
        }

        isMore = (lanedetection_rgb_B.loc <= acc1_idx_5);
        if (((lanedetection_rgb_B.idxRow2 - 1 == lanedetection_rgb_B.col) ||
             (!isMore)) && (lanedetection_rgb_B.lastRow >= 2527)) {
          lanedetection_rgb_B.col = lanedetection_rgb_B.loc_m * 316 +
            lanedetection_rgb_B.idxTmp;
          thetaIdx2 = lanedetection_rgb_B.col;
          for (q2 = lanedetection_rgb_B.idxTmp; q2 <=
               lanedetection_rgb_B.lastRowOut; q2++) {
            if (lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] == 64) {
              lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] = (uint8_T)
                ((((lanedetection_rgb_P.DrawShapes_color[0] << 14) -
                   (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] << 14)) +
                  (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] << 14)) >> 14);
            } else {
              lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] = (uint8_T)
                ((((((lanedetection_rgb_P.DrawShapes_color[0] << 14) -
                     (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] << 14)) *
                    lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2]) >> 6) +
                  (lanedetection_rgb_B.DrawShapes_o1[thetaIdx2] << 14)) >> 14);
            }

            thetaIdx2++;
          }

          thetaIdx2 = lanedetection_rgb_B.col;
          for (q2 = lanedetection_rgb_B.idxTmp; q2 <=
               lanedetection_rgb_B.lastRowOut; q2++) {
            if (lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] == 64) {
              lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] = (uint8_T)
                ((((lanedetection_rgb_P.DrawShapes_color[1] << 14) -
                   (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] << 14)) +
                  (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] << 14)) >> 14);
            } else {
              lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] = (uint8_T)
                ((((((lanedetection_rgb_P.DrawShapes_color[1] << 14) -
                     (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] << 14)) *
                    lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2]) >> 6) +
                  (lanedetection_rgb_B.DrawShapes_o2[thetaIdx2] << 14)) >> 14);
            }

            thetaIdx2++;
          }

          for (q2 = lanedetection_rgb_B.idxTmp; q2 <=
               lanedetection_rgb_B.lastRowOut; q2++) {
            if (lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2] == 64) {
              lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.col] =
                (uint8_T)((((lanedetection_rgb_P.DrawShapes_color[2] << 14) -
                            (lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.col]
                             << 14)) +
                           (lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.col]
                            << 14)) >> 14);
            } else {
              lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.col] =
                (uint8_T)((((((lanedetection_rgb_P.DrawShapes_color[2] << 14) -
                              (lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.col]
                               << 14)) *
                             lanedetection_rgb_DW.DrawShapes_DW_PixCount[q2]) >>
                            6) +
                           (lanedetection_rgb_B.DrawShapes_o3[lanedetection_rgb_B.col]
                            << 14)) >> 14);
            }

            lanedetection_rgb_B.col++;
          }

          while (lanedetection_rgb_B.idxTmp <= lanedetection_rgb_B.lastRowOut) {
            lanedetection_rgb_DW.DrawShapes_DW_PixCount[lanedetection_rgb_B.idxTmp]
              = 0U;
            lanedetection_rgb_B.idxTmp++;
          }

          lanedetection_rgb_B.loc_m++;
          lanedetection_rgb_B.idxRow2 += 8;
          lanedetection_rgb_B.idxTmp = 316;
          lanedetection_rgb_B.lastRowOut = 0;
        }
      }

      /* Move to the next polygon. */
      imgIdx += lanedetection_rgb_B.imgCol * 9;
      if (thetaIdx >= div_s32_floor(lanedetection_rgb_B.imgRow,
           lanedetection_rgb_B.imgCol) - 1) {
        thetaIdx = 0;
      } else {
        thetaIdx++;
      }

      isMore = (imgIdx < (lanedetection_rgb_B.imgCol << 1) * 9);
    }
  }

  /* End of S-Function (svipdrawshapes): '<Root>/Draw Shapes' */
  /* Start for MATLABSystem: '<S4>/MATLAB System' */
  memcpy(&lanedetection_rgb_B.ColorSpaceConversion[0],
         &lanedetection_rgb_B.DrawShapes_o1[0], 22120U * sizeof(uint8_T));
  memcpy(&lanedetection_rgb_B.pln2[0], &lanedetection_rgb_B.DrawShapes_o2[0],
         22120U * sizeof(uint8_T));
  memcpy(&lanedetection_rgb_B.pln3[0], &lanedetection_rgb_B.DrawShapes_o3[0],
         22120U * sizeof(uint8_T));
  MW_SDL_videoDisplayOutput(lanedetection_rgb_B.ColorSpaceConversion,
    lanedetection_rgb_B.pln2, lanedetection_rgb_B.pln3);

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
  lanedetection_rgb_M->Sizes.checksums[0] = (963921893U);
  lanedetection_rgb_M->Sizes.checksums[1] = (406326302U);
  lanedetection_rgb_M->Sizes.checksums[2] = (3064103111U);
  lanedetection_rgb_M->Sizes.checksums[3] = (3997718587U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    lanedetection_rgb_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
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
    lanedetection_rgb_B.HoughTransform_o2[0] = -102944;
    lanedetection_rgb_B.HoughTransform_o2[1] = -101800;
    lanedetection_rgb_B.HoughTransform_o2[2] = -100656;
    lanedetection_rgb_B.HoughTransform_o2[3] = -99512;
    lanedetection_rgb_B.HoughTransform_o2[4] = -98368;
    lanedetection_rgb_B.HoughTransform_o2[5] = -97225;
    lanedetection_rgb_B.HoughTransform_o2[6] = -96081;
    lanedetection_rgb_B.HoughTransform_o2[7] = -94937;
    lanedetection_rgb_B.HoughTransform_o2[8] = -93793;
    lanedetection_rgb_B.HoughTransform_o2[9] = -92649;
    lanedetection_rgb_B.HoughTransform_o2[10] = -91506;
    lanedetection_rgb_B.HoughTransform_o2[11] = -90362;
    lanedetection_rgb_B.HoughTransform_o2[12] = -89218;
    lanedetection_rgb_B.HoughTransform_o2[13] = -88074;
    lanedetection_rgb_B.HoughTransform_o2[14] = -86930;
    lanedetection_rgb_B.HoughTransform_o2[15] = -85786;
    lanedetection_rgb_B.HoughTransform_o2[16] = -84643;
    lanedetection_rgb_B.HoughTransform_o2[17] = -83499;
    lanedetection_rgb_B.HoughTransform_o2[18] = -82355;
    lanedetection_rgb_B.HoughTransform_o2[19] = -81211;
    lanedetection_rgb_B.HoughTransform_o2[20] = -80067;
    lanedetection_rgb_B.HoughTransform_o2[21] = -78924;
    lanedetection_rgb_B.HoughTransform_o2[22] = -77780;
    lanedetection_rgb_B.HoughTransform_o2[23] = -76636;
    lanedetection_rgb_B.HoughTransform_o2[24] = -75492;
    lanedetection_rgb_B.HoughTransform_o2[25] = -74348;
    lanedetection_rgb_B.HoughTransform_o2[26] = -73204;
    lanedetection_rgb_B.HoughTransform_o2[27] = -72061;
    lanedetection_rgb_B.HoughTransform_o2[28] = -70917;
    lanedetection_rgb_B.HoughTransform_o2[29] = -69773;
    lanedetection_rgb_B.HoughTransform_o2[30] = -68629;
    lanedetection_rgb_B.HoughTransform_o2[31] = -67485;
    lanedetection_rgb_B.HoughTransform_o2[32] = -66342;
    lanedetection_rgb_B.HoughTransform_o2[33] = -65198;
    lanedetection_rgb_B.HoughTransform_o2[34] = -64054;
    lanedetection_rgb_B.HoughTransform_o2[35] = -62910;
    lanedetection_rgb_B.HoughTransform_o2[36] = -61766;
    lanedetection_rgb_B.HoughTransform_o2[37] = -60622;
    lanedetection_rgb_B.HoughTransform_o2[38] = -59479;
    lanedetection_rgb_B.HoughTransform_o2[39] = -58335;
    lanedetection_rgb_B.HoughTransform_o2[40] = -57191;
    lanedetection_rgb_B.HoughTransform_o2[41] = -56047;
    lanedetection_rgb_B.HoughTransform_o2[42] = -54903;
    lanedetection_rgb_B.HoughTransform_o2[43] = -53759;
    lanedetection_rgb_B.HoughTransform_o2[44] = -52616;
    lanedetection_rgb_B.HoughTransform_o2[45] = -51472;
    lanedetection_rgb_B.HoughTransform_o2[46] = -50328;
    lanedetection_rgb_B.HoughTransform_o2[47] = -49184;
    lanedetection_rgb_B.HoughTransform_o2[48] = -48040;
    lanedetection_rgb_B.HoughTransform_o2[49] = -46897;
    lanedetection_rgb_B.HoughTransform_o2[50] = -45753;
    lanedetection_rgb_B.HoughTransform_o2[51] = -44609;
    lanedetection_rgb_B.HoughTransform_o2[52] = -43465;
    lanedetection_rgb_B.HoughTransform_o2[53] = -42321;
    lanedetection_rgb_B.HoughTransform_o2[54] = -41177;
    lanedetection_rgb_B.HoughTransform_o2[55] = -40034;
    lanedetection_rgb_B.HoughTransform_o2[56] = -38890;
    lanedetection_rgb_B.HoughTransform_o2[57] = -37746;
    lanedetection_rgb_B.HoughTransform_o2[58] = -36602;
    lanedetection_rgb_B.HoughTransform_o2[59] = -35458;
    lanedetection_rgb_B.HoughTransform_o2[60] = -34315;
    lanedetection_rgb_B.HoughTransform_o2[61] = -33171;
    lanedetection_rgb_B.HoughTransform_o2[62] = -32027;
    lanedetection_rgb_B.HoughTransform_o2[63] = -30883;
    lanedetection_rgb_B.HoughTransform_o2[64] = -29739;
    lanedetection_rgb_B.HoughTransform_o2[65] = -28595;
    lanedetection_rgb_B.HoughTransform_o2[66] = -27452;
    lanedetection_rgb_B.HoughTransform_o2[67] = -26308;
    lanedetection_rgb_B.HoughTransform_o2[68] = -25164;
    lanedetection_rgb_B.HoughTransform_o2[69] = -24020;
    lanedetection_rgb_B.HoughTransform_o2[70] = -22876;
    lanedetection_rgb_B.HoughTransform_o2[71] = -21733;
    lanedetection_rgb_B.HoughTransform_o2[72] = -20589;
    lanedetection_rgb_B.HoughTransform_o2[73] = -19445;
    lanedetection_rgb_B.HoughTransform_o2[74] = -18301;
    lanedetection_rgb_B.HoughTransform_o2[75] = -17157;
    lanedetection_rgb_B.HoughTransform_o2[76] = -16013;
    lanedetection_rgb_B.HoughTransform_o2[77] = -14870;
    lanedetection_rgb_B.HoughTransform_o2[78] = -13726;
    lanedetection_rgb_B.HoughTransform_o2[79] = -12582;
    lanedetection_rgb_B.HoughTransform_o2[80] = -11438;
    lanedetection_rgb_B.HoughTransform_o2[81] = -10294;
    lanedetection_rgb_B.HoughTransform_o2[82] = -9151;
    lanedetection_rgb_B.HoughTransform_o2[83] = -8007;
    lanedetection_rgb_B.HoughTransform_o2[84] = -6863;
    lanedetection_rgb_B.HoughTransform_o2[85] = -5719;
    lanedetection_rgb_B.HoughTransform_o2[86] = -4575;
    lanedetection_rgb_B.HoughTransform_o2[87] = -3431;
    lanedetection_rgb_B.HoughTransform_o2[88] = -2288;
    lanedetection_rgb_B.HoughTransform_o2[89] = -1144;
    lanedetection_rgb_B.HoughTransform_o2[90] = 0;
    lanedetection_rgb_B.HoughTransform_o2[91] = 1144;
    lanedetection_rgb_B.HoughTransform_o2[92] = 2288;
    lanedetection_rgb_B.HoughTransform_o2[93] = 3431;
    lanedetection_rgb_B.HoughTransform_o2[94] = 4575;
    lanedetection_rgb_B.HoughTransform_o2[95] = 5719;
    lanedetection_rgb_B.HoughTransform_o2[96] = 6863;
    lanedetection_rgb_B.HoughTransform_o2[97] = 8007;
    lanedetection_rgb_B.HoughTransform_o2[98] = 9151;
    lanedetection_rgb_B.HoughTransform_o2[99] = 10294;
    lanedetection_rgb_B.HoughTransform_o2[100] = 11438;
    lanedetection_rgb_B.HoughTransform_o2[101] = 12582;
    lanedetection_rgb_B.HoughTransform_o2[102] = 13726;
    lanedetection_rgb_B.HoughTransform_o2[103] = 14870;
    lanedetection_rgb_B.HoughTransform_o2[104] = 16013;
    lanedetection_rgb_B.HoughTransform_o2[105] = 17157;
    lanedetection_rgb_B.HoughTransform_o2[106] = 18301;
    lanedetection_rgb_B.HoughTransform_o2[107] = 19445;
    lanedetection_rgb_B.HoughTransform_o2[108] = 20589;
    lanedetection_rgb_B.HoughTransform_o2[109] = 21733;
    lanedetection_rgb_B.HoughTransform_o2[110] = 22876;
    lanedetection_rgb_B.HoughTransform_o2[111] = 24020;
    lanedetection_rgb_B.HoughTransform_o2[112] = 25164;
    lanedetection_rgb_B.HoughTransform_o2[113] = 26308;
    lanedetection_rgb_B.HoughTransform_o2[114] = 27452;
    lanedetection_rgb_B.HoughTransform_o2[115] = 28595;
    lanedetection_rgb_B.HoughTransform_o2[116] = 29739;
    lanedetection_rgb_B.HoughTransform_o2[117] = 30883;
    lanedetection_rgb_B.HoughTransform_o2[118] = 32027;
    lanedetection_rgb_B.HoughTransform_o2[119] = 33171;
    lanedetection_rgb_B.HoughTransform_o2[120] = 34315;
    lanedetection_rgb_B.HoughTransform_o2[121] = 35458;
    lanedetection_rgb_B.HoughTransform_o2[122] = 36602;
    lanedetection_rgb_B.HoughTransform_o2[123] = 37746;
    lanedetection_rgb_B.HoughTransform_o2[124] = 38890;
    lanedetection_rgb_B.HoughTransform_o2[125] = 40034;
    lanedetection_rgb_B.HoughTransform_o2[126] = 41177;
    lanedetection_rgb_B.HoughTransform_o2[127] = 42321;
    lanedetection_rgb_B.HoughTransform_o2[128] = 43465;
    lanedetection_rgb_B.HoughTransform_o2[129] = 44609;
    lanedetection_rgb_B.HoughTransform_o2[130] = 45753;
    lanedetection_rgb_B.HoughTransform_o2[131] = 46897;
    lanedetection_rgb_B.HoughTransform_o2[132] = 48040;
    lanedetection_rgb_B.HoughTransform_o2[133] = 49184;
    lanedetection_rgb_B.HoughTransform_o2[134] = 50328;
    lanedetection_rgb_B.HoughTransform_o2[135] = 51472;
    lanedetection_rgb_B.HoughTransform_o2[136] = 52616;
    lanedetection_rgb_B.HoughTransform_o2[137] = 53759;
    lanedetection_rgb_B.HoughTransform_o2[138] = 54903;
    lanedetection_rgb_B.HoughTransform_o2[139] = 56047;
    lanedetection_rgb_B.HoughTransform_o2[140] = 57191;
    lanedetection_rgb_B.HoughTransform_o2[141] = 58335;
    lanedetection_rgb_B.HoughTransform_o2[142] = 59479;
    lanedetection_rgb_B.HoughTransform_o2[143] = 60622;
    lanedetection_rgb_B.HoughTransform_o2[144] = 61766;
    lanedetection_rgb_B.HoughTransform_o2[145] = 62910;
    lanedetection_rgb_B.HoughTransform_o2[146] = 64054;
    lanedetection_rgb_B.HoughTransform_o2[147] = 65198;
    lanedetection_rgb_B.HoughTransform_o2[148] = 66342;
    lanedetection_rgb_B.HoughTransform_o2[149] = 67485;
    lanedetection_rgb_B.HoughTransform_o2[150] = 68629;
    lanedetection_rgb_B.HoughTransform_o2[151] = 69773;
    lanedetection_rgb_B.HoughTransform_o2[152] = 70917;
    lanedetection_rgb_B.HoughTransform_o2[153] = 72061;
    lanedetection_rgb_B.HoughTransform_o2[154] = 73204;
    lanedetection_rgb_B.HoughTransform_o2[155] = 74348;
    lanedetection_rgb_B.HoughTransform_o2[156] = 75492;
    lanedetection_rgb_B.HoughTransform_o2[157] = 76636;
    lanedetection_rgb_B.HoughTransform_o2[158] = 77780;
    lanedetection_rgb_B.HoughTransform_o2[159] = 78924;
    lanedetection_rgb_B.HoughTransform_o2[160] = 80067;
    lanedetection_rgb_B.HoughTransform_o2[161] = 81211;
    lanedetection_rgb_B.HoughTransform_o2[162] = 82355;
    lanedetection_rgb_B.HoughTransform_o2[163] = 83499;
    lanedetection_rgb_B.HoughTransform_o2[164] = 84643;
    lanedetection_rgb_B.HoughTransform_o2[165] = 85786;
    lanedetection_rgb_B.HoughTransform_o2[166] = 86930;
    lanedetection_rgb_B.HoughTransform_o2[167] = 88074;
    lanedetection_rgb_B.HoughTransform_o2[168] = 89218;
    lanedetection_rgb_B.HoughTransform_o2[169] = 90362;
    lanedetection_rgb_B.HoughTransform_o2[170] = 91506;
    lanedetection_rgb_B.HoughTransform_o2[171] = 92649;
    lanedetection_rgb_B.HoughTransform_o2[172] = 93793;
    lanedetection_rgb_B.HoughTransform_o2[173] = 94937;
    lanedetection_rgb_B.HoughTransform_o2[174] = 96081;
    lanedetection_rgb_B.HoughTransform_o2[175] = 97225;
    lanedetection_rgb_B.HoughTransform_o2[176] = 98368;
    lanedetection_rgb_B.HoughTransform_o2[177] = 99512;
    lanedetection_rgb_B.HoughTransform_o2[178] = 100656;
    lanedetection_rgb_B.HoughTransform_o2[179] = 101800;
    lanedetection_rgb_B.HoughTransform_o3[0] = -21233664;
    lanedetection_rgb_B.HoughTransform_o3[1] = -21037056;
    lanedetection_rgb_B.HoughTransform_o3[2] = -20840448;
    lanedetection_rgb_B.HoughTransform_o3[3] = -20643840;
    lanedetection_rgb_B.HoughTransform_o3[4] = -20447232;
    lanedetection_rgb_B.HoughTransform_o3[5] = -20250624;
    lanedetection_rgb_B.HoughTransform_o3[6] = -20054016;
    lanedetection_rgb_B.HoughTransform_o3[7] = -19857408;
    lanedetection_rgb_B.HoughTransform_o3[8] = -19660800;
    lanedetection_rgb_B.HoughTransform_o3[9] = -19464192;
    lanedetection_rgb_B.HoughTransform_o3[10] = -19267584;
    lanedetection_rgb_B.HoughTransform_o3[11] = -19070976;
    lanedetection_rgb_B.HoughTransform_o3[12] = -18874368;
    lanedetection_rgb_B.HoughTransform_o3[13] = -18677760;
    lanedetection_rgb_B.HoughTransform_o3[14] = -18481152;
    lanedetection_rgb_B.HoughTransform_o3[15] = -18284544;
    lanedetection_rgb_B.HoughTransform_o3[16] = -18087936;
    lanedetection_rgb_B.HoughTransform_o3[17] = -17891328;
    lanedetection_rgb_B.HoughTransform_o3[18] = -17694720;
    lanedetection_rgb_B.HoughTransform_o3[19] = -17498112;
    lanedetection_rgb_B.HoughTransform_o3[20] = -17301504;
    lanedetection_rgb_B.HoughTransform_o3[21] = -17104896;
    lanedetection_rgb_B.HoughTransform_o3[22] = -16908288;
    lanedetection_rgb_B.HoughTransform_o3[23] = -16711680;
    lanedetection_rgb_B.HoughTransform_o3[24] = -16515072;
    lanedetection_rgb_B.HoughTransform_o3[25] = -16318464;
    lanedetection_rgb_B.HoughTransform_o3[26] = -16121856;
    lanedetection_rgb_B.HoughTransform_o3[27] = -15925248;
    lanedetection_rgb_B.HoughTransform_o3[28] = -15728640;
    lanedetection_rgb_B.HoughTransform_o3[29] = -15532032;
    lanedetection_rgb_B.HoughTransform_o3[30] = -15335424;
    lanedetection_rgb_B.HoughTransform_o3[31] = -15138816;
    lanedetection_rgb_B.HoughTransform_o3[32] = -14942208;
    lanedetection_rgb_B.HoughTransform_o3[33] = -14745600;
    lanedetection_rgb_B.HoughTransform_o3[34] = -14548992;
    lanedetection_rgb_B.HoughTransform_o3[35] = -14352384;
    lanedetection_rgb_B.HoughTransform_o3[36] = -14155776;
    lanedetection_rgb_B.HoughTransform_o3[37] = -13959168;
    lanedetection_rgb_B.HoughTransform_o3[38] = -13762560;
    lanedetection_rgb_B.HoughTransform_o3[39] = -13565952;
    lanedetection_rgb_B.HoughTransform_o3[40] = -13369344;
    lanedetection_rgb_B.HoughTransform_o3[41] = -13172736;
    lanedetection_rgb_B.HoughTransform_o3[42] = -12976128;
    lanedetection_rgb_B.HoughTransform_o3[43] = -12779520;
    lanedetection_rgb_B.HoughTransform_o3[44] = -12582912;
    lanedetection_rgb_B.HoughTransform_o3[45] = -12386304;
    lanedetection_rgb_B.HoughTransform_o3[46] = -12189696;
    lanedetection_rgb_B.HoughTransform_o3[47] = -11993088;
    lanedetection_rgb_B.HoughTransform_o3[48] = -11796480;
    lanedetection_rgb_B.HoughTransform_o3[49] = -11599872;
    lanedetection_rgb_B.HoughTransform_o3[50] = -11403264;
    lanedetection_rgb_B.HoughTransform_o3[51] = -11206656;
    lanedetection_rgb_B.HoughTransform_o3[52] = -11010048;
    lanedetection_rgb_B.HoughTransform_o3[53] = -10813440;
    lanedetection_rgb_B.HoughTransform_o3[54] = -10616832;
    lanedetection_rgb_B.HoughTransform_o3[55] = -10420224;
    lanedetection_rgb_B.HoughTransform_o3[56] = -10223616;
    lanedetection_rgb_B.HoughTransform_o3[57] = -10027008;
    lanedetection_rgb_B.HoughTransform_o3[58] = -9830400;
    lanedetection_rgb_B.HoughTransform_o3[59] = -9633792;
    lanedetection_rgb_B.HoughTransform_o3[60] = -9437184;
    lanedetection_rgb_B.HoughTransform_o3[61] = -9240576;
    lanedetection_rgb_B.HoughTransform_o3[62] = -9043968;
    lanedetection_rgb_B.HoughTransform_o3[63] = -8847360;
    lanedetection_rgb_B.HoughTransform_o3[64] = -8650752;
    lanedetection_rgb_B.HoughTransform_o3[65] = -8454144;
    lanedetection_rgb_B.HoughTransform_o3[66] = -8257536;
    lanedetection_rgb_B.HoughTransform_o3[67] = -8060928;
    lanedetection_rgb_B.HoughTransform_o3[68] = -7864320;
    lanedetection_rgb_B.HoughTransform_o3[69] = -7667712;
    lanedetection_rgb_B.HoughTransform_o3[70] = -7471104;
    lanedetection_rgb_B.HoughTransform_o3[71] = -7274496;
    lanedetection_rgb_B.HoughTransform_o3[72] = -7077888;
    lanedetection_rgb_B.HoughTransform_o3[73] = -6881280;
    lanedetection_rgb_B.HoughTransform_o3[74] = -6684672;
    lanedetection_rgb_B.HoughTransform_o3[75] = -6488064;
    lanedetection_rgb_B.HoughTransform_o3[76] = -6291456;
    lanedetection_rgb_B.HoughTransform_o3[77] = -6094848;
    lanedetection_rgb_B.HoughTransform_o3[78] = -5898240;
    lanedetection_rgb_B.HoughTransform_o3[79] = -5701632;
    lanedetection_rgb_B.HoughTransform_o3[80] = -5505024;
    lanedetection_rgb_B.HoughTransform_o3[81] = -5308416;
    lanedetection_rgb_B.HoughTransform_o3[82] = -5111808;
    lanedetection_rgb_B.HoughTransform_o3[83] = -4915200;
    lanedetection_rgb_B.HoughTransform_o3[84] = -4718592;
    lanedetection_rgb_B.HoughTransform_o3[85] = -4521984;
    lanedetection_rgb_B.HoughTransform_o3[86] = -4325376;
    lanedetection_rgb_B.HoughTransform_o3[87] = -4128768;
    lanedetection_rgb_B.HoughTransform_o3[88] = -3932160;
    lanedetection_rgb_B.HoughTransform_o3[89] = -3735552;
    lanedetection_rgb_B.HoughTransform_o3[90] = -3538944;
    lanedetection_rgb_B.HoughTransform_o3[91] = -3342336;
    lanedetection_rgb_B.HoughTransform_o3[92] = -3145728;
    lanedetection_rgb_B.HoughTransform_o3[93] = -2949120;
    lanedetection_rgb_B.HoughTransform_o3[94] = -2752512;
    lanedetection_rgb_B.HoughTransform_o3[95] = -2555904;
    lanedetection_rgb_B.HoughTransform_o3[96] = -2359296;
    lanedetection_rgb_B.HoughTransform_o3[97] = -2162688;
    lanedetection_rgb_B.HoughTransform_o3[98] = -1966080;
    lanedetection_rgb_B.HoughTransform_o3[99] = -1769472;
    lanedetection_rgb_B.HoughTransform_o3[100] = -1572864;
    lanedetection_rgb_B.HoughTransform_o3[101] = -1376256;
    lanedetection_rgb_B.HoughTransform_o3[102] = -1179648;
    lanedetection_rgb_B.HoughTransform_o3[103] = -983040;
    lanedetection_rgb_B.HoughTransform_o3[104] = -786432;
    lanedetection_rgb_B.HoughTransform_o3[105] = -589824;
    lanedetection_rgb_B.HoughTransform_o3[106] = -393216;
    lanedetection_rgb_B.HoughTransform_o3[107] = -196608;
    lanedetection_rgb_B.HoughTransform_o3[108] = 0;
    lanedetection_rgb_B.HoughTransform_o3[109] = 196608;
    lanedetection_rgb_B.HoughTransform_o3[110] = 393216;
    lanedetection_rgb_B.HoughTransform_o3[111] = 589824;
    lanedetection_rgb_B.HoughTransform_o3[112] = 786432;
    lanedetection_rgb_B.HoughTransform_o3[113] = 983040;
    lanedetection_rgb_B.HoughTransform_o3[114] = 1179648;
    lanedetection_rgb_B.HoughTransform_o3[115] = 1376256;
    lanedetection_rgb_B.HoughTransform_o3[116] = 1572864;
    lanedetection_rgb_B.HoughTransform_o3[117] = 1769472;
    lanedetection_rgb_B.HoughTransform_o3[118] = 1966080;
    lanedetection_rgb_B.HoughTransform_o3[119] = 2162688;
    lanedetection_rgb_B.HoughTransform_o3[120] = 2359296;
    lanedetection_rgb_B.HoughTransform_o3[121] = 2555904;
    lanedetection_rgb_B.HoughTransform_o3[122] = 2752512;
    lanedetection_rgb_B.HoughTransform_o3[123] = 2949120;
    lanedetection_rgb_B.HoughTransform_o3[124] = 3145728;
    lanedetection_rgb_B.HoughTransform_o3[125] = 3342336;
    lanedetection_rgb_B.HoughTransform_o3[126] = 3538944;
    lanedetection_rgb_B.HoughTransform_o3[127] = 3735552;
    lanedetection_rgb_B.HoughTransform_o3[128] = 3932160;
    lanedetection_rgb_B.HoughTransform_o3[129] = 4128768;
    lanedetection_rgb_B.HoughTransform_o3[130] = 4325376;
    lanedetection_rgb_B.HoughTransform_o3[131] = 4521984;
    lanedetection_rgb_B.HoughTransform_o3[132] = 4718592;
    lanedetection_rgb_B.HoughTransform_o3[133] = 4915200;
    lanedetection_rgb_B.HoughTransform_o3[134] = 5111808;
    lanedetection_rgb_B.HoughTransform_o3[135] = 5308416;
    lanedetection_rgb_B.HoughTransform_o3[136] = 5505024;
    lanedetection_rgb_B.HoughTransform_o3[137] = 5701632;
    lanedetection_rgb_B.HoughTransform_o3[138] = 5898240;
    lanedetection_rgb_B.HoughTransform_o3[139] = 6094848;
    lanedetection_rgb_B.HoughTransform_o3[140] = 6291456;
    lanedetection_rgb_B.HoughTransform_o3[141] = 6488064;
    lanedetection_rgb_B.HoughTransform_o3[142] = 6684672;
    lanedetection_rgb_B.HoughTransform_o3[143] = 6881280;
    lanedetection_rgb_B.HoughTransform_o3[144] = 7077888;
    lanedetection_rgb_B.HoughTransform_o3[145] = 7274496;
    lanedetection_rgb_B.HoughTransform_o3[146] = 7471104;
    lanedetection_rgb_B.HoughTransform_o3[147] = 7667712;
    lanedetection_rgb_B.HoughTransform_o3[148] = 7864320;
    lanedetection_rgb_B.HoughTransform_o3[149] = 8060928;
    lanedetection_rgb_B.HoughTransform_o3[150] = 8257536;
    lanedetection_rgb_B.HoughTransform_o3[151] = 8454144;
    lanedetection_rgb_B.HoughTransform_o3[152] = 8650752;
    lanedetection_rgb_B.HoughTransform_o3[153] = 8847360;
    lanedetection_rgb_B.HoughTransform_o3[154] = 9043968;
    lanedetection_rgb_B.HoughTransform_o3[155] = 9240576;
    lanedetection_rgb_B.HoughTransform_o3[156] = 9437184;
    lanedetection_rgb_B.HoughTransform_o3[157] = 9633792;
    lanedetection_rgb_B.HoughTransform_o3[158] = 9830400;
    lanedetection_rgb_B.HoughTransform_o3[159] = 10027008;
    lanedetection_rgb_B.HoughTransform_o3[160] = 10223616;
    lanedetection_rgb_B.HoughTransform_o3[161] = 10420224;
    lanedetection_rgb_B.HoughTransform_o3[162] = 10616832;
    lanedetection_rgb_B.HoughTransform_o3[163] = 10813440;
    lanedetection_rgb_B.HoughTransform_o3[164] = 11010048;
    lanedetection_rgb_B.HoughTransform_o3[165] = 11206656;
    lanedetection_rgb_B.HoughTransform_o3[166] = 11403264;
    lanedetection_rgb_B.HoughTransform_o3[167] = 11599872;
    lanedetection_rgb_B.HoughTransform_o3[168] = 11796480;
    lanedetection_rgb_B.HoughTransform_o3[169] = 11993088;
    lanedetection_rgb_B.HoughTransform_o3[170] = 12189696;
    lanedetection_rgb_B.HoughTransform_o3[171] = 12386304;
    lanedetection_rgb_B.HoughTransform_o3[172] = 12582912;
    lanedetection_rgb_B.HoughTransform_o3[173] = 12779520;
    lanedetection_rgb_B.HoughTransform_o3[174] = 12976128;
    lanedetection_rgb_B.HoughTransform_o3[175] = 13172736;
    lanedetection_rgb_B.HoughTransform_o3[176] = 13369344;
    lanedetection_rgb_B.HoughTransform_o3[177] = 13565952;
    lanedetection_rgb_B.HoughTransform_o3[178] = 13762560;
    lanedetection_rgb_B.HoughTransform_o3[179] = 13959168;
    lanedetection_rgb_B.HoughTransform_o3[180] = 14155776;
    lanedetection_rgb_B.HoughTransform_o3[181] = 14352384;
    lanedetection_rgb_B.HoughTransform_o3[182] = 14548992;
    lanedetection_rgb_B.HoughTransform_o3[183] = 14745600;
    lanedetection_rgb_B.HoughTransform_o3[184] = 14942208;
    lanedetection_rgb_B.HoughTransform_o3[185] = 15138816;
    lanedetection_rgb_B.HoughTransform_o3[186] = 15335424;
    lanedetection_rgb_B.HoughTransform_o3[187] = 15532032;
    lanedetection_rgb_B.HoughTransform_o3[188] = 15728640;
    lanedetection_rgb_B.HoughTransform_o3[189] = 15925248;
    lanedetection_rgb_B.HoughTransform_o3[190] = 16121856;
    lanedetection_rgb_B.HoughTransform_o3[191] = 16318464;
    lanedetection_rgb_B.HoughTransform_o3[192] = 16515072;
    lanedetection_rgb_B.HoughTransform_o3[193] = 16711680;
    lanedetection_rgb_B.HoughTransform_o3[194] = 16908288;
    lanedetection_rgb_B.HoughTransform_o3[195] = 17104896;
    lanedetection_rgb_B.HoughTransform_o3[196] = 17301504;
    lanedetection_rgb_B.HoughTransform_o3[197] = 17498112;
    lanedetection_rgb_B.HoughTransform_o3[198] = 17694720;
    lanedetection_rgb_B.HoughTransform_o3[199] = 17891328;
    lanedetection_rgb_B.HoughTransform_o3[200] = 18087936;
    lanedetection_rgb_B.HoughTransform_o3[201] = 18284544;
    lanedetection_rgb_B.HoughTransform_o3[202] = 18481152;
    lanedetection_rgb_B.HoughTransform_o3[203] = 18677760;
    lanedetection_rgb_B.HoughTransform_o3[204] = 18874368;
    lanedetection_rgb_B.HoughTransform_o3[205] = 19070976;
    lanedetection_rgb_B.HoughTransform_o3[206] = 19267584;
    lanedetection_rgb_B.HoughTransform_o3[207] = 19464192;
    lanedetection_rgb_B.HoughTransform_o3[208] = 19660800;
    lanedetection_rgb_B.HoughTransform_o3[209] = 19857408;
    lanedetection_rgb_B.HoughTransform_o3[210] = 20054016;
    lanedetection_rgb_B.HoughTransform_o3[211] = 20250624;
    lanedetection_rgb_B.HoughTransform_o3[212] = 20447232;
    lanedetection_rgb_B.HoughTransform_o3[213] = 20643840;
    lanedetection_rgb_B.HoughTransform_o3[214] = 20840448;
    lanedetection_rgb_B.HoughTransform_o3[215] = 21037056;
    lanedetection_rgb_B.HoughTransform_o3[216] = 21233664;
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
    dtInfo.numDataTypes = 24;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Start for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureInit(lanedetection_rgb_ConstP.V4L2VideoCapture_p1, 0, 0, 0, 0,
                      320U, 240U, 2U, 2U, 1U, 0.1);

  /* Start for S-Function (svipedge): '<Root>/Edge Detection' */
  lanedetection_rgb_DW.EdgeDetection_VO_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOU_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOD_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOL_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOR_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOLR_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOUL_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOLL_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOUR_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_HO_DW[0] = 1;
  lanedetection_rgb_DW.EdgeDetection_HOU_DW[0] = 1;
  lanedetection_rgb_DW.EdgeDetection_HOD_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_HOL_DW[0] = 1;
  lanedetection_rgb_DW.EdgeDetection_HOR_DW[0] = 1;
  lanedetection_rgb_DW.EdgeDetection_HOLR_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_HOUL_DW[0] = 1;
  lanedetection_rgb_DW.EdgeDetection_HOLL_DW[0] = 0;
  lanedetection_rgb_DW.EdgeDetection_HOUR_DW[0] = 1;
  lanedetection_rgb_DW.EdgeDetection_VO_DW[1] = 317;
  lanedetection_rgb_DW.EdgeDetection_VOU_DW[1] = 317;
  lanedetection_rgb_DW.EdgeDetection_VOD_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_VOL_DW[1] = 317;
  lanedetection_rgb_DW.EdgeDetection_VOR_DW[1] = 1;
  lanedetection_rgb_DW.EdgeDetection_VOLR_DW[1] = 0;
  lanedetection_rgb_DW.EdgeDetection_VOUL_DW[1] = 317;
  lanedetection_rgb_DW.EdgeDetection_VOLL_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_VOUR_DW[1] = 1;
  lanedetection_rgb_DW.EdgeDetection_HO_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_HOU_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_HOD_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_HOL_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_HOR_DW[1] = 0;
  lanedetection_rgb_DW.EdgeDetection_HOLR_DW[1] = 0;
  lanedetection_rgb_DW.EdgeDetection_HOUL_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_HOLL_DW[1] = 316;
  lanedetection_rgb_DW.EdgeDetection_HOUR_DW[1] = 0;

  /* Start for MATLABSystem: '<S4>/MATLAB System' */
  lanedetection_rgb_DW.obj.matlabCodegenIsDeleted = true;
  lanedetection_rgb_DW.obj.isInitialized = 0;
  lanedetection_rgb_DW.obj.matlabCodegenIsDeleted = false;
  lanedetection_rgb_DW.obj.isSetupComplete = false;
  lanedetection_rgb_DW.obj.isInitialized = 1;
  lanedetection_rgb_DW.obj.PixelFormatEnum = 1;
  MW_SDL_videoDisplayInit(lanedetection_rgb_DW.obj.PixelFormatEnum, 1, 1, 316.0,
    70.0);
  lanedetection_rgb_DW.obj.isSetupComplete = true;

  /* End of Start for SubSystem: '<Root>/SDL Video Display' */
}

/* Model terminate function */
void lanedetection_rgb_terminate(void)
{
  /* Terminate for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureTerminate(lanedetection_rgb_ConstP.V4L2VideoCapture_p1);

  /* Terminate for MATLABSystem: '<S4>/MATLAB System' */
  matlabCodegenHandle_matlabCodeg(&lanedetection_rgb_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/SDL Video Display' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
