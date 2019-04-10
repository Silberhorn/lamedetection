/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection.c
 *
 * Code generated for Simulink model 'lanedetection'.
 *
 * Model version                  : 1.193
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Wed Apr 10 15:33:34 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "lanedetection.h"
#include "lanedetection_private.h"
#include "lanedetection_dt.h"

/* Block signals (default storage) */
B_lanedetection_T lanedetection_B;

/* Block states (default storage) */
DW_lanedetection_T lanedetection_DW;

/* Real-time model */
RT_MODEL_lanedetection_T lanedetection_M_;
RT_MODEL_lanedetection_T *const lanedetection_M = &lanedetection_M_;

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

void mul_wide_su32(int32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                   *ptrOutBitsLo)
{
  uint32_T outBitsLo;
  uint32_T absIn0;
  uint32_T in0Hi;
  uint32_T in1Lo;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
  in0Hi = absIn0 >> 16U;
  absIn0 &= 65535U;
  in1Hi = in1 >> 16U;
  in1Lo = in1 & 65535U;
  productHiLo = in0Hi * in1Lo;
  productLoHi = absIn0 * in1Hi;
  absIn0 *= in1Lo;
  in1Lo = 0U;
  outBitsLo = (productLoHi << /*MW:OvBitwiseOk*/ 16U) + /*MW:OvCarryOk*/ absIn0;
  if (outBitsLo < absIn0) {
    in1Lo = 1U;
  }

  absIn0 = outBitsLo;
  outBitsLo += /*MW:OvCarryOk*/ productHiLo << /*MW:OvBitwiseOk*/ 16U;
  if (outBitsLo < absIn0) {
    in1Lo++;
  }

  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
    in1Lo;
  if (!((in1 == 0U) || (in0 >= 0))) {
    absIn0 = ~absIn0;
    outBitsLo = ~outBitsLo;
    outBitsLo++;
    if (outBitsLo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = outBitsLo;
}

int32_T mul_ssu32_sat(int32_T a, uint32_T b)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_su32(a, b, &u32_chi, &u32_clo);
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
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetectio_SystemCore_release(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SDL_videoDisplayTerminate(0, 0);
  }

  /* End of Start for MATLABSystem: '<S3>/MATLAB System' */
}

static void lanedetection_SystemCore_delete(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  lanedetectio_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAnyP(obj, true);
    lanedetection_SystemCore_delete(obj);
  }

  /* End of Start for MATLABSystem: '<S3>/MATLAB System' */
}

