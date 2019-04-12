/*
 * lanedetection_Kopie_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "lanedetection_Kopie".
 *
 * Model version              : 1.167
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C source code generated on : Fri Apr 12 12:20:22 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int8_T),
  sizeof(codertarget_linux_blocks_SDLV_T),
  sizeof(codertarget_raspi_internal_SC_T),
  sizeof(int32_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "int8_T",
  "codertarget_linux_blocks_SDLV_T",
  "codertarget_raspi_internal_SC_T",
  "int32_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&lanedetection_Kopie_B.V4L2VideoCapture_o1[0]), 3, 0, 38400 },

  { (char_T *)(&lanedetection_Kopie_B.Resize1[0]), 3, 0, 9600 },

  { (char_T *)(&lanedetection_Kopie_B.xCenter), 0, 0, 1 },

  { (char_T *)(&lanedetection_Kopie_B.Add), 2, 0, 1 }
  ,

  { (char_T *)(&lanedetection_Kopie_DW.obj), 15, 0, 1 },

  { (char_T *)(&lanedetection_Kopie_DW.obj_n), 16, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  6U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&lanedetection_Kopie_P.Gain_Gain), 0, 0, 1 },

  { (char_T *)(&lanedetection_Kopie_P.OffsetServo_Value), 2, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  2U,
  rtPTransitions
};

/* [EOF] lanedetection_Kopie_dt.h */
