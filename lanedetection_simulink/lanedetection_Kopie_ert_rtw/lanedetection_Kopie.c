/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_Kopie.c
 *
 * Code generated for Simulink model 'lanedetection_Kopie'.
 *
 * Model version                  : 1.167
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Apr 12 12:20:22 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "lanedetection_Kopie.h"
#include "lanedetection_Kopie_private.h"
#include "lanedetection_Kopie_dt.h"

/* Block signals (default storage) */
B_lanedetection_Kopie_T lanedetection_Kopie_B;

/* Block states (default storage) */
DW_lanedetection_Kopie_T lanedetection_Kopie_DW;

/* Real-time model */
RT_MODEL_lanedetection_Kopie_T lanedetection_Kopie_M_;
RT_MODEL_lanedetection_Kopie_T *const lanedetection_Kopie_M =
  &lanedetection_Kopie_M_;

/* Forward declaration for local functions */
static void lanedetection_Kopie_conv2(const real_T a[4800], const real_T b[9],
  real_T c[4800]);
static real_T lanedetection_Kopie_mean(const real_T x_data[], const int32_T
  *x_size);
static void SystemProp_matlabCodegenSetAn_d(codertarget_linux_blocks_SDLV_T *obj,
  boolean_T value);
static void lanedetect_SystemCore_release_d(const
  codertarget_linux_blocks_SDLV_T *obj);
static void lanedetecti_SystemCore_delete_d(const
  codertarget_linux_blocks_SDLV_T *obj);
static void matlabCodegenHandle_matlabCod_d(codertarget_linux_blocks_SDLV_T *obj);
static void SystemProp_matlabCodegenSetAnyP(codertarget_raspi_internal_SC_T *obj,
  boolean_T value);
static void lanedetectio_SystemCore_release(const
  codertarget_raspi_internal_SC_T *obj);
static void lanedetection_SystemCore_delete(const
  codertarget_raspi_internal_SC_T *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_raspi_internal_SC_T *obj);

/* Function for MATLAB Function: '<Root>/MATLAB Function' */
static void lanedetection_Kopie_conv2(const real_T a[4800], const real_T b[9],
  real_T c[4800])
{
  int32_T lastColA;
  int32_T iC;
  int32_T iA;
  int32_T iB;
  int32_T aidx;
  int32_T cidx;
  int32_T j;
  int32_T k;
  int32_T r;
  memset(&c[0], 0, 4800U * sizeof(real_T));
  for (j = 0; j < 3; j++) {
    if (j + 29 < 30) {
      lastColA = 29;
    } else {
      lastColA = 30 - j;
    }

    for (k = (j < 1); k <= lastColA; k++) {
      iC = j + k;
      if (!(iC > 1)) {
        iC = 1;
      }

      iC = (iC - 1) * 160;
      iA = k * 160;
      iB = j * 3;
      aidx = iA + 1;
      cidx = iC;
      for (r = 1; r < 160; r++) {
        c[cidx] += b[iB] * a[aidx];
        aidx++;
        cidx++;
      }

      iB++;
      aidx = iA;
      cidx = iC;
      for (r = 1; r < 161; r++) {
        c[cidx] += b[iB] * a[aidx];
        aidx++;
        cidx++;
      }

      iB++;
      cidx = iC + 1;
      aidx = iA;
      for (r = 1; r < 160; r++) {
        c[cidx] += b[iB] * a[aidx];
        aidx++;
        cidx++;
      }
    }
  }
}

/* Function for MATLAB Function: '<Root>/MATLAB Function' */
static real_T lanedetection_Kopie_mean(const real_T x_data[], const int32_T
  *x_size)
{
  real_T b_y;
  int32_T k;
  if (*x_size == 0) {
    b_y = 0.0;
  } else {
    b_y = x_data[0];
    for (k = 2; k <= *x_size; k++) {
      b_y += x_data[k - 1];
    }
  }

  return b_y / (real_T)*x_size;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void SystemProp_matlabCodegenSetAn_d(codertarget_linux_blocks_SDLV_T *obj,
  boolean_T value)
{
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetect_SystemCore_release_d(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SDL_videoDisplayTerminate(0, 0);
  }
}

static void lanedetecti_SystemCore_delete_d(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  lanedetect_SystemCore_release_d(obj);
}

static void matlabCodegenHandle_matlabCod_d(codertarget_linux_blocks_SDLV_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAn_d(obj, true);
    lanedetecti_SystemCore_delete_d(obj);
  }
}