/* Model step function */
void lanedetection_step(void)
{
  boolean_T visited2;
  boolean_T isMore;
  boolean_T prevEdgeIsVertical;
  int8_T idxTmpArray[2];
  int32_T numActiveEdge;
  int32_T edgeTmp;
  int32_T lastColA;
  int32_T iC;
  int32_T iA;
  int32_T iB;
  int32_T aidx;
  int32_T cidx;
  static const int8_T b[9] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };

  boolean_T done;
  int32_T max_idx;
  real32_T maxValue;
  int32_T edgeTmp_tmp;
  int32_T DrawShapes_DW_Polygon_tmp;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_ConstP.V4L2VideoCapture_p1,
                        lanedetection_B.V4L2VideoCapture_o1,
                        lanedetection_B.V4L2VideoCapture_o2,
                        lanedetection_B.V4L2VideoCapture_o3);

  /* S-Function (svipresize): '<Root>/Resize' */
  /* this algorithm computes interpolation weights on demand as oppose to using a lookup table */
  /* first resize along X-axis direction */
  aidx = 0;
  for (lastColA = 0; lastColA < 240; lastColA++) {
    iA = lastColA << 10;
    max_idx = iA >> 10;
    lanedetection_B.intPart = max_idx * 160;
    if (max_idx < 239) {
      iB = lanedetection_B.intPart + 160;
    } else {
      iB = lanedetection_B.intPart;
    }

    iA -= max_idx << 10;

    /* bilinear interpolation */
    cidx = 1024 - iA;

    /* adjust offsets so that the input image index will not exceed the image bounds */
    if (iB > 38240) {
      iB = 38240;
    }

    for (iC = 0; iC < 160; iC++) {
      lanedetection_B.acc3 = mul_ssu32_sat(cidx,
        lanedetection_B.V4L2VideoCapture_o2[iC + lanedetection_B.intPart]);
      max_idx = mul_ssu32_sat(iA, lanedetection_B.V4L2VideoCapture_o2[iB + iC]);
      if ((lanedetection_B.acc3 < 0) && (max_idx < MIN_int32_T
           - lanedetection_B.acc3)) {
        max_idx = MIN_int32_T;
      } else if ((lanedetection_B.acc3 > 0) && (max_idx > MAX_int32_T
                  - lanedetection_B.acc3)) {
        max_idx = MAX_int32_T;
      } else {
        max_idx += lanedetection_B.acc3;
      }

      max_idx = ((max_idx & 512U) != 0U) + (max_idx >> 10);
      if (max_idx < 0) {
        max_idx = 0;
      } else {
        if (max_idx > 255) {
          max_idx = 255;
        }
      }

      lanedetection_B.Resize[aidx + iC] = (uint8_T)max_idx;
    }

    aidx += 320;
  }

  /* resize along Y-axis direction */
  lanedetection_B.acc3 = 0;
  for (lastColA = 0; lastColA < 240; lastColA++) {
    max_idx = lastColA * 320;
    for (iC = 0; iC < 160; iC++) {
      lanedetection_DW.Resize_LineBuffer[iC] = lanedetection_B.Resize[max_idx];
      max_idx++;
    }

    aidx = lanedetection_B.acc3;
    for (iC = 0; iC < 320; iC++) {
      iA = (iC << 10) + 512;
      iA = (((iA & 1U) != 0U) + (iA >> 1)) - 512;
      lanedetection_B.intPart = iA >> 10;
      max_idx = lanedetection_B.intPart << 10;
      if ((iA >= 0) && (max_idx < iA - MAX_int32_T)) {
        iA = MAX_int32_T;
      } else if ((iA < 0) && (max_idx > iA - MIN_int32_T)) {
        iA = MIN_int32_T;
      } else {
        iA -= max_idx;
      }

      if (lanedetection_B.intPart < 0) {
        lanedetection_B.intPart = 0;
        iB = 0;
      } else if (lanedetection_B.intPart < 159) {
        iB = lanedetection_B.intPart + 1;
      } else {
        iB = 159;
      }

      if (iA < -2147482623) {
        cidx = MAX_int32_T;
      } else {
        cidx = 1024 - iA;
      }

      lanedetection_B.intPart = mul_ssu32_sat(cidx,
        lanedetection_DW.Resize_LineBuffer[lanedetection_B.intPart]);
      max_idx = mul_ssu32_sat(iA, lanedetection_DW.Resize_LineBuffer[iB]);
      if ((lanedetection_B.intPart < 0) && (max_idx < MIN_int32_T
           - lanedetection_B.intPart)) {
        iA = MIN_int32_T;
      } else if ((lanedetection_B.intPart > 0) && (max_idx > MAX_int32_T
                  - lanedetection_B.intPart)) {
        iA = MAX_int32_T;
      } else {
        iA = lanedetection_B.intPart + max_idx;
      }

      max_idx = ((iA & 512U) != 0U) + (iA >> 10);
      if (max_idx < 0) {
        max_idx = 0;
      } else {
        if (max_idx > 255) {
          max_idx = 255;
        }
      }

      lanedetection_B.Resize[aidx] = (uint8_T)max_idx;
      aidx++;
    }

    lanedetection_B.acc3 += 320;
  }

  /* End of S-Function (svipresize): '<Root>/Resize' */

  /* S-Function (svipresize): '<Root>/Resize1' */
  /* this algorithm computes interpolation weights on demand as oppose to using a lookup table */
  /* first resize along X-axis direction */
  aidx = 0;
  for (lastColA = 0; lastColA < 240; lastColA++) {
    iA = lastColA << 10;
    max_idx = iA >> 10;
    lanedetection_B.intPart = max_idx * 160;
    if (max_idx < 239) {
      iB = lanedetection_B.intPart + 160;
    } else {
      iB = lanedetection_B.intPart;
    }

    iA -= max_idx << 10;

    /* bilinear interpolation */
    cidx = 1024 - iA;

    /* adjust offsets so that the input image index will not exceed the image bounds */
    if (iB > 38240) {
      iB = 38240;
    }

    for (iC = 0; iC < 160; iC++) {
      lanedetection_B.acc3 = mul_ssu32_sat(cidx,
        lanedetection_B.V4L2VideoCapture_o3[iC + lanedetection_B.intPart]);
      max_idx = mul_ssu32_sat(iA, lanedetection_B.V4L2VideoCapture_o3[iB + iC]);
      if ((lanedetection_B.acc3 < 0) && (max_idx < MIN_int32_T
           - lanedetection_B.acc3)) {
        max_idx = MIN_int32_T;
      } else if ((lanedetection_B.acc3 > 0) && (max_idx > MAX_int32_T
                  - lanedetection_B.acc3)) {
        max_idx = MAX_int32_T;
      } else {
        max_idx += lanedetection_B.acc3;
      }

      max_idx = ((max_idx & 512U) != 0U) + (max_idx >> 10);
      if (max_idx < 0) {
        max_idx = 0;
      } else {
        if (max_idx > 255) {
          max_idx = 255;
        }
      }

      lanedetection_B.Resize1[aidx + iC] = (uint8_T)max_idx;
    }

    aidx += 320;
  }

  /* resize along Y-axis direction */
  lanedetection_B.acc3 = 0;
  for (lastColA = 0; lastColA < 240; lastColA++) {
    max_idx = lastColA * 320;
    for (iC = 0; iC < 160; iC++) {
      lanedetection_DW.Resize_LineBuffer[iC] = lanedetection_B.Resize1[max_idx];
      max_idx++;
    }

    aidx = lanedetection_B.acc3;
    for (iC = 0; iC < 320; iC++) {
      iA = (iC << 10) + 512;
      iA = (((iA & 1U) != 0U) + (iA >> 1)) - 512;
      lanedetection_B.intPart = iA >> 10;
      max_idx = lanedetection_B.intPart << 10;
      if ((iA >= 0) && (max_idx < iA - MAX_int32_T)) {
        iA = MAX_int32_T;
      } else if ((iA < 0) && (max_idx > iA - MIN_int32_T)) {
        iA = MIN_int32_T;
      } else {
        iA -= max_idx;
      }

      if (lanedetection_B.intPart < 0) {
        lanedetection_B.intPart = 0;
        iB = 0;
      } else if (lanedetection_B.intPart < 159) {
        iB = lanedetection_B.intPart + 1;
      } else {
        iB = 159;
      }

      if (iA < -2147482623) {
        cidx = MAX_int32_T;
      } else {
        cidx = 1024 - iA;
      }

      lanedetection_B.intPart = mul_ssu32_sat(cidx,
        lanedetection_DW.Resize_LineBuffer[lanedetection_B.intPart]);
      max_idx = mul_ssu32_sat(iA, lanedetection_DW.Resize_LineBuffer[iB]);
      if ((lanedetection_B.intPart < 0) && (max_idx < MIN_int32_T
           - lanedetection_B.intPart)) {
        iA = MIN_int32_T;
      } else if ((lanedetection_B.intPart > 0) && (max_idx > MAX_int32_T
                  - lanedetection_B.intPart)) {
        iA = MAX_int32_T;
      } else {
        iA = lanedetection_B.intPart + max_idx;
      }

      max_idx = ((iA & 512U) != 0U) + (iA >> 10);
      if (max_idx < 0) {
        max_idx = 0;
      } else {
        if (max_idx > 255) {
          max_idx = 255;
        }
      }

      lanedetection_B.Resize1[aidx] = (uint8_T)max_idx;
      aidx++;
    }

    lanedetection_B.acc3 += 320;
  }

  /* End of S-Function (svipresize): '<Root>/Resize1' */

  /* MATLAB Function: '<Root>/MATLAB Function1' */
  for (max_idx = 0; max_idx < 100; max_idx++) {
    memcpy(&lanedetection_B.imgOUT[max_idx * 320],
           &lanedetection_B.V4L2VideoCapture_o1[max_idx * 320 + 38079], 320U *
           sizeof(uint8_T));
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function1' */

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Threshold'
   */
  memset(&lanedetection_B.V[0], 0, 32000U * sizeof(real_T));
  for (lanedetection_B.intPart = 0; lanedetection_B.intPart < 3;
       lanedetection_B.intPart++) {
    if (lanedetection_B.intPart + 99 < 100) {
      lastColA = 99;
    } else {
      lastColA = 100 - lanedetection_B.intPart;
    }

    for (max_idx = (lanedetection_B.intPart < 1); max_idx <= lastColA; max_idx++)
    {
      iC = lanedetection_B.intPart + max_idx;
      if (!(iC > 1)) {
        iC = 1;
      }

      iC = (iC - 1) * 320;
      iA = max_idx * 320 + 1;
      iB = lanedetection_B.intPart * 3;
      aidx = iA;
      cidx = iC;
      lanedetection_B.acc3 = 1;
      while (lanedetection_B.acc3 <= 319) {
        lanedetection_B.V[cidx] += (real_T)(b[iB] * lanedetection_B.imgOUT[aidx]);
        aidx++;
        cidx++;
        lanedetection_B.acc3++;
      }

      iB++;
      aidx = iA - 1;
      cidx = iC;
      lanedetection_B.acc3 = 1;
      while (lanedetection_B.acc3 <= 320) {
        lanedetection_B.V[cidx] += (real_T)(b[iB] * lanedetection_B.imgOUT[aidx]);
        aidx++;
        cidx++;
        lanedetection_B.acc3++;
      }

      iB++;
      cidx = iC + 1;
      aidx = iA - 1;
      lanedetection_B.acc3 = 1;
      while (lanedetection_B.acc3 <= 319) {
        lanedetection_B.V[cidx] += (real_T)(b[iB] * lanedetection_B.imgOUT[aidx]);
        aidx++;
        cidx++;
        lanedetection_B.acc3++;
      }
    }
  }

  for (max_idx = 0; max_idx < 32000; max_idx++) {
    lanedetection_B.imgEdge[max_idx] = (lanedetection_B.V[max_idx] >
      lanedetection_P.Threshold_Value);
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* S-Function (sviphough): '<Root>/Hough Transform' */
  MWVIP_Hough_R(&lanedetection_B.imgEdge[0], &lanedetection_B.HoughTransform_o1
                [0], &lanedetection_ConstP.HoughTransform_SINE_TABLE_RTP[0],
                &lanedetection_ConstP.HoughTransform_FIRSTRHO_RTP, 320, 100, 671,
                91);

  /* S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */
  iC = 0;
  done = false;
  for (lastColA = 0; lastColA < 120780; lastColA++) {
    lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA] =
      lanedetection_B.HoughTransform_o1[lastColA];
  }

  lanedetection_B.FindLocalMaxima_o1[0] = 0U;
  lanedetection_B.FindLocalMaxima_o1[1] = 0U;
  while (!done) {
    max_idx = 0;
    maxValue = lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[0];
    for (lastColA = 0; lastColA < 120780; lastColA++) {
      if (lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA] > maxValue)
      {
        max_idx = lastColA;
        maxValue = lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA];
      }
    }

    iB = max_idx % 671;
    lastColA = max_idx / 671;
    if (lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[max_idx] >=
        lanedetection_P.FindLocalMaxima_threshold) {
      lanedetection_B.FindLocalMaxima_o1[iC] = (uint32_T)(1 + lastColA);
      lanedetection_B.FindLocalMaxima_o1[1U + iC] = (uint32_T)(1 + iB);
      iC++;
      if (iC == 1) {
        done = true;
      }

      iA = iB - 2;
      if (!(iA > 0)) {
        iA = 0;
      }

      iB += 2;
      if (!(iB < 670)) {
        iB = 670;
      }

      max_idx = lastColA - 3;
      aidx = lastColA + 3;
      if (!((max_idx < 0) || (aidx > 179))) {
        while (max_idx <= aidx) {
          cidx = max_idx * 671;
          for (lastColA = iA; lastColA <= iB; lastColA++) {
            lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA + cidx] =
              0.0F;
          }

          max_idx++;
        }
      } else {
        if (max_idx < 0) {
          lanedetection_B.intPart = max_idx;
          while (lanedetection_B.intPart <= aidx) {
            if (lanedetection_B.intPart < 0) {
              cidx = (lanedetection_B.intPart + 180) * 671 + 670;
              for (lastColA = iA; lastColA <= iB; lastColA++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[cidx - lastColA]
                  = 0.0F;
              }
            } else {
              cidx = lanedetection_B.intPart * 671;
              for (lastColA = iA; lastColA <= iB; lastColA++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA + cidx]
                  = 0.0F;
              }
            }

            lanedetection_B.intPart++;
          }
        }

        if (aidx > 179) {
          lanedetection_B.intPart = max_idx;
          while (lanedetection_B.intPart <= aidx) {
            if (lanedetection_B.intPart > 179) {
              cidx = (lanedetection_B.intPart - 180) * 671 + 670;
              for (lastColA = iA; lastColA <= iB; lastColA++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[cidx - lastColA]
                  = 0.0F;
              }
            } else {
              cidx = lanedetection_B.intPart * 671;
              for (lastColA = iA; lastColA <= iB; lastColA++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA + cidx]
                  = 0.0F;
              }
            }

            lanedetection_B.intPart++;
          }
        }
      }
    } else {
      done = true;
    }
  }

  /* End of S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix1' */
  lanedetection_B.Submatrix1[0] = lanedetection_B.FindLocalMaxima_o1[0];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_B.Submatrix[0] = lanedetection_B.FindLocalMaxima_o1[0];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix1' */
  lanedetection_B.Submatrix1[1] = lanedetection_B.FindLocalMaxima_o1[1];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_B.Submatrix[1] = lanedetection_B.FindLocalMaxima_o1[1];

  /* S-Function (sviphoughlines): '<Root>/Hough Lines' incorporates:
   *  Selector: '<Root>/Selector'
   *  Selector: '<Root>/Selector1'
   */
  lastColA = 0;
  maxValue = (lanedetection_B.HoughTransform_o3[(int32_T)
              lanedetection_B.Submatrix[0] - 1] + 1.1920929E-7F) / ((real32_T)
    cos(lanedetection_B.HoughTransform_o2[(int32_T)lanedetection_B.Submatrix1[0]
        - 1]) + 1.1920929E-7F);

  /* part-1: top horizontal axis */
  lanedetection_B.tmpRound = (real32_T)floor(maxValue + 0.5F);
  if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 99.0F))
  {
    lanedetection_B.tmpOutRC[0U] = 0;
    if (lanedetection_B.tmpRound >= 0.5F) {
      lanedetection_B.tmpOutRC[1U] = (int32_T)(real32_T)floor
        (lanedetection_B.tmpRound + 0.5F);
    } else {
      lanedetection_B.tmpOutRC[1U] = (int32_T)(lanedetection_B.tmpRound * 0.0F);
    }

    lastColA = 1;
  }

  lanedetection_B.y2 = (lanedetection_B.HoughTransform_o3[(int32_T)
                        lanedetection_B.Submatrix[0] - 1] + 1.1920929E-7F) /
    ((real32_T)sin(lanedetection_B.HoughTransform_o2[(int32_T)
                   lanedetection_B.Submatrix1[0] - 1]) + 1.1920929E-7F);

  /* part-2: left vertical axis */
  lanedetection_B.tmpRound = (real32_T)floor(lanedetection_B.y2 + 0.5F);
  if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 319.0F))
  {
    if (lanedetection_B.tmpRound >= 0.5F) {
      lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
        (lanedetection_B.tmpRound + 0.5F);
    } else {
      lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)
        (lanedetection_B.tmpRound * 0.0F);
    }

    lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = 0;
    lastColA++;
  }

  /* part-3: Right vertical axis */
  if (lastColA < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - 99.0F) *
      (lanedetection_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <=
         319.0F)) {
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = 99;
      lastColA++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (lastColA < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_B.y2 * 319.0F) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 99.0F))
    {
      lanedetection_B.tmpOutRC[lastColA << 1] = 319;
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      lastColA++;
    }
  }

  if (lastColA < 2) {
    lanedetection_B.tmpOutRC[0U] = -1;
    lanedetection_B.tmpOutRC[1U] = -1;
    lanedetection_B.tmpOutRC[2U] = -1;
    lanedetection_B.tmpOutRC[3U] = -1;
  }

  lanedetection_B.HoughLines[0] = lanedetection_B.tmpOutRC[1] + 1;
  lanedetection_B.HoughLines[2] = lanedetection_B.tmpOutRC[0] + 1;
  lanedetection_B.HoughLines[4] = lanedetection_B.tmpOutRC[3] + 1;
  lanedetection_B.HoughLines[6] = lanedetection_B.tmpOutRC[2] + 1;
  lastColA = 0;
  maxValue = (lanedetection_B.HoughTransform_o3[(int32_T)
              lanedetection_B.Submatrix[1] - 1] + 1.1920929E-7F) / ((real32_T)
    cos(lanedetection_B.HoughTransform_o2[(int32_T)lanedetection_B.Submatrix1[1]
        - 1]) + 1.1920929E-7F);

  /* part-1: top horizontal axis */
  lanedetection_B.tmpRound = (real32_T)floor(maxValue + 0.5F);
  if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 99.0F))
  {
    lanedetection_B.tmpOutRC[0U] = 0;
    if (lanedetection_B.tmpRound >= 0.5F) {
      lanedetection_B.tmpOutRC[1U] = (int32_T)(real32_T)floor
        (lanedetection_B.tmpRound + 0.5F);
    } else {
      lanedetection_B.tmpOutRC[1U] = (int32_T)(lanedetection_B.tmpRound * 0.0F);
    }

    lastColA = 1;
  }

  lanedetection_B.y2 = (lanedetection_B.HoughTransform_o3[(int32_T)
                        lanedetection_B.Submatrix[1] - 1] + 1.1920929E-7F) /
    ((real32_T)sin(lanedetection_B.HoughTransform_o2[(int32_T)
                   lanedetection_B.Submatrix1[1] - 1]) + 1.1920929E-7F);

  /* part-2: left vertical axis */
  lanedetection_B.tmpRound = (real32_T)floor(lanedetection_B.y2 + 0.5F);
  if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 319.0F))
  {
    if (lanedetection_B.tmpRound >= 0.5F) {
      lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
        (lanedetection_B.tmpRound + 0.5F);
    } else {
      lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)
        (lanedetection_B.tmpRound * 0.0F);
    }

    lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = 0;
    lastColA++;
  }

  /* part-3: Right vertical axis */
  if (lastColA < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - 99.0F) *
      (lanedetection_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <=
         319.0F)) {
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[lastColA << 1] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = 99;
      lastColA++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (lastColA < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_B.y2 * 319.0F) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 99.0F))
    {
      lanedetection_B.tmpOutRC[lastColA << 1] = 319;
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      lastColA++;
    }
  }

  if (lastColA < 2) {
    lanedetection_B.tmpOutRC[0U] = -1;
    lanedetection_B.tmpOutRC[1U] = -1;
    lanedetection_B.tmpOutRC[2U] = -1;
    lanedetection_B.tmpOutRC[3U] = -1;
  }

  lanedetection_B.HoughLines[1] = lanedetection_B.tmpOutRC[1] + 1;
  lanedetection_B.HoughLines[3] = lanedetection_B.tmpOutRC[0] + 1;
  lanedetection_B.HoughLines[5] = lanedetection_B.tmpOutRC[3] + 1;
  lanedetection_B.HoughLines[7] = lanedetection_B.tmpOutRC[2] + 1;

  /* End of S-Function (sviphoughlines): '<Root>/Hough Lines' */

  /* S-Function (svipdrawshapes): '<Root>/Draw Shapes' */
  if (lanedetection_P.DrawShapes_lineWidth == 1) {
    /* Compute output for unity line width
     */
    /* Copy the image from input to output. */
    memcpy(&lanedetection_B.DrawShapes_o1[0],
           &lanedetection_B.V4L2VideoCapture_o1[0], 76800U * sizeof(uint8_T));
    memcpy(&lanedetection_B.DrawShapes_o2[0], &lanedetection_B.Resize[0], 76800U
           * sizeof(uint8_T));
    memcpy(&lanedetection_B.DrawShapes_o3[0], &lanedetection_B.Resize1[0],
           76800U * sizeof(uint8_T));

    /* Update view port. */
    for (lastColA = 0; lastColA < 2; lastColA++) {
      aidx = lanedetection_B.HoughLines[lastColA + 2] - 1;
      lanedetection_B.intPart = lanedetection_B.HoughLines[lastColA] - 1;
      cidx = lanedetection_B.HoughLines[lastColA + 6] - 1;
      lanedetection_B.acc3 = lanedetection_B.HoughLines[4 + lastColA] - 1;
      if ((cidx != aidx) || (lanedetection_B.acc3 != lanedetection_B.intPart)) {
        isMore = false;

        /* Find the visible portion of a line. */
        prevEdgeIsVertical = false;
        visited2 = false;
        done = false;
        max_idx = aidx;
        iA = lanedetection_B.intPart;
        iC = cidx;
        iB = lanedetection_B.acc3;
        while (!done) {
          lanedetection_B.numUniquePix = 0;
          lanedetection_B.loc = 0;

          /* Determine viewport violations. */
          if (max_idx < 0) {
            lanedetection_B.numUniquePix = 4;
          } else {
            if (max_idx > 319) {
              lanedetection_B.numUniquePix = 8;
            }
          }

          if (iC < 0) {
            lanedetection_B.loc = 4;
          } else {
            if (iC > 319) {
              lanedetection_B.loc = 8;
            }
          }

          if (iA < 0) {
            lanedetection_B.numUniquePix |= 1U;
          } else {
            if (iA > 239) {
              lanedetection_B.numUniquePix |= 2U;
            }
          }

          if (iB < 0) {
            lanedetection_B.loc |= 1U;
          } else {
            if (iB > 239) {
              lanedetection_B.loc |= 2U;
            }
          }

          if (!(((uint32_T)lanedetection_B.numUniquePix | lanedetection_B.loc)
                != 0U)) {
            /* Line falls completely within bounds. */
            done = true;
            isMore = true;
          } else if (((uint32_T)lanedetection_B.numUniquePix &
                      lanedetection_B.loc) != 0U) {
            /* Line falls completely out of bounds. */
            done = true;
            isMore = false;
          } else if ((uint32_T)lanedetection_B.numUniquePix != 0U) {
            /* Clip 1st point; if it's in-bounds, clip 2nd point. */
            if (prevEdgeIsVertical) {
              max_idx = aidx;
              iA = lanedetection_B.intPart;
            }

            lanedetection_B.idxCol1 = iC - max_idx;
            lanedetection_B.idxCol2 = iB - iA;
            if ((lanedetection_B.idxCol1 > 1073741824) ||
                (lanedetection_B.idxCol1 < -1073741824) ||
                ((lanedetection_B.idxCol2 > 1073741824) ||
                 (lanedetection_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              done = true;
              isMore = false;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_B.numUniquePix & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_B.numUniquePix = -max_idx * lanedetection_B.idxCol2;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol1 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol1 < 0))) {
                iA += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                iA -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              }

              max_idx = 0;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_B.numUniquePix & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_B.numUniquePix = (319 - max_idx) *
                lanedetection_B.idxCol2;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol1 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol1 < 0))) {
                iA += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                iA -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              }

              max_idx = 319;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_B.numUniquePix & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_B.numUniquePix = -iA * lanedetection_B.idxCol1;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol2 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol2 < 0))) {
                max_idx += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                  lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                max_idx -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                  lanedetection_B.idxCol2) + 1) >> 1;
              }

              iA = 0;
              prevEdgeIsVertical = true;
            } else {
              /* Violated CMax. */
              lanedetection_B.numUniquePix = (239 - iA) *
                lanedetection_B.idxCol1;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol2 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol2 < 0))) {
                max_idx += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                  lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                max_idx -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                  lanedetection_B.idxCol2) + 1) >> 1;
              }

              iA = 239;
              prevEdgeIsVertical = true;
            }
          } else {
            /* Clip the 2nd point. */
            if (visited2) {
              iC = cidx;
              iB = lanedetection_B.acc3;
            }

            lanedetection_B.idxCol1 = iC - max_idx;
            lanedetection_B.idxCol2 = iB - iA;
            if ((lanedetection_B.idxCol1 > 1073741824) ||
                (lanedetection_B.idxCol1 < -1073741824) ||
                ((lanedetection_B.idxCol2 > 1073741824) ||
                 (lanedetection_B.idxCol2 < -1073741824))) {
              /* Possible Inf or Nan. */
              done = true;
              isMore = false;
              visited2 = true;
            } else if ((lanedetection_B.loc & 4U) != 0U) {
              /* Violated RMin. */
              lanedetection_B.numUniquePix = -iC * lanedetection_B.idxCol2;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol1 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol1 < 0))) {
                iB += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                iB -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              }

              iC = 0;
              visited2 = true;
            } else if ((lanedetection_B.loc & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_B.numUniquePix = (319 - iC) *
                lanedetection_B.idxCol2;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol1 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol1 < 0))) {
                iB += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                iB -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              }

              iC = 319;
              visited2 = true;
            } else if ((lanedetection_B.loc & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_B.numUniquePix = -iB * lanedetection_B.idxCol1;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol2 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol2 < 0))) {
                iC += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                iC -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol2) + 1) >> 1;
              }

              iB = 0;
              visited2 = true;
            } else {
              /* Violated CMax. */
              lanedetection_B.numUniquePix = (239 - iB) *
                lanedetection_B.idxCol1;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol2 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol2 < 0))) {
                iC += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                iC -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol2) + 1) >> 1;
              }

              iB = 239;
              visited2 = true;
            }
          }
        }

        if (isMore) {
          /* Draw a line using Bresenham algorithm. */
          /* Initialize the Bresenham algorithm. */
          if (iC >= max_idx) {
            aidx = iC - max_idx;
          } else {
            aidx = max_idx - iC;
          }

          if (iB >= iA) {
            lanedetection_B.intPart = iB - iA;
          } else {
            lanedetection_B.intPart = iA - iB;
          }

          if (aidx > lanedetection_B.intPart) {
            aidx = 1;
            lanedetection_B.intPart = 320;
          } else {
            aidx = 320;
            lanedetection_B.intPart = 1;
            cidx = max_idx;
            max_idx = iA;
            iA = cidx;
            cidx = iC;
            iC = iB;
            iB = cidx;
          }

          if (max_idx > iC) {
            cidx = max_idx;
            max_idx = iC;
            iC = cidx;
            cidx = iA;
            iA = iB;
            iB = cidx;
          }

          cidx = iC - max_idx;
          if (iA <= iB) {
            lanedetection_B.acc3 = 1;
            iB -= iA;
          } else {
            lanedetection_B.acc3 = -1;
            iB = iA - iB;
          }

          lanedetection_B.idxCol1 = -((cidx + 1) >> 1);
          iA = max_idx * aidx + iA * lanedetection_B.intPart;
          lanedetection_B.intPart = lanedetection_B.acc3 *
            lanedetection_B.intPart + aidx;
          done = (max_idx <= iC);
          while (done) {
            lanedetection_B.DrawShapes_o1[iA] =
              lanedetection_P.DrawShapes_color[0];
            lanedetection_B.DrawShapes_o2[iA] =
              lanedetection_P.DrawShapes_color[1];
            lanedetection_B.DrawShapes_o3[iA] =
              lanedetection_P.DrawShapes_color[2];

            /* Compute the next location using Bresenham algorithm. */
            /* Move to the next pixel location. */
            lanedetection_B.idxCol1 += iB;
            if (lanedetection_B.idxCol1 >= 0) {
              lanedetection_B.idxCol1 -= cidx;
              iA += lanedetection_B.intPart;
            } else {
              iA += aidx;
            }

            max_idx++;
            done = (max_idx <= iC);
          }
        }
      }
    }
  } else {
    /* Compute output for non-unity line width
     */
    /* Copy the image from input to output. */
    memcpy(&lanedetection_B.DrawShapes_o1[0],
           &lanedetection_B.V4L2VideoCapture_o1[0], 76800U * sizeof(uint8_T));
    memcpy(&lanedetection_B.DrawShapes_o2[0], &lanedetection_B.Resize[0], 76800U
           * sizeof(uint8_T));
    memcpy(&lanedetection_B.DrawShapes_o3[0], &lanedetection_B.Resize1[0],
           76800U * sizeof(uint8_T));

    /* Update view port. */
    /* ProcessStep-start-1
     */
    if (lanedetection_P.DrawShapes_lineWidth > 1) {
      /* convertLinePts2PolygonPts
       */
      lastColA = lanedetection_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      iC = lanedetection_B.HoughLines[2] - lanedetection_B.HoughLines[6];
      iA = lanedetection_B.HoughLines[0] - lanedetection_B.HoughLines[4];
      if (iA == 0) {
        aidx = 0;
        iB = 1;
        max_idx = ((lanedetection_B.HoughLines[0] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[0] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[2] - 1) << 14;
      } else if (iC == 0) {
        iB = 2;
        aidx = 0;
        max_idx = ((lanedetection_B.HoughLines[2] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[2] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[0] - 1) << 14;
      } else {
        iB = 0;
        aidx = div_repeat_s32_floor(iC << 14, iA << 14, 14U);
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[2] - 1) << 14) -
          mul_s32_loSR((lanedetection_B.HoughLines[0] - 1) << 14, aidx, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iA <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((iC * iC + iA * iA) << 14) << 7,
          14U), 14U);
        max_idx = lanedetection_B.intPart + cidx;
        lanedetection_B.intPart -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_B.HoughLines[0] - 1) << 14,
          aidx, 14U) + ((lanedetection_B.HoughLines[2] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iB == 1) {
        lanedetection_DW.DrawShapes_DW_Points[0] = ((max_idx & 8192U) != 0U) +
          (max_idx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[2] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[12] = ((lanedetection_B.intPart &
          8192U) != 0U) + (lanedetection_B.intPart >> 14);
        lanedetection_DW.DrawShapes_DW_Points[14] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[0] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[2] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            max_idx, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[0] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx += mul_s32_loSR(aidx, lanedetection_B.acc3, 14U);
          lanedetection_DW.DrawShapes_DW_Points[2] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        }

        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[12] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[14] = ((lanedetection_B.intPart
            & 8192U) != 0U) + (lanedetection_B.intPart >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            lanedetection_B.intPart, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) +
            16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[12] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx = mul_s32_loSR(aidx, lanedetection_B.acc3, 14U) +
            lanedetection_B.intPart;
          lanedetection_DW.DrawShapes_DW_Points[14] = ((max_idx & 8192U) != 0U)
            + (max_idx >> 14);
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
      if (iA == 0) {
        aidx = 0;
        iB = 1;
        max_idx = ((lanedetection_B.HoughLines[0] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[0] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[6] - 1) << 14;
      } else if (iC == 0) {
        iB = 2;
        aidx = 0;
        max_idx = ((lanedetection_B.HoughLines[2] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[2] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[4] - 1) << 14;
      } else {
        iB = 0;
        aidx = div_repeat_s32_floor(iC << 14, iA << 14, 14U);
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[2] - 1) << 14) -
          mul_s32_loSR((lanedetection_B.HoughLines[0] - 1) << 14, aidx, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iA <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((iC * iC + iA * iA) << 14) << 7,
          14U), 14U);
        max_idx = lanedetection_B.intPart + cidx;
        lanedetection_B.intPart -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_B.HoughLines[4] - 1) << 14,
          aidx, 14U) + ((lanedetection_B.HoughLines[6] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iB == 1) {
        lanedetection_DW.DrawShapes_DW_Points[4] = ((max_idx & 8192U) != 0U) +
          (max_idx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[6] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[8] = ((lanedetection_B.intPart &
          8192U) != 0U) + (lanedetection_B.intPart >> 14);
        lanedetection_DW.DrawShapes_DW_Points[10] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[4] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[6] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            max_idx, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[4] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx += mul_s32_loSR(aidx, lanedetection_B.acc3, 14U);
          lanedetection_DW.DrawShapes_DW_Points[6] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        }

        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[8] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[10] = ((lanedetection_B.intPart
            & 8192U) != 0U) + (lanedetection_B.intPart >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            lanedetection_B.intPart, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) +
            16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[8] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx = mul_s32_loSR(aidx, lanedetection_B.acc3, 14U) +
            lanedetection_B.intPart;
          lanedetection_DW.DrawShapes_DW_Points[10] = ((max_idx & 8192U) != 0U)
            + (max_idx >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      lastColA = lanedetection_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      iC = lanedetection_B.HoughLines[3] - lanedetection_B.HoughLines[7];
      iA = lanedetection_B.HoughLines[1] - lanedetection_B.HoughLines[5];
      if (iA == 0) {
        aidx = 0;
        iB = 1;
        max_idx = ((lanedetection_B.HoughLines[1] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[1] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[3] - 1) << 14;
      } else if (iC == 0) {
        iB = 2;
        aidx = 0;
        max_idx = ((lanedetection_B.HoughLines[3] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[3] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[1] - 1) << 14;
      } else {
        iB = 0;
        aidx = div_repeat_s32_floor(iC << 14, iA << 14, 14U);
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[3] - 1) << 14) -
          mul_s32_loSR((lanedetection_B.HoughLines[1] - 1) << 14, aidx, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iA <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((iC * iC + iA * iA) << 14) << 7,
          14U), 14U);
        max_idx = lanedetection_B.intPart + cidx;
        lanedetection_B.intPart -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_B.HoughLines[1] - 1) << 14,
          aidx, 14U) + ((lanedetection_B.HoughLines[3] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iB == 1) {
        lanedetection_DW.DrawShapes_DW_Points[1] = ((max_idx & 8192U) != 0U) +
          (max_idx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[3] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[13] = ((lanedetection_B.intPart &
          8192U) != 0U) + (lanedetection_B.intPart >> 14);
        lanedetection_DW.DrawShapes_DW_Points[15] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[1] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[3] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            max_idx, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[1] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx += mul_s32_loSR(aidx, lanedetection_B.acc3, 14U);
          lanedetection_DW.DrawShapes_DW_Points[3] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        }

        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[13] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[15] = ((lanedetection_B.intPart
            & 8192U) != 0U) + (lanedetection_B.intPart >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            lanedetection_B.intPart, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) +
            16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[13] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx = mul_s32_loSR(aidx, lanedetection_B.acc3, 14U) +
            lanedetection_B.intPart;
          lanedetection_DW.DrawShapes_DW_Points[15] = ((max_idx & 8192U) != 0U)
            + (max_idx >> 14);
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
      if (iA == 0) {
        aidx = 0;
        iB = 1;
        max_idx = ((lanedetection_B.HoughLines[1] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[1] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[7] - 1) << 14;
      } else if (iC == 0) {
        iB = 2;
        aidx = 0;
        max_idx = ((lanedetection_B.HoughLines[3] - lastColA) - 1) << 14;
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[3] + lastColA) -
          1) << 14;
        cidx = (lanedetection_B.HoughLines[5] - 1) << 14;
      } else {
        iB = 0;
        aidx = div_repeat_s32_floor(iC << 14, iA << 14, 14U);
        lanedetection_B.intPart = ((lanedetection_B.HoughLines[3] - 1) << 14) -
          mul_s32_loSR((lanedetection_B.HoughLines[1] - 1) << 14, aidx, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iA <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((iC * iC + iA * iA) << 14) << 7,
          14U), 14U);
        max_idx = lanedetection_B.intPart + cidx;
        lanedetection_B.intPart -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_B.HoughLines[5] - 1) << 14,
          aidx, 14U) + ((lanedetection_B.HoughLines[7] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iB == 1) {
        lanedetection_DW.DrawShapes_DW_Points[5] = ((max_idx & 8192U) != 0U) +
          (max_idx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[7] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_DW.DrawShapes_DW_Points[9] = ((lanedetection_B.intPart &
          8192U) != 0U) + (lanedetection_B.intPart >> 14);
        lanedetection_DW.DrawShapes_DW_Points[11] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[5] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[7] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            max_idx, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[5] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx += mul_s32_loSR(aidx, lanedetection_B.acc3, 14U);
          lanedetection_DW.DrawShapes_DW_Points[7] = ((max_idx & 8192U) != 0U) +
            (max_idx >> 14);
        }

        if (iB == 2) {
          lanedetection_DW.DrawShapes_DW_Points[9] = ((cidx & 8192U) != 0U) +
            (cidx >> 14);
          lanedetection_DW.DrawShapes_DW_Points[11] = ((lanedetection_B.intPart
            & 8192U) != 0U) + (lanedetection_B.intPart >> 14);
        } else {
          lanedetection_B.acc3 = div_repeat_s32_floor(mul_s32_loSR(cidx -
            lanedetection_B.intPart, aidx, 14U), mul_s32_loSR(aidx, aidx, 14U) +
            16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[9] = ((lanedetection_B.acc3 &
            8192U) != 0U) + (lanedetection_B.acc3 >> 14);
          max_idx = mul_s32_loSR(aidx, lanedetection_B.acc3, 14U) +
            lanedetection_B.intPart;
          lanedetection_DW.DrawShapes_DW_Points[11] = ((max_idx & 8192U) != 0U)
            + (max_idx >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
    }

    /* ProcessStep-after poly points-1
     */
    max_idx = 2;

    /* just before call for cgpolygon
     */
    if (lanedetection_P.DrawShapes_lineWidth > 1) {
      /* just before call for cgpolygon-2
       */
      max_idx = 4;
    }

    iC = max_idx << 1;

    /* Reset scanline states. */
    iA = 0;
    iB = 0;
    idxTmpArray[0U] = (int8_T)(max_idx - 1);
    isMore = true;
    while (isMore) {
      /* Initialize the scanline. */
      /* Convert polygon vertices to boundaries. */
      aidx = 0;
      lanedetection_B.intPart = iA;
      cidx = iA;

      /* start for loop
       */
      lanedetection_B.acc3 = (((idxTmpArray[0] << 1) + 1) << 1) + iB;
      lanedetection_B.idxCol1 = (idxTmpArray[0] << 2) + iB;
      lanedetection_B.idxTmp = idxTmpArray[0];
      lanedetection_B.idxCol2 = ((idxTmpArray[0] - 1) << 2) + iB;
      lanedetection_B.numUniquePix = max_idx;
      if (lanedetection_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_B.loc =
          lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];

        /* getLoc-1
         */
        lastColA = lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_B.loc = lanedetection_B.HoughLines[lanedetection_B.idxCol1];

        /* getLoc-2
         */
        lastColA = lanedetection_B.HoughLines[lanedetection_B.idxCol2];
      }

      while ((lanedetection_B.idxCol2 >= 0) && (lanedetection_B.loc - 1 ==
              lastColA - 1)) {
        lanedetection_B.idxTmp--;
        lanedetection_B.idxCol2 = ((lanedetection_B.idxTmp - 1) << 2) + iB;
        lanedetection_B.numUniquePix--;
        if (lanedetection_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          lastColA =
            lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];
        } else {
          /* getLoc-2
           */
          lastColA = lanedetection_B.HoughLines[lanedetection_B.idxCol2];
        }
      }

      if (lanedetection_B.idxCol2 < 0) {
        lanedetection_B.idxCol2 = 0;
      }

      if (lanedetection_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_B.loc =
          lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];

        /* getLoc-1
         */
        lanedetection_B.loc_m =
          lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_B.loc = lanedetection_B.HoughLines[lanedetection_B.idxCol1];

        /* getLoc-2
         */
        lanedetection_B.loc_m =
          lanedetection_B.HoughLines[lanedetection_B.idxCol2];
      }

      done = (lanedetection_B.loc_m - 1 > lanedetection_B.loc - 1);
      lanedetection_B.idxRow2 = 2 + iB;
      lanedetection_B.idxCol2 = iB;
      prevEdgeIsVertical = false;
      if (lanedetection_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_B.loc = lanedetection_DW.DrawShapes_DW_Points[iB];

        /* getLoc-1
         */
        lanedetection_B.loc_m =
          lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];
      } else {
        /* getLoc-2
         */
        lanedetection_B.loc = lanedetection_B.HoughLines[iB];

        /* getLoc-2
         */
        lanedetection_B.loc_m =
          lanedetection_B.HoughLines[lanedetection_B.idxCol1];
      }

      for (lastColA = 0; lastColA < lanedetection_B.numUniquePix; lastColA++) {
        if (lanedetection_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          lanedetection_B.idxTmp =
            lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];

          /* getLoc-1
           */
          numActiveEdge =
            lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];
        } else {
          /* getLoc-2
           */
          lanedetection_B.idxTmp =
            lanedetection_B.HoughLines[lanedetection_B.idxCol2];

          /* getLoc-2
           */
          numActiveEdge = lanedetection_B.HoughLines[lanedetection_B.idxCol1];
        }

        if (numActiveEdge - 1 != lanedetection_B.idxTmp - 1) {
          if (lanedetection_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_B.idxTmp =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];

            /* getLoc-1
             */
            numActiveEdge =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];
          } else {
            /* getLoc-2
             */
            lanedetection_B.idxTmp =
              lanedetection_B.HoughLines[lanedetection_B.idxCol2];

            /* getLoc-2
             */
            numActiveEdge = lanedetection_B.HoughLines[lanedetection_B.idxCol1];
          }

          if (numActiveEdge - 1 < lanedetection_B.idxTmp - 1) {
            isMore = false;
          } else {
            isMore = true;
            lanedetection_B.idxTmp = lanedetection_B.acc3;
            lanedetection_B.acc3 = lanedetection_B.idxRow2;
            lanedetection_B.idxRow2 = lanedetection_B.idxTmp;
            lanedetection_B.idxTmp = lanedetection_B.idxCol1;
            lanedetection_B.idxCol1 = lanedetection_B.idxCol2;
            lanedetection_B.idxCol2 = lanedetection_B.idxTmp;
          }

          if (lanedetection_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_B.idxTmp =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];

            /* getLoc-1
             */
            numActiveEdge =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxRow2];

            /* getLoc-1
             */
            lanedetection_B.idxNew =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];

            /* getLoc-1
             */
            lanedetection_B.idxOld =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.acc3];
          } else {
            /* getLoc-2
             */
            lanedetection_B.idxTmp =
              lanedetection_B.HoughLines[lanedetection_B.idxCol2];

            /* getLoc-2
             */
            numActiveEdge = lanedetection_B.HoughLines[lanedetection_B.idxRow2];

            /* getLoc-2
             */
            lanedetection_B.idxNew =
              lanedetection_B.HoughLines[lanedetection_B.idxCol1];

            /* getLoc-2
             */
            lanedetection_B.idxOld =
              lanedetection_B.HoughLines[lanedetection_B.acc3];
          }

          /* Initialize a Bresenham line. */
          edgeTmp_tmp = lanedetection_B.idxTmp - lanedetection_B.idxNew;
          lanedetection_DW.DrawShapes_DW_Polygon[cidx] = 0;
          lanedetection_DW.DrawShapes_DW_Polygon[cidx + 1] =
            lanedetection_B.idxOld - 1;
          lanedetection_DW.DrawShapes_DW_Polygon[cidx + 2] =
            lanedetection_B.idxNew - 1;
          lanedetection_DW.DrawShapes_DW_Polygon[cidx + 3] =
            lanedetection_B.idxTmp - 1;
          lanedetection_DW.DrawShapes_DW_Polygon[cidx + 6] = 0;
          if (numActiveEdge - 1 >= lanedetection_B.idxOld - 1) {
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 8] = numActiveEdge -
              lanedetection_B.idxOld;
          } else {
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 8] =
              lanedetection_B.idxOld - numActiveEdge;
          }

          while (lanedetection_DW.DrawShapes_DW_Polygon[cidx + 8] >= 0) {
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 6]++;
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 8] -= edgeTmp_tmp;
          }

          lanedetection_DW.DrawShapes_DW_Polygon[cidx + 5] =
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 6] - 1;
          lanedetection_DW.DrawShapes_DW_Polygon[cidx + 7] =
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 8] + edgeTmp_tmp;
          lanedetection_DW.DrawShapes_DW_Polygon[cidx + 4] = edgeTmp_tmp -
            (lanedetection_DW.DrawShapes_DW_Polygon[cidx + 7] << 1);
          if (lanedetection_B.idxOld - 1 > numActiveEdge - 1) {
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 5] =
              -lanedetection_DW.DrawShapes_DW_Polygon[cidx + 5];
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 6] =
              -lanedetection_DW.DrawShapes_DW_Polygon[cidx + 6];
          }

          if ((!done) && (!isMore)) {
            /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
            lanedetection_DW.DrawShapes_DW_Polygon[cidx + 2]++;
            if ((lanedetection_DW.DrawShapes_DW_Polygon[cidx] << 1) >
                lanedetection_DW.DrawShapes_DW_Polygon[cidx + 4]) {
              lanedetection_DW.DrawShapes_DW_Polygon[cidx] +=
                lanedetection_DW.DrawShapes_DW_Polygon[cidx + 8];
              lanedetection_DW.DrawShapes_DW_Polygon[cidx + 1] +=
                lanedetection_DW.DrawShapes_DW_Polygon[cidx + 6];
            } else {
              lanedetection_DW.DrawShapes_DW_Polygon[cidx] +=
                lanedetection_DW.DrawShapes_DW_Polygon[cidx + 7];
              lanedetection_DW.DrawShapes_DW_Polygon[cidx + 1] +=
                lanedetection_DW.DrawShapes_DW_Polygon[cidx + 5];
            }
          } else {
            if (done && isMore) {
              lanedetection_DW.DrawShapes_DW_Polygon[cidx + 3]--;
            }
          }

          done = isMore;
          if (!prevEdgeIsVertical) {
            /* Merge two Bresenham lines. */
            prevEdgeIsVertical = false;
            if ((lanedetection_B.intPart != cidx) &&
                ((lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                  + 5] == lanedetection_DW.DrawShapes_DW_Polygon[cidx + 5]) &&
                 (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                  + 6] == lanedetection_DW.DrawShapes_DW_Polygon[cidx + 6]) &&
                 (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                  + 7] == lanedetection_DW.DrawShapes_DW_Polygon[cidx + 7]) &&
                 (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                  + 8] == lanedetection_DW.DrawShapes_DW_Polygon[cidx + 8]))) {
              if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                  + 3] + 1 == lanedetection_DW.DrawShapes_DW_Polygon[cidx + 2])
              {
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart +
                  3] = lanedetection_DW.DrawShapes_DW_Polygon[cidx + 3];
                prevEdgeIsVertical = true;
              } else {
                if (lanedetection_DW.DrawShapes_DW_Polygon[cidx + 3] + 1 ==
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                    + 2]) {
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                    + 1] = lanedetection_DW.DrawShapes_DW_Polygon[cidx + 1];
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                    + 2] = lanedetection_DW.DrawShapes_DW_Polygon[cidx + 2];
                  prevEdgeIsVertical = true;
                }
              }
            }

            if (!prevEdgeIsVertical) {
              lanedetection_B.intPart = cidx;
              aidx++;
            }
          } else {
            lanedetection_B.intPart = cidx;
            aidx++;
          }

          cidx = lanedetection_B.intPart + 9;
          if (!isMore) {
            lanedetection_B.acc3 = lanedetection_B.idxRow2;
            lanedetection_B.idxCol1 = lanedetection_B.idxCol2;
          }

          lanedetection_B.idxRow2 = lanedetection_B.acc3 + 4;
          lanedetection_B.idxCol2 = lanedetection_B.idxCol1 + 4;
          prevEdgeIsVertical = false;
        } else {
          prevEdgeIsVertical = true;
          lanedetection_B.acc3 = lanedetection_B.idxRow2;
          lanedetection_B.idxCol1 = lanedetection_B.idxCol2;
          lanedetection_B.idxRow2 += 4;
          lanedetection_B.idxCol2 += 4;
        }
      }

      if (!(lanedetection_B.loc_m - 1 == lanedetection_B.loc - 1)) {
        /* Merge two Bresenham lines. */
        done = false;
        if ((iA != lanedetection_B.intPart) &&
            ((lanedetection_DW.DrawShapes_DW_Polygon[iA + 5] ==
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart + 5])
             && (lanedetection_DW.DrawShapes_DW_Polygon[iA + 6] ==
                 lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                 + 6]) && (lanedetection_DW.DrawShapes_DW_Polygon[iA + 7] ==
                           lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart
                           + 7]) && (lanedetection_DW.DrawShapes_DW_Polygon[iA +
              8] ==
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart + 8])))
        {
          if (lanedetection_DW.DrawShapes_DW_Polygon[iA + 3] + 1 ==
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart + 2])
          {
            lanedetection_DW.DrawShapes_DW_Polygon[iA + 3] =
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart + 3];
            done = true;
          } else {
            if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart +
                3] + 1 == lanedetection_DW.DrawShapes_DW_Polygon[iA + 2]) {
              lanedetection_DW.DrawShapes_DW_Polygon[iA + 1] =
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart +
                1];
              lanedetection_DW.DrawShapes_DW_Polygon[iA + 2] =
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart +
                2];
              done = true;
            }
          }
        }

        if (done) {
          aidx--;
          cidx -= 9;
        }
      }

      /* Set all other edges to invalid. */
      for (lastColA = aidx; lastColA < max_idx; lastColA++) {
        lanedetection_DW.DrawShapes_DW_Polygon[cidx + 2] = 1;
        lanedetection_DW.DrawShapes_DW_Polygon[cidx + 3] = 0;
        cidx += 9;
      }

      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_B.idxNew = iA;
        lanedetection_B.idxOld = iA + 9;
        isMore = false;
        for (lastColA = 1; lastColA < aidx; lastColA++) {
          if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew + 2]
              > lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
              2]) {
            isMore = true;
            for (lanedetection_B.intPart = 0; lanedetection_B.intPart < 9;
                 lanedetection_B.intPart++) {
              edgeTmp_tmp = lanedetection_B.idxNew + lanedetection_B.intPart;
              edgeTmp = lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_B.idxOld +
                lanedetection_B.intPart;
              lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp] =
                edgeTmp;
            }
          }

          lanedetection_B.idxNew = lanedetection_B.idxOld;
          lanedetection_B.idxOld += 9;
        }
      }

      /* Find out the last column of the polygon. */
      lanedetection_B.intPart = iA + 3;
      cidx = lanedetection_DW.DrawShapes_DW_Polygon[iA + 3];
      for (lastColA = 1; lastColA < aidx; lastColA++) {
        lanedetection_B.intPart += 9;
        if (cidx <
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart]) {
          cidx = lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart];
        }
      }

      lanedetection_B.acc3 = cidx;
      if (cidx > 239) {
        lanedetection_B.acc3 = 239;
      }

      /* Find out the first column of the polygon. */
      lanedetection_B.intPart = iA + 2;
      cidx = lanedetection_DW.DrawShapes_DW_Polygon[iA + 2];
      for (lastColA = 1; lastColA < aidx; lastColA++) {
        lanedetection_B.intPart += 9;
        if (cidx >
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart]) {
          cidx = lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.intPart];
        }
      }

      if (cidx < 0) {
        cidx = 0;
      }

      /* Move to the next column and find out boundaries of the polygon at this column. */
      lanedetection_B.idxNew = iA;
      lanedetection_B.idxOld = iA;
      lanedetection_B.idxCol1 = iA;
      lanedetection_B.idxCol2 = 0;
      numActiveEdge = 0;
      for (lastColA = 0; lastColA < aidx; lastColA++) {
        /* Find out the valid boundaries and bring them to the latest column. */
        if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld + 3] >=
            cidx) {
          if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld + 2]
              <= cidx) {
            while (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                   + 2] < cidx) {
              /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld + 2]
                ++;
              if ((lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld]
                   << 1) >
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                  + 4]) {
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld] +=
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                  + 8];
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
                  1] +=
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                  + 6];
              } else {
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld] +=
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                  + 7];
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
                  1] +=
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                  + 5];
              }
            }

            lanedetection_B.idxCol1 += 9;
            numActiveEdge++;
          }

          if (lanedetection_B.idxOld != lanedetection_B.idxNew) {
            for (lanedetection_B.intPart = 0; lanedetection_B.intPart < 9;
                 lanedetection_B.intPart++) {
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew +
                lanedetection_B.intPart] =
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
                lanedetection_B.intPart];
            }
          }

          lanedetection_B.idxNew += 9;
          lanedetection_B.idxCol2++;
        }

        lanedetection_B.idxOld += 9;
      }

      /* Sort the boundaries of the polygon according to row values. */
      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_B.idxNew = iA;
        lanedetection_B.idxOld = iA + 9;
        isMore = false;
        for (lastColA = 1; lastColA < numActiveEdge; lastColA++) {
          if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew + 1]
              > lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
              1]) {
            isMore = true;
            for (lanedetection_B.intPart = 0; lanedetection_B.intPart < 9;
                 lanedetection_B.intPart++) {
              edgeTmp_tmp = lanedetection_B.idxNew + lanedetection_B.intPart;
              edgeTmp = lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_B.idxOld +
                lanedetection_B.intPart;
              lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp] =
                edgeTmp;
            }
          }

          lanedetection_B.idxNew = lanedetection_B.idxOld;
          lanedetection_B.idxOld += 9;
        }
      }

      aidx = iA;
      lanedetection_B.numUniquePix = cidx + 1;
      lanedetection_B.loc = 0;
      lanedetection_B.intPart = 0;
      numActiveEdge = -1;
      isMore = (0 <= lanedetection_B.acc3);
      while (isMore) {
        /* Get a string of pixels */
        prevEdgeIsVertical = false;
        done = (lanedetection_B.intPart != 0);
        lanedetection_B.idxTmp = lanedetection_B.loc;
        if ((lanedetection_B.loc >= cidx) && (lanedetection_B.loc <=
             lanedetection_B.acc3)) {
          if (aidx < lanedetection_B.idxCol1) {
            lastColA = lanedetection_DW.DrawShapes_DW_Polygon[aidx + 1];
            aidx += 9;
            if ((lastColA == numActiveEdge) && (aidx < lanedetection_B.idxCol1))
            {
              lanedetection_B.loc_m =
                lanedetection_DW.DrawShapes_DW_Polygon[aidx + 1];
              isMore = (aidx < lanedetection_B.idxCol1);
              while (isMore && (lastColA == lanedetection_B.loc_m)) {
                prevEdgeIsVertical = true;
                lastColA = lanedetection_DW.DrawShapes_DW_Polygon[aidx + 1];
                aidx += 9;
                isMore = (aidx < lanedetection_B.idxCol1);
                if (isMore) {
                  lanedetection_B.loc_m =
                    lanedetection_DW.DrawShapes_DW_Polygon[aidx + 1];
                }
              }

              if (!isMore) {
                prevEdgeIsVertical = false;
              }
            }

            if (lanedetection_B.intPart != 0) {
              lanedetection_B.loc_m = numActiveEdge;
              if (lastColA <= 319) {
                lanedetection_B.idxRow2 = lastColA;
                numActiveEdge = lastColA;
              } else {
                lanedetection_B.idxRow2 = 319;
                numActiveEdge = 319;
              }
            } else {
              lanedetection_B.loc_m = numActiveEdge + 1;
              if ((lastColA > 0) && (lastColA <= 319)) {
                lanedetection_B.idxRow2 = lastColA - 1;
                numActiveEdge = lastColA;
              } else if (lastColA <= 0) {
                lanedetection_B.idxRow2 = -1;
                numActiveEdge = 0;
              } else {
                lanedetection_B.idxRow2 = 319;
                numActiveEdge = 320;
              }
            }

            if (!prevEdgeIsVertical) {
              lanedetection_B.intPart = !(lanedetection_B.intPart != 0);
            }
          } else {
            /* Reset states and move to the next column. */
            done = false;
            lanedetection_B.loc_m = numActiveEdge + 1;
            lanedetection_B.idxRow2 = 319;

            /* Move to the next column and find out boundaries of the polygon at this column. */
            lanedetection_B.idxNew = iA;
            lanedetection_B.idxOld = iA;
            lanedetection_B.idxCol1 = iA;
            aidx = 0;
            numActiveEdge = 0;
            for (lastColA = 0; lastColA < lanedetection_B.idxCol2; lastColA++) {
              /* Find out the valid boundaries and bring them to the latest column. */
              if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                  + 3] >= lanedetection_B.numUniquePix) {
                if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                    + 2] <= lanedetection_B.numUniquePix) {
                  while
                      (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                       + 2] < lanedetection_B.numUniquePix) {
                    /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                      + 2]++;
                    if ((lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld]
                         << 1) >
                        lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                        + 4]) {
                      lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld]
                        +=
                        lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                        + 8];
                      lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                        + 1] +=
                        lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                        + 6];
                    } else {
                      lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld]
                        +=
                        lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                        + 7];
                      lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                        + 1] +=
                        lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                        + 5];
                    }
                  }

                  lanedetection_B.idxCol1 += 9;
                  numActiveEdge++;
                }

                if (lanedetection_B.idxOld != lanedetection_B.idxNew) {
                  for (lanedetection_B.intPart = 0; lanedetection_B.intPart < 9;
                       lanedetection_B.intPart++) {
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew
                      + lanedetection_B.intPart] =
                      lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                      + lanedetection_B.intPart];
                  }
                }

                lanedetection_B.idxNew += 9;
                aidx++;
              }

              lanedetection_B.idxOld += 9;
            }

            lanedetection_B.idxCol2 = aidx;

            /* Sort the boundaries of the polygon according to row values. */
            /* Sort the boundaries of the polygon. */
            isMore = true;
            while (isMore) {
              lanedetection_B.idxNew = iA;
              lanedetection_B.idxOld = iA + 9;
              isMore = false;
              for (lastColA = 1; lastColA < numActiveEdge; lastColA++) {
                if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew
                    + 1] >
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                    + 1]) {
                  isMore = true;
                  for (lanedetection_B.intPart = 0; lanedetection_B.intPart < 9;
                       lanedetection_B.intPart++) {
                    edgeTmp_tmp = lanedetection_B.idxNew +
                      lanedetection_B.intPart;
                    edgeTmp = lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
                    DrawShapes_DW_Polygon_tmp = lanedetection_B.idxOld +
                      lanedetection_B.intPart;
                    lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                      lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
                    lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                      = edgeTmp;
                  }
                }

                lanedetection_B.idxNew = lanedetection_B.idxOld;
                lanedetection_B.idxOld += 9;
              }
            }

            aidx = iA;
            lanedetection_B.numUniquePix++;
            lanedetection_B.intPart = 0;
            numActiveEdge = -1;
            lanedetection_B.loc++;
          }
        } else {
          lanedetection_B.loc_m = 0;
          lanedetection_B.idxRow2 = 319;
          lanedetection_B.loc++;
        }

        if (lanedetection_B.loc_m < 0) {
          lanedetection_B.loc_m = 0;
        }

        if (lanedetection_B.idxRow2 < lanedetection_B.loc_m) {
          lanedetection_B.idxRow2 = lanedetection_B.loc_m - 1;
        }

        if (done) {
          lanedetection_B.idxTmp = lanedetection_B.idxTmp * 320 +
            lanedetection_B.loc_m;
          lanedetection_B.idxNew = 1;
          if (lanedetection_P.DrawShapes_lineWidth > 1) {
            lanedetection_B.idxNew = 0;
          }

          lanedetection_B.idxOld = lanedetection_B.idxTmp;
          for (lastColA = lanedetection_B.loc_m; lastColA <=
               lanedetection_B.idxRow2; lastColA++) {
            if (lanedetection_B.idxNew != 0) {
              lanedetection_B.DrawShapes_o1[lanedetection_B.idxOld] = (uint8_T)
                (((int32_T)((uint32_T)
                            lanedetection_B.DrawShapes_o1[lanedetection_B.idxOld]
                            * lanedetection_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_B.DrawShapes_o1[lanedetection_B.idxOld] = (uint8_T)
                ((uint32_T)lanedetection_B.DrawShapes_o1[lanedetection_B.idxOld]
                 + lanedetection_P.DrawShapes_color[0]);
            } else {
              lanedetection_B.DrawShapes_o1[lanedetection_B.idxOld] =
                lanedetection_P.DrawShapes_color[0];
            }

            lanedetection_B.idxOld++;
          }

          lanedetection_B.idxNew = 1;
          if (lanedetection_P.DrawShapes_lineWidth > 1) {
            lanedetection_B.idxNew = 0;
          }

          lanedetection_B.idxOld = lanedetection_B.idxTmp;
          for (lastColA = lanedetection_B.loc_m; lastColA <=
               lanedetection_B.idxRow2; lastColA++) {
            if (lanedetection_B.idxNew != 0) {
              lanedetection_B.DrawShapes_o2[lanedetection_B.idxOld] = (uint8_T)
                (((int32_T)((uint32_T)
                            lanedetection_B.DrawShapes_o2[lanedetection_B.idxOld]
                            * lanedetection_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_B.DrawShapes_o2[lanedetection_B.idxOld] = (uint8_T)
                ((uint32_T)lanedetection_B.DrawShapes_o2[lanedetection_B.idxOld]
                 + lanedetection_P.DrawShapes_color[1]);
            } else {
              lanedetection_B.DrawShapes_o2[lanedetection_B.idxOld] =
                lanedetection_P.DrawShapes_color[1];
            }

            lanedetection_B.idxOld++;
          }

          lanedetection_B.idxNew = 1;
          if (lanedetection_P.DrawShapes_lineWidth > 1) {
            lanedetection_B.idxNew = 0;
          }

          while (lanedetection_B.loc_m <= lanedetection_B.idxRow2) {
            if (lanedetection_B.idxNew != 0) {
              lanedetection_B.DrawShapes_o3[lanedetection_B.idxTmp] = (uint8_T)
                (((int32_T)((uint32_T)
                            lanedetection_B.DrawShapes_o3[lanedetection_B.idxTmp]
                            * lanedetection_B.DrawShapes_o1[0]) << 14) >> 14);
              lanedetection_B.DrawShapes_o3[lanedetection_B.idxTmp] = (uint8_T)
                ((uint32_T)lanedetection_B.DrawShapes_o3[lanedetection_B.idxTmp]
                 + lanedetection_P.DrawShapes_color[2]);
            } else {
              lanedetection_B.DrawShapes_o3[lanedetection_B.idxTmp] =
                lanedetection_P.DrawShapes_color[2];
            }

            lanedetection_B.idxTmp++;
            lanedetection_B.loc_m++;
          }
        }

        isMore = (lanedetection_B.loc <= lanedetection_B.acc3);
      }

      /* Move to the next polygon. */
      iA += max_idx * 9;
      if (iB >= div_s32_floor(iC, max_idx) - 1) {
        iB = 0;
      } else {
        iB++;
      }

      isMore = (iA < (max_idx << 1) * 9);
    }
  }

  /* End of S-Function (svipdrawshapes): '<Root>/Draw Shapes' */

  /* S-Function (svipresize): '<Root>/Resize2' */
  /* use pre-computed weights and index table to perform interpolation */
  aidx = 0;

  /* resize along X-axis direction */
  for (iC = 0; iC < 320; iC++) {
    max_idx = iC;
    for (lastColA = 0; lastColA < 240; lastColA++) {
      iA = (lanedetection_B.DrawShapes_o2[lastColA * 320 + iC] * 127) << 3;
      lanedetection_DW.Resize2_IntBuffer[max_idx] = (uint8_T)(((iA & 512U) != 0U)
        + (iA >> 10));
      max_idx += 320;
    }
  }

  /* resize along Y-axis direction */
  for (lastColA = 0; lastColA < 240; lastColA++) {
    max_idx = lastColA * 320;
    for (iC = 0; iC < 320; iC++) {
      lanedetection_DW.Resize2_LineBuffer[iC] =
        lanedetection_DW.Resize2_IntBuffer[max_idx];
      max_idx++;
    }

    for (iC = 0; iC < 160; iC++) {
      iA = (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iC]]
            * lanedetection_ConstP.pooled7[iC]) << 3;
      iB = iC + 160;
      max_idx =
        (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iB]] *
         lanedetection_ConstP.pooled7[iB]) << 3;
      if ((iA < 0) && (max_idx < MIN_int32_T - iA)) {
        iA = MIN_int32_T;
      } else if ((iA > 0) && (max_idx > MAX_int32_T - iA)) {
        iA = MAX_int32_T;
      } else {
        iA += max_idx;
      }

      iB += 160;
      max_idx =
        (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iB]] *
         lanedetection_ConstP.pooled7[iB]) << 3;
      if ((iA < 0) && (max_idx < MIN_int32_T - iA)) {
        iA = MIN_int32_T;
      } else if ((iA > 0) && (max_idx > MAX_int32_T - iA)) {
        iA = MAX_int32_T;
      } else {
        iA += max_idx;
      }

      iB += 160;
      max_idx =
        (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iB]] *
         lanedetection_ConstP.pooled7[iB]) << 3;
      if ((iA < 0) && (max_idx < MIN_int32_T - iA)) {
        iA = MIN_int32_T;
      } else if ((iA > 0) && (max_idx > MAX_int32_T - iA)) {
        iA = MAX_int32_T;
      } else {
        iA += max_idx;
      }

      max_idx = ((iA & 512U) != 0U) + (iA >> 10);
      if (max_idx < 0) {
        max_idx = 0;
      } else {
        if (max_idx > 255) {
          max_idx = 255;
        }
      }

      lanedetection_B.Resize2[aidx] = (uint8_T)max_idx;
      aidx++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize2' */

  /* S-Function (svipresize): '<Root>/Resize3' */
  /* use pre-computed weights and index table to perform interpolation */
  aidx = 0;

  /* resize along X-axis direction */
  for (iC = 0; iC < 320; iC++) {
    max_idx = iC;
    for (lastColA = 0; lastColA < 240; lastColA++) {
      iA = (lanedetection_B.DrawShapes_o3[lastColA * 320 + iC] * 127) << 3;
      lanedetection_DW.Resize3_IntBuffer[max_idx] = (uint8_T)(((iA & 512U) != 0U)
        + (iA >> 10));
      max_idx += 320;
    }
  }

  /* resize along Y-axis direction */
  for (lastColA = 0; lastColA < 240; lastColA++) {
    max_idx = lastColA * 320;
    for (iC = 0; iC < 320; iC++) {
      lanedetection_DW.Resize2_LineBuffer[iC] =
        lanedetection_DW.Resize3_IntBuffer[max_idx];
      max_idx++;
    }

    for (iC = 0; iC < 160; iC++) {
      iA = (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iC]]
            * lanedetection_ConstP.pooled7[iC]) << 3;
      iB = iC + 160;
      max_idx =
        (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iB]] *
         lanedetection_ConstP.pooled7[iB]) << 3;
      if ((iA < 0) && (max_idx < MIN_int32_T - iA)) {
        iA = MIN_int32_T;
      } else if ((iA > 0) && (max_idx > MAX_int32_T - iA)) {
        iA = MAX_int32_T;
      } else {
        iA += max_idx;
      }

      iB += 160;
      max_idx =
        (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iB]] *
         lanedetection_ConstP.pooled7[iB]) << 3;
      if ((iA < 0) && (max_idx < MIN_int32_T - iA)) {
        iA = MIN_int32_T;
      } else if ((iA > 0) && (max_idx > MAX_int32_T - iA)) {
        iA = MAX_int32_T;
      } else {
        iA += max_idx;
      }

      iB += 160;
      max_idx =
        (lanedetection_DW.Resize2_LineBuffer[lanedetection_ConstP.pooled2[iB]] *
         lanedetection_ConstP.pooled7[iB]) << 3;
      if ((iA < 0) && (max_idx < MIN_int32_T - iA)) {
        iA = MIN_int32_T;
      } else if ((iA > 0) && (max_idx > MAX_int32_T - iA)) {
        iA = MAX_int32_T;
      } else {
        iA += max_idx;
      }

      max_idx = ((iA & 512U) != 0U) + (iA >> 10);
      if (max_idx < 0) {
        max_idx = 0;
      } else {
        if (max_idx > 255) {
          max_idx = 255;
        }
      }

      lanedetection_B.Resize3[aidx] = (uint8_T)max_idx;
      aidx++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize3' */
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  memcpy(&lanedetection_B.DrawShapes_o2[0], &lanedetection_B.DrawShapes_o1[0],
         76800U * sizeof(uint8_T));
  memcpy(&lanedetection_B.pln2[0], &lanedetection_B.Resize2[0], 38400U * sizeof
         (uint8_T));
  memcpy(&lanedetection_B.pln3[0], &lanedetection_B.Resize3[0], 38400U * sizeof
         (uint8_T));
  MW_SDL_videoDisplayOutput(lanedetection_B.DrawShapes_o2, lanedetection_B.pln2,
    lanedetection_B.pln3);

  /* Math: '<Root>/Transpose' */
  for (max_idx = 0; max_idx < 320; max_idx++) {
    for (lastColA = 0; lastColA < 100; lastColA++) {
      lanedetection_B.Transpose[lastColA + 100 * max_idx] =
        lanedetection_B.imgEdge[320 * lastColA + max_idx];
    }
  }

  /* End of Math: '<Root>/Transpose' */

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.05s, 0.0s] */
    rtExtModeUpload(0, lanedetection_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.05s, 0.0s] */
    if ((rtmGetTFinal(lanedetection_M)!=-1) &&
        !((rtmGetTFinal(lanedetection_M)-lanedetection_M->Timing.taskTime0) >
          lanedetection_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(lanedetection_M, "Simulation finished");
    }

    if (rtmGetStopRequested(lanedetection_M)) {
      rtmSetErrorStatus(lanedetection_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  lanedetection_M->Timing.taskTime0 =
    (++lanedetection_M->Timing.clockTick0) * lanedetection_M->Timing.stepSize0;
}

/* Model initialize function */
void lanedetection_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)lanedetection_M, 0,
                sizeof(RT_MODEL_lanedetection_T));
  rtmSetTFinal(lanedetection_M, -1);
  lanedetection_M->Timing.stepSize0 = 0.05;

  /* External mode info */
  lanedetection_M->Sizes.checksums[0] = (1260964239U);
  lanedetection_M->Sizes.checksums[1] = (1201864594U);
  lanedetection_M->Sizes.checksums[2] = (1678593302U);
  lanedetection_M->Sizes.checksums[3] = (2177331807U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    lanedetection_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lanedetection_M->extModeInfo,
      &lanedetection_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lanedetection_M->extModeInfo,
                        lanedetection_M->Sizes.checksums);
    rteiSetTPtr(lanedetection_M->extModeInfo, rtmGetTPtr(lanedetection_M));
  }

  /* block I/O */
  (void) memset(((void *) &lanedetection_B), 0,
                sizeof(B_lanedetection_T));

  {
    lanedetection_B.HoughTransform_o2[0] = -1.57079637F;
    lanedetection_B.HoughTransform_o2[1] = -1.55334306F;
    lanedetection_B.HoughTransform_o2[2] = -1.53588974F;
    lanedetection_B.HoughTransform_o2[3] = -1.51843643F;
    lanedetection_B.HoughTransform_o2[4] = -1.50098312F;
    lanedetection_B.HoughTransform_o2[5] = -1.48352981F;
    lanedetection_B.HoughTransform_o2[6] = -1.46607661F;
    lanedetection_B.HoughTransform_o2[7] = -1.4486233F;
    lanedetection_B.HoughTransform_o2[8] = -1.43117F;
    lanedetection_B.HoughTransform_o2[9] = -1.41371667F;
    lanedetection_B.HoughTransform_o2[10] = -1.39626336F;
    lanedetection_B.HoughTransform_o2[11] = -1.37881017F;
    lanedetection_B.HoughTransform_o2[12] = -1.36135685F;
    lanedetection_B.HoughTransform_o2[13] = -1.34390354F;
    lanedetection_B.HoughTransform_o2[14] = -1.32645023F;
    lanedetection_B.HoughTransform_o2[15] = -1.30899692F;
    lanedetection_B.HoughTransform_o2[16] = -1.2915436F;
    lanedetection_B.HoughTransform_o2[17] = -1.27409041F;
    lanedetection_B.HoughTransform_o2[18] = -1.2566371F;
    lanedetection_B.HoughTransform_o2[19] = -1.23918378F;
    lanedetection_B.HoughTransform_o2[20] = -1.22173047F;
    lanedetection_B.HoughTransform_o2[21] = -1.20427716F;
    lanedetection_B.HoughTransform_o2[22] = -1.18682384F;
    lanedetection_B.HoughTransform_o2[23] = -1.16937065F;
    lanedetection_B.HoughTransform_o2[24] = -1.15191734F;
    lanedetection_B.HoughTransform_o2[25] = -1.13446403F;
    lanedetection_B.HoughTransform_o2[26] = -1.11701071F;
    lanedetection_B.HoughTransform_o2[27] = -1.0995574F;
    lanedetection_B.HoughTransform_o2[28] = -1.08210409F;
    lanedetection_B.HoughTransform_o2[29] = -1.06465089F;
    lanedetection_B.HoughTransform_o2[30] = -1.04719758F;
    lanedetection_B.HoughTransform_o2[31] = -1.02974427F;
    lanedetection_B.HoughTransform_o2[32] = -1.01229095F;
    lanedetection_B.HoughTransform_o2[33] = -0.994837701F;
    lanedetection_B.HoughTransform_o2[34] = -0.977384388F;
    lanedetection_B.HoughTransform_o2[35] = -0.959931076F;
    lanedetection_B.HoughTransform_o2[36] = -0.942477822F;
    lanedetection_B.HoughTransform_o2[37] = -0.925024509F;
    lanedetection_B.HoughTransform_o2[38] = -0.907571197F;
    lanedetection_B.HoughTransform_o2[39] = -0.890117943F;
    lanedetection_B.HoughTransform_o2[40] = -0.87266463F;
    lanedetection_B.HoughTransform_o2[41] = -0.855211318F;
    lanedetection_B.HoughTransform_o2[42] = -0.837758064F;
    lanedetection_B.HoughTransform_o2[43] = -0.820304751F;
    lanedetection_B.HoughTransform_o2[44] = -0.802851439F;
    lanedetection_B.HoughTransform_o2[45] = -0.785398185F;
    lanedetection_B.HoughTransform_o2[46] = -0.767944872F;
    lanedetection_B.HoughTransform_o2[47] = -0.75049156F;
    lanedetection_B.HoughTransform_o2[48] = -0.733038306F;
    lanedetection_B.HoughTransform_o2[49] = -0.715585F;
    lanedetection_B.HoughTransform_o2[50] = -0.69813168F;
    lanedetection_B.HoughTransform_o2[51] = -0.680678427F;
    lanedetection_B.HoughTransform_o2[52] = -0.663225114F;
    lanedetection_B.HoughTransform_o2[53] = -0.645771801F;
    lanedetection_B.HoughTransform_o2[54] = -0.628318548F;
    lanedetection_B.HoughTransform_o2[55] = -0.610865235F;
    lanedetection_B.HoughTransform_o2[56] = -0.593411922F;
    lanedetection_B.HoughTransform_o2[57] = -0.575958669F;
    lanedetection_B.HoughTransform_o2[58] = -0.558505356F;
    lanedetection_B.HoughTransform_o2[59] = -0.541052043F;
    lanedetection_B.HoughTransform_o2[60] = -0.52359879F;
    lanedetection_B.HoughTransform_o2[61] = -0.506145477F;
    lanedetection_B.HoughTransform_o2[62] = -0.488692194F;
    lanedetection_B.HoughTransform_o2[63] = -0.471238911F;
    lanedetection_B.HoughTransform_o2[64] = -0.453785598F;
    lanedetection_B.HoughTransform_o2[65] = -0.436332315F;
    lanedetection_B.HoughTransform_o2[66] = -0.418879032F;
    lanedetection_B.HoughTransform_o2[67] = -0.401425719F;
    lanedetection_B.HoughTransform_o2[68] = -0.383972436F;
    lanedetection_B.HoughTransform_o2[69] = -0.366519153F;
    lanedetection_B.HoughTransform_o2[70] = -0.34906584F;
    lanedetection_B.HoughTransform_o2[71] = -0.331612557F;
    lanedetection_B.HoughTransform_o2[72] = -0.314159274F;
    lanedetection_B.HoughTransform_o2[73] = -0.296705961F;
    lanedetection_B.HoughTransform_o2[74] = -0.279252678F;
    lanedetection_B.HoughTransform_o2[75] = -0.261799395F;
    lanedetection_B.HoughTransform_o2[76] = -0.244346097F;
    lanedetection_B.HoughTransform_o2[77] = -0.226892799F;
    lanedetection_B.HoughTransform_o2[78] = -0.209439516F;
    lanedetection_B.HoughTransform_o2[79] = -0.191986218F;
    lanedetection_B.HoughTransform_o2[80] = -0.17453292F;
    lanedetection_B.HoughTransform_o2[81] = -0.157079637F;
    lanedetection_B.HoughTransform_o2[82] = -0.139626339F;
    lanedetection_B.HoughTransform_o2[83] = -0.122173049F;
    lanedetection_B.HoughTransform_o2[84] = -0.104719758F;
    lanedetection_B.HoughTransform_o2[85] = -0.0872664601F;
    lanedetection_B.HoughTransform_o2[86] = -0.0698131695F;
    lanedetection_B.HoughTransform_o2[87] = -0.052359879F;
    lanedetection_B.HoughTransform_o2[88] = -0.0349065848F;
    lanedetection_B.HoughTransform_o2[89] = -0.0174532924F;
    lanedetection_B.HoughTransform_o2[90] = 0.0F;
    lanedetection_B.HoughTransform_o2[91] = 0.0174532924F;
    lanedetection_B.HoughTransform_o2[92] = 0.0349065848F;
    lanedetection_B.HoughTransform_o2[93] = 0.052359879F;
    lanedetection_B.HoughTransform_o2[94] = 0.0698131695F;
    lanedetection_B.HoughTransform_o2[95] = 0.0872664601F;
    lanedetection_B.HoughTransform_o2[96] = 0.104719758F;
    lanedetection_B.HoughTransform_o2[97] = 0.122173049F;
    lanedetection_B.HoughTransform_o2[98] = 0.139626339F;
    lanedetection_B.HoughTransform_o2[99] = 0.157079637F;
    lanedetection_B.HoughTransform_o2[100] = 0.17453292F;
    lanedetection_B.HoughTransform_o2[101] = 0.191986218F;
    lanedetection_B.HoughTransform_o2[102] = 0.209439516F;
    lanedetection_B.HoughTransform_o2[103] = 0.226892799F;
    lanedetection_B.HoughTransform_o2[104] = 0.244346097F;
    lanedetection_B.HoughTransform_o2[105] = 0.261799395F;
    lanedetection_B.HoughTransform_o2[106] = 0.279252678F;
    lanedetection_B.HoughTransform_o2[107] = 0.296705961F;
    lanedetection_B.HoughTransform_o2[108] = 0.314159274F;
    lanedetection_B.HoughTransform_o2[109] = 0.331612557F;
    lanedetection_B.HoughTransform_o2[110] = 0.34906584F;
    lanedetection_B.HoughTransform_o2[111] = 0.366519153F;
    lanedetection_B.HoughTransform_o2[112] = 0.383972436F;
    lanedetection_B.HoughTransform_o2[113] = 0.401425719F;
    lanedetection_B.HoughTransform_o2[114] = 0.418879032F;
    lanedetection_B.HoughTransform_o2[115] = 0.436332315F;
    lanedetection_B.HoughTransform_o2[116] = 0.453785598F;
    lanedetection_B.HoughTransform_o2[117] = 0.471238911F;
    lanedetection_B.HoughTransform_o2[118] = 0.488692194F;
    lanedetection_B.HoughTransform_o2[119] = 0.506145477F;
    lanedetection_B.HoughTransform_o2[120] = 0.52359879F;
    lanedetection_B.HoughTransform_o2[121] = 0.541052043F;
    lanedetection_B.HoughTransform_o2[122] = 0.558505356F;
    lanedetection_B.HoughTransform_o2[123] = 0.575958669F;
    lanedetection_B.HoughTransform_o2[124] = 0.593411922F;
    lanedetection_B.HoughTransform_o2[125] = 0.610865235F;
    lanedetection_B.HoughTransform_o2[126] = 0.628318548F;
    lanedetection_B.HoughTransform_o2[127] = 0.645771801F;
    lanedetection_B.HoughTransform_o2[128] = 0.663225114F;
    lanedetection_B.HoughTransform_o2[129] = 0.680678427F;
    lanedetection_B.HoughTransform_o2[130] = 0.69813168F;
    lanedetection_B.HoughTransform_o2[131] = 0.715585F;
    lanedetection_B.HoughTransform_o2[132] = 0.733038306F;
    lanedetection_B.HoughTransform_o2[133] = 0.75049156F;
    lanedetection_B.HoughTransform_o2[134] = 0.767944872F;
    lanedetection_B.HoughTransform_o2[135] = 0.785398185F;
    lanedetection_B.HoughTransform_o2[136] = 0.802851439F;
    lanedetection_B.HoughTransform_o2[137] = 0.820304751F;
    lanedetection_B.HoughTransform_o2[138] = 0.837758064F;
    lanedetection_B.HoughTransform_o2[139] = 0.855211318F;
    lanedetection_B.HoughTransform_o2[140] = 0.87266463F;
    lanedetection_B.HoughTransform_o2[141] = 0.890117943F;
    lanedetection_B.HoughTransform_o2[142] = 0.907571197F;
    lanedetection_B.HoughTransform_o2[143] = 0.925024509F;
    lanedetection_B.HoughTransform_o2[144] = 0.942477822F;
    lanedetection_B.HoughTransform_o2[145] = 0.959931076F;
    lanedetection_B.HoughTransform_o2[146] = 0.977384388F;
    lanedetection_B.HoughTransform_o2[147] = 0.994837701F;
    lanedetection_B.HoughTransform_o2[148] = 1.01229095F;
    lanedetection_B.HoughTransform_o2[149] = 1.02974427F;
    lanedetection_B.HoughTransform_o2[150] = 1.04719758F;
    lanedetection_B.HoughTransform_o2[151] = 1.06465089F;
    lanedetection_B.HoughTransform_o2[152] = 1.08210409F;
    lanedetection_B.HoughTransform_o2[153] = 1.0995574F;
    lanedetection_B.HoughTransform_o2[154] = 1.11701071F;
    lanedetection_B.HoughTransform_o2[155] = 1.13446403F;
    lanedetection_B.HoughTransform_o2[156] = 1.15191734F;
    lanedetection_B.HoughTransform_o2[157] = 1.16937065F;
    lanedetection_B.HoughTransform_o2[158] = 1.18682384F;
    lanedetection_B.HoughTransform_o2[159] = 1.20427716F;
    lanedetection_B.HoughTransform_o2[160] = 1.22173047F;
    lanedetection_B.HoughTransform_o2[161] = 1.23918378F;
    lanedetection_B.HoughTransform_o2[162] = 1.2566371F;
    lanedetection_B.HoughTransform_o2[163] = 1.27409041F;
    lanedetection_B.HoughTransform_o2[164] = 1.2915436F;
    lanedetection_B.HoughTransform_o2[165] = 1.30899692F;
    lanedetection_B.HoughTransform_o2[166] = 1.32645023F;
    lanedetection_B.HoughTransform_o2[167] = 1.34390354F;
    lanedetection_B.HoughTransform_o2[168] = 1.36135685F;
    lanedetection_B.HoughTransform_o2[169] = 1.37881017F;
    lanedetection_B.HoughTransform_o2[170] = 1.39626336F;
    lanedetection_B.HoughTransform_o2[171] = 1.41371667F;
    lanedetection_B.HoughTransform_o2[172] = 1.43117F;
    lanedetection_B.HoughTransform_o2[173] = 1.4486233F;
    lanedetection_B.HoughTransform_o2[174] = 1.46607661F;
    lanedetection_B.HoughTransform_o2[175] = 1.48352981F;
    lanedetection_B.HoughTransform_o2[176] = 1.50098312F;
    lanedetection_B.HoughTransform_o2[177] = 1.51843643F;
    lanedetection_B.HoughTransform_o2[178] = 1.53588974F;
    lanedetection_B.HoughTransform_o2[179] = 1.55334306F;
    lanedetection_B.HoughTransform_o3[0] = -335.0F;
    lanedetection_B.HoughTransform_o3[1] = -334.0F;
    lanedetection_B.HoughTransform_o3[2] = -333.0F;
    lanedetection_B.HoughTransform_o3[3] = -332.0F;
    lanedetection_B.HoughTransform_o3[4] = -331.0F;
    lanedetection_B.HoughTransform_o3[5] = -330.0F;
    lanedetection_B.HoughTransform_o3[6] = -329.0F;
    lanedetection_B.HoughTransform_o3[7] = -328.0F;
    lanedetection_B.HoughTransform_o3[8] = -327.0F;
    lanedetection_B.HoughTransform_o3[9] = -326.0F;
    lanedetection_B.HoughTransform_o3[10] = -325.0F;
    lanedetection_B.HoughTransform_o3[11] = -324.0F;
    lanedetection_B.HoughTransform_o3[12] = -323.0F;
    lanedetection_B.HoughTransform_o3[13] = -322.0F;
    lanedetection_B.HoughTransform_o3[14] = -321.0F;
    lanedetection_B.HoughTransform_o3[15] = -320.0F;
    lanedetection_B.HoughTransform_o3[16] = -319.0F;
    lanedetection_B.HoughTransform_o3[17] = -318.0F;
    lanedetection_B.HoughTransform_o3[18] = -317.0F;
    lanedetection_B.HoughTransform_o3[19] = -316.0F;
    lanedetection_B.HoughTransform_o3[20] = -315.0F;
    lanedetection_B.HoughTransform_o3[21] = -314.0F;
    lanedetection_B.HoughTransform_o3[22] = -313.0F;
    lanedetection_B.HoughTransform_o3[23] = -312.0F;
    lanedetection_B.HoughTransform_o3[24] = -311.0F;
    lanedetection_B.HoughTransform_o3[25] = -310.0F;
    lanedetection_B.HoughTransform_o3[26] = -309.0F;
    lanedetection_B.HoughTransform_o3[27] = -308.0F;
    lanedetection_B.HoughTransform_o3[28] = -307.0F;
    lanedetection_B.HoughTransform_o3[29] = -306.0F;
    lanedetection_B.HoughTransform_o3[30] = -305.0F;
    lanedetection_B.HoughTransform_o3[31] = -304.0F;
    lanedetection_B.HoughTransform_o3[32] = -303.0F;
    lanedetection_B.HoughTransform_o3[33] = -302.0F;
    lanedetection_B.HoughTransform_o3[34] = -301.0F;
    lanedetection_B.HoughTransform_o3[35] = -300.0F;
    lanedetection_B.HoughTransform_o3[36] = -299.0F;
    lanedetection_B.HoughTransform_o3[37] = -298.0F;
    lanedetection_B.HoughTransform_o3[38] = -297.0F;
    lanedetection_B.HoughTransform_o3[39] = -296.0F;
    lanedetection_B.HoughTransform_o3[40] = -295.0F;
    lanedetection_B.HoughTransform_o3[41] = -294.0F;
    lanedetection_B.HoughTransform_o3[42] = -293.0F;
    lanedetection_B.HoughTransform_o3[43] = -292.0F;
    lanedetection_B.HoughTransform_o3[44] = -291.0F;
    lanedetection_B.HoughTransform_o3[45] = -290.0F;
    lanedetection_B.HoughTransform_o3[46] = -289.0F;
    lanedetection_B.HoughTransform_o3[47] = -288.0F;
    lanedetection_B.HoughTransform_o3[48] = -287.0F;
    lanedetection_B.HoughTransform_o3[49] = -286.0F;
    lanedetection_B.HoughTransform_o3[50] = -285.0F;
    lanedetection_B.HoughTransform_o3[51] = -284.0F;
    lanedetection_B.HoughTransform_o3[52] = -283.0F;
    lanedetection_B.HoughTransform_o3[53] = -282.0F;
    lanedetection_B.HoughTransform_o3[54] = -281.0F;
    lanedetection_B.HoughTransform_o3[55] = -280.0F;
    lanedetection_B.HoughTransform_o3[56] = -279.0F;
    lanedetection_B.HoughTransform_o3[57] = -278.0F;
    lanedetection_B.HoughTransform_o3[58] = -277.0F;
    lanedetection_B.HoughTransform_o3[59] = -276.0F;
    lanedetection_B.HoughTransform_o3[60] = -275.0F;
    lanedetection_B.HoughTransform_o3[61] = -274.0F;
    lanedetection_B.HoughTransform_o3[62] = -273.0F;
    lanedetection_B.HoughTransform_o3[63] = -272.0F;
    lanedetection_B.HoughTransform_o3[64] = -271.0F;
    lanedetection_B.HoughTransform_o3[65] = -270.0F;
    lanedetection_B.HoughTransform_o3[66] = -269.0F;
    lanedetection_B.HoughTransform_o3[67] = -268.0F;
    lanedetection_B.HoughTransform_o3[68] = -267.0F;
    lanedetection_B.HoughTransform_o3[69] = -266.0F;
    lanedetection_B.HoughTransform_o3[70] = -265.0F;
    lanedetection_B.HoughTransform_o3[71] = -264.0F;
    lanedetection_B.HoughTransform_o3[72] = -263.0F;
    lanedetection_B.HoughTransform_o3[73] = -262.0F;
    lanedetection_B.HoughTransform_o3[74] = -261.0F;
    lanedetection_B.HoughTransform_o3[75] = -260.0F;
    lanedetection_B.HoughTransform_o3[76] = -259.0F;
    lanedetection_B.HoughTransform_o3[77] = -258.0F;
    lanedetection_B.HoughTransform_o3[78] = -257.0F;
    lanedetection_B.HoughTransform_o3[79] = -256.0F;
    lanedetection_B.HoughTransform_o3[80] = -255.0F;
    lanedetection_B.HoughTransform_o3[81] = -254.0F;
    lanedetection_B.HoughTransform_o3[82] = -253.0F;
    lanedetection_B.HoughTransform_o3[83] = -252.0F;
    lanedetection_B.HoughTransform_o3[84] = -251.0F;
    lanedetection_B.HoughTransform_o3[85] = -250.0F;
    lanedetection_B.HoughTransform_o3[86] = -249.0F;
    lanedetection_B.HoughTransform_o3[87] = -248.0F;
    lanedetection_B.HoughTransform_o3[88] = -247.0F;
    lanedetection_B.HoughTransform_o3[89] = -246.0F;
    lanedetection_B.HoughTransform_o3[90] = -245.0F;
    lanedetection_B.HoughTransform_o3[91] = -244.0F;
    lanedetection_B.HoughTransform_o3[92] = -243.0F;
    lanedetection_B.HoughTransform_o3[93] = -242.0F;
    lanedetection_B.HoughTransform_o3[94] = -241.0F;
    lanedetection_B.HoughTransform_o3[95] = -240.0F;
    lanedetection_B.HoughTransform_o3[96] = -239.0F;
    lanedetection_B.HoughTransform_o3[97] = -238.0F;
    lanedetection_B.HoughTransform_o3[98] = -237.0F;
    lanedetection_B.HoughTransform_o3[99] = -236.0F;
    lanedetection_B.HoughTransform_o3[100] = -235.0F;
    lanedetection_B.HoughTransform_o3[101] = -234.0F;
    lanedetection_B.HoughTransform_o3[102] = -233.0F;
    lanedetection_B.HoughTransform_o3[103] = -232.0F;
    lanedetection_B.HoughTransform_o3[104] = -231.0F;
    lanedetection_B.HoughTransform_o3[105] = -230.0F;
    lanedetection_B.HoughTransform_o3[106] = -229.0F;
    lanedetection_B.HoughTransform_o3[107] = -228.0F;
    lanedetection_B.HoughTransform_o3[108] = -227.0F;
    lanedetection_B.HoughTransform_o3[109] = -226.0F;
    lanedetection_B.HoughTransform_o3[110] = -225.0F;
    lanedetection_B.HoughTransform_o3[111] = -224.0F;
    lanedetection_B.HoughTransform_o3[112] = -223.0F;
    lanedetection_B.HoughTransform_o3[113] = -222.0F;
    lanedetection_B.HoughTransform_o3[114] = -221.0F;
    lanedetection_B.HoughTransform_o3[115] = -220.0F;
    lanedetection_B.HoughTransform_o3[116] = -219.0F;
    lanedetection_B.HoughTransform_o3[117] = -218.0F;
    lanedetection_B.HoughTransform_o3[118] = -217.0F;
    lanedetection_B.HoughTransform_o3[119] = -216.0F;
    lanedetection_B.HoughTransform_o3[120] = -215.0F;
    lanedetection_B.HoughTransform_o3[121] = -214.0F;
    lanedetection_B.HoughTransform_o3[122] = -213.0F;
    lanedetection_B.HoughTransform_o3[123] = -212.0F;
    lanedetection_B.HoughTransform_o3[124] = -211.0F;
    lanedetection_B.HoughTransform_o3[125] = -210.0F;
    lanedetection_B.HoughTransform_o3[126] = -209.0F;
    lanedetection_B.HoughTransform_o3[127] = -208.0F;
    lanedetection_B.HoughTransform_o3[128] = -207.0F;
    lanedetection_B.HoughTransform_o3[129] = -206.0F;
    lanedetection_B.HoughTransform_o3[130] = -205.0F;
    lanedetection_B.HoughTransform_o3[131] = -204.0F;
    lanedetection_B.HoughTransform_o3[132] = -203.0F;
    lanedetection_B.HoughTransform_o3[133] = -202.0F;
    lanedetection_B.HoughTransform_o3[134] = -201.0F;
    lanedetection_B.HoughTransform_o3[135] = -200.0F;
    lanedetection_B.HoughTransform_o3[136] = -199.0F;
    lanedetection_B.HoughTransform_o3[137] = -198.0F;
    lanedetection_B.HoughTransform_o3[138] = -197.0F;
    lanedetection_B.HoughTransform_o3[139] = -196.0F;
    lanedetection_B.HoughTransform_o3[140] = -195.0F;
    lanedetection_B.HoughTransform_o3[141] = -194.0F;
    lanedetection_B.HoughTransform_o3[142] = -193.0F;
    lanedetection_B.HoughTransform_o3[143] = -192.0F;
    lanedetection_B.HoughTransform_o3[144] = -191.0F;
    lanedetection_B.HoughTransform_o3[145] = -190.0F;
    lanedetection_B.HoughTransform_o3[146] = -189.0F;
    lanedetection_B.HoughTransform_o3[147] = -188.0F;
    lanedetection_B.HoughTransform_o3[148] = -187.0F;
    lanedetection_B.HoughTransform_o3[149] = -186.0F;
    lanedetection_B.HoughTransform_o3[150] = -185.0F;
    lanedetection_B.HoughTransform_o3[151] = -184.0F;
    lanedetection_B.HoughTransform_o3[152] = -183.0F;
    lanedetection_B.HoughTransform_o3[153] = -182.0F;
    lanedetection_B.HoughTransform_o3[154] = -181.0F;
    lanedetection_B.HoughTransform_o3[155] = -180.0F;
    lanedetection_B.HoughTransform_o3[156] = -179.0F;
    lanedetection_B.HoughTransform_o3[157] = -178.0F;
    lanedetection_B.HoughTransform_o3[158] = -177.0F;
    lanedetection_B.HoughTransform_o3[159] = -176.0F;
    lanedetection_B.HoughTransform_o3[160] = -175.0F;
    lanedetection_B.HoughTransform_o3[161] = -174.0F;
    lanedetection_B.HoughTransform_o3[162] = -173.0F;
    lanedetection_B.HoughTransform_o3[163] = -172.0F;
    lanedetection_B.HoughTransform_o3[164] = -171.0F;
    lanedetection_B.HoughTransform_o3[165] = -170.0F;
    lanedetection_B.HoughTransform_o3[166] = -169.0F;
    lanedetection_B.HoughTransform_o3[167] = -168.0F;
    lanedetection_B.HoughTransform_o3[168] = -167.0F;
    lanedetection_B.HoughTransform_o3[169] = -166.0F;
    lanedetection_B.HoughTransform_o3[170] = -165.0F;
    lanedetection_B.HoughTransform_o3[171] = -164.0F;
    lanedetection_B.HoughTransform_o3[172] = -163.0F;
    lanedetection_B.HoughTransform_o3[173] = -162.0F;
    lanedetection_B.HoughTransform_o3[174] = -161.0F;
    lanedetection_B.HoughTransform_o3[175] = -160.0F;
    lanedetection_B.HoughTransform_o3[176] = -159.0F;
    lanedetection_B.HoughTransform_o3[177] = -158.0F;
    lanedetection_B.HoughTransform_o3[178] = -157.0F;
    lanedetection_B.HoughTransform_o3[179] = -156.0F;
    lanedetection_B.HoughTransform_o3[180] = -155.0F;
    lanedetection_B.HoughTransform_o3[181] = -154.0F;
    lanedetection_B.HoughTransform_o3[182] = -153.0F;
    lanedetection_B.HoughTransform_o3[183] = -152.0F;
    lanedetection_B.HoughTransform_o3[184] = -151.0F;
    lanedetection_B.HoughTransform_o3[185] = -150.0F;
    lanedetection_B.HoughTransform_o3[186] = -149.0F;
    lanedetection_B.HoughTransform_o3[187] = -148.0F;
    lanedetection_B.HoughTransform_o3[188] = -147.0F;
    lanedetection_B.HoughTransform_o3[189] = -146.0F;
    lanedetection_B.HoughTransform_o3[190] = -145.0F;
    lanedetection_B.HoughTransform_o3[191] = -144.0F;
    lanedetection_B.HoughTransform_o3[192] = -143.0F;
    lanedetection_B.HoughTransform_o3[193] = -142.0F;
    lanedetection_B.HoughTransform_o3[194] = -141.0F;
    lanedetection_B.HoughTransform_o3[195] = -140.0F;
    lanedetection_B.HoughTransform_o3[196] = -139.0F;
    lanedetection_B.HoughTransform_o3[197] = -138.0F;
    lanedetection_B.HoughTransform_o3[198] = -137.0F;
    lanedetection_B.HoughTransform_o3[199] = -136.0F;
    lanedetection_B.HoughTransform_o3[200] = -135.0F;
    lanedetection_B.HoughTransform_o3[201] = -134.0F;
    lanedetection_B.HoughTransform_o3[202] = -133.0F;
    lanedetection_B.HoughTransform_o3[203] = -132.0F;
    lanedetection_B.HoughTransform_o3[204] = -131.0F;
    lanedetection_B.HoughTransform_o3[205] = -130.0F;
    lanedetection_B.HoughTransform_o3[206] = -129.0F;
    lanedetection_B.HoughTransform_o3[207] = -128.0F;
    lanedetection_B.HoughTransform_o3[208] = -127.0F;
    lanedetection_B.HoughTransform_o3[209] = -126.0F;
    lanedetection_B.HoughTransform_o3[210] = -125.0F;
    lanedetection_B.HoughTransform_o3[211] = -124.0F;
    lanedetection_B.HoughTransform_o3[212] = -123.0F;
    lanedetection_B.HoughTransform_o3[213] = -122.0F;
    lanedetection_B.HoughTransform_o3[214] = -121.0F;
    lanedetection_B.HoughTransform_o3[215] = -120.0F;
    lanedetection_B.HoughTransform_o3[216] = -119.0F;
    lanedetection_B.HoughTransform_o3[217] = -118.0F;
    lanedetection_B.HoughTransform_o3[218] = -117.0F;
    lanedetection_B.HoughTransform_o3[219] = -116.0F;
    lanedetection_B.HoughTransform_o3[220] = -115.0F;
    lanedetection_B.HoughTransform_o3[221] = -114.0F;
    lanedetection_B.HoughTransform_o3[222] = -113.0F;
    lanedetection_B.HoughTransform_o3[223] = -112.0F;
    lanedetection_B.HoughTransform_o3[224] = -111.0F;
    lanedetection_B.HoughTransform_o3[225] = -110.0F;
    lanedetection_B.HoughTransform_o3[226] = -109.0F;
    lanedetection_B.HoughTransform_o3[227] = -108.0F;
    lanedetection_B.HoughTransform_o3[228] = -107.0F;
    lanedetection_B.HoughTransform_o3[229] = -106.0F;
    lanedetection_B.HoughTransform_o3[230] = -105.0F;
    lanedetection_B.HoughTransform_o3[231] = -104.0F;
    lanedetection_B.HoughTransform_o3[232] = -103.0F;
    lanedetection_B.HoughTransform_o3[233] = -102.0F;
    lanedetection_B.HoughTransform_o3[234] = -101.0F;
    lanedetection_B.HoughTransform_o3[235] = -100.0F;
    lanedetection_B.HoughTransform_o3[236] = -99.0F;
    lanedetection_B.HoughTransform_o3[237] = -98.0F;
    lanedetection_B.HoughTransform_o3[238] = -97.0F;
    lanedetection_B.HoughTransform_o3[239] = -96.0F;
    lanedetection_B.HoughTransform_o3[240] = -95.0F;
    lanedetection_B.HoughTransform_o3[241] = -94.0F;
    lanedetection_B.HoughTransform_o3[242] = -93.0F;
    lanedetection_B.HoughTransform_o3[243] = -92.0F;
    lanedetection_B.HoughTransform_o3[244] = -91.0F;
    lanedetection_B.HoughTransform_o3[245] = -90.0F;
    lanedetection_B.HoughTransform_o3[246] = -89.0F;
    lanedetection_B.HoughTransform_o3[247] = -88.0F;
    lanedetection_B.HoughTransform_o3[248] = -87.0F;
    lanedetection_B.HoughTransform_o3[249] = -86.0F;
    lanedetection_B.HoughTransform_o3[250] = -85.0F;
    lanedetection_B.HoughTransform_o3[251] = -84.0F;
    lanedetection_B.HoughTransform_o3[252] = -83.0F;
    lanedetection_B.HoughTransform_o3[253] = -82.0F;
    lanedetection_B.HoughTransform_o3[254] = -81.0F;
    lanedetection_B.HoughTransform_o3[255] = -80.0F;
    lanedetection_B.HoughTransform_o3[256] = -79.0F;
    lanedetection_B.HoughTransform_o3[257] = -78.0F;
    lanedetection_B.HoughTransform_o3[258] = -77.0F;
    lanedetection_B.HoughTransform_o3[259] = -76.0F;
    lanedetection_B.HoughTransform_o3[260] = -75.0F;
    lanedetection_B.HoughTransform_o3[261] = -74.0F;
    lanedetection_B.HoughTransform_o3[262] = -73.0F;
    lanedetection_B.HoughTransform_o3[263] = -72.0F;
    lanedetection_B.HoughTransform_o3[264] = -71.0F;
    lanedetection_B.HoughTransform_o3[265] = -70.0F;
    lanedetection_B.HoughTransform_o3[266] = -69.0F;
    lanedetection_B.HoughTransform_o3[267] = -68.0F;
    lanedetection_B.HoughTransform_o3[268] = -67.0F;
    lanedetection_B.HoughTransform_o3[269] = -66.0F;
    lanedetection_B.HoughTransform_o3[270] = -65.0F;
    lanedetection_B.HoughTransform_o3[271] = -64.0F;
    lanedetection_B.HoughTransform_o3[272] = -63.0F;
    lanedetection_B.HoughTransform_o3[273] = -62.0F;
    lanedetection_B.HoughTransform_o3[274] = -61.0F;
    lanedetection_B.HoughTransform_o3[275] = -60.0F;
    lanedetection_B.HoughTransform_o3[276] = -59.0F;
    lanedetection_B.HoughTransform_o3[277] = -58.0F;
    lanedetection_B.HoughTransform_o3[278] = -57.0F;
    lanedetection_B.HoughTransform_o3[279] = -56.0F;
    lanedetection_B.HoughTransform_o3[280] = -55.0F;
    lanedetection_B.HoughTransform_o3[281] = -54.0F;
    lanedetection_B.HoughTransform_o3[282] = -53.0F;
    lanedetection_B.HoughTransform_o3[283] = -52.0F;
    lanedetection_B.HoughTransform_o3[284] = -51.0F;
    lanedetection_B.HoughTransform_o3[285] = -50.0F;
    lanedetection_B.HoughTransform_o3[286] = -49.0F;
    lanedetection_B.HoughTransform_o3[287] = -48.0F;
    lanedetection_B.HoughTransform_o3[288] = -47.0F;
    lanedetection_B.HoughTransform_o3[289] = -46.0F;
    lanedetection_B.HoughTransform_o3[290] = -45.0F;
    lanedetection_B.HoughTransform_o3[291] = -44.0F;
    lanedetection_B.HoughTransform_o3[292] = -43.0F;
    lanedetection_B.HoughTransform_o3[293] = -42.0F;
    lanedetection_B.HoughTransform_o3[294] = -41.0F;
    lanedetection_B.HoughTransform_o3[295] = -40.0F;
    lanedetection_B.HoughTransform_o3[296] = -39.0F;
    lanedetection_B.HoughTransform_o3[297] = -38.0F;
    lanedetection_B.HoughTransform_o3[298] = -37.0F;
    lanedetection_B.HoughTransform_o3[299] = -36.0F;
    lanedetection_B.HoughTransform_o3[300] = -35.0F;
    lanedetection_B.HoughTransform_o3[301] = -34.0F;
    lanedetection_B.HoughTransform_o3[302] = -33.0F;
    lanedetection_B.HoughTransform_o3[303] = -32.0F;
    lanedetection_B.HoughTransform_o3[304] = -31.0F;
    lanedetection_B.HoughTransform_o3[305] = -30.0F;
    lanedetection_B.HoughTransform_o3[306] = -29.0F;
    lanedetection_B.HoughTransform_o3[307] = -28.0F;
    lanedetection_B.HoughTransform_o3[308] = -27.0F;
    lanedetection_B.HoughTransform_o3[309] = -26.0F;
    lanedetection_B.HoughTransform_o3[310] = -25.0F;
    lanedetection_B.HoughTransform_o3[311] = -24.0F;
    lanedetection_B.HoughTransform_o3[312] = -23.0F;
    lanedetection_B.HoughTransform_o3[313] = -22.0F;
    lanedetection_B.HoughTransform_o3[314] = -21.0F;
    lanedetection_B.HoughTransform_o3[315] = -20.0F;
    lanedetection_B.HoughTransform_o3[316] = -19.0F;
    lanedetection_B.HoughTransform_o3[317] = -18.0F;
    lanedetection_B.HoughTransform_o3[318] = -17.0F;
    lanedetection_B.HoughTransform_o3[319] = -16.0F;
    lanedetection_B.HoughTransform_o3[320] = -15.0F;
    lanedetection_B.HoughTransform_o3[321] = -14.0F;
    lanedetection_B.HoughTransform_o3[322] = -13.0F;
    lanedetection_B.HoughTransform_o3[323] = -12.0F;
    lanedetection_B.HoughTransform_o3[324] = -11.0F;
    lanedetection_B.HoughTransform_o3[325] = -10.0F;
    lanedetection_B.HoughTransform_o3[326] = -9.0F;
    lanedetection_B.HoughTransform_o3[327] = -8.0F;
    lanedetection_B.HoughTransform_o3[328] = -7.0F;
    lanedetection_B.HoughTransform_o3[329] = -6.0F;
    lanedetection_B.HoughTransform_o3[330] = -5.0F;
    lanedetection_B.HoughTransform_o3[331] = -4.0F;
    lanedetection_B.HoughTransform_o3[332] = -3.0F;
    lanedetection_B.HoughTransform_o3[333] = -2.0F;
    lanedetection_B.HoughTransform_o3[334] = -1.0F;
    lanedetection_B.HoughTransform_o3[335] = 0.0F;
    lanedetection_B.HoughTransform_o3[336] = 1.0F;
    lanedetection_B.HoughTransform_o3[337] = 2.0F;
    lanedetection_B.HoughTransform_o3[338] = 3.0F;
    lanedetection_B.HoughTransform_o3[339] = 4.0F;
    lanedetection_B.HoughTransform_o3[340] = 5.0F;
    lanedetection_B.HoughTransform_o3[341] = 6.0F;
    lanedetection_B.HoughTransform_o3[342] = 7.0F;
    lanedetection_B.HoughTransform_o3[343] = 8.0F;
    lanedetection_B.HoughTransform_o3[344] = 9.0F;
    lanedetection_B.HoughTransform_o3[345] = 10.0F;
    lanedetection_B.HoughTransform_o3[346] = 11.0F;
    lanedetection_B.HoughTransform_o3[347] = 12.0F;
    lanedetection_B.HoughTransform_o3[348] = 13.0F;
    lanedetection_B.HoughTransform_o3[349] = 14.0F;
    lanedetection_B.HoughTransform_o3[350] = 15.0F;
    lanedetection_B.HoughTransform_o3[351] = 16.0F;
    lanedetection_B.HoughTransform_o3[352] = 17.0F;
    lanedetection_B.HoughTransform_o3[353] = 18.0F;
    lanedetection_B.HoughTransform_o3[354] = 19.0F;
    lanedetection_B.HoughTransform_o3[355] = 20.0F;
    lanedetection_B.HoughTransform_o3[356] = 21.0F;
    lanedetection_B.HoughTransform_o3[357] = 22.0F;
    lanedetection_B.HoughTransform_o3[358] = 23.0F;
    lanedetection_B.HoughTransform_o3[359] = 24.0F;
    lanedetection_B.HoughTransform_o3[360] = 25.0F;
    lanedetection_B.HoughTransform_o3[361] = 26.0F;
    lanedetection_B.HoughTransform_o3[362] = 27.0F;
    lanedetection_B.HoughTransform_o3[363] = 28.0F;
    lanedetection_B.HoughTransform_o3[364] = 29.0F;
    lanedetection_B.HoughTransform_o3[365] = 30.0F;
    lanedetection_B.HoughTransform_o3[366] = 31.0F;
    lanedetection_B.HoughTransform_o3[367] = 32.0F;
    lanedetection_B.HoughTransform_o3[368] = 33.0F;
    lanedetection_B.HoughTransform_o3[369] = 34.0F;
    lanedetection_B.HoughTransform_o3[370] = 35.0F;
    lanedetection_B.HoughTransform_o3[371] = 36.0F;
    lanedetection_B.HoughTransform_o3[372] = 37.0F;
    lanedetection_B.HoughTransform_o3[373] = 38.0F;
    lanedetection_B.HoughTransform_o3[374] = 39.0F;
    lanedetection_B.HoughTransform_o3[375] = 40.0F;
    lanedetection_B.HoughTransform_o3[376] = 41.0F;
    lanedetection_B.HoughTransform_o3[377] = 42.0F;
    lanedetection_B.HoughTransform_o3[378] = 43.0F;
    lanedetection_B.HoughTransform_o3[379] = 44.0F;
    lanedetection_B.HoughTransform_o3[380] = 45.0F;
    lanedetection_B.HoughTransform_o3[381] = 46.0F;
    lanedetection_B.HoughTransform_o3[382] = 47.0F;
    lanedetection_B.HoughTransform_o3[383] = 48.0F;
    lanedetection_B.HoughTransform_o3[384] = 49.0F;
    lanedetection_B.HoughTransform_o3[385] = 50.0F;
    lanedetection_B.HoughTransform_o3[386] = 51.0F;
    lanedetection_B.HoughTransform_o3[387] = 52.0F;
    lanedetection_B.HoughTransform_o3[388] = 53.0F;
    lanedetection_B.HoughTransform_o3[389] = 54.0F;
    lanedetection_B.HoughTransform_o3[390] = 55.0F;
    lanedetection_B.HoughTransform_o3[391] = 56.0F;
    lanedetection_B.HoughTransform_o3[392] = 57.0F;
    lanedetection_B.HoughTransform_o3[393] = 58.0F;
    lanedetection_B.HoughTransform_o3[394] = 59.0F;
    lanedetection_B.HoughTransform_o3[395] = 60.0F;
    lanedetection_B.HoughTransform_o3[396] = 61.0F;
    lanedetection_B.HoughTransform_o3[397] = 62.0F;
    lanedetection_B.HoughTransform_o3[398] = 63.0F;
    lanedetection_B.HoughTransform_o3[399] = 64.0F;
    lanedetection_B.HoughTransform_o3[400] = 65.0F;
    lanedetection_B.HoughTransform_o3[401] = 66.0F;
    lanedetection_B.HoughTransform_o3[402] = 67.0F;
    lanedetection_B.HoughTransform_o3[403] = 68.0F;
    lanedetection_B.HoughTransform_o3[404] = 69.0F;
    lanedetection_B.HoughTransform_o3[405] = 70.0F;
    lanedetection_B.HoughTransform_o3[406] = 71.0F;
    lanedetection_B.HoughTransform_o3[407] = 72.0F;
    lanedetection_B.HoughTransform_o3[408] = 73.0F;
    lanedetection_B.HoughTransform_o3[409] = 74.0F;
    lanedetection_B.HoughTransform_o3[410] = 75.0F;
    lanedetection_B.HoughTransform_o3[411] = 76.0F;
    lanedetection_B.HoughTransform_o3[412] = 77.0F;
    lanedetection_B.HoughTransform_o3[413] = 78.0F;
    lanedetection_B.HoughTransform_o3[414] = 79.0F;
    lanedetection_B.HoughTransform_o3[415] = 80.0F;
    lanedetection_B.HoughTransform_o3[416] = 81.0F;
    lanedetection_B.HoughTransform_o3[417] = 82.0F;
    lanedetection_B.HoughTransform_o3[418] = 83.0F;
    lanedetection_B.HoughTransform_o3[419] = 84.0F;
    lanedetection_B.HoughTransform_o3[420] = 85.0F;
    lanedetection_B.HoughTransform_o3[421] = 86.0F;
    lanedetection_B.HoughTransform_o3[422] = 87.0F;
    lanedetection_B.HoughTransform_o3[423] = 88.0F;
    lanedetection_B.HoughTransform_o3[424] = 89.0F;
    lanedetection_B.HoughTransform_o3[425] = 90.0F;
    lanedetection_B.HoughTransform_o3[426] = 91.0F;
    lanedetection_B.HoughTransform_o3[427] = 92.0F;
    lanedetection_B.HoughTransform_o3[428] = 93.0F;
    lanedetection_B.HoughTransform_o3[429] = 94.0F;
    lanedetection_B.HoughTransform_o3[430] = 95.0F;
    lanedetection_B.HoughTransform_o3[431] = 96.0F;
    lanedetection_B.HoughTransform_o3[432] = 97.0F;
    lanedetection_B.HoughTransform_o3[433] = 98.0F;
    lanedetection_B.HoughTransform_o3[434] = 99.0F;
    lanedetection_B.HoughTransform_o3[435] = 100.0F;
    lanedetection_B.HoughTransform_o3[436] = 101.0F;
    lanedetection_B.HoughTransform_o3[437] = 102.0F;
    lanedetection_B.HoughTransform_o3[438] = 103.0F;
    lanedetection_B.HoughTransform_o3[439] = 104.0F;
    lanedetection_B.HoughTransform_o3[440] = 105.0F;
    lanedetection_B.HoughTransform_o3[441] = 106.0F;
    lanedetection_B.HoughTransform_o3[442] = 107.0F;
    lanedetection_B.HoughTransform_o3[443] = 108.0F;
    lanedetection_B.HoughTransform_o3[444] = 109.0F;
    lanedetection_B.HoughTransform_o3[445] = 110.0F;
    lanedetection_B.HoughTransform_o3[446] = 111.0F;
    lanedetection_B.HoughTransform_o3[447] = 112.0F;
    lanedetection_B.HoughTransform_o3[448] = 113.0F;
    lanedetection_B.HoughTransform_o3[449] = 114.0F;
    lanedetection_B.HoughTransform_o3[450] = 115.0F;
    lanedetection_B.HoughTransform_o3[451] = 116.0F;
    lanedetection_B.HoughTransform_o3[452] = 117.0F;
    lanedetection_B.HoughTransform_o3[453] = 118.0F;
    lanedetection_B.HoughTransform_o3[454] = 119.0F;
    lanedetection_B.HoughTransform_o3[455] = 120.0F;
    lanedetection_B.HoughTransform_o3[456] = 121.0F;
    lanedetection_B.HoughTransform_o3[457] = 122.0F;
    lanedetection_B.HoughTransform_o3[458] = 123.0F;
    lanedetection_B.HoughTransform_o3[459] = 124.0F;
    lanedetection_B.HoughTransform_o3[460] = 125.0F;
    lanedetection_B.HoughTransform_o3[461] = 126.0F;
    lanedetection_B.HoughTransform_o3[462] = 127.0F;
    lanedetection_B.HoughTransform_o3[463] = 128.0F;
    lanedetection_B.HoughTransform_o3[464] = 129.0F;
    lanedetection_B.HoughTransform_o3[465] = 130.0F;
    lanedetection_B.HoughTransform_o3[466] = 131.0F;
    lanedetection_B.HoughTransform_o3[467] = 132.0F;
    lanedetection_B.HoughTransform_o3[468] = 133.0F;
    lanedetection_B.HoughTransform_o3[469] = 134.0F;
    lanedetection_B.HoughTransform_o3[470] = 135.0F;
    lanedetection_B.HoughTransform_o3[471] = 136.0F;
    lanedetection_B.HoughTransform_o3[472] = 137.0F;
    lanedetection_B.HoughTransform_o3[473] = 138.0F;
    lanedetection_B.HoughTransform_o3[474] = 139.0F;
    lanedetection_B.HoughTransform_o3[475] = 140.0F;
    lanedetection_B.HoughTransform_o3[476] = 141.0F;
    lanedetection_B.HoughTransform_o3[477] = 142.0F;
    lanedetection_B.HoughTransform_o3[478] = 143.0F;
    lanedetection_B.HoughTransform_o3[479] = 144.0F;
    lanedetection_B.HoughTransform_o3[480] = 145.0F;
    lanedetection_B.HoughTransform_o3[481] = 146.0F;
    lanedetection_B.HoughTransform_o3[482] = 147.0F;
    lanedetection_B.HoughTransform_o3[483] = 148.0F;
    lanedetection_B.HoughTransform_o3[484] = 149.0F;
    lanedetection_B.HoughTransform_o3[485] = 150.0F;
    lanedetection_B.HoughTransform_o3[486] = 151.0F;
    lanedetection_B.HoughTransform_o3[487] = 152.0F;
    lanedetection_B.HoughTransform_o3[488] = 153.0F;
    lanedetection_B.HoughTransform_o3[489] = 154.0F;
    lanedetection_B.HoughTransform_o3[490] = 155.0F;
    lanedetection_B.HoughTransform_o3[491] = 156.0F;
    lanedetection_B.HoughTransform_o3[492] = 157.0F;
    lanedetection_B.HoughTransform_o3[493] = 158.0F;
    lanedetection_B.HoughTransform_o3[494] = 159.0F;
    lanedetection_B.HoughTransform_o3[495] = 160.0F;
    lanedetection_B.HoughTransform_o3[496] = 161.0F;
    lanedetection_B.HoughTransform_o3[497] = 162.0F;
    lanedetection_B.HoughTransform_o3[498] = 163.0F;
    lanedetection_B.HoughTransform_o3[499] = 164.0F;
    lanedetection_B.HoughTransform_o3[500] = 165.0F;
    lanedetection_B.HoughTransform_o3[501] = 166.0F;
    lanedetection_B.HoughTransform_o3[502] = 167.0F;
    lanedetection_B.HoughTransform_o3[503] = 168.0F;
    lanedetection_B.HoughTransform_o3[504] = 169.0F;
    lanedetection_B.HoughTransform_o3[505] = 170.0F;
    lanedetection_B.HoughTransform_o3[506] = 171.0F;
    lanedetection_B.HoughTransform_o3[507] = 172.0F;
    lanedetection_B.HoughTransform_o3[508] = 173.0F;
    lanedetection_B.HoughTransform_o3[509] = 174.0F;
    lanedetection_B.HoughTransform_o3[510] = 175.0F;
    lanedetection_B.HoughTransform_o3[511] = 176.0F;
    lanedetection_B.HoughTransform_o3[512] = 177.0F;
    lanedetection_B.HoughTransform_o3[513] = 178.0F;
    lanedetection_B.HoughTransform_o3[514] = 179.0F;
    lanedetection_B.HoughTransform_o3[515] = 180.0F;
    lanedetection_B.HoughTransform_o3[516] = 181.0F;
    lanedetection_B.HoughTransform_o3[517] = 182.0F;
    lanedetection_B.HoughTransform_o3[518] = 183.0F;
    lanedetection_B.HoughTransform_o3[519] = 184.0F;
    lanedetection_B.HoughTransform_o3[520] = 185.0F;
    lanedetection_B.HoughTransform_o3[521] = 186.0F;
    lanedetection_B.HoughTransform_o3[522] = 187.0F;
    lanedetection_B.HoughTransform_o3[523] = 188.0F;
    lanedetection_B.HoughTransform_o3[524] = 189.0F;
    lanedetection_B.HoughTransform_o3[525] = 190.0F;
    lanedetection_B.HoughTransform_o3[526] = 191.0F;
    lanedetection_B.HoughTransform_o3[527] = 192.0F;
    lanedetection_B.HoughTransform_o3[528] = 193.0F;
    lanedetection_B.HoughTransform_o3[529] = 194.0F;
    lanedetection_B.HoughTransform_o3[530] = 195.0F;
    lanedetection_B.HoughTransform_o3[531] = 196.0F;
    lanedetection_B.HoughTransform_o3[532] = 197.0F;
    lanedetection_B.HoughTransform_o3[533] = 198.0F;
    lanedetection_B.HoughTransform_o3[534] = 199.0F;
    lanedetection_B.HoughTransform_o3[535] = 200.0F;
    lanedetection_B.HoughTransform_o3[536] = 201.0F;
    lanedetection_B.HoughTransform_o3[537] = 202.0F;
    lanedetection_B.HoughTransform_o3[538] = 203.0F;
    lanedetection_B.HoughTransform_o3[539] = 204.0F;
    lanedetection_B.HoughTransform_o3[540] = 205.0F;
    lanedetection_B.HoughTransform_o3[541] = 206.0F;
    lanedetection_B.HoughTransform_o3[542] = 207.0F;
    lanedetection_B.HoughTransform_o3[543] = 208.0F;
    lanedetection_B.HoughTransform_o3[544] = 209.0F;
    lanedetection_B.HoughTransform_o3[545] = 210.0F;
    lanedetection_B.HoughTransform_o3[546] = 211.0F;
    lanedetection_B.HoughTransform_o3[547] = 212.0F;
    lanedetection_B.HoughTransform_o3[548] = 213.0F;
    lanedetection_B.HoughTransform_o3[549] = 214.0F;
    lanedetection_B.HoughTransform_o3[550] = 215.0F;
    lanedetection_B.HoughTransform_o3[551] = 216.0F;
    lanedetection_B.HoughTransform_o3[552] = 217.0F;
    lanedetection_B.HoughTransform_o3[553] = 218.0F;
    lanedetection_B.HoughTransform_o3[554] = 219.0F;
    lanedetection_B.HoughTransform_o3[555] = 220.0F;
    lanedetection_B.HoughTransform_o3[556] = 221.0F;
    lanedetection_B.HoughTransform_o3[557] = 222.0F;
    lanedetection_B.HoughTransform_o3[558] = 223.0F;
    lanedetection_B.HoughTransform_o3[559] = 224.0F;
    lanedetection_B.HoughTransform_o3[560] = 225.0F;
    lanedetection_B.HoughTransform_o3[561] = 226.0F;
    lanedetection_B.HoughTransform_o3[562] = 227.0F;
    lanedetection_B.HoughTransform_o3[563] = 228.0F;
    lanedetection_B.HoughTransform_o3[564] = 229.0F;
    lanedetection_B.HoughTransform_o3[565] = 230.0F;
    lanedetection_B.HoughTransform_o3[566] = 231.0F;
    lanedetection_B.HoughTransform_o3[567] = 232.0F;
    lanedetection_B.HoughTransform_o3[568] = 233.0F;
    lanedetection_B.HoughTransform_o3[569] = 234.0F;
    lanedetection_B.HoughTransform_o3[570] = 235.0F;
    lanedetection_B.HoughTransform_o3[571] = 236.0F;
    lanedetection_B.HoughTransform_o3[572] = 237.0F;
    lanedetection_B.HoughTransform_o3[573] = 238.0F;
    lanedetection_B.HoughTransform_o3[574] = 239.0F;
    lanedetection_B.HoughTransform_o3[575] = 240.0F;
    lanedetection_B.HoughTransform_o3[576] = 241.0F;
    lanedetection_B.HoughTransform_o3[577] = 242.0F;
    lanedetection_B.HoughTransform_o3[578] = 243.0F;
    lanedetection_B.HoughTransform_o3[579] = 244.0F;
    lanedetection_B.HoughTransform_o3[580] = 245.0F;
    lanedetection_B.HoughTransform_o3[581] = 246.0F;
    lanedetection_B.HoughTransform_o3[582] = 247.0F;
    lanedetection_B.HoughTransform_o3[583] = 248.0F;
    lanedetection_B.HoughTransform_o3[584] = 249.0F;
    lanedetection_B.HoughTransform_o3[585] = 250.0F;
    lanedetection_B.HoughTransform_o3[586] = 251.0F;
    lanedetection_B.HoughTransform_o3[587] = 252.0F;
    lanedetection_B.HoughTransform_o3[588] = 253.0F;
    lanedetection_B.HoughTransform_o3[589] = 254.0F;
    lanedetection_B.HoughTransform_o3[590] = 255.0F;
    lanedetection_B.HoughTransform_o3[591] = 256.0F;
    lanedetection_B.HoughTransform_o3[592] = 257.0F;
    lanedetection_B.HoughTransform_o3[593] = 258.0F;
    lanedetection_B.HoughTransform_o3[594] = 259.0F;
    lanedetection_B.HoughTransform_o3[595] = 260.0F;
    lanedetection_B.HoughTransform_o3[596] = 261.0F;
    lanedetection_B.HoughTransform_o3[597] = 262.0F;
    lanedetection_B.HoughTransform_o3[598] = 263.0F;
    lanedetection_B.HoughTransform_o3[599] = 264.0F;
    lanedetection_B.HoughTransform_o3[600] = 265.0F;
    lanedetection_B.HoughTransform_o3[601] = 266.0F;
    lanedetection_B.HoughTransform_o3[602] = 267.0F;
    lanedetection_B.HoughTransform_o3[603] = 268.0F;
    lanedetection_B.HoughTransform_o3[604] = 269.0F;
    lanedetection_B.HoughTransform_o3[605] = 270.0F;
    lanedetection_B.HoughTransform_o3[606] = 271.0F;
    lanedetection_B.HoughTransform_o3[607] = 272.0F;
    lanedetection_B.HoughTransform_o3[608] = 273.0F;
    lanedetection_B.HoughTransform_o3[609] = 274.0F;
    lanedetection_B.HoughTransform_o3[610] = 275.0F;
    lanedetection_B.HoughTransform_o3[611] = 276.0F;
    lanedetection_B.HoughTransform_o3[612] = 277.0F;
    lanedetection_B.HoughTransform_o3[613] = 278.0F;
    lanedetection_B.HoughTransform_o3[614] = 279.0F;
    lanedetection_B.HoughTransform_o3[615] = 280.0F;
    lanedetection_B.HoughTransform_o3[616] = 281.0F;
    lanedetection_B.HoughTransform_o3[617] = 282.0F;
    lanedetection_B.HoughTransform_o3[618] = 283.0F;
    lanedetection_B.HoughTransform_o3[619] = 284.0F;
    lanedetection_B.HoughTransform_o3[620] = 285.0F;
    lanedetection_B.HoughTransform_o3[621] = 286.0F;
    lanedetection_B.HoughTransform_o3[622] = 287.0F;
    lanedetection_B.HoughTransform_o3[623] = 288.0F;
    lanedetection_B.HoughTransform_o3[624] = 289.0F;
    lanedetection_B.HoughTransform_o3[625] = 290.0F;
    lanedetection_B.HoughTransform_o3[626] = 291.0F;
    lanedetection_B.HoughTransform_o3[627] = 292.0F;
    lanedetection_B.HoughTransform_o3[628] = 293.0F;
    lanedetection_B.HoughTransform_o3[629] = 294.0F;
    lanedetection_B.HoughTransform_o3[630] = 295.0F;
    lanedetection_B.HoughTransform_o3[631] = 296.0F;
    lanedetection_B.HoughTransform_o3[632] = 297.0F;
    lanedetection_B.HoughTransform_o3[633] = 298.0F;
    lanedetection_B.HoughTransform_o3[634] = 299.0F;
    lanedetection_B.HoughTransform_o3[635] = 300.0F;
    lanedetection_B.HoughTransform_o3[636] = 301.0F;
    lanedetection_B.HoughTransform_o3[637] = 302.0F;
    lanedetection_B.HoughTransform_o3[638] = 303.0F;
    lanedetection_B.HoughTransform_o3[639] = 304.0F;
    lanedetection_B.HoughTransform_o3[640] = 305.0F;
    lanedetection_B.HoughTransform_o3[641] = 306.0F;
    lanedetection_B.HoughTransform_o3[642] = 307.0F;
    lanedetection_B.HoughTransform_o3[643] = 308.0F;
    lanedetection_B.HoughTransform_o3[644] = 309.0F;
    lanedetection_B.HoughTransform_o3[645] = 310.0F;
    lanedetection_B.HoughTransform_o3[646] = 311.0F;
    lanedetection_B.HoughTransform_o3[647] = 312.0F;
    lanedetection_B.HoughTransform_o3[648] = 313.0F;
    lanedetection_B.HoughTransform_o3[649] = 314.0F;
    lanedetection_B.HoughTransform_o3[650] = 315.0F;
    lanedetection_B.HoughTransform_o3[651] = 316.0F;
    lanedetection_B.HoughTransform_o3[652] = 317.0F;
    lanedetection_B.HoughTransform_o3[653] = 318.0F;
    lanedetection_B.HoughTransform_o3[654] = 319.0F;
    lanedetection_B.HoughTransform_o3[655] = 320.0F;
    lanedetection_B.HoughTransform_o3[656] = 321.0F;
    lanedetection_B.HoughTransform_o3[657] = 322.0F;
    lanedetection_B.HoughTransform_o3[658] = 323.0F;
    lanedetection_B.HoughTransform_o3[659] = 324.0F;
    lanedetection_B.HoughTransform_o3[660] = 325.0F;
    lanedetection_B.HoughTransform_o3[661] = 326.0F;
    lanedetection_B.HoughTransform_o3[662] = 327.0F;
    lanedetection_B.HoughTransform_o3[663] = 328.0F;
    lanedetection_B.HoughTransform_o3[664] = 329.0F;
    lanedetection_B.HoughTransform_o3[665] = 330.0F;
    lanedetection_B.HoughTransform_o3[666] = 331.0F;
    lanedetection_B.HoughTransform_o3[667] = 332.0F;
    lanedetection_B.HoughTransform_o3[668] = 333.0F;
    lanedetection_B.HoughTransform_o3[669] = 334.0F;
    lanedetection_B.HoughTransform_o3[670] = 335.0F;
  }

  /* states (dwork) */
  (void) memset((void *)&lanedetection_DW, 0,
                sizeof(DW_lanedetection_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lanedetection_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 21;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Start for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureInit(lanedetection_ConstP.V4L2VideoCapture_p1, 0, 0, 0, 0, 320U,
                      240U, 1U, 2U, 1U, 0.05);

  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  lanedetection_DW.obj.matlabCodegenIsDeleted = true;
  lanedetection_DW.obj.isInitialized = 0;
  lanedetection_DW.obj.matlabCodegenIsDeleted = false;
  lanedetection_DW.obj.isSetupComplete = false;
  lanedetection_DW.obj.isInitialized = 1;
  lanedetection_DW.obj.PixelFormatEnum = 2;
  MW_SDL_videoDisplayInit(lanedetection_DW.obj.PixelFormatEnum, 1, 1, 320.0,
    240.0);
  lanedetection_DW.obj.isSetupComplete = true;

  /* End of Start for SubSystem: '<Root>/SDL Video Display' */
}

/* Model terminate function */
void lanedetection_terminate(void)
{
  /* Terminate for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureTerminate(lanedetection_ConstP.V4L2VideoCapture_p1);

  /* Terminate for MATLABSystem: '<S3>/MATLAB System' */
  matlabCodegenHandle_matlabCodeg(&lanedetection_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/SDL Video Display' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
