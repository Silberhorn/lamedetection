/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection.c
 *
 * Code generated for Simulink model 'lanedetection'.
 *
 * Model version                  : 1.212
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Apr 11 10:22:41 2019
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
  int8_T threshSquared;
  int32_T imgCol;
  int32_T imgRow;
  int8_T accumOne;
  int8_T accumTwo;
  int32_T imgIdx;
  int8_T accumThree;
  int8_T accumFour;
  boolean_T done;
  int32_T i;
  real32_T maxValue;
  int32_T p;
  int32_T q2;
  int32_T jRowsIn;
  int32_T acc1_idx_5;
  int32_T edgeTmp_tmp;
  int32_T DrawShapes_DW_Polygon_tmp;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_ConstP.V4L2VideoCapture_p1,
                        lanedetection_B.V4L2VideoCapture_o1,
                        lanedetection_B.V4L2VideoCapture_o2,
                        lanedetection_B.V4L2VideoCapture_o3);

  /* MATLAB Function: '<Root>/MATLAB Function1' */
  for (imgCol = 0; imgCol < 100; imgCol++) {
    memcpy(&lanedetection_B.imgOUT[imgCol * 320],
           &lanedetection_B.V4L2VideoCapture_o1[imgCol * 320 + 38079], 320U *
           sizeof(uint8_T));
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function1' */

  /* S-Function (svipresize): '<Root>/Resize' */
  /* use pre-computed weights and index table to perform interpolation */
  imgRow = 0;

  /* resize along X-axis direction */
  for (p = 0; p < 160; p++) {
    i = p;
    for (imgIdx = 0; imgIdx < 100; imgIdx++) {
      jRowsIn = imgIdx;
      q2 = 0;
      for (lanedetection_B.k = 0; lanedetection_B.k < 5; lanedetection_B.k++) {
        imgCol =
          (lanedetection_B.V4L2VideoCapture_o2[lanedetection_ConstP.pooled3[jRowsIn]
           * 160 + p] * lanedetection_ConstP.pooled9[jRowsIn]) << 3;
        if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
          q2 = MIN_int32_T;
        } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
          q2 = MAX_int32_T;
        } else {
          q2 += imgCol;
        }

        jRowsIn += 100;
      }

      imgCol = ((q2 & 512U) != 0U) + (q2 >> 10);
      if (imgCol < 0) {
        imgCol = 0;
      } else {
        if (imgCol > 255) {
          imgCol = 255;
        }
      }

      lanedetection_DW.Resize_IntBuffer[i] = (uint8_T)imgCol;
      i += 160;
    }
  }

  /* resize along Y-axis direction */
  for (imgIdx = 0; imgIdx < 100; imgIdx++) {
    i = imgIdx * 160;
    for (imgCol = 0; imgCol < 160; imgCol++) {
      lanedetection_DW.Resize_LineBuffer[imgCol] =
        lanedetection_DW.Resize_IntBuffer[i];
      i++;
    }

    for (p = 0; p < 320; p++) {
      q2 = (lanedetection_DW.Resize_LineBuffer[lanedetection_ConstP.pooled2[p]] *
            lanedetection_ConstP.pooled8[p]) << 3;
      i = p + 320;
      imgCol =
        (lanedetection_DW.Resize_LineBuffer[lanedetection_ConstP.pooled2[i]] *
         lanedetection_ConstP.pooled8[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      imgCol = ((q2 & 512U) != 0U) + (q2 >> 10);
      if (imgCol < 0) {
        imgCol = 0;
      } else {
        if (imgCol > 255) {
          imgCol = 255;
        }
      }

      lanedetection_B.Resize[imgRow] = (uint8_T)imgCol;
      imgRow++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize' */

  /* S-Function (svipresize): '<Root>/Resize1' */
  /* use pre-computed weights and index table to perform interpolation */
  imgRow = 0;

  /* resize along X-axis direction */
  for (p = 0; p < 160; p++) {
    i = p;
    for (imgIdx = 0; imgIdx < 100; imgIdx++) {
      jRowsIn = imgIdx;
      q2 = 0;
      for (lanedetection_B.k = 0; lanedetection_B.k < 5; lanedetection_B.k++) {
        imgCol =
          (lanedetection_B.V4L2VideoCapture_o3[lanedetection_ConstP.pooled3[jRowsIn]
           * 160 + p] * lanedetection_ConstP.pooled9[jRowsIn]) << 3;
        if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
          q2 = MIN_int32_T;
        } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
          q2 = MAX_int32_T;
        } else {
          q2 += imgCol;
        }

        jRowsIn += 100;
      }

      imgCol = ((q2 & 512U) != 0U) + (q2 >> 10);
      if (imgCol < 0) {
        imgCol = 0;
      } else {
        if (imgCol > 255) {
          imgCol = 255;
        }
      }

      lanedetection_DW.Resize1_IntBuffer[i] = (uint8_T)imgCol;
      i += 160;
    }
  }

  /* resize along Y-axis direction */
  for (imgIdx = 0; imgIdx < 100; imgIdx++) {
    i = imgIdx * 160;
    for (imgCol = 0; imgCol < 160; imgCol++) {
      lanedetection_DW.Resize_LineBuffer[imgCol] =
        lanedetection_DW.Resize1_IntBuffer[i];
      i++;
    }

    for (p = 0; p < 320; p++) {
      q2 = (lanedetection_DW.Resize_LineBuffer[lanedetection_ConstP.pooled2[p]] *
            lanedetection_ConstP.pooled8[p]) << 3;
      i = p + 320;
      imgCol =
        (lanedetection_DW.Resize_LineBuffer[lanedetection_ConstP.pooled2[i]] *
         lanedetection_ConstP.pooled8[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      imgCol = ((q2 & 512U) != 0U) + (q2 >> 10);
      if (imgCol < 0) {
        imgCol = 0;
      } else {
        if (imgCol > 255) {
          imgCol = 255;
        }
      }

      lanedetection_B.Resize1[imgRow] = (uint8_T)imgCol;
      imgRow++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize1' */

  /* S-Function (svipedge): '<Root>/Edge Detection' incorporates:
   *  Constant: '<Root>/Threshold'
   */
  threshSquared = (int8_T)(((int32_T)((uint32_T)lanedetection_P.Threshold_Value *
    lanedetection_P.Threshold_Value) << 8) >> 8);
  for (imgCol = 0; imgCol < 98; imgCol++) {
    for (imgRow = 0; imgRow < 318; imgRow++) {
      imgIdx = ((imgCol + 1) * 320 + imgRow) + 1;
      accumOne = (int8_T)((int8_T)((lanedetection_B.imgOUT[imgIdx +
        lanedetection_DW.EdgeDetection_VO_DW[0]] << 7) >> 8) +
                          ((lanedetection_B.imgOUT[imgIdx +
                            lanedetection_DW.EdgeDetection_VO_DW[1]] * -128) >>
                           8));
      accumTwo = (int8_T)((int8_T)((lanedetection_B.imgOUT[imgIdx +
        lanedetection_DW.EdgeDetection_HO_DW[0]] * -128) >> 8) +
                          ((lanedetection_B.imgOUT[imgIdx +
                            lanedetection_DW.EdgeDetection_HO_DW[1]] << 7) >> 8));
      lanedetection_B.EdgeDetection[imgIdx] = ((int8_T)((int8_T)(((accumOne *
        accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >> 8)) >
        threshSquared);
    }
  }

  for (imgCol = 0; imgCol < 98; imgCol++) {
    imgRow = (imgCol + 1) * 320;
    imgIdx = (imgCol + 1) * 320 + 319;
    accumOne = (int8_T)((int8_T)((lanedetection_B.imgOUT[imgRow +
      lanedetection_DW.EdgeDetection_HOU_DW[0]] * -128) >> 8) +
                        ((lanedetection_B.imgOUT[imgRow +
                          lanedetection_DW.EdgeDetection_HOU_DW[1]] << 7) >> 8));
    accumTwo = (int8_T)((int8_T)((lanedetection_B.imgOUT[imgIdx +
      lanedetection_DW.EdgeDetection_HOD_DW[0]] * -128) >> 8) +
                        ((lanedetection_B.imgOUT[imgIdx +
                          lanedetection_DW.EdgeDetection_HOD_DW[1]] << 7) >> 8));
    accumThree = (int8_T)((int8_T)((lanedetection_B.imgOUT[imgRow +
      lanedetection_DW.EdgeDetection_VOU_DW[0]] << 7) >> 8) +
                          ((lanedetection_B.imgOUT[imgRow +
      lanedetection_DW.EdgeDetection_VOU_DW[1]] * -128) >> 8));
    accumFour = (int8_T)((int8_T)((lanedetection_B.imgOUT[imgIdx +
      lanedetection_DW.EdgeDetection_VOD_DW[0]] << 7) >> 8) +
                         ((lanedetection_B.imgOUT[imgIdx +
      lanedetection_DW.EdgeDetection_VOD_DW[1]] * -128) >> 8));
    lanedetection_B.EdgeDetection[imgRow] = ((int8_T)((int8_T)(((accumOne *
      accumOne) << 8) >> 8) + (int8_T)(((accumThree * accumThree) << 8) >> 8)) >
      threshSquared);
    lanedetection_B.EdgeDetection[imgIdx] = ((int8_T)((int8_T)(((accumTwo *
      accumTwo) << 8) >> 8) + (int8_T)(((accumFour * accumFour) << 8) >> 8)) >
      threshSquared);
  }

  for (imgRow = 0; imgRow < 318; imgRow++) {
    accumOne = (int8_T)((int8_T)((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_VOL_DW[0]) + 1] << 7) >> 8) +
                        ((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_VOL_DW[1]) + 1] * -128) >> 8));
    accumTwo = (int8_T)((int8_T)((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_VOR_DW[0]) + 31681] << 7) >> 8) +
                        ((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_VOR_DW[1]) + 31681] * -128) >> 8));
    accumThree = (int8_T)((int8_T)((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_HOL_DW[0]) + 1] * -128) >> 8) +
                          ((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_HOL_DW[1]) + 1] << 7) >> 8));
    accumFour = (int8_T)((int8_T)((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_HOR_DW[0]) + 31681] * -128) >> 8) +
                         ((lanedetection_B.imgOUT[(imgRow +
      lanedetection_DW.EdgeDetection_HOR_DW[1]) + 31681] << 7) >> 8));
    lanedetection_B.EdgeDetection[imgRow + 1] = ((int8_T)((int8_T)(((accumOne *
      accumOne) << 8) >> 8) + (int8_T)(((accumThree * accumThree) << 8) >> 8)) >
      threshSquared);
    lanedetection_B.EdgeDetection[31681 + imgRow] = ((int8_T)((int8_T)
      (((accumTwo * accumTwo) << 8) >> 8) + (int8_T)(((accumFour * accumFour) <<
      8) >> 8)) > threshSquared);
  }

  accumOne = (int8_T)((int8_T)
                      ((lanedetection_B.imgOUT[lanedetection_DW.EdgeDetection_VOUL_DW
                        [0]] << 7) >> 8) +
                      ((lanedetection_B.imgOUT[lanedetection_DW.EdgeDetection_VOUL_DW
                        [1]] * -128) >> 8));
  accumTwo = (int8_T)((int8_T)
                      ((lanedetection_B.imgOUT[lanedetection_DW.EdgeDetection_HOUL_DW
                        [0]] * -128) >> 8) +
                      ((lanedetection_B.imgOUT[lanedetection_DW.EdgeDetection_HOUL_DW
                        [1]] << 7) >> 8));
  accumThree = (int8_T)((int8_T)((lanedetection_B.imgOUT[319 +
    lanedetection_DW.EdgeDetection_VOLL_DW[0]] << 7) >> 8) +
                        ((lanedetection_B.imgOUT[319 +
    lanedetection_DW.EdgeDetection_VOLL_DW[1]] * -128) >> 8));
  accumFour = (int8_T)((int8_T)((lanedetection_B.imgOUT[319 +
    lanedetection_DW.EdgeDetection_HOLL_DW[0]] * -128) >> 8) +
                       ((lanedetection_B.imgOUT[319 +
    lanedetection_DW.EdgeDetection_HOLL_DW[1]] << 7) >> 8));
  lanedetection_B.EdgeDetection[0] = ((int8_T)((int8_T)(((accumOne * accumOne) <<
    8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >> 8)) > threshSquared);
  lanedetection_B.EdgeDetection[319] = ((int8_T)((int8_T)(((accumThree *
    accumThree) << 8) >> 8) + (int8_T)(((accumFour * accumFour) << 8) >> 8)) >
    threshSquared);
  accumOne = (int8_T)((int8_T)((lanedetection_B.imgOUT[31680 +
    lanedetection_DW.EdgeDetection_VOUR_DW[0]] << 7) >> 8) +
                      ((lanedetection_B.imgOUT[31680 +
                        lanedetection_DW.EdgeDetection_VOUR_DW[1]] * -128) >> 8));
  accumTwo = (int8_T)((int8_T)((lanedetection_B.imgOUT[31680 +
    lanedetection_DW.EdgeDetection_HOUR_DW[0]] * -128) >> 8) +
                      ((lanedetection_B.imgOUT[31680 +
                        lanedetection_DW.EdgeDetection_HOUR_DW[1]] << 7) >> 8));
  accumThree = (int8_T)((int8_T)((lanedetection_B.imgOUT[31999 +
    lanedetection_DW.EdgeDetection_VOLR_DW[0]] << 7) >> 8) +
                        ((lanedetection_B.imgOUT[31999 +
    lanedetection_DW.EdgeDetection_VOLR_DW[1]] * -128) >> 8));
  accumFour = (int8_T)((int8_T)((lanedetection_B.imgOUT[31999 +
    lanedetection_DW.EdgeDetection_HOLR_DW[0]] * -128) >> 8) +
                       ((lanedetection_B.imgOUT[31999 +
    lanedetection_DW.EdgeDetection_HOLR_DW[1]] << 7) >> 8));
  lanedetection_B.EdgeDetection[31680] = ((int8_T)((int8_T)(((accumOne *
    accumOne) << 8) >> 8) + (int8_T)(((accumTwo * accumTwo) << 8) >> 8)) >
    threshSquared);
  lanedetection_B.EdgeDetection[31999] = ((int8_T)((int8_T)(((accumThree *
    accumThree) << 8) >> 8) + (int8_T)(((accumFour * accumFour) << 8) >> 8)) >
    threshSquared);

  /* End of S-Function (svipedge): '<Root>/Edge Detection' */

  /* S-Function (sviphough): '<Root>/Hough Transform' */
  MWVIP_Hough_R(&lanedetection_B.EdgeDetection[0],
                &lanedetection_B.HoughTransform_o1[0],
                &lanedetection_ConstP.HoughTransform_SINE_TABLE_RTP[0],
                &lanedetection_ConstP.HoughTransform_FIRSTRHO_RTP, 320, 100, 671,
                91);

  /* Math: '<Root>/Transpose' */
  for (imgCol = 0; imgCol < 320; imgCol++) {
    for (imgRow = 0; imgRow < 100; imgRow++) {
      lanedetection_B.Transpose[imgRow + 100 * imgCol] =
        lanedetection_B.EdgeDetection[320 * imgRow + imgCol];
    }
  }

  /* End of Math: '<Root>/Transpose' */

  /* S-Function (svipfindlocalmax): '<Root>/Find Local Maxima' */
  imgRow = 0;
  done = false;
  for (i = 0; i < 120780; i++) {
    lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[i] =
      lanedetection_B.HoughTransform_o1[i];
  }

  lanedetection_B.FindLocalMaxima_o1[0] = 0U;
  lanedetection_B.FindLocalMaxima_o1[1] = 0U;
  while (!done) {
    imgCol = 0;
    maxValue = lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[0];
    for (i = 0; i < 120780; i++) {
      if (lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[i] > maxValue) {
        imgCol = i;
        maxValue = lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[i];
      }
    }

    p = imgCol % 671;
    i = imgCol / 671;
    if (lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[imgCol] >=
        lanedetection_P.FindLocalMaxima_threshold) {
      lanedetection_B.FindLocalMaxima_o1[imgRow] = (uint32_T)(1 + i);
      lanedetection_B.FindLocalMaxima_o1[1U + imgRow] = (uint32_T)(1 + p);
      imgRow++;
      if (imgRow == 1) {
        done = true;
      }

      imgIdx = p - 2;
      if (!(imgIdx > 0)) {
        imgIdx = 0;
      }

      p += 2;
      if (!(p < 670)) {
        p = 670;
      }

      imgCol = i - 3;
      q2 = i + 3;
      if (!((imgCol < 0) || (q2 > 179))) {
        while (imgCol <= q2) {
          jRowsIn = imgCol * 671;
          for (i = imgIdx; i <= p; i++) {
            lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[i + jRowsIn] = 0.0F;
          }

          imgCol++;
        }
      } else {
        if (imgCol < 0) {
          lanedetection_B.activeEdgeIdxBdy = imgCol;
          while (lanedetection_B.activeEdgeIdxBdy <= q2) {
            if (lanedetection_B.activeEdgeIdxBdy < 0) {
              jRowsIn = (lanedetection_B.activeEdgeIdxBdy + 180) * 671 + 670;
              for (i = imgIdx; i <= p; i++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[jRowsIn - i] =
                  0.0F;
              }
            } else {
              jRowsIn = lanedetection_B.activeEdgeIdxBdy * 671;
              for (i = imgIdx; i <= p; i++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[i + jRowsIn] =
                  0.0F;
              }
            }

            lanedetection_B.activeEdgeIdxBdy++;
          }
        }

        if (q2 > 179) {
          lanedetection_B.activeEdgeIdxBdy = imgCol;
          while (lanedetection_B.activeEdgeIdxBdy <= q2) {
            if (lanedetection_B.activeEdgeIdxBdy > 179) {
              jRowsIn = (lanedetection_B.activeEdgeIdxBdy - 180) * 671 + 670;
              for (i = imgIdx; i <= p; i++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[jRowsIn - i] =
                  0.0F;
              }
            } else {
              jRowsIn = lanedetection_B.activeEdgeIdxBdy * 671;
              for (i = imgIdx; i <= p; i++) {
                lanedetection_DW.FindLocalMaxima_TEMP_IN_DWORKS[i + jRowsIn] =
                  0.0F;
              }
            }

            lanedetection_B.activeEdgeIdxBdy++;
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
  imgCol = 0;
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

    imgCol = 1;
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
      lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
        (lanedetection_B.tmpRound + 0.5F);
    } else {
      lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)(lanedetection_B.tmpRound
        * 0.0F);
    }

    lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = 0;
    imgCol++;
  }

  /* part-3: Right vertical axis */
  if (imgCol < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - 99.0F) *
      (lanedetection_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <=
         319.0F)) {
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = 99;
      imgCol++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (imgCol < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_B.y2 * 319.0F) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 99.0F))
    {
      lanedetection_B.tmpOutRC[imgCol << 1] = 319;
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      imgCol++;
    }
  }

  if (imgCol < 2) {
    lanedetection_B.tmpOutRC[0U] = -1;
    lanedetection_B.tmpOutRC[1U] = -1;
    lanedetection_B.tmpOutRC[2U] = -1;
    lanedetection_B.tmpOutRC[3U] = -1;
  }

  lanedetection_B.HoughLines[0] = lanedetection_B.tmpOutRC[1] + 1;
  lanedetection_B.HoughLines[2] = lanedetection_B.tmpOutRC[0] + 1;
  lanedetection_B.HoughLines[4] = lanedetection_B.tmpOutRC[3] + 1;
  lanedetection_B.HoughLines[6] = lanedetection_B.tmpOutRC[2] + 1;
  imgCol = 0;
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

    imgCol = 1;
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
      lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
        (lanedetection_B.tmpRound + 0.5F);
    } else {
      lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)(lanedetection_B.tmpRound
        * 0.0F);
    }

    lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = 0;
    imgCol++;
  }

  /* part-3: Right vertical axis */
  if (imgCol < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - 99.0F) *
      (lanedetection_B.y2 / maxValue) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <=
         319.0F)) {
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[imgCol << 1] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = 99;
      imgCol++;
    }
  }

  /* part-4: bottom horizontal axis */
  if (imgCol < 2) {
    lanedetection_B.tmpRound = (real32_T)floor((maxValue - maxValue /
      lanedetection_B.y2 * 319.0F) + 0.5F);
    if ((lanedetection_B.tmpRound >= 0.0F) && (lanedetection_B.tmpRound <= 99.0F))
    {
      lanedetection_B.tmpOutRC[imgCol << 1] = 319;
      if (lanedetection_B.tmpRound >= 0.5F) {
        lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)(real32_T)floor
          (lanedetection_B.tmpRound + 0.5F);
      } else {
        lanedetection_B.tmpOutRC[1 + (imgCol << 1)] = (int32_T)
          (lanedetection_B.tmpRound * 0.0F);
      }

      imgCol++;
    }
  }

  if (imgCol < 2) {
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
    for (i = 0; i < 32000; i++) {
      lanedetection_B.DrawShapes_o1[i] = lanedetection_B.imgOUT[i];
      lanedetection_B.DrawShapes_o3[i] = lanedetection_B.Resize1[i];
      lanedetection_B.imgOUT[i] = lanedetection_B.Resize[i];
    }

    /* Update view port. */
    for (imgCol = 0; imgCol < 2; imgCol++) {
      p = lanedetection_B.HoughLines[imgCol + 2] - 1;
      jRowsIn = lanedetection_B.HoughLines[imgCol] - 1;
      if ((lanedetection_B.HoughLines[imgCol + 6] - 1 != p) ||
          (lanedetection_B.HoughLines[4 + imgCol] - 1 != jRowsIn)) {
        isMore = false;
        p = (p << 3) + 4;
        lanedetection_B.k = ((lanedetection_B.HoughLines[imgCol + 6] - 1) << 3)
          + 4;
        jRowsIn = (jRowsIn << 3) + 4;
        acc1_idx_5 = ((lanedetection_B.HoughLines[4 + imgCol] - 1) << 3) + 4;

        /* Find the visible portion of a line. */
        prevEdgeIsVertical = false;
        visited2 = false;
        done = false;
        imgRow = p;
        i = jRowsIn;
        imgIdx = lanedetection_B.k;
        q2 = acc1_idx_5;
        while (!done) {
          lanedetection_B.numUniquePix = 0;
          lanedetection_B.loc = 0;

          /* Determine viewport violations. */
          if (imgRow < 0) {
            lanedetection_B.numUniquePix = 4;
          } else {
            if (imgRow > 2559) {
              lanedetection_B.numUniquePix = 8;
            }
          }

          if (imgIdx < 0) {
            lanedetection_B.loc = 4;
          } else {
            if (imgIdx > 2559) {
              lanedetection_B.loc = 8;
            }
          }

          if (i < 0) {
            lanedetection_B.numUniquePix |= 1U;
          } else {
            if (i > 799) {
              lanedetection_B.numUniquePix |= 2U;
            }
          }

          if (q2 < 0) {
            lanedetection_B.loc |= 1U;
          } else {
            if (q2 > 799) {
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
              imgRow = p;
              i = jRowsIn;
            }

            lanedetection_B.idxCol1 = imgIdx - imgRow;
            lanedetection_B.idxCol2 = q2 - i;
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
              lanedetection_B.numUniquePix = -imgRow * lanedetection_B.idxCol2;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol1 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol1 < 0))) {
                i += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                    lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                i -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                    lanedetection_B.idxCol1) + 1) >> 1;
              }

              imgRow = 0;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_B.numUniquePix & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_B.numUniquePix = (2559 - imgRow) *
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
                i += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                    lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                i -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                    lanedetection_B.idxCol1) + 1) >> 1;
              }

              imgRow = 2559;
              prevEdgeIsVertical = true;
            } else if ((lanedetection_B.numUniquePix & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_B.numUniquePix = -i * lanedetection_B.idxCol1;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol2 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol2 < 0))) {
                imgRow += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                imgRow -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              }

              i = 0;
              prevEdgeIsVertical = true;
            } else {
              /* Violated CMax. */
              lanedetection_B.numUniquePix = (799 - i) * lanedetection_B.idxCol1;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol2 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol2 < 0))) {
                imgRow += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                imgRow -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              }

              i = 799;
              prevEdgeIsVertical = true;
            }
          } else {
            /* Clip the 2nd point. */
            if (visited2) {
              imgIdx = lanedetection_B.k;
              q2 = acc1_idx_5;
            }

            lanedetection_B.idxCol1 = imgIdx - imgRow;
            lanedetection_B.idxCol2 = q2 - i;
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
              lanedetection_B.numUniquePix = -imgIdx * lanedetection_B.idxCol2;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol1 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol1 < 0))) {
                q2 += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                q2 -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              }

              imgIdx = 0;
              visited2 = true;
            } else if ((lanedetection_B.loc & 8U) != 0U) {
              /* Violated RMax. */
              lanedetection_B.numUniquePix = (2559 - imgIdx) *
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
                q2 += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              } else {
                q2 -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                                     lanedetection_B.idxCol1) + 1) >> 1;
              }

              imgIdx = 2559;
              visited2 = true;
            } else if ((lanedetection_B.loc & 1U) != 0U) {
              /* Violated CMin. */
              lanedetection_B.numUniquePix = -q2 * lanedetection_B.idxCol1;
              if ((lanedetection_B.numUniquePix > 1073741824) ||
                  (lanedetection_B.numUniquePix < -1073741824)) {
                /* Check for Inf or Nan. */
                done = true;
                isMore = false;
              } else if (((lanedetection_B.numUniquePix >= 0) &&
                          (lanedetection_B.idxCol2 >= 0)) ||
                         ((lanedetection_B.numUniquePix < 0) &&
                          (lanedetection_B.idxCol2 < 0))) {
                imgIdx += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              }

              q2 = 0;
              visited2 = true;
            } else {
              /* Violated CMax. */
              lanedetection_B.numUniquePix = (799 - q2) *
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
                imgIdx += (div_s32_floor(lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              } else {
                imgIdx -= (div_s32_floor(-lanedetection_B.numUniquePix << 1,
                            lanedetection_B.idxCol2) + 1) >> 1;
              }

              q2 = 799;
              visited2 = true;
            }
          }
        }

        if (isMore) {
          /* Initialize the Bresenham algorithm. */
          if (imgIdx >= imgRow) {
            lanedetection_B.k = imgIdx - imgRow;
          } else {
            lanedetection_B.k = imgRow - imgIdx;
          }

          if (q2 >= i) {
            acc1_idx_5 = q2 - i;
          } else {
            acc1_idx_5 = i - q2;
          }

          if (lanedetection_B.k > acc1_idx_5) {
            p = 1;
            jRowsIn = 320;
          } else {
            p = 320;
            jRowsIn = 1;
            lanedetection_B.k = imgRow;
            imgRow = i;
            i = lanedetection_B.k;
            lanedetection_B.k = imgIdx;
            imgIdx = q2;
            q2 = lanedetection_B.k;
          }

          if (imgRow > imgIdx) {
            lanedetection_B.k = imgRow;
            imgRow = imgIdx;
            imgIdx = lanedetection_B.k;
            lanedetection_B.k = i;
            i = q2;
            q2 = lanedetection_B.k;
          }

          lanedetection_B.k = imgIdx - imgRow;
          if (i <= q2) {
            acc1_idx_5 = 1;
            lanedetection_B.idxCol1 = q2 - i;
          } else {
            acc1_idx_5 = -1;
            lanedetection_B.idxCol1 = i - q2;
          }

          lanedetection_B.idxCol2 = i - 4;
          lanedetection_B.numUniquePix = -((lanedetection_B.k + 1) >> 1);
          if (p != 1) {
            lanedetection_B.loc = 2559;
          } else {
            lanedetection_B.loc = 799;
          }

          lanedetection_B.loc_m = imgRow >> 3;
          lanedetection_B.col = ((lanedetection_B.loc_m + 1) << 3) - imgRow;
          lanedetection_B.idxRow2 = 320;
          lanedetection_B.idxTmp = 0;
          memset(&lanedetection_DW.DrawShapes_DW_PixCount[0], 0, 320U * sizeof
                 (uint8_T));
          done = (imgRow <= imgIdx);
          while (done) {
            lanedetection_B.col--;
            lanedetection_B.lastRow = lanedetection_B.idxCol2;

            /* Compute the next location using Bresenham algorithm. */
            /* Move to the next sub-pixel location. */
            lanedetection_B.numUniquePix += lanedetection_B.idxCol1;
            if (lanedetection_B.numUniquePix >= 0) {
              lanedetection_B.idxCol2 += acc1_idx_5;
              lanedetection_B.numUniquePix -= lanedetection_B.k;
            }

            imgRow++;
            done = (imgRow <= imgIdx);
            if (done) {
              lanedetection_B.activeEdgeIdxBdy = lanedetection_B.lastRow + 7;
              if ((lanedetection_B.lastRow + 7 > 0) && (lanedetection_B.lastRow <
                   lanedetection_B.loc)) {
                if (lanedetection_B.lastRow < 0) {
                  lanedetection_B.lastRow = 0;
                }

                if (lanedetection_B.activeEdgeIdxBdy > lanedetection_B.loc) {
                  lanedetection_B.activeEdgeIdxBdy = lanedetection_B.loc;
                }

                q2 = lanedetection_B.lastRow >> 3;
                i = lanedetection_B.activeEdgeIdxBdy >> 3;
                if (lanedetection_B.idxRow2 > q2) {
                  lanedetection_B.idxRow2 = q2;
                }

                if (lanedetection_B.idxTmp < i) {
                  lanedetection_B.idxTmp = i;
                }

                if (i > q2) {
                  lanedetection_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                    (((uint32_T)((q2 + 1) << 3) +
                      lanedetection_DW.DrawShapes_DW_PixCount[q2]) -
                     lanedetection_B.lastRow);
                  lanedetection_DW.DrawShapes_DW_PixCount[i] = (uint8_T)
                    (((uint32_T)(lanedetection_B.activeEdgeIdxBdy - (i << 3)) +
                      lanedetection_DW.DrawShapes_DW_PixCount[i]) + 1U);
                  for (q2++; q2 < i; q2++) {
                    lanedetection_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                      (lanedetection_DW.DrawShapes_DW_PixCount[q2] + 8U);
                  }
                } else {
                  if (i == q2) {
                    lanedetection_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                      (((uint32_T)(lanedetection_B.activeEdgeIdxBdy -
                                   lanedetection_B.lastRow) +
                        lanedetection_DW.DrawShapes_DW_PixCount[q2]) + 1U);
                  }
                }
              }
            }

            if ((lanedetection_B.col == 0) || (!done)) {
              while (lanedetection_B.idxRow2 <= lanedetection_B.idxTmp) {
                i = lanedetection_B.loc_m * p + lanedetection_B.idxRow2 *
                  jRowsIn;
                if (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_B.idxRow2]
                    == 64) {
                  lanedetection_B.DrawShapes_o1[i] = (uint8_T)
                    ((((lanedetection_P.DrawShapes_color[0] << 14) -
                       (lanedetection_B.DrawShapes_o1[i] << 14)) +
                      (lanedetection_B.DrawShapes_o1[i] << 14)) >> 14);
                  lanedetection_B.imgOUT[i] = (uint8_T)
                    ((((lanedetection_P.DrawShapes_color[1] << 14) -
                       (lanedetection_B.imgOUT[i] << 14)) +
                      (lanedetection_B.imgOUT[i] << 14)) >> 14);
                  lanedetection_B.DrawShapes_o3[i] = (uint8_T)
                    ((((lanedetection_P.DrawShapes_color[2] << 14) -
                       (lanedetection_B.DrawShapes_o3[i] << 14)) +
                      (lanedetection_B.DrawShapes_o3[i] << 14)) >> 14);
                } else {
                  lanedetection_B.DrawShapes_o1[i] = (uint8_T)
                    ((((((lanedetection_P.DrawShapes_color[0] << 14) -
                         (lanedetection_B.DrawShapes_o1[i] << 14)) *
                        lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_B.idxRow2])
                       >> 6) + (lanedetection_B.DrawShapes_o1[i] << 14)) >> 14);
                  lanedetection_B.imgOUT[i] = (uint8_T)
                    ((((((lanedetection_P.DrawShapes_color[1] << 14) -
                         (lanedetection_B.imgOUT[i] << 14)) *
                        lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_B.idxRow2])
                       >> 6) + (lanedetection_B.imgOUT[i] << 14)) >> 14);
                  lanedetection_B.DrawShapes_o3[i] = (uint8_T)
                    ((((((lanedetection_P.DrawShapes_color[2] << 14) -
                         (lanedetection_B.DrawShapes_o3[i] << 14)) *
                        lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_B.idxRow2])
                       >> 6) + (lanedetection_B.DrawShapes_o3[i] << 14)) >> 14);
                }

                lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_B.idxRow2]
                  = 0U;
                lanedetection_B.idxRow2++;
              }

              lanedetection_B.col = 8;
              lanedetection_B.idxRow2 = 320;
              lanedetection_B.idxTmp = 0;
              lanedetection_B.loc_m++;
            }
          }
        }
      }
    }
  } else {
    /* Compute output for non-unity line width
     */
    /* Copy the image from input to output. */
    for (i = 0; i < 32000; i++) {
      lanedetection_B.DrawShapes_o1[i] = lanedetection_B.imgOUT[i];
      lanedetection_B.DrawShapes_o3[i] = lanedetection_B.Resize1[i];
      lanedetection_B.imgOUT[i] = lanedetection_B.Resize[i];
    }

    /* Update view port. */
    /* ProcessStep-start-1
     */
    if (lanedetection_P.DrawShapes_lineWidth > 1) {
      /* convertLinePts2PolygonPts
       */
      imgRow = lanedetection_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      imgIdx = lanedetection_B.HoughLines[2] - lanedetection_B.HoughLines[6];
      p = lanedetection_B.HoughLines[0] - lanedetection_B.HoughLines[4];
      if (p == 0) {
        q2 = 0;
        i = 1;
        imgCol = ((lanedetection_B.HoughLines[0] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[0] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[2] - 1) << 14;
      } else if (imgIdx == 0) {
        i = 2;
        q2 = 0;
        imgCol = ((lanedetection_B.HoughLines[2] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[2] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[0] - 1) << 14;
      } else {
        i = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, p << 14, 14U);
        jRowsIn = ((lanedetection_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_B.HoughLines[0] - 1) << 14, q2, 14U);
        lanedetection_B.k = div_repeat_s32_floor(imgRow << 14,
          div_repeat_s32_floor(p << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgIdx *
          imgIdx + p * p) << 14) << 7, 14U), 14U);
        imgCol = jRowsIn + lanedetection_B.k;
        jRowsIn -= lanedetection_B.k;
        lanedetection_B.k = div_repeat_s32_floor((lanedetection_B.HoughLines[0]
          - 1) << 14, q2, 14U) + ((lanedetection_B.HoughLines[2] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (i == 1) {
        lanedetection_DW.DrawShapes_DW_Points[0] = ((imgCol & 8192U) != 0U) +
          (imgCol >> 14);
        lanedetection_DW.DrawShapes_DW_Points[2] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
        lanedetection_DW.DrawShapes_DW_Points[12] = ((jRowsIn & 8192U) != 0U) +
          (jRowsIn >> 14);
        lanedetection_DW.DrawShapes_DW_Points[14] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
      } else {
        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[0] = ((lanedetection_B.k & 8192U)
            != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[2] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[0] = ((acc1_idx_5 & 8192U) != 0U)
            + (acc1_idx_5 >> 14);
          imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_DW.DrawShapes_DW_Points[2] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        }

        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[12] = ((lanedetection_B.k &
            8192U) != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[14] = ((jRowsIn & 8192U) != 0U)
            + (jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            jRowsIn, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[12] = ((acc1_idx_5 & 8192U) !=
            0U) + (acc1_idx_5 >> 14);
          imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + jRowsIn;
          lanedetection_DW.DrawShapes_DW_Points[14] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
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
      if (p == 0) {
        q2 = 0;
        i = 1;
        imgCol = ((lanedetection_B.HoughLines[0] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[0] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[6] - 1) << 14;
      } else if (imgIdx == 0) {
        i = 2;
        q2 = 0;
        imgCol = ((lanedetection_B.HoughLines[2] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[2] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[4] - 1) << 14;
      } else {
        i = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, p << 14, 14U);
        jRowsIn = ((lanedetection_B.HoughLines[2] - 1) << 14) - mul_s32_loSR
          ((lanedetection_B.HoughLines[0] - 1) << 14, q2, 14U);
        lanedetection_B.k = div_repeat_s32_floor(imgRow << 14,
          div_repeat_s32_floor(p << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgIdx *
          imgIdx + p * p) << 14) << 7, 14U), 14U);
        imgCol = jRowsIn + lanedetection_B.k;
        jRowsIn -= lanedetection_B.k;
        lanedetection_B.k = div_repeat_s32_floor((lanedetection_B.HoughLines[4]
          - 1) << 14, q2, 14U) + ((lanedetection_B.HoughLines[6] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (i == 1) {
        lanedetection_DW.DrawShapes_DW_Points[4] = ((imgCol & 8192U) != 0U) +
          (imgCol >> 14);
        lanedetection_DW.DrawShapes_DW_Points[6] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
        lanedetection_DW.DrawShapes_DW_Points[8] = ((jRowsIn & 8192U) != 0U) +
          (jRowsIn >> 14);
        lanedetection_DW.DrawShapes_DW_Points[10] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
      } else {
        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[4] = ((lanedetection_B.k & 8192U)
            != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[6] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[4] = ((acc1_idx_5 & 8192U) != 0U)
            + (acc1_idx_5 >> 14);
          imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_DW.DrawShapes_DW_Points[6] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        }

        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[8] = ((lanedetection_B.k & 8192U)
            != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[10] = ((jRowsIn & 8192U) != 0U)
            + (jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            jRowsIn, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[8] = ((acc1_idx_5 & 8192U) != 0U)
            + (acc1_idx_5 >> 14);
          imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + jRowsIn;
          lanedetection_DW.DrawShapes_DW_Points[10] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      imgRow = lanedetection_P.DrawShapes_lineWidth >> 1;

      /* getLineParams-1
       */
      /* getLineParams-main fcn
       */
      imgIdx = lanedetection_B.HoughLines[3] - lanedetection_B.HoughLines[7];
      p = lanedetection_B.HoughLines[1] - lanedetection_B.HoughLines[5];
      if (p == 0) {
        q2 = 0;
        i = 1;
        imgCol = ((lanedetection_B.HoughLines[1] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[1] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[3] - 1) << 14;
      } else if (imgIdx == 0) {
        i = 2;
        q2 = 0;
        imgCol = ((lanedetection_B.HoughLines[3] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[3] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[1] - 1) << 14;
      } else {
        i = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, p << 14, 14U);
        jRowsIn = ((lanedetection_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_B.HoughLines[1] - 1) << 14, q2, 14U);
        lanedetection_B.k = div_repeat_s32_floor(imgRow << 14,
          div_repeat_s32_floor(p << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgIdx *
          imgIdx + p * p) << 14) << 7, 14U), 14U);
        imgCol = jRowsIn + lanedetection_B.k;
        jRowsIn -= lanedetection_B.k;
        lanedetection_B.k = div_repeat_s32_floor((lanedetection_B.HoughLines[1]
          - 1) << 14, q2, 14U) + ((lanedetection_B.HoughLines[3] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-1
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (i == 1) {
        lanedetection_DW.DrawShapes_DW_Points[1] = ((imgCol & 8192U) != 0U) +
          (imgCol >> 14);
        lanedetection_DW.DrawShapes_DW_Points[3] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
        lanedetection_DW.DrawShapes_DW_Points[13] = ((jRowsIn & 8192U) != 0U) +
          (jRowsIn >> 14);
        lanedetection_DW.DrawShapes_DW_Points[15] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
      } else {
        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[1] = ((lanedetection_B.k & 8192U)
            != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[3] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[1] = ((acc1_idx_5 & 8192U) != 0U)
            + (acc1_idx_5 >> 14);
          imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_DW.DrawShapes_DW_Points[3] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        }

        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[13] = ((lanedetection_B.k &
            8192U) != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[15] = ((jRowsIn & 8192U) != 0U)
            + (jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            jRowsIn, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[13] = ((acc1_idx_5 & 8192U) !=
            0U) + (acc1_idx_5 >> 14);
          imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + jRowsIn;
          lanedetection_DW.DrawShapes_DW_Points[15] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
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
      if (p == 0) {
        q2 = 0;
        i = 1;
        imgCol = ((lanedetection_B.HoughLines[1] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[1] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[7] - 1) << 14;
      } else if (imgIdx == 0) {
        i = 2;
        q2 = 0;
        imgCol = ((lanedetection_B.HoughLines[3] - imgRow) - 1) << 14;
        jRowsIn = ((lanedetection_B.HoughLines[3] + imgRow) - 1) << 14;
        lanedetection_B.k = (lanedetection_B.HoughLines[5] - 1) << 14;
      } else {
        i = 0;
        q2 = div_repeat_s32_floor(imgIdx << 14, p << 14, 14U);
        jRowsIn = ((lanedetection_B.HoughLines[3] - 1) << 14) - mul_s32_loSR
          ((lanedetection_B.HoughLines[1] - 1) << 14, q2, 14U);
        lanedetection_B.k = div_repeat_s32_floor(imgRow << 14,
          div_repeat_s32_floor(p << 14, rt_sqrt_Us32En14_Ys16E_tOJnWsQ0((imgIdx *
          imgIdx + p * p) << 14) << 7, 14U), 14U);
        imgCol = jRowsIn + lanedetection_B.k;
        jRowsIn -= lanedetection_B.k;
        lanedetection_B.k = div_repeat_s32_floor((lanedetection_B.HoughLines[5]
          - 1) << 14, q2, 14U) + ((lanedetection_B.HoughLines[7] - 1) << 14);
      }

      /* findPointOfIntersectionNormal-3
       */
      /* findPointOfIntersectionNormal- main fcn
       */
      if (i == 1) {
        lanedetection_DW.DrawShapes_DW_Points[5] = ((imgCol & 8192U) != 0U) +
          (imgCol >> 14);
        lanedetection_DW.DrawShapes_DW_Points[7] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
        lanedetection_DW.DrawShapes_DW_Points[9] = ((jRowsIn & 8192U) != 0U) +
          (jRowsIn >> 14);
        lanedetection_DW.DrawShapes_DW_Points[11] = ((lanedetection_B.k & 8192U)
          != 0U) + (lanedetection_B.k >> 14);
      } else {
        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[5] = ((lanedetection_B.k & 8192U)
            != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[7] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            imgCol, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[5] = ((acc1_idx_5 & 8192U) != 0U)
            + (acc1_idx_5 >> 14);
          imgCol += mul_s32_loSR(q2, acc1_idx_5, 14U);
          lanedetection_DW.DrawShapes_DW_Points[7] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        }

        if (i == 2) {
          lanedetection_DW.DrawShapes_DW_Points[9] = ((lanedetection_B.k & 8192U)
            != 0U) + (lanedetection_B.k >> 14);
          lanedetection_DW.DrawShapes_DW_Points[11] = ((jRowsIn & 8192U) != 0U)
            + (jRowsIn >> 14);
        } else {
          acc1_idx_5 = div_repeat_s32_floor(mul_s32_loSR(lanedetection_B.k -
            jRowsIn, q2, 14U), mul_s32_loSR(q2, q2, 14U) + 16384, 14U);
          lanedetection_DW.DrawShapes_DW_Points[9] = ((acc1_idx_5 & 8192U) != 0U)
            + (acc1_idx_5 >> 14);
          imgCol = mul_s32_loSR(q2, acc1_idx_5, 14U) + jRowsIn;
          lanedetection_DW.DrawShapes_DW_Points[11] = ((imgCol & 8192U) != 0U) +
            (imgCol >> 14);
        }
      }

      /* findPointOfIntersectionNormal-4
       */
      /* findPointOfIntersectionNormal- main fcn
       */
    }

    /* ProcessStep-after poly points-1
     */
    imgCol = 2;

    /* just before call for cgpolygon
     */
    if (lanedetection_P.DrawShapes_lineWidth > 1) {
      /* just before call for cgpolygon-2
       */
      imgCol = 4;
    }

    imgRow = imgCol << 1;
    memset(&lanedetection_DW.DrawShapes_DW_PixCount[0], 0, 320U * sizeof(uint8_T));

    /* Reset scanline states. */
    imgIdx = 0;
    p = 0;
    idxTmpArray[0U] = (int8_T)(imgCol - 1);
    isMore = true;
    while (isMore) {
      /* Initialize the scanline. */
      /* Convert polygon vertices to boundaries. */
      q2 = 0;
      jRowsIn = imgIdx;
      lanedetection_B.k = imgIdx;

      /* start for loop
       */
      acc1_idx_5 = (((idxTmpArray[0] << 1) + 1) << 1) + p;
      lanedetection_B.idxCol1 = (idxTmpArray[0] << 2) + p;
      lanedetection_B.idxTmp = idxTmpArray[0];
      lanedetection_B.idxCol2 = ((idxTmpArray[0] - 1) << 2) + p;
      lanedetection_B.numUniquePix = imgCol;
      if (lanedetection_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_B.loc =
          lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];

        /* getLoc-1
         */
        i = lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];
      } else {
        /* getLoc-2
         */
        lanedetection_B.loc = lanedetection_B.HoughLines[lanedetection_B.idxCol1];

        /* getLoc-2
         */
        i = lanedetection_B.HoughLines[lanedetection_B.idxCol2];
      }

      while ((lanedetection_B.idxCol2 >= 0) && (lanedetection_B.loc - 1 == i - 1))
      {
        lanedetection_B.idxTmp--;
        lanedetection_B.idxCol2 = ((lanedetection_B.idxTmp - 1) << 2) + p;
        lanedetection_B.numUniquePix--;
        if (lanedetection_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          i = lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];
        } else {
          /* getLoc-2
           */
          i = lanedetection_B.HoughLines[lanedetection_B.idxCol2];
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
      lanedetection_B.idxRow2 = 2 + p;
      lanedetection_B.idxCol2 = p;
      prevEdgeIsVertical = false;
      if (lanedetection_P.DrawShapes_lineWidth > 1) {
        /* getLoc-1
         */
        lanedetection_B.loc = lanedetection_DW.DrawShapes_DW_Points[p];

        /* getLoc-1
         */
        lanedetection_B.loc_m =
          lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];
      } else {
        /* getLoc-2
         */
        lanedetection_B.loc = lanedetection_B.HoughLines[p];

        /* getLoc-2
         */
        lanedetection_B.loc_m =
          lanedetection_B.HoughLines[lanedetection_B.idxCol1];
      }

      for (i = 0; i < lanedetection_B.numUniquePix; i++) {
        if (lanedetection_P.DrawShapes_lineWidth > 1) {
          /* getLoc-1
           */
          lanedetection_B.col =
            lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];

          /* getLoc-1
           */
          lanedetection_B.activeEdgeIdxBdy =
            lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];
        } else {
          /* getLoc-2
           */
          lanedetection_B.col =
            lanedetection_B.HoughLines[lanedetection_B.idxCol2];

          /* getLoc-2
           */
          lanedetection_B.activeEdgeIdxBdy =
            lanedetection_B.HoughLines[lanedetection_B.idxCol1];
        }

        if (lanedetection_B.activeEdgeIdxBdy - 1 != lanedetection_B.col - 1) {
          if (lanedetection_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_B.col =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_B.activeEdgeIdxBdy =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];
          } else {
            /* getLoc-2
             */
            lanedetection_B.col =
              lanedetection_B.HoughLines[lanedetection_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_B.activeEdgeIdxBdy =
              lanedetection_B.HoughLines[lanedetection_B.idxCol1];
          }

          if (lanedetection_B.activeEdgeIdxBdy - 1 < lanedetection_B.col - 1) {
            isMore = false;
          } else {
            isMore = true;
            lanedetection_B.idxTmp = acc1_idx_5;
            acc1_idx_5 = lanedetection_B.idxRow2;
            lanedetection_B.idxRow2 = lanedetection_B.idxTmp;
            lanedetection_B.idxTmp = lanedetection_B.idxCol1;
            lanedetection_B.idxCol1 = lanedetection_B.idxCol2;
            lanedetection_B.idxCol2 = lanedetection_B.idxTmp;
          }

          if (lanedetection_P.DrawShapes_lineWidth > 1) {
            /* getLoc-1
             */
            lanedetection_B.col =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol2];

            /* getLoc-1
             */
            lanedetection_B.activeEdgeIdxBdy =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxRow2];

            /* getLoc-1
             */
            lanedetection_B.lastRow =
              lanedetection_DW.DrawShapes_DW_Points[lanedetection_B.idxCol1];

            /* getLoc-1
             */
            lanedetection_B.idxTmp =
              lanedetection_DW.DrawShapes_DW_Points[acc1_idx_5];
          } else {
            /* getLoc-2
             */
            lanedetection_B.col =
              lanedetection_B.HoughLines[lanedetection_B.idxCol2];

            /* getLoc-2
             */
            lanedetection_B.activeEdgeIdxBdy =
              lanedetection_B.HoughLines[lanedetection_B.idxRow2];

            /* getLoc-2
             */
            lanedetection_B.lastRow =
              lanedetection_B.HoughLines[lanedetection_B.idxCol1];

            /* getLoc-2
             */
            lanedetection_B.idxTmp = lanedetection_B.HoughLines[acc1_idx_5];
          }

          /* Initialize a Bresenham line. */
          lanedetection_B.idxTmp = ((lanedetection_B.idxTmp - 1) << 3) + 4;
          lanedetection_B.lastRow = ((lanedetection_B.lastRow - 1) << 3) + 4;
          lanedetection_B.activeEdgeIdxBdy = ((lanedetection_B.activeEdgeIdxBdy
            - 1) << 3) + 4;
          lanedetection_B.col = ((lanedetection_B.col - 1) << 3) + 4;
          lanedetection_B.firstRow = lanedetection_B.col -
            lanedetection_B.lastRow;
          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k] = 0;
          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 1] =
            lanedetection_B.idxTmp;
          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 2] =
            lanedetection_B.lastRow;
          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 3] =
            lanedetection_B.col;
          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 6] = 0;
          if (lanedetection_B.activeEdgeIdxBdy >= lanedetection_B.idxTmp) {
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 8] =
              lanedetection_B.activeEdgeIdxBdy - lanedetection_B.idxTmp;
          } else {
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 8] =
              lanedetection_B.idxTmp - lanedetection_B.activeEdgeIdxBdy;
          }

          while (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 8] >=
                 0) {
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 6]++;
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 8] -=
              lanedetection_B.firstRow;
          }

          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 5] =
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 6] - 1;
          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 7] =
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 8] +
            lanedetection_B.firstRow;
          lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 4] =
            lanedetection_B.firstRow -
            (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 7] << 1);
          if (lanedetection_B.idxTmp > lanedetection_B.activeEdgeIdxBdy) {
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 5] =
              -lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 5];
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 6] =
              -lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 6];
          }

          if ((!done) && (!isMore)) {
            /* Use Bresenham algorithm to calculate the polygon boundaries at the next column */
            lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 2]++;
            if ((lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k] << 1)
                > lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 4])
            {
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k] +=
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 8];
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 1] +=
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 6];
            } else {
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k] +=
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 7];
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 1] +=
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 5];
            }
          } else {
            if (done && isMore) {
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 3]--;
            }
          }

          done = isMore;
          if (!prevEdgeIsVertical) {
            /* Merge two Bresenham lines. */
            prevEdgeIsVertical = false;
            if ((jRowsIn != lanedetection_B.k) &&
                ((lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 5] ==
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 5])
                 && (lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 6] ==
                     lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k +
                     6]) && (lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 7]
                             ==
                             lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k
                             + 7]) &&
                 (lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 8] ==
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 8])))
            {
              if (lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 3] + 1 ==
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 2])
              {
                lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 3] =
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 3];
                prevEdgeIsVertical = true;
              } else {
                if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 3]
                    + 1 == lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 2])
                {
                  lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 1] =
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 1];
                  lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 2] =
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 2];
                  prevEdgeIsVertical = true;
                }
              }
            }

            if (!prevEdgeIsVertical) {
              jRowsIn = lanedetection_B.k;
              q2++;
            }
          } else {
            jRowsIn = lanedetection_B.k;
            q2++;
          }

          lanedetection_B.k = jRowsIn + 9;
          if (!isMore) {
            acc1_idx_5 = lanedetection_B.idxRow2;
            lanedetection_B.idxCol1 = lanedetection_B.idxCol2;
          }

          lanedetection_B.idxRow2 = acc1_idx_5 + 4;
          lanedetection_B.idxCol2 = lanedetection_B.idxCol1 + 4;
          prevEdgeIsVertical = false;
        } else {
          prevEdgeIsVertical = true;
          acc1_idx_5 = lanedetection_B.idxRow2;
          lanedetection_B.idxCol1 = lanedetection_B.idxCol2;
          lanedetection_B.idxRow2 += 4;
          lanedetection_B.idxCol2 += 4;
        }
      }

      if (!(lanedetection_B.loc_m - 1 == lanedetection_B.loc - 1)) {
        /* Merge two Bresenham lines. */
        done = false;
        if ((imgIdx != jRowsIn) &&
            ((lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 5] ==
              lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 5]) &&
             (lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 6] ==
              lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 6]) &&
             (lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 7] ==
              lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 7]) &&
             (lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 8] ==
              lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 8]))) {
          if (lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 3] + 1 ==
              lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 2]) {
            lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 3] =
              lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 3];
            done = true;
          } else {
            if (lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 3] + 1 ==
                lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 2]) {
              lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 1] =
                lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 1];
              lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 2] =
                lanedetection_DW.DrawShapes_DW_Polygon[jRowsIn + 2];
              done = true;
            }
          }
        }

        if (done) {
          q2--;
          lanedetection_B.k -= 9;
        }
      }

      /* Set all other edges to invalid. */
      for (i = q2; i < imgCol; i++) {
        lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 2] = 1;
        lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.k + 3] = 0;
        lanedetection_B.k += 9;
      }

      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_B.idxNew = imgIdx;
        lanedetection_B.idxOld = imgIdx + 9;
        isMore = false;
        for (i = 1; i < q2; i++) {
          if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew + 2]
              > lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
              2]) {
            isMore = true;
            for (lanedetection_B.activeEdgeIdxBdy = 0;
                 lanedetection_B.activeEdgeIdxBdy < 9;
                 lanedetection_B.activeEdgeIdxBdy++) {
              edgeTmp_tmp = lanedetection_B.idxNew +
                lanedetection_B.activeEdgeIdxBdy;
              lanedetection_B.edgeTmp =
                lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_B.idxOld +
                lanedetection_B.activeEdgeIdxBdy;
              lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp] =
                lanedetection_B.edgeTmp;
            }
          }

          lanedetection_B.idxNew = lanedetection_B.idxOld;
          lanedetection_B.idxOld += 9;
        }
      }

      /* Find out the last column of the polygon. */
      acc1_idx_5 = imgIdx + 3;
      jRowsIn = lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 3];
      for (i = 1; i < q2; i++) {
        acc1_idx_5 += 9;
        if (jRowsIn < lanedetection_DW.DrawShapes_DW_Polygon[acc1_idx_5]) {
          jRowsIn = lanedetection_DW.DrawShapes_DW_Polygon[acc1_idx_5];
        }
      }

      lanedetection_B.k = jRowsIn;
      if (jRowsIn > 799) {
        lanedetection_B.k = 799;
      }

      /* Find out the first column of the polygon. */
      acc1_idx_5 = imgIdx + 2;
      jRowsIn = lanedetection_DW.DrawShapes_DW_Polygon[imgIdx + 2];
      for (i = 1; i < q2; i++) {
        acc1_idx_5 += 9;
        if (jRowsIn > lanedetection_DW.DrawShapes_DW_Polygon[acc1_idx_5]) {
          jRowsIn = lanedetection_DW.DrawShapes_DW_Polygon[acc1_idx_5];
        }
      }

      if (jRowsIn < 0) {
        jRowsIn = 0;
      }

      /* Move to the next column and find out boundaries of the polygon at this column. */
      lanedetection_B.idxNew = imgIdx;
      lanedetection_B.idxOld = imgIdx;
      acc1_idx_5 = imgIdx;
      lanedetection_B.idxCol1 = 0;
      lanedetection_B.numActiveEdge = 0;
      for (i = 0; i < q2; i++) {
        /* Find out the valid boundaries and bring them to the latest column. */
        if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld + 3] >=
            jRowsIn) {
          if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld + 2]
              <= jRowsIn) {
            while (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                   + 2] < jRowsIn) {
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

            acc1_idx_5 += 9;
            lanedetection_B.numActiveEdge++;
          }

          if (lanedetection_B.idxOld != lanedetection_B.idxNew) {
            for (lanedetection_B.activeEdgeIdxBdy = 0;
                 lanedetection_B.activeEdgeIdxBdy < 9;
                 lanedetection_B.activeEdgeIdxBdy++) {
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew +
                lanedetection_B.activeEdgeIdxBdy] =
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
                lanedetection_B.activeEdgeIdxBdy];
            }
          }

          lanedetection_B.idxNew += 9;
          lanedetection_B.idxCol1++;
        }

        lanedetection_B.idxOld += 9;
      }

      /* Sort the boundaries of the polygon according to row values. */
      /* Sort the boundaries of the polygon. */
      isMore = true;
      while (isMore) {
        lanedetection_B.idxNew = imgIdx;
        lanedetection_B.idxOld = imgIdx + 9;
        isMore = false;
        for (i = 1; i < lanedetection_B.numActiveEdge; i++) {
          if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew + 1]
              > lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld +
              1]) {
            isMore = true;
            for (lanedetection_B.activeEdgeIdxBdy = 0;
                 lanedetection_B.activeEdgeIdxBdy < 9;
                 lanedetection_B.activeEdgeIdxBdy++) {
              edgeTmp_tmp = lanedetection_B.idxNew +
                lanedetection_B.activeEdgeIdxBdy;
              lanedetection_B.edgeTmp =
                lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
              DrawShapes_DW_Polygon_tmp = lanedetection_B.idxOld +
                lanedetection_B.activeEdgeIdxBdy;
              lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
              lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp] =
                lanedetection_B.edgeTmp;
            }
          }

          lanedetection_B.idxNew = lanedetection_B.idxOld;
          lanedetection_B.idxOld += 9;
        }
      }

      lanedetection_B.activeEdgeIdxBdy = imgIdx;
      lanedetection_B.idxCol2 = jRowsIn + 1;
      lanedetection_B.numUniquePix = 0;
      lanedetection_B.numActiveEdge = 0;
      lanedetection_B.idxNew = -1;
      lanedetection_B.loc = jRowsIn >> 3;
      lanedetection_B.loc_m = (lanedetection_B.loc + 1) << 3;
      lanedetection_B.idxRow2 = 320;
      lanedetection_B.idxTmp = 0;
      isMore = (0 <= lanedetection_B.k);
      while (isMore) {
        /* Get a string of pixels */
        prevEdgeIsVertical = false;
        done = (lanedetection_B.numActiveEdge != 0);
        lanedetection_B.col = lanedetection_B.numUniquePix;
        if ((lanedetection_B.numUniquePix >= jRowsIn) &&
            (lanedetection_B.numUniquePix <= lanedetection_B.k)) {
          if (lanedetection_B.activeEdgeIdxBdy < acc1_idx_5) {
            i =
              lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.activeEdgeIdxBdy
              + 1];
            lanedetection_B.activeEdgeIdxBdy += 9;
            if ((i == lanedetection_B.idxNew) &&
                (lanedetection_B.activeEdgeIdxBdy < acc1_idx_5)) {
              q2 =
                lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.activeEdgeIdxBdy
                + 1];
              isMore = (lanedetection_B.activeEdgeIdxBdy < acc1_idx_5);
              while (isMore && (i == q2)) {
                prevEdgeIsVertical = true;
                i =
                  lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.activeEdgeIdxBdy
                  + 1];
                lanedetection_B.activeEdgeIdxBdy += 9;
                isMore = (lanedetection_B.activeEdgeIdxBdy < acc1_idx_5);
                if (isMore) {
                  q2 =
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.activeEdgeIdxBdy
                    + 1];
                }
              }

              if (!isMore) {
                prevEdgeIsVertical = false;
              }
            }

            if (lanedetection_B.numActiveEdge != 0) {
              lanedetection_B.firstRow = lanedetection_B.idxNew;
              if (i <= 2559) {
                lanedetection_B.lastRow = i;
                lanedetection_B.idxNew = i;
              } else {
                lanedetection_B.lastRow = 2559;
                lanedetection_B.idxNew = 2559;
              }
            } else {
              lanedetection_B.firstRow = lanedetection_B.idxNew + 1;
              if ((i > 0) && (i <= 2559)) {
                lanedetection_B.lastRow = i - 1;
                lanedetection_B.idxNew = i;
              } else if (i <= 0) {
                lanedetection_B.lastRow = -1;
                lanedetection_B.idxNew = 0;
              } else {
                lanedetection_B.lastRow = 2559;
                lanedetection_B.idxNew = 2560;
              }
            }

            if (!prevEdgeIsVertical) {
              lanedetection_B.numActiveEdge = !(lanedetection_B.numActiveEdge !=
                0);
            }
          } else {
            /* Reset states and move to the next column. */
            done = false;
            lanedetection_B.firstRow = lanedetection_B.idxNew + 1;
            lanedetection_B.lastRow = 2559;

            /* Move to the next column and find out boundaries of the polygon at this column. */
            lanedetection_B.idxNew = imgIdx;
            lanedetection_B.idxOld = imgIdx;
            acc1_idx_5 = imgIdx;
            q2 = 0;
            lanedetection_B.numActiveEdge = 0;
            for (i = 0; i < lanedetection_B.idxCol1; i++) {
              /* Find out the valid boundaries and bring them to the latest column. */
              if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                  + 3] >= lanedetection_B.idxCol2) {
                if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                    + 2] <= lanedetection_B.idxCol2) {
                  while
                      (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                       + 2] < lanedetection_B.idxCol2) {
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

                  acc1_idx_5 += 9;
                  lanedetection_B.numActiveEdge++;
                }

                if (lanedetection_B.idxOld != lanedetection_B.idxNew) {
                  for (lanedetection_B.activeEdgeIdxBdy = 0;
                       lanedetection_B.activeEdgeIdxBdy < 9;
                       lanedetection_B.activeEdgeIdxBdy++) {
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew
                      + lanedetection_B.activeEdgeIdxBdy] =
                      lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                      + lanedetection_B.activeEdgeIdxBdy];
                  }
                }

                lanedetection_B.idxNew += 9;
                q2++;
              }

              lanedetection_B.idxOld += 9;
            }

            lanedetection_B.idxCol1 = q2;

            /* Sort the boundaries of the polygon according to row values. */
            /* Sort the boundaries of the polygon. */
            isMore = true;
            while (isMore) {
              lanedetection_B.idxNew = imgIdx;
              lanedetection_B.idxOld = imgIdx + 9;
              isMore = false;
              for (i = 1; i < lanedetection_B.numActiveEdge; i++) {
                if (lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxNew
                    + 1] >
                    lanedetection_DW.DrawShapes_DW_Polygon[lanedetection_B.idxOld
                    + 1]) {
                  isMore = true;
                  for (lanedetection_B.activeEdgeIdxBdy = 0;
                       lanedetection_B.activeEdgeIdxBdy < 9;
                       lanedetection_B.activeEdgeIdxBdy++) {
                    edgeTmp_tmp = lanedetection_B.idxNew +
                      lanedetection_B.activeEdgeIdxBdy;
                    lanedetection_B.edgeTmp =
                      lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp];
                    DrawShapes_DW_Polygon_tmp = lanedetection_B.idxOld +
                      lanedetection_B.activeEdgeIdxBdy;
                    lanedetection_DW.DrawShapes_DW_Polygon[edgeTmp_tmp] =
                      lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp];
                    lanedetection_DW.DrawShapes_DW_Polygon[DrawShapes_DW_Polygon_tmp]
                      = lanedetection_B.edgeTmp;
                  }
                }

                lanedetection_B.idxNew = lanedetection_B.idxOld;
                lanedetection_B.idxOld += 9;
              }
            }

            lanedetection_B.activeEdgeIdxBdy = imgIdx;
            lanedetection_B.idxCol2++;
            lanedetection_B.numActiveEdge = 0;
            lanedetection_B.idxNew = -1;
            lanedetection_B.numUniquePix++;
          }
        } else {
          lanedetection_B.firstRow = 0;
          lanedetection_B.lastRow = 2559;
          lanedetection_B.numUniquePix++;
        }

        if (lanedetection_B.firstRow < 0) {
          lanedetection_B.firstRow = 0;
        }

        if (lanedetection_B.lastRow < lanedetection_B.firstRow) {
          lanedetection_B.lastRow = lanedetection_B.firstRow - 1;
        }

        if (done && ((lanedetection_B.lastRow > 0) && (lanedetection_B.firstRow <
              2559))) {
          if (lanedetection_B.lastRow > 2559) {
            lanedetection_B.lastRow = 2559;
          }

          q2 = lanedetection_B.firstRow >> 3;
          i = lanedetection_B.lastRow >> 3;
          if (lanedetection_B.idxRow2 > q2) {
            lanedetection_B.idxRow2 = q2;
          }

          if (lanedetection_B.idxTmp < i) {
            lanedetection_B.idxTmp = i;
          }

          if (i > q2) {
            lanedetection_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)(((uint32_T)
              ((q2 + 1) << 3) + lanedetection_DW.DrawShapes_DW_PixCount[q2]) -
              lanedetection_B.firstRow);
            lanedetection_DW.DrawShapes_DW_PixCount[i] = (uint8_T)(((uint32_T)
              (lanedetection_B.lastRow - (i << 3)) +
              lanedetection_DW.DrawShapes_DW_PixCount[i]) + 1U);
            for (q2++; q2 < i; q2++) {
              lanedetection_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)
                (lanedetection_DW.DrawShapes_DW_PixCount[q2] + 8U);
            }
          } else {
            if (i == q2) {
              lanedetection_DW.DrawShapes_DW_PixCount[q2] = (uint8_T)(((uint32_T)
                (lanedetection_B.lastRow - lanedetection_B.firstRow) +
                lanedetection_DW.DrawShapes_DW_PixCount[q2]) + 1U);
            }
          }
        }

        isMore = (lanedetection_B.numUniquePix <= lanedetection_B.k);
        if (((lanedetection_B.loc_m - 1 == lanedetection_B.col) || (!isMore)) &&
            (lanedetection_B.lastRow >= 2559)) {
          lanedetection_B.col = lanedetection_B.loc * 320 +
            lanedetection_B.idxRow2;
          i = lanedetection_B.col;
          for (q2 = lanedetection_B.idxRow2; q2 <= lanedetection_B.idxTmp; q2++)
          {
            if (lanedetection_DW.DrawShapes_DW_PixCount[q2] == 64) {
              lanedetection_B.DrawShapes_o1[i] = (uint8_T)
                ((((lanedetection_P.DrawShapes_color[0] << 14) -
                   (lanedetection_B.DrawShapes_o1[i] << 14)) +
                  (lanedetection_B.DrawShapes_o1[i] << 14)) >> 14);
            } else {
              lanedetection_B.DrawShapes_o1[i] = (uint8_T)
                ((((((lanedetection_P.DrawShapes_color[0] << 14) -
                     (lanedetection_B.DrawShapes_o1[i] << 14)) *
                    lanedetection_DW.DrawShapes_DW_PixCount[q2]) >> 6) +
                  (lanedetection_B.DrawShapes_o1[i] << 14)) >> 14);
            }

            i++;
          }

          i = lanedetection_B.col;
          for (q2 = lanedetection_B.idxRow2; q2 <= lanedetection_B.idxTmp; q2++)
          {
            if (lanedetection_DW.DrawShapes_DW_PixCount[q2] == 64) {
              lanedetection_B.imgOUT[i] = (uint8_T)
                ((((lanedetection_P.DrawShapes_color[1] << 14) -
                   (lanedetection_B.imgOUT[i] << 14)) +
                  (lanedetection_B.imgOUT[i] << 14)) >> 14);
            } else {
              lanedetection_B.imgOUT[i] = (uint8_T)
                ((((((lanedetection_P.DrawShapes_color[1] << 14) -
                     (lanedetection_B.imgOUT[i] << 14)) *
                    lanedetection_DW.DrawShapes_DW_PixCount[q2]) >> 6) +
                  (lanedetection_B.imgOUT[i] << 14)) >> 14);
            }

            i++;
          }

          for (q2 = lanedetection_B.idxRow2; q2 <= lanedetection_B.idxTmp; q2++)
          {
            if (lanedetection_DW.DrawShapes_DW_PixCount[q2] == 64) {
              lanedetection_B.DrawShapes_o3[lanedetection_B.col] = (uint8_T)
                ((((lanedetection_P.DrawShapes_color[2] << 14) -
                   (lanedetection_B.DrawShapes_o3[lanedetection_B.col] << 14)) +
                  (lanedetection_B.DrawShapes_o3[lanedetection_B.col] << 14)) >>
                 14);
            } else {
              lanedetection_B.DrawShapes_o3[lanedetection_B.col] = (uint8_T)
                ((((((lanedetection_P.DrawShapes_color[2] << 14) -
                     (lanedetection_B.DrawShapes_o3[lanedetection_B.col] << 14))
                    * lanedetection_DW.DrawShapes_DW_PixCount[q2]) >> 6) +
                  (lanedetection_B.DrawShapes_o3[lanedetection_B.col] << 14)) >>
                 14);
            }

            lanedetection_B.col++;
          }

          while (lanedetection_B.idxRow2 <= lanedetection_B.idxTmp) {
            lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_B.idxRow2] =
              0U;
            lanedetection_B.idxRow2++;
          }

          lanedetection_B.loc++;
          lanedetection_B.loc_m += 8;
          lanedetection_B.idxRow2 = 320;
          lanedetection_B.idxTmp = 0;
        }
      }

      /* Move to the next polygon. */
      imgIdx += imgCol * 9;
      if (p >= div_s32_floor(imgRow, imgCol) - 1) {
        p = 0;
      } else {
        p++;
      }

      isMore = (imgIdx < (imgCol << 1) * 9);
    }
  }

  /* End of S-Function (svipdrawshapes): '<Root>/Draw Shapes' */

  /* S-Function (svipresize): '<Root>/Resize2' */
  /* use pre-computed weights and index table to perform interpolation */
  imgRow = 0;

  /* resize along X-axis direction */
  for (p = 0; p < 320; p++) {
    i = p;
    for (imgIdx = 0; imgIdx < 100; imgIdx++) {
      q2 = (lanedetection_B.imgOUT[imgIdx * 320 + p] * 127) << 3;
      lanedetection_DW.Resize2_IntBuffer[i] = (uint8_T)(((q2 & 512U) != 0U) +
        (q2 >> 10));
      i += 320;
    }
  }

  /* resize along Y-axis direction */
  for (imgIdx = 0; imgIdx < 100; imgIdx++) {
    i = imgIdx * 320;
    for (imgCol = 0; imgCol < 320; imgCol++) {
      lanedetection_DW.DrawShapes_DW_PixCount[imgCol] =
        lanedetection_DW.Resize2_IntBuffer[i];
      i++;
    }

    for (p = 0; p < 160; p++) {
      q2 =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[p]]
         * lanedetection_ConstP.pooled10[p]) << 3;
      i = p + 160;
      imgCol =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[i]]
         * lanedetection_ConstP.pooled10[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      i += 160;
      imgCol =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[i]]
         * lanedetection_ConstP.pooled10[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      i += 160;
      imgCol =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[i]]
         * lanedetection_ConstP.pooled10[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      imgCol = ((q2 & 512U) != 0U) + (q2 >> 10);
      if (imgCol < 0) {
        imgCol = 0;
      } else {
        if (imgCol > 255) {
          imgCol = 255;
        }
      }

      lanedetection_B.Resize2[imgRow] = (uint8_T)imgCol;
      imgRow++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize2' */

  /* S-Function (svipresize): '<Root>/Resize3' */
  /* use pre-computed weights and index table to perform interpolation */
  imgRow = 0;

  /* resize along X-axis direction */
  for (p = 0; p < 320; p++) {
    i = p;
    for (imgIdx = 0; imgIdx < 100; imgIdx++) {
      q2 = (lanedetection_B.DrawShapes_o3[imgIdx * 320 + p] * 127) << 3;
      lanedetection_DW.Resize3_IntBuffer[i] = (uint8_T)(((q2 & 512U) != 0U) +
        (q2 >> 10));
      i += 320;
    }
  }

  /* resize along Y-axis direction */
  for (imgIdx = 0; imgIdx < 100; imgIdx++) {
    i = imgIdx * 320;
    for (imgCol = 0; imgCol < 320; imgCol++) {
      lanedetection_DW.DrawShapes_DW_PixCount[imgCol] =
        lanedetection_DW.Resize3_IntBuffer[i];
      i++;
    }

    for (p = 0; p < 160; p++) {
      q2 =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[p]]
         * lanedetection_ConstP.pooled10[p]) << 3;
      i = p + 160;
      imgCol =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[i]]
         * lanedetection_ConstP.pooled10[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      i += 160;
      imgCol =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[i]]
         * lanedetection_ConstP.pooled10[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      i += 160;
      imgCol =
        (lanedetection_DW.DrawShapes_DW_PixCount[lanedetection_ConstP.pooled5[i]]
         * lanedetection_ConstP.pooled10[i]) << 3;
      if ((q2 < 0) && (imgCol < MIN_int32_T - q2)) {
        q2 = MIN_int32_T;
      } else if ((q2 > 0) && (imgCol > MAX_int32_T - q2)) {
        q2 = MAX_int32_T;
      } else {
        q2 += imgCol;
      }

      imgCol = ((q2 & 512U) != 0U) + (q2 >> 10);
      if (imgCol < 0) {
        imgCol = 0;
      } else {
        if (imgCol > 255) {
          imgCol = 255;
        }
      }

      lanedetection_B.Resize3[imgRow] = (uint8_T)imgCol;
      imgRow++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize3' */
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  memcpy(&lanedetection_DW.Resize3_IntBuffer[0], &lanedetection_B.DrawShapes_o1
         [0], 32000U * sizeof(uint8_T));
  memcpy(&lanedetection_DW.Resize1_IntBuffer[0], &lanedetection_B.Resize2[0],
         16000U * sizeof(uint8_T));
  memcpy(&lanedetection_DW.Resize_IntBuffer[0], &lanedetection_B.Resize3[0],
         16000U * sizeof(uint8_T));
  MW_SDL_videoDisplayOutput(lanedetection_DW.Resize3_IntBuffer,
    lanedetection_DW.Resize1_IntBuffer, lanedetection_DW.Resize_IntBuffer);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.1s, 0.0s] */
    rtExtModeUpload(0, lanedetection_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
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
  lanedetection_M->Timing.stepSize0 = 0.1;

  /* External mode info */
  lanedetection_M->Sizes.checksums[0] = (2595789524U);
  lanedetection_M->Sizes.checksums[1] = (2759855367U);
  lanedetection_M->Sizes.checksums[2] = (2299279627U);
  lanedetection_M->Sizes.checksums[3] = (1982392442U);

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
                      240U, 1U, 2U, 1U, 0.1);

  /* Start for S-Function (svipedge): '<Root>/Edge Detection' */
  lanedetection_DW.EdgeDetection_VO_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOU_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOD_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOL_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOR_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOLR_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOUL_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOLL_DW[0] = 0;
  lanedetection_DW.EdgeDetection_VOUR_DW[0] = 0;
  lanedetection_DW.EdgeDetection_HO_DW[0] = 1;
  lanedetection_DW.EdgeDetection_HOU_DW[0] = 1;
  lanedetection_DW.EdgeDetection_HOD_DW[0] = 0;
  lanedetection_DW.EdgeDetection_HOL_DW[0] = 1;
  lanedetection_DW.EdgeDetection_HOR_DW[0] = 1;
  lanedetection_DW.EdgeDetection_HOLR_DW[0] = 0;
  lanedetection_DW.EdgeDetection_HOUL_DW[0] = 1;
  lanedetection_DW.EdgeDetection_HOLL_DW[0] = 0;
  lanedetection_DW.EdgeDetection_HOUR_DW[0] = 1;
  lanedetection_DW.EdgeDetection_VO_DW[1] = 321;
  lanedetection_DW.EdgeDetection_VOU_DW[1] = 321;
  lanedetection_DW.EdgeDetection_VOD_DW[1] = 320;
  lanedetection_DW.EdgeDetection_VOL_DW[1] = 321;
  lanedetection_DW.EdgeDetection_VOR_DW[1] = 1;
  lanedetection_DW.EdgeDetection_VOLR_DW[1] = 0;
  lanedetection_DW.EdgeDetection_VOUL_DW[1] = 321;
  lanedetection_DW.EdgeDetection_VOLL_DW[1] = 320;
  lanedetection_DW.EdgeDetection_VOUR_DW[1] = 1;
  lanedetection_DW.EdgeDetection_HO_DW[1] = 320;
  lanedetection_DW.EdgeDetection_HOU_DW[1] = 320;
  lanedetection_DW.EdgeDetection_HOD_DW[1] = 320;
  lanedetection_DW.EdgeDetection_HOL_DW[1] = 320;
  lanedetection_DW.EdgeDetection_HOR_DW[1] = 0;
  lanedetection_DW.EdgeDetection_HOLR_DW[1] = 0;
  lanedetection_DW.EdgeDetection_HOUL_DW[1] = 320;
  lanedetection_DW.EdgeDetection_HOLL_DW[1] = 320;
  lanedetection_DW.EdgeDetection_HOUR_DW[1] = 0;

  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  lanedetection_DW.obj.matlabCodegenIsDeleted = true;
  lanedetection_DW.obj.isInitialized = 0;
  lanedetection_DW.obj.matlabCodegenIsDeleted = false;
  lanedetection_DW.obj.isSetupComplete = false;
  lanedetection_DW.obj.isInitialized = 1;
  lanedetection_DW.obj.PixelFormatEnum = 2;
  MW_SDL_videoDisplayInit(lanedetection_DW.obj.PixelFormatEnum, 1, 1, 320.0,
    100.0);
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
