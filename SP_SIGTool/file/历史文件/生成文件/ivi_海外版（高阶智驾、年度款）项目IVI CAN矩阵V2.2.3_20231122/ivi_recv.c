/**
* Copyright (c) 2018-2023 ThunderSoft
* All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
* You may not use, copy, distribute, modify, transmit in any form this file
* except in compliance with ThunderSoft in writing by applicable law.
*
*/
/**
* @file    ivi_recv.c
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

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include <string.h>
#include "app_task_cfg.h"
#include "ipc_api.h"
#include "r_rlin.h"
#include "log_api.h"
#include "RTE.h"
#include "ivi_recv.h"
#include "ivi_api.h"
#include "NvmControl.h"
#include "NvmIf.h"

#define IVI_SIG_BUF_MAX 50
#define READFLASHOK     1
extern const uint8_t Com_SignalInitValue_IVI_UserGearFb_0x408_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_LockCloseWinSet_0x096_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_childLockCtrl_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_centralLockCtrl_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_fuelPortCapOpenCtrl_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_v2vChrgOnOffSet_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_obcDschrgOnOffSet_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_chrgPortCapOpenCtrl_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_NormalHvOffRequest_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_MirrorSw_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_rearDefrostCtrl_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_MaxFuelConsumptionSW_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_MaxFuelConsumptionModeSW_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_approachingUnlockCtrl_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_awayLockCtrl_0x075_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_NozzleHeatingSw_0x095_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_rvMirrorAutoTurnDownSet_0x095_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_followMeHomeSet_0x095_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_AutoDrySet_0x095_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_VehicleModeSet_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_RegenModeSet_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_ChargeControl_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_ParkingChargeReq_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_TowModeSet_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_maxChrgSocSet_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_ParkingChargeModeSet_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_chargeSetValid_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_ChargeStartTimeHour_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_ChargeStartTimeMinute_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_ChargeStartTimeValid_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_driveModeSet_0x0A5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_epsModeSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_escOffSw_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hdcOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_aebOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_lcaBsdOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_rctaOnOffSetReserved_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_dowOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hmaOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_laneAssistFuncSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_lasWarningModeSelection_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_TrailerModeReq_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_RCTBOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_ELKOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_avhOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_pcwOnOffSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_TJAFuncSet_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_esc_epbButtonRelease_0x065_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_SterringWheelHeatSw_0x105_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_RearseatbeltVoiceWarningSet_0x0C5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hudOnOffSet_0x0C5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_pdcOnOffSet_0x0C5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_vsp_SoundConfigure_0x0C5_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_unlocksoundSet_0x0C5_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_ISAOnOffSet_0x0C5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_easyEntrySet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_drSeatHeatLevelSet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_passSeatHeatLevelSet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_drSeatMassLevelSet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_passSeatMassLevelSet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_MirrorAutoFoldUnfoldSet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_DrMassgIntenSet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_PsgMassgIntenSet_0x0F5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ic_hudillumiLvSet_0x3F2_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_PassAirbSuppressionStSet_0x3F8_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hvacOnOffReq_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hvacAutoModeReq_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hvacRecircModeReq_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_IVI_ACEnergySavingReq_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hvacModeReq_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_driverTempCSet_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hvacBlowLvReq_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_passengerTempCSet_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_hvacDualMode_0x3B5_INFO_Message;
extern const uint8_t Com_SignalInitValue_ivi_acReq_0x3B5_INFO_Message;
void setSignal_IC_info(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_SLA_408(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_User_ID(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_096(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_control(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_comfortSet(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_pwrSet(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_chassisSet1(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_chassisSet_065(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_APASet_066(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_ACCSet_067(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_ACCSet_069(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_AVMSet_068(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_APASet_06A(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_APASet_06B(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_dvrSet(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_dsmmSet(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_dsmmSet2(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_infoSet(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_infoSet2(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_AVMSet_3D2(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_scuSet(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent1Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent2Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent3Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent4Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent5Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent6Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent7Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_vent8Ctrl(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_NaviChrgSt_33D(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_NaviChrgSt_33E(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_engineOFF(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_faultSum(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_infoSet(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_3F8(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_state3(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_Warning(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_Warningfb(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_state(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_info2(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_state1(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_EnergyConsumption(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_state2(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_state4(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_state5(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_StatusAndNotify(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_hmi(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_State_5F0(uint8_t *sigbuff, uint8_t len);
void setSignal_IC_RequestAndStatus(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_set(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_navi(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_NaviDirection_LaneX(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_media(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_naviText(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_TelSongText(uint8_t *sigbuff, uint8_t len);
void setSignal_Diag_Resp_IVI(uint8_t *sigbuff, uint8_t len);
void setSignal_IVI_ADAS_3E1(uint8_t *sigbuff, uint8_t len);
void setSignal_Wacc_500(uint8_t *sigbuff, uint8_t len);
void setIVISignal_IVI_infoSet_ivi_ICIllumiLevelSet(uint8_t par);
static struct package_0x0E6_st_IVI_EPA_VOL p_IVI_EPA_VOL_bk = {0};
static struct package_0x0E7_st_IVI_EPA_ADAS_VOL p_IVI_EPA_ADAS_VOL_bk = {0};
static struct package_0x0E9_st_IVI_EPA_CONTROL p_IVI_EPA_CONTROL_bk = {0};
static struct package_0x0EA_st_IVI_EPA_GEQ_GAIN p_IVI_EPA_GEQ_GAIN_bk = {0};
uint8_t invm_data_temp[E_APP_DATA_TYPE_Max] = {0};
static uint8_t s_u8FirstPowerOnFlag = 0;

static uint8_t s_invm_data[E_APP_DATA_TYPE_Max] = {0};
const uint8_t audio_par_default[E_APP_DATA_TYPE_Max] = {
                        0x23, 0x19, 0x23, 0x23, 0x23, 0x23, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, \
                                                                    // len 17, p_IVI_EPA_VOL_st
                        0x0, 0x0, 0x0, 0x19, \
                                                                    // len 4, p_IVI_EPA_ADAS_VOL_st
                        0x7, 0x7, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0, \
                                                                    // len 13, p_IVI_EPA_CONTROL_st
                        0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, \
                                                                    // len 7, p_IVI_EPA_GEQ_GAIN_st
                        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // not use
};

void Interaction_Init() {
    uint8_t ret = 0;
    ret = NvmReadDataFlash(STOR_DATABLK_SIGNALS, (uint8_t *)&s_invm_data, sizeof(s_invm_data));
    if (ret != READFLASHOK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"checksum error / NVM empty :\r\n");
        memcpy((uint8_t *)&s_invm_data, (uint8_t *)&audio_par_default, sizeof(s_invm_data));
    }
    memcpy((uint8_t *)(&p_IVI_EPA_VOL_st.IVI_CH0_CH1_VOL_STEP), (uint8_t *)&s_invm_data[E_APP_IVI_CH0_CH1_VOL_STEP], sizeof(p_IVI_EPA_VOL_st)-4);
    memcpy((uint8_t *)(&p_IVI_EPA_ADAS_VOL_st.IVI_CH8_VOL_STEP), (uint8_t *)&s_invm_data[E_APP_IVI_CH8_VOL_STEP], sizeof(p_IVI_EPA_ADAS_VOL_st)-4);
    memcpy((uint8_t *)(&p_IVI_EPA_CONTROL_st.IVI_SOUND_FADE), (uint8_t *)&s_invm_data[E_APP_IVI_SOUND_FADE], sizeof(p_IVI_EPA_CONTROL_st)-4);
    memcpy((uint8_t *)(&p_IVI_EPA_GEQ_GAIN_st.IVI_GEQ_GAIN_BAND_1), (uint8_t *)&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_1], sizeof(p_IVI_EPA_GEQ_GAIN_st)-4);
    // backup android data
    memcpy(&p_IVI_EPA_VOL_bk, &p_IVI_EPA_VOL_st, sizeof(p_IVI_EPA_VOL_st));
    memcpy(&p_IVI_EPA_ADAS_VOL_bk, &p_IVI_EPA_ADAS_VOL_st, sizeof(p_IVI_EPA_ADAS_VOL_st));
    memcpy(&p_IVI_EPA_CONTROL_bk, &p_IVI_EPA_CONTROL_st, sizeof(p_IVI_EPA_CONTROL_st));
    memcpy(&p_IVI_EPA_GEQ_GAIN_bk, &p_IVI_EPA_GEQ_GAIN_st, sizeof(p_IVI_EPA_GEQ_GAIN_st));
}
void interaction_output_to_can(void) {
    uint8_t bResult = 0;
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH0_CH1_VOL_STEP(&s_invm_data[E_APP_IVI_CH0_CH1_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH2_VOL_STEP(&s_invm_data[E_APP_IVI_CH2_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH3_VOL_STEP(&s_invm_data[E_APP_IVI_CH3_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH4_VOL_STEP(&s_invm_data[E_APP_IVI_CH4_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH5_VOL_STEP(&s_invm_data[E_APP_IVI_CH5_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH6_VOL_STEP(&s_invm_data[E_APP_IVI_CH6_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH7_VOL_STEP(&s_invm_data[E_APP_IVI_CH7_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH0_CH1_MUTE(&s_invm_data[E_APP_IVI_CH0_CH1_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH2_MUTE(&s_invm_data[E_APP_IVI_CH2_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH3_MUTE(&s_invm_data[E_APP_IVI_CH3_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH4_MUTE(&s_invm_data[E_APP_IVI_CH4_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH5_MUTE(&s_invm_data[E_APP_IVI_CH5_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH6_MUTE(&s_invm_data[E_APP_IVI_CH6_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH7_MUTE(&s_invm_data[E_APP_IVI_CH7_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH8_MUTE(&s_invm_data[E_APP_IVI_CH8_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH9_MUTE(&s_invm_data[E_APP_IVI_CH9_MUTE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_VOL_ComIn_VeCAN_IVI_CH10_CH15_MUTE(&s_invm_data[E_APP_IVI_CH10_CH15_MUTE]);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_ADAS_VOL_ComIn_VeCAN_IVI_CH8_VOL_STEP(&s_invm_data[E_APP_IVI_CH8_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_ADAS_VOL_ComIn_VeCAN_IVI_CH9_VOL_STEP(&s_invm_data[E_APP_IVI_CH9_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_ADAS_VOL_ComIn_VeCAN_IVI_CH10_CH15_VOL_STEP(&s_invm_data[E_APP_IVI_CH10_CH15_VOL_STEP]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_ADAS_VOL_ComIn_VeCAN_IVI_CH0_CH1_OMP_STEP(&s_invm_data[E_APP_IVI_CH0_CH1_OMP_STEP]);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_SOUND_FADE(&s_invm_data[E_APP_IVI_SOUND_FADE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_SOUND_BAL(&s_invm_data[E_APP_IVI_SOUND_BAL]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_ATMOS_MOD_TYPE(&s_invm_data[E_APP_IVI_ATMOS_MOD_TYPE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_VOL_SPEED_SW(&s_invm_data[E_APP_IVI_VOL_SPEED_SW]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_ESE_MOD_SW(&s_invm_data[E_APP_IVI_ESE_MOD_SW]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_ESE_MOD_TYPE(&s_invm_data[E_APP_IVI_ESE_MOD_TYPE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_ESE_VOL(&s_invm_data[E_APP_IVI_ESE_VOL]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_PED_ALARM(&s_invm_data[E_APP_IVI_PED_ALARM]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_UNLOCK_SW(&s_invm_data[E_APP_IVI_UNLOCK_SW]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_LOCK_SW(&s_invm_data[E_APP_IVI_LOCK_SW]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_OMP_Switch(&s_invm_data[E_APP_IVI_OMP_Switch]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_HRS_MODE_TYPE(&s_invm_data[E_APP_IVI_HRS_MODE_TYPE]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_CONTROL_ComIn_VeCAN_IVI_ECALL_STATUS(&s_invm_data[E_APP_IVI_ECALL_STATUS]);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_GEQ_GAIN_ComIn_VeCAN_IVI_GEQ_GAIN_BAND_1(&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_1]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_GEQ_GAIN_ComIn_VeCAN_IVI_GEQ_GAIN_BAND_2(&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_2]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_GEQ_GAIN_ComIn_VeCAN_IVI_GEQ_GAIN_BAND_3(&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_3]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_GEQ_GAIN_ComIn_VeCAN_IVI_GEQ_GAIN_BAND_4(&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_4]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_GEQ_GAIN_ComIn_VeCAN_IVI_GEQ_GAIN_BAND_5(&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_5]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_GEQ_GAIN_ComIn_VeCAN_IVI_GEQ_GAIN_BAND_6(&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_6]);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_EPA_GEQ_GAIN_ComIn_VeCAN_IVI_GEQ_GAIN_BAND_7(&s_invm_data[E_APP_IVI_GEQ_GAIN_BAND_7]);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"first power on send fail :0x%x\r\n", bResult);
    }
}

void Ivi_RecvIVISignal(Message msg, uint8_t type)
{
    if (s_u8FirstPowerOnFlag == 0) {
        Interaction_Init();
        interaction_output_to_can();
        s_u8FirstPowerOnFlag = 1;
    }
    memcpy(&invm_data_temp, &s_invm_data, E_APP_DATA_TYPE_Max);

    uint8_t tempBuffer[RX_IVI_SIG_MAX_LEN] = {0};
    memcpy(tempBuffer, msg.lparam, msg.len);
    int i = 0;

    int startpos = 0;
    while(startpos + 3 < msg.len) {
        uint16_t can_id = (((uint16_t)tempBuffer[startpos]) << 8) + tempBuffer[startpos + 1];
        uint8_t len = tempBuffer[startpos + 2];
        uint8_t status = tempBuffer[startpos + 3];
        if (0 == can_id) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"can_id error, can_id:0x%x\r\n", can_id);
            break;
        }
        if (0 == len) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"len == 0\r\n");
            break;
        }
        if (startpos + len + 3 > msg.len) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"len error, can_id:0x%x, startpos:%d, len:%d, msg.len:%d\r\n", can_id, startpos, len+3, msg.len);
            break;
        }
        if (status != RTE_SIG_OK) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"status not ok, can_id:0x%x, status:%d\r\n", can_id, status);
            startpos = startpos + len + 3;
            continue;
        }
        if (len - 1 > IVI_SIG_BUF_MAX) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len over long:%d\r\n", len - 1);
            startpos = startpos + len + 3;
            continue;
        }
        /* set signal */
        uint8_t sigbuff[IVI_SIG_BUF_MAX];
        memcpy(sigbuff, &tempBuffer[startpos + 4], len - 1);
        if (IVI_SIG_PUB == type) {
            switch (can_id) {
            case 0x4F3:
                setSignal_IC_info(sigbuff, len - 1);
                break;
            case 0x408:
                setSignal_IVI_SLA_408(sigbuff, len - 1);
                break;
            case 0x376:
                setSignal_IVI_User_ID(sigbuff, len - 1);
                break;
            case 0x096:
                setSignal_IVI_096(sigbuff, len - 1);
                break;
            case 0x075:
                setSignal_IVI_control(sigbuff, len - 1);
                break;
            case 0x095:
                setSignal_IVI_comfortSet(sigbuff, len - 1);
                break;
            case 0x0A5:
                setSignal_IVI_pwrSet(sigbuff, len - 1);
                break;
            case 0x1D5:
                setSignal_IVI_chassisSet1(sigbuff, len - 1);
                break;
            case 0x065:
                setSignal_IVI_chassisSet_065(sigbuff, len - 1);
                break;
            case 0x066:
                setSignal_IVI_APASet_066(sigbuff, len - 1);
                break;
            case 0x067:
                setSignal_IVI_ACCSet_067(sigbuff, len - 1);
                break;
            case 0x069:
                setSignal_IVI_ACCSet_069(sigbuff, len - 1);
                break;
            case 0x068:
                setSignal_IVI_AVMSet_068(sigbuff, len - 1);
                break;
            case 0x06A:
                setSignal_IVI_APASet_06A(sigbuff, len - 1);
                break;
            case 0x06B:
                setSignal_IVI_APASet_06B(sigbuff, len - 1);
                break;
            case 0x105:
                setSignal_IVI_dvrSet(sigbuff, len - 1);
                break;
            case 0x098:
                setSignal_IVI_dsmmSet(sigbuff, len - 1);
                break;
            case 0x093:
                setSignal_IVI_dsmmSet2(sigbuff, len - 1);
                break;
            case 0x0C5:
                setSignal_IVI_infoSet(sigbuff, len - 1);
                break;
            case 0x0C6:
                setSignal_IVI_infoSet2(sigbuff, len - 1);
                break;
            case 0x3D2:
                setSignal_IVI_AVMSet_3D2(sigbuff, len - 1);
                break;
            case 0x0F5:
                setSignal_IVI_scuSet(sigbuff, len - 1);
                break;
            case 0x31C:
                setSignal_IVI_vent1Ctrl(sigbuff, len - 1);
                break;
            case 0x31D:
                setSignal_IVI_vent2Ctrl(sigbuff, len - 1);
                break;
            case 0x325:
                setSignal_IVI_vent3Ctrl(sigbuff, len - 1);
                break;
            case 0x328:
                setSignal_IVI_vent4Ctrl(sigbuff, len - 1);
                break;
            case 0x33A:
                setSignal_IVI_vent5Ctrl(sigbuff, len - 1);
                break;
            case 0x33B:
                setSignal_IVI_vent6Ctrl(sigbuff, len - 1);
                break;
            case 0x34A:
                setSignal_IVI_vent7Ctrl(sigbuff, len - 1);
                break;
            case 0x34B:
                setSignal_IVI_vent8Ctrl(sigbuff, len - 1);
                break;
            case 0x33D:
                setSignal_IVI_NaviChrgSt_33D(sigbuff, len - 1);
                break;
            case 0x33E:
                setSignal_IVI_NaviChrgSt_33E(sigbuff, len - 1);
                break;
            case 0x052:
                setSignal_IC_engineOFF(sigbuff, len - 1);
                break;
            case 0x5FD:
                setSignal_IC_faultSum(sigbuff, len - 1);
                break;
            case 0x3F2:
                setSignal_IC_infoSet(sigbuff, len - 1);
                break;
            case 0x3F8:
                setSignal_IC_3F8(sigbuff, len - 1);
                break;
            case 0x4F4:
                setSignal_IC_state3(sigbuff, len - 1);
                break;
            case 0x571:
                setSignal_IC_Warning(sigbuff, len - 1);
                break;
            case 0x570:
                setSignal_IC_Warningfb(sigbuff, len - 1);
                break;
            case 0x2F2:
                setSignal_IC_state(sigbuff, len - 1);
                break;
            case 0x3F7:
                setSignal_IC_info2(sigbuff, len - 1);
                break;
            case 0x482:
                setSignal_IC_state1(sigbuff, len - 1);
                break;
            case 0x491:
                setSignal_IC_EnergyConsumption(sigbuff, len - 1);
                break;
            case 0x492:
                setSignal_IC_state2(sigbuff, len - 1);
                break;
            case 0x493:
                setSignal_IC_state4(sigbuff, len - 1);
                break;
            case 0x494:
                setSignal_IC_state5(sigbuff, len - 1);
                break;
            case 0x495:
                setSignal_IVI_StatusAndNotify(sigbuff, len - 1);
                break;
            case 0x496:
                setSignal_IVI_hmi(sigbuff, len - 1);
                break;
            case 0x5F0:
                setSignal_IVI_State_5F0(sigbuff, len - 1);
                break;
            case 0x4A2:
                setSignal_IC_RequestAndStatus(sigbuff, len - 1);
                break;
            case 0x3B5:
                setSignal_IVI_set(sigbuff, len - 1);
                break;
            case 0x485:
                setSignal_IVI_navi(sigbuff, len - 1);
                break;
            case 0x486:
                setSignal_IVI_NaviDirection_LaneX(sigbuff, len - 1);
                break;
            case 0x395:
                setSignal_IVI_media(sigbuff, len - 1);
                break;
            case 0x3C5:
                setSignal_IVI_naviText(sigbuff, len - 1);
                break;
            case 0x3A5:
                setSignal_IVI_TelSongText(sigbuff, len - 1);
                break;
            case 0x7A5:
                setSignal_Diag_Resp_IVI(sigbuff, len - 1);
                break;
            case 0x3E1:
                setSignal_IVI_ADAS_3E1(sigbuff, len - 1);
                break;
            case 0x500:
                setSignal_Wacc_500(sigbuff, len - 1);
                break;
            default:
                break;
            }
        } else if (IVI_SIG_PRI == type) {
            switch (can_id) {
            default:
                break;
            }
        }
        startpos = startpos + len + 3;
    }
    if (0 != memcmp(s_invm_data, invm_data_temp, E_APP_DATA_TYPE_Max)) {
        uint8_t writeRes = 0;
        memcpy(s_invm_data, invm_data_temp, E_APP_DATA_TYPE_Max);
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,">>> Update interaction nvm , checksum = %d\r\n", s_invm_data[E_APP_CheckSumNum]);
        writeRes = NvmWriteDataFlash(STOR_DATABLK_SIGNALS, s_invm_data);
        if (DATAFLASH_WRITE_NG == writeRes) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT, "Failed to save SIGNALS \r\n");
        }
    }
}

