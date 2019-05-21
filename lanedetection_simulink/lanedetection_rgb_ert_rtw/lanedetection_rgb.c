/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_rgb.c
 *
 * Code generated for Simulink model 'lanedetection_rgb'.
 *
 * Model version                  : 1.623
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri May  3 16:45:50 2019
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
void lanedetection_rgb_step(void)
{
  boolean_T visited2;
  boolean_T isMore;
  boolean_T prevEdgeIsVertical;
  int8_T idxTmpArray[2];
  int32_T lastColA;
  int32_T iC;
  int32_T iA;
  int32_T iB;
  int32_T aidx;
  int32_T cidx;
  int32_T j;
  int32_T r;
  static const int8_T b[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };

  int32_T countPeak;
  boolean_T done;
  real32_T maxValue;
  int32_T edgeTmp_tmp;
  int32_T DrawShapes_DW_Polygon_tmp;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_rgb_ConstP.V4L2VideoCapture_p1,
                        lanedetection_rgb_B.V4L2VideoCapture_o1,
                        lanedetection_rgb_B.V4L2VideoCapture_o2,
                        lanedetection_rgb_B.V4L2VideoCapture_o3);

  /* MATLAB Function: '<Root>/img_ROI' */
  for (aidx = 0; aidx < 70; aidx++) {
    memcpy(&lanedetection_rgb_B.rOUT[aidx * 316],
           &lanedetection_rgb_B.V4L2VideoCapture_o1[aidx * 320 + 30402], 316U *
           sizeof(uint8_T));
  }

  for (aidx = 0; aidx < 70; aidx++) {
    memcpy(&lanedetection_rgb_B.gOUT[aidx * 316],
           &lanedetection_rgb_B.V4L2VideoCapture_o2[aidx * 320 + 30402], 316U *
           sizeof(uint8_T));
  }

  for (aidx = 0; aidx < 70; aidx++) {
    memcpy(&lanedetection_rgb_B.bOUT[aidx * 316],
           &lanedetection_rgb_B.V4L2VideoCapture_o3[aidx * 320 + 30402], 316U *
           sizeof(uint8_T));
  }

  /* End of MATLAB Function: '<Root>/img_ROI' */
  for (lastColA = 0; lastColA < 22120; lastColA++) {
    /* S-Function (svipcolorconv): '<Root>/Color Space  Conversion' */
    lanedetection_rgb_B.ColorSpaceConversion_o1[lastColA] = (uint8_T)
      ((((lanedetection_rgb_B.rOUT[lastColA] * 16829U +
          lanedetection_rgb_B.gOUT[lastColA] * 33039U) +
         lanedetection_rgb_B.bOUT[lastColA] * 6416U) + 1081344U) >> 16);

    /* MATLAB Function: '<Root>/MATLAB Function' */
    lanedetection_rgb_B.V[lastColA] = 0.0;
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Threshold'
   */
  for (j = 0; j < 3; j++) {
    if (j + 69 < 70) {
      lastColA = 69;
    } else {
      lastColA = 70 - j;
    }

    for (countPeak = (j < 1); countPeak <= lastColA; countPeak++) {
      iC = j + countPeak;
      if (!(iC > 1)) {
        iC = 1;
      }

      iC = (iC - 1) * 316;
      iA = countPeak * 316 + 1;
      iB = j * 3;
      aidx = iA;
      cidx = iC;
      for (r = 1; r < 316; r++) {
        lanedetection_rgb_B.V[cidx] += (real_T)(b[iB] *
          lanedetection_rgb_B.ColorSpaceConversion_o1[aidx]);
        aidx++;
        cidx++;
      }

      iB++;
      aidx = iA - 1;
      cidx = iC;
      for (r = 1; r < 317; r++) {
        lanedetection_rgb_B.V[cidx] += (real_T)(b[iB] *
          lanedetection_rgb_B.ColorSpaceConversion_o1[aidx]);
        aidx++;
        cidx++;
      }

      iB++;
      cidx = iC + 1;
      aidx = iA - 1;
      for (r = 1; r < 316; r++) {
        lanedetection_rgb_B.V[cidx] += (real_T)(b[iB] *
          lanedetection_rgb_B.ColorSpaceConversion_o1[aidx]);
        aidx++;
        cidx++;
      }
    }
  }

  for (aidx = 0; aidx < 22120; aidx++) {
    lanedetection_rgb_B.imgEdges[aidx] = (lanedetection_rgb_B.V[aidx] >
      lanedetection_rgb_P.Threshold_Value);
  }

  /* Math: '<Root>/Transpose' */
  for (aidx = 0; aidx < 316; aidx++) {
    for (lastColA = 0; lastColA < 70; lastColA++) {
      lanedetection_rgb_B.Transpose[lastColA + 70 * aidx] =
        lanedetection_rgb_B.imgEdges[316 * lastColA + aidx];
    }
  }

  /* End of Math: '<Root>/Transpose' */

  /* S-Function (sviphough): '<Root>/Hough Transform' */
  MWVIP_Hough_R(&lanedetection_rgb_B.imgEdges[0],
                &lanedetection_rgb_B.HoughTransform_o1[0],
                &lanedetection_rgb_ConstP.HoughTransform_SINE_TABLE_RTP[0],
                &lanedetection_rgb_ConstP.HoughTransform_FIRSTRHO_RTP, 316, 70,
                163, 46);

  /* S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */
  countPeak = 0;
  done = false;
  for (lastColA = 0; lastColA < 14670; lastColA++) {
    lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA] =
      lanedetection_rgb_B.HoughTransform_o1[lastColA];
  }

  lanedetection_rgb_B.FindLocalMaxima_o1[0] = 0.0F;
  lanedetection_rgb_B.FindLocalMaxima_o1[1] = 0.0F;
  lanedetection_rgb_B.FindLocalMaxima_o1[2] = 0.0F;
  lanedetection_rgb_B.FindLocalMaxima_o1[3] = 0.0F;
  while (!done) {
    iC = 0;
    maxValue = lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[0];
    for (lastColA = 0; lastColA < 14670; lastColA++) {
      if (lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA] >
          maxValue) {
        iC = lastColA;
        maxValue = lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA];
      }
    }

    iA = iC % 163;
    lastColA = iC / 163;
    if (lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[iC] >=
        lanedetection_rgb_P.FindLocalMaxima_threshold) {
      lanedetection_rgb_B.FindLocalMaxima_o1[countPeak] = 1.0F + (real32_T)
        lastColA;
      lanedetection_rgb_B.FindLocalMaxima_o1[2U + countPeak] = (real32_T)(1 + iA);
      countPeak++;
      if (countPeak == 2) {
        done = true;
      }

      iC = iA - 22;
      if (!(iC > 0)) {
        iC = 0;
      }

      iA += 22;
      if (!(iA < 162)) {
        iA = 162;
      }

      iB = lastColA - 12;
      aidx = lastColA + 12;
      if (!((iB < 0) || (aidx > 89))) {
        while (iB <= aidx) {
          cidx = iB * 163;
          for (lastColA = iC; lastColA <= iA; lastColA++) {
            lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA + cidx]
              = 0.0F;
          }

          iB++;
        }
      } else {
        if (iB < 0) {
          for (j = iB; j <= aidx; j++) {
            if (j < 0) {
              cidx = (j + 90) * 163 + 162;
              for (lastColA = iC; lastColA <= iA; lastColA++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[cidx -
                  lastColA] = 0.0F;
              }
            } else {
              cidx = j * 163;
              for (lastColA = iC; lastColA <= iA; lastColA++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA +
                  cidx] = 0.0F;
              }
            }
          }
        }

        if (aidx > 89) {
          for (j = iB; j <= aidx; j++) {
            if (j > 89) {
              cidx = (j - 90) * 163 + 162;
              for (lastColA = iC; lastColA <= iA; lastColA++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[cidx -
                  lastColA] = 0.0F;
              }
            } else {
              cidx = j * 163;
              for (lastColA = iC; lastColA <= iA; lastColA++) {
                lanedetection_rgb_DW.FindLocalMaxima_TEMP_IN_DWORKS[lastColA +
                  cidx] = 0.0F;
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
  lanedetection_rgb_B.Submatrix1[1] = lanedetection_rgb_B.FindLocalMaxima_o1[1];

  /* S-Function (sdspsubmtrx): '<Root>/Submatrix' */
  lanedetection_rgb_B.Submatrix[0] = lanedetection_rgb_B.FindLocalMaxima_o1[2];
  lanedetection_rgb_B.Submatrix[1] = lanedetection_rgb_B.FindLocalMaxima_o1[3];

  /* S-Function (sviphoughlines): '<Root>/Hough Lines' incorporates:
   *  Selector: '<Root>/Selector'
   *  Selector: '<Root>/Selector1'
   */
  lastColA = 0;
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

    lastColA = 1;
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
      lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
        (lanedetection_rgb_B.tmpRound + 0.5F);
    } else {
      lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)
        (lanedetection_rgb_B.tmpRound * 0.0F);
    }

    lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = 0;
    lastColA++;
  }

  /* part-3: Right vertical axis */
  if (lastColA < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - 69.0F) *
      (lanedetection_rgb_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         315.0F)) {
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
          (lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = 69;
      lastColA++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (lastColA < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_rgb_B.y2 * 315.0F) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         69.0F)) {
      lanedetection_rgb_B.tmpOutRC[lastColA << 1] = 315;
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)(real32_T)
          floor(lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      lastColA++;
    }
  }

  if (lastColA < 2) {
    lanedetection_rgb_B.tmpOutRC[0U] = -1;
    lanedetection_rgb_B.tmpOutRC[1U] = -1;
    lanedetection_rgb_B.tmpOutRC[2U] = -1;
    lanedetection_rgb_B.tmpOutRC[3U] = -1;
  }

  lanedetection_rgb_B.HoughLines[0] = lanedetection_rgb_B.tmpOutRC[1] + 1;
  lanedetection_rgb_B.HoughLines[2] = lanedetection_rgb_B.tmpOutRC[0] + 1;
  lanedetection_rgb_B.HoughLines[4] = lanedetection_rgb_B.tmpOutRC[3] + 1;
  lanedetection_rgb_B.HoughLines[6] = lanedetection_rgb_B.tmpOutRC[2] + 1;
  lastColA = 0;
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

    lastColA = 1;
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
      lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
        (lanedetection_rgb_B.tmpRound + 0.5F);
    } else {
      lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)
        (lanedetection_rgb_B.tmpRound * 0.0F);
    }

    lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = 0;
    lastColA++;
  }

  /* part-3: Right vertical axis */
  if (lastColA < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - 69.0F) *
      (lanedetection_rgb_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         315.0F)) {
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)(real32_T)floor
          (lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[lastColA << 1] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = 69;
      lastColA++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (lastColA < 2) {
    lanedetection_rgb_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_rgb_B.y2 * 315.0F) + 0.5F);
    if ((lanedetection_rgb_B.tmpRound >= 0.0F) && (lanedetection_rgb_B.tmpRound <=
         69.0F)) {
      lanedetection_rgb_B.tmpOutRC[lastColA << 1] = 315;
      if (lanedetection_rgb_B.tmpRound >= 0.5F) {
        lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)(real32_T)
          floor(lanedetection_rgb_B.tmpRound + 0.5F);
      } else {
        lanedetection_rgb_B.tmpOutRC[1 + (lastColA << 1)] = (int32_T)
          (lanedetection_rgb_B.tmpRound * 0.0F);
      }

      lastColA++;
    }
  }

  if (lastColA < 2) {
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
    for (lastColA = 0; lastColA < 2; lastColA++) {
      aidx = lanedetection_rgb_B.HoughLines[lastColA + 2] - 1;
      j = lanedetection_rgb_B.HoughLines[lastColA] - 1;
      cidx = lanedetection_rgb_B.HoughLines[lastColA + 6] - 1;
      r = lanedetection_rgb_B.HoughLines[4 + lastColA] - 1;
      if ((cidx != aidx) || (r != j)) {
        isMore = false;

        /* Find the visible portion of a line. */
        prevEdgeIsVertical = false;
        visited2 = false;
        done = false;
        countPeak = aidx;
        iA = j;
        iC = cidx;
        iB = r;
        while (!done) {
          lanedetection_rgb_B.numUniquePix = 0;
          lanedetection_rgb_B.loc = 0;

          /* Determine viewport violations. */
          if (countPeak < 0) {
            lanedetection_rgb_B.numUniquePix = 4;
          } else {
            if (countPeak > 315) {
              lanedetection_rgb_B.numUniquePix = 8;
            }
          }

          if (iC < 0) {
            lanedetection_rgb_B.loc = 4;
          } else {
            if (iC > 315) {
              lanedetection_rgb_B.loc = 8;
            }
          }

          if (iA < 0) {
            lanedetection_rgb_B.numUniquePix |= 1U;
          } else {
            if (iA > 69) {
              lanedetection_rgb_B.numUniquePix |= 2U;
            }
          }

          if (iB < 0) {
            lanedetection_rgb_B.loc |= 1U;
          } else {
            if (iB > 69) {
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
              countPeak = aidx;
              iA = j;
            }

            lanedetection_rgb_B.idxCol1 = iC - countPeak;
            lanedetection_rgb_B.idxCol2 = iB - iA;
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
              lanedetection_rgb_B.numUniquePix = -countPeak *
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
                iA += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                iA -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              countPeak = 0;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_rgb_B.numUniquePix = (315 - countPeak) *
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
                iA += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                iA -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              countPeak = 315;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_rgb_B.numUniquePix & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_rgb_B.numUniquePix = -iA *
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
                countPeak += (div_s32_floor(lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                countPeak -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              iA = 0;
              prevEdgeIsVertical = true;
            } else {
              /* Violated CMax. */
              lanedetection_rgb_B.numUniquePix = (69 - iA) *
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
                countPeak += (div_s32_floor(lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                countPeak -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix <<
                  1, lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              iA = 69;
              prevEdgeIsVertical = true;
            }
          } else {
            /* Clip the 2nd point. */
            if (visited2) {
              iC = cidx;
              iB = r;
            }

            lanedetection_rgb_B.idxCol1 = iC - countPeak;
            lanedetection_rgb_B.idxCol2 = iB - iA;
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
              lanedetection_rgb_B.numUniquePix = -iC *
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
                iB += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                iB -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              iC = 0;
              visited2 = true;
            } else if ((lanedetection_rgb_B.loc & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_rgb_B.numUniquePix = (315 - iC) *
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
                iB += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              } else {
                iB -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol1) + 1) >> 1;
              }

              iC = 315;
              visited2 = true;
            } else if ((lanedetection_rgb_B.loc & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_rgb_B.numUniquePix = -iB *
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
                iC += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                iC -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              iB = 0;
              visited2 = true;
            } else {
              /* Violated CMax. */
              lanedetection_rgb_B.numUniquePix = (69 - iB) *
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
                iC += (div_s32_floor(lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol2) + 1) >> 1;
              } else {
                iC -= (div_s32_floor(-lanedetection_rgb_B.numUniquePix << 1,
                                     lanedetection_rgb_B.idxCol2) + 1) >> 1;
              }

              iB = 69;
              visited2 = true;
            }
          }
        }

        if (isMore) {
          /* Draw a line using Bresenham algorithm. */
          /* Initialize the Bresenham algorithm. */
          if (iC >= countPeak) {
            aidx = iC - countPeak;
          } else {
            aidx = countPeak - iC;
          }

          if (iB >= iA) {
            j = iB - iA;
          } else {
            j = iA - iB;
          }

          if (aidx > j) {
            aidx = 1;
            j = 316;
          } else {
            aidx = 316;
            j = 1;
            cidx = countPeak;
            countPeak = iA;
            iA = cidx;
            cidx = iC;
            iC = iB;
            iB = cidx;
          }

          if (countPeak > iC) {
            cidx = countPeak;
            countPeak = iC;
            iC = cidx;
            cidx = iA;
            iA = iB;
            iB = cidx;
          }

          cidx = iC - countPeak;
          if (iA <= iB) {
            r = 1;
            iB -= iA;
          } else {
            r = -1;
            iB = iA - iB;
          }

          lanedetection_rgb_B.idxCol1 = -((cidx + 1) >> 1);
          iA = countPeak * aidx + iA * j;
          j = r * j + aidx;
          done = (countPeak <= iC);
          while (done) {
            lanedetection_rgb_B.DrawShapes_o1[iA] =
              lanedetection_rgb_P.DrawShapes_color[0];
            lanedetection_rgb_B.DrawShapes_o2[iA] =
              lanedetection_rgb_P.DrawShapes_color[1];
            lanedetection_rgb_B.DrawShapes_o3[iA] =
              lanedetection_rgb_P.DrawShapes_color[2];

            /* Compute the next location using Bresenham algorithm. */
            /* Move to the next pixel location. */
            lanedetection_rgb_B.idxCol1 += iB;
            if (lanedetection_rgb_B.idxCol1 >= 0) {
              lanedetection_rgb_B.idxCol1 -= cidx;
              iA += j;
            } else {
              iA += aidx;
            }

            countPeak++;
            done = (countPeak <= iC);
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
      lastColA = lanedetection_rgb_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      countPeak = lanedetection_rgb_B.HoughLines[2] -
        lanedetection_rgb_B.HoughLines[6];
      iC = lanedetection_rgb_B.HoughLines[0] - lanedetection_rgb_B.HoughLines[4];
      if (iC == 0) {
        iB = 0;
        iA = 1;
        aidx = ((lanedetection_rgb_B.HoughLines[0] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[0] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[2] - 1) << 14;
      } else if (countPeak == 0) {
        iA = 2;
        iB = 0;
        aidx = ((lanedetection_rgb_B.HoughLines[2] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[2] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[0] - 1) << 14;
      } else {
        iA = 0;
        iB = div_repeat_s32_floor(countPeak << 14, iC << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[0] - 1) << 14, iB, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iC <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((countPeak * countPeak + iC * iC) <<
          14) << 7, 14U), 14U);
        aidx = j + cidx;
        j -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[0] - 1) <<
          14, iB, 14U) + ((lanedetection_rgb_B.HoughLines[2] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iA == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((aidx & 8192U) != 0U) +
          (aidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[2] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((j & 8192U) != 0U) + (j
          >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[14] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[2] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - aidx, iB, 14U),
            mul_s32_loSR(iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[0] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx += mul_s32_loSR(iB, r, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[2] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        }

        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[14] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - j, iB, 14U), mul_s32_loSR
            (iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[12] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx = mul_s32_loSR(iB, r, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[14] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
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
      if (iC == 0) {
        iB = 0;
        iA = 1;
        aidx = ((lanedetection_rgb_B.HoughLines[0] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[0] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[6] - 1) << 14;
      } else if (countPeak == 0) {
        iA = 2;
        iB = 0;
        aidx = ((lanedetection_rgb_B.HoughLines[2] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[2] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[4] - 1) << 14;
      } else {
        iA = 0;
        iB = div_repeat_s32_floor(countPeak << 14, iC << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[0] - 1) << 14, iB, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iC <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((countPeak * countPeak + iC * iC) <<
          14) << 7, 14U), 14U);
        aidx = j + cidx;
        j -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[4] - 1) <<
          14, iB, 14U) + ((lanedetection_rgb_B.HoughLines[6] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iA == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((aidx & 8192U) != 0U) +
          (aidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[6] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((j & 8192U) != 0U) + (j >>
          14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[10] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[6] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - aidx, iB, 14U),
            mul_s32_loSR(iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[4] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx += mul_s32_loSR(iB, r, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[6] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        }

        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[10] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - j, iB, 14U), mul_s32_loSR
            (iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[8] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx = mul_s32_loSR(iB, r, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[10] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      lastColA = lanedetection_rgb_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      countPeak = lanedetection_rgb_B.HoughLines[3] -
        lanedetection_rgb_B.HoughLines[7];
      iC = lanedetection_rgb_B.HoughLines[1] - lanedetection_rgb_B.HoughLines[5];
      if (iC == 0) {
        iB = 0;
        iA = 1;
        aidx = ((lanedetection_rgb_B.HoughLines[1] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[1] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[3] - 1) << 14;
      } else if (countPeak == 0) {
        iA = 2;
        iB = 0;
        aidx = ((lanedetection_rgb_B.HoughLines[3] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[3] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[1] - 1) << 14;
      } else {
        iA = 0;
        iB = div_repeat_s32_floor(countPeak << 14, iC << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[1] - 1) << 14, iB, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iC <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((countPeak * countPeak + iC * iC) <<
          14) << 7, 14U), 14U);
        aidx = j + cidx;
        j -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[1] - 1) <<
          14, iB, 14U) + ((lanedetection_rgb_B.HoughLines[3] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iA == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((aidx & 8192U) != 0U) +
          (aidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[3] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((j & 8192U) != 0U) + (j
          >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[15] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[3] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - aidx, iB, 14U),
            mul_s32_loSR(iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[1] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx += mul_s32_loSR(iB, r, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[3] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        }

        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[15] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - j, iB, 14U), mul_s32_loSR
            (iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[13] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx = mul_s32_loSR(iB, r, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[15] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
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
      if (iC == 0) {
        iB = 0;
        iA = 1;
        aidx = ((lanedetection_rgb_B.HoughLines[1] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[1] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[7] - 1) << 14;
      } else if (countPeak == 0) {
        iA = 2;
        iB = 0;
        aidx = ((lanedetection_rgb_B.HoughLines[3] - lastColA) - 1) << 14;
        j = ((lanedetection_rgb_B.HoughLines[3] + lastColA) - 1) << 14;
        cidx = (lanedetection_rgb_B.HoughLines[5] - 1) << 14;
      } else {
        iA = 0;
        iB = div_repeat_s32_floor(countPeak << 14, iC << 14, 14U);
        j = ((lanedetection_rgb_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_rgb_B.HoughLines[1] - 1) << 14, iB, 14U);
        cidx = div_repeat_s32_floor(lastColA << 14, div_repeat_s32_floor(iC <<
          14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((countPeak * countPeak + iC * iC) <<
          14) << 7, 14U), 14U);
        aidx = j + cidx;
        j -= cidx;
        cidx = div_repeat_s32_floor((lanedetection_rgb_B.HoughLines[5] - 1) <<
          14, iB, 14U) + ((lanedetection_rgb_B.HoughLines[7] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (iA == 1) {
        lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((aidx & 8192U) != 0U) +
          (aidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[7] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((j & 8192U) != 0U) + (j >>
          14);
        lanedetection_rgb_DW.DrawShapes_DW_Points[11] = ((cidx & 8192U) != 0U) +
          (cidx >> 14);
      } else {
        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[7] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - aidx, iB, 14U),
            mul_s32_loSR(iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[5] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx += mul_s32_loSR(iB, r, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[7] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        }

        if (iA == 2) {
          lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((cidx & 8192U) != 0U)
            + (cidx >> 14);
          lanedetection_rgb_DW.DrawShapes_DW_Points[11] = ((j & 8192U) != 0U) +
            (j >> 14);
        } else {
          r = div_repeat_s32_floor(mul_s32_loSR(cidx - j, iB, 14U), mul_s32_loSR
            (iB, iB, 14U) + 16384, 14U);
          lanedetection_rgb_DW.DrawShapes_DW_Points[9] = ((r & 8192U) != 0U) +
            (r >> 14);
          aidx = mul_s32_loSR(iB, r, 14U) + j;
          lanedetection_rgb_DW.DrawShapes_DW_Points[11] = ((aidx & 8192U) != 0U)
            + (aidx >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
    }

    /* ProcessStep-after poly points-1
     */
    countPeak = 2;

    /* just before call for cgpolygon
     */
    if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
      /* just before call for cgpolygon-2
       */
      countPeak = 4;
    }

    iC = countPeak << 1;

    /* Reset scanline states. */
    iA = 0;
    iB = 0;
    idxTmpArray[0U] = (int8_T)(countPeak - 1);
    isMore = true;
    while (isMore) {
      /* Initialize the scanline. */
      /* Convert polygon vertices to boundaries. */
      aidx = 0;
      j = iA;
      cidx = iA;

      /* start for loop
       */
      r = (((idxTmpArray[0] << 1) + 1) << 1) + iB;
      lanedetection_rgb_B.idxCol1 = (idxTmpArray[0] << 2) + iB;
      lanedetection_rgb_B.idxTmp = idxTmpArray[0];
      lanedetection_rgb_B.idxCol2 = ((idxTmpArray[0] - 1) << 2) + iB;
      lanedetection_rgb_B.numUniquePix = countPeak;
      if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];

        /* getLoc-1
         */
        lastColA =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_rgb_B.loc =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];

        /* getLoc-2
         */
        lastColA = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];
      }

      while ((lanedetection_rgb_B.idxCol2 >= 0) && (lanedetection_rgb_B.loc - 1 ==
              lastColA - 1)) {
        lanedetection_rgb_B.idxTmp--;
        lanedetection_rgb_B.idxCol2 = ((lanedetection_rgb_B.idxTmp - 1) << 2) +
          iB;
        lanedetection_rgb_B.numUniquePix--;
        if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          lastColA =
            lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol2];
        } else {
          /* getLoc-2
           */
          lastColA = lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol2];
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
      lanedetection_rgb_B.idxRow2 = 2 + iB;
      lanedetection_rgb_B.idxCol2 = iB;
      prevEdgeIsVertical = false;
      if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_rgb_B.loc = lanedetection_rgb_DW.DrawShapes_DW_Points[iB];

        /* getLoc-1
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_DW.DrawShapes_DW_Points[lanedetection_rgb_B.idxCol1];
      } else {
        /* getLoc-2
         */
        lanedetection_rgb_B.loc = lanedetection_rgb_B.HoughLines[iB];

        /* getLoc-2
         */
        lanedetection_rgb_B.loc_m =
          lanedetection_rgb_B.HoughLines[lanedetection_rgb_B.idxCol1];
      }

      for (lastColA = 0; lastColA < lanedetection_rgb_B.numUniquePix; lastColA++)
      {
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
            isMore = false;
          } else {
            isMore = true;
            lanedetection_rgb_B.idxTmp = r;
            r = lanedetection_rgb_B.idxRow2;
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
              lanedetection_rgb_DW.DrawShapes_DW_Points[r];
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
            lanedetection_rgb_B.idxOld = lanedetection_rgb_B.HoughLines[r];
          }

          /* Initialize a Bresenham line. */
          edgeTmp_tmp = lanedetection_rgb_B.idxTmp - lanedetection_rgb_B.idxNew;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx] = 0;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 1] =
            lanedetection_rgb_B.idxOld - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 2] =
            lanedetection_rgb_B.idxNew - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 3] =
            lanedetection_rgb_B.idxTmp - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 6] = 0;
          if (lanedetection_rgb_B.numActiveEdge - 1 >=
              lanedetection_rgb_B.idxOld - 1) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 8] =
              lanedetection_rgb_B.numActiveEdge - lanedetection_rgb_B.idxOld;
          } else {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 8] =
              lanedetection_rgb_B.idxOld - lanedetection_rgb_B.numActiveEdge;
          }

          while (lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 8] >= 0) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 6]++;
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 8] -= edgeTmp_tmp;
          }

          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 5] =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 6] - 1;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 7] =
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 8] + edgeTmp_tmp;
          lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 4] = edgeTmp_tmp -
            (lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 7] << 1);
          if (lanedetection_rgb_B.idxOld - 1 > lanedetection_rgb_B.numActiveEdge
              - 1) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 5] =
              -lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 5];
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 6] =
              -lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 6];
          }

          if ((!done) && (!isMore)) {
            /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 2]++;
            if ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx] << 1) >
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 4]) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 8];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 1] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 6];
            } else {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 7];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 1] +=
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 5];
            }
          } else {
            if (done && isMore) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 3]--;
            }
          }

          done = isMore;
          if (!prevEdgeIsVertical) {
            /* Merge two Bresenham lines. */
            prevEdgeIsVertical = false;
            if ((j != cidx) && ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[j +
                                 5] ==
                                 lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx
                                 + 5]) &&
                                (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j +
                                 6] ==
                                 lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx
                                 + 6]) &&
                                (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j +
                                 7] ==
                                 lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx
                                 + 7]) &&
                                (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j +
                                 8] ==
                                 lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx
                                 + 8]))) {
              if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3] + 1 ==
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 2]) {
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3] =
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 3];
                prevEdgeIsVertical = true;
              } else {
                if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 3] + 1 ==
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2]) {
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1] =
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 1];
                  lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2] =
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 2];
                  prevEdgeIsVertical = true;
                }
              }
            }

            if (!prevEdgeIsVertical) {
              j = cidx;
              aidx++;
            }
          } else {
            j = cidx;
            aidx++;
          }

          cidx = j + 9;
          if (!isMore) {
            r = lanedetection_rgb_B.idxRow2;
            lanedetection_rgb_B.idxCol1 = lanedetection_rgb_B.idxCol2;
          }

          lanedetection_rgb_B.idxRow2 = r + 4;
          lanedetection_rgb_B.idxCol2 = lanedetection_rgb_B.idxCol1 + 4;
          prevEdgeIsVertical = false;
        } else {
          prevEdgeIsVertical = true;
          r = lanedetection_rgb_B.idxRow2;
          lanedetection_rgb_B.idxCol1 = lanedetection_rgb_B.idxCol2;
          lanedetection_rgb_B.idxRow2 += 4;
          lanedetection_rgb_B.idxCol2 += 4;
        }
      }

      if (!(lanedetection_rgb_B.loc_m - 1 == lanedetection_rgb_B.loc - 1)) {
        /* Merge two Bresenham lines. */
        done = false;
        if ((iA != j) && ((lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 5] ==
                           lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 5]) &&
                          (lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 6] ==
                           lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 6]) &&
                          (lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 7] ==
                           lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 7]) &&
                          (lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 8] ==
                           lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 8])))
        {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 3] + 1 ==
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2]) {
            lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 3] =
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3];
            done = true;
          } else {
            if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 3] + 1 ==
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 2]) {
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 1] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 1];
              lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 2] =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[j + 2];
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
      for (lastColA = aidx; lastColA < countPeak; lastColA++) {
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 2] = 1;
        lanedetection_rgb_DW.DrawShapes_DW_Polygon[cidx + 3] = 0;
        cidx += 9;
      }

      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_rgb_B.idxNew = iA;
        lanedetection_rgb_B.idxOld = iA + 9;
        isMore = false;
        for (lastColA = 1; lastColA < aidx; lastColA++) {
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
      j = iA + 3;
      cidx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 3];
      for (lastColA = 1; lastColA < aidx; lastColA++) {
        j += 9;
        if (cidx < lanedetection_rgb_DW.DrawShapes_DW_Polygon[j]) {
          cidx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j];
        }
      }

      r = cidx;
      if (cidx > 69) {
        r = 69;
      }

      /* Find out the first column of the polygon. */
      j = iA + 2;
      cidx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[iA + 2];
      for (lastColA = 1; lastColA < aidx; lastColA++) {
        j += 9;
        if (cidx > lanedetection_rgb_DW.DrawShapes_DW_Polygon[j]) {
          cidx = lanedetection_rgb_DW.DrawShapes_DW_Polygon[j];
        }
      }

      if (cidx < 0) {
        cidx = 0;
      }

      /* Move to the next column and find out boundaries of the polygon at this column. */
      lanedetection_rgb_B.idxNew = iA;
      lanedetection_rgb_B.idxOld = iA;
      lanedetection_rgb_B.idxCol1 = iA;
      lanedetection_rgb_B.idxCol2 = 0;
      lanedetection_rgb_B.numActiveEdge = 0;
      for (lastColA = 0; lastColA < aidx; lastColA++) {
        /* Find out the valid boundaries and bring them to the latest column. */
        if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
            + 3] >= cidx) {
          if (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
              + 2] <= cidx) {
            while
                (lanedetection_rgb_DW.DrawShapes_DW_Polygon[lanedetection_rgb_B.idxOld
                 + 2] < cidx) {
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
        lanedetection_rgb_B.idxNew = iA;
        lanedetection_rgb_B.idxOld = iA + 9;
        isMore = false;
        for (lastColA = 1; lastColA < lanedetection_rgb_B.numActiveEdge;
             lastColA++) {
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

      aidx = iA;
      lanedetection_rgb_B.numUniquePix = cidx + 1;
      lanedetection_rgb_B.loc = 0;
      j = 0;
      lanedetection_rgb_B.numActiveEdge = -1;
      isMore = (0 <= r);
      while (isMore) {
        /* Get a string of pixels */
        prevEdgeIsVertical = false;
        done = (j != 0);
        lanedetection_rgb_B.idxTmp = lanedetection_rgb_B.loc;
        if ((lanedetection_rgb_B.loc >= cidx) && (lanedetection_rgb_B.loc <= r))
        {
          if (aidx < lanedetection_rgb_B.idxCol1) {
            lastColA = lanedetection_rgb_DW.DrawShapes_DW_Polygon[aidx + 1];
            aidx += 9;
            if ((lastColA == lanedetection_rgb_B.numActiveEdge) && (aidx <
                 lanedetection_rgb_B.idxCol1)) {
              lanedetection_rgb_B.loc_m =
                lanedetection_rgb_DW.DrawShapes_DW_Polygon[aidx + 1];
              isMore = (aidx < lanedetection_rgb_B.idxCol1);
              while (isMore && (lastColA == lanedetection_rgb_B.loc_m)) {
                prevEdgeIsVertical = true;
                lastColA = lanedetection_rgb_DW.DrawShapes_DW_Polygon[aidx + 1];
                aidx += 9;
                isMore = (aidx < lanedetection_rgb_B.idxCol1);
                if (isMore) {
                  lanedetection_rgb_B.loc_m =
                    lanedetection_rgb_DW.DrawShapes_DW_Polygon[aidx + 1];
                }
              }

              if (!isMore) {
                prevEdgeIsVertical = false;
              }
            }

            if (j != 0) {
              lanedetection_rgb_B.loc_m = lanedetection_rgb_B.numActiveEdge;
              if (lastColA <= 315) {
                lanedetection_rgb_B.idxRow2 = lastColA;
                lanedetection_rgb_B.numActiveEdge = lastColA;
              } else {
                lanedetection_rgb_B.idxRow2 = 315;
                lanedetection_rgb_B.numActiveEdge = 315;
              }
            } else {
              lanedetection_rgb_B.loc_m = lanedetection_rgb_B.numActiveEdge + 1;
              if ((lastColA > 0) && (lastColA <= 315)) {
                lanedetection_rgb_B.idxRow2 = lastColA - 1;
                lanedetection_rgb_B.numActiveEdge = lastColA;
              } else if (lastColA <= 0) {
                lanedetection_rgb_B.idxRow2 = -1;
                lanedetection_rgb_B.numActiveEdge = 0;
              } else {
                lanedetection_rgb_B.idxRow2 = 315;
                lanedetection_rgb_B.numActiveEdge = 316;
              }
            }

            if (!prevEdgeIsVertical) {
              j = !(j != 0);
            }
          } else {
            /* Reset states and move to the next column. */
            done = false;
            lanedetection_rgb_B.loc_m = lanedetection_rgb_B.numActiveEdge + 1;
            lanedetection_rgb_B.idxRow2 = 315;

            /* Move to the next column and find out boundaries of the polygon at this column. */
            lanedetection_rgb_B.idxNew = iA;
            lanedetection_rgb_B.idxOld = iA;
            lanedetection_rgb_B.idxCol1 = iA;
            aidx = 0;
            lanedetection_rgb_B.numActiveEdge = 0;
            for (lastColA = 0; lastColA < lanedetection_rgb_B.idxCol2; lastColA
                 ++) {
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
                aidx++;
              }

              lanedetection_rgb_B.idxOld += 9;
            }

            lanedetection_rgb_B.idxCol2 = aidx;

            /* Sort the boundaries of the polygon according to row values. */
            /* Sort the boundaries of the polygon. */
            isMore = true;
            while (isMore) {
              lanedetection_rgb_B.idxNew = iA;
              lanedetection_rgb_B.idxOld = iA + 9;
              isMore = false;
              for (lastColA = 1; lastColA < lanedetection_rgb_B.numActiveEdge;
                   lastColA++) {
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

            aidx = iA;
            lanedetection_rgb_B.numUniquePix++;
            j = 0;
            lanedetection_rgb_B.numActiveEdge = -1;
            lanedetection_rgb_B.loc++;
          }
        } else {
          lanedetection_rgb_B.loc_m = 0;
          lanedetection_rgb_B.idxRow2 = 315;
          lanedetection_rgb_B.loc++;
        }

        if (lanedetection_rgb_B.loc_m < 0) {
          lanedetection_rgb_B.loc_m = 0;
        }

        if (lanedetection_rgb_B.idxRow2 < lanedetection_rgb_B.loc_m) {
          lanedetection_rgb_B.idxRow2 = lanedetection_rgb_B.loc_m - 1;
        }

        if (done) {
          lanedetection_rgb_B.idxTmp = lanedetection_rgb_B.idxTmp * 316 +
            lanedetection_rgb_B.loc_m;
          lanedetection_rgb_B.idxNew = 1;
          if (lanedetection_rgb_P.DrawShapes_lineWidth > 1) {
            lanedetection_rgb_B.idxNew = 0;
          }

          lanedetection_rgb_B.idxOld = lanedetection_rgb_B.idxTmp;
          for (lastColA = lanedetection_rgb_B.loc_m; lastColA <=
               lanedetection_rgb_B.idxRow2; lastColA++) {
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
          for (lastColA = lanedetection_rgb_B.loc_m; lastColA <=
               lanedetection_rgb_B.idxRow2; lastColA++) {
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

          while (lanedetection_rgb_B.loc_m <= lanedetection_rgb_B.idxRow2) {
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
            lanedetection_rgb_B.loc_m++;
          }
        }

        isMore = (lanedetection_rgb_B.loc <= r);
      }

      /* Move to the next polygon. */
      iA += countPeak * 9;
      if (iB >= div_s32_floor(iC, countPeak) - 1) {
        iB = 0;
      } else {
        iB++;
      }

      isMore = (iA < (countPeak << 1) * 9);
    }
  }

  /* End of S-Function (svipdrawshapes): '<Root>/Draw Shapes' */
  /* Start for MATLABSystem: '<S2>/MATLAB System' */
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
  lanedetection_rgb_M->Sizes.checksums[0] = (3810892094U);
  lanedetection_rgb_M->Sizes.checksums[1] = (287240213U);
  lanedetection_rgb_M->Sizes.checksums[2] = (3392133978U);
  lanedetection_rgb_M->Sizes.checksums[3] = (755500555U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    lanedetection_rgb_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
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
    dtInfo.numDataTypes = 18;
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

  /* Start for MATLABSystem: '<S2>/MATLAB System' */
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

  /* Terminate for MATLABSystem: '<S2>/MATLAB System' */
  matlabCodegenHandle_matlabCodeg(&lanedetection_rgb_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/SDL Video Display' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
