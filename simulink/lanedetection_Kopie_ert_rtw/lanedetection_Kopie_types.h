/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: lanedetection_Kopie_types.h
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

#ifndef RTW_HEADER_lanedetection_Kopie_types_h_
#define RTW_HEADER_lanedetection_Kopie_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Custom Type definition for MATLABSystem: '<Root>/Serial Write' */
#include "MW_SVD.h"
#include <stddef.h>
#ifndef typedef_codertarget_raspi_internal_Ha_T
#define typedef_codertarget_raspi_internal_Ha_T

typedef struct {
  int32_T __dummy;
} codertarget_raspi_internal_Ha_T;

#endif                                 /*typedef_codertarget_raspi_internal_Ha_T*/

#ifndef typedef_codertarget_raspi_internal_SC_T
#define typedef_codertarget_raspi_internal_SC_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  codertarget_raspi_internal_Ha_T Hw;
  MW_Handle_Type MW_SCIHANDLE;
} codertarget_raspi_internal_SC_T;

#endif                                 /*typedef_codertarget_raspi_internal_SC_T*/

#ifndef typedef_codertarget_linux_blocks_SDLV_T
#define typedef_codertarget_linux_blocks_SDLV_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  int32_T PixelFormatEnum;
} codertarget_linux_blocks_SDLV_T;

#endif                                 /*typedef_codertarget_linux_blocks_SDLV_T*/

/* Parameters (default storage) */
typedef struct P_lanedetection_Kopie_T_ P_lanedetection_Kopie_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_lanedetection_Kopie_T RT_MODEL_lanedetection_Kopie_T;

#endif                                 /* RTW_HEADER_lanedetection_Kopie_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
