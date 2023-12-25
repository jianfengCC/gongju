/**
* Copyright (c) 2018-2023 ThunderSoft
* All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
* You may not use, copy, distribute, modify, transmit in any form this file
* except in compliance with ThunderSoft in writing by applicable law.
*
*/
/**
* @file    ivi_send.h
* @brief   ivi send function.
* @details detailed function description.
* @version 1.0
* @author  cuiliu
* @date    2023-04-21
*
* Edit History
* ----------------------------------------------------------------------------
* DATE                     NAME               DESCRIPTION
* 2023-04-21               cuiliu             Create it.
*
*/

#ifndef  _IVI_SEND_H_
#define  _IVI_SEND_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "RTE.h"
typedef unsigned char   BOOL;


struct package_0x35F_st_TBOX_chargeSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t tbox_VehicleRepairModeFB;
    uint8_t TBOX_VehiclePositioSts;
    uint8_t tbox_ChargeEndTimeHour;
    uint8_t tbox_ChargeEndTimeMinute;
    uint8_t tbox_ChargeStartTimeHour;
    uint8_t tbox_ChargeStartTimeMinute;
    uint8_t tbox_MaxChargeSOCSet;
    uint8_t tbox_ChargeEndTimeValid;
    uint8_t tbox_ChargeStartTimeValid;
}p_TBOX_chargeSet_st = {0x03, 0x5F, 10};

struct package_0x514_st_BMS_metric
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bms_SOC_H;
    uint8_t bms_SOC_L;
    uint8_t bms_SOH_H;
    uint8_t bms_SOH_L;
    uint8_t bms_SOE_H;
    uint8_t bms_SOE_L;
    uint8_t bms_SOCActual_H;
    uint8_t bms_SOCActual_L;
    uint8_t bms_maxChargeSOC;
    uint8_t BMS_BatterFaultLightContro;
    uint8_t BMS_BatteryTempLowLight;
    uint8_t BMS_NavigChrgPostFB;
    uint8_t bms_stEgyFlowSysDischRgn;
    uint8_t bms_stEgyFlowOBCAndBatt;
    uint8_t bms_chargeFormstatus;
}p_BMS_metric_st = {0x05, 0x14, 16};

struct package_0x574_st_BMS_tboxRequest
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bms_remainChargeTime_H;
    uint8_t bms_remainChargeTime_L;
    uint8_t bms_ChgAmount_H;
    uint8_t bms_ChgAmount_L;
}p_BMS_tboxRequest_st = {0x05, 0x74, 5};

struct package_0x561_st_VCU_range
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_avgPwr_H;
    uint8_t vcu_avgPwr_L;
    uint8_t vcu_alertLevel;
    uint8_t VCU_chargeFaultReason;
    uint8_t VCU_RegenWeakRemind;
}p_VCU_range_st = {0x05, 0x61, 6};

struct package_0x351_st_VCU_range1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_remainingMileage_H;
    uint8_t vcu_remainingMileage_L;
    uint8_t vcu_ComprehensiveRemainingMileage_H;
    uint8_t vcu_ComprehensiveRemainingMileage_L;
    uint8_t vcu_SysAlertLevel;
    uint8_t VCU_PowerLimitLight;
    uint8_t VCU_SysFaultLight;
    uint8_t VCU_LVPowSupSYSAbn_lit;
    uint8_t VCU_UserGearReq;
    uint8_t VCU_PowerManageSt;
    uint8_t vcu_PwroCrntTrip_H;
    uint8_t vcu_PwroCrntTrip_L;
}p_VCU_range1_st = {0x03, 0x51, 13};

struct package_0x111_st_VCU_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_accelPos_H;
    uint8_t vcu_accelPos_L;
    uint8_t vcu_BrakeWarning;
}p_VCU_state_st = {0x01, 0x11, 4};

struct package_0x311_st_VCU_vehicle
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t VCU_CLTCRemaininingMileage_H;
    uint8_t VCU_CLTCRemaininingMileage_L;
}p_VCU_vehicle_st = {0x03, 0x11, 3};

struct package_0x387_st_OBC_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t obc_state;
    uint8_t obc_batteryConnectStatus_;
    uint8_t obc_CcResistance;
}p_OBC_state_st = {0x03, 0x87, 4};

struct package_0x407_st_OBC_state1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t obc_DCVoltage_H;
    uint8_t obc_DCVoltage_L;
    uint8_t obc_DCCurrent_H;
    uint8_t obc_DCCurrent_L;
}p_OBC_state1_st = {0x04, 0x07, 5};

struct package_0x38D_st_DCDC_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t dcdc_systemStatus;
    uint8_t dcdc_deratingStatus;
    uint8_t dcdc_realOutputCurrent_H;
    uint8_t dcdc_realOutputCurrent_L;
}p_DCDC_state_st = {0x03, 0x8D, 5};

struct package_0x309_st_GSM_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gsm_NoticeReq;
    uint8_t gsm_gearSelectorPos;
}p_GSM_state_st = {0x03, 0x09, 3};

struct package_0x38A_st_GTW_mcur0_mcuf0_info
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mcur0_torqueEst_H;
    uint8_t mcur0_torqueEst_L;
    uint8_t mcuf0_torqueEst_H;
    uint8_t mcuf0_torqueEst_L;
}p_GTW_mcur0_mcuf0_info_st = {0x03, 0x8A, 5};

struct package_0x304_st_BMS_temperature
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bms_packTempMax_H;
    uint8_t bms_packTempMax_L;
    uint8_t bms_packTempMin_H;
    uint8_t bms_packTempMin_L;
    uint8_t bms_packTempAvg_H;
    uint8_t bms_packTempAvg_L;
}p_BMS_temperature_st = {0x03, 0x04, 7};

struct package_0x331_st_VCU_Info
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_Rev_VehicleHVpower_H;
    uint8_t vcu_Rev_VehicleHVpower_L;
    uint8_t vcu_stEgyFlowGenMotAndBatt;
    uint8_t vcu_stEgyFlowEngAndGenMot;
    uint8_t VCU_stEgyFlowMcuf0AndBatt;
    uint8_t VCU_stEgyFlowMcur0AndBatt;
    uint8_t VCU_IVI_HVDownRepairMode;
    uint8_t VCU_LowFuel;
    uint8_t VCU_LowSOC;
    uint8_t vcu_obcDschrgAllow;
    uint8_t vcu_v2vChrgFdbk;
    uint8_t vcu_obcDschrgFdbk;
    uint8_t vcu_v2vChrgOutCurntFdbk;
    uint8_t VCU_MaxFuelConsumptionSt;
    uint8_t VCU_MaxFuelConsumptionModeSt;
    uint8_t vcu_RangeExtenderNoSt;
}p_VCU_Info_st = {0x03, 0x31, 17};

struct package_0x10C_st_GCU_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gcu_MotorControlMode;
}p_GCU_state_st = {0x01, 0x0C, 2};

struct package_0x7DF_st_Diag_FuncReq
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t Diag_FuncReq_Data_8;
    uint8_t Diag_FuncReq_Data_7;
    uint8_t Diag_FuncReq_Data_6;
    uint8_t Diag_FuncReq_Data_5;
    uint8_t Diag_FuncReq_Data_4;
    uint8_t Diag_FuncReq_Data_3;
    uint8_t Diag_FuncReq_Data_2;
    uint8_t Diag_FuncReq_Data_1;
}p_Diag_FuncReq_st = {0x07, 0xDF, 9};

struct package_0x301_st_VCU_pwr
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_avgPwrCurrentTrip_H;
    uint8_t vcu_avgPwrCurrentTrip_L;
    uint8_t vcu_avgPwrSincelastcharge_H;
    uint8_t vcu_avgPwrSincelastcharge_L;
    uint8_t vcu_avgPwroftripA_H;
    uint8_t vcu_avgPwroftripA_L;
    uint8_t vcu_PwroftripB_H;
    uint8_t vcu_PwroftripB_L;
    uint8_t vcu_avgPwroftripB_H;
    uint8_t vcu_avgPwroftripB_L;
    uint8_t vcu_lowSocwarming;
    uint8_t VCU_SysFaulttext;
}p_VCU_pwr_st = {0x03, 0x01, 13};

struct package_0x330_st_VCU_RevV2V
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_v2vChrgAllow;
    uint8_t vcu_v2vChrgOptVoltg_H;
    uint8_t vcu_v2vChrgOptVoltg_L;
    uint8_t vcu_v2vChrgOptCurnt_H;
    uint8_t vcu_v2vChrgOptCurnt_L;
    uint8_t VCU_InstantaneousPower_H;
    uint8_t VCU_InstantaneousPower_L;
    uint8_t VCU_ConveyerBeltMode;
}p_VCU_RevV2V_st = {0x03, 0x30, 9};

struct package_0x3A4_st_BMS_ASSt
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t BMS_ThrmlRunawaySt;
    uint8_t BMS_ThrmlForecastersSt;
    uint8_t BMS_AcFullChargeToWarmState;
    uint8_t BMS_3A4_RollingCounter;
    uint8_t BMS_3A4_Checksum;
}p_BMS_ASSt_st = {0x03, 0xA4, 6};

struct package_0x3A1_st_VCU_stateCha1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_driveMode;
    uint8_t VCU_SuperPowerSavingModeSt;
    uint8_t VCU_SuperPowerSavingModeReq;
    uint8_t VCU_PercentInstantaneousPower;
    uint8_t VCU_SuperPowerSavingModeFaultReason;
    uint8_t Vcu_ParkingChargeFB;
    uint8_t Vcu_ParkingChargeModFB;
    uint8_t vcu_towMode;
    uint8_t vcu_ready;
    uint8_t vcu_traveModeSts;
    uint8_t vcu_highVoltagefaultSts;
    uint8_t VCU_VehicleRepairModeFB;
    uint8_t VCU_CampModeSts;
    uint8_t vcu_RegenModeStatus;
    uint8_t VCU_RangeExtenderSt;
    uint8_t vcu_highVoltageSuccess;
    uint8_t vcu_hvOnMode;
    uint8_t vcu_VehicleMode;
    uint8_t vcu_memoryStatus;
    uint8_t VCU_Eng_SelfShieldStart;
    uint8_t VCU_ExhibitionRequest;
    uint8_t VCU_TrailerModeSts;
    uint8_t vcu_ExhibitionMode;
}p_VCU_stateCha1_st = {0x03, 0xA1, 24};

struct package_0x124_st_EPS_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t eps_warningLamp;
    uint8_t eps_rollingCounter;
    uint8_t eps_checksum;
}p_EPS_state_st = {0x01, 0x24, 4};

struct package_0x144_st_EPS_sas
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t eps_sasSteeringAngle_H;
    uint8_t eps_sasSteeringAngle_L;
    uint8_t eps_sasRawSteeringAngle_H;
    uint8_t eps_sasRawSteeringAngle_L;
    uint8_t eps_sasSteeringAngleSpd_H;
    uint8_t eps_sasSteeringAngleSpd_L;
    uint8_t eps_sasSteeringAngleSpdValid;
    uint8_t eps_calibratedStatus;
    uint8_t eps_sasSteeringAngleValid;
}p_EPS_sas_st = {0x01, 0x44, 10};

struct package_0x142_st_ESC_wheelSpd_Front
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_wheelSpeedFL_H;
    uint8_t esc_wheelSpeedFL_L;
    uint8_t esc_wheelSpeedFLValid;
    uint8_t esc_wheelSpeedFR_H;
    uint8_t esc_wheelSpeedFR_L;
    uint8_t esc_wheelSpeedFRValid;
    uint8_t esc_142_rollingCounter;
    uint8_t esc_142_checksum;
}p_ESC_wheelSpd_Front_st = {0x01, 0x42, 9};

struct package_0x122_st_ESC_wheelSpd_Rear
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_wheelSpeedRL_H;
    uint8_t esc_wheelSpeedRL_L;
    uint8_t esc_wheelSpeedRLValid;
    uint8_t esc_wheelSpeedRR_H;
    uint8_t esc_wheelSpeedRR_L;
    uint8_t esc_wheelSpeedRRValid;
    uint8_t esc_122_rollingCounter;
    uint8_t esc_122_checksum;
}p_ESC_wheelSpd_Rear_st = {0x01, 0x22, 9};

struct package_0x212_st_ESC_state1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_vehicleSpeed_H;
    uint8_t esc_vehicleSpeed_L;
    uint8_t esc_vehicleSpeedValid;
    uint8_t esc_absFault;
    uint8_t esc_absActive;
    uint8_t esc_escActive;
    uint8_t esc_tcsActive;
    uint8_t esc_avhActive;
    uint8_t esc_avhStandby;
    uint8_t esc_avhAvailable;
    uint8_t esc_cdpActive;
    uint8_t esc_hdcStatus;
    uint8_t esc_hdcAvailable;
    uint8_t esc_hhcAvailable;
    uint8_t esc_ebdFault;
    uint8_t esc_offStatus;
    uint8_t esc_escFault;
    uint8_t esc_emergencyBrakeSts;
    uint8_t esc_212_rollingCounter;
    uint8_t esc_212_checksum;
}p_ESC_state1_st = {0x02, 0x12, 21};

struct package_0x2A2_st_ESC_state2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_hmiWarningOn;
    uint8_t esc_hmiWarningOn_Q;
    uint8_t esc_2A2_rollingCounter;
    uint8_t esc_2A2_checksum;
}p_ESC_state2_st = {0x02, 0xA2, 5};

struct package_0x252_st_ESC_yawState
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_longAcceleration_H;
    uint8_t esc_longAcceleration_L;
    uint8_t esc_longAccelerationValid;
    uint8_t esc_yawRateValid;
    uint8_t esc_yawRate_H;
    uint8_t esc_yawRate_L;
}p_ESC_yawState_st = {0x02, 0x52, 7};

struct package_0x3FB_st_GW_ESC_yawState
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t apa_funcSts;
    uint8_t APA_laeb_BrkReq;
}p_GW_ESC_yawState_st = {0x03, 0xFB, 3};

struct package_0x272_st_ESC_wssFront
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_wheelDirectionFLValid;
    uint8_t esc_wheelDirectionFRValid;
    uint8_t esc_wheelDirectionFL;
    uint8_t esc_wheelDirectionFR;
    uint8_t esc_272_rollingCounter;
    uint8_t esc_272_checksum;
}p_ESC_wssFront_st = {0x02, 0x72, 7};

struct package_0x282_st_ESC_wssRear
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_wheelDirectionRLValid;
    uint8_t esc_wheelDirectionRRValid;
    uint8_t esc_wheelDirectionRL;
    uint8_t esc_wheelDirectionRR;
}p_ESC_wssRear_st = {0x02, 0x82, 5};

struct package_0x2C2_st_ESC_epb
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_epbFaultLamp;
    uint8_t esc_epbParkingLamp;
    uint8_t esc_epbTextDisplay;
    uint8_t esc_epbStatus;
    uint8_t ESC_BrakeLevelAlarm;
    uint8_t esc_2C2_rollingCounter;
    uint8_t esc_2C2_checkSum;
}p_ESC_epb_st = {0x02, 0xC2, 8};

struct package_0x219_st_MRR_acc
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_accMode;
    uint8_t mrr_RCTBOnOffStatus;
    uint8_t mrr_219_RollingCounter;
    uint8_t mrr_219_CheckSum;
}p_MRR_acc_st = {0x02, 0x19, 5};

struct package_0x239_st_MRR_pss
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_EBAReq;
    uint8_t mrr_aebReq;
    uint8_t mrr_aebOnOffStatus;
    uint8_t mrr_accTakeOverReq;
    uint8_t mrr_vSetDis_H;
    uint8_t mrr_vSetDis_L;
    uint8_t mrr_PEBSWarning;
    uint8_t mrr_timeGapSet;
    uint8_t mrr_pcwOnOffStatus;
    uint8_t mrr_textInfo;
    uint8_t mrr_BlockedSt;
    uint8_t mrr_SystemFailureSt;
    uint8_t mrr_239_RollingCounter;
    uint8_t mrr_239_CheckSum;
}p_MRR_pss_st = {0x02, 0x39, 15};

struct package_0x349_st_MRR_hmi1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_ACC_TargetType;
    uint8_t mrr_ACC_TargetDetection;
    uint8_t mrr_ACC_TargetRange_H;
    uint8_t mrr_ACC_TargetRange_L;
    uint8_t mrr_ACC_RelevantTargetLatRange_H;
    uint8_t mrr_ACC_RelevantTargetLatRange_L;
}p_MRR_hmi1_st = {0x03, 0x49, 7};

struct package_0x369_st_MRR_hmi2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_ACC_LeftTargetType;
    uint8_t mrr_ACC_LeftTargetDetection;
    uint8_t mrr_ACC_LeftTargetLngRange_H;
    uint8_t mrr_ACC_LeftTargetLngRange_L;
    uint8_t mrr_ACC_LeftTargetLatRange_H;
    uint8_t mrr_ACC_LeftTargetLatRange_L;
    uint8_t mrr_ACC_RightTargetType;
    uint8_t mrr_ACC_RightTargetLngRange_H;
    uint8_t mrr_ACC_RightTargetLngRange_L;
    uint8_t mrr_ACC_RightTargetLatRange_H;
    uint8_t mrr_ACC_RightTargetLatRange_L;
    uint8_t mrr_ACC_RightTargetDetection;
}p_MRR_hmi2_st = {0x03, 0x69, 13};

struct package_0x34E_st_MRR_hmi3_34E
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_ACC_TargetType2;
    uint8_t mrr_ACC_TargetDetection2;
    uint8_t mrr_ACC_TargetRange2_H;
    uint8_t mrr_ACC_TargetRange2_L;
    uint8_t mrr_ACC_RelevantTargetLatRange2_H;
    uint8_t mrr_ACC_RelevantTargetLatRange2_L;
}p_MRR_hmi3_34E_st = {0x03, 0x4E, 7};

struct package_0x34F_st_MRR_hmi4_34F
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_ACC_LeftTargetType2;
    uint8_t mrr_ACC_LeftTargetDetection2;
    uint8_t mrr_ACC_LeftTargetLngRange2_H;
    uint8_t mrr_ACC_LeftTargetLngRange2_L;
    uint8_t mrr_ACC_LeftTargetLatRange2_H;
    uint8_t mrr_ACC_LeftTargetLatRange2_L;
    uint8_t mrr_ACC_RightTargetType2;
    uint8_t mrr_ACC_RightTargetLngRange2_H;
    uint8_t mrr_ACC_RightTargetLngRange2_L;
    uint8_t mrr_ACC_RightTargetLatRange2_H;
    uint8_t mrr_ACC_RightTargetLatRange2_L;
    uint8_t mrr_ACC_RightTargetDetection2;
}p_MRR_hmi4_34F_st = {0x03, 0x4F, 13};

struct package_0x355_st_MRR_hmi5_355
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_ACC_TargetType3;
    uint8_t mrr_ACC_TargetDetection3;
    uint8_t mrr_ACC_TargetRange3_H;
    uint8_t mrr_ACC_TargetRange3_L;
    uint8_t mrr_ACC_RelevantTargetLatRange3_H;
    uint8_t mrr_ACC_RelevantTargetLatRange3_L;
}p_MRR_hmi5_355_st = {0x03, 0x55, 7};

struct package_0x356_st_MRR_hmi6_356
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mrr_ACC_LeftTargetType3;
    uint8_t mrr_ACC_LeftTargetDetection3;
    uint8_t mrr_ACC_LeftTargetLngRange3_H;
    uint8_t mrr_ACC_LeftTargetLngRange3_L;
    uint8_t mrr_ACC_LeftTargetLatRange3_H;
    uint8_t mrr_ACC_LeftTargetLatRange3_L;
    uint8_t mrr_ACC_RightTargetType3;
    uint8_t mrr_ACC_RightTargetLngRange3_H;
    uint8_t mrr_ACC_RightTargetLngRange3_L;
    uint8_t mrr_ACC_RightTargetLatRange3_H;
    uint8_t mrr_ACC_RightTargetLatRange3_L;
    uint8_t mrr_ACC_RightTargetDetection3;
}p_MRR_hmi6_356_st = {0x03, 0x56, 13};

struct package_0x21A_st_MPC_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mpc_leftVisualization;
    uint8_t mpc_rightVisualization;
    uint8_t mpc_laneAssitType;
    uint8_t mpc_slaSpeedLimitUnits;
    uint8_t mpc_lasStatus;
    uint8_t mpc_lasWarningModeSelection;
    uint8_t mpc_adasTakeoverReq;
    uint8_t mpc_IACCStatus;
    uint8_t mpc_hmaStatus;
    uint8_t mpc_hmaHighbeamReq;
    uint8_t mpc_slaStatus;
    uint8_t mpc_slaSpeedLimit;
    uint8_t mpc_slaOnOffSts;
    uint8_t mpc_hmaOnOffSts;
    uint8_t mpc_rollingCounter;
    uint8_t mpc_checkSum;
}p_MPC_state_st = {0x02, 0x1A, 17};

struct package_0x35A_st_MPC_hmi
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mpc_LAS_roadCurvature;
    uint8_t mpc_LAS_LLaneDistance;
    uint8_t mpc_LAS_RLaneDistance;
    uint8_t mpc_LAS_LLaneMarkerType;
    uint8_t mpc_LAS_RLaneMarkerType;
    uint8_t MPC_FrontCameraeStatus;
    uint8_t MPC_textinfor;
    uint8_t MPC_TJAonoffStatus;
    uint8_t MPC_LLLaneMarkerType;
    uint8_t MPC_LLLaneDistance;
    uint8_t MPC_RRLaneDistance;
    uint8_t MPC_RRLaneMarkerType;
    uint8_t MPC_LleftVisualization;
    uint8_t MPC_RrightVisualization;
    uint8_t MPC_autododgeOnOffSts;
}p_MPC_hmi_st = {0x03, 0x5A, 16};

struct package_0x359_st_MPC_RoadState_359
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t MPC_LaneEquationC1_H;
    uint8_t MPC_LaneEquationC1_L;
    uint8_t MPC_LaneEquationC2_H;
    uint8_t MPC_LaneEquationC2_L;
    uint8_t MPC_LaneEquationC3_H;
    uint8_t MPC_LaneEquationC3_L;
    uint8_t MPC_LaneEquationStatus;
    uint8_t MPC_RoadCurvatureNear;
    uint8_t MPC_RoadCurvatureFar;
}p_MPC_RoadState_359_st = {0x03, 0x59, 10};

struct package_0x35D_st_MPC_hmi_35D
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t MPC_ELKSet;
    uint8_t MPC_ELKSts;
    uint8_t MPC_ISASet;
    uint8_t MPC_ISASts;
    uint8_t MPC_ISASpeedLimit_AddSignType;
    uint8_t MPC_ISAVisualWarnSts;
    uint8_t MPC_ISAAcousticWarnSts;
    uint8_t ADS_ConditionalCheck;
    uint8_t ADS_FactoryResetResult;
    uint8_t ADS_FactoryResetTime_H;
    uint8_t ADS_FactoryResetTime_L;
    uint8_t MPC_ISASpeedLimit_ModeStatus;
    uint8_t mpc_ElksWarning;
    uint8_t mpc_ISASpeedLimit;
    uint8_t ADS_MapCountryCode;
}p_MPC_hmi_35D_st = {0x03, 0x5D, 16};

struct package_0x22B_st_SRR_R_state_22B
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t SRR_r_ctaWarningReqRight;
    uint8_t SRR_r_bsdLCAWarningReqRight;
    uint8_t SRR_r_displayInfo;
    uint8_t SRR_r_bsdLCASts;
    uint8_t SRR_r_ctaSts;
    uint8_t SRR_r_dowSts;
    uint8_t SRR_r_ctaWarningReqLeft;
    uint8_t SRR_r_bsdLCAWarningReqLeft;
    uint8_t SRR_R_DOWFrontLeftDoorWarn;
    uint8_t SRR_R_DOWRearLeftDoorWarn;
    uint8_t SRR_R_DOWFrontRightDoorWarn;
    uint8_t SRR_R_DOWRearRightDoorWarn;
    uint8_t SRR_RCTBOnOffStatus;
    uint8_t Rear_radar_RCTB_Waring;
}p_SRR_R_state_22B_st = {0x02, 0x2B, 15};

struct package_0x3AC_st_ADS_RPA_3AC
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_ParkDirCfm;
    uint8_t ADS_ParkOutDir_ParaLe;
    uint8_t ADS_ParkOutDir_ParaRi;
    uint8_t ADS_ParkOutDir_PerpFwd;
    uint8_t ADS_ParkOutDir_PerpLeFwd;
    uint8_t ADS_ParkOutDir_PerpRiFwd;
    uint8_t ADS_ParkOutDir_PerpLeBack;
    uint8_t ADS_ParkOutDir_PerpRiBack;
    uint8_t ADS_ParkOutDir_PerpBack;
}p_ADS_RPA_3AC_st = {0x03, 0xAC, 10};

struct package_0x3A8_st_ADS_RPA_3A8
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_actualGear;
}p_ADS_RPA_3A8_st = {0x03, 0xA8, 2};

struct package_0x380_st_ABM_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t acu_warningLampStatus;
    uint8_t acu_crashOutputStatusValid;
    uint8_t acu_crashOutputStatus;
    uint8_t ABM_PassAirbSuppressionSt;
    uint8_t acu_driverSeatBeltStatus;
    uint8_t acu_driverSeatBeltStatusValid;
    uint8_t acu_passengerSeatBeltStatus;
    uint8_t acu_passengerSeatBeltStatusValid;
    uint8_t acu_rollingCounter_;
    uint8_t acu_checksum_;
}p_ABM_state_st = {0x03, 0x80, 11};

struct package_0x35B_st_APA_35B
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t APA_voice_reminder;
    uint8_t APA_textinfo;
    uint8_t APA_FinishReason;
}p_APA_35B_st = {0x03, 0x5B, 4};

struct package_0x345_st_ADS_TDU_STATE_345
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t MDC_FuncReq_SentryModDetect;
    uint8_t MDC_FuncReq_SentryModWarn;
}p_ADS_TDU_STATE_345_st = {0x03, 0x45, 3};

struct package_0x2AA_st_ADS_WarningSt_2AA
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_Fault;
    uint8_t ADS_NicaReminderLEDVisual;
    uint8_t ADS_NicaReminderAcoustic;
    uint8_t ADS_2AA_Counter;
    uint8_t ADS_2AA_Checksum;
}p_ADS_WarningSt_2AA_st = {0x02, 0xAA, 6};

struct package_0x2AB_st_ADS_WarningSt_2AB
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_TakeoverLevel;
    uint8_t ADS_TakeoverID_H;
    uint8_t ADS_TakeoverID_L;
    uint8_t ADS_TORIDCorrespErrorID_H;
    uint8_t ADS_TORIDCorrespErrorID_L;
    uint8_t ADS_TakeoverExtended1_H;
    uint8_t ADS_TakeoverExtended1_L;
    uint8_t ADS_TakeoverExtended2;
}p_ADS_WarningSt_2AB_st = {0x02, 0xAB, 9};

struct package_0x2AD_st_ADS_RadarWarningSt_2AD
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_RadarWarnSection0Distance;
    uint8_t ADS_RadarWarnSection1Distance;
    uint8_t ADS_RadarWarnSection2Distance;
    uint8_t ADS_RadarWarnSection3Distance;
    uint8_t ADS_RadarWarnSection4Distance;
    uint8_t ADS_RadarWarnSection5Distance;
    uint8_t ADS_RadarWarnSection6Distance;
    uint8_t ADS_RadarWarnSection7Distance;
}p_ADS_RadarWarningSt_2AD_st = {0x02, 0xAD, 9};

struct package_0x2AF_st_ADS_RadarWarningSt_2AF
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_RadarWarnSection8Distance;
    uint8_t ADS_RadarWarnSection9Distance;
    uint8_t ADS_RadarWarnSection10Distance;
    uint8_t ADS_RadarWarnSection11Distance;
    uint8_t ADS_RadarWarnSection12Distance;
    uint8_t ADS_RadarWarnSection13Distance;
    uint8_t ADS_RadarWarnSection14Distance;
    uint8_t ADS_RadarWarnSection15Distance;
}p_ADS_RadarWarningSt_2AF_st = {0x02, 0xAF, 9};

struct package_0x2B2_st_ADS_RadarWarningSt_2B2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_RadarWarnSection0AcoLevel;
    uint8_t ADS_RadarWarnSection1AcoLevel;
    uint8_t ADS_RadarWarnSection2AcoLevel;
    uint8_t ADS_RadarWarnSection3AcoLevel;
    uint8_t ADS_RadarWarnSection4AcoLevel;
    uint8_t ADS_RadarWarnSection5AcoLevel;
    uint8_t ADS_RadarWarnSection6AcoLevel;
    uint8_t ADS_RadarWarnSection7AcoLevel;
    uint8_t ADS_RadarWarnSection8AcoLevel;
    uint8_t ADS_RadarWarnSection9AcoLevel;
    uint8_t ADS_RadarWarnSection10AcoLevel;
    uint8_t ADS_RadarWarnSection11AcoLevel;
    uint8_t ADS_RadarWarnSection12AcoLevel;
    uint8_t ADS_RadarWarnSection13AcoLevel;
    uint8_t ADS_RadarWarnSection14AcoLevel;
    uint8_t ADS_RadarWarnSection15AcoLevel;
}p_ADS_RadarWarningSt_2B2_st = {0x02, 0xB2, 17};

struct package_0x2B3_st_ADS_FunctionSt_2B3
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_AccFunctionStatus;
    uint8_t ADS_NicaFunctionStatus;
    uint8_t ADS_ACCfault;
    uint8_t ADS_ICAfault;
    uint8_t ADS_NCAfault;
    uint8_t ADS_AVPfault;
    uint8_t ADS_APARPAfault;
    uint8_t ADS_FucntionNotActive;
    uint8_t ADS_AvpFunctionStatus;
    uint8_t ADS_SpeedSetByDriver_H;
    uint8_t ADS_SpeedSetByDriver_L;
    uint8_t ADS_SpeedLimitValue;
    uint8_t ADS_SpeedAutoFollow;
    uint8_t ADS_OneTouchSpeedAdjustment;
    uint8_t ADS_TimeGapAdjustment;
    uint8_t ADS_HMAFunctionStatus;
    uint8_t ADS_DriverSetSpeedDisplay;
}p_ADS_FunctionSt_2B3_st = {0x02, 0xB3, 18};

struct package_0x2B5_st_ADS_FunctionSt_2B5
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_CalibProcess;
    uint8_t ADS_CalibState;
    uint8_t ADS_CalibType;
    uint8_t ADS_TL1State;
    uint8_t ADS_TL1Countdown;
    uint8_t ADS_TL1Color;
    uint8_t ADS_TL1Blink;
    uint8_t ADS_TL2State;
    uint8_t ADS_TL2Countdown;
    uint8_t ADS_TL2Color;
    uint8_t ADS_TL2Blink;
    uint8_t ADS_HODReminder;
    uint8_t ADS_DMSReminder;
    uint8_t ADS_SpeedLimitConfidenceType;
    uint8_t ADS_SpeedDriverConfirm;
}p_ADS_FunctionSt_2B5_st = {0x02, 0xB5, 16};

struct package_0x2B6_st_ADS_FunctionSt_2B6
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_FcwWaning;
    uint8_t ADS_FCWfault;
    uint8_t ADS_AebWaning;
    uint8_t ADS_AEBfault;
    uint8_t ADS_AebObjType;
    uint8_t ADS_RaebWarning;
    uint8_t ADS_RAEBfault;
    uint8_t ADS_RcwWarning;
    uint8_t ADS_RCWfault;
    uint8_t ADS_FctaLeftWarning;
    uint8_t ADS_FctaRightWarning;
    uint8_t ADS_FctbLeftWarning;
    uint8_t ADS_FctbRightWarning;
    uint8_t ADS_RctaLeftWarning;
    uint8_t ADS_RctaRightWarning;
    uint8_t ADS_RctbLeftWarning;
    uint8_t ADS_RctbRightWarning;
    uint8_t ADS_LdwWarning;
    uint8_t ADS_LDWfault;
    uint8_t ADS_LKAWarning;
    uint8_t ADS_LKAfault;
    uint8_t ADS_RCTAfault;
}p_ADS_FunctionSt_2B6_st = {0x02, 0xB6, 23};

struct package_0x2B7_st_ADS_FunctionSt_2B7
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_LeftMirrWarningCmd;
    uint8_t ADS_RightMirrWarningCmd;
    uint8_t ADS_BSDfault;
    uint8_t ADS_LeFrntDoorWarningCmd;
    uint8_t ADS_LeReDoorWarningCmd;
    uint8_t ADS_RiFrntDoorWarningCmd;
    uint8_t ADS_RiReDoorWarningCmd;
    uint8_t ADS_DOWfault;
    uint8_t ADS_SpeedLimitWarning;
    uint8_t ADS_SetAbsltSpdLim_H;
    uint8_t ADS_SetAbsltSpdLim_L;
    uint8_t ADS_TLAWarning;
    uint8_t ADS_TLAfault;
    uint8_t ADS_TSRfault;
    uint8_t ADS_ELKAWarning;
    uint8_t ADS_ELKAfault;
}p_ADS_FunctionSt_2B7_st = {0x02, 0xB7, 17};

struct package_0x2C6_st_ADS_HMI_2C6
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_LineType_Left;
    uint8_t ADS_LineType_Right;
    uint8_t ADS_LaneChangeConfirm;
    uint8_t ADS_LateralAction;
    uint8_t ADS_EthSignalState;
    uint8_t ADS_EthPdcSignalState;
}p_ADS_HMI_2C6_st = {0x02, 0xC6, 7};

struct package_0x30A_st_ADS_DisState_30A
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_RAEBSts;
    uint8_t ADS_SLAWarnMode;
}p_ADS_DisState_30A_st = {0x03, 0x0A, 3};

struct package_0x30D_st_ADS_APAState_30D
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_RPAFuncSts;
    uint8_t ADS_AVMRotationAngle_X_H;
    uint8_t ADS_AVMRotationAngle_X_L;
    uint8_t ADS_AVMRotationAngle_Y;
    uint8_t ADS_APADrvSpeedSts;
    uint8_t ADS_AVMCarBodyTranspSts;
    uint8_t ADS_AVMtrigBySensorSts;
    uint8_t ADS_AVMtrigByTurnSts;
    uint8_t AVM_TrajectoryDisplaySts;
    uint8_t ADS_APALaebSWSts;
    uint8_t ADS_APALaebSts;
}p_ADS_APAState_30D_st = {0x03, 0x0D, 12};

struct package_0x30E_st_ADS_ACCState_30E
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_ICAOnOffSt;
    uint8_t ADS_lanechangestaly;
    uint8_t ADS_autolanechangeSet;
    uint8_t ADS_RampfollowcarSt;
    uint8_t ADS_NCAOnOffSt;
    uint8_t ADS_SpeedlimitSt;
    uint8_t ADS_voicebroadcastSt;
    uint8_t ADS_UpgradingAnddowngradeSt;
    uint8_t ADS_HMAonoffSt;
    uint8_t ADS_SpeedProportionSt;
    uint8_t ADS_SpeedValueSt;
    uint8_t ADS_ParkPosn1_ID_H;
    uint8_t ADS_ParkPosn1_ID_L;
    uint8_t ADS_ICAStatus;
    uint8_t ADS_NCAState;
    uint8_t ADS_LaneChangingStatus;
    uint8_t ADS_LaneChangeConfirmType;
}p_ADS_ACCState_30E_st = {0x03, 0x0E, 18};

struct package_0x308_st_ADS_FunctionSt_308
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_AEBSts;
    uint8_t ADS_FCTALeftSts;
    uint8_t ADS_FCTARightSts;
    uint8_t ADS_FCTBLeftSts;
    uint8_t ADS_FCTBRightSts;
    uint8_t ADS_RCTALeftSts;
    uint8_t ADS_RCTARightSts;
    uint8_t ADS_RCTBLeftSts;
    uint8_t ADS_RCTBRightSts;
    uint8_t ADS_ELKSts;
    uint8_t LDW_State;
    uint8_t RDP_State;
    uint8_t ADS_BSDLeftSts;
    uint8_t ADS_BSDRightSts;
    uint8_t ADS_ICAStatus;
    uint8_t ADS_NCAState;
    uint8_t ADS_DOWLeftSts;
    uint8_t ADS_DOWRightSts;
}p_ADS_FunctionSt_308_st = {0x03, 0x08, 19};

struct package_0x307_st_ADS_FunctionSt_307
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_APAViewSts;
    uint8_t ADS_AVMViewSts;
    uint8_t ADS_APAFuncType;
    uint8_t ADS_APAParkInTypeSel;
    uint8_t ADS_APACustomizeSlotFB;
    uint8_t ADS_RpaApaSwitchFB;
    uint8_t ADS_APAUIFuncSts;
    uint8_t ADS_ParkSpcGrdLockSts;
    uint8_t ADS_AVMSideViewSts;
    uint8_t ADS_ParkFRmngDst_H;
    uint8_t ADS_ParkFRmngDst_L;
    uint8_t ADS_ParkRRmngDst_H;
    uint8_t ADS_ParkRRmngDst_L;
    uint8_t ADS_FrontPDCAlarmSts;
    uint8_t ADS_PDCMuteSts;
    uint8_t ADS_APACustomizedSlotSt;
    uint8_t ADS_VehParkModeAvil;
}p_ADS_FunctionSt_307_st = {0x03, 0x07, 18};

struct package_0x31B_st_ADS_FunctionSt_31B
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_APAToastID_H;
    uint8_t ADS_APAToastID_L;
    uint8_t ADS_APATipsID_H;
    uint8_t ADS_APATipsID_L;
    uint8_t ADS_APAToastTTS;
    uint8_t ADS_APAToastLevel;
}p_ADS_FunctionSt_31B_st = {0x03, 0x1B, 7};

struct package_0x321_st_ADS_FunctionSt_321
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ADS_LanechangStyle;
    uint8_t ADS_TargetSpeedOffsetType;
    uint8_t ADS_TargetSpeedOffsetValue;
    uint8_t ADS_NCAFuncSts;
    uint8_t ADS_ICAFuncSts;
    uint8_t ADS_ALCFuncSts;
    uint8_t ADS_SLAFuncSts;
    uint8_t ADS_SLAsetAdjustSts;
    uint8_t ADS_ValueAdjustSts;
    uint8_t ADS_TrafficLightRemFuncSts;
    uint8_t ADS_LaneAssitType;
    uint8_t ADS_LasWarnMode;
    uint8_t ADS_ELKFuncSts;
    uint8_t ADS_FcwFuncSts;
    uint8_t ADS_AEBFuncSts;
    uint8_t ADS_LaebFuncSts;
    uint8_t ADS_RCWFuncSts;
    uint8_t ADS_BsdLcaFuncSts;
    uint8_t ADS_DowFuncSts;
    uint8_t ADS_StartRemFuncSts;
    uint8_t ADS_AdsVoiceBroadcastTypeSts;
    uint8_t ADS_HmaFuncSts;
    uint8_t ADS_AccStatus;
}p_ADS_FunctionSt_321_st = {0x03, 0x21, 24};

struct package_0x3B1_st_VCU_state2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t VCU_CLTCEvRemainingMileage_H;
    uint8_t VCU_CLTCEvRemainingMileage_L;
}p_VCU_state2_st = {0x03, 0xB1, 3};

struct package_0x413_st_TBOX_413
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t TBOX_FuncReq_SentryMod;
}p_TBOX_413_st = {0x04, 0x13, 2};

struct package_0x347_st_BLE_FB
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t BLE_approachingUnlockFedb;
    uint8_t BLE_awayLockFeedback;
    uint8_t BLE_RPAmodeReq;
}p_BLE_FB_st = {0x03, 0x47, 4};

struct package_0x375_st_BLE_User_ID
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t BLE_User_ID_8;
    uint8_t BLE_User_ID_7;
    uint8_t BLE_User_ID_6;
    uint8_t BLE_User_ID_5;
    uint8_t BLE_User_ID_4;
    uint8_t BLE_User_ID_3;
    uint8_t BLE_User_ID_2;
    uint8_t BLE_User_ID_1;
}p_BLE_User_ID_st = {0x03, 0x75, 9};

struct package_0x360_st_TBOX_Factory_360
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t TBOX_ConditionalCheck;
    uint8_t TBOX_FactoryResetResult;
    uint8_t TBOX_FactoryResetTime_H;
    uint8_t TBOX_FactoryResetTime_L;
}p_TBOX_Factory_360_st = {0x03, 0x60, 5};

struct package_0x3B6_st_AC_ctrlFeedback
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ac_systemOnOffSts;
    uint8_t ac_autoStatus;
    uint8_t ac_acStatus;
    uint8_t ac_driverTempC;
    uint8_t ac_dualStatus;
    uint8_t ac_frontDefrostStatus1;
    uint8_t ac_recircStatus;
    uint8_t ac_passengerTempC;
    uint8_t ac_blowerLvAUTOStatus;
    uint8_t AC_EnergySavingSts;
    uint8_t ac_modeAUTOStatus;
    uint8_t ac_modeStatus;
    uint8_t ac_blowerLvStatus;
    uint8_t AC_InigentizePurificationStSwitch;
    uint8_t AC_InigentizePurificationSt;
    uint8_t AC_InsidePM25Level;
    uint8_t AC_PM25InCar_H;
    uint8_t AC_PM25InCar_L;
    uint8_t AC_PurificationQuikReq;
    uint8_t AC_AutoDrySts;
}p_AC_ctrlFeedback_st = {0x03, 0xB6, 21};

struct package_0x386_st_AC_state2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ac_FrontDefrostLevelStatus;
}p_AC_state2_st = {0x03, 0x86, 2};

struct package_0x2A1_st_BCM_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bcm_cruiseSW;
    uint8_t bcm_cruiseSWValid;
    uint8_t BCM_cruiseHeadway_increase_KeySts;
    uint8_t BCM_cruiseHeadway_increase_KeyStsValid;
    uint8_t bcm_hoodSts;
    uint8_t bcm_hazardLightSwSts;
    uint8_t bcm_leftTurnLampSwSts;
    uint8_t bcm_leftTurnLampSts;
    uint8_t bcm_rightTurnLampSts;
    uint8_t bcm_rightTurnLampSwSts;
    uint8_t bcm_doorFLSts;
    uint8_t bcm_doorFRSts;
    uint8_t bcm_doorRLSts;
    uint8_t bcm_doorRRSts;
    uint8_t bcm_doorFLLockSts;
    uint8_t bcm_antiTheftSts;
    uint8_t bcm_FuelTapStatus;
    uint8_t bcm_frontWiperSts;
    uint8_t bcm_chrgCapSts;
    uint8_t BCM_cruiseHeadway_decrease_KeySts;
    uint8_t BCM_cruiseHeadway_decrease_KeyStsValid;
    uint8_t bcm_driverSeatDetectSts;
}p_BCM_state_st = {0x02, 0xA1, 23};

struct package_0x3C1_st_BCM_state2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bcm_rearMirrorSts;
    uint8_t BCM_HighBeamModel;
    uint8_t bcm_windowLFSts;
    uint8_t bcm_windowRFSts;
    uint8_t bcm_windowLRSts;
    uint8_t bcm_windowRRSts;
    uint8_t bcm_rearDefrostSts;
    uint8_t BCM_AutoRainWiperstatus;
    uint8_t bcm_rainSensorError;
    uint8_t bcm_positionLampSts;
    uint8_t bcm_autoLampSwSts;
    uint8_t bcm_rsmSolarRight;
    uint8_t bcm_rsmSolarLeft;
    uint8_t bcm_lowBeamSts;
    uint8_t bcm_highBeamSts;
    uint8_t bcm_rearFogLampSts;
    uint8_t bcm_lightSensorError;
    uint8_t bcm_roofLampSts;
}p_BCM_state2_st = {0x03, 0xC1, 19};

struct package_0x3C2_st_BCM_state3
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t BCM_NozzleHeatingSt;
    uint8_t BCM_VolOrSOCLowAlarm;
    uint8_t BCM_ModeFB;
    uint8_t BCM_FLWINOpenDegree;
    uint8_t BCM_FRWINOpenDegree;
    uint8_t BCM_PresentONState;
    uint8_t BCM_VSPReq;
    uint8_t BCM_lockSoundSetfedb;
    uint8_t BCM_brakeLightSts;
    uint8_t BCM_RLWINOpenDegree;
    uint8_t BCM_RRWINOpenDegree;
    uint8_t BCM_NFC_PS_KeyReq;
    uint8_t BCM_PowerState;
}p_BCM_state3_st = {0x03, 0xC2, 14};

struct package_0x305_st_BCM_state4
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bcm_footLightSwitchSts;
    uint8_t BCM_HighBeamModel;
}p_BCM_state4_st = {0x03, 0x05, 3};

struct package_0x411_st_BCM_tpms
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bcm_tpmsLFStatus;
    uint8_t bcm_tyreLFPressure;
    uint8_t bcm_tyreLFTemp;
    uint8_t bcm_tpmsRFStatus;
    uint8_t bcm_tyreRFPressure;
    uint8_t bcm_tyreRFTemp;
    uint8_t BCM_wipperMaintModeSts;
}p_BCM_tpms_st = {0x04, 0x11, 8};

struct package_0x421_st_BCM_tpms1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bcm_tpmsLRStatus;
    uint8_t bcm_tyreLRPressure;
    uint8_t bcm_tyreLRTemp;
    uint8_t bcm_tpmsRRStatus;
    uint8_t bcm_tyreRRPressure;
    uint8_t bcm_tyreRRTemp;
}p_BCM_tpms1_st = {0x04, 0x21, 7};

struct package_0x2C1_st_BCM_peps
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bcm_pepsPowerMode;
    uint8_t bcm_ChildSafetyLockRRSts;
    uint8_t bcm_pepsKeyNotInCarInd;
    uint8_t bcm_pepsKeySerchFailInd;
    uint8_t bcm_pepsKeyCloserInd;
    uint8_t bcm_pepsFobLowBatWarning;
    uint8_t bcm_pepsPowerRelayErrWarning;
    uint8_t bcm_ChildSafetyLockSts;
    uint8_t bcm_esclUnlockFailWarning;
    uint8_t bcm_esclLockFailWarning;
    uint8_t bcm_remoteMode;
    uint8_t bcm_DriveDoorUnlockFedb;
    uint8_t bcm_doorFLUnlockSts;
    uint8_t bcm_12VBatterySOC;
    uint8_t bcm_pepsKeyInCarInd;
    uint8_t bcm_lowBeamFailureInd;
    uint8_t bcm_frontLeftTurnLightFailInd;
    uint8_t bcm_frontRightTurnLightFailInd;
    uint8_t bcm_rearFixLeftTurnLightFailInd;
    uint8_t bcm_rearMoveLeftTurnLightFailInd;
    uint8_t bcm_rearFixRightTurnLightFailInd;
    uint8_t bcm_rearMoRightTurnLightFailInd;
    uint8_t bcm_ChildSafetyLockRLSts;
    uint8_t bcm_doorTopSwitchSts;
    uint8_t bcm_approachingUnlockFedb;
    uint8_t bcm_followMeHomeFedb;
    uint8_t bcm_awayLockFeedback;
    uint8_t bcm_MirrorAutoFoldUnfoldStatus;
}p_BCM_peps_st = {0x02, 0xC1, 29};

struct package_0x3D1_st_BCM_rsm
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t BCM_apm_PassengeLockStatus;
    uint8_t BCM_positionLightOnReq;
    uint8_t BCM_LockCloseWinFedb;
}p_BCM_rsm_st = {0x03, 0xD1, 4};

struct package_0x5C3_st_BCM_RemotFB
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t BCM_LockFaultReason;
    uint8_t BCM_FRWINReason;
    uint8_t BCM_FLWINReason;
    uint8_t BCM_RLWINReason;
    uint8_t BCM_RRWINReason;
}p_BCM_RemotFB_st = {0x05, 0xC3, 6};

struct package_0x32A_st_LCU_32A
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t LCU_danceOnOffSet_FB;
    uint8_t LCU_unlockAnimatSet_FB;
    uint8_t LCU_lockAnimatSet_FB;
}p_LCU_32A_st = {0x03, 0x2A, 4};

struct package_0x394_st_PLG_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t PLG_antipinchWarning;
    uint8_t PLG_tailgateOpenFailWarning;
    uint8_t PLG_tailgateCloseFailWarning;
    uint8_t PLG_tailgateOpenSts;
    uint8_t PLG_antiPlayWarning;
    uint8_t PLG_tailgateOpenSts2;
    uint8_t PLG_OpenDegree;
    uint8_t PLG_tailgateFaultReason;
}p_PLG_state_st = {0x03, 0x94, 9};

struct package_0x335_st_GW_Handle_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t handle1_handlePosition;
    uint8_t handle2_handlePosition;
    uint8_t handle3_handlePosition;
    uint8_t handle4_handlePosition;
}p_GW_Handle_state_st = {0x03, 0x35, 5};

struct package_0x3D5_st_DSM_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t DSM_drSeatMassSts;
    uint8_t DSM_passSeatMassSts;
    uint8_t DSM_easyEntryStatus;
    uint8_t DSM_MirrorAutoTurnDownStatus;
    uint8_t DSM_DrMassgIntenSt;
    uint8_t DSM_PsgMassgIntenSt;
    uint8_t DSM_DSMStatustOutput;
    uint8_t DSM_MemoryPosition;
    uint8_t DSM_DevSupportSts;
    uint8_t DSM_DevLinkSts;
    uint8_t DSM_DevType;
    uint8_t DSM_ChargeSts;
}p_DSM_state_st = {0x03, 0xD5, 13};

struct package_0x3D6_st_PSM_memory
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t PSM_PassSeatRouteSetFB;
    uint8_t PSM_PassSeatbackrestSetFB;
    uint8_t PSM_PassSeatCushionSetFB;
    uint8_t PSM_PassSeatCushionAngleSetFB;
    uint8_t PSM_LimitbackrestAngle;
}p_PSM_memory_st = {0x03, 0xD6, 6};

struct package_0x3D4_st_DSM_memory
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t DSM_drSeatRouteSetFB;
    uint8_t DSM_drSeatbackrestSetFB;
    uint8_t DSM_drSeatCushionSetFB;
    uint8_t DSM_drSeatCushionAngleSetFB;
    uint8_t DSM_LmirrorUDSetFB;
    uint8_t DSM_LimitbackrestAngle;
    uint8_t DSM_LmirrorLRSetFB;
    uint8_t DSM_RmirrorUDSetFB;
    uint8_t DSM_RmirrorLRSetFB;
    uint8_t DSM_drSeatMovementSts;
}p_DSM_memory_st = {0x03, 0xD4, 11};

struct package_0x318_st_PSM_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t PSM_drSeatHeatSts;
    uint8_t PSM_drSeatVentSts;
    uint8_t PSM_passSeatHeatSts;
    uint8_t PSM_passSeatVentSts;
    uint8_t PSM_DevSupportSts;
    uint8_t PSM_DevLinkSts;
    uint8_t PSM_DevType;
    uint8_t PSM_ChargeSts;
}p_PSM_state_st = {0x03, 0x18, 9};

struct package_0x31A_st_LRSM_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t LRSM_LSeatHeatSts;
    uint8_t LRSM_RSeatHeatSts;
}p_LRSM_state_st = {0x03, 0x1A, 3};

struct package_0x0A8_st_TBOX_infoCtrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t tbox_remotePetModeReq;
    uint8_t TBOX_SentryReq;
    uint8_t TBOX_TakeVideoPosReq;
    uint8_t TBOX_TakePhotoReq;
    uint8_t TBOX_SentryTimeSet;
    uint8_t TBOX_CarSearchReq;
    uint8_t TBOX_WaccMODERequest;
    uint8_t TBOX_WaccTempSet;
    uint8_t TBOX_WaccEaultEliminate;
}p_TBOX_infoCtrl_st = {0x00, 0xA8, 10};

struct package_0x3A0_st_VSP_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vsp_errorStatus;
    uint8_t vsp_soundEnable;
    uint8_t vsp_errorIdentification;
    uint8_t vsp_SoundOnOffSts;
    uint8_t vsp_SoundConfigure;
    uint8_t VSP_unlocksoundSetFb;
    uint8_t VSP_lockSoundSetFb;
}p_VSP_state_st = {0x03, 0xA0, 8};

struct package_0x3C6_st_GW_vent1Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent1ErrorStatus;
    uint8_t gw_ElVent1OverHeatStatus;
    uint8_t gw_ElVent1ElectricalFailureSts;
    uint8_t gw_ElVent1VoltageStatus;
    uint8_t gw_ElVent1EmergencyRunningSts;
    uint8_t gw_ElVent1ObstructionDetect;
    uint8_t gw_ElVent1ObstructionStatus;
    uint8_t gw_ElVent1ResetStatus;
    uint8_t gw_ElVent1CoilStatus;
    uint8_t gw_ElVent1LocationStatus;
    uint8_t gw_ElVent1SpeedStatus;
    uint8_t gw_ElVent1MotorCurrentLocation_H;
    uint8_t gw_ElVent1MotorCurrentLocation_L;
    uint8_t gw_ElVent1MotorDrivingDirection;
    uint8_t gw_ElVent1TorqueKeepingSts;
    uint8_t gw_ElVent1SpecialFunction;
    uint8_t gw_ElVent1LocationActuator;
    uint8_t gw_ElVent1EmgyStopSwitchSts;
    uint8_t gw_ElVent1EmgyStopSLocation;
    uint8_t gw_ElVent1RotationMode;
    uint8_t gw_ElVent1StopStatus;
}p_GW_vent1Sts_st = {0x03, 0xC6, 22};

struct package_0x3C7_st_GW_vent2Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent2ErrorStatus;
    uint8_t gw_ElVent2OverHeatStatus;
    uint8_t gw_ElVent2ElectricalFailureSts;
    uint8_t gw_ElVent2VoltageStatus;
    uint8_t gw_ElVent2EmergencyRunningSts;
    uint8_t gw_ElVent2ObstructionDetect;
    uint8_t gw_ElVent2ObstructionStatus;
    uint8_t gw_ElVent2ResetStatus;
    uint8_t gw_ElVent2CoilStatus;
    uint8_t gw_ElVent2LocationStatus;
    uint8_t gw_ElVent2SpeedStatus;
    uint8_t gw_ElVent2MotorCurrentLocation_H;
    uint8_t gw_ElVent2MotorCurrentLocation_L;
    uint8_t gw_ElVent2MotorDrivingDirection;
    uint8_t gw_ElVent2TorqueKeepingSts;
    uint8_t gw_ElVent2SpecialFunction;
    uint8_t gw_ElVent2LocationActuator;
    uint8_t gw_ElVent2EmgyStopSwitchSts;
    uint8_t gw_ElVent2EmgyStopSLocation;
    uint8_t gw_ElVent2RotationMode;
    uint8_t gw_ElVent2StopStatus;
}p_GW_vent2Sts_st = {0x03, 0xC7, 22};

struct package_0x3C8_st_GW_vent3Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent3ErrorStatus;
    uint8_t gw_ElVent3OverHeatStatus;
    uint8_t gw_ElVent3ElectricalFailureSts;
    uint8_t gw_ElVent3VoltageStatus;
    uint8_t gw_ElVent3EmergencyRunningSts;
    uint8_t gw_ElVent3ObstructionDetect;
    uint8_t gw_ElVent3ObstructionStatus;
    uint8_t gw_ElVent3ResetStatus;
    uint8_t gw_ElVent3CoilStatus;
    uint8_t gw_ElVent3LocationStatus;
    uint8_t gw_ElVent3SpeedStatus;
    uint8_t gw_ElVent3MotorCurrentLocation_H;
    uint8_t gw_ElVent3MotorCurrentLocation_L;
    uint8_t gw_ElVent3MotorDrivingDirection;
    uint8_t gw_ElVent3TorqueKeepingSts;
    uint8_t gw_ElVent3SpecialFunction;
    uint8_t gw_ElVent3LocationActuator;
    uint8_t gw_ElVent3EmgyStopSwitchSts;
    uint8_t gw_ElVent3EmgyStopSLocation;
    uint8_t gw_ElVent3RotationMode;
    uint8_t gw_ElVent3StopStatus;
}p_GW_vent3Sts_st = {0x03, 0xC8, 22};

struct package_0x3C9_st_GW_vent4Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent4ErrorStatus;
    uint8_t gw_ElVent4OverHeatStatus;
    uint8_t gw_ElVent4ElectricalFailureSts;
    uint8_t gw_ElVent4VoltageStatus;
    uint8_t gw_ElVent4EmergencyRunningSts;
    uint8_t gw_ElVent4ObstructionDetect;
    uint8_t gw_ElVent4ObstructionStatus;
    uint8_t gw_ElVent4ResetStatus;
    uint8_t gw_ElVent4CoilStatus;
    uint8_t gw_ElVent4LocationStatus;
    uint8_t gw_ElVent4SpeedStatus;
    uint8_t gw_ElVent4MotorCurrentLocation_H;
    uint8_t gw_ElVent4MotorCurrentLocation_L;
    uint8_t gw_ElVent4MotorDrivingDirection;
    uint8_t gw_ElVent4TorqueKeepingSts;
    uint8_t gw_ElVent4SpecialFunction;
    uint8_t gw_ElVent4LocationActuator;
    uint8_t gw_ElVent4EmgyStopSwitchSts;
    uint8_t gw_ElVent4EmgyStopSLocation;
    uint8_t gw_ElVent4RotationMode;
    uint8_t gw_ElVent4StopStatus;
}p_GW_vent4Sts_st = {0x03, 0xC9, 22};

struct package_0x3CA_st_GW_vent5Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent5ErrorStatus;
    uint8_t gw_ElVent5OverHeatStatus;
    uint8_t gw_ElVent5ElectricalFailureSts;
    uint8_t gw_ElVent5VoltageStatus;
    uint8_t gw_ElVent5EmergencyRunningSts;
    uint8_t gw_ElVent5ObstructionDetect;
    uint8_t gw_ElVent5ObstructionStatus;
    uint8_t gw_ElVent5ResetStatus;
    uint8_t gw_ElVent5CoilStatus;
    uint8_t gw_ElVent5LocationStatus;
    uint8_t gw_ElVent5SpeedStatus;
    uint8_t gw_ElVent5MotorCurrentLocation_H;
    uint8_t gw_ElVent5MotorCurrentLocation_L;
    uint8_t gw_ElVent5MotorDrivingDirection;
    uint8_t gw_ElVent5TorqueKeepingSts;
    uint8_t gw_ElVent5SpecialFunction;
    uint8_t gw_ElVent5LocationActuator;
    uint8_t gw_ElVent5EmgyStopSwitchSts;
    uint8_t gw_ElVent5EmgyStopSLocation;
    uint8_t gw_ElVent5RotationMode;
    uint8_t gw_ElVent5StopStatus;
}p_GW_vent5Sts_st = {0x03, 0xCA, 22};

struct package_0x3CB_st_GW_vent6Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent6ErrorStatus;
    uint8_t gw_ElVent6OverHeatStatus;
    uint8_t gw_ElVent6ElectricalFailureSts;
    uint8_t gw_ElVent6VoltageStatus;
    uint8_t gw_ElVent6EmergencyRunningSts;
    uint8_t gw_ElVent6ObstructionDetect;
    uint8_t gw_ElVent6ObstructionStatus;
    uint8_t gw_ElVent6ResetStatus;
    uint8_t gw_ElVent6CoilStatus;
    uint8_t gw_ElVent6LocationStatus;
    uint8_t gw_ElVent6SpeedStatus;
    uint8_t gw_ElVent6MotorCurrentLocation_H;
    uint8_t gw_ElVent6MotorCurrentLocation_L;
    uint8_t gw_ElVent6MotorDrivingDirection;
    uint8_t gw_ElVent6TorqueKeepingSts;
    uint8_t gw_ElVent6SpecialFunction;
    uint8_t gw_ElVent6LocationActuator;
    uint8_t gw_ElVent6EmgyStopSwitchSts;
    uint8_t gw_ElVent6EmgyStopSLocation;
    uint8_t gw_ElVent6RotationMode;
    uint8_t gw_ElVent6StopStatus;
}p_GW_vent6Sts_st = {0x03, 0xCB, 22};

struct package_0x3CC_st_GW_vent7Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent7ErrorStatus;
    uint8_t gw_ElVent7OverHeatStatus;
    uint8_t gw_ElVent7ElectricalFailureSts;
    uint8_t gw_ElVent7VoltageStatus;
    uint8_t gw_ElVent7EmergencyRunningSts;
    uint8_t gw_ElVent7ObstructionDetect;
    uint8_t gw_ElVent7ObstructionStatus;
    uint8_t gw_ElVent7ResetStatus;
    uint8_t gw_ElVent7CoilStatus;
    uint8_t gw_ElVent7LocationStatus;
    uint8_t gw_ElVent7SpeedStatus;
    uint8_t gw_ElVent7MotorCurrentLocation_H;
    uint8_t gw_ElVent7MotorCurrentLocation_L;
    uint8_t gw_ElVent7MotorDrivingDirection;
    uint8_t gw_ElVent7TorqueKeepingSts;
    uint8_t gw_ElVent7SpecialFunction;
    uint8_t gw_ElVent7LocationActuator;
    uint8_t gw_ElVent7EmgyStopSwitchSts;
    uint8_t gw_ElVent7EmgyStopSLocation;
    uint8_t gw_ElVent7RotationMode;
    uint8_t gw_ElVent7StopStatus;
}p_GW_vent7Sts_st = {0x03, 0xCC, 22};

struct package_0x3CD_st_GW_vent8Sts
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gw_ElVent8ErrorStatus;
    uint8_t gw_ElVent8OverHeatStatus;
    uint8_t gw_ElVent8ElectricalFailureSts;
    uint8_t gw_ElVent8VoltageStatus;
    uint8_t gw_ElVent8EmergencyRunningSts;
    uint8_t gw_ElVent8ObstructionDetect;
    uint8_t gw_ElVent8ObstructionStatus;
    uint8_t gw_ElVent8ResetStatus;
    uint8_t gw_ElVent8CoilStatus;
    uint8_t gw_ElVent8LocationStatus;
    uint8_t gw_ElVent8SpeedStatus;
    uint8_t gw_ElVent8MotorCurrentLocation_H;
    uint8_t gw_ElVent8MotorCurrentLocation_L;
    uint8_t gw_ElVent8MotorDrivingDirection;
    uint8_t gw_ElVent8TorqueKeepingSts;
    uint8_t gw_ElVent8SpecialFunction;
    uint8_t gw_ElVent8LocationActuator;
    uint8_t gw_ElVent8EmgyStopSwitchSts;
    uint8_t gw_ElVent8EmgyStopSLocation;
    uint8_t gw_ElVent8RotationMode;
    uint8_t gw_ElVent8StopStatus;
}p_GW_vent8Sts_st = {0x03, 0xCD, 22};

struct package_0x3DE_st_GW_BMS_meas
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bms_vPackBmu_H;
    uint8_t bms_vPackBmu_L;
    uint8_t bms_vPackBms_H;
    uint8_t bms_vPackBms_L;
    uint8_t bms_iPack_H;
    uint8_t bms_iPack_L;
}p_GW_BMS_meas_st = {0x03, 0xDE, 7};

struct package_0x31E_st_BMS_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t bms_state;
    uint8_t bms_dcChargeState;
    uint8_t bms_acChargeState;
    uint8_t BMS_HVInterlock_Status;
    uint8_t bms_isolationState;
    uint8_t bms_contactorState;
    uint8_t bms_acChargeConnection;
    uint8_t bms_dcChargeConnection;
    uint8_t bms_authenticationResult;
    uint8_t bms_alertLevel;
    uint8_t bms_pPack_H;
    uint8_t bms_pPack_L;
}p_BMS_state_st = {0x03, 0x1E, 13};

struct package_0x3AE_st_GTW_mcur0_info
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mcur0_speed_H;
    uint8_t mcur0_speed_MH;
    uint8_t mcur0_speed_ML;
    uint8_t mcur0_speed_L;
    uint8_t mcur0_iBus_H;
    uint8_t mcur0_iBus_L;
    uint8_t mcur0_vBus_H;
    uint8_t mcur0_vBus_L;
    uint8_t mcur0_stEgyFlowAndBatt;
    uint8_t mcur0_Fault_Light_Ctrl;
    uint8_t mcur0_faultLevel;
}p_GTW_mcur0_info_st = {0x03, 0xAE, 12};

struct package_0x3BE_st_GTW_mcuf0_info
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t mcuf0_speed_H;
    uint8_t mcuf0_speed_MH;
    uint8_t mcuf0_speed_ML;
    uint8_t mcuf0_speed_L;
    uint8_t mcuf0_iBus_H;
    uint8_t mcuf0_iBus_L;
    uint8_t mcuf0_vBus_H;
    uint8_t mcuf0_vBus_L;
    uint8_t mcuf0_stEgyFlowAndBatt;
    uint8_t mcuf0_Fault_Light_Ctrl;
    uint8_t mcuf0_faultLevel;
}p_GTW_mcuf0_info_st = {0x03, 0xBE, 12};

struct package_0x37E_st_GTW_ecu_gcu_vcu_info
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t gcu_torqueEst_H;
    uint8_t gcu_torqueEst_L;
    uint8_t ecu_engSpeed_H;
    uint8_t ecu_engSpeed_L;
    uint8_t ecu_engCoolantTemp;
    uint8_t ecu_fuelComsump100ms_H;
    uint8_t ecu_fuelComsump100ms_L;
    uint8_t ecu_milIndicator;
    uint8_t vcu_coolantLevelLow;
    uint8_t vcu_brakeLight;
    uint8_t ecu_state;
    uint8_t vcu_highVoltFail;
    uint8_t vcu_Regenmode;
}p_GTW_ecu_gcu_vcu_info_st = {0x03, 0x7E, 14};

struct package_0x223_st_GTW_esc_eps_iB_info
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t esc_vehicleSpeed_H;
    uint8_t esc_vehicleSpeed_L;
    uint8_t esc_vehicleSpeedValid;
    uint8_t esc_absFault;
    uint8_t esc_avhActive;
    uint8_t esc_avhStandby;
    uint8_t esc_avhAvailable;
    uint8_t esc_hdcStatus;
    uint8_t esc_ebdFault;
    uint8_t esc_offStatus;
    uint8_t esc_escFault;
    uint8_t esc_vlcTorqReq_H;
    uint8_t esc_vlcTorqReq_L;
    uint8_t esc_vlcTorqReqActive;
    uint8_t esc_vlcError;
    uint8_t esc_vlcAvalible;
    uint8_t esc_vlcInterTargetAx;
    uint8_t esc_vlcActive;
    uint8_t eps_modeStatus;
    uint8_t esc_escActive;
    uint8_t esc_hdcAvailable;
    uint8_t iB_hmiWarningOn;
    uint8_t iB_hmiWarningOn_Q;
    uint8_t esc_hhcAvailable;
}p_GTW_esc_eps_iB_info_st = {0x02, 0x23, 25};

struct package_0x353_st_GW_EPS_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t eps_torsionBarTorque_H;
    uint8_t eps_torsionBarTorque_L;
    uint8_t eps_torsionBarTorqueValid;
}p_GW_EPS_state_st = {0x03, 0x53, 4};

struct package_0x24E_st_VCU_stateCha2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t vcu_brakePedalSts;
    uint8_t vcu_brakePedalStsValid;
    uint8_t vcu_actualGearValid;
    uint8_t vcu_actualGear;
    uint8_t vcu_totalPowerConsumThisTrip_H;
    uint8_t vcu_totalPowerConsumThisTrip_L;
    uint8_t vcu_241_rollingCounter;
    uint8_t vcu_241_checksum;
}p_VCU_stateCha2_st = {0x02, 0x4E, 9};

struct package_0x3CE_st_AC_temp_pressure
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ac_ambientTemp;
    uint8_t ac_cabinTemp;
    uint8_t ac_ambientTempValid;
}p_AC_temp_pressure_st = {0x03, 0xCE, 4};

struct package_0x3B7_st_PDC_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t pdc_buzzerAlarmPattern;
    uint8_t pdc_modeStatus;
    uint8_t pdc_distanceFL;
    uint8_t pdc_sensorFaultFL;
    uint8_t pdc_distanceFML;
    uint8_t pdc_sensorFaultFML;
    uint8_t pdc_distanceFMR;
    uint8_t pdc_sensorFaultFMR;
    uint8_t pdc_distanceFR;
    uint8_t pdc_sensorFaultFR;
    uint8_t pdc_distanceRL;
    uint8_t pdc_sensorFaultRL;
    uint8_t pdc_distanceRML;
    uint8_t pdc_sensorFaultRML;
    uint8_t pdc_distanceRMR;
    uint8_t pdc_sensorFaultRMR;
    uint8_t pdc_distanceRR;
    uint8_t pdc_sensorFaultRR;
    uint8_t pdc_FrontRadarActiveStatus;
    uint8_t pdc_distanceFSL;
    uint8_t pdc_sensorFaultFSL;
    uint8_t pdc_distanceFSR;
    uint8_t pdc_sensorFaultFSR;
    uint8_t pdc_distanceRSL;
    uint8_t pdc_sensorFaultRSL;
    uint8_t pdc_distanceRSR;
    uint8_t pdc_sensorFaultRSR;
}p_PDC_state_st = {0x03, 0xB7, 28};

struct package_0x3B8_st_PDC_state1_3B8
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t pdc_actualdistanceFL__H;
    uint8_t pdc_actualdistanceFL__L;
    uint8_t pdc_actualdistanceFML__H;
    uint8_t pdc_actualdistanceFML__L;
    uint8_t pdc_actualdistanceFMR__H;
    uint8_t pdc_actualdistanceFMR__L;
    uint8_t pdc_actualdistanceFR__H;
    uint8_t pdc_actualdistanceFR__L;
    uint8_t pdc_actualdistanceFSL_H;
    uint8_t pdc_actualdistanceFSL_L;
    uint8_t pdc_actualdistanceFSR_H;
    uint8_t pdc_actualdistanceFSR_L;
}p_PDC_state1_3B8_st = {0x03, 0xB8, 13};

struct package_0x3B9_st_PDC_state1_3B9
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t pdc_actualdistanceRL__H;
    uint8_t pdc_actualdistanceRL__L;
    uint8_t pdc_actualdistanceRML__H;
    uint8_t pdc_actualdistanceRML__L;
    uint8_t pdc_actualdistanceRMR__H;
    uint8_t pdc_actualdistanceRMR__L;
    uint8_t pdc_actualdistanceRR__H;
    uint8_t pdc_actualdistanceRR__L;
    uint8_t pdc_actualdistanceRSL_H;
    uint8_t pdc_actualdistanceRSL_L;
    uint8_t pdc_actualdistanceRSR_H;
    uint8_t pdc_actualdistanceRSR_L;
}p_PDC_state1_3B9_st = {0x03, 0xB9, 13};

struct package_0x3AD_st_WCM_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t wcm_LeftchargingStatus;
    uint8_t wcm_failureStatus;
    uint8_t wcm_workingStatus;
    uint8_t wcm_selfCheckToIVI;
    uint8_t WCM_PhoneReminder;
    uint8_t wcm_onOffFeedback;
    uint8_t wcm_RightchargingStatus;
}p_WCM_state_st = {0x03, 0xAD, 8};

struct package_0x484_st_AVM_state_484
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t AVM_apa_sts;
    uint8_t AVM_SentryModeFB;
    uint8_t AVM_sysFailureSts;
    uint8_t AVM_singleViewSts;
    uint8_t AVM_apa_FrontCameraFailure;
    uint8_t AVM_apa_RearCameraFailure;
    uint8_t AVM_apa_LeftCameraFailure;
    uint8_t AVM_apa_RightCameraFailure;
    uint8_t APA_laeb_SW_Sts;
    uint8_t APA_laeb_Sts;
}p_AVM_state_484_st = {0x04, 0x84, 11};

struct package_0x3FA_st_HUD_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t hud_onOffSts;
}p_HUD_state_st = {0x03, 0xFA, 2};

struct package_0x0A9_st_MFW_Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t MFW_PRE_Key;
    uint8_t MFW_NEXT_Key;
    uint8_t MFW_VolumeUp_Key;
    uint8_t MFW_VolumeDown_Key;
    uint8_t MFW_PlayPause_Key;
    uint8_t MFW_Answer_Key;
    uint8_t MFW_HangUp_Key;
    uint8_t MFW_APA_AVM_Key;
    uint8_t MFW_PageUP_Key;
    uint8_t MFW_PageDown_Key;
    uint8_t MFW_Interface_Key;
    uint8_t MFW_VoiceButton_Key;
    uint8_t MFW_CustomButton1_Key;
    uint8_t MFW_ExhibitionMode;
    uint8_t MFW_TJAICAACTIVEKeySts;
    uint8_t MFW_TJAICAACTIVEKeyStsValid;
    uint8_t MFW_IVI_Reset;
}p_MFW_Ctrl_st = {0x00, 0xA9, 18};

struct package_0x498_st_MFW_KeySt
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t MFW_PRE_KeySt;
    uint8_t MFW_NEXT_KeySt;
    uint8_t MFW_PlayPause_KeySt;
    uint8_t MFW_Answer_KeySt;
    uint8_t MFW_HangUp_KeySt;
    uint8_t MFW_VoiceButton_KeySt;
    uint8_t MFW_CustomButton1_KeySt;
    uint8_t MFW_APA_AVM_KeySt;
    uint8_t MFW_TJAICAACTIVEKeySt;
}p_MFW_KeySt_st = {0x04, 0x98, 10};

struct package_0x21C_st_HOD_21C
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t HOD_Handoffmonitor;
    uint8_t HOD_HandoffmonitorValid;
}p_HOD_21C_st = {0x02, 0x1C, 3};

struct package_0x181_st_IC_info_181
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_displayFail;
    uint8_t ic_IllumiLevelSts;
}p_IC_info_181_st = {0x01, 0x81, 3};

struct package_0x4F5_st_TBOX_timeAndGPS
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t TBOX_TimeInfoSecond;
    uint8_t TBOX_TimeInfoMinute;
    uint8_t TBOX_TimeInfoHour;
    uint8_t TBOX_TimeInfoDay;
    uint8_t TBOX_TimeInfoMonth;
    uint8_t TBOX_TimeInfoYear;
    uint8_t TBOX_TimeValid;
    uint8_t TBOX_longitude_H;
    uint8_t TBOX_longitude_L;
    uint8_t TBOX_latitude_H;
    uint8_t TBOX_latitude_L;
}p_TBOX_timeAndGPS_st = {0x04, 0xF5, 12};

struct package_0x35E_st_GTW_BMS_Rev
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t obc_acVoltage_H;
    uint8_t obc_acVoltage_L;
    uint8_t obc_acCurrent_H;
    uint8_t obc_acCurrent_L;
    uint8_t CCU_CompressorState;
    uint8_t vcu_PTC_Request;
    uint8_t bms_v2vChrgConnection;
}p_GTW_BMS_Rev_st = {0x03, 0x5E, 8};

struct package_0x725_st_Diag_PhyReq_IVI
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t Diag_PhyReq_IVI_Data_8;
    uint8_t Diag_PhyReq_IVI_Data_7;
    uint8_t Diag_PhyReq_IVI_Data_6;
    uint8_t Diag_PhyReq_IVI_Data_5;
    uint8_t Diag_PhyReq_IVI_Data_4;
    uint8_t Diag_PhyReq_IVI_Data_3;
    uint8_t Diag_PhyReq_IVI_Data_2;
    uint8_t Diag_PhyReq_IVI_Data_1;
}p_Diag_PhyReq_IVI_st = {0x07, 0x25, 9};

struct package_0x515_st_GW_IF_OBD_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t GW_OBD_Diag;
    uint8_t GW_OBD_Serve;
}p_GW_IF_OBD_state_st = {0x05, 0x15, 3};

struct package_0x400_st_SWHC_400
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t SWHC_SterringWheelHeatSts;
    uint8_t SWHC_SterringWheelHeatFaultReason;
}p_SWHC_400_st = {0x04, 0x00, 3};



#endif