/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ServoControl.c
 *
 * Code generated for Simulink model 'ServoControl'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Mar 28 11:10:47 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ServoControl.h"
#include "ServoControl_private.h"
#include "ServoControl_dt.h"

/* Block signals (default storage) */
B_ServoControl_T ServoControl_B;

/* Block states (default storage) */
DW_ServoControl_T ServoControl_DW;

/* Real-time model */
RT_MODEL_ServoControl_T ServoControl_M_;
RT_MODEL_ServoControl_T *const ServoControl_M = &ServoControl_M_;

/* Forward declaration for local functions */
static void SystemProp_matlabCodegenSetAn_p(codertarget_raspi_internal__p_T *obj,
  boolean_T value);
static void ServoContr_SystemCore_release_p(const
  codertarget_raspi_internal__p_T *obj);
static void ServoContro_SystemCore_delete_p(const
  codertarget_raspi_internal__p_T *obj);
static void matlabCodegenHandle_matlabCod_p(codertarget_raspi_internal__p_T *obj);
static void SystemProp_matlabCodegenSetAnyP(codertarget_raspi_internal_SC_T *obj,
  boolean_T value);
static void ServoControl_SystemCore_release(const
  codertarget_raspi_internal_SC_T *obj);
static void ServoControl_SystemCore_delete(const codertarget_raspi_internal_SC_T
  *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_raspi_internal_SC_T *obj);
static void SystemProp_matlabCodegenSetAn_p(codertarget_raspi_internal__p_T *obj,
  boolean_T value)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  obj->matlabCodegenIsDeleted = value;
}

static void ServoContr_SystemCore_release_p(const
  codertarget_raspi_internal__p_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SCI_Close(obj->MW_SCIHANDLE);
  }

  /* End of Start for MATLABSystem: '<Root>/Serial Write' */
}

static void ServoContro_SystemCore_delete_p(const
  codertarget_raspi_internal__p_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  ServoContr_SystemCore_release_p(obj);
}

static void matlabCodegenHandle_matlabCod_p(codertarget_raspi_internal__p_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Write' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAn_p(obj, true);
    ServoContro_SystemCore_delete_p(obj);
  }

  /* End of Start for MATLABSystem: '<Root>/Serial Write' */
}

static void SystemProp_matlabCodegenSetAnyP(codertarget_raspi_internal_SC_T *obj,
  boolean_T value)
{
  /* Start for MATLABSystem: '<Root>/Serial Read' */
  obj->matlabCodegenIsDeleted = value;
}

static void ServoControl_SystemCore_release(const
  codertarget_raspi_internal_SC_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Read' */
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SCI_Close(obj->MW_SCIHANDLE);
  }

  /* End of Start for MATLABSystem: '<Root>/Serial Read' */
}

static void ServoControl_SystemCore_delete(const codertarget_raspi_internal_SC_T
  *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Read' */
  ServoControl_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_raspi_internal_SC_T *obj)
{
  /* Start for MATLABSystem: '<Root>/Serial Read' */
  if (!obj->matlabCodegenIsDeleted) {
    SystemProp_matlabCodegenSetAnyP(obj, true);
    ServoControl_SystemCore_delete(obj);
  }

  /* End of Start for MATLABSystem: '<Root>/Serial Read' */
}

/* Model step function */
void ServoControl_step(void)
{
  uint8_T TxDataLocChar;
  boolean_T p;
  boolean_T p_0;
  int8_T rtb_DataTypeConversion;
  real_T tmp;

  /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
   *  Constant: '<Root>/Constant'
   */
  tmp = floor(ServoControl_P.Constant_Value);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  rtb_DataTypeConversion = (int8_T)(tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)
    (uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp);

  /* End of DataTypeConversion: '<Root>/Data Type Conversion' */

  /* Start for MATLABSystem: '<Root>/Serial Write' */
  memcpy((void *)&TxDataLocChar, (void *)&rtb_DataTypeConversion, (uint32_T)
         ((size_t)1 * sizeof(uint8_T)));
  MW_SCI_Transmit(ServoControl_DW.obj_p.MW_SCIHANDLE, &TxDataLocChar, 1U);

  /* Start for MATLABSystem: '<Root>/Serial Read' */
  p = false;
  p_0 = true;
  if (!(ServoControl_DW.obj.SampleTime == ServoControl_P.SerialRead_SampleTime))
  {
    p_0 = false;
  }

  if (p_0) {
    p = true;
  }

  if (!p) {
    ServoControl_DW.obj.SampleTime = ServoControl_P.SerialRead_SampleTime;
  }

  /* MATLABSystem: '<Root>/Serial Read' */
  ServoControl_B.SerialRead_o2 = MW_SCI_Receive(ServoControl_DW.obj.MW_SCIHANDLE,
    &TxDataLocChar, 1U);

  /* Start for MATLABSystem: '<Root>/Serial Read' */
  memcpy((void *)&ServoControl_B.SerialRead_o1, (void *)&TxDataLocChar,
         (uint32_T)((size_t)1 * sizeof(uint8_T)));

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.1s, 0.0s] */
    rtExtModeUpload(0, ServoControl_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
    if ((rtmGetTFinal(ServoControl_M)!=-1) &&
        !((rtmGetTFinal(ServoControl_M)-ServoControl_M->Timing.taskTime0) >
          ServoControl_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(ServoControl_M, "Simulation finished");
    }

    if (rtmGetStopRequested(ServoControl_M)) {
      rtmSetErrorStatus(ServoControl_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  ServoControl_M->Timing.taskTime0 =
    (++ServoControl_M->Timing.clockTick0) * ServoControl_M->Timing.stepSize0;
}

/* Model initialize function */
void ServoControl_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ServoControl_M, 0,
                sizeof(RT_MODEL_ServoControl_T));
  rtmSetTFinal(ServoControl_M, -1);
  ServoControl_M->Timing.stepSize0 = 0.1;

  /* External mode info */
  ServoControl_M->Sizes.checksums[0] = (3898422131U);
  ServoControl_M->Sizes.checksums[1] = (161692338U);
  ServoControl_M->Sizes.checksums[2] = (421573838U);
  ServoControl_M->Sizes.checksums[3] = (523065627U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    ServoControl_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ServoControl_M->extModeInfo,
      &ServoControl_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(ServoControl_M->extModeInfo,
                        ServoControl_M->Sizes.checksums);
    rteiSetTPtr(ServoControl_M->extModeInfo, rtmGetTPtr(ServoControl_M));
  }

  /* block I/O */
  (void) memset(((void *) &ServoControl_B), 0,
                sizeof(B_ServoControl_T));

  /* states (dwork) */
  (void) memset((void *)&ServoControl_DW, 0,
                sizeof(DW_ServoControl_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    ServoControl_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    codertarget_raspi_internal__p_T *obj;
    uint32_T RxPinLoc;
    uint32_T TxPinLoc;
    MW_SCI_StopBits_Type StopBitsValue;
    MW_SCI_Parity_Type ParityValue;
    codertarget_raspi_internal_SC_T *obj_0;
    static const char_T tmp[12] = { '/', 'd', 'e', 'v', '/', 't', 't', 'y', 'A',
      'C', 'M', '0' };

    int32_T i;

    /* Start for MATLABSystem: '<Root>/Serial Write' */
    ServoControl_DW.obj_p.matlabCodegenIsDeleted = true;
    ServoControl_DW.obj_p.isInitialized = 0;
    ServoControl_DW.obj_p.matlabCodegenIsDeleted = false;
    obj = &ServoControl_DW.obj_p;
    ServoControl_DW.obj_p.isSetupComplete = false;
    ServoControl_DW.obj_p.isInitialized = 1;
    RxPinLoc = MW_UNDEFINED_VALUE;
    TxPinLoc = MW_UNDEFINED_VALUE;
    for (i = 0; i < 12; i++) {
      ServoControl_B.SCIModuleLoc[i] = tmp[i];
    }

    ServoControl_B.SCIModuleLoc[12] = '\x00';
    obj->MW_SCIHANDLE = MW_SCI_Open(ServoControl_B.SCIModuleLoc, true, RxPinLoc,
      TxPinLoc);
    MW_SCI_SetBaudrate(ServoControl_DW.obj_p.MW_SCIHANDLE, 9600U);
    StopBitsValue = MW_SCI_STOPBITS_1;
    ParityValue = MW_SCI_PARITY_NONE;
    MW_SCI_SetFrameFormat(ServoControl_DW.obj_p.MW_SCIHANDLE, 8, ParityValue,
                          StopBitsValue);
    ServoControl_DW.obj_p.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/Serial Write' */

    /* Start for MATLABSystem: '<Root>/Serial Read' */
    ServoControl_DW.obj.matlabCodegenIsDeleted = true;
    ServoControl_DW.obj.isInitialized = 0;
    ServoControl_DW.obj.matlabCodegenIsDeleted = false;
    ServoControl_DW.obj.SampleTime = ServoControl_P.SerialRead_SampleTime;
    obj_0 = &ServoControl_DW.obj;
    ServoControl_DW.obj.isSetupComplete = false;
    ServoControl_DW.obj.isInitialized = 1;
    RxPinLoc = MW_UNDEFINED_VALUE;
    TxPinLoc = MW_UNDEFINED_VALUE;
    for (i = 0; i < 12; i++) {
      ServoControl_B.SCIModuleLoc[i] = tmp[i];
    }

    ServoControl_B.SCIModuleLoc[12] = '\x00';
    obj_0->MW_SCIHANDLE = MW_SCI_Open(ServoControl_B.SCIModuleLoc, true,
      RxPinLoc, TxPinLoc);
    MW_SCI_SetBaudrate(ServoControl_DW.obj.MW_SCIHANDLE, 9600U);
    StopBitsValue = MW_SCI_STOPBITS_1;
    ParityValue = MW_SCI_PARITY_NONE;
    MW_SCI_SetFrameFormat(ServoControl_DW.obj.MW_SCIHANDLE, 8, ParityValue,
                          StopBitsValue);
    ServoControl_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/Serial Read' */
  }
}

/* Model terminate function */
void ServoControl_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Write' */
  matlabCodegenHandle_matlabCod_p(&ServoControl_DW.obj_p);

  /* Terminate for MATLABSystem: '<Root>/Serial Read' */
  matlabCodegenHandle_matlabCodeg(&ServoControl_DW.obj);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