static void SystemProp_matlabCodegenSetAnyP(codertarget_raspi_internal_SC_T *obj,
  boolean_T value)
{
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetectio_SystemCore_release(const
  codertarget_raspi_internal_SC_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SCI_Close(obj->MW_SCIHANDLE);
  }
}

static void lanedetection_SystemCore_delete(const
  codertarget_raspi_internal_SC_T *obj)
{
  lanedetectio_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_raspi_internal_SC_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAnyP(obj, true);
    lanedetection_SystemCore_delete(obj);
  }
}

/* Model step function */
void lanedetection_Kopie_step(void)
{
  int32_T apnd;
  int32_T cdiff;
  int32_T b_nm1d2;
  int32_T b_k;
  static const real_T f[9] = { 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 };

  uint8_T TxDataLocChar;
  boolean_T exitg1;
  boolean_T guard1 = false;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_Kopie_ConstP.V4L2VideoCapture_p1,
                        lanedetection_Kopie_B.V4L2VideoCapture_o1,
                        lanedetection_Kopie_B.V4L2VideoCapture_o2,
                        lanedetection_Kopie_B.V4L2VideoCapture_o3);

  /* MATLAB Function: '<Root>/MATLAB Function1' */
  for (apnd = 0; apnd < 30; apnd++) {
    memcpy(&lanedetection_Kopie_B.imgOUT[apnd * 160],
           &lanedetection_Kopie_B.V4L2VideoCapture_o1[apnd * 160 + 11200], 160U *
           sizeof(uint8_T));
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function1' */

  /* MATLAB Function: '<Root>/MATLAB Function' */
  for (apnd = 0; apnd < 4800; apnd++) {
    lanedetection_Kopie_B.rtb_imgOUT_m[apnd] = lanedetection_Kopie_B.imgOUT[apnd];
  }

  lanedetection_Kopie_conv2(lanedetection_Kopie_B.rtb_imgOUT_m, f,
    lanedetection_Kopie_B.dv0);
  for (apnd = 0; apnd < 4800; apnd++) {
    lanedetection_Kopie_B.imgEdge[apnd] = (uint8_T)
      ((lanedetection_Kopie_B.dv0[apnd] > 60.0) * 255U);
  }

  lanedetection_Kopie_B.idx = 0;
  lanedetection_Kopie_B.ii = 1;
  lanedetection_Kopie_B.jj = 1;
  exitg1 = false;
  while ((!exitg1) && (lanedetection_Kopie_B.jj <= 30)) {
    guard1 = false;
    if (lanedetection_Kopie_B.imgEdge[((lanedetection_Kopie_B.jj - 1) * 160 +
         lanedetection_Kopie_B.ii) - 1] != 0) {
      lanedetection_Kopie_B.idx++;
      lanedetection_Kopie_B.i_data[lanedetection_Kopie_B.idx - 1] =
        lanedetection_Kopie_B.ii;
      lanedetection_Kopie_B.j_data[lanedetection_Kopie_B.idx - 1] = (int8_T)
        lanedetection_Kopie_B.jj;
      if (lanedetection_Kopie_B.idx >= 4800) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      lanedetection_Kopie_B.ii++;
      if (lanedetection_Kopie_B.ii > 160) {
        lanedetection_Kopie_B.ii = 1;
        lanedetection_Kopie_B.jj++;
      }
    }
  }

  if (1 > lanedetection_Kopie_B.idx) {
    lanedetection_Kopie_B.idx = 0;
    lanedetection_Kopie_B.ii = 0;
  } else {
    lanedetection_Kopie_B.ii = lanedetection_Kopie_B.idx;
  }

  cdiff = lanedetection_Kopie_B.idx;
  for (apnd = 0; apnd < lanedetection_Kopie_B.idx; apnd++) {
    lanedetection_Kopie_B.x_data[apnd] = lanedetection_Kopie_B.i_data[apnd];
  }

  b_nm1d2 = lanedetection_Kopie_B.ii;
  for (apnd = 0; apnd < lanedetection_Kopie_B.ii; apnd++) {
    lanedetection_Kopie_B.y_data[apnd] = lanedetection_Kopie_B.j_data[apnd];
  }

  lanedetection_Kopie_B.xCenter = rt_roundd_snf(lanedetection_Kopie_mean
    (lanedetection_Kopie_B.x_data, &cdiff));
  lanedetection_Kopie_B.yCenter = rt_roundd_snf(lanedetection_Kopie_mean
    (lanedetection_Kopie_B.y_data, &b_nm1d2));
  if ((1.0 > lanedetection_Kopie_B.xCenter - 2.0) || rtIsNaN
      (lanedetection_Kopie_B.xCenter - 2.0)) {
    lanedetection_Kopie_B.maxval = 1.0;
  } else {
    lanedetection_Kopie_B.maxval = lanedetection_Kopie_B.xCenter - 2.0;
  }

  if (lanedetection_Kopie_B.xCenter + 2.0 < 160.0) {
    lanedetection_Kopie_B.minval = lanedetection_Kopie_B.xCenter + 2.0;
  } else {
    lanedetection_Kopie_B.minval = 160.0;
  }

  if (lanedetection_Kopie_B.minval < lanedetection_Kopie_B.maxval) {
    lanedetection_Kopie_B.jj = 0;
  } else if (lanedetection_Kopie_B.maxval == lanedetection_Kopie_B.maxval) {
    cdiff = (int32_T)((real32_T)lanedetection_Kopie_B.minval - (real32_T)
                      lanedetection_Kopie_B.maxval);
    lanedetection_Kopie_B.jj = cdiff + 1;
    for (apnd = 0; apnd <= cdiff; apnd++) {
      lanedetection_Kopie_B.xx_data[apnd] = lanedetection_Kopie_B.maxval +
        (real_T)apnd;
    }
  } else {
    lanedetection_Kopie_B.jj = (int32_T)floor((lanedetection_Kopie_B.minval -
      lanedetection_Kopie_B.maxval) + 0.5);
    apnd = (int32_T)lanedetection_Kopie_B.maxval + lanedetection_Kopie_B.jj;
    cdiff = apnd - (int32_T)lanedetection_Kopie_B.minval;
    if ((int32_T)lanedetection_Kopie_B.maxval > (int32_T)
        lanedetection_Kopie_B.minval) {
      lanedetection_Kopie_B.nm1d2 = (int32_T)lanedetection_Kopie_B.maxval;
    } else {
      lanedetection_Kopie_B.nm1d2 = (int32_T)lanedetection_Kopie_B.minval;
    }

    if (fabs((real_T)cdiff) < 4.4408920985006262E-16 * (real_T)
        lanedetection_Kopie_B.nm1d2) {
      lanedetection_Kopie_B.jj++;
      apnd = (int32_T)lanedetection_Kopie_B.minval;
    } else if (cdiff > 0) {
      apnd = ((int32_T)lanedetection_Kopie_B.maxval + lanedetection_Kopie_B.jj)
        - 1;
    } else {
      lanedetection_Kopie_B.jj++;
    }

    if (lanedetection_Kopie_B.jj >= 0) {
      cdiff = lanedetection_Kopie_B.jj - 1;
    } else {
      cdiff = -1;
    }

    lanedetection_Kopie_B.jj = cdiff + 1;
    if (cdiff + 1 > 0) {
      lanedetection_Kopie_B.xx_data[0] = lanedetection_Kopie_B.maxval;
      if (cdiff + 1 > 1) {
        lanedetection_Kopie_B.xx_data[cdiff] = apnd;
        lanedetection_Kopie_B.nm1d2 = cdiff / 2;
        for (b_nm1d2 = 1; b_nm1d2 < lanedetection_Kopie_B.nm1d2; b_nm1d2++) {
          lanedetection_Kopie_B.xx_data[b_nm1d2] = lanedetection_Kopie_B.maxval
            + (real_T)b_nm1d2;
          lanedetection_Kopie_B.xx_data[cdiff - b_nm1d2] = apnd - b_nm1d2;
        }

        if (lanedetection_Kopie_B.nm1d2 << 1 == cdiff) {
          lanedetection_Kopie_B.xx_data[lanedetection_Kopie_B.nm1d2] =
            (lanedetection_Kopie_B.maxval + (real_T)apnd) / 2.0;
        } else {
          lanedetection_Kopie_B.xx_data[lanedetection_Kopie_B.nm1d2] =
            lanedetection_Kopie_B.maxval + (real_T)lanedetection_Kopie_B.nm1d2;
          lanedetection_Kopie_B.xx_data[lanedetection_Kopie_B.nm1d2 + 1] = apnd
            - lanedetection_Kopie_B.nm1d2;
        }
      }
    }
  }

  if ((1.0 > lanedetection_Kopie_B.yCenter - 2.0) || rtIsNaN
      (lanedetection_Kopie_B.yCenter - 2.0)) {
    lanedetection_Kopie_B.maxval = 1.0;
  } else {
    lanedetection_Kopie_B.maxval = lanedetection_Kopie_B.yCenter - 2.0;
  }

  if (lanedetection_Kopie_B.yCenter + 2.0 < 30.0) {
    lanedetection_Kopie_B.yCenter += 2.0;
  } else {
    lanedetection_Kopie_B.yCenter = 30.0;
  }

  if (lanedetection_Kopie_B.yCenter < lanedetection_Kopie_B.maxval) {
    lanedetection_Kopie_B.nm1d2 = 0;
  } else if (lanedetection_Kopie_B.maxval == lanedetection_Kopie_B.maxval) {
    cdiff = (int32_T)((real32_T)lanedetection_Kopie_B.yCenter - (real32_T)
                      lanedetection_Kopie_B.maxval);
    lanedetection_Kopie_B.nm1d2 = cdiff + 1;
    for (apnd = 0; apnd <= cdiff; apnd++) {
      lanedetection_Kopie_B.b_y_data[apnd] = lanedetection_Kopie_B.maxval +
        (real_T)apnd;
    }
  } else {
    apnd = (int32_T)floor((lanedetection_Kopie_B.yCenter -
      lanedetection_Kopie_B.maxval) + 0.5);
    cdiff = (int32_T)lanedetection_Kopie_B.maxval + apnd;
    lanedetection_Kopie_B.nm1d2 = cdiff - (int32_T)lanedetection_Kopie_B.yCenter;
    if ((int32_T)lanedetection_Kopie_B.maxval > (int32_T)
        lanedetection_Kopie_B.yCenter) {
      b_nm1d2 = (int32_T)lanedetection_Kopie_B.maxval;
    } else {
      b_nm1d2 = (int32_T)lanedetection_Kopie_B.yCenter;
    }

    if (fabs((real_T)lanedetection_Kopie_B.nm1d2) < 4.4408920985006262E-16 *
        (real_T)b_nm1d2) {
      apnd++;
      cdiff = (int32_T)lanedetection_Kopie_B.yCenter;
    } else if (lanedetection_Kopie_B.nm1d2 > 0) {
      cdiff = ((int32_T)lanedetection_Kopie_B.maxval + apnd) - 1;
    } else {
      apnd++;
    }

    if (apnd >= 0) {
      apnd--;
    } else {
      apnd = -1;
    }

    lanedetection_Kopie_B.nm1d2 = apnd + 1;
    if (apnd + 1 > 0) {
      lanedetection_Kopie_B.b_y_data[0] = lanedetection_Kopie_B.maxval;
      if (apnd + 1 > 1) {
        lanedetection_Kopie_B.b_y_data[apnd] = cdiff;
        b_nm1d2 = apnd / 2;
        for (b_k = 1; b_k < b_nm1d2; b_k++) {
          lanedetection_Kopie_B.b_y_data[b_k] = lanedetection_Kopie_B.maxval +
            (real_T)b_k;
          lanedetection_Kopie_B.b_y_data[apnd - b_k] = cdiff - b_k;
        }

        if (b_nm1d2 << 1 == apnd) {
          lanedetection_Kopie_B.b_y_data[b_nm1d2] =
            (lanedetection_Kopie_B.maxval + (real_T)cdiff) / 2.0;
        } else {
          lanedetection_Kopie_B.b_y_data[b_nm1d2] = lanedetection_Kopie_B.maxval
            + (real_T)b_nm1d2;
          lanedetection_Kopie_B.b_y_data[b_nm1d2 + 1] = cdiff - b_nm1d2;
        }
      }
    }
  }

  memset(&lanedetection_Kopie_B.imgOUT[0], 0, 4800U * sizeof(uint8_T));
  if ((!(lanedetection_Kopie_B.idx == 0)) && (!(lanedetection_Kopie_B.ii == 0)))
  {
    for (apnd = 0; apnd < lanedetection_Kopie_B.jj; apnd++) {
      lanedetection_Kopie_B.b_data[apnd] = (int32_T)
        lanedetection_Kopie_B.xx_data[apnd];
    }

    for (apnd = 0; apnd < lanedetection_Kopie_B.nm1d2; apnd++) {
      lanedetection_Kopie_B.c_data[apnd] = (int32_T)
        lanedetection_Kopie_B.b_y_data[apnd];
    }

    for (apnd = 0; apnd < lanedetection_Kopie_B.nm1d2; apnd++) {
      for (lanedetection_Kopie_B.idx = 0; lanedetection_Kopie_B.idx <
           lanedetection_Kopie_B.jj; lanedetection_Kopie_B.idx++) {
        lanedetection_Kopie_B.imgOUT
          [(lanedetection_Kopie_B.b_data[lanedetection_Kopie_B.idx] + 160 *
            (lanedetection_Kopie_B.c_data[apnd] - 1)) - 1] = MAX_uint8_T;
      }
    }
  } else {
    for (apnd = 0; apnd < lanedetection_Kopie_B.jj; apnd++) {
      lanedetection_Kopie_B.b_data[apnd] = (int32_T)
        lanedetection_Kopie_B.xx_data[apnd];
    }

    for (apnd = 0; apnd < lanedetection_Kopie_B.nm1d2; apnd++) {
      lanedetection_Kopie_B.c_data[apnd] = (int32_T)
        lanedetection_Kopie_B.b_y_data[apnd];
    }

    for (apnd = 0; apnd < lanedetection_Kopie_B.nm1d2; apnd++) {
      for (lanedetection_Kopie_B.idx = 0; lanedetection_Kopie_B.idx <
           lanedetection_Kopie_B.jj; lanedetection_Kopie_B.idx++) {
        lanedetection_Kopie_B.imgOUT
          [(lanedetection_Kopie_B.b_data[lanedetection_Kopie_B.idx] + 160 *
            (lanedetection_Kopie_B.c_data[apnd] - 1)) - 1] = 0U;
      }
    }
  }

  for (apnd = 0; apnd < 4800; apnd++) {
    lanedetection_Kopie_B.idx = (int32_T)((uint32_T)
      lanedetection_Kopie_B.imgEdge[apnd] + lanedetection_Kopie_B.imgOUT[apnd]);
    if ((uint32_T)lanedetection_Kopie_B.idx > 255U) {
      lanedetection_Kopie_B.idx = 255;
    }

    lanedetection_Kopie_B.imgEdge[apnd] = (uint8_T)lanedetection_Kopie_B.idx;
  }

  /* S-Function (svipresize): '<Root>/Resize1' */
  /* use pre-computed weights and index table to perform interpolation */
  lanedetection_Kopie_B.idx = 0;

  /* resize along X-axis direction */
  for (lanedetection_Kopie_B.ii = 0; lanedetection_Kopie_B.ii < 160;
       lanedetection_Kopie_B.ii++) {
    apnd = lanedetection_Kopie_B.ii;
    for (cdiff = 0; cdiff < 30; cdiff++) {
      lanedetection_Kopie_B.jj = (lanedetection_Kopie_B.imgOUT[cdiff * 160 +
        lanedetection_Kopie_B.ii] * 127) << 3;
      lanedetection_Kopie_DW.Resize1_IntBuffer[apnd] = (uint8_T)
        (((lanedetection_Kopie_B.jj & 512U) != 0U) + (lanedetection_Kopie_B.jj >>
          10));
      apnd += 160;
    }
  }

  /* resize along Y-axis direction */
  for (cdiff = 0; cdiff < 30; cdiff++) {
    apnd = cdiff * 160;
    for (lanedetection_Kopie_B.ii = 0; lanedetection_Kopie_B.ii < 160;
         lanedetection_Kopie_B.ii++) {
      lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_B.ii] =
        lanedetection_Kopie_DW.Resize1_IntBuffer[apnd];
      apnd++;
    }

    for (lanedetection_Kopie_B.ii = 0; lanedetection_Kopie_B.ii < 80;
         lanedetection_Kopie_B.ii++) {
      lanedetection_Kopie_B.jj =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [lanedetection_Kopie_B.ii]] *
         lanedetection_Kopie_ConstP.pooled5[lanedetection_Kopie_B.ii]) << 3;
      apnd = lanedetection_Kopie_B.ii + 80;
      lanedetection_Kopie_B.nm1d2 =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [apnd]] * lanedetection_Kopie_ConstP.pooled5[apnd]) << 3;
      if ((lanedetection_Kopie_B.jj < 0) && (lanedetection_Kopie_B.nm1d2 <
           MIN_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MIN_int32_T;
      } else if ((lanedetection_Kopie_B.jj > 0) && (lanedetection_Kopie_B.nm1d2 >
                  MAX_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MAX_int32_T;
      } else {
        lanedetection_Kopie_B.jj += lanedetection_Kopie_B.nm1d2;
      }

      apnd += 80;
      lanedetection_Kopie_B.nm1d2 =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [apnd]] * lanedetection_Kopie_ConstP.pooled5[apnd]) << 3;
      if ((lanedetection_Kopie_B.jj < 0) && (lanedetection_Kopie_B.nm1d2 <
           MIN_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MIN_int32_T;
      } else if ((lanedetection_Kopie_B.jj > 0) && (lanedetection_Kopie_B.nm1d2 >
                  MAX_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MAX_int32_T;
      } else {
        lanedetection_Kopie_B.jj += lanedetection_Kopie_B.nm1d2;
      }

      apnd += 80;
      lanedetection_Kopie_B.nm1d2 =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [apnd]] * lanedetection_Kopie_ConstP.pooled5[apnd]) << 3;
      if ((lanedetection_Kopie_B.jj < 0) && (lanedetection_Kopie_B.nm1d2 <
           MIN_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MIN_int32_T;
      } else if ((lanedetection_Kopie_B.jj > 0) && (lanedetection_Kopie_B.nm1d2 >
                  MAX_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MAX_int32_T;
      } else {
        lanedetection_Kopie_B.jj += lanedetection_Kopie_B.nm1d2;
      }

      apnd = ((lanedetection_Kopie_B.jj & 512U) != 0U) +
        (lanedetection_Kopie_B.jj >> 10);
      if (apnd < 0) {
        apnd = 0;
      } else {
        if (apnd > 255) {
          apnd = 255;
        }
      }

      lanedetection_Kopie_B.Resize1[lanedetection_Kopie_B.idx] = (uint8_T)apnd;
      lanedetection_Kopie_B.idx++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize1' */

  /* S-Function (svipresize): '<Root>/Resize2' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /* use pre-computed weights and index table to perform interpolation */
  lanedetection_Kopie_B.idx = 0;

  /* resize along X-axis direction */
  for (lanedetection_Kopie_B.ii = 0; lanedetection_Kopie_B.ii < 160;
       lanedetection_Kopie_B.ii++) {
    apnd = lanedetection_Kopie_B.ii;
    for (cdiff = 0; cdiff < 30; cdiff++) {
      lanedetection_Kopie_B.jj = (lanedetection_Kopie_B.imgOUT[cdiff * 160 +
        lanedetection_Kopie_B.ii] * 127) << 3;
      lanedetection_Kopie_DW.Resize2_IntBuffer[apnd] = (uint8_T)
        (((lanedetection_Kopie_B.jj & 512U) != 0U) + (lanedetection_Kopie_B.jj >>
          10));
      apnd += 160;
    }
  }

  /* resize along Y-axis direction */
  for (cdiff = 0; cdiff < 30; cdiff++) {
    apnd = cdiff * 160;
    for (lanedetection_Kopie_B.ii = 0; lanedetection_Kopie_B.ii < 160;
         lanedetection_Kopie_B.ii++) {
      lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_B.ii] =
        lanedetection_Kopie_DW.Resize2_IntBuffer[apnd];
      apnd++;
    }

    for (lanedetection_Kopie_B.ii = 0; lanedetection_Kopie_B.ii < 80;
         lanedetection_Kopie_B.ii++) {
      lanedetection_Kopie_B.jj =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [lanedetection_Kopie_B.ii]] *
         lanedetection_Kopie_ConstP.pooled5[lanedetection_Kopie_B.ii]) << 3;
      apnd = lanedetection_Kopie_B.ii + 80;
      lanedetection_Kopie_B.nm1d2 =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [apnd]] * lanedetection_Kopie_ConstP.pooled5[apnd]) << 3;
      if ((lanedetection_Kopie_B.jj < 0) && (lanedetection_Kopie_B.nm1d2 <
           MIN_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MIN_int32_T;
      } else if ((lanedetection_Kopie_B.jj > 0) && (lanedetection_Kopie_B.nm1d2 >
                  MAX_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MAX_int32_T;
      } else {
        lanedetection_Kopie_B.jj += lanedetection_Kopie_B.nm1d2;
      }

      apnd += 80;
      lanedetection_Kopie_B.nm1d2 =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [apnd]] * lanedetection_Kopie_ConstP.pooled5[apnd]) << 3;
      if ((lanedetection_Kopie_B.jj < 0) && (lanedetection_Kopie_B.nm1d2 <
           MIN_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MIN_int32_T;
      } else if ((lanedetection_Kopie_B.jj > 0) && (lanedetection_Kopie_B.nm1d2 >
                  MAX_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MAX_int32_T;
      } else {
        lanedetection_Kopie_B.jj += lanedetection_Kopie_B.nm1d2;
      }

      apnd += 80;
      lanedetection_Kopie_B.nm1d2 =
        (lanedetection_Kopie_DW.Resize1_LineBuffer[lanedetection_Kopie_ConstP.pooled2
         [apnd]] * lanedetection_Kopie_ConstP.pooled5[apnd]) << 3;
      if ((lanedetection_Kopie_B.jj < 0) && (lanedetection_Kopie_B.nm1d2 <
           MIN_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MIN_int32_T;
      } else if ((lanedetection_Kopie_B.jj > 0) && (lanedetection_Kopie_B.nm1d2 >
                  MAX_int32_T - lanedetection_Kopie_B.jj)) {
        lanedetection_Kopie_B.jj = MAX_int32_T;
      } else {
        lanedetection_Kopie_B.jj += lanedetection_Kopie_B.nm1d2;
      }

      apnd = ((lanedetection_Kopie_B.jj & 512U) != 0U) +
        (lanedetection_Kopie_B.jj >> 10);
      if (apnd < 0) {
        apnd = 0;
      } else {
        if (apnd > 255) {
          apnd = 255;
        }
      }

      lanedetection_Kopie_B.Resize2[lanedetection_Kopie_B.idx] = (uint8_T)apnd;
      lanedetection_Kopie_B.idx++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize2' */
  /* MATLABSystem: '<S3>/MATLAB System' */
  memcpy(&lanedetection_Kopie_DW.Resize2_IntBuffer[0],
         &lanedetection_Kopie_B.imgEdge[0], 4800U * sizeof(uint8_T));
  memcpy(&lanedetection_Kopie_B.pln2[0], &lanedetection_Kopie_B.Resize1[0],
         2400U * sizeof(uint8_T));
  memcpy(&lanedetection_Kopie_B.pln3[0], &lanedetection_Kopie_B.Resize2[0],
         2400U * sizeof(uint8_T));
  MW_SDL_videoDisplayOutput(lanedetection_Kopie_DW.Resize2_IntBuffer,
    lanedetection_Kopie_B.pln2, lanedetection_Kopie_B.pln3);

  /* DataTypeConversion: '<Root>/Cast' incorporates:
   *  Gain: '<Root>/Gain'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  lanedetection_Kopie_B.yCenter = floor((lanedetection_Kopie_B.xCenter - 80.0) *
    lanedetection_Kopie_P.Gain_Gain);
  if (rtIsNaN(lanedetection_Kopie_B.yCenter) || rtIsInf
      (lanedetection_Kopie_B.yCenter)) {
    lanedetection_Kopie_B.yCenter = 0.0;
  } else {
    lanedetection_Kopie_B.yCenter = fmod(lanedetection_Kopie_B.yCenter, 256.0);
  }

  /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/Offset Servo'
   *  DataTypeConversion: '<Root>/Cast'
   */
  lanedetection_Kopie_B.Add = (int8_T)((lanedetection_Kopie_B.yCenter < 0.0 ?
    (int32_T)(int8_T)-(int8_T)(uint8_T)-lanedetection_Kopie_B.yCenter : (int32_T)
    (int8_T)(uint8_T)lanedetection_Kopie_B.yCenter) +
    lanedetection_Kopie_P.OffsetServo_Value);

  /* MATLABSystem: '<Root>/Serial Write' */
  memcpy((void *)&TxDataLocChar, (void *)&lanedetection_Kopie_B.Add, (uint32_T)
         ((size_t)1 * sizeof(uint8_T)));
  MW_SCI_Transmit(lanedetection_Kopie_DW.obj_n.MW_SCIHANDLE, &TxDataLocChar, 1U);

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.011111111111111112s, 0.0s] */
    rtExtModeUpload(0, lanedetection_Kopie_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.011111111111111112s, 0.0s] */
    if ((rtmGetTFinal(lanedetection_Kopie_M)!=-1) &&
        !((rtmGetTFinal(lanedetection_Kopie_M)-
           lanedetection_Kopie_M->Timing.taskTime0) >
          lanedetection_Kopie_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(lanedetection_Kopie_M, "Simulation finished");
    }

    if (rtmGetStopRequested(lanedetection_Kopie_M)) {
      rtmSetErrorStatus(lanedetection_Kopie_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  lanedetection_Kopie_M->Timing.taskTime0 =
    (++lanedetection_Kopie_M->Timing.clockTick0) *
    lanedetection_Kopie_M->Timing.stepSize0;
}

/* Model initialize function */
void lanedetection_Kopie_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)lanedetection_Kopie_M, 0,
                sizeof(RT_MODEL_lanedetection_Kopie_T));
  rtmSetTFinal(lanedetection_Kopie_M, -1);
  lanedetection_Kopie_M->Timing.stepSize0 = 0.011111111111111112;

  /* External mode info */
  lanedetection_Kopie_M->Sizes.checksums[0] = (3681088908U);
  lanedetection_Kopie_M->Sizes.checksums[1] = (3852212849U);
  lanedetection_Kopie_M->Sizes.checksums[2] = (4030688129U);
  lanedetection_Kopie_M->Sizes.checksums[3] = (1198713997U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    lanedetection_Kopie_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lanedetection_Kopie_M->extModeInfo,
      &lanedetection_Kopie_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lanedetection_Kopie_M->extModeInfo,
                        lanedetection_Kopie_M->Sizes.checksums);
    rteiSetTPtr(lanedetection_Kopie_M->extModeInfo, rtmGetTPtr
                (lanedetection_Kopie_M));
  }

  /* block I/O */
  (void) memset(((void *) &lanedetection_Kopie_B), 0,
                sizeof(B_lanedetection_Kopie_T));

  /* states (dwork) */
  (void) memset((void *)&lanedetection_Kopie_DW, 0,
                sizeof(DW_lanedetection_Kopie_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lanedetection_Kopie_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 18;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    codertarget_raspi_internal_SC_T *obj;
    uint32_T RxPinLoc;
    uint32_T TxPinLoc;
    char_T SCIModuleLoc[13];
    MW_SCI_StopBits_Type StopBitsValue;
    MW_SCI_Parity_Type ParityValue;
    static const char_T tmp[12] = { '/', 'd', 'e', 'v', '/', 't', 't', 'y', 'A',
      'C', 'M', '0' };

    int32_T i;

    /* Start for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
    MW_videoCaptureInit(lanedetection_Kopie_ConstP.V4L2VideoCapture_p1, 0, 0, 0,
                        0, 160U, 120U, 1U, 2U, 1U, 0.011111111111111112);

    /* Start for MATLABSystem: '<S3>/MATLAB System' */
    lanedetection_Kopie_DW.obj.matlabCodegenIsDeleted = true;
    lanedetection_Kopie_DW.obj.isInitialized = 0;
    lanedetection_Kopie_DW.obj.matlabCodegenIsDeleted = false;
    lanedetection_Kopie_DW.obj.isSetupComplete = false;
    lanedetection_Kopie_DW.obj.isInitialized = 1;
    lanedetection_Kopie_DW.obj.PixelFormatEnum = 2;
    MW_SDL_videoDisplayInit(lanedetection_Kopie_DW.obj.PixelFormatEnum, 1, 1,
      160.0, 30.0);
    lanedetection_Kopie_DW.obj.isSetupComplete = true;

    /* End of Start for SubSystem: '<Root>/SDL Video Display' */

    /* Start for MATLABSystem: '<Root>/Serial Write' */
    lanedetection_Kopie_DW.obj_n.matlabCodegenIsDeleted = true;
    lanedetection_Kopie_DW.obj_n.isInitialized = 0;
    lanedetection_Kopie_DW.obj_n.matlabCodegenIsDeleted = false;
    obj = &lanedetection_Kopie_DW.obj_n;
    lanedetection_Kopie_DW.obj_n.isSetupComplete = false;
    lanedetection_Kopie_DW.obj_n.isInitialized = 1;
    RxPinLoc = MW_UNDEFINED_VALUE;
    TxPinLoc = MW_UNDEFINED_VALUE;
    for (i = 0; i < 12; i++) {
      SCIModuleLoc[i] = tmp[i];
    }

    SCIModuleLoc[12] = '\x00';
    obj->MW_SCIHANDLE = MW_SCI_Open(SCIModuleLoc, true, RxPinLoc, TxPinLoc);
    MW_SCI_SetBaudrate(lanedetection_Kopie_DW.obj_n.MW_SCIHANDLE, 115200U);
    StopBitsValue = MW_SCI_STOPBITS_1;
    ParityValue = MW_SCI_PARITY_NONE;
    MW_SCI_SetFrameFormat(lanedetection_Kopie_DW.obj_n.MW_SCIHANDLE, 8,
                          ParityValue, StopBitsValue);
    lanedetection_Kopie_DW.obj_n.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/Serial Write' */
  }
}

/* Model terminate function */
void lanedetection_Kopie_terminate(void)
{
  /* Terminate for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureTerminate(lanedetection_Kopie_ConstP.V4L2VideoCapture_p1);

  /* Terminate for MATLABSystem: '<S3>/MATLAB System' */
  matlabCodegenHandle_matlabCod_d(&lanedetection_Kopie_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/SDL Video Display' */

  /* Terminate for MATLABSystem: '<Root>/Serial Write' */
  matlabCodegenHandle_matlabCodeg(&lanedetection_Kopie_DW.obj_n);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