void setSignal_IC_info(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ic_avgSpdTripB = 0;
    uint16_t u16ic_lastingtime = 0;
    uint16_t u16ic_mileageSincethelastcharge = 0;
    uint16_t u16ic_tripmeterThisMoment = 0;
    if (p_IC_info_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_info_st) + 4, sigbuff, len);

    u16ic_avgSpdTripB = (((uint16_t)p_IC_info_st.ic_avgSpdTripB_H) << 8) + 
                                ((uint16_t)p_IC_info_st.ic_avgSpdTripB_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info_ComIn_VeCAN_ic_avgSpdTripB(&u16ic_avgSpdTripB);
    u16ic_lastingtime = (((uint16_t)p_IC_info_st.ic_lastingtime_H) << 8) + 
                                ((uint16_t)p_IC_info_st.ic_lastingtime_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info_ComIn_VeCAN_ic_lastingtime(&u16ic_lastingtime);
    u16ic_mileageSincethelastcharge = (((uint16_t)p_IC_info_st.ic_mileageSincethelastcharge_H) << 8) + 
                                ((uint16_t)p_IC_info_st.ic_mileageSincethelastcharge_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info_ComIn_VeCAN_ic_mileageSincethelastcharge(&u16ic_mileageSincethelastcharge);
    u16ic_tripmeterThisMoment = (((uint16_t)p_IC_info_st.ic_tripmeterThisMoment_H) << 8) + 
                                ((uint16_t)p_IC_info_st.ic_tripmeterThisMoment_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info_ComIn_VeCAN_ic_tripmeterThisMoment(&u16ic_tripmeterThisMoment);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_info error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_SLA_408(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_SLA_408_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_SLA_408_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_currentRoadType(&p_IVI_SLA_408_st.ivi_currentRoadType);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_NAVIcameraspeedLimitvalueValid(&p_IVI_SLA_408_st.ivi_NAVIcameraspeedLimitvalueValid);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_NAVIspeedLimitvalueValid(&p_IVI_SLA_408_st.ivi_NAVIspeedLimitvalueValid);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_NAVItype(&p_IVI_SLA_408_st.ivi_NAVItype);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_NAVIcameraspeedLimitvalue(&p_IVI_SLA_408_st.ivi_NAVIcameraspeedLimitvalue);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_NAVIspeedLimitvalue(&p_IVI_SLA_408_st.ivi_NAVIspeedLimitvalue);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_NAVIStaus(&p_IVI_SLA_408_st.ivi_NAVIStaus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_VehicleRepairModeReq(&p_IVI_SLA_408_st.IVI_VehicleRepairModeReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_VehicleRepairModeSts(&p_IVI_SLA_408_st.IVI_VehicleRepairModeSts);
    if(p_IVI_SLA_408_st.IVI_UserGearFb != Com_SignalInitValue_IVI_UserGearFb_0x408_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_UserGearFb(&p_IVI_SLA_408_st.IVI_UserGearFb);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_CarSearchSts(&p_IVI_SLA_408_st.IVI_CarSearchSts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_CarSearchControl(&p_IVI_SLA_408_st.IVI_CarSearchControl);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_ModeSuppressSts(&p_IVI_SLA_408_st.IVI_ModeSuppressSts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_UserClass(&p_IVI_SLA_408_st.IVI_UserClass);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_AutoRainWiperReq(&p_IVI_SLA_408_st.IVI_AutoRainWiperReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_VehiclePosition(&p_IVI_SLA_408_st.IVI_VehiclePosition);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_IVI_AccountLoginStatus(&p_IVI_SLA_408_st.IVI_AccountLoginStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_SLA_408_ComIn_VeCAN_ivi_languageSet1(&p_IVI_SLA_408_st.ivi_languageSet1);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_SLA_408 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_User_ID(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint64_t u64IVI_User_ID = 0;
    if (p_IVI_User_ID_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_User_ID_st) + 4, sigbuff, len);

    u64IVI_User_ID = (((uint64_t)p_IVI_User_ID_st.IVI_User_ID_8) << 56) + 
                                (((uint64_t)p_IVI_User_ID_st.IVI_User_ID_7) << 48) + 
                                (((uint64_t)p_IVI_User_ID_st.IVI_User_ID_6) << 40) + 
                                (((uint64_t)p_IVI_User_ID_st.IVI_User_ID_5) << 32) + 
                                (((uint64_t)p_IVI_User_ID_st.IVI_User_ID_4) << 24) + 
                                (((uint64_t)p_IVI_User_ID_st.IVI_User_ID_3) << 16) + 
                                (((uint64_t)p_IVI_User_ID_st.IVI_User_ID_2) << 8) + 
                                ((uint64_t)p_IVI_User_ID_st.IVI_User_ID_1);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_User_ID_ComIn_VeCAN_IVI_User_ID(&u64IVI_User_ID);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_User_ID error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_096(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_096_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_096_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_danceOnOffSet(&p_IVI_096_st.IVI_danceOnOffSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_unlockAnimatSet(&p_IVI_096_st.IVI_unlockAnimatSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_lockAnimatSet(&p_IVI_096_st.IVI_lockAnimatSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_FLWINOpenDegreeRe(&p_IVI_096_st.IVI_FLWINOpenDegreeRe);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_FRWINOpenDegreeRe(&p_IVI_096_st.IVI_FRWINOpenDegreeRe);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_RLWINOpenDegreeRe(&p_IVI_096_st.IVI_RLWINOpenDegreeRe);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_RRWINOpenDegreeRe(&p_IVI_096_st.IVI_RRWINOpenDegreeRe);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_BCMlockSoundSet(&p_IVI_096_st.IVI_BCMlockSoundSet);
    if(p_IVI_096_st.IVI_LockCloseWinSet != Com_SignalInitValue_IVI_LockCloseWinSet_0x096_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_IVI_LockCloseWinSet(&p_IVI_096_st.IVI_LockCloseWinSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_096_ComIn_VeCAN_ivi_FrontDefrostLevelSet(&p_IVI_096_st.ivi_FrontDefrostLevelSet);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_096 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_control(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_control_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_control_st) + 4, sigbuff, len);

    if(p_IVI_control_st.ivi_childLockCtrl != Com_SignalInitValue_ivi_childLockCtrl_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_childLockCtrl(&p_IVI_control_st.ivi_childLockCtrl);
    }
    if(p_IVI_control_st.ivi_centralLockCtrl != Com_SignalInitValue_ivi_centralLockCtrl_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_centralLockCtrl(&p_IVI_control_st.ivi_centralLockCtrl);
    }
    if(p_IVI_control_st.ivi_fuelPortCapOpenCtrl != Com_SignalInitValue_ivi_fuelPortCapOpenCtrl_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_fuelPortCapOpenCtrl(&p_IVI_control_st.ivi_fuelPortCapOpenCtrl);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_lowBeamOnOffCtrl(&p_IVI_control_st.ivi_lowBeamOnOffCtrl);
    if(p_IVI_control_st.ivi_v2vChrgOnOffSet != Com_SignalInitValue_ivi_v2vChrgOnOffSet_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_v2vChrgOnOffSet(&p_IVI_control_st.ivi_v2vChrgOnOffSet);
    }
    if(p_IVI_control_st.ivi_obcDschrgOnOffSet != Com_SignalInitValue_ivi_obcDschrgOnOffSet_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_obcDschrgOnOffSet(&p_IVI_control_st.ivi_obcDschrgOnOffSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_rearFogLampOnOffCtrl(&p_IVI_control_st.ivi_rearFogLampOnOffCtrl);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_roofLampOnOffCtrl(&p_IVI_control_st.ivi_roofLampOnOffCtrl);
    if(p_IVI_control_st.ivi_chrgPortCapOpenCtrl != Com_SignalInitValue_ivi_chrgPortCapOpenCtrl_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_chrgPortCapOpenCtrl(&p_IVI_control_st.ivi_chrgPortCapOpenCtrl);
    }
    if(p_IVI_control_st.ivi_NormalHvOffRequest != Com_SignalInitValue_ivi_NormalHvOffRequest_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_NormalHvOffRequest(&p_IVI_control_st.ivi_NormalHvOffRequest);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_tailgateCtrl(&p_IVI_control_st.ivi_tailgateCtrl);
    if(p_IVI_control_st.ivi_MirrorSw != Com_SignalInitValue_ivi_MirrorSw_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_MirrorSw(&p_IVI_control_st.ivi_MirrorSw);
    }
    if(p_IVI_control_st.ivi_rearDefrostCtrl != Com_SignalInitValue_ivi_rearDefrostCtrl_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_rearDefrostCtrl(&p_IVI_control_st.ivi_rearDefrostCtrl);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_footLightSwitchCtrl(&p_IVI_control_st.ivi_footLightSwitchCtrl);
    if(p_IVI_control_st.ivi_MaxFuelConsumptionSW != Com_SignalInitValue_ivi_MaxFuelConsumptionSW_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_MaxFuelConsumptionSW(&p_IVI_control_st.ivi_MaxFuelConsumptionSW);
    }
    if(p_IVI_control_st.ivi_MaxFuelConsumptionModeSW != Com_SignalInitValue_ivi_MaxFuelConsumptionModeSW_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_MaxFuelConsumptionModeSW(&p_IVI_control_st.ivi_MaxFuelConsumptionModeSW);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_v2vChrgOptCurntSet(&p_IVI_control_st.ivi_v2vChrgOptCurntSet);
    if(p_IVI_control_st.ivi_approachingUnlockCtrl != Com_SignalInitValue_ivi_approachingUnlockCtrl_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_approachingUnlockCtrl(&p_IVI_control_st.ivi_approachingUnlockCtrl);
    }
    if(p_IVI_control_st.ivi_awayLockCtrl != Com_SignalInitValue_ivi_awayLockCtrl_0x075_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_awayLockCtrl(&p_IVI_control_st.ivi_awayLockCtrl);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_wipperMaintModeCtrl(&p_IVI_control_st.ivi_wipperMaintModeCtrl);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_control_ComIn_VeCAN_ivi_modememory(&p_IVI_control_st.ivi_modememory);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_control error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_comfortSet(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_comfortSet_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_comfortSet_st) + 4, sigbuff, len);

    if(p_IVI_comfortSet_st.IVI_NozzleHeatingSw != Com_SignalInitValue_IVI_NozzleHeatingSw_0x095_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_IVI_NozzleHeatingSw(&p_IVI_comfortSet_st.IVI_NozzleHeatingSw);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_ambientLightOnOffSet(&p_IVI_comfortSet_st.ivi_ambientLightOnOffSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_IVI_OneKeyModeSet(&p_IVI_comfortSet_st.IVI_OneKeyModeSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_ambientLightColorSet(&p_IVI_comfortSet_st.ivi_ambientLightColorSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_ambientLightLumiLvSet(&p_IVI_comfortSet_st.ivi_ambientLightLumiLvSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_limitmodeset(&p_IVI_comfortSet_st.ivi_limitmodeset);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_doorTopSwitch(&p_IVI_comfortSet_st.ivi_doorTopSwitch);
    if(p_IVI_comfortSet_st.ivi_rvMirrorAutoTurnDownSet != Com_SignalInitValue_ivi_rvMirrorAutoTurnDownSet_0x095_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_rvMirrorAutoTurnDownSet(&p_IVI_comfortSet_st.ivi_rvMirrorAutoTurnDownSet);
    }
    if(p_IVI_comfortSet_st.ivi_followMeHomeSet != Com_SignalInitValue_ivi_followMeHomeSet_0x095_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_followMeHomeSet(&p_IVI_comfortSet_st.ivi_followMeHomeSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_WinLFCtrlRqst(&p_IVI_comfortSet_st.ivi_WinLFCtrlRqst);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_WinRFCtrlRqst(&p_IVI_comfortSet_st.ivi_WinRFCtrlRqst);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_WinLRCtrlRqst(&p_IVI_comfortSet_st.ivi_WinLRCtrlRqst);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_WinRRCtrlRqst(&p_IVI_comfortSet_st.ivi_WinRRCtrlRqst);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_childLockRLCtrl(&p_IVI_comfortSet_st.ivi_childLockRLCtrl);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_childLockRRCtrl(&p_IVI_comfortSet_st.ivi_childLockRRCtrl);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_ivi_DriveDoorUnlockCtrl(&p_IVI_comfortSet_st.ivi_DriveDoorUnlockCtrl);
    if(p_IVI_comfortSet_st.IVI_AutoDrySet != Com_SignalInitValue_IVI_AutoDrySet_0x095_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_comfortSet_ComIn_VeCAN_IVI_AutoDrySet(&p_IVI_comfortSet_st.IVI_AutoDrySet);
    }

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_comfortSet error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_pwrSet(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_pwrSet_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_pwrSet_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_TripAReset(&p_IVI_pwrSet_st.ivi_TripAReset);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_TripBReset(&p_IVI_pwrSet_st.ivi_TripBReset);
    if(p_IVI_pwrSet_st.ivi_VehicleModeSet != Com_SignalInitValue_ivi_VehicleModeSet_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_VehicleModeSet(&p_IVI_pwrSet_st.ivi_VehicleModeSet);
    }
    if(p_IVI_pwrSet_st.ivi_RegenModeSet != Com_SignalInitValue_ivi_RegenModeSet_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_RegenModeSet(&p_IVI_pwrSet_st.ivi_RegenModeSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_traveModeSet(&p_IVI_pwrSet_st.ivi_traveModeSet);
    if(p_IVI_pwrSet_st.ivi_ChargeControl != Com_SignalInitValue_ivi_ChargeControl_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ChargeControl(&p_IVI_pwrSet_st.ivi_ChargeControl);
    }
    if(p_IVI_pwrSet_st.ivi_ParkingChargeReq != Com_SignalInitValue_ivi_ParkingChargeReq_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ParkingChargeReq(&p_IVI_pwrSet_st.ivi_ParkingChargeReq);
    }
    if(p_IVI_pwrSet_st.ivi_TowModeSet != Com_SignalInitValue_ivi_TowModeSet_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_TowModeSet(&p_IVI_pwrSet_st.ivi_TowModeSet);
    }
    if(p_IVI_pwrSet_st.ivi_maxChrgSocSet != Com_SignalInitValue_ivi_maxChrgSocSet_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_maxChrgSocSet(&p_IVI_pwrSet_st.ivi_maxChrgSocSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_chargeFormSet(&p_IVI_pwrSet_st.ivi_chargeFormSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_remainningMilModeSet(&p_IVI_pwrSet_st.ivi_remainningMilModeSet);
    if(p_IVI_pwrSet_st.ivi_ParkingChargeModeSet != Com_SignalInitValue_ivi_ParkingChargeModeSet_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ParkingChargeModeSet(&p_IVI_pwrSet_st.ivi_ParkingChargeModeSet);
    }
    if(p_IVI_pwrSet_st.ivi_chargeSetValid != Com_SignalInitValue_ivi_chargeSetValid_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_chargeSetValid(&p_IVI_pwrSet_st.ivi_chargeSetValid);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ChargeEndTimeHour(&p_IVI_pwrSet_st.ivi_ChargeEndTimeHour);
    if(p_IVI_pwrSet_st.ivi_ChargeStartTimeHour != Com_SignalInitValue_ivi_ChargeStartTimeHour_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ChargeStartTimeHour(&p_IVI_pwrSet_st.ivi_ChargeStartTimeHour);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ChargeEndTimeMinute(&p_IVI_pwrSet_st.ivi_ChargeEndTimeMinute);
    if(p_IVI_pwrSet_st.ivi_ChargeStartTimeMinute != Com_SignalInitValue_ivi_ChargeStartTimeMinute_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ChargeStartTimeMinute(&p_IVI_pwrSet_st.ivi_ChargeStartTimeMinute);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ResetCurrentTrip(&p_IVI_pwrSet_st.ivi_ResetCurrentTrip);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_IVI_AcFullChargeToWarmSet(&p_IVI_pwrSet_st.IVI_AcFullChargeToWarmSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ChargeEndTimeValid(&p_IVI_pwrSet_st.ivi_ChargeEndTimeValid);
    if(p_IVI_pwrSet_st.ivi_ChargeStartTimeValid != Com_SignalInitValue_ivi_ChargeStartTimeValid_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_ChargeStartTimeValid(&p_IVI_pwrSet_st.ivi_ChargeStartTimeValid);
    }
    if(p_IVI_pwrSet_st.ivi_driveModeSet != Com_SignalInitValue_ivi_driveModeSet_0x0A5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_pwrSet_ComIn_VeCAN_ivi_driveModeSet(&p_IVI_pwrSet_st.ivi_driveModeSet);
    }

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_pwrSet error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_chassisSet1(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_chassisSet1_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_chassisSet1_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_ivi_EmergencyHvOffRequestReserved(&p_IVI_chassisSet1_st.ivi_EmergencyHvOffRequestReserved);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_ivi_ExhibitionModeCtrl(&p_IVI_chassisSet1_st.ivi_ExhibitionModeCtrl);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_ivi_DCDCAutoChargeSet(&p_IVI_chassisSet1_st.ivi_DCDCAutoChargeSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_ivi_OTAModeStatus(&p_IVI_chassisSet1_st.ivi_OTAModeStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_IVI_HVDownRepairMode(&p_IVI_chassisSet1_st.IVI_HVDownRepairMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_IVI_FactoryRestHold(&p_IVI_chassisSet1_st.IVI_FactoryRestHold);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_ivi_chassisSet1_rollingCounter(&p_IVI_chassisSet1_st.ivi_chassisSet1_rollingCounter);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet1_ComIn_VeCAN_ivi_chassisSet1_CheckSum(&p_IVI_chassisSet1_st.ivi_chassisSet1_CheckSum);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_chassisSet1 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_chassisSet_065(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_chassisSet_065_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_chassisSet_065_st) + 4, sigbuff, len);

    if(p_IVI_chassisSet_065_st.ivi_epsModeSet != Com_SignalInitValue_ivi_epsModeSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_epsModeSet(&p_IVI_chassisSet_065_st.ivi_epsModeSet);
    }
    if(p_IVI_chassisSet_065_st.ivi_escOffSw != Com_SignalInitValue_ivi_escOffSw_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_escOffSw(&p_IVI_chassisSet_065_st.ivi_escOffSw);
    }
    if(p_IVI_chassisSet_065_st.ivi_hdcOnOffSet != Com_SignalInitValue_ivi_hdcOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_hdcOnOffSet(&p_IVI_chassisSet_065_st.ivi_hdcOnOffSet);
    }
    if(p_IVI_chassisSet_065_st.ivi_aebOnOffSet != Com_SignalInitValue_ivi_aebOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_aebOnOffSet(&p_IVI_chassisSet_065_st.ivi_aebOnOffSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_iBModeSet(&p_IVI_chassisSet_065_st.ivi_iBModeSet);
    if(p_IVI_chassisSet_065_st.ivi_lcaBsdOnOffSet != Com_SignalInitValue_ivi_lcaBsdOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_lcaBsdOnOffSet(&p_IVI_chassisSet_065_st.ivi_lcaBsdOnOffSet);
    }
    if(p_IVI_chassisSet_065_st.ivi_rctaOnOffSetReserved != Com_SignalInitValue_ivi_rctaOnOffSetReserved_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_rctaOnOffSetReserved(&p_IVI_chassisSet_065_st.ivi_rctaOnOffSetReserved);
    }
    if(p_IVI_chassisSet_065_st.ivi_dowOnOffSet != Com_SignalInitValue_ivi_dowOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_dowOnOffSet(&p_IVI_chassisSet_065_st.ivi_dowOnOffSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_StartRevSOCSet(&p_IVI_chassisSet_065_st.ivi_StartRevSOCSet);
    if(p_IVI_chassisSet_065_st.ivi_hmaOnOffSet != Com_SignalInitValue_ivi_hmaOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_hmaOnOffSet(&p_IVI_chassisSet_065_st.ivi_hmaOnOffSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_speedLimitOnOffSet(&p_IVI_chassisSet_065_st.ivi_speedLimitOnOffSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_ASCHeightModeSelected(&p_IVI_chassisSet_065_st.ivi_ASCHeightModeSelected);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_ASCMoveModeControl(&p_IVI_chassisSet_065_st.ivi_ASCMoveModeControl);
    if(p_IVI_chassisSet_065_st.ivi_laneAssistFuncSet != Com_SignalInitValue_ivi_laneAssistFuncSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_laneAssistFuncSet(&p_IVI_chassisSet_065_st.ivi_laneAssistFuncSet);
    }
    if(p_IVI_chassisSet_065_st.ivi_lasWarningModeSelection != Com_SignalInitValue_ivi_lasWarningModeSelection_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_lasWarningModeSelection(&p_IVI_chassisSet_065_st.ivi_lasWarningModeSelection);
    }
    if(p_IVI_chassisSet_065_st.TrailerModeReq != Com_SignalInitValue_TrailerModeReq_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_TrailerModeReq(&p_IVI_chassisSet_065_st.TrailerModeReq);
    }
    if(p_IVI_chassisSet_065_st.IVI_RCTBOnOffSet != Com_SignalInitValue_IVI_RCTBOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_IVI_RCTBOnOffSet(&p_IVI_chassisSet_065_st.IVI_RCTBOnOffSet);
    }
    if(p_IVI_chassisSet_065_st.IVI_ELKOnOffSet != Com_SignalInitValue_IVI_ELKOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_IVI_ELKOnOffSet(&p_IVI_chassisSet_065_st.IVI_ELKOnOffSet);
    }
    if(p_IVI_chassisSet_065_st.ivi_avhOnOffSet != Com_SignalInitValue_ivi_avhOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_avhOnOffSet(&p_IVI_chassisSet_065_st.ivi_avhOnOffSet);
    }
    if(p_IVI_chassisSet_065_st.ivi_pcwOnOffSet != Com_SignalInitValue_ivi_pcwOnOffSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_pcwOnOffSet(&p_IVI_chassisSet_065_st.ivi_pcwOnOffSet);
    }
    if(p_IVI_chassisSet_065_st.ivi_TJAFuncSet != Com_SignalInitValue_ivi_TJAFuncSet_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_TJAFuncSet(&p_IVI_chassisSet_065_st.ivi_TJAFuncSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_IVI_autododgeOnOffSet(&p_IVI_chassisSet_065_st.IVI_autododgeOnOffSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_trailerModeOnOffSet(&p_IVI_chassisSet_065_st.ivi_trailerModeOnOffSet);
    if(p_IVI_chassisSet_065_st.ivi_esc_epbButtonRelease != Com_SignalInitValue_ivi_esc_epbButtonRelease_0x065_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_ivi_esc_epbButtonRelease(&p_IVI_chassisSet_065_st.ivi_esc_epbButtonRelease);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_chassisSet_065_ComIn_VeCAN_IVI_ApaOnOffReq(&p_IVI_chassisSet_065_st.IVI_ApaOnOffReq);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_chassisSet_065 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_APASet_066(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_APASet_066_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_APASet_066_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_APAFuncSet(&p_IVI_APASet_066_st.IVI_APAFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_RPAFuncSet(&p_IVI_APASet_066_st.IVI_RPAFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_APADrvSpeedSet(&p_IVI_APASet_066_st.IVI_APADrvSpeedSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_AVMViewSet(&p_IVI_APASet_066_st.IVI_AVMViewSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_AVMCarBodyTranspSet(&p_IVI_APASet_066_st.IVI_AVMCarBodyTranspSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_AVMtrigByTurnningSet(&p_IVI_APASet_066_st.IVI_AVMtrigByTurnningSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_AVMTrajectoryDisplaySet(&p_IVI_APASet_066_st.IVI_AVMTrajectoryDisplaySet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_AVMtrigBySensorSet(&p_IVI_APASet_066_st.IVI_AVMtrigBySensorSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_PDCSoundSet(&p_IVI_APASet_066_st.IVI_PDCSoundSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_PDCMuteReq(&p_IVI_APASet_066_st.IVI_PDCMuteReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_laeb_SW(&p_IVI_APASet_066_st.IVI_laeb_SW);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_FrontPDCAlarmSet(&p_IVI_APASet_066_st.IVI_FrontPDCAlarmSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_APAParkInTypeSel(&p_IVI_APASet_066_st.IVI_APAParkInTypeSel);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_066_ComIn_VeCAN_IVI_ParkSceneReconSw(&p_IVI_APASet_066_st.IVI_ParkSceneReconSw);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_APASet_066 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_ACCSet_067(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IVI_ParkPosn1_ID = 0;
    if (p_IVI_ACCSet_067_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_ACCSet_067_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_ICAOnOffSet(&p_IVI_ACCSet_067_st.IVI_ICAOnOffSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_lanechangestaly(&p_IVI_ACCSet_067_st.IVI_lanechangestaly);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_ivi_autolanechangeSet(&p_IVI_ACCSet_067_st.ivi_autolanechangeSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_ivi_RampfollowcarSet(&p_IVI_ACCSet_067_st.ivi_RampfollowcarSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_NCAOnOffSet(&p_IVI_ACCSet_067_st.IVI_NCAOnOffSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_SpeedlimitSet(&p_IVI_ACCSet_067_st.IVI_SpeedlimitSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_voicebroadcastSet(&p_IVI_ACCSet_067_st.IVI_voicebroadcastSet);
    u16IVI_ParkPosn1_ID = (((uint16_t)p_IVI_ACCSet_067_st.IVI_ParkPosn1_ID_H) << 8) + 
                                ((uint16_t)p_IVI_ACCSet_067_st.IVI_ParkPosn1_ID_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_ParkPosn1_ID(&u16IVI_ParkPosn1_ID);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_SpeedProportionSet(&p_IVI_ACCSet_067_st.IVI_SpeedProportionSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_SpeedValueSet(&p_IVI_ACCSet_067_st.IVI_SpeedValueSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_LanechangStyleSet(&p_IVI_ACCSet_067_st.IVI_LanechangStyleSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_TargetSpeedOffsetSet(&p_IVI_ACCSet_067_st.IVI_TargetSpeedOffsetSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_TargetSpeedOffsetValueSet(&p_IVI_ACCSet_067_st.IVI_TargetSpeedOffsetValueSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_NCAFuncSet(&p_IVI_ACCSet_067_st.IVI_NCAFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_ICAFuncSet(&p_IVI_ACCSet_067_st.IVI_ICAFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_ALCFuncSet(&p_IVI_ACCSet_067_st.IVI_ALCFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_067_ComIn_VeCAN_IVI_LaneChangeConfirmSet(&p_IVI_ACCSet_067_st.IVI_LaneChangeConfirmSet);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_ACCSet_067 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_ACCSet_069(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_ACCSet_069_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_ACCSet_069_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_SLAFuncSet(&p_IVI_ACCSet_069_st.IVI_SLAFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_SlaOffsetAdjusttSet(&p_IVI_ACCSet_069_st.IVI_SlaOffsetAdjusttSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_SlaValueAdjustSet(&p_IVI_ACCSet_069_st.IVI_SlaValueAdjustSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_TrafficLightRemFuncSet(&p_IVI_ACCSet_069_st.IVI_TrafficLightRemFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_LaneAssistTypeSet(&p_IVI_ACCSet_069_st.IVI_LaneAssistTypeSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_LasWarnModeSet(&p_IVI_ACCSet_069_st.IVI_LasWarnModeSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_ELKFuncSet(&p_IVI_ACCSet_069_st.IVI_ELKFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_FcwFuncSet(&p_IVI_ACCSet_069_st.IVI_FcwFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_AEBFuncSet(&p_IVI_ACCSet_069_st.IVI_AEBFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_LaebFuncSet(&p_IVI_ACCSet_069_st.IVI_LaebFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_RCWFuncSet(&p_IVI_ACCSet_069_st.IVI_RCWFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_BsdLcaFuncSet(&p_IVI_ACCSet_069_st.IVI_BsdLcaFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_DowFuncSet(&p_IVI_ACCSet_069_st.IVI_DowFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_StartRemFuncSet(&p_IVI_ACCSet_069_st.IVI_StartRemFuncSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_AdsVoiceBroadcastTypeSet(&p_IVI_ACCSet_069_st.IVI_AdsVoiceBroadcastTypeSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ACCSet_069_ComIn_VeCAN_IVI_HmaFuncSet(&p_IVI_ACCSet_069_st.IVI_HmaFuncSet);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_ACCSet_069 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_AVMSet_068(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IVI_AVMRotationAngle_X = 0;
    if (p_IVI_AVMSet_068_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_AVMSet_068_st) + 4, sigbuff, len);

    u16IVI_AVMRotationAngle_X = (((uint16_t)p_IVI_AVMSet_068_st.IVI_AVMRotationAngle_X_H) << 8) + 
                                ((uint16_t)p_IVI_AVMSet_068_st.IVI_AVMRotationAngle_X_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_AVMRotationAngle_X(&u16IVI_AVMRotationAngle_X);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_AVMRotationAngle_Y(&p_IVI_AVMSet_068_st.IVI_AVMRotationAngle_Y);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_APACustomizeSlot(&p_IVI_AVMSet_068_st.IVI_APACustomizeSlot);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_RpaApaSwitch(&p_IVI_AVMSet_068_st.IVI_RpaApaSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_APAFuncReq(&p_IVI_AVMSet_068_st.IVI_APAFuncReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_ParkDirSel(&p_IVI_AVMSet_068_st.IVI_ParkDirSel);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_AVMViewSelect(&p_IVI_AVMSet_068_st.IVI_AVMViewSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_068_ComIn_VeCAN_IVI_ParkSpcGrdLockCfim(&p_IVI_AVMSet_068_st.IVI_ParkSpcGrdLockCfim);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_AVMSet_068 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_APASet_06A(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint32_t u32IVI_APAChosedSlotID = 0;
    if (p_IVI_APASet_06A_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_APASet_06A_st) + 4, sigbuff, len);

    u32IVI_APAChosedSlotID = (((uint32_t)p_IVI_APASet_06A_st.IVI_APAChosedSlotID_H) << 24) + 
                                (((uint32_t)p_IVI_APASet_06A_st.IVI_APAChosedSlotID_MH) << 16) + 
                                (((uint32_t)p_IVI_APASet_06A_st.IVI_APAChosedSlotID_ML) << 8) + 
                                ((uint32_t)p_IVI_APASet_06A_st.IVI_APAChosedSlotID_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_06A_ComIn_VeCAN_IVI_APAChosedSlotID(&u32IVI_APAChosedSlotID);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_APASet_06A error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_APASet_06B(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IVI_APACustomizedSlotCPoint_x = 0;
    uint16_t u16IVI_APACustomizedSlotCPoint_y = 0;
    uint16_t u16IVI_APACustomizedSlotAngle = 0;
    if (p_IVI_APASet_06B_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_APASet_06B_st) + 4, sigbuff, len);

    u16IVI_APACustomizedSlotCPoint_x = (((uint16_t)p_IVI_APASet_06B_st.IVI_APACustomizedSlotCPoint_x_H) << 8) + 
                                ((uint16_t)p_IVI_APASet_06B_st.IVI_APACustomizedSlotCPoint_x_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_06B_ComIn_VeCAN_IVI_APACustomizedSlotCPoint_x(&u16IVI_APACustomizedSlotCPoint_x);
    u16IVI_APACustomizedSlotCPoint_y = (((uint16_t)p_IVI_APASet_06B_st.IVI_APACustomizedSlotCPoint_y_H) << 8) + 
                                ((uint16_t)p_IVI_APASet_06B_st.IVI_APACustomizedSlotCPoint_y_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_06B_ComIn_VeCAN_IVI_APACustomizedSlotCPoint_y(&u16IVI_APACustomizedSlotCPoint_y);
    u16IVI_APACustomizedSlotAngle = (((uint16_t)p_IVI_APASet_06B_st.IVI_APACustomizedSlotAngle_H) << 8) + 
                                ((uint16_t)p_IVI_APASet_06B_st.IVI_APACustomizedSlotAngle_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_APASet_06B_ComIn_VeCAN_IVI_APACustomizedSlotAngle(&u16IVI_APACustomizedSlotAngle);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_APASet_06B error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_dvrSet(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_dvrSet_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_dvrSet_st) + 4, sigbuff, len);

    if(p_IVI_dvrSet_st.IVI_SterringWheelHeatSw != Com_SignalInitValue_IVI_SterringWheelHeatSw_0x105_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_dvrSet_ComIn_VeCAN_IVI_SterringWheelHeatSw(&p_IVI_dvrSet_st.IVI_SterringWheelHeatSw);
    }

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_dvrSet error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_dsmmSet(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_dsmmSet_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_dsmmSet_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_drSeatRouteSet(&p_IVI_dsmmSet_st.IVI_drSeatRouteSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_drSeatbackrestSet(&p_IVI_dsmmSet_st.IVI_drSeatbackrestSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_drSeatCushionSet(&p_IVI_dsmmSet_st.IVI_drSeatCushionSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_drSeatCushionAngleSet(&p_IVI_dsmmSet_st.IVI_drSeatCushionAngleSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_LmirrorUDSet(&p_IVI_dsmmSet_st.IVI_LmirrorUDSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_LmirrorLRSet(&p_IVI_dsmmSet_st.IVI_LmirrorLRSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_RmirrorUDSet(&p_IVI_dsmmSet_st.IVI_RmirrorUDSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_RmirrorLRSet(&p_IVI_dsmmSet_st.IVI_RmirrorLRSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet_ComIn_VeCAN_IVI_DSMChargeCtrl(&p_IVI_dsmmSet_st.IVI_DSMChargeCtrl);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_dsmmSet error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_dsmmSet2(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_dsmmSet2_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_dsmmSet2_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet2_ComIn_VeCAN_IVI_PassSeatRouteSet(&p_IVI_dsmmSet2_st.IVI_PassSeatRouteSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet2_ComIn_VeCAN_IVI_PassSeatbackrestSet(&p_IVI_dsmmSet2_st.IVI_PassSeatbackrestSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet2_ComIn_VeCAN_IVI_PassSeatCushionSet(&p_IVI_dsmmSet2_st.IVI_PassSeatCushionSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet2_ComIn_VeCAN_IVI_PassSeatCushionAngleSet(&p_IVI_dsmmSet2_st.IVI_PassSeatCushionAngleSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_dsmmSet2_ComIn_VeCAN_IVI_PSMChargeCtrl(&p_IVI_dsmmSet2_st.IVI_PSMChargeCtrl);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_dsmmSet2 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_infoSet(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_infoSet_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_infoSet_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_darkIllumiLevelSetReserved(&p_IVI_infoSet_st.ivi_darkIllumiLevelSetReserved);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_TripSwitchReserved(&p_IVI_infoSet_st.ivi_TripSwitchReserved);
    if(p_IVI_infoSet_st.IVI_RearseatbeltVoiceWarningSet != Com_SignalInitValue_IVI_RearseatbeltVoiceWarningSet_0x0C5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_IVI_RearseatbeltVoiceWarningSet(&p_IVI_infoSet_st.IVI_RearseatbeltVoiceWarningSet);
    }
    if(p_IVI_infoSet_st.ivi_hudOnOffSet != Com_SignalInitValue_ivi_hudOnOffSet_0x0C5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_hudOnOffSet(&p_IVI_infoSet_st.ivi_hudOnOffSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_IVI_PEBSVoiceWarningSet(&p_IVI_infoSet_st.IVI_PEBSVoiceWarningSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_NaviSwitchReserved(&p_IVI_infoSet_st.ivi_NaviSwitchReserved);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_themeSetReserved(&p_IVI_infoSet_st.ivi_themeSetReserved);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_wcmLeftOnOffSet(&p_IVI_infoSet_st.ivi_wcmLeftOnOffSet);
    if(p_IVI_infoSet_st.ivi_pdcOnOffSet != Com_SignalInitValue_ivi_pdcOnOffSet_0x0C5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_pdcOnOffSet(&p_IVI_infoSet_st.ivi_pdcOnOffSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_ICthemegangedSetReserved(&p_IVI_infoSet_st.ivi_ICthemegangedSetReserved);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_IVI_FactoryResetCommand(&p_IVI_infoSet_st.IVI_FactoryResetCommand);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_ICIllumiLevelSet(&p_IVI_infoSet_st.ivi_ICIllumiLevelSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_IVI_laeb_SW(&p_IVI_infoSet_st.IVI_laeb_SW);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_vspOnOffSet(&p_IVI_infoSet_st.ivi_vspOnOffSet);
    if(p_IVI_infoSet_st.ivi_vsp_SoundConfigure != Com_SignalInitValue_ivi_vsp_SoundConfigure_0x0C5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_vsp_SoundConfigure(&p_IVI_infoSet_st.ivi_vsp_SoundConfigure);
    }
    if(p_IVI_infoSet_st.IVI_unlocksoundSet != Com_SignalInitValue_IVI_unlocksoundSet_0x0C5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_IVI_unlocksoundSet(&p_IVI_infoSet_st.IVI_unlocksoundSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_IVI_locksoundSet(&p_IVI_infoSet_st.IVI_locksoundSet);
    if(p_IVI_infoSet_st.IVI_ISAOnOffSet != Com_SignalInitValue_IVI_ISAOnOffSet_0x0C5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_IVI_ISAOnOffSet(&p_IVI_infoSet_st.IVI_ISAOnOffSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet_ComIn_VeCAN_ivi_IllumiLevelSetReserved(&p_IVI_infoSet_st.ivi_IllumiLevelSetReserved);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_infoSet error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_infoSet2(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_infoSet2_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_infoSet2_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet2_ComIn_VeCAN_IVI_VehIntMntnMile(&p_IVI_infoSet2_st.IVI_VehIntMntnMile);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet2_ComIn_VeCAN_IVI_VehMntnMileClea(&p_IVI_infoSet2_st.IVI_VehMntnMileClea);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet2_ComIn_VeCAN_IVI_OilMntnMileClea(&p_IVI_infoSet2_st.IVI_OilMntnMileClea);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet2_ComIn_VeCAN_IVI_OilFilMntnMileClea(&p_IVI_infoSet2_st.IVI_OilFilMntnMileClea);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet2_ComIn_VeCAN_IVI_AirFilMntnMileClea(&p_IVI_infoSet2_st.IVI_AirFilMntnMileClea);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_infoSet2_ComIn_VeCAN_IVI_VehMntnTimeClea(&p_IVI_infoSet2_st.IVI_VehMntnTimeClea);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_infoSet2 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_AVMSet_3D2(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_AVMXCoordinate = 0;
    uint16_t u16ivi_AVMYCoordinate = 0;
    if (p_IVI_AVMSet_3D2_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_AVMSet_3D2_st) + 4, sigbuff, len);

    u16ivi_AVMXCoordinate = (((uint16_t)p_IVI_AVMSet_3D2_st.ivi_AVMXCoordinate_H) << 8) + 
                                ((uint16_t)p_IVI_AVMSet_3D2_st.ivi_AVMXCoordinate_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_ivi_AVMXCoordinate(&u16ivi_AVMXCoordinate);
    u16ivi_AVMYCoordinate = (((uint16_t)p_IVI_AVMSet_3D2_st.ivi_AVMYCoordinate_H) << 8) + 
                                ((uint16_t)p_IVI_AVMSet_3D2_st.ivi_AVMYCoordinate_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_ivi_AVMYCoordinate(&u16ivi_AVMYCoordinate);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_ivi_AVMCoTouchMotion(&p_IVI_AVMSet_3D2_st.ivi_AVMCoTouchMotion);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_ivi_IVIthemeSet1(&p_IVI_AVMSet_3D2_st.ivi_IVIthemeSet1);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_IVI_TakeINVideoPosReq(&p_IVI_AVMSet_3D2_st.IVI_TakeINVideoPosReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_IVI_TakePhotoFaultReason(&p_IVI_AVMSet_3D2_st.IVI_TakePhotoFaultReason);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_IVI_AlarmListrequest(&p_IVI_AVMSet_3D2_st.IVI_AlarmListrequest);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_IVI_driveModeSts(&p_IVI_AVMSet_3D2_st.IVI_driveModeSts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_AVMSet_3D2_ComIn_VeCAN_IVI_PetFaultReason(&p_IVI_AVMSet_3D2_st.IVI_PetFaultReason);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_AVMSet_3D2 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_scuSet(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_scuSet_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_scuSet_st) + 4, sigbuff, len);

    if(p_IVI_scuSet_st.ivi_easyEntrySet != Com_SignalInitValue_ivi_easyEntrySet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_easyEntrySet(&p_IVI_scuSet_st.ivi_easyEntrySet);
    }
    if(p_IVI_scuSet_st.ivi_drSeatHeatLevelSet != Com_SignalInitValue_ivi_drSeatHeatLevelSet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_drSeatHeatLevelSet(&p_IVI_scuSet_st.ivi_drSeatHeatLevelSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_drSeatVentLevelSet(&p_IVI_scuSet_st.ivi_drSeatVentLevelSet);
    if(p_IVI_scuSet_st.ivi_passSeatHeatLevelSet != Com_SignalInitValue_ivi_passSeatHeatLevelSet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_passSeatHeatLevelSet(&p_IVI_scuSet_st.ivi_passSeatHeatLevelSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_passSeatVentLevelSet(&p_IVI_scuSet_st.ivi_passSeatVentLevelSet);
    if(p_IVI_scuSet_st.ivi_drSeatMassLevelSet != Com_SignalInitValue_ivi_drSeatMassLevelSet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_drSeatMassLevelSet(&p_IVI_scuSet_st.ivi_drSeatMassLevelSet);
    }
    if(p_IVI_scuSet_st.ivi_passSeatMassLevelSet != Com_SignalInitValue_ivi_passSeatMassLevelSet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_passSeatMassLevelSet(&p_IVI_scuSet_st.ivi_passSeatMassLevelSet);
    }
    if(p_IVI_scuSet_st.ivi_MirrorAutoFoldUnfoldSet != Com_SignalInitValue_ivi_MirrorAutoFoldUnfoldSet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_MirrorAutoFoldUnfoldSet(&p_IVI_scuSet_st.ivi_MirrorAutoFoldUnfoldSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_IVI_RLSeatHeatLevelSet(&p_IVI_scuSet_st.IVI_RLSeatHeatLevelSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_dsmSetMemoryReqReserved(&p_IVI_scuSet_st.ivi_dsmSetMemoryReqReserved);
    if(p_IVI_scuSet_st.ivi_DrMassgIntenSet != Com_SignalInitValue_ivi_DrMassgIntenSet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_DrMassgIntenSet(&p_IVI_scuSet_st.ivi_DrMassgIntenSet);
    }
    if(p_IVI_scuSet_st.ivi_PsgMassgIntenSet != Com_SignalInitValue_ivi_PsgMassgIntenSet_0x0F5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_ivi_PsgMassgIntenSet(&p_IVI_scuSet_st.ivi_PsgMassgIntenSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_IVI_DSMMemoryReq(&p_IVI_scuSet_st.IVI_DSMMemoryReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_scuSet_ComIn_VeCAN_IVI_RRSeatHeatLevelSet(&p_IVI_scuSet_st.IVI_RRSeatHeatLevelSet);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_scuSet error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent1Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent1MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent1MotorOriginalLocation = 0;
    if (p_IVI_vent1Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent1Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1LocationActuator(&p_IVI_vent1Ctrl_st.ivi_ElVent1LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1ProgrammingDataSave(&p_IVI_vent1Ctrl_st.ivi_ElVent1ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1ObstructionCheck(&p_IVI_vent1Ctrl_st.ivi_ElVent1ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1MarkClear(&p_IVI_vent1Ctrl_st.ivi_ElVent1MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1CoilElectrify(&p_IVI_vent1Ctrl_st.ivi_ElVent1CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1LocationSelect(&p_IVI_vent1Ctrl_st.ivi_ElVent1LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1SpeedMode(&p_IVI_vent1Ctrl_st.ivi_ElVent1SpeedMode);
    u16ivi_ElVent1MotorTargetLocation = (((uint16_t)p_IVI_vent1Ctrl_st.ivi_ElVent1MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent1Ctrl_st.ivi_ElVent1MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1MotorTargetLocation(&u16ivi_ElVent1MotorTargetLocation);
    u16ivi_ElVent1MotorOriginalLocation = (((uint16_t)p_IVI_vent1Ctrl_st.ivi_ElVent1MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent1Ctrl_st.ivi_ElVent1MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1MotorOriginalLocation(&u16ivi_ElVent1MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1EmergencyStopSwitch(&p_IVI_vent1Ctrl_st.ivi_ElVent1EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1EmergencyStopLocation(&p_IVI_vent1Ctrl_st.ivi_ElVent1EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1RotationMode(&p_IVI_vent1Ctrl_st.ivi_ElVent1RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent1Ctrl_ComIn_VeCAN_ivi_ElVent1StopMode(&p_IVI_vent1Ctrl_st.ivi_ElVent1StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent1Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent2Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent2MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent2MotorOriginalLocation = 0;
    if (p_IVI_vent2Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent2Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2LocationActuator(&p_IVI_vent2Ctrl_st.ivi_ElVent2LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2ProgrammingDataSave(&p_IVI_vent2Ctrl_st.ivi_ElVent2ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2ObstructionCheck(&p_IVI_vent2Ctrl_st.ivi_ElVent2ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2MarkClear(&p_IVI_vent2Ctrl_st.ivi_ElVent2MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2CoilElectrify(&p_IVI_vent2Ctrl_st.ivi_ElVent2CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2LocationSelect(&p_IVI_vent2Ctrl_st.ivi_ElVent2LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2SpeedMode(&p_IVI_vent2Ctrl_st.ivi_ElVent2SpeedMode);
    u16ivi_ElVent2MotorTargetLocation = (((uint16_t)p_IVI_vent2Ctrl_st.ivi_ElVent2MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent2Ctrl_st.ivi_ElVent2MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2MotorTargetLocation(&u16ivi_ElVent2MotorTargetLocation);
    u16ivi_ElVent2MotorOriginalLocation = (((uint16_t)p_IVI_vent2Ctrl_st.ivi_ElVent2MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent2Ctrl_st.ivi_ElVent2MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2MotorOriginalLocation(&u16ivi_ElVent2MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2EmergencyStopSwitch(&p_IVI_vent2Ctrl_st.ivi_ElVent2EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2EmergencyStopLocation(&p_IVI_vent2Ctrl_st.ivi_ElVent2EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2RotationMode(&p_IVI_vent2Ctrl_st.ivi_ElVent2RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent2Ctrl_ComIn_VeCAN_ivi_ElVent2StopMode(&p_IVI_vent2Ctrl_st.ivi_ElVent2StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent2Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent3Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent3MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent3MotorOriginalLocation = 0;
    if (p_IVI_vent3Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent3Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3LocationActuator(&p_IVI_vent3Ctrl_st.ivi_ElVent3LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3ProgrammingDataSave(&p_IVI_vent3Ctrl_st.ivi_ElVent3ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3ObstructionCheck(&p_IVI_vent3Ctrl_st.ivi_ElVent3ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3MarkClear(&p_IVI_vent3Ctrl_st.ivi_ElVent3MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3CoilElectrify(&p_IVI_vent3Ctrl_st.ivi_ElVent3CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3LocationSelect(&p_IVI_vent3Ctrl_st.ivi_ElVent3LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3SpeedMode(&p_IVI_vent3Ctrl_st.ivi_ElVent3SpeedMode);
    u16ivi_ElVent3MotorTargetLocation = (((uint16_t)p_IVI_vent3Ctrl_st.ivi_ElVent3MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent3Ctrl_st.ivi_ElVent3MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3MotorTargetLocation(&u16ivi_ElVent3MotorTargetLocation);
    u16ivi_ElVent3MotorOriginalLocation = (((uint16_t)p_IVI_vent3Ctrl_st.ivi_ElVent3MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent3Ctrl_st.ivi_ElVent3MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3MotorOriginalLocation(&u16ivi_ElVent3MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3EmergencyStopSwitch(&p_IVI_vent3Ctrl_st.ivi_ElVent3EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3EmergencyStopLocation(&p_IVI_vent3Ctrl_st.ivi_ElVent3EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3RotationMode(&p_IVI_vent3Ctrl_st.ivi_ElVent3RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent3Ctrl_ComIn_VeCAN_ivi_ElVent3StopMode(&p_IVI_vent3Ctrl_st.ivi_ElVent3StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent3Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent4Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent4MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent4MotorOriginalLocation = 0;
    if (p_IVI_vent4Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent4Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4LocationActuator(&p_IVI_vent4Ctrl_st.ivi_ElVent4LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4ProgrammingDataSave(&p_IVI_vent4Ctrl_st.ivi_ElVent4ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4ObstructionCheck(&p_IVI_vent4Ctrl_st.ivi_ElVent4ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4MarkClear(&p_IVI_vent4Ctrl_st.ivi_ElVent4MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4CoilElectrify(&p_IVI_vent4Ctrl_st.ivi_ElVent4CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4LocationSelect(&p_IVI_vent4Ctrl_st.ivi_ElVent4LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4SpeedMode(&p_IVI_vent4Ctrl_st.ivi_ElVent4SpeedMode);
    u16ivi_ElVent4MotorTargetLocation = (((uint16_t)p_IVI_vent4Ctrl_st.ivi_ElVent4MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent4Ctrl_st.ivi_ElVent4MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4MotorTargetLocation(&u16ivi_ElVent4MotorTargetLocation);
    u16ivi_ElVent4MotorOriginalLocation = (((uint16_t)p_IVI_vent4Ctrl_st.ivi_ElVent4MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent4Ctrl_st.ivi_ElVent4MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4MotorOriginalLocation(&u16ivi_ElVent4MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4EmergencyStopSwitch(&p_IVI_vent4Ctrl_st.ivi_ElVent4EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4EmergencyStopLocation(&p_IVI_vent4Ctrl_st.ivi_ElVent4EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4RotationMode(&p_IVI_vent4Ctrl_st.ivi_ElVent4RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent4Ctrl_ComIn_VeCAN_ivi_ElVent4StopMode(&p_IVI_vent4Ctrl_st.ivi_ElVent4StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent4Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent5Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent5MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent5MotorOriginalLocation = 0;
    if (p_IVI_vent5Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent5Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5LocationActuator(&p_IVI_vent5Ctrl_st.ivi_ElVent5LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5ProgrammingDataSave(&p_IVI_vent5Ctrl_st.ivi_ElVent5ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5ObstructionCheck(&p_IVI_vent5Ctrl_st.ivi_ElVent5ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5MarkClear(&p_IVI_vent5Ctrl_st.ivi_ElVent5MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5CoilElectrify(&p_IVI_vent5Ctrl_st.ivi_ElVent5CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5LocationSelect(&p_IVI_vent5Ctrl_st.ivi_ElVent5LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5SpeedMode(&p_IVI_vent5Ctrl_st.ivi_ElVent5SpeedMode);
    u16ivi_ElVent5MotorTargetLocation = (((uint16_t)p_IVI_vent5Ctrl_st.ivi_ElVent5MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent5Ctrl_st.ivi_ElVent5MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5MotorTargetLocation(&u16ivi_ElVent5MotorTargetLocation);
    u16ivi_ElVent5MotorOriginalLocation = (((uint16_t)p_IVI_vent5Ctrl_st.ivi_ElVent5MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent5Ctrl_st.ivi_ElVent5MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5MotorOriginalLocation(&u16ivi_ElVent5MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5EmergencyStopSwitch(&p_IVI_vent5Ctrl_st.ivi_ElVent5EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5EmergencyStopLocation(&p_IVI_vent5Ctrl_st.ivi_ElVent5EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5RotationMode(&p_IVI_vent5Ctrl_st.ivi_ElVent5RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent5Ctrl_ComIn_VeCAN_ivi_ElVent5StopMode(&p_IVI_vent5Ctrl_st.ivi_ElVent5StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent5Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent6Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent6MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent6MotorOriginalLocation = 0;
    if (p_IVI_vent6Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent6Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6LocationActuator(&p_IVI_vent6Ctrl_st.ivi_ElVent6LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6ProgrammingDataSave(&p_IVI_vent6Ctrl_st.ivi_ElVent6ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6ObstructionCheck(&p_IVI_vent6Ctrl_st.ivi_ElVent6ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6MarkClear(&p_IVI_vent6Ctrl_st.ivi_ElVent6MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6CoilElectrify(&p_IVI_vent6Ctrl_st.ivi_ElVent6CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6LocationSelect(&p_IVI_vent6Ctrl_st.ivi_ElVent6LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6SpeedMode(&p_IVI_vent6Ctrl_st.ivi_ElVent6SpeedMode);
    u16ivi_ElVent6MotorTargetLocation = (((uint16_t)p_IVI_vent6Ctrl_st.ivi_ElVent6MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent6Ctrl_st.ivi_ElVent6MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6MotorTargetLocation(&u16ivi_ElVent6MotorTargetLocation);
    u16ivi_ElVent6MotorOriginalLocation = (((uint16_t)p_IVI_vent6Ctrl_st.ivi_ElVent6MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent6Ctrl_st.ivi_ElVent6MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6MotorOriginalLocation(&u16ivi_ElVent6MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6EmergencyStopSwitch(&p_IVI_vent6Ctrl_st.ivi_ElVent6EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6EmergencyStopLocation(&p_IVI_vent6Ctrl_st.ivi_ElVent6EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6RotationMode(&p_IVI_vent6Ctrl_st.ivi_ElVent6RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent6Ctrl_ComIn_VeCAN_ivi_ElVent6StopMode(&p_IVI_vent6Ctrl_st.ivi_ElVent6StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent6Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent7Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent7MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent7MotorOriginalLocation = 0;
    if (p_IVI_vent7Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent7Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7LocationActuator(&p_IVI_vent7Ctrl_st.ivi_ElVent7LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7ProgrammingDataSave(&p_IVI_vent7Ctrl_st.ivi_ElVent7ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7ObstructionCheck(&p_IVI_vent7Ctrl_st.ivi_ElVent7ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7MarkClear(&p_IVI_vent7Ctrl_st.ivi_ElVent7MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7CoilElectrify(&p_IVI_vent7Ctrl_st.ivi_ElVent7CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7LocationSelect(&p_IVI_vent7Ctrl_st.ivi_ElVent7LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7SpeedMode(&p_IVI_vent7Ctrl_st.ivi_ElVent7SpeedMode);
    u16ivi_ElVent7MotorTargetLocation = (((uint16_t)p_IVI_vent7Ctrl_st.ivi_ElVent7MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent7Ctrl_st.ivi_ElVent7MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7MotorTargetLocation(&u16ivi_ElVent7MotorTargetLocation);
    u16ivi_ElVent7MotorOriginalLocation = (((uint16_t)p_IVI_vent7Ctrl_st.ivi_ElVent7MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent7Ctrl_st.ivi_ElVent7MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7MotorOriginalLocation(&u16ivi_ElVent7MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7EmergencyStopSwitch(&p_IVI_vent7Ctrl_st.ivi_ElVent7EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7EmergencyStopLocation(&p_IVI_vent7Ctrl_st.ivi_ElVent7EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7RotationMode(&p_IVI_vent7Ctrl_st.ivi_ElVent7RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent7Ctrl_ComIn_VeCAN_ivi_ElVent7StopMode(&p_IVI_vent7Ctrl_st.ivi_ElVent7StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent7Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_vent8Ctrl(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_ElVent8MotorTargetLocation = 0;
    uint16_t u16ivi_ElVent8MotorOriginalLocation = 0;
    if (p_IVI_vent8Ctrl_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_vent8Ctrl_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8LocationActuator(&p_IVI_vent8Ctrl_st.ivi_ElVent8LocationActuator);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8ProgrammingDataSave(&p_IVI_vent8Ctrl_st.ivi_ElVent8ProgrammingDataSave);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8ObstructionCheck(&p_IVI_vent8Ctrl_st.ivi_ElVent8ObstructionCheck);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8MarkClear(&p_IVI_vent8Ctrl_st.ivi_ElVent8MarkClear);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8CoilElectrify(&p_IVI_vent8Ctrl_st.ivi_ElVent8CoilElectrify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8LocationSelect(&p_IVI_vent8Ctrl_st.ivi_ElVent8LocationSelect);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8SpeedMode(&p_IVI_vent8Ctrl_st.ivi_ElVent8SpeedMode);
    u16ivi_ElVent8MotorTargetLocation = (((uint16_t)p_IVI_vent8Ctrl_st.ivi_ElVent8MotorTargetLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent8Ctrl_st.ivi_ElVent8MotorTargetLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8MotorTargetLocation(&u16ivi_ElVent8MotorTargetLocation);
    u16ivi_ElVent8MotorOriginalLocation = (((uint16_t)p_IVI_vent8Ctrl_st.ivi_ElVent8MotorOriginalLocation_H) << 8) + 
                                ((uint16_t)p_IVI_vent8Ctrl_st.ivi_ElVent8MotorOriginalLocation_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8MotorOriginalLocation(&u16ivi_ElVent8MotorOriginalLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8EmergencyStopSwitch(&p_IVI_vent8Ctrl_st.ivi_ElVent8EmergencyStopSwitch);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8EmergencyStopLocation(&p_IVI_vent8Ctrl_st.ivi_ElVent8EmergencyStopLocation);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8RotationMode(&p_IVI_vent8Ctrl_st.ivi_ElVent8RotationMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_vent8Ctrl_ComIn_VeCAN_ivi_ElVent8StopMode(&p_IVI_vent8Ctrl_st.ivi_ElVent8StopMode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_vent8Ctrl error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_NaviChrgSt_33D(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IVI_DestEstimSOC = 0;
    uint16_t u16IVI_DestEstimTi = 0;
    uint16_t u16IVI_DestEstimMilg = 0;
    if (p_IVI_NaviChrgSt_33D_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_NaviChrgSt_33D_st) + 4, sigbuff, len);

    u16IVI_DestEstimSOC = (((uint16_t)p_IVI_NaviChrgSt_33D_st.IVI_DestEstimSOC_H) << 8) + 
                                ((uint16_t)p_IVI_NaviChrgSt_33D_st.IVI_DestEstimSOC_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33D_ComIn_VeCAN_IVI_DestEstimSOC(&u16IVI_DestEstimSOC);
    u16IVI_DestEstimTi = (((uint16_t)p_IVI_NaviChrgSt_33D_st.IVI_DestEstimTi_H) << 8) + 
                                ((uint16_t)p_IVI_NaviChrgSt_33D_st.IVI_DestEstimTi_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33D_ComIn_VeCAN_IVI_DestEstimTi(&u16IVI_DestEstimTi);
    u16IVI_DestEstimMilg = (((uint16_t)p_IVI_NaviChrgSt_33D_st.IVI_DestEstimMilg_H) << 8) + 
                                ((uint16_t)p_IVI_NaviChrgSt_33D_st.IVI_DestEstimMilg_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33D_ComIn_VeCAN_IVI_DestEstimMilg(&u16IVI_DestEstimMilg);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_NaviChrgSt_33D error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_NaviChrgSt_33E(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IVI_NextChrgStationPileRatedPwr = 0;
    uint16_t u16IVI_NextChrgStationPileRatedCurrent = 0;
    uint16_t u16IVI_NextChrgStationPileMaxU = 0;
    uint16_t u16IVI_NextChrgStationPileMinU = 0;
    if (p_IVI_NaviChrgSt_33E_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_NaviChrgSt_33E_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33E_ComIn_VeCAN_IVI_NextChrgStationTyp(&p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationTyp);
    u16IVI_NextChrgStationPileRatedPwr = (((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileRatedPwr_H) << 8) + 
                                ((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileRatedPwr_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33E_ComIn_VeCAN_IVI_NextChrgStationPileRatedPwr(&u16IVI_NextChrgStationPileRatedPwr);
    u16IVI_NextChrgStationPileRatedCurrent = (((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileRatedCurrent_H) << 8) + 
                                ((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileRatedCurrent_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33E_ComIn_VeCAN_IVI_NextChrgStationPileRatedCurrent(&u16IVI_NextChrgStationPileRatedCurrent);
    u16IVI_NextChrgStationPileMaxU = (((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileMaxU_H) << 8) + 
                                ((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileMaxU_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33E_ComIn_VeCAN_IVI_NextChrgStationPileMaxU(&u16IVI_NextChrgStationPileMaxU);
    u16IVI_NextChrgStationPileMinU = (((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileMinU_H) << 8) + 
                                ((uint16_t)p_IVI_NaviChrgSt_33E_st.IVI_NextChrgStationPileMinU_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33E_ComIn_VeCAN_IVI_NextChrgStationPileMinU(&u16IVI_NextChrgStationPileMinU);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33E_ComIn_VeCAN_IVI_OutChrgStationOpenHour(&p_IVI_NaviChrgSt_33E_st.IVI_OutChrgStationOpenHour);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviChrgSt_33E_ComIn_VeCAN_IVI_NavigChrgPostReq(&p_IVI_NaviChrgSt_33E_st.IVI_NavigChrgPostReq);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_NaviChrgSt_33E error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_engineOFF(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ic_engOffTime = 0;
    if (p_IC_engineOFF_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_engineOFF_st) + 4, sigbuff, len);

    u16ic_engOffTime = (((uint16_t)p_IC_engineOFF_st.ic_engOffTime_H) << 8) + 
                                ((uint16_t)p_IC_engineOFF_st.ic_engOffTime_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_engineOFF_ComIn_VeCAN_ic_engOffTime(&u16ic_engOffTime);
    bResult |= Rte_Write_rpSR_CANMSG_IC_engineOFF_ComIn_VeCAN_ic_engOffTimeValid(&p_IC_engineOFF_st.ic_engOffTimeValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_engineOFF_ComIn_VeCAN_IC_songFaultNum(&p_IC_engineOFF_st.IC_songFaultNum);
    bResult |= Rte_Write_rpSR_CANMSG_IC_engineOFF_ComIn_VeCAN_IC_songWarningSts(&p_IC_engineOFF_st.IC_songWarningSts);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_engineOFF error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_faultSum(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IC_faultSum_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_faultSum_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IC_faultSum_ComIn_VeCAN_IC_LowBatteryvoltage(&p_IC_faultSum_st.IC_LowBatteryvoltage);
    bResult |= Rte_Write_rpSR_CANMSG_IC_faultSum_ComIn_VeCAN_IC_engCoolantTempAlarm(&p_IC_faultSum_st.IC_engCoolantTempAlarm);
    bResult |= Rte_Write_rpSR_CANMSG_IC_faultSum_ComIn_VeCAN_IC_lowfuleAlarm(&p_IC_faultSum_st.IC_lowfuleAlarm);
    bResult |= Rte_Write_rpSR_CANMSG_IC_faultSum_ComIn_VeCAN_IC_lowbrakefluidlevel(&p_IC_faultSum_st.IC_lowbrakefluidlevel);
    bResult |= Rte_Write_rpSR_CANMSG_IC_faultSum_ComIn_VeCAN_IC_lowoilpressure(&p_IC_faultSum_st.IC_lowoilpressure);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_faultSum error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_infoSet(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IC_infoSet_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_infoSet_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IC_infoSet_ComIn_VeCAN_ic_hudScreenTransition(&p_IC_infoSet_st.ic_hudScreenTransition);
    bResult |= Rte_Write_rpSR_CANMSG_IC_infoSet_ComIn_VeCAN_ic_hudHeightSet(&p_IC_infoSet_st.ic_hudHeightSet);
    if(p_IC_infoSet_st.ic_hudillumiLvSet != Com_SignalInitValue_ic_hudillumiLvSet_0x3F2_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IC_infoSet_ComIn_VeCAN_ic_hudillumiLvSet(&p_IC_infoSet_st.ic_hudillumiLvSet);
    }

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_infoSet error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_3F8(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IC_CLTCFuleRemainingMileage = 0;
    uint16_t u16IC_CLTCRemainingMileage = 0;
    if (p_IC_3F8_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_3F8_st) + 4, sigbuff, len);

    if(p_IC_3F8_st.IVI_PassAirbSuppressionStSet != Com_SignalInitValue_IVI_PassAirbSuppressionStSet_0x3F8_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IVI_PassAirbSuppressionStSet(&p_IC_3F8_st.IVI_PassAirbSuppressionStSet);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_driverSeatBeltStatus(&p_IC_3F8_st.IC_driverSeatBeltStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_driverSeatBeltStatusValid(&p_IC_3F8_st.IC_driverSeatBeltStatusValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_passengerSeatBeltStatus(&p_IC_3F8_st.IC_passengerSeatBeltStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_passengerSeatBeltStatusValid(&p_IC_3F8_st.IC_passengerSeatBeltStatusValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_ic_passengerSeatDetectSts(&p_IC_3F8_st.ic_passengerSeatDetectSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_ic_RLSeatDetectSts(&p_IC_3F8_st.ic_RLSeatDetectSts);
    u16IC_CLTCFuleRemainingMileage = (((uint16_t)p_IC_3F8_st.IC_CLTCFuleRemainingMileage_H) << 8) + 
                                ((uint16_t)p_IC_3F8_st.IC_CLTCFuleRemainingMileage_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_CLTCFuleRemainingMileage(&u16IC_CLTCFuleRemainingMileage);
    u16IC_CLTCRemainingMileage = (((uint16_t)p_IC_3F8_st.IC_CLTCRemainingMileage_H) << 8) + 
                                ((uint16_t)p_IC_3F8_st.IC_CLTCRemainingMileage_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_CLTCRemainingMileage(&u16IC_CLTCRemainingMileage);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_3F8Counter(&p_IC_3F8_st.IC_3F8Counter);
    bResult |= Rte_Write_rpSR_CANMSG_IC_3F8_ComIn_VeCAN_IC_3F8Checksum(&p_IC_3F8_st.IC_3F8Checksum);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_3F8 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_state3(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ic_avgTimeSincethelastchargeTripReserved = 0;
    uint16_t u16ic_avgSpdSincethelastchargeTripReserved = 0;
    uint16_t u16ic_FuelComsumpV2V = 0;
    uint16_t u16ic_FuelConsumCrntTrip = 0;
    if (p_IC_state3_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_state3_st) + 4, sigbuff, len);

    u16ic_avgTimeSincethelastchargeTripReserved = (((uint16_t)p_IC_state3_st.ic_avgTimeSincethelastchargeTripReserved_H) << 8) + 
                                ((uint16_t)p_IC_state3_st.ic_avgTimeSincethelastchargeTripReserved_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state3_ComIn_VeCAN_ic_avgTimeSincethelastchargeTripReserved(&u16ic_avgTimeSincethelastchargeTripReserved);
    u16ic_avgSpdSincethelastchargeTripReserved = (((uint16_t)p_IC_state3_st.ic_avgSpdSincethelastchargeTripReserved_H) << 8) + 
                                ((uint16_t)p_IC_state3_st.ic_avgSpdSincethelastchargeTripReserved_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state3_ComIn_VeCAN_ic_avgSpdSincethelastchargeTripReserved(&u16ic_avgSpdSincethelastchargeTripReserved);
    u16ic_FuelComsumpV2V = (((uint16_t)p_IC_state3_st.ic_FuelComsumpV2V_H) << 8) + 
                                ((uint16_t)p_IC_state3_st.ic_FuelComsumpV2V_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state3_ComIn_VeCAN_ic_FuelComsumpV2V(&u16ic_FuelComsumpV2V);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state3_ComIn_VeCAN_ic_FuelTankResistance(&p_IC_state3_st.ic_FuelTankResistance);
    u16ic_FuelConsumCrntTrip = (((uint16_t)p_IC_state3_st.ic_FuelConsumCrntTrip_H) << 8) + 
                                ((uint16_t)p_IC_state3_st.ic_FuelConsumCrntTrip_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state3_ComIn_VeCAN_ic_FuelConsumCrntTrip(&u16ic_FuelConsumCrntTrip);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_state3 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_Warning(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IC_Warning_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_Warning_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_AlarmListflag(&p_IC_Warning_st.IC_AlarmListflag);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_FaultNum(&p_IC_Warning_st.IC_FaultNum);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_WarningStatus(&p_IC_Warning_st.IC_WarningStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_FaultNum2(&p_IC_Warning_st.IC_FaultNum2);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_WarningStatus2(&p_IC_Warning_st.IC_WarningStatus2);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_FaultNum3(&p_IC_Warning_st.IC_FaultNum3);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_WarningStatus3(&p_IC_Warning_st.IC_WarningStatus3);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_FaultNum4(&p_IC_Warning_st.IC_FaultNum4);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_WarningStatus4(&p_IC_Warning_st.IC_WarningStatus4);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_FaultNum5(&p_IC_Warning_st.IC_FaultNum5);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_WarningStatus5(&p_IC_Warning_st.IC_WarningStatus5);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_FaultNum6(&p_IC_Warning_st.IC_FaultNum6);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warning_ComIn_VeCAN_IC_WarningStatus6(&p_IC_Warning_st.IC_WarningStatus6);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_Warning error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_Warningfb(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IC_Warningfb_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_Warningfb_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IC_Warningfb_ComIn_VeCAN_IC_DMS_DistractionIconFB(&p_IC_Warningfb_st.IC_DMS_DistractionIconFB);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warningfb_ComIn_VeCAN_IC_DMS_FatigueIconFB(&p_IC_Warningfb_st.IC_DMS_FatigueIconFB);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warningfb_ComIn_VeCAN_IC_DMS_Res1(&p_IC_Warningfb_st.IC_DMS_Res1);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warningfb_ComIn_VeCAN_IC_DMS_Res2(&p_IC_Warningfb_st.IC_DMS_Res2);
    bResult |= Rte_Write_rpSR_CANMSG_IC_Warningfb_ComIn_VeCAN_IC_DMS_Res3(&p_IC_Warningfb_st.IC_DMS_Res3);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_Warningfb error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_state(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint32_t u32ic_totalMileage = 0;
    uint16_t u16ic_vehicleSpeedDisp = 0;
    if (p_IC_state_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_state_st) + 4, sigbuff, len);

    u32ic_totalMileage = (((uint32_t)p_IC_state_st.ic_totalMileage_H) << 24) + 
                                (((uint32_t)p_IC_state_st.ic_totalMileage_MH) << 16) + 
                                (((uint32_t)p_IC_state_st.ic_totalMileage_ML) << 8) + 
                                ((uint32_t)p_IC_state_st.ic_totalMileage_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_totalMileage(&u32ic_totalMileage);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_lowSocIndication(&p_IC_state_st.ic_lowSocIndication);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_passengerSeatDetectSts(&p_IC_state_st.ic_passengerSeatDetectSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_RMSeatDetectSts(&p_IC_state_st.ic_RMSeatDetectSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_RRSeatDetectSts(&p_IC_state_st.ic_RRSeatDetectSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_2ndRowLeftSeatBeltSts(&p_IC_state_st.ic_2ndRowLeftSeatBeltSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_2ndRowLeftSeatBeltStsValid(&p_IC_state_st.ic_2ndRowLeftSeatBeltStsValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_2ndRowMiddleSeatBeltSts(&p_IC_state_st.ic_2ndRowMiddleSeatBeltSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_2ndRowMiddleSeatBeltStsValid(&p_IC_state_st.ic_2ndRowMiddleSeatBeltStsValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_2ndRowRightSeatBeltSts(&p_IC_state_st.ic_2ndRowRightSeatBeltSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_2ndRowRightSeatBeltStsValid(&p_IC_state_st.ic_2ndRowRightSeatBeltStsValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_displayFail(&p_IC_state_st.ic_displayFail);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_qDashACCFail(&p_IC_state_st.ic_qDashACCFail);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_RLSeatDetectSts(&p_IC_state_st.ic_RLSeatDetectSts);
    u16ic_vehicleSpeedDisp = (((uint16_t)p_IC_state_st.ic_vehicleSpeedDisp_H) << 8) + 
                                ((uint16_t)p_IC_state_st.ic_vehicleSpeedDisp_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_vehicleSpeedDisp(&u16ic_vehicleSpeedDisp);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_brakeFluidLevel(&p_IC_state_st.ic_brakeFluidLevel);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_totalMileageValid(&p_IC_state_st.ic_totalMileageValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_vehicleSpeedDispValid(&p_IC_state_st.ic_vehicleSpeedDispValid);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_state_rollingCounter(&p_IC_state_st.ic_state_rollingCounter);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state_ComIn_VeCAN_ic_state_CheckSum(&p_IC_state_st.ic_state_CheckSum);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_state error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_info2(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ic_SUMRemainingMileage = 0;
    uint16_t u16ic_WLTCRemainingMileage = 0;
    uint16_t u16ic_SUMFuleRemainingMileage = 0;
    uint16_t u16ic_WLTCFuleRemainingMileage = 0;
    if (p_IC_info2_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_info2_st) + 4, sigbuff, len);

    u16ic_SUMRemainingMileage = (((uint16_t)p_IC_info2_st.ic_SUMRemainingMileage_H) << 8) + 
                                ((uint16_t)p_IC_info2_st.ic_SUMRemainingMileage_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_SUMRemainingMileage(&u16ic_SUMRemainingMileage);
    u16ic_WLTCRemainingMileage = (((uint16_t)p_IC_info2_st.ic_WLTCRemainingMileage_H) << 8) + 
                                ((uint16_t)p_IC_info2_st.ic_WLTCRemainingMileage_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_WLTCRemainingMileage(&u16ic_WLTCRemainingMileage);
    u16ic_SUMFuleRemainingMileage = (((uint16_t)p_IC_info2_st.ic_SUMFuleRemainingMileage_H) << 8) + 
                                ((uint16_t)p_IC_info2_st.ic_SUMFuleRemainingMileage_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_SUMFuleRemainingMileage(&u16ic_SUMFuleRemainingMileage);
    u16ic_WLTCFuleRemainingMileage = (((uint16_t)p_IC_info2_st.ic_WLTCFuleRemainingMileage_H) << 8) + 
                                ((uint16_t)p_IC_info2_st.ic_WLTCFuleRemainingMileage_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_WLTCFuleRemainingMileage(&u16ic_WLTCFuleRemainingMileage);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_SpeedLimitSts(&p_IC_info2_st.ic_SpeedLimitSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_SpeedLimitModeSts(&p_IC_info2_st.ic_SpeedLimitModeSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_RearseatbeltVoiceWarningSetFb(&p_IC_info2_st.ic_RearseatbeltVoiceWarningSetFb);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_RemainingMilmodeSts(&p_IC_info2_st.ic_RemainingMilmodeSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_OverspeedSts(&p_IC_info2_st.ic_OverspeedSts);
    bResult |= Rte_Write_rpSR_CANMSG_IC_info2_ComIn_VeCAN_ic_IllumiLevelSts(&p_IC_info2_st.ic_IllumiLevelSts);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_info2 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_state1(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ic_avgFuelConsumTripA = 0;
    uint16_t u16ic_avgFuelConsumCrntTrip = 0;
    uint16_t u16ic_avgFuelConsumTripB = 0;
    uint16_t u16ic_avgFuelConsumCrntLastTrip = 0;
    if (p_IC_state1_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_state1_st) + 4, sigbuff, len);

    u16ic_avgFuelConsumTripA = (((uint16_t)p_IC_state1_st.ic_avgFuelConsumTripA_H) << 8) + 
                                ((uint16_t)p_IC_state1_st.ic_avgFuelConsumTripA_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state1_ComIn_VeCAN_ic_avgFuelConsumTripA(&u16ic_avgFuelConsumTripA);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state1_ComIn_VeCAN_ic_languageSts(&p_IC_state1_st.ic_languageSts);
    u16ic_avgFuelConsumCrntTrip = (((uint16_t)p_IC_state1_st.ic_avgFuelConsumCrntTrip_H) << 8) + 
                                ((uint16_t)p_IC_state1_st.ic_avgFuelConsumCrntTrip_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state1_ComIn_VeCAN_ic_avgFuelConsumCrntTrip(&u16ic_avgFuelConsumCrntTrip);
    u16ic_avgFuelConsumTripB = (((uint16_t)p_IC_state1_st.ic_avgFuelConsumTripB_H) << 8) + 
                                ((uint16_t)p_IC_state1_st.ic_avgFuelConsumTripB_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state1_ComIn_VeCAN_ic_avgFuelConsumTripB(&u16ic_avgFuelConsumTripB);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state1_ComIn_VeCAN_ic_oilPercentFail(&p_IC_state1_st.ic_oilPercentFail);
    u16ic_avgFuelConsumCrntLastTrip = (((uint16_t)p_IC_state1_st.ic_avgFuelConsumCrntLastTrip_H) << 8) + 
                                ((uint16_t)p_IC_state1_st.ic_avgFuelConsumCrntLastTrip_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state1_ComIn_VeCAN_ic_avgFuelConsumCrntLastTrip(&u16ic_avgFuelConsumCrntLastTrip);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state1_ComIn_VeCAN_ic_oilPercent(&p_IC_state1_st.ic_oilPercent);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_state1 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_EnergyConsumption(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IC_E_energyconsumption = 0;
    uint16_t u16IC_E_energyconsumptionA = 0;
    uint16_t u16IC_E_energyconsumptionB = 0;
    uint16_t u16IC_F_energyconsumption = 0;
    uint16_t u16IC_F_energyconsumptionA = 0;
    uint16_t u16IC_F_energyconsumptionB = 0;
    if (p_IC_EnergyConsumption_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_EnergyConsumption_st) + 4, sigbuff, len);

    u16IC_E_energyconsumption = (((uint16_t)p_IC_EnergyConsumption_st.IC_E_energyconsumption_H) << 8) + 
                                ((uint16_t)p_IC_EnergyConsumption_st.IC_E_energyconsumption_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_EnergyConsumption_ComIn_VeCAN_IC_E_energyconsumption(&u16IC_E_energyconsumption);
    u16IC_E_energyconsumptionA = (((uint16_t)p_IC_EnergyConsumption_st.IC_E_energyconsumptionA_H) << 8) + 
                                ((uint16_t)p_IC_EnergyConsumption_st.IC_E_energyconsumptionA_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_EnergyConsumption_ComIn_VeCAN_IC_E_energyconsumptionA(&u16IC_E_energyconsumptionA);
    u16IC_E_energyconsumptionB = (((uint16_t)p_IC_EnergyConsumption_st.IC_E_energyconsumptionB_H) << 8) + 
                                ((uint16_t)p_IC_EnergyConsumption_st.IC_E_energyconsumptionB_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_EnergyConsumption_ComIn_VeCAN_IC_E_energyconsumptionB(&u16IC_E_energyconsumptionB);
    u16IC_F_energyconsumption = (((uint16_t)p_IC_EnergyConsumption_st.IC_F_energyconsumption_H) << 8) + 
                                ((uint16_t)p_IC_EnergyConsumption_st.IC_F_energyconsumption_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_EnergyConsumption_ComIn_VeCAN_IC_F_energyconsumption(&u16IC_F_energyconsumption);
    u16IC_F_energyconsumptionA = (((uint16_t)p_IC_EnergyConsumption_st.IC_F_energyconsumptionA_H) << 8) + 
                                ((uint16_t)p_IC_EnergyConsumption_st.IC_F_energyconsumptionA_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_EnergyConsumption_ComIn_VeCAN_IC_F_energyconsumptionA(&u16IC_F_energyconsumptionA);
    u16IC_F_energyconsumptionB = (((uint16_t)p_IC_EnergyConsumption_st.IC_F_energyconsumptionB_H) << 8) + 
                                ((uint16_t)p_IC_EnergyConsumption_st.IC_F_energyconsumptionB_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_EnergyConsumption_ComIn_VeCAN_IC_F_energyconsumptionB(&u16IC_F_energyconsumptionB);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_EnergyConsumption error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_state2(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint32_t u32IC_VehRemMntnMile = 0;
    uint16_t u16ic_avgSpdTripA = 0;
    uint16_t u16ic_avgSpdCurrentTrip = 0;
    if (p_IC_state2_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_state2_st) + 4, sigbuff, len);

    u32IC_VehRemMntnMile = (((uint32_t)p_IC_state2_st.IC_VehRemMntnMile_H) << 24) + 
                                (((uint32_t)p_IC_state2_st.IC_VehRemMntnMile_MH) << 16) + 
                                (((uint32_t)p_IC_state2_st.IC_VehRemMntnMile_ML) << 8) + 
                                ((uint32_t)p_IC_state2_st.IC_VehRemMntnMile_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state2_ComIn_VeCAN_IC_VehRemMntnMile(&u32IC_VehRemMntnMile);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state2_ComIn_VeCAN_IC_VehMntnMileRmnReq(&p_IC_state2_st.IC_VehMntnMileRmnReq);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state2_ComIn_VeCAN_IC_VehMntnTimeRmnReq(&p_IC_state2_st.IC_VehMntnTimeRmnReq);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state2_ComIn_VeCAN_IC_REMntnRmnReq(&p_IC_state2_st.IC_REMntnRmnReq);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state2_ComIn_VeCAN_ic_PowerReset(&p_IC_state2_st.ic_PowerReset);
    u16ic_avgSpdTripA = (((uint16_t)p_IC_state2_st.ic_avgSpdTripA_H) << 8) + 
                                ((uint16_t)p_IC_state2_st.ic_avgSpdTripA_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state2_ComIn_VeCAN_ic_avgSpdTripA(&u16ic_avgSpdTripA);
    u16ic_avgSpdCurrentTrip = (((uint16_t)p_IC_state2_st.ic_avgSpdCurrentTrip_H) << 8) + 
                                ((uint16_t)p_IC_state2_st.ic_avgSpdCurrentTrip_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state2_ComIn_VeCAN_ic_avgSpdCurrentTrip(&u16ic_avgSpdCurrentTrip);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_state2 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_state4(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint32_t u32ic_tripmeterA = 0;
    uint32_t u32ic_tripmeterB = 0;
    if (p_IC_state4_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_state4_st) + 4, sigbuff, len);

    u32ic_tripmeterA = (((uint32_t)p_IC_state4_st.ic_tripmeterA_H) << 24) + 
                                (((uint32_t)p_IC_state4_st.ic_tripmeterA_MH) << 16) + 
                                (((uint32_t)p_IC_state4_st.ic_tripmeterA_ML) << 8) + 
                                ((uint32_t)p_IC_state4_st.ic_tripmeterA_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state4_ComIn_VeCAN_ic_tripmeterA(&u32ic_tripmeterA);
    u32ic_tripmeterB = (((uint32_t)p_IC_state4_st.ic_tripmeterB_H) << 24) + 
                                (((uint32_t)p_IC_state4_st.ic_tripmeterB_MH) << 16) + 
                                (((uint32_t)p_IC_state4_st.ic_tripmeterB_ML) << 8) + 
                                ((uint32_t)p_IC_state4_st.ic_tripmeterB_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state4_ComIn_VeCAN_ic_tripmeterB(&u32ic_tripmeterB);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state4_ComIn_VeCAN_IC_VehMntnMileCleaFb(&p_IC_state4_st.IC_VehMntnMileCleaFb);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state4_ComIn_VeCAN_IC_OilMntnMileCleaFb(&p_IC_state4_st.IC_OilMntnMileCleaFb);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state4_ComIn_VeCAN_IC_OilFilMntnMileCleaFb(&p_IC_state4_st.IC_OilFilMntnMileCleaFb);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state4_ComIn_VeCAN_IC_AirFilMntnMileCleaFb(&p_IC_state4_st.IC_AirFilMntnMileCleaFb);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state4_ComIn_VeCAN_IC_VehIntMntnMileFb(&p_IC_state4_st.IC_VehIntMntnMileFb);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_state4 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_state5(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint32_t u32IC_OilRemMntnMile = 0;
    uint16_t u16IC_VehRemMntnTime = 0;
    uint32_t u32IC_OilFilRemMntnMile = 0;
    uint32_t u32IC_AirFilRemMntnMile = 0;
    if (p_IC_state5_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_state5_st) + 4, sigbuff, len);

    u32IC_OilRemMntnMile = (((uint32_t)p_IC_state5_st.IC_OilRemMntnMile_H) << 24) + 
                                (((uint32_t)p_IC_state5_st.IC_OilRemMntnMile_MH) << 16) + 
                                (((uint32_t)p_IC_state5_st.IC_OilRemMntnMile_ML) << 8) + 
                                ((uint32_t)p_IC_state5_st.IC_OilRemMntnMile_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state5_ComIn_VeCAN_IC_OilRemMntnMile(&u32IC_OilRemMntnMile);
    u16IC_VehRemMntnTime = (((uint16_t)p_IC_state5_st.IC_VehRemMntnTime_H) << 8) + 
                                ((uint16_t)p_IC_state5_st.IC_VehRemMntnTime_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state5_ComIn_VeCAN_IC_VehRemMntnTime(&u16IC_VehRemMntnTime);
    u32IC_OilFilRemMntnMile = (((uint32_t)p_IC_state5_st.IC_OilFilRemMntnMile_H) << 24) + 
                                (((uint32_t)p_IC_state5_st.IC_OilFilRemMntnMile_MH) << 16) + 
                                (((uint32_t)p_IC_state5_st.IC_OilFilRemMntnMile_ML) << 8) + 
                                ((uint32_t)p_IC_state5_st.IC_OilFilRemMntnMile_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state5_ComIn_VeCAN_IC_OilFilRemMntnMile(&u32IC_OilFilRemMntnMile);
    u32IC_AirFilRemMntnMile = (((uint32_t)p_IC_state5_st.IC_AirFilRemMntnMile_H) << 24) + 
                                (((uint32_t)p_IC_state5_st.IC_AirFilRemMntnMile_MH) << 16) + 
                                (((uint32_t)p_IC_state5_st.IC_AirFilRemMntnMile_ML) << 8) + 
                                ((uint32_t)p_IC_state5_st.IC_AirFilRemMntnMile_L);
    bResult |= Rte_Write_rpSR_CANMSG_IC_state5_ComIn_VeCAN_IC_AirFilRemMntnMile(&u32IC_AirFilRemMntnMile);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_state5 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_StatusAndNotify(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IVI_averagePowerConsumThisTrip = 0;
    if (p_IVI_StatusAndNotify_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_StatusAndNotify_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_FrameType(&p_IVI_StatusAndNotify_st.IVI_FrameType);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_WorkStatus(&p_IVI_StatusAndNotify_st.IVI_WorkStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_CurrentVideo(&p_IVI_StatusAndNotify_st.IVI_CurrentVideo);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_EventNotify(&p_IVI_StatusAndNotify_st.IVI_EventNotify);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_IC_Sync(&p_IVI_StatusAndNotify_st.IVI_IC_Sync);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_Respitemodests(&p_IVI_StatusAndNotify_st.IVI_Respitemodests);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_ModeSts(&p_IVI_StatusAndNotify_st.IVI_ModeSts);
    u16IVI_averagePowerConsumThisTrip = (((uint16_t)p_IVI_StatusAndNotify_st.IVI_averagePowerConsumThisTrip_H) << 8) + 
                                ((uint16_t)p_IVI_StatusAndNotify_st.IVI_averagePowerConsumThisTrip_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_averagePowerConsumThisTrip(&u16IVI_averagePowerConsumThisTrip);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_SentryReq(&p_IVI_StatusAndNotify_st.IVI_SentryReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_SentryAlarmSts(&p_IVI_StatusAndNotify_st.IVI_SentryAlarmSts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_ModeReq(&p_IVI_StatusAndNotify_st.IVI_ModeReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_SentryTimeFd(&p_IVI_StatusAndNotify_st.IVI_SentryTimeFd);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_ChildrenLeftremindSts(&p_IVI_StatusAndNotify_st.IVI_ChildrenLeftremindSts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_PetModeSts(&p_IVI_StatusAndNotify_st.IVI_PetModeSts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_SentryFaultReason(&p_IVI_StatusAndNotify_st.IVI_SentryFaultReason);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_WashModeSts(&p_IVI_StatusAndNotify_st.IVI_WashModeSts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_StatusAndNotify_ComIn_VeCAN_IVI_HCUcontrol(&p_IVI_StatusAndNotify_st.IVI_HCUcontrol);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_StatusAndNotify error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_hmi(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_hmi_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_hmi_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_IVI_DMS_DistractionIcon(&p_IVI_hmi_st.IVI_DMS_DistractionIcon);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_IVI_DMS_FatigueIcon(&p_IVI_hmi_st.IVI_DMS_FatigueIcon);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_IVI_DMS_Res1(&p_IVI_hmi_st.IVI_DMS_Res1);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_IVI_DMS_Res2(&p_IVI_hmi_st.IVI_DMS_Res2);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_IVI_DMS_Res3(&p_IVI_hmi_st.IVI_DMS_Res3);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_IVI_AdsWarnLvl(&p_IVI_hmi_st.IVI_AdsWarnLvl);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_IVI_UserID(&p_IVI_hmi_st.IVI_UserID);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_hmi_ComIn_VeCAN_ivi_CampModeReq(&p_IVI_hmi_st.ivi_CampModeReq);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_hmi error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_State_5F0(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_State_5F0_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_State_5F0_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_status(&p_IVI_State_5F0_st.cdc_status);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_mcuStatus(&p_IVI_State_5F0_st.cdc_mcuStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_mcuEnvStatus(&p_IVI_State_5F0_st.cdc_mcuEnvStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_mcuBatStatus(&p_IVI_State_5F0_st.cdc_mcuBatStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_mcuFsmStatus(&p_IVI_State_5F0_st.cdc_mcuFsmStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_rdcStatus(&p_IVI_State_5F0_st.cdc_rdcStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_socChipStatus(&p_IVI_State_5F0_st.cdc_socChipStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_icPowerStatus(&p_IVI_State_5F0_st.cdc_icPowerStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_iviPowerStatus(&p_IVI_State_5F0_st.cdc_iviPowerStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_silsStatus(&p_IVI_State_5F0_st.cdc_silsStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_icLcdStatus(&p_IVI_State_5F0_st.cdc_icLcdStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_State_5F0_ComIn_VeCAN_cdc_iviLcdStatus(&p_IVI_State_5F0_st.cdc_iviLcdStatus);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_State_5F0 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IC_RequestAndStatus(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IC_RequestAndStatus_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IC_RequestAndStatus_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IC_RequestAndStatus_ComIn_VeCAN_IC_FrameType(&p_IC_RequestAndStatus_st.IC_FrameType);
    bResult |= Rte_Write_rpSR_CANMSG_IC_RequestAndStatus_ComIn_VeCAN_IC_WorkStatus(&p_IC_RequestAndStatus_st.IC_WorkStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IC_RequestAndStatus_ComIn_VeCAN_IC_RequestVideo(&p_IC_RequestAndStatus_st.IC_RequestVideo);
    bResult |= Rte_Write_rpSR_CANMSG_IC_RequestAndStatus_ComIn_VeCAN_IC_currentDisplayVideo(&p_IC_RequestAndStatus_st.IC_currentDisplayVideo);
    bResult |= Rte_Write_rpSR_CANMSG_IC_RequestAndStatus_ComIn_VeCAN_IC_keyOperation(&p_IC_RequestAndStatus_st.IC_keyOperation);
    bResult |= Rte_Write_rpSR_CANMSG_IC_RequestAndStatus_ComIn_VeCAN_IC_RightVideoStatus(&p_IC_RequestAndStatus_st.IC_RightVideoStatus);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IC_RequestAndStatus error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_set(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_set_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_set_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_hvacDefrostMode(&p_IVI_set_st.ivi_hvacDefrostMode);
    if(p_IVI_set_st.ivi_hvacOnOffReq != Com_SignalInitValue_ivi_hvacOnOffReq_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_hvacOnOffReq(&p_IVI_set_st.ivi_hvacOnOffReq);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_ExhibitionScene(&p_IVI_set_st.IVI_ExhibitionScene);
    if(p_IVI_set_st.ivi_hvacAutoModeReq != Com_SignalInitValue_ivi_hvacAutoModeReq_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_hvacAutoModeReq(&p_IVI_set_st.ivi_hvacAutoModeReq);
    }
    if(p_IVI_set_st.ivi_hvacRecircModeReq != Com_SignalInitValue_ivi_hvacRecircModeReq_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_hvacRecircModeReq(&p_IVI_set_st.ivi_hvacRecircModeReq);
    }
    if(p_IVI_set_st.IVI_ACEnergySavingReq != Com_SignalInitValue_IVI_ACEnergySavingReq_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_ACEnergySavingReq(&p_IVI_set_st.IVI_ACEnergySavingReq);
    }
    if(p_IVI_set_st.ivi_hvacModeReq != Com_SignalInitValue_ivi_hvacModeReq_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_hvacModeReq(&p_IVI_set_st.ivi_hvacModeReq);
    }
    if(p_IVI_set_st.ivi_driverTempCSet != Com_SignalInitValue_ivi_driverTempCSet_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_driverTempCSet(&p_IVI_set_st.ivi_driverTempCSet);
    }
    if(p_IVI_set_st.ivi_hvacBlowLvReq != Com_SignalInitValue_ivi_hvacBlowLvReq_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_hvacBlowLvReq(&p_IVI_set_st.ivi_hvacBlowLvReq);
    }
    if(p_IVI_set_st.ivi_passengerTempCSet != Com_SignalInitValue_ivi_passengerTempCSet_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_passengerTempCSet(&p_IVI_set_st.ivi_passengerTempCSet);
    }
    if(p_IVI_set_st.ivi_hvacDualMode != Com_SignalInitValue_ivi_hvacDualMode_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_hvacDualMode(&p_IVI_set_st.ivi_hvacDualMode);
    }
    if(p_IVI_set_st.ivi_acReq != Com_SignalInitValue_ivi_acReq_0x3B5_INFO_Message){
        bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_acReq(&p_IVI_set_st.ivi_acReq);
    }
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_NavigatioRecircReq(&p_IVI_set_st.IVI_NavigatioRecircReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_NaviTunnelstatus(&p_IVI_set_st.IVI_NaviTunnelstatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_ScreenOutReq(&p_IVI_set_st.IVI_ScreenOutReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_TimeFormatset(&p_IVI_set_st.IVI_TimeFormatset);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_USB_Sts(&p_IVI_set_st.USB_Sts);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_svcSteerInteractionSetReserved(&p_IVI_set_st.ivi_svcSteerInteractionSetReserved);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_InterfaceSwitchReq(&p_IVI_set_st.ivi_InterfaceSwitchReq);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_languageSet(&p_IVI_set_st.ivi_languageSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_IntPuficationSw(&p_IVI_set_st.IVI_IntPuficationSw);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_ivi_unitSet(&p_IVI_set_st.ivi_unitSet);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_NaturalwindSw(&p_IVI_set_st.IVI_NaturalwindSw);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_VideoResult(&p_IVI_set_st.IVI_VideoResult);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_set_ComIn_VeCAN_IVI_TakePhotoReq(&p_IVI_set_st.IVI_TakePhotoReq);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_set error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_navi(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint32_t u32ivi_crossNaviDistance = 0;
    if (p_IVI_navi_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_navi_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_navi_ComIn_VeCAN_ivi_crossNaviMode(&p_IVI_navi_st.ivi_crossNaviMode);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_navi_ComIn_VeCAN_ivi_naviDirection(&p_IVI_navi_st.ivi_naviDirection);
    u32ivi_crossNaviDistance = (((uint32_t)p_IVI_navi_st.ivi_crossNaviDistance_H) << 24) + 
                                (((uint32_t)p_IVI_navi_st.ivi_crossNaviDistance_MH) << 16) + 
                                (((uint32_t)p_IVI_navi_st.ivi_crossNaviDistance_ML) << 8) + 
                                ((uint32_t)p_IVI_navi_st.ivi_crossNaviDistance_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_navi_ComIn_VeCAN_ivi_crossNaviDistance(&u32ivi_crossNaviDistance);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_navi error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_NaviDirection_LaneX(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_IVI_NaviDirection_LaneX_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_NaviDirection_LaneX_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane1(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane1);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane2(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane2);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane3(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane3);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane4(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane4);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane5(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane5);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane6(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane6);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane7(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane7);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_NaviDirection_LaneX_ComIn_VeCAN_ivi_NavidirectionLane8(&p_IVI_NaviDirection_LaneX_st.ivi_NavidirectionLane8);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_NaviDirection_LaneX error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_media(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_frequenceAM = 0;
    if (p_IVI_media_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_media_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_radioStatus(&p_IVI_media_st.ivi_radioStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_blueToothStatus(&p_IVI_media_st.ivi_blueToothStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_usbStatus(&p_IVI_media_st.ivi_usbStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_iPodStatus(&p_IVI_media_st.ivi_iPodStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_lvdsStatus(&p_IVI_media_st.ivi_lvdsStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_DMS_Sysfault(&p_IVI_media_st.ivi_DMS_Sysfault);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_sdStatus(&p_IVI_media_st.ivi_sdStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_auxStatus_Reserved(&p_IVI_media_st.ivi_auxStatus_Reserved);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_tvStatus(&p_IVI_media_st.ivi_tvStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_discStatus(&p_IVI_media_st.ivi_discStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_dvbtStatus(&p_IVI_media_st.ivi_dvbtStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_naviStatus(&p_IVI_media_st.ivi_naviStatus);
    u16ivi_frequenceAM = (((uint16_t)p_IVI_media_st.ivi_frequenceAM_H) << 8) + 
                                ((uint16_t)p_IVI_media_st.ivi_frequenceAM_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_frequenceAM(&u16ivi_frequenceAM);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_lvdsReadyStatus(&p_IVI_media_st.ivi_lvdsReadyStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_media_ComIn_VeCAN_ivi_frequenceFM(&p_IVI_media_st.ivi_frequenceFM);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_media error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_naviText(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_naviText1 = 0;
    uint16_t u16ivi_naviText2 = 0;
    uint16_t u16ivi_naviText3 = 0;
    if (p_IVI_naviText_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_naviText_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_naviText_ComIn_VeCAN_ivi_naviTextStrLength(&p_IVI_naviText_st.ivi_naviTextStrLength);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_naviText_ComIn_VeCAN_ivi_naviTextCountNum(&p_IVI_naviText_st.ivi_naviTextCountNum);
    u16ivi_naviText1 = (((uint16_t)p_IVI_naviText_st.ivi_naviText1_H) << 8) + 
                                ((uint16_t)p_IVI_naviText_st.ivi_naviText1_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_naviText_ComIn_VeCAN_ivi_naviText1(&u16ivi_naviText1);
    u16ivi_naviText2 = (((uint16_t)p_IVI_naviText_st.ivi_naviText2_H) << 8) + 
                                ((uint16_t)p_IVI_naviText_st.ivi_naviText2_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_naviText_ComIn_VeCAN_ivi_naviText2(&u16ivi_naviText2);
    u16ivi_naviText3 = (((uint16_t)p_IVI_naviText_st.ivi_naviText3_H) << 8) + 
                                ((uint16_t)p_IVI_naviText_st.ivi_naviText3_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_naviText_ComIn_VeCAN_ivi_naviText3(&u16ivi_naviText3);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_naviText error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_TelSongText(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16ivi_telSongText1 = 0;
    uint16_t u16ivi_telSongText2 = 0;
    uint16_t u16ivi_telSongText3 = 0;
    if (p_IVI_TelSongText_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_TelSongText_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_TelSongText_ComIn_VeCAN_ivi_telSongTextStrLength(&p_IVI_TelSongText_st.ivi_telSongTextStrLength);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_TelSongText_ComIn_VeCAN_ivi_telSongTextCountNum(&p_IVI_TelSongText_st.ivi_telSongTextCountNum);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_TelSongText_ComIn_VeCAN_ivi_telSongTextType(&p_IVI_TelSongText_st.ivi_telSongTextType);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_TelSongText_ComIn_VeCAN_ivi_telSongTextEncodingType(&p_IVI_TelSongText_st.ivi_telSongTextEncodingType);
    u16ivi_telSongText1 = (((uint16_t)p_IVI_TelSongText_st.ivi_telSongText1_H) << 8) + 
                                ((uint16_t)p_IVI_TelSongText_st.ivi_telSongText1_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_TelSongText_ComIn_VeCAN_ivi_telSongText1(&u16ivi_telSongText1);
    u16ivi_telSongText2 = (((uint16_t)p_IVI_TelSongText_st.ivi_telSongText2_H) << 8) + 
                                ((uint16_t)p_IVI_TelSongText_st.ivi_telSongText2_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_TelSongText_ComIn_VeCAN_ivi_telSongText2(&u16ivi_telSongText2);
    u16ivi_telSongText3 = (((uint16_t)p_IVI_TelSongText_st.ivi_telSongText3_H) << 8) + 
                                ((uint16_t)p_IVI_TelSongText_st.ivi_telSongText3_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_TelSongText_ComIn_VeCAN_ivi_telSongText3(&u16ivi_telSongText3);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_TelSongText error bResult:0x%x\r\n", bResult);
    }
}


void setSignal_Diag_Resp_IVI(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint64_t u64Diag_Resp_IVI_Data = 0;
    if (p_Diag_Resp_IVI_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_Diag_Resp_IVI_st) + 4, sigbuff, len);

    u64Diag_Resp_IVI_Data = (((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_8) << 56) + 
                                (((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_7) << 48) + 
                                (((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_6) << 40) + 
                                (((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_5) << 32) + 
                                (((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_4) << 24) + 
                                (((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_3) << 16) + 
                                (((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_2) << 8) + 
                                ((uint64_t)p_Diag_Resp_IVI_st.Diag_Resp_IVI_Data_1);
    bResult |= Rte_Write_rpSR_CANMSG_Diag_Resp_IVI_ComIn_VeCAN_Diag_Resp_IVI_Data(&u64Diag_Resp_IVI_Data);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_Diag_Resp_IVI error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_IVI_ADAS_3E1(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    uint16_t u16IVI_MapRampOffset = 0;
    if (p_IVI_ADAS_3E1_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_IVI_ADAS_3E1_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapSpeedlimit(&p_IVI_ADAS_3E1_st.IVI_MapSpeedlimit);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_FactoryRestHold(&p_IVI_ADAS_3E1_st.IVI_FactoryRestHold);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapStatus(&p_IVI_ADAS_3E1_st.IVI_MapStatus);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapNextRamp(&p_IVI_ADAS_3E1_st.IVI_MapNextRamp);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapCurrentRoad(&p_IVI_ADAS_3E1_st.IVI_MapCurrentRoad);
    u16IVI_MapRampOffset = (((uint16_t)p_IVI_ADAS_3E1_st.IVI_MapRampOffset_H) << 8) + 
                                ((uint16_t)p_IVI_ADAS_3E1_st.IVI_MapRampOffset_L);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapRampOffset(&u16IVI_MapRampOffset);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapSpeedlimit_Unit(&p_IVI_ADAS_3E1_st.IVI_MapSpeedlimit_Unit);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapRoadtype(&p_IVI_ADAS_3E1_st.IVI_MapRoadtype);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapSpeedlimit_Type(&p_IVI_ADAS_3E1_st.IVI_MapSpeedlimit_Type);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapTimeConditionSignUsed(&p_IVI_ADAS_3E1_st.IVI_MapTimeConditionSignUsed);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapTimeConditionSignExist(&p_IVI_ADAS_3E1_st.IVI_MapTimeConditionSignExist);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapTrafficSign_Type(&p_IVI_ADAS_3E1_st.IVI_MapTrafficSign_Type);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapSpeedLimit_Rain(&p_IVI_ADAS_3E1_st.IVI_MapSpeedLimit_Rain);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapSpeedLimit_Snow(&p_IVI_ADAS_3E1_st.IVI_MapSpeedLimit_Snow);
    bResult |= Rte_Write_rpSR_CANMSG_IVI_ADAS_3E1_ComIn_VeCAN_IVI_MapCountryCode(&p_IVI_ADAS_3E1_st.IVI_MapCountryCode);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_IVI_ADAS_3E1 error bResult:0x%x\r\n", bResult);
    }
}

void setSignal_Wacc_500(uint8_t *sigbuff, uint8_t len)
{
    uint8_t bResult = RTE_SIG_OK;
    if (p_Wacc_500_st.data_len - 1 != len) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len error:%d\r\n", len);
        return;
    }
    memcpy(((uint8_t*)&p_Wacc_500_st) + 4, sigbuff, len);

    bResult |= Rte_Write_rpSR_CANMSG_Wacc_500_ComIn_VeCAN_IVI_Waccst(&p_Wacc_500_st.IVI_Waccst);
    bResult |= Rte_Write_rpSR_CANMSG_Wacc_500_ComIn_VeCAN_IVI_IviConWcp(&p_Wacc_500_st.IVI_IviConWcp);
    bResult |= Rte_Write_rpSR_CANMSG_Wacc_500_ComIn_VeCAN_IVI_WaccTempDisply(&p_Wacc_500_st.IVI_WaccTempDisply);
    bResult |= Rte_Write_rpSR_CANMSG_Wacc_500_ComIn_VeCAN_IVI_WaccEault(&p_Wacc_500_st.IVI_WaccEault);
    bResult |= Rte_Write_rpSR_CANMSG_Wacc_500_ComIn_VeCAN_IVI_WacctgTemp(&p_Wacc_500_st.IVI_WacctgTemp);

    if (bResult != RTE_SIG_OK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"setSignal_Wacc_500 error bResult:0x%x\r\n", bResult);
    }
}




/* -------------------------external interface----------------------- */
uint8_t getIVISignal_IC_info2_ic_RemainingMilmodeSts()
{
    return p_IC_info2_st.ic_RemainingMilmodeSts;
}

uint8_t getIVISignal_IVI_AVMSet_3D2_IVI_driveModeSts()
{
    return p_IVI_AVMSet_3D2_st.IVI_driveModeSts;
}

void setIVISignal_IVI_infoSet_ivi_ICIllumiLevelSet(uint8_t para)
{
    p_IVI_infoSet_st.ivi_ICIllumiLevelSet = para;
}