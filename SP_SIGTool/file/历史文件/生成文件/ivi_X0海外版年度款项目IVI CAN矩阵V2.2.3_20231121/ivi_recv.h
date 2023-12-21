/**
* Copyright (c) 2018-2023 ThunderSoft
* All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
* You may not use, copy, distribute, modify, transmit in any form this file
* except in compliance with ThunderSoft in writing by applicable law.
*
*/
/**
* @file    ivi_recv.h
* @brief   ivi recv function.
* @details detailed function description.
* @version 1.0
* @author  cuiliu
* @date    2023-04-26
*
* Edit History
* ----------------------------------------------------------------------------
* DATE                     NAME               DESCRIPTION
* 2023-04-26               cuiliu             Create it.
*
*/

#ifndef  _IVI_RECV_H_
#define  _IVI_RECV_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "RTE.h"
typedef unsigned char   BOOL;

struct package_0x4F3_st_IC_info
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_avgSpdTripB_H;
    uint8_t ic_avgSpdTripB_L;
    uint8_t ic_lastingtime_H;
    uint8_t ic_lastingtime_L;
    uint8_t ic_mileageSincethelastcharge_H;
    uint8_t ic_mileageSincethelastcharge_L;
    uint8_t ic_tripmeterThisMoment_H;
    uint8_t ic_tripmeterThisMoment_L;
}p_IC_info_st = {0x04, 0xF3, 9};

struct package_0x408_st_IVI_SLA_408
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_currentRoadType;
    uint8_t ivi_NAVIcameraspeedLimitvalueValid;
    uint8_t ivi_NAVIspeedLimitvalueValid;
    uint8_t ivi_NAVItype;
    uint8_t ivi_NAVIcameraspeedLimitvalue;
    uint8_t ivi_NAVIspeedLimitvalue;
    uint8_t ivi_NAVIStaus;
    uint8_t IVI_VehicleRepairModeReq;
    uint8_t IVI_VehicleRepairModeSts;
    uint8_t IVI_UserGearFb;
    uint8_t IVI_CarSearchSts;
    uint8_t IVI_CarSearchControl;
    uint8_t IVI_UserClass;
    uint8_t IVI_AutoRainWiperReq;
    uint8_t IVI_VehiclePosition;
    uint8_t IVI_AccountLoginStatus;
    uint8_t ivi_languageSet1;
}p_IVI_SLA_408_st = {0x04, 0x08, 18};

struct package_0x376_st_IVI_User_ID
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_User_ID_8;
    uint8_t IVI_User_ID_7;
    uint8_t IVI_User_ID_6;
    uint8_t IVI_User_ID_5;
    uint8_t IVI_User_ID_4;
    uint8_t IVI_User_ID_3;
    uint8_t IVI_User_ID_2;
    uint8_t IVI_User_ID_1;
}p_IVI_User_ID_st = {0x03, 0x76, 9};

struct package_0x096_st_IVI_096
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_danceOnOffSet;
    uint8_t IVI_unlockAnimatSet;
    uint8_t IVI_lockAnimatSet;
    uint8_t IVI_FLWINOpenDegreeRe;
    uint8_t IVI_FRWINOpenDegreeRe;
    uint8_t IVI_RLWINOpenDegreeRe;
    uint8_t IVI_RRWINOpenDegreeRe;
    uint8_t IVI_BCMlockSoundSet;
    uint8_t IVI_LockCloseWinSet;
}p_IVI_096_st = {0x00, 0x96, 10};

struct package_0x075_st_IVI_control
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_childLockCtrl;
    uint8_t ivi_centralLockCtrl;
    uint8_t ivi_fuelPortCapOpenCtrl;
    uint8_t ivi_lowBeamOnOffCtrl;
    uint8_t ivi_v2vChrgOnOffSet;
    uint8_t ivi_obcDschrgOnOffSet;
    uint8_t ivi_rearFogLampOnOffCtrl;
    uint8_t ivi_roofLampOnOffCtrl;
    uint8_t ivi_chrgPortCapOpenCtrl;
    uint8_t ivi_NormalHvOffRequest;
    uint8_t ivi_tailgateCtrl;
    uint8_t ivi_MirrorSw;
    uint8_t ivi_rearDefrostCtrl;
    uint8_t ivi_footLightSwitchCtrl;
    uint8_t ivi_MaxFuelConsumptionSW;
    uint8_t ivi_MaxFuelConsumptionModeSW;
    uint8_t ivi_v2vChrgOptCurntSet;
    uint8_t ivi_approachingUnlockCtrl;
    uint8_t ivi_awayLockCtrl;
    uint8_t ivi_wipperMaintModeCtrl;
    uint8_t ivi_modememory;
}p_IVI_control_st = {0x00, 0x75, 22};

struct package_0x095_st_IVI_comfortSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_NozzleHeatingSw;
    uint8_t ivi_ambientLightOnOffSet;
    uint8_t IVI_OneKeyModeSet;
    uint8_t ivi_ambientLightColorSet;
    uint8_t ivi_ambientLightLumiLvSet;
    uint8_t ivi_limitmodeset;
    uint8_t ivi_doorTopSwitch;
    uint8_t ivi_rvMirrorAutoTurnDownSet;
    uint8_t ivi_followMeHomeSet;
    uint8_t ivi_WinLFCtrlRqst;
    uint8_t ivi_WinRFCtrlRqst;
    uint8_t ivi_WinLRCtrlRqst;
    uint8_t ivi_WinRRCtrlRqst;
    uint8_t ivi_childLockRLCtrl;
    uint8_t ivi_childLockRRCtrl;
    uint8_t ivi_DriveDoorUnlockCtrl;
    uint8_t IVI_AutoDrySet;
}p_IVI_comfortSet_st = {0x00, 0x95, 18};

struct package_0x0A5_st_IVI_pwrSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_TripAReset;
    uint8_t ivi_TripBReset;
    uint8_t ivi_VehicleModeSet;
    uint8_t ivi_RegenModeSet;
    uint8_t ivi_traveModeSet;
    uint8_t ivi_ChargeControl;
    uint8_t ivi_ParkingChargeReq;
    uint8_t ivi_TowModeSet;
    uint8_t ivi_maxChrgSocSet;
    uint8_t ivi_chargeFormSet;
    uint8_t ivi_remainningMilModeSet;
    uint8_t ivi_ParkingChargeModeSet;
    uint8_t ivi_chargeSetValid;
    uint8_t ivi_ChargeEndTimeHour;
    uint8_t ivi_ChargeStartTimeHour;
    uint8_t ivi_ChargeEndTimeMinute;
    uint8_t ivi_ChargeStartTimeMinute;
    uint8_t ivi_ResetCurrentTrip;
    uint8_t IVI_AcFullChargeToWarmSet;
    uint8_t ivi_ChargeEndTimeValid;
    uint8_t ivi_ChargeStartTimeValid;
    uint8_t ivi_driveModeSet;
}p_IVI_pwrSet_st = {0x00, 0xA5, 23};

struct package_0x1D5_st_IVI_chassisSet1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_EmergencyHvOffRequestReserved;
    uint8_t ivi_ExhibitionModeCtrl;
    uint8_t ivi_DCDCAutoChargeSet;
    uint8_t ivi_OTAModeStatus;
    uint8_t IVI_HVDownRepairMode;
    uint8_t IVI_FactoryRestHold;
    uint8_t ivi_chassisSet1_rollingCounter;
    uint8_t ivi_chassisSet1_CheckSum;
}p_IVI_chassisSet1_st = {0x01, 0xD5, 9};

struct package_0x065_st_IVI_chassisSet_065
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_epsModeSet;
    uint8_t ivi_escOffSw;
    uint8_t ivi_hdcOnOffSet;
    uint8_t ivi_aebOnOffSet;
    uint8_t ivi_iBModeSet;
    uint8_t ivi_lcaBsdOnOffSet;
    uint8_t ivi_rctaOnOffSetReserved;
    uint8_t ivi_dowOnOffSet;
    uint8_t ivi_StartRevSOCSet;
    uint8_t ivi_hmaOnOffSet;
    uint8_t ivi_speedLimitOnOffSet;
    uint8_t ivi_ASCHeightModeSelected;
    uint8_t ivi_ASCMoveModeControl;
    uint8_t ivi_laneAssistFuncSet;
    uint8_t ivi_lasWarningModeSelection;
    uint8_t TrailerModeReq;
    uint8_t IVI_RCTBOnOffSet;
    uint8_t IVI_ELKOnOffSet;
    uint8_t ivi_avhOnOffSet;
    uint8_t ivi_pcwOnOffSet;
    uint8_t ivi_TJAFuncSet;
    uint8_t IVI_autododgeOnOffSet;
    uint8_t ivi_trailerModeOnOffSet;
    uint8_t ivi_esc_epbButtonRelease;
    uint8_t IVI_ApaOnOffReq;
}p_IVI_chassisSet_065_st = {0x00, 0x65, 26};

struct package_0x105_st_IVI_dvrSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_PRE_Key;
    uint8_t IVI_NEXT_Key;
    uint8_t IVI_Play_Key;
    uint8_t IVI_Lock_Key;
    uint8_t IVI_Delete_Request;
    uint8_t IVI_AVREnableSet;
    uint8_t IVI_AVRTapeSet;
    uint8_t IVI_AVREmergencyRecSet;
    uint8_t IVI_AVRPhotoReq;
    uint8_t IVI_FormatSDReq;
    uint8_t IVI_AVRRecCycleSet;
    uint8_t IVI_SetReplayDirectory;
    uint8_t ivi_VehicleInfoRecordSet;
    uint8_t ivi_FactorySettingReq;
    uint8_t IVI_SterringWheelHeatSw;
}p_IVI_dvrSet_st = {0x01, 0x05, 16};

struct package_0x098_st_IVI_dsmmSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_drSeatRouteSet;
    uint8_t IVI_drSeatbackrestSet;
    uint8_t IVI_drSeatCushionSet;
    uint8_t IVI_drSeatCushionAngleSet;
    uint8_t IVI_LmirrorUDSet;
    uint8_t IVI_LmirrorLRSet;
    uint8_t IVI_RmirrorUDSet;
    uint8_t IVI_RmirrorLRSet;
    uint8_t IVI_DSMChargeCtrl;
}p_IVI_dsmmSet_st = {0x00, 0x98, 10};

struct package_0x093_st_IVI_dsmmSet2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_PassSeatRouteSet;
    uint8_t IVI_PassSeatbackrestSet;
    uint8_t IVI_PassSeatCushionSet;
    uint8_t IVI_PassSeatCushionAngleSet;
    uint8_t IVI_PSMChargeCtrl;
}p_IVI_dsmmSet2_st = {0x00, 0x93, 6};

struct package_0x0C5_st_IVI_infoSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_darkIllumiLevelSetReserved;
    uint8_t ivi_TripSwitchReserved;
    uint8_t IVI_RearseatbeltVoiceWarningSet;
    uint8_t ivi_hudOnOffSet;
    uint8_t IVI_PEBSVoiceWarningSet;
    uint8_t ivi_NaviSwitchReserved;
    uint8_t ivi_themeSetReserved;
    uint8_t ivi_wcmLeftOnOffSet;
    uint8_t ivi_pdcOnOffSet;
    uint8_t ivi_ICthemegangedSetReserved;
    uint8_t IVI_FactoryResetCommand;
    uint8_t ivi_ICIllumiLevelSet;
    uint8_t IVI_laeb_SW;
    uint8_t ivi_vspOnOffSet;
    uint8_t ivi_vsp_SoundConfigure;
    uint8_t IVI_unlocksoundSet;
    uint8_t IVI_locksoundSet;
    uint8_t IVI_ISAOnOffSet;
    uint8_t ivi_IllumiLevelSetReserved;
}p_IVI_infoSet_st = {0x00, 0xC5, 20};

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

struct package_0x0C6_st_IVI_infoSet2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_VehIntMntnMile;
    uint8_t IVI_VehMntnMileClea;
    uint8_t IVI_OilMntnMileClea;
    uint8_t IVI_OilFilMntnMileClea;
    uint8_t IVI_AirFilMntnMileClea;
    uint8_t IVI_VehMntnTimeClea;
}p_IVI_infoSet2_st = {0x00, 0xC6, 7};

struct package_0x3D2_st_IVI_AVMSet_3D2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_AVMXCoordinate_H;
    uint8_t ivi_AVMXCoordinate_L;
    uint8_t ivi_AVMYCoordinate_H;
    uint8_t ivi_AVMYCoordinate_L;
    uint8_t ivi_AVMCoTouchMotion;
    uint8_t ivi_IVIthemeSet1;
    uint8_t IVI_TakeINVideoPosReq;
    uint8_t IVI_TakePhotoFaultReason;
    uint8_t IVI_AlarmListrequest;
    uint8_t IVI_driveModeSts;
    uint8_t IVI_PetFaultReason;
}p_IVI_AVMSet_3D2_st = {0x03, 0xD2, 12};

struct package_0x0F5_st_IVI_scuSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_easyEntrySet;
    uint8_t ivi_drSeatHeatLevelSet;
    uint8_t ivi_drSeatVentLevelSet;
    uint8_t ivi_passSeatHeatLevelSet;
    uint8_t ivi_passSeatVentLevelSet;
    uint8_t ivi_drSeatMassLevelSet;
    uint8_t ivi_passSeatMassLevelSet;
    uint8_t ivi_MirrorAutoFoldUnfoldSet;
    uint8_t IVI_RLSeatHeatLevelSet;
    uint8_t ivi_DrMassgIntenSet;
    uint8_t ivi_PsgMassgIntenSet;
    uint8_t IVI_DSMMemoryReq;
    uint8_t IVI_RRSeatHeatLevelSet;
}p_IVI_scuSet_st = {0x00, 0xF5, 14};

struct package_0x31C_st_IVI_vent1Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent1LocationActuator;
    uint8_t ivi_ElVent1ProgrammingDataSave;
    uint8_t ivi_ElVent1ObstructionCheck;
    uint8_t ivi_ElVent1MarkClear;
    uint8_t ivi_ElVent1CoilElectrify;
    uint8_t ivi_ElVent1LocationSelect;
    uint8_t ivi_ElVent1SpeedMode;
    uint8_t ivi_ElVent1MotorTargetLocation_H;
    uint8_t ivi_ElVent1MotorTargetLocation_L;
    uint8_t ivi_ElVent1MotorOriginalLocation_H;
    uint8_t ivi_ElVent1MotorOriginalLocation_L;
    uint8_t ivi_ElVent1EmergencyStopSwitch;
    uint8_t ivi_ElVent1EmergencyStopLocation;
    uint8_t ivi_ElVent1RotationMode;
    uint8_t ivi_ElVent1StopMode;
}p_IVI_vent1Ctrl_st = {0x03, 0x1C, 16};

struct package_0x31D_st_IVI_vent2Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent2LocationActuator;
    uint8_t ivi_ElVent2ProgrammingDataSave;
    uint8_t ivi_ElVent2ObstructionCheck;
    uint8_t ivi_ElVent2MarkClear;
    uint8_t ivi_ElVent2CoilElectrify;
    uint8_t ivi_ElVent2LocationSelect;
    uint8_t ivi_ElVent2SpeedMode;
    uint8_t ivi_ElVent2MotorTargetLocation_H;
    uint8_t ivi_ElVent2MotorTargetLocation_L;
    uint8_t ivi_ElVent2MotorOriginalLocation_H;
    uint8_t ivi_ElVent2MotorOriginalLocation_L;
    uint8_t ivi_ElVent2EmergencyStopSwitch;
    uint8_t ivi_ElVent2EmergencyStopLocation;
    uint8_t ivi_ElVent2RotationMode;
    uint8_t ivi_ElVent2StopMode;
}p_IVI_vent2Ctrl_st = {0x03, 0x1D, 16};

struct package_0x325_st_IVI_vent3Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent3LocationActuator;
    uint8_t ivi_ElVent3ProgrammingDataSave;
    uint8_t ivi_ElVent3ObstructionCheck;
    uint8_t ivi_ElVent3MarkClear;
    uint8_t ivi_ElVent3CoilElectrify;
    uint8_t ivi_ElVent3LocationSelect;
    uint8_t ivi_ElVent3SpeedMode;
    uint8_t ivi_ElVent3MotorTargetLocation_H;
    uint8_t ivi_ElVent3MotorTargetLocation_L;
    uint8_t ivi_ElVent3MotorOriginalLocation_H;
    uint8_t ivi_ElVent3MotorOriginalLocation_L;
    uint8_t ivi_ElVent3EmergencyStopSwitch;
    uint8_t ivi_ElVent3EmergencyStopLocation;
    uint8_t ivi_ElVent3RotationMode;
    uint8_t ivi_ElVent3StopMode;
}p_IVI_vent3Ctrl_st = {0x03, 0x25, 16};

struct package_0x328_st_IVI_vent4Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent4LocationActuator;
    uint8_t ivi_ElVent4ProgrammingDataSave;
    uint8_t ivi_ElVent4ObstructionCheck;
    uint8_t ivi_ElVent4MarkClear;
    uint8_t ivi_ElVent4CoilElectrify;
    uint8_t ivi_ElVent4LocationSelect;
    uint8_t ivi_ElVent4SpeedMode;
    uint8_t ivi_ElVent4MotorTargetLocation_H;
    uint8_t ivi_ElVent4MotorTargetLocation_L;
    uint8_t ivi_ElVent4MotorOriginalLocation_H;
    uint8_t ivi_ElVent4MotorOriginalLocation_L;
    uint8_t ivi_ElVent4EmergencyStopSwitch;
    uint8_t ivi_ElVent4EmergencyStopLocation;
    uint8_t ivi_ElVent4RotationMode;
    uint8_t ivi_ElVent4StopMode;
}p_IVI_vent4Ctrl_st = {0x03, 0x28, 16};

struct package_0x33A_st_IVI_vent5Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent5LocationActuator;
    uint8_t ivi_ElVent5ProgrammingDataSave;
    uint8_t ivi_ElVent5ObstructionCheck;
    uint8_t ivi_ElVent5MarkClear;
    uint8_t ivi_ElVent5CoilElectrify;
    uint8_t ivi_ElVent5LocationSelect;
    uint8_t ivi_ElVent5SpeedMode;
    uint8_t ivi_ElVent5MotorTargetLocation_H;
    uint8_t ivi_ElVent5MotorTargetLocation_L;
    uint8_t ivi_ElVent5MotorOriginalLocation_H;
    uint8_t ivi_ElVent5MotorOriginalLocation_L;
    uint8_t ivi_ElVent5EmergencyStopSwitch;
    uint8_t ivi_ElVent5EmergencyStopLocation;
    uint8_t ivi_ElVent5RotationMode;
    uint8_t ivi_ElVent5StopMode;
}p_IVI_vent5Ctrl_st = {0x03, 0x3A, 16};

struct package_0x33B_st_IVI_vent6Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent6LocationActuator;
    uint8_t ivi_ElVent6ProgrammingDataSave;
    uint8_t ivi_ElVent6ObstructionCheck;
    uint8_t ivi_ElVent6MarkClear;
    uint8_t ivi_ElVent6CoilElectrify;
    uint8_t ivi_ElVent6LocationSelect;
    uint8_t ivi_ElVent6SpeedMode;
    uint8_t ivi_ElVent6MotorTargetLocation_H;
    uint8_t ivi_ElVent6MotorTargetLocation_L;
    uint8_t ivi_ElVent6MotorOriginalLocation_H;
    uint8_t ivi_ElVent6MotorOriginalLocation_L;
    uint8_t ivi_ElVent6EmergencyStopSwitch;
    uint8_t ivi_ElVent6EmergencyStopLocation;
    uint8_t ivi_ElVent6RotationMode;
    uint8_t ivi_ElVent6StopMode;
}p_IVI_vent6Ctrl_st = {0x03, 0x3B, 16};

struct package_0x34A_st_IVI_vent7Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent7LocationActuator;
    uint8_t ivi_ElVent7ProgrammingDataSave;
    uint8_t ivi_ElVent7ObstructionCheck;
    uint8_t ivi_ElVent7MarkClear;
    uint8_t ivi_ElVent7CoilElectrify;
    uint8_t ivi_ElVent7LocationSelect;
    uint8_t ivi_ElVent7SpeedMode;
    uint8_t ivi_ElVent7MotorTargetLocation_H;
    uint8_t ivi_ElVent7MotorTargetLocation_L;
    uint8_t ivi_ElVent7MotorOriginalLocation_H;
    uint8_t ivi_ElVent7MotorOriginalLocation_L;
    uint8_t ivi_ElVent7EmergencyStopSwitch;
    uint8_t ivi_ElVent7EmergencyStopLocation;
    uint8_t ivi_ElVent7RotationMode;
    uint8_t ivi_ElVent7StopMode;
}p_IVI_vent7Ctrl_st = {0x03, 0x4A, 16};

struct package_0x34B_st_IVI_vent8Ctrl
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_ElVent8LocationActuator;
    uint8_t ivi_ElVent8ProgrammingDataSave;
    uint8_t ivi_ElVent8ObstructionCheck;
    uint8_t ivi_ElVent8MarkClear;
    uint8_t ivi_ElVent8CoilElectrify;
    uint8_t ivi_ElVent8LocationSelect;
    uint8_t ivi_ElVent8SpeedMode;
    uint8_t ivi_ElVent8MotorTargetLocation_H;
    uint8_t ivi_ElVent8MotorTargetLocation_L;
    uint8_t ivi_ElVent8MotorOriginalLocation_H;
    uint8_t ivi_ElVent8MotorOriginalLocation_L;
    uint8_t ivi_ElVent8EmergencyStopSwitch;
    uint8_t ivi_ElVent8EmergencyStopLocation;
    uint8_t ivi_ElVent8RotationMode;
    uint8_t ivi_ElVent8StopMode;
}p_IVI_vent8Ctrl_st = {0x03, 0x4B, 16};

struct package_0x33D_st_IVI_NaviChrgSt_33D
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_DestEstimSOC_H;
    uint8_t IVI_DestEstimSOC_L;
    uint8_t IVI_DestEstimTi_H;
    uint8_t IVI_DestEstimTi_L;
    uint8_t IVI_DestEstimMilg_H;
    uint8_t IVI_DestEstimMilg_L;
}p_IVI_NaviChrgSt_33D_st = {0x03, 0x3D, 7};

struct package_0x33E_st_IVI_NaviChrgSt_33E
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_NextChrgStationTyp;
    uint8_t IVI_NextChrgStationPileRatedPwr_H;
    uint8_t IVI_NextChrgStationPileRatedPwr_L;
    uint8_t IVI_NextChrgStationPileRatedCurrent_H;
    uint8_t IVI_NextChrgStationPileRatedCurrent_L;
    uint8_t IVI_NextChrgStationPileMaxU_H;
    uint8_t IVI_NextChrgStationPileMaxU_L;
    uint8_t IVI_NextChrgStationPileMinU_H;
    uint8_t IVI_NextChrgStationPileMinU_L;
    uint8_t IVI_OutChrgStationOpenHour;
    uint8_t IVI_NavigChrgPostReq;
}p_IVI_NaviChrgSt_33E_st = {0x03, 0x3E, 12};

struct package_0x052_st_IC_engineOFF
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_engOffTime_H;
    uint8_t ic_engOffTime_L;
    uint8_t ic_engOffTimeValid;
    uint8_t IC_songFaultNum;
    uint8_t IC_songWarningSts;
}p_IC_engineOFF_st = {0x00, 0x52, 6};

struct package_0x5FD_st_IC_faultSum
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IC_LowBatteryvoltage;
    uint8_t IC_engCoolantTempAlarm;
    uint8_t IC_lowfuleAlarm;
    uint8_t IC_lowbrakefluidlevel;
    uint8_t IC_lowoilpressure;
}p_IC_faultSum_st = {0x05, 0xFD, 6};

struct package_0x3F2_st_IC_infoSet
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_hudScreenTransition;
    uint8_t ic_hudHeightSet;
    uint8_t ic_hudillumiLvSet;
}p_IC_infoSet_st = {0x03, 0xF2, 4};

struct package_0x3F8_st_IC_3F8
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_PassAirbSuppressionStSet;
    uint8_t IC_driverSeatBeltStatus;
    uint8_t IC_driverSeatBeltStatusValid;
    uint8_t IC_passengerSeatBeltStatus;
    uint8_t IC_passengerSeatBeltStatusValid;
    uint8_t ic_passengerSeatDetectSts;
    uint8_t ic_RLSeatDetectSts;
    uint8_t IC_CLTCFuleRemainingMileage_H;
    uint8_t IC_CLTCFuleRemainingMileage_L;
    uint8_t IC_CLTCRemainingMileage_H;
    uint8_t IC_CLTCRemainingMileage_L;
    uint8_t IC_3F8Counter;
    uint8_t IC_3F8Checksum;
}p_IC_3F8_st = {0x03, 0xF8, 14};

struct package_0x4F4_st_IC_state3
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_avgTimeSincethelastchargeTripReserved_H;
    uint8_t ic_avgTimeSincethelastchargeTripReserved_L;
    uint8_t ic_avgSpdSincethelastchargeTripReserved_H;
    uint8_t ic_avgSpdSincethelastchargeTripReserved_L;
    uint8_t ic_FuelComsumpV2V_H;
    uint8_t ic_FuelComsumpV2V_L;
    uint8_t ic_FuelTankResistance;
    uint8_t ic_FuelConsumCrntTrip_H;
    uint8_t ic_FuelConsumCrntTrip_L;
}p_IC_state3_st = {0x04, 0xF4, 10};

struct package_0x571_st_IC_Warning
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IC_AlarmListflag;
    uint8_t IC_FaultNum;
    uint8_t IC_WarningStatus;
    uint8_t IC_FaultNum2;
    uint8_t IC_WarningStatus2;
    uint8_t IC_FaultNum3;
    uint8_t IC_WarningStatus3;
    uint8_t IC_FaultNum4;
    uint8_t IC_WarningStatus4;
    uint8_t IC_FaultNum5;
    uint8_t IC_WarningStatus5;
    uint8_t IC_FaultNum6;
    uint8_t IC_WarningStatus6;
}p_IC_Warning_st = {0x05, 0x71, 14};

struct package_0x570_st_IC_Warningfb
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IC_DMS_DistractionIconFB;
    uint8_t IC_DMS_FatigueIconFB;
    uint8_t IC_DMS_Res1;
    uint8_t IC_DMS_Res2;
    uint8_t IC_DMS_Res3;
}p_IC_Warningfb_st = {0x05, 0x70, 6};

struct package_0x2F2_st_IC_state
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_totalMileage_H;
    uint8_t ic_totalMileage_MH;
    uint8_t ic_totalMileage_ML;
    uint8_t ic_totalMileage_L;
    uint8_t ic_lowSocIndication;
    uint8_t ic_passengerSeatDetectSts;
    uint8_t ic_RMSeatDetectSts;
    uint8_t ic_RRSeatDetectSts;
    uint8_t ic_2ndRowLeftSeatBeltSts;
    uint8_t ic_2ndRowLeftSeatBeltStsValid;
    uint8_t ic_2ndRowMiddleSeatBeltSts;
    uint8_t ic_2ndRowMiddleSeatBeltStsValid;
    uint8_t ic_2ndRowRightSeatBeltSts;
    uint8_t ic_2ndRowRightSeatBeltStsValid;
    uint8_t ic_displayFail;
    uint8_t ic_qDashACCFail;
    uint8_t ic_RLSeatDetectSts;
    uint8_t ic_vehicleSpeedDisp_H;
    uint8_t ic_vehicleSpeedDisp_L;
    uint8_t ic_brakeFluidLevel;
    uint8_t ic_totalMileageValid;
    uint8_t ic_vehicleSpeedDispValid;
    uint8_t ic_state_rollingCounter;
    uint8_t ic_state_CheckSum;
}p_IC_state_st = {0x02, 0xF2, 25};

struct package_0x3F7_st_IC_info2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_SUMRemainingMileage_H;
    uint8_t ic_SUMRemainingMileage_L;
    uint8_t ic_WLTCRemainingMileage_H;
    uint8_t ic_WLTCRemainingMileage_L;
    uint8_t ic_SUMFuleRemainingMileage_H;
    uint8_t ic_SUMFuleRemainingMileage_L;
    uint8_t ic_WLTCFuleRemainingMileage_H;
    uint8_t ic_WLTCFuleRemainingMileage_L;
    uint8_t ic_SpeedLimitSts;
    uint8_t ic_SpeedLimitModeSts;
    uint8_t ic_RearseatbeltVoiceWarningSetFb;
    uint8_t ic_RemainingMilmodeSts;
    uint8_t ic_OverspeedSts;
    uint8_t ic_IllumiLevelSts;
}p_IC_info2_st = {0x03, 0xF7, 15};

struct package_0x482_st_IC_state1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_avgFuelConsumTripA_H;
    uint8_t ic_avgFuelConsumTripA_L;
    uint8_t ic_languageSts;
    uint8_t ic_avgFuelConsumCrntTrip_H;
    uint8_t ic_avgFuelConsumCrntTrip_L;
    uint8_t ic_avgFuelConsumTripB_H;
    uint8_t ic_avgFuelConsumTripB_L;
    uint8_t ic_oilPercentFail;
    uint8_t ic_avgFuelConsumCrntLastTrip_H;
    uint8_t ic_avgFuelConsumCrntLastTrip_L;
    uint8_t ic_oilPercent;
}p_IC_state1_st = {0x04, 0x82, 12};

struct package_0x491_st_IC_EnergyConsumption
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IC_E_energyconsumption_H;
    uint8_t IC_E_energyconsumption_L;
    uint8_t IC_E_energyconsumptionA_H;
    uint8_t IC_E_energyconsumptionA_L;
    uint8_t IC_E_energyconsumptionB_H;
    uint8_t IC_E_energyconsumptionB_L;
    uint8_t IC_F_energyconsumption_H;
    uint8_t IC_F_energyconsumption_L;
    uint8_t IC_F_energyconsumptionA_H;
    uint8_t IC_F_energyconsumptionA_L;
    uint8_t IC_F_energyconsumptionB_H;
    uint8_t IC_F_energyconsumptionB_L;
}p_IC_EnergyConsumption_st = {0x04, 0x91, 13};

struct package_0x492_st_IC_state2
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IC_VehRemMntnMile_H;
    uint8_t IC_VehRemMntnMile_MH;
    uint8_t IC_VehRemMntnMile_ML;
    uint8_t IC_VehRemMntnMile_L;
    uint8_t IC_VehMntnMileRmnReq;
    uint8_t IC_VehMntnTimeRmnReq;
    uint8_t IC_REMntnRmnReq;
    uint8_t ic_PowerReset;
    uint8_t ic_avgSpdTripA_H;
    uint8_t ic_avgSpdTripA_L;
    uint8_t ic_avgSpdCurrentTrip_H;
    uint8_t ic_avgSpdCurrentTrip_L;
}p_IC_state2_st = {0x04, 0x92, 13};

struct package_0x493_st_IC_state4
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ic_tripmeterA_H;
    uint8_t ic_tripmeterA_MH;
    uint8_t ic_tripmeterA_ML;
    uint8_t ic_tripmeterA_L;
    uint8_t ic_tripmeterB_H;
    uint8_t ic_tripmeterB_MH;
    uint8_t ic_tripmeterB_ML;
    uint8_t ic_tripmeterB_L;
    uint8_t IC_VehMntnMileCleaFb;
    uint8_t IC_OilMntnMileCleaFb;
    uint8_t IC_OilFilMntnMileCleaFb;
    uint8_t IC_AirFilMntnMileCleaFb;
    uint8_t IC_VehIntMntnMileFb;
}p_IC_state4_st = {0x04, 0x93, 14};

struct package_0x494_st_IC_state5
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IC_OilRemMntnMile_H;
    uint8_t IC_OilRemMntnMile_MH;
    uint8_t IC_OilRemMntnMile_ML;
    uint8_t IC_OilRemMntnMile_L;
    uint8_t IC_VehRemMntnTime_H;
    uint8_t IC_VehRemMntnTime_L;
    uint8_t IC_OilFilRemMntnMile_H;
    uint8_t IC_OilFilRemMntnMile_MH;
    uint8_t IC_OilFilRemMntnMile_ML;
    uint8_t IC_OilFilRemMntnMile_L;
    uint8_t IC_AirFilRemMntnMile_H;
    uint8_t IC_AirFilRemMntnMile_MH;
    uint8_t IC_AirFilRemMntnMile_ML;
    uint8_t IC_AirFilRemMntnMile_L;
}p_IC_state5_st = {0x04, 0x94, 15};

struct package_0x495_st_IVI_StatusAndNotify
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_FrameType;
    uint8_t IVI_WorkStatus;
    uint8_t IVI_CurrentVideo;
    uint8_t IVI_EventNotify;
    uint8_t IVI_IC_Sync;
    uint8_t IVI_Respitemodests;
    uint8_t IVI_ModeSts;
    uint8_t IVI_averagePowerConsumThisTrip_H;
    uint8_t IVI_averagePowerConsumThisTrip_L;
    uint8_t IVI_SentryReq;
    uint8_t IVI_SentryAlarmSts;
    uint8_t IVI_ModeReq;
    uint8_t IVI_SentryTimeFd;
    uint8_t IVI_ChildrenLeftremindSts;
    uint8_t IVI_PetModeSts;
    uint8_t IVI_SentryFaultReason;
    uint8_t IVI_WashModeSts;
    uint8_t IVI_HCUcontrol;
}p_IVI_StatusAndNotify_st = {0x04, 0x95, 19};

struct package_0x496_st_IVI_hmi
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_DMS_DistractionIcon;
    uint8_t IVI_DMS_FatigueIcon;
    uint8_t IVI_DMS_Res1;
    uint8_t IVI_DMS_Res2;
    uint8_t IVI_DMS_Res3;
    uint8_t IVI_UserID;
    uint8_t ivi_CampModeReq;
}p_IVI_hmi_st = {0x04, 0x96, 8};

struct package_0x5F0_st_IVI_State_5F0
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t cdc_status;
    uint8_t cdc_mcuStatus;
    uint8_t cdc_mcuEnvStatus;
    uint8_t cdc_mcuBatStatus;
    uint8_t cdc_mcuFsmStatus;
    uint8_t cdc_rdcStatus;
    uint8_t cdc_socChipStatus;
    uint8_t cdc_icPowerStatus;
    uint8_t cdc_iviPowerStatus;
    uint8_t cdc_silsStatus;
    uint8_t cdc_icLcdStatus;
    uint8_t cdc_iviLcdStatus;
}p_IVI_State_5F0_st = {0x05, 0xF0, 13};

struct package_0x4A2_st_IC_RequestAndStatus
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IC_FrameType;
    uint8_t IC_WorkStatus;
    uint8_t IC_RequestVideo;
    uint8_t IC_currentDisplayVideo;
    uint8_t IC_keyOperation;
    uint8_t IC_RightVideoStatus;
    uint8_t IC_DisFail;
}p_IC_RequestAndStatus_st = {0x04, 0xA2, 8};

struct package_0x3B5_st_IVI_set
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_hvacDefrostMode;
    uint8_t ivi_hvacOnOffReq;
    uint8_t IVI_ExhibitionScene;
    uint8_t ivi_hvacAutoModeReq;
    uint8_t ivi_hvacRecircModeReq;
    uint8_t IVI_ACEnergySavingReq;
    uint8_t ivi_hvacModeReq;
    uint8_t ivi_driverTempCSet;
    uint8_t ivi_hvacBlowLvReq;
    uint8_t ivi_passengerTempCSet;
    uint8_t ivi_hvacDualMode;
    uint8_t ivi_acReq;
    uint8_t IVI_NavigatioRecircReq;
    uint8_t IVI_NaviTunnelstatus;
    uint8_t IVI_ScreenOutReq;
    uint8_t USB_Sts;
    uint8_t ivi_svcSteerInteractionSetReserved;
    uint8_t ivi_InterfaceSwitchReq;
    uint8_t ivi_languageSet;
    uint8_t IVI_IntPuficationSw;
    uint8_t ivi_unitSet;
    uint8_t IVI_NaturalwindSw;
    uint8_t IVI_VideoResult;
    uint8_t IVI_TakePhotoReq;
}p_IVI_set_st = {0x03, 0xB5, 25};

struct package_0x485_st_IVI_navi
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_crossNaviMode;
    uint8_t ivi_naviDirection;
    uint8_t ivi_crossNaviDistance_H;
    uint8_t ivi_crossNaviDistance_MH;
    uint8_t ivi_crossNaviDistance_ML;
    uint8_t ivi_crossNaviDistance_L;
}p_IVI_navi_st = {0x04, 0x85, 7};

struct package_0x486_st_IVI_NaviDirection_LaneX
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_NavidirectionLane1;
    uint8_t ivi_NavidirectionLane2;
    uint8_t ivi_NavidirectionLane3;
    uint8_t ivi_NavidirectionLane4;
    uint8_t ivi_NavidirectionLane5;
    uint8_t ivi_NavidirectionLane6;
    uint8_t ivi_NavidirectionLane7;
    uint8_t ivi_NavidirectionLane8;
}p_IVI_NaviDirection_LaneX_st = {0x04, 0x86, 9};

struct package_0x395_st_IVI_media
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_radioStatus;
    uint8_t ivi_blueToothStatus;
    uint8_t ivi_usbStatus;
    uint8_t ivi_iPodStatus;
    uint8_t ivi_lvdsStatus;
    uint8_t ivi_DMS_Sysfault;
    uint8_t ivi_sdStatus;
    uint8_t ivi_auxStatus_Reserved;
    uint8_t ivi_tvStatus;
    uint8_t ivi_discStatus;
    uint8_t ivi_dvbtStatus;
    uint8_t ivi_naviStatus;
    uint8_t ivi_frequenceAM_H;
    uint8_t ivi_frequenceAM_L;
    uint8_t ivi_lvdsReadyStatus;
    uint8_t ivi_frequenceFM;
}p_IVI_media_st = {0x03, 0x95, 17};

struct package_0x3C5_st_IVI_naviText
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_naviTextStrLength;
    uint8_t ivi_naviTextCountNum;
    uint8_t ivi_naviText1_H;
    uint8_t ivi_naviText1_L;
    uint8_t ivi_naviText2_H;
    uint8_t ivi_naviText2_L;
    uint8_t ivi_naviText3_H;
    uint8_t ivi_naviText3_L;
}p_IVI_naviText_st = {0x03, 0xC5, 9};

struct package_0x3A5_st_IVI_TelSongText
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t ivi_telSongTextStrLength;
    uint8_t ivi_telSongTextCountNum;
    uint8_t ivi_telSongTextType;
    uint8_t ivi_telSongTextEncodingType;
    uint8_t ivi_telSongText1_H;
    uint8_t ivi_telSongText1_L;
    uint8_t ivi_telSongText2_H;
    uint8_t ivi_telSongText2_L;
    uint8_t ivi_telSongText3_H;
    uint8_t ivi_telSongText3_L;
}p_IVI_TelSongText_st = {0x03, 0xA5, 11};

struct package_0x7A5_st_Diag_Resp_IVI
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t Diag_Resp_IVI_Data_8;
    uint8_t Diag_Resp_IVI_Data_7;
    uint8_t Diag_Resp_IVI_Data_6;
    uint8_t Diag_Resp_IVI_Data_5;
    uint8_t Diag_Resp_IVI_Data_4;
    uint8_t Diag_Resp_IVI_Data_3;
    uint8_t Diag_Resp_IVI_Data_2;
    uint8_t Diag_Resp_IVI_Data_1;
}p_Diag_Resp_IVI_st = {0x07, 0xA5, 9};

struct package_0x3E1_st_IVI_ADAS_3E1
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_MapSpeedlimit;
    uint8_t IVI_FactoryRestHold;
    uint8_t IVI_MapStatus;
    uint8_t IVI_MapNextRamp;
    uint8_t IVI_MapCurrentRoad;
    uint8_t IVI_MapRampOffset_H;
    uint8_t IVI_MapRampOffset_L;
    uint8_t IVI_MapSpeedlimit_Unit;
    uint8_t IVI_MapRoadtype;
    uint8_t IVI_MapSpeedlimit_Type;
    uint8_t IVI_MapTimeConditionSignUsed;
    uint8_t IVI_MapTimeConditionSignExist;
    uint8_t IVI_MapTrafficSign_Type;
    uint8_t IVI_MapSpeedLimit_Rain;
    uint8_t IVI_MapSpeedLimit_Snow;
    uint8_t IVI_MapCountryCode;
}p_IVI_ADAS_3E1_st = {0x03, 0xE1, 17};

struct package_0x500_st_Wacc_500
{
    uint8_t canid_high;
    uint8_t canid_low;
    uint8_t data_len;
    uint8_t data_status;
    uint8_t IVI_Waccst;
    uint8_t IVI_IviConWcp;
    uint8_t IVI_WaccTempDisply;
    uint8_t IVI_WaccEault;
    uint8_t IVI_WacctgTemp;
}p_Wacc_500_st = {0x05, 0x00, 6};



#endif