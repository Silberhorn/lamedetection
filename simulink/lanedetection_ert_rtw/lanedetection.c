/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection.c
 *
 * Code generated for Simulink model 'lanedetection'.
 *
 * Model version                  : 1.100
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Tue Mar 26 10:54:35 2019
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
static void lanedetection_conv2(const real_T a[4800], const real_T b[9], real_T
  c[4800]);
static real_T lanedetection_mean(const real_T x_data[], const int32_T *x_size);
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
static void lanedetection_conv2(const real_T a[4800], const real_T b[9], real_T
  c[4800])
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
static real_T lanedetection_mean(const real_T x_data[], const int32_T *x_size)
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
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetect_SystemCore_release_d(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SDL_videoDisplayTerminate(0, 0);
  }

  /* End of Start for MATLABSystem: '<S3>/MATLAB System' */
}

static void lanedetecti_SystemCore_delete_d(const
  codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  lanedetect_SystemCore_release_d(obj);
}

static void matlabCodegenHandle_matlabCod_d(codertarget_linux_blocks_SDLV_T *obj)
{
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAn_d(obj, true);
    lanedetecti_SystemCore_delete_d(obj);
  }

  /* End of Start for MATLABSystem: '<S3>/MATLAB System' */
}

static void SystemProp_matlabCodegenSetAnyP(codertarget_raspi_internal_SC_T *obj,
  boolean_T value)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  obj->matlabCodegenIsDeleted = value;
}

static void lanedetectio_SystemCore_release(const
  codertarget_raspi_internal_SC_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SCI_Close(obj->MW_SCIHANDLE);
  }

  /* End of Start for MATLABSystem: '<Root>/Serial Write' */
}

static void lanedetection_SystemCore_delete(const
  codertarget_raspi_internal_SC_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  lanedetectio_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_raspi_internal_SC_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAnyP(obj, true);
    lanedetection_SystemCore_delete(obj);
  }

  /* End of Start for MATLABSystem: '<Root>/Serial Write' */
}

/* Model step function */
void lanedetection_step(void)
{
  int32_T nm1d2;
  int32_T apnd;
  int32_T cdiff;
  int32_T b_ndbl;
  static const real_T f[9] = { 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 };

  uint8_T TxDataLocChar;
  boolean_T exitg1;
  boolean_T guard1 = false;

  /* S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureOutput(lanedetection_ConstP.V4L2VideoCapture_p1,
                        lanedetection_B.V4L2VideoCapture_o1,
                        lanedetection_B.V4L2VideoCapture_o2,
                        lanedetection_B.V4L2VideoCapture_o3);

  /* S-Function (svipresize): '<Root>/Resize3' */
  /* use pre-computed weights and index table to perform interpolation */
  lanedetection_B.idx = 0;

  /* resize along X-axis direction */
  for (lanedetection_B.ii = 0; lanedetection_B.ii < 800; lanedetection_B.ii++) {
    lanedetection_B.jj = lanedetection_B.ii;
    for (cdiff = 0; cdiff < 120; cdiff++) {
      lanedetection_B.indxTblX = cdiff;
      nm1d2 = 0;
      for (b_ndbl = 0; b_ndbl < 10; b_ndbl++) {
        apnd =
          (lanedetection_B.V4L2VideoCapture_o1[lanedetection_ConstP.Resize3_Xindex
           [lanedetection_B.indxTblX] * 800 + lanedetection_B.ii] *
           lanedetection_ConstP.Resize3_Xweights[lanedetection_B.indxTblX]) << 3;
        if ((nm1d2 < 0) && (apnd < MIN_int32_T - nm1d2)) {
          nm1d2 = MIN_int32_T;
        } else if ((nm1d2 > 0) && (apnd > MAX_int32_T - nm1d2)) {
          nm1d2 = MAX_int32_T;
        } else {
          nm1d2 += apnd;
        }

        lanedetection_B.indxTblX += 120;
      }

      b_ndbl = ((nm1d2 & 512U) != 0U) + (nm1d2 >> 10);
      if (b_ndbl < 0) {
        b_ndbl = 0;
      } else {
        if (b_ndbl > 255) {
          b_ndbl = 255;
        }
      }

      lanedetection_DW.Resize3_IntBuffer[lanedetection_B.jj] = (uint8_T)b_ndbl;
      lanedetection_B.jj += 800;
    }
  }

  /* resize along Y-axis direction */
  for (cdiff = 0; cdiff < 120; cdiff++) {
    lanedetection_B.jj = cdiff * 800;
    for (lanedetection_B.ii = 0; lanedetection_B.ii < 800; lanedetection_B.ii++)
    {
      lanedetection_DW.Resize3_LineBuffer[lanedetection_B.ii] =
        lanedetection_DW.Resize3_IntBuffer[lanedetection_B.jj];
      lanedetection_B.jj++;
    }

    for (lanedetection_B.ii = 0; lanedetection_B.ii < 160; lanedetection_B.ii++)
    {
      lanedetection_B.jj = lanedetection_B.ii;
      nm1d2 = 0;
      for (b_ndbl = 0; b_ndbl < 10; b_ndbl++) {
        apnd =
          (lanedetection_DW.Resize3_LineBuffer[lanedetection_ConstP.Resize3_Yindex
           [lanedetection_B.jj]] *
           lanedetection_ConstP.Resize3_Yweights[lanedetection_B.jj]) << 3;
        if ((nm1d2 < 0) && (apnd < MIN_int32_T - nm1d2)) {
          nm1d2 = MIN_int32_T;
        } else if ((nm1d2 > 0) && (apnd > MAX_int32_T - nm1d2)) {
          nm1d2 = MAX_int32_T;
        } else {
          nm1d2 += apnd;
        }

        lanedetection_B.jj += 160;
      }

      b_ndbl = ((nm1d2 & 512U) != 0U) + (nm1d2 >> 10);
      if (b_ndbl < 0) {
        b_ndbl = 0;
      } else {
        if (b_ndbl > 255) {
          b_ndbl = 255;
        }
      }

      lanedetection_B.Resize3[lanedetection_B.idx] = (uint8_T)b_ndbl;
      lanedetection_B.idx++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize3' */

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function1'
   */
  for (b_ndbl = 0; b_ndbl < 30; b_ndbl++) {
    for (lanedetection_B.idx = 0; lanedetection_B.idx < 160; lanedetection_B.idx
         ++) {
      lanedetection_B.dv0[lanedetection_B.idx + 160 * b_ndbl] =
        lanedetection_B.Resize3[(65 + b_ndbl) * 160 + lanedetection_B.idx];
    }
  }

  lanedetection_conv2(lanedetection_B.dv0, f, lanedetection_B.dv1);
  for (b_ndbl = 0; b_ndbl < 4800; b_ndbl++) {
    lanedetection_B.imgEdge[b_ndbl] = (uint8_T)((lanedetection_B.dv1[b_ndbl] >
      40.0) * 255U);
  }

  lanedetection_B.idx = 0;
  lanedetection_B.ii = 1;
  lanedetection_B.jj = 1;
  exitg1 = false;
  while ((!exitg1) && (lanedetection_B.jj <= 30)) {
    guard1 = false;
    if (lanedetection_B.imgEdge[((lanedetection_B.jj - 1) * 160 +
         lanedetection_B.ii) - 1] != 0) {
      lanedetection_B.idx++;
      lanedetection_B.i_data[lanedetection_B.idx - 1] = lanedetection_B.ii;
      lanedetection_B.j_data[lanedetection_B.idx - 1] = (int8_T)
        lanedetection_B.jj;
      if (lanedetection_B.idx >= 4800) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      lanedetection_B.ii++;
      if (lanedetection_B.ii > 160) {
        lanedetection_B.ii = 1;
        lanedetection_B.jj++;
      }
    }
  }

  if (1 > lanedetection_B.idx) {
    lanedetection_B.idx = 0;
    lanedetection_B.ii = 0;
  } else {
    lanedetection_B.ii = lanedetection_B.idx;
  }

  cdiff = lanedetection_B.idx;
  for (b_ndbl = 0; b_ndbl < lanedetection_B.idx; b_ndbl++) {
    lanedetection_B.x_data[b_ndbl] = lanedetection_B.i_data[b_ndbl];
  }

  nm1d2 = lanedetection_B.ii;
  for (b_ndbl = 0; b_ndbl < lanedetection_B.ii; b_ndbl++) {
    lanedetection_B.y_data[b_ndbl] = lanedetection_B.j_data[b_ndbl];
  }

  lanedetection_B.xCenter = rt_roundd_snf(lanedetection_mean
    (lanedetection_B.x_data, &cdiff));
  lanedetection_B.yCenter = rt_roundd_snf(lanedetection_mean
    (lanedetection_B.y_data, &nm1d2));
  if ((1.0 > lanedetection_B.xCenter - 2.0) || rtIsNaN(lanedetection_B.xCenter -
       2.0)) {
    lanedetection_B.maxval = 1.0;
  } else {
    lanedetection_B.maxval = lanedetection_B.xCenter - 2.0;
  }

  if (lanedetection_B.xCenter + 2.0 < 160.0) {
    lanedetection_B.minval = lanedetection_B.xCenter + 2.0;
  } else {
    lanedetection_B.minval = 160.0;
  }

  if (lanedetection_B.minval < lanedetection_B.maxval) {
    lanedetection_B.jj = 0;
  } else if (lanedetection_B.maxval == lanedetection_B.maxval) {
    cdiff = (int32_T)((real32_T)lanedetection_B.minval - (real32_T)
                      lanedetection_B.maxval);
    lanedetection_B.jj = cdiff + 1;
    for (b_ndbl = 0; b_ndbl <= cdiff; b_ndbl++) {
      lanedetection_B.xx_data[b_ndbl] = lanedetection_B.maxval + (real_T)b_ndbl;
    }
  } else {
    lanedetection_B.jj = (int32_T)floor((lanedetection_B.minval -
      lanedetection_B.maxval) + 0.5);
    apnd = (int32_T)lanedetection_B.maxval + lanedetection_B.jj;
    cdiff = apnd - (int32_T)lanedetection_B.minval;
    if ((int32_T)lanedetection_B.maxval > (int32_T)lanedetection_B.minval) {
      b_ndbl = (int32_T)lanedetection_B.maxval;
    } else {
      b_ndbl = (int32_T)lanedetection_B.minval;
    }

    if (fabs((real_T)cdiff) < 4.4408920985006262E-16 * (real_T)b_ndbl) {
      lanedetection_B.jj++;
      apnd = (int32_T)lanedetection_B.minval;
    } else if (cdiff > 0) {
      apnd = ((int32_T)lanedetection_B.maxval + lanedetection_B.jj) - 1;
    } else {
      lanedetection_B.jj++;
    }

    if (lanedetection_B.jj >= 0) {
      cdiff = lanedetection_B.jj - 1;
    } else {
      cdiff = -1;
    }

    lanedetection_B.jj = cdiff + 1;
    if (cdiff + 1 > 0) {
      lanedetection_B.xx_data[0] = lanedetection_B.maxval;
      if (cdiff + 1 > 1) {
        lanedetection_B.xx_data[cdiff] = apnd;
        nm1d2 = cdiff / 2;
        for (b_ndbl = 1; b_ndbl < nm1d2; b_ndbl++) {
          lanedetection_B.xx_data[b_ndbl] = lanedetection_B.maxval + (real_T)
            b_ndbl;
          lanedetection_B.xx_data[cdiff - b_ndbl] = apnd - b_ndbl;
        }

        if (nm1d2 << 1 == cdiff) {
          lanedetection_B.xx_data[nm1d2] = (lanedetection_B.maxval + (real_T)
            apnd) / 2.0;
        } else {
          lanedetection_B.xx_data[nm1d2] = lanedetection_B.maxval + (real_T)
            nm1d2;
          lanedetection_B.xx_data[nm1d2 + 1] = apnd - nm1d2;
        }
      }
    }
  }

  if ((1.0 > lanedetection_B.yCenter - 2.0) || rtIsNaN(lanedetection_B.yCenter -
       2.0)) {
    lanedetection_B.maxval = 1.0;
  } else {
    lanedetection_B.maxval = lanedetection_B.yCenter - 2.0;
  }

  if (lanedetection_B.yCenter + 2.0 < 30.0) {
    lanedetection_B.yCenter += 2.0;
  } else {
    lanedetection_B.yCenter = 30.0;
  }

  if (lanedetection_B.yCenter < lanedetection_B.maxval) {
    apnd = 0;
  } else if (lanedetection_B.maxval == lanedetection_B.maxval) {
    cdiff = (int32_T)((real32_T)lanedetection_B.yCenter - (real32_T)
                      lanedetection_B.maxval);
    apnd = cdiff + 1;
    for (b_ndbl = 0; b_ndbl <= cdiff; b_ndbl++) {
      lanedetection_B.b_y_data[b_ndbl] = lanedetection_B.maxval + (real_T)b_ndbl;
    }
  } else {
    b_ndbl = (int32_T)floor((lanedetection_B.yCenter - lanedetection_B.maxval) +
      0.5);
    cdiff = (int32_T)lanedetection_B.maxval + b_ndbl;
    apnd = cdiff - (int32_T)lanedetection_B.yCenter;
    if ((int32_T)lanedetection_B.maxval > (int32_T)lanedetection_B.yCenter) {
      nm1d2 = (int32_T)lanedetection_B.maxval;
    } else {
      nm1d2 = (int32_T)lanedetection_B.yCenter;
    }

    if (fabs((real_T)apnd) < 4.4408920985006262E-16 * (real_T)nm1d2) {
      b_ndbl++;
      cdiff = (int32_T)lanedetection_B.yCenter;
    } else if (apnd > 0) {
      cdiff = ((int32_T)lanedetection_B.maxval + b_ndbl) - 1;
    } else {
      b_ndbl++;
    }

    if (b_ndbl >= 0) {
      b_ndbl--;
    } else {
      b_ndbl = -1;
    }

    apnd = b_ndbl + 1;
    if (b_ndbl + 1 > 0) {
      lanedetection_B.b_y_data[0] = lanedetection_B.maxval;
      if (b_ndbl + 1 > 1) {
        lanedetection_B.b_y_data[b_ndbl] = cdiff;
        nm1d2 = b_ndbl / 2;
        lanedetection_B.indxTblX = 1;
        while (lanedetection_B.indxTblX <= nm1d2 - 1) {
          lanedetection_B.b_y_data[lanedetection_B.indxTblX] =
            lanedetection_B.maxval + (real_T)lanedetection_B.indxTblX;
          lanedetection_B.b_y_data[b_ndbl - lanedetection_B.indxTblX] = cdiff -
            lanedetection_B.indxTblX;
          lanedetection_B.indxTblX++;
        }

        if (nm1d2 << 1 == b_ndbl) {
          lanedetection_B.b_y_data[nm1d2] = (lanedetection_B.maxval + (real_T)
            cdiff) / 2.0;
        } else {
          lanedetection_B.b_y_data[nm1d2] = lanedetection_B.maxval + (real_T)
            nm1d2;
          lanedetection_B.b_y_data[nm1d2 + 1] = cdiff - nm1d2;
        }
      }
    }
  }

  memset(&lanedetection_B.CbDot[0], 0, 4800U * sizeof(uint8_T));
  if ((!(lanedetection_B.idx == 0)) && (!(lanedetection_B.ii == 0))) {
    for (b_ndbl = 0; b_ndbl < lanedetection_B.jj; b_ndbl++) {
      lanedetection_B.b_data[b_ndbl] = (int32_T)lanedetection_B.xx_data[b_ndbl];
    }

    for (b_ndbl = 0; b_ndbl < apnd; b_ndbl++) {
      lanedetection_B.c_data[b_ndbl] = (int32_T)lanedetection_B.b_y_data[b_ndbl];
    }

    for (b_ndbl = 0; b_ndbl < apnd; b_ndbl++) {
      for (lanedetection_B.idx = 0; lanedetection_B.idx < lanedetection_B.jj;
           lanedetection_B.idx++) {
        lanedetection_B.CbDot[(lanedetection_B.b_data[lanedetection_B.idx] + 160
          * (lanedetection_B.c_data[b_ndbl] - 1)) - 1] = MAX_uint8_T;
      }
    }
  } else {
    for (b_ndbl = 0; b_ndbl < lanedetection_B.jj; b_ndbl++) {
      lanedetection_B.b_data[b_ndbl] = (int32_T)lanedetection_B.xx_data[b_ndbl];
    }

    for (b_ndbl = 0; b_ndbl < apnd; b_ndbl++) {
      lanedetection_B.c_data[b_ndbl] = (int32_T)lanedetection_B.b_y_data[b_ndbl];
    }

    for (b_ndbl = 0; b_ndbl < apnd; b_ndbl++) {
      for (lanedetection_B.idx = 0; lanedetection_B.idx < lanedetection_B.jj;
           lanedetection_B.idx++) {
        lanedetection_B.CbDot[(lanedetection_B.b_data[lanedetection_B.idx] + 160
          * (lanedetection_B.c_data[b_ndbl] - 1)) - 1] = 0U;
      }
    }
  }

  for (b_ndbl = 0; b_ndbl < 4800; b_ndbl++) {
    lanedetection_B.idx = (int32_T)((uint32_T)lanedetection_B.imgEdge[b_ndbl] +
      lanedetection_B.CbDot[b_ndbl]);
    if ((uint32_T)lanedetection_B.idx > 255U) {
      lanedetection_B.idx = 255;
    }

    lanedetection_B.imgEdge[b_ndbl] = (uint8_T)lanedetection_B.idx;
  }

  /* S-Function (svipresize): '<Root>/Resize1' */
  /* use pre-computed weights and index table to perform interpolation */
  lanedetection_B.idx = 0;

  /* resize along X-axis direction */
  for (lanedetection_B.ii = 0; lanedetection_B.ii < 160; lanedetection_B.ii++) {
    lanedetection_B.jj = lanedetection_B.ii;
    for (cdiff = 0; cdiff < 30; cdiff++) {
      nm1d2 = (lanedetection_B.CbDot[cdiff * 160 + lanedetection_B.ii] * 127) <<
        3;
      lanedetection_DW.Resize1_IntBuffer[lanedetection_B.jj] = (uint8_T)(((nm1d2
        & 512U) != 0U) + (nm1d2 >> 10));
      lanedetection_B.jj += 160;
    }
  }

  /* resize along Y-axis direction */
  for (cdiff = 0; cdiff < 30; cdiff++) {
    lanedetection_B.jj = cdiff * 160;
    for (lanedetection_B.ii = 0; lanedetection_B.ii < 160; lanedetection_B.ii++)
    {
      lanedetection_DW.Resize1_LineBuffer[lanedetection_B.ii] =
        lanedetection_DW.Resize1_IntBuffer[lanedetection_B.jj];
      lanedetection_B.jj++;
    }

    for (lanedetection_B.ii = 0; lanedetection_B.ii < 80; lanedetection_B.ii++)
    {
      nm1d2 =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.ii]]
         * lanedetection_ConstP.pooled5[lanedetection_B.ii]) << 3;
      lanedetection_B.jj = lanedetection_B.ii + 80;
      apnd =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.jj]]
         * lanedetection_ConstP.pooled5[lanedetection_B.jj]) << 3;
      if ((nm1d2 < 0) && (apnd < MIN_int32_T - nm1d2)) {
        b_ndbl = MIN_int32_T;
      } else if ((nm1d2 > 0) && (apnd > MAX_int32_T - nm1d2)) {
        b_ndbl = MAX_int32_T;
      } else {
        b_ndbl = nm1d2 + apnd;
      }

      lanedetection_B.jj += 80;
      apnd =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.jj]]
         * lanedetection_ConstP.pooled5[lanedetection_B.jj]) << 3;
      if ((b_ndbl < 0) && (apnd < MIN_int32_T - b_ndbl)) {
        b_ndbl = MIN_int32_T;
      } else if ((b_ndbl > 0) && (apnd > MAX_int32_T - b_ndbl)) {
        b_ndbl = MAX_int32_T;
      } else {
        b_ndbl += apnd;
      }

      lanedetection_B.jj += 80;
      apnd =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.jj]]
         * lanedetection_ConstP.pooled5[lanedetection_B.jj]) << 3;
      if ((b_ndbl < 0) && (apnd < MIN_int32_T - b_ndbl)) {
        b_ndbl = MIN_int32_T;
      } else if ((b_ndbl > 0) && (apnd > MAX_int32_T - b_ndbl)) {
        b_ndbl = MAX_int32_T;
      } else {
        b_ndbl += apnd;
      }

      b_ndbl = ((b_ndbl & 512U) != 0U) + (b_ndbl >> 10);
      if (b_ndbl < 0) {
        b_ndbl = 0;
      } else {
        if (b_ndbl > 255) {
          b_ndbl = 255;
        }
      }

      lanedetection_B.Resize1[lanedetection_B.idx] = (uint8_T)b_ndbl;
      lanedetection_B.idx++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize1' */

  /* S-Function (svipresize): '<Root>/Resize2' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /* use pre-computed weights and index table to perform interpolation */
  lanedetection_B.idx = 0;

  /* resize along X-axis direction */
  for (lanedetection_B.ii = 0; lanedetection_B.ii < 160; lanedetection_B.ii++) {
    lanedetection_B.jj = lanedetection_B.ii;
    for (cdiff = 0; cdiff < 30; cdiff++) {
      nm1d2 = (lanedetection_B.CbDot[cdiff * 160 + lanedetection_B.ii] * 127) <<
        3;
      lanedetection_DW.Resize2_IntBuffer[lanedetection_B.jj] = (uint8_T)(((nm1d2
        & 512U) != 0U) + (nm1d2 >> 10));
      lanedetection_B.jj += 160;
    }
  }

  /* resize along Y-axis direction */
  for (cdiff = 0; cdiff < 30; cdiff++) {
    lanedetection_B.jj = cdiff * 160;
    for (lanedetection_B.ii = 0; lanedetection_B.ii < 160; lanedetection_B.ii++)
    {
      lanedetection_DW.Resize1_LineBuffer[lanedetection_B.ii] =
        lanedetection_DW.Resize2_IntBuffer[lanedetection_B.jj];
      lanedetection_B.jj++;
    }

    for (lanedetection_B.ii = 0; lanedetection_B.ii < 80; lanedetection_B.ii++)
    {
      nm1d2 =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.ii]]
         * lanedetection_ConstP.pooled5[lanedetection_B.ii]) << 3;
      lanedetection_B.jj = lanedetection_B.ii + 80;
      apnd =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.jj]]
         * lanedetection_ConstP.pooled5[lanedetection_B.jj]) << 3;
      if ((nm1d2 < 0) && (apnd < MIN_int32_T - nm1d2)) {
        b_ndbl = MIN_int32_T;
      } else if ((nm1d2 > 0) && (apnd > MAX_int32_T - nm1d2)) {
        b_ndbl = MAX_int32_T;
      } else {
        b_ndbl = nm1d2 + apnd;
      }

      lanedetection_B.jj += 80;
      apnd =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.jj]]
         * lanedetection_ConstP.pooled5[lanedetection_B.jj]) << 3;
      if ((b_ndbl < 0) && (apnd < MIN_int32_T - b_ndbl)) {
        b_ndbl = MIN_int32_T;
      } else if ((b_ndbl > 0) && (apnd > MAX_int32_T - b_ndbl)) {
        b_ndbl = MAX_int32_T;
      } else {
        b_ndbl += apnd;
      }

      lanedetection_B.jj += 80;
      apnd =
        (lanedetection_DW.Resize1_LineBuffer[lanedetection_ConstP.pooled2[lanedetection_B.jj]]
         * lanedetection_ConstP.pooled5[lanedetection_B.jj]) << 3;
      if ((b_ndbl < 0) && (apnd < MIN_int32_T - b_ndbl)) {
        b_ndbl = MIN_int32_T;
      } else if ((b_ndbl > 0) && (apnd > MAX_int32_T - b_ndbl)) {
        b_ndbl = MAX_int32_T;
      } else {
        b_ndbl += apnd;
      }

      b_ndbl = ((b_ndbl & 512U) != 0U) + (b_ndbl >> 10);
      if (b_ndbl < 0) {
        b_ndbl = 0;
      } else {
        if (b_ndbl > 255) {
          b_ndbl = 255;
        }
      }

      lanedetection_B.Resize2[lanedetection_B.idx] = (uint8_T)b_ndbl;
      lanedetection_B.idx++;
    }
  }

  /* End of S-Function (svipresize): '<Root>/Resize2' */
  /* Start for MATLABSystem: '<S3>/MATLAB System' */
  memcpy(&lanedetection_B.CbDot[0], &lanedetection_B.imgEdge[0], 4800U * sizeof
         (uint8_T));
  memcpy(&lanedetection_B.pln2[0], &lanedetection_B.Resize1[0], 2400U * sizeof
         (uint8_T));
  memcpy(&lanedetection_B.pln3[0], &lanedetection_B.Resize2[0], 2400U * sizeof
         (uint8_T));
  MW_SDL_videoDisplayOutput(lanedetection_B.CbDot, lanedetection_B.pln2,
    lanedetection_B.pln3);

  /* DataTypeConversion: '<Root>/Cast' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  if (rtIsNaN(lanedetection_B.xCenter - 80.0) || rtIsInf(lanedetection_B.xCenter
       - 80.0)) {
    lanedetection_B.xCenter = 0.0;
  } else {
    lanedetection_B.xCenter = fmod(lanedetection_B.xCenter - 80.0, 256.0);
  }

  lanedetection_B.Cast = (int8_T)(lanedetection_B.xCenter < 0.0 ? (int32_T)
    (int8_T)-(int8_T)(uint8_T)-lanedetection_B.xCenter : (int32_T)(int8_T)
    (uint8_T)lanedetection_B.xCenter);

  /* End of DataTypeConversion: '<Root>/Cast' */

  /* Start for MATLABSystem: '<Root>/Serial Write' */
  memcpy((void *)&TxDataLocChar, (void *)&lanedetection_B.Cast, (uint32_T)
         ((size_t)1 * sizeof(uint8_T)));
  MW_SCI_Transmit(lanedetection_DW.obj_n.MW_SCIHANDLE, &TxDataLocChar, 1U);

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

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)lanedetection_M, 0,
                sizeof(RT_MODEL_lanedetection_T));
  rtmSetTFinal(lanedetection_M, -1);
  lanedetection_M->Timing.stepSize0 = 0.05;

  /* External mode info */
  lanedetection_M->Sizes.checksums[0] = (2187559452U);
  lanedetection_M->Sizes.checksums[1] = (2390752517U);
  lanedetection_M->Sizes.checksums[2] = (2578938969U);
  lanedetection_M->Sizes.checksums[3] = (3153663096U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    lanedetection_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lanedetection_M->extModeInfo,
      &lanedetection_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lanedetection_M->extModeInfo,
                        lanedetection_M->Sizes.checksums);
    rteiSetTPtr(lanedetection_M->extModeInfo, rtmGetTPtr(lanedetection_M));
  }

  /* block I/O */
  (void) memset(((void *) &lanedetection_B), 0,
                sizeof(B_lanedetection_T));

  /* states (dwork) */
  (void) memset((void *)&lanedetection_DW, 0,
                sizeof(DW_lanedetection_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lanedetection_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 18;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;
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
    MW_videoCaptureInit(lanedetection_ConstP.V4L2VideoCapture_p1, 0, 0, 0, 0,
                        800U, 600U, 1U, 2U, 1U, 0.05);

    /* Start for MATLABSystem: '<S3>/MATLAB System' */
    lanedetection_DW.obj.matlabCodegenIsDeleted = true;
    lanedetection_DW.obj.isInitialized = 0;
    lanedetection_DW.obj.matlabCodegenIsDeleted = false;
    lanedetection_DW.obj.isSetupComplete = false;
    lanedetection_DW.obj.isInitialized = 1;
    lanedetection_DW.obj.PixelFormatEnum = 2;
    MW_SDL_videoDisplayInit(lanedetection_DW.obj.PixelFormatEnum, 1, 1, 160.0,
      30.0);
    lanedetection_DW.obj.isSetupComplete = true;

    /* End of Start for SubSystem: '<Root>/SDL Video Display' */

    /* Start for MATLABSystem: '<Root>/Serial Write' */
    lanedetection_DW.obj_n.matlabCodegenIsDeleted = true;
    lanedetection_DW.obj_n.isInitialized = 0;
    lanedetection_DW.obj_n.matlabCodegenIsDeleted = false;
    obj = &lanedetection_DW.obj_n;
    lanedetection_DW.obj_n.isSetupComplete = false;
    lanedetection_DW.obj_n.isInitialized = 1;
    RxPinLoc = MW_UNDEFINED_VALUE;
    TxPinLoc = MW_UNDEFINED_VALUE;
    for (i = 0; i < 12; i++) {
      SCIModuleLoc[i] = tmp[i];
    }

    SCIModuleLoc[12] = '\x00';
    obj->MW_SCIHANDLE = MW_SCI_Open(SCIModuleLoc, true, RxPinLoc, TxPinLoc);
    MW_SCI_SetBaudrate(lanedetection_DW.obj_n.MW_SCIHANDLE, 9600U);
    StopBitsValue = MW_SCI_STOPBITS_1;
    ParityValue = MW_SCI_PARITY_NONE;
    MW_SCI_SetFrameFormat(lanedetection_DW.obj_n.MW_SCIHANDLE, 8, ParityValue,
                          StopBitsValue);
    lanedetection_DW.obj_n.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/Serial Write' */
  }
}

/* Model terminate function */
void lanedetection_terminate(void)
{
  /* Terminate for S-Function (v4l2_video_capture_sfcn): '<Root>/V4L2 Video Capture' */
  MW_videoCaptureTerminate(lanedetection_ConstP.V4L2VideoCapture_p1);

  /* Terminate for MATLABSystem: '<S3>/MATLAB System' */
  matlabCodegenHandle_matlabCod_d(&lanedetection_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/SDL Video Display' */

  /* Terminate for MATLABSystem: '<Root>/Serial Write' */
  matlabCodegenHandle_matlabCodeg(&lanedetection_DW.obj_n);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
