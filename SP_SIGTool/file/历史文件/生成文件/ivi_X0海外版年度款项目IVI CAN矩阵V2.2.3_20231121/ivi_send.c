/**
* Copyright (c) 2018-2023 ThunderSoft
* All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
* You may not use, copy, distribute, modify, transmit in any form this file
* except in compliance with ThunderSoft in writing by applicable law.
*
*/
/**
* @file    ivi_send.c
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

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "ivi_send.h"
#include <string.h>
#include "app_task_cfg.h"
#include "ipc_api.h"
#include "r_rlin.h"
#include "log_api.h"
#include "RTE.h"
#include "ipc_event.h"

#define BUF_MAX_SIZE 250

BOOL getSignal_TBOX_chargeSet(void);
BOOL getSignal_BMS_metric(void);
BOOL getSignal_BMS_tboxRequest(void);
BOOL getSignal_VCU_range(void);
BOOL getSignal_VCU_range1(void);
BOOL getSignal_VCU_state(void);
BOOL getSignal_OBC_state(void);
BOOL getSignal_OBC_state1(void);
BOOL getSignal_DCDC_state(void);
BOOL getSignal_GSM_state(void);
BOOL getSignal_GTW_mcur0_mcuf0_info(void);
BOOL getSignal_BMS_temperature(void);
BOOL getSignal_VCU_Info(void);
BOOL getSignal_Diag_FuncReq(void);
BOOL getSignal_VCU_pwr(void);
BOOL getSignal_BMS_ASSt(void);
BOOL getSignal_VCU_stateCha1(void);
BOOL getSignal_EPS_state(void);
BOOL getSignal_EPS_sas(void);
BOOL getSignal_ESC_wheelSpd_Front(void);
BOOL getSignal_ESC_wheelSpd_Rear(void);
BOOL getSignal_ESC_state1(void);
BOOL getSignal_ESC_state2(void);
BOOL getSignal_ESC_yawState(void);
BOOL getSignal_GW_ESC_yawState(void);
BOOL getSignal_ESC_wssFront(void);
BOOL getSignal_ESC_wssRear(void);
BOOL getSignal_ESC_epb(void);
BOOL getSignal_MRR_acc(void);
BOOL getSignal_MRR_pss(void);
BOOL getSignal_MRR_hmi1(void);
BOOL getSignal_MRR_hmi2(void);
BOOL getSignal_MRR_hmi3_34E(void);
BOOL getSignal_MRR_hmi4_34F(void);
BOOL getSignal_MRR_hmi5_355(void);
BOOL getSignal_MRR_hmi6_356(void);
BOOL getSignal_MPC_state(void);
BOOL getSignal_MPC_hmi(void);
BOOL getSignal_MPC_RoadState_359(void);
BOOL getSignal_MPC_hmi_35D(void);
BOOL getSignal_SRR_R_state_22B(void);
BOOL getSignal_ABM_state(void);
BOOL getSignal_APA_35B(void);
BOOL getSignal_VCU_state2(void);
BOOL getSignal_BLE_FB(void);
BOOL getSignal_BLE_User_ID(void);
BOOL getSignal_TBOX_Factory_360(void);
BOOL getSignal_AC_ctrlFeedback(void);
BOOL getSignal_AC_state2(void);
BOOL getSignal_BCM_state(void);
BOOL getSignal_BCM_state2(void);
BOOL getSignal_BCM_state3(void);
BOOL getSignal_BCM_state4(void);
BOOL getSignal_BCM_tpms(void);
BOOL getSignal_BCM_tpms1(void);
BOOL getSignal_BCM_peps(void);
BOOL getSignal_BCM_rsm(void);
BOOL getSignal_BCM_RemotFB(void);
BOOL getSignal_LCU_32A(void);
BOOL getSignal_PLG_state(void);
BOOL getSignal_GW_Handle_state(void);
BOOL getSignal_DSM_state(void);
BOOL getSignal_PSM_memory(void);
BOOL getSignal_DSM_memory(void);
BOOL getSignal_PSM_state(void);
BOOL getSignal_LRSM_state(void);
BOOL getSignal_TBOX_infoCtrl(void);
BOOL getSignal_GW_vent1Sts(void);
BOOL getSignal_GW_vent2Sts(void);
BOOL getSignal_GW_vent3Sts(void);
BOOL getSignal_GW_vent4Sts(void);
BOOL getSignal_GW_vent5Sts(void);
BOOL getSignal_GW_vent6Sts(void);
BOOL getSignal_GW_vent7Sts(void);
BOOL getSignal_GW_vent8Sts(void);
BOOL getSignal_GW_BMS_meas(void);
BOOL getSignal_BMS_state(void);
BOOL getSignal_GTW_mcur0_info(void);
BOOL getSignal_GTW_mcuf0_info(void);
BOOL getSignal_GTW_ecu_gcu_vcu_info(void);
BOOL getSignal_GTW_esc_eps_iB_info(void);
BOOL getSignal_GW_EPS_state(void);
BOOL getSignal_VCU_stateCha2(void);
BOOL getSignal_AC_temp_pressure(void);
BOOL getSignal_WCM_state(void);
BOOL getSignal_AVM_state_484(void);
BOOL getSignal_HUD_state(void);
BOOL getSignal_MFW_Ctrl(void);
BOOL getSignal_MFW_KeySt(void);
BOOL getSignal_IVI_timeAndGPS(void);
BOOL getSignal_GTW_BMS_Rev(void);
BOOL getSignal_Diag_PhyReq_IVI(void);
BOOL getSignal_SWHC_400(void);


    typedef BOOL (*pGetSigFunc)(void);

    typedef struct STC_SIGNAL_INFO_
    {
        uint8_t*            pSigStc;
        pGetSigFunc         pSigFunc;
    } STC_SIGNAL_INFO;
    
#define SIG_PUB_MAX_SIZE 93
STC_SIGNAL_INFO gPubSigInfo[SIG_PUB_MAX_SIZE] =
    {
    {&p_TBOX_chargeSet_st, getSignal_TBOX_chargeSet},
    {&p_BMS_metric_st, getSignal_BMS_metric},
    {&p_BMS_tboxRequest_st, getSignal_BMS_tboxRequest},
    {&p_VCU_range_st, getSignal_VCU_range},
    {&p_VCU_range1_st, getSignal_VCU_range1},
    {&p_VCU_state_st, getSignal_VCU_state},
    {&p_OBC_state_st, getSignal_OBC_state},
    {&p_OBC_state1_st, getSignal_OBC_state1},
    {&p_DCDC_state_st, getSignal_DCDC_state},
    {&p_GSM_state_st, getSignal_GSM_state},
    {&p_GTW_mcur0_mcuf0_info_st, getSignal_GTW_mcur0_mcuf0_info},
    {&p_BMS_temperature_st, getSignal_BMS_temperature},
    {&p_VCU_Info_st, getSignal_VCU_Info},
    {&p_Diag_FuncReq_st, getSignal_Diag_FuncReq},
    {&p_VCU_pwr_st, getSignal_VCU_pwr},
    {&p_BMS_ASSt_st, getSignal_BMS_ASSt},
    {&p_VCU_stateCha1_st, getSignal_VCU_stateCha1},
    {&p_EPS_state_st, getSignal_EPS_state},
    {&p_EPS_sas_st, getSignal_EPS_sas},
    {&p_ESC_wheelSpd_Front_st, getSignal_ESC_wheelSpd_Front},
    {&p_ESC_wheelSpd_Rear_st, getSignal_ESC_wheelSpd_Rear},
    {&p_ESC_state1_st, getSignal_ESC_state1},
    {&p_ESC_state2_st, getSignal_ESC_state2},
    {&p_ESC_yawState_st, getSignal_ESC_yawState},
    {&p_GW_ESC_yawState_st, getSignal_GW_ESC_yawState},
    {&p_ESC_wssFront_st, getSignal_ESC_wssFront},
    {&p_ESC_wssRear_st, getSignal_ESC_wssRear},
    {&p_ESC_epb_st, getSignal_ESC_epb},
    {&p_MRR_acc_st, getSignal_MRR_acc},
    {&p_MRR_pss_st, getSignal_MRR_pss},
    {&p_MRR_hmi1_st, getSignal_MRR_hmi1},
    {&p_MRR_hmi2_st, getSignal_MRR_hmi2},
    {&p_MRR_hmi3_34E_st, getSignal_MRR_hmi3_34E},
    {&p_MRR_hmi4_34F_st, getSignal_MRR_hmi4_34F},
    {&p_MRR_hmi5_355_st, getSignal_MRR_hmi5_355},
    {&p_MRR_hmi6_356_st, getSignal_MRR_hmi6_356},
    {&p_MPC_state_st, getSignal_MPC_state},
    {&p_MPC_hmi_st, getSignal_MPC_hmi},
    {&p_MPC_RoadState_359_st, getSignal_MPC_RoadState_359},
    {&p_MPC_hmi_35D_st, getSignal_MPC_hmi_35D},
    {&p_SRR_R_state_22B_st, getSignal_SRR_R_state_22B},
    {&p_ABM_state_st, getSignal_ABM_state},
    {&p_APA_35B_st, getSignal_APA_35B},
    {&p_VCU_state2_st, getSignal_VCU_state2},
    {&p_BLE_FB_st, getSignal_BLE_FB},
    {&p_BLE_User_ID_st, getSignal_BLE_User_ID},
    {&p_TBOX_Factory_360_st, getSignal_TBOX_Factory_360},
    {&p_AC_ctrlFeedback_st, getSignal_AC_ctrlFeedback},
    {&p_AC_state2_st, getSignal_AC_state2},
    {&p_BCM_state_st, getSignal_BCM_state},
    {&p_BCM_state2_st, getSignal_BCM_state2},
    {&p_BCM_state3_st, getSignal_BCM_state3},
    {&p_BCM_state4_st, getSignal_BCM_state4},
    {&p_BCM_tpms_st, getSignal_BCM_tpms},
    {&p_BCM_tpms1_st, getSignal_BCM_tpms1},
    {&p_BCM_peps_st, getSignal_BCM_peps},
    {&p_BCM_rsm_st, getSignal_BCM_rsm},
    {&p_BCM_RemotFB_st, getSignal_BCM_RemotFB},
    {&p_LCU_32A_st, getSignal_LCU_32A},
    {&p_PLG_state_st, getSignal_PLG_state},
    {&p_GW_Handle_state_st, getSignal_GW_Handle_state},
    {&p_DSM_state_st, getSignal_DSM_state},
    {&p_PSM_memory_st, getSignal_PSM_memory},
    {&p_DSM_memory_st, getSignal_DSM_memory},
    {&p_PSM_state_st, getSignal_PSM_state},
    {&p_LRSM_state_st, getSignal_LRSM_state},
    {&p_TBOX_infoCtrl_st, getSignal_TBOX_infoCtrl},
    {&p_GW_vent1Sts_st, getSignal_GW_vent1Sts},
    {&p_GW_vent2Sts_st, getSignal_GW_vent2Sts},
    {&p_GW_vent3Sts_st, getSignal_GW_vent3Sts},
    {&p_GW_vent4Sts_st, getSignal_GW_vent4Sts},
    {&p_GW_vent5Sts_st, getSignal_GW_vent5Sts},
    {&p_GW_vent6Sts_st, getSignal_GW_vent6Sts},
    {&p_GW_vent7Sts_st, getSignal_GW_vent7Sts},
    {&p_GW_vent8Sts_st, getSignal_GW_vent8Sts},
    {&p_GW_BMS_meas_st, getSignal_GW_BMS_meas},
    {&p_BMS_state_st, getSignal_BMS_state},
    {&p_GTW_mcur0_info_st, getSignal_GTW_mcur0_info},
    {&p_GTW_mcuf0_info_st, getSignal_GTW_mcuf0_info},
    {&p_GTW_ecu_gcu_vcu_info_st, getSignal_GTW_ecu_gcu_vcu_info},
    {&p_GTW_esc_eps_iB_info_st, getSignal_GTW_esc_eps_iB_info},
    {&p_GW_EPS_state_st, getSignal_GW_EPS_state},
    {&p_VCU_stateCha2_st, getSignal_VCU_stateCha2},
    {&p_AC_temp_pressure_st, getSignal_AC_temp_pressure},
    {&p_WCM_state_st, getSignal_WCM_state},
    {&p_AVM_state_484_st, getSignal_AVM_state_484},
    {&p_HUD_state_st, getSignal_HUD_state},
    {&p_MFW_Ctrl_st, getSignal_MFW_Ctrl},
    {&p_MFW_KeySt_st, getSignal_MFW_KeySt},
    {&p_IVI_timeAndGPS_st, getSignal_IVI_timeAndGPS},
    {&p_GTW_BMS_Rev_st, getSignal_GTW_BMS_Rev},
    {&p_Diag_PhyReq_IVI_st, getSignal_Diag_PhyReq_IVI},
    {&p_SWHC_400_st, getSignal_SWHC_400},
};

    void printlog(uint8_t* buf, uint8_t size)
    {
        #if USE_TEST
        int i = 0;
        SystemApiLogPrintf(LOG_INFO_OUTPUT, "--------------  send2soc size:%d\r\n", size);
        for (i; i < size; i++) {
            SystemApiLogPrintf(LOG_INFO_OUTPUT, "0x%x ", buf[i]);
        }
        SystemApiLogPrintf(LOG_INFO_OUTPUT, "\r\n");
        #endif
    }

    void Ivi_send2Soc(uint16_t event_id)
    {
        int size = 0;
        int sizeAll = 0;
        uint8_t buf[BUF_MAX_SIZE] = {0};
        int i = 0;
        int max_size = 0;
        Message msg;

        msg.event = event_id;
        max_size = SIG_PUB_MAX_SIZE;
    for (i; i < max_size; i++) {;
        STC_SIGNAL_INFO cursig = gPubSigInfo[i];
        if(TRUE == (*cursig.pSigFunc)()) {
                size = cursig.pSigStc[2] + 3;
                if ((sizeAll + size) <= BUF_MAX_SIZE) {
                    memcpy(&buf[sizeAll], cursig.pSigStc, size);
                    sizeAll += size;
                } else {
                    msg.len = sizeAll;
                    msg.lparam = (uint32_t)&buf[0];

                    if (IpcGetStatus() == true) {
                        printlog(buf, sizeAll);
                        SystemSendMessage(TASK_ID_IPC, msg);
                    }

                    sizeAll = 0;
                    memset(buf, 0, sizeof(buf));
                    memcpy(&buf[sizeAll], cursig.pSigStc, size);
                    sizeAll += size;
                }
            }
        }

        if (0 != sizeAll) {
            msg.len = sizeAll;
            msg.lparam = (uint32_t)&buf[0];

            if (IpcGetStatus() == true) {
                printlog(buf, sizeAll);
                SystemSendMessage(TASK_ID_IPC, msg);
            }
        }
    }

BOOL getSignal_TBOX_chargeSet(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x35F_st_TBOX_chargeSet signal_bk;
    memcpy(&signal_bk, &p_TBOX_chargeSet_st, sizeof(p_TBOX_chargeSet_st));

    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_VehicleRepairModeFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_VehicleRepairModeFB = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_VehicleRepairModeFB = 0;
    }
    p_TBOX_chargeSet_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_TBOX_VehiclePositioSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.TBOX_VehiclePositioSts = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.TBOX_VehiclePositioSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_ChargeEndTimeHour(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_ChargeEndTimeHour = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_ChargeEndTimeHour = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_ChargeEndTimeMinute(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_ChargeEndTimeMinute = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_ChargeEndTimeMinute = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_ChargeStartTimeHour(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_ChargeStartTimeHour = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_ChargeStartTimeHour = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_ChargeStartTimeMinute(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_ChargeStartTimeMinute = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_ChargeStartTimeMinute = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_MaxChargeSOCSet(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_MaxChargeSOCSet = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_MaxChargeSOCSet = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_ChargeEndTimeValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_ChargeEndTimeValid = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_ChargeEndTimeValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_chargeSet_ComIn_VeCAN_tbox_ChargeStartTimeValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_chargeSet_st.tbox_ChargeStartTimeValid = Read_Signal;
    } else {
        p_TBOX_chargeSet_st.tbox_ChargeStartTimeValid = 0;
    }

    if (memcmp(&signal_bk, &p_TBOX_chargeSet_st, sizeof(p_TBOX_chargeSet_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BMS_metric(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x514_st_BMS_metric signal_bk;
    memcpy(&signal_bk, &p_BMS_metric_st, sizeof(p_BMS_metric_st));

    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_SOC(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_SOC_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_metric_st.bms_SOC_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_SOC_H = 0;
        p_BMS_metric_st.bms_SOC_L = 0;
    }
    p_BMS_metric_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_SOH(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_SOH_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_metric_st.bms_SOH_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_SOH_H = 0;
        p_BMS_metric_st.bms_SOH_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_SOE(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_SOE_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_metric_st.bms_SOE_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_SOE_H = 0;
        p_BMS_metric_st.bms_SOE_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_SOCActual(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_SOCActual_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_metric_st.bms_SOCActual_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_SOCActual_H = 0;
        p_BMS_metric_st.bms_SOCActual_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_maxChargeSOC(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_maxChargeSOC = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_maxChargeSOC = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_BMS_BatterFaultLightContro(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.BMS_BatterFaultLightContro = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.BMS_BatterFaultLightContro = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_BMS_BatteryTempLowLight(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.BMS_BatteryTempLowLight = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.BMS_BatteryTempLowLight = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_BMS_NavigChrgPostFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.BMS_NavigChrgPostFB = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.BMS_NavigChrgPostFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_stEgyFlowSysDischRgn(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_stEgyFlowSysDischRgn = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_stEgyFlowSysDischRgn = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_stEgyFlowOBCAndBatt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_stEgyFlowOBCAndBatt = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_stEgyFlowOBCAndBatt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_metric_ComIn_VeCAN_bms_chargeFormstatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_metric_st.bms_chargeFormstatus = (uint8_t)(Read_Signal);
    } else {
        p_BMS_metric_st.bms_chargeFormstatus = 0;
    }

    if (memcmp(&signal_bk, &p_BMS_metric_st, sizeof(p_BMS_metric_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BMS_tboxRequest(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x574_st_BMS_tboxRequest signal_bk;
    memcpy(&signal_bk, &p_BMS_tboxRequest_st, sizeof(p_BMS_tboxRequest_st));

    bResult = Rte_Read_rpSR_CANMSG_BMS_tboxRequest_ComIn_VeCAN_bms_remainChargeTime(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_tboxRequest_st.bms_remainChargeTime_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_tboxRequest_st.bms_remainChargeTime_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_tboxRequest_st.bms_remainChargeTime_H = 0;
        p_BMS_tboxRequest_st.bms_remainChargeTime_L = 0;
    }
    p_BMS_tboxRequest_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_tboxRequest_ComIn_VeCAN_bms_ChgAmount(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_tboxRequest_st.bms_ChgAmount_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_tboxRequest_st.bms_ChgAmount_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_tboxRequest_st.bms_ChgAmount_H = 0;
        p_BMS_tboxRequest_st.bms_ChgAmount_L = 0;
    }

    if (memcmp(&signal_bk, &p_BMS_tboxRequest_st, sizeof(p_BMS_tboxRequest_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_range(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x561_st_VCU_range signal_bk;
    memcpy(&signal_bk, &p_VCU_range_st, sizeof(p_VCU_range_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_range_ComIn_VeCAN_vcu_avgPwr(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range_st.vcu_avgPwr_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_range_st.vcu_avgPwr_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range_st.vcu_avgPwr_H = 0;
        p_VCU_range_st.vcu_avgPwr_L = 0;
    }
    p_VCU_range_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range_ComIn_VeCAN_vcu_alertLevel(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range_st.vcu_alertLevel = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range_st.vcu_alertLevel = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range_ComIn_VeCAN_VCU_chargeFaultReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range_st.VCU_chargeFaultReason = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range_st.VCU_chargeFaultReason = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range_ComIn_VeCAN_VCU_RegenWeakRemind(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range_st.VCU_RegenWeakRemind = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range_st.VCU_RegenWeakRemind = 0;
    }

    if (memcmp(&signal_bk, &p_VCU_range_st, sizeof(p_VCU_range_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_range1(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x351_st_VCU_range1 signal_bk;
    memcpy(&signal_bk, &p_VCU_range1_st, sizeof(p_VCU_range1_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_vcu_remainingMileage(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.vcu_remainingMileage_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_range1_st.vcu_remainingMileage_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.vcu_remainingMileage_H = 0;
        p_VCU_range1_st.vcu_remainingMileage_L = 0;
    }
    p_VCU_range1_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_vcu_ComprehensiveRemainingMileage(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.vcu_ComprehensiveRemainingMileage_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_range1_st.vcu_ComprehensiveRemainingMileage_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.vcu_ComprehensiveRemainingMileage_H = 0;
        p_VCU_range1_st.vcu_ComprehensiveRemainingMileage_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_vcu_SysAlertLevel(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.vcu_SysAlertLevel = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.vcu_SysAlertLevel = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_VCU_PowerLimitLight(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.VCU_PowerLimitLight = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.VCU_PowerLimitLight = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_VCU_SysFaultLight(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.VCU_SysFaultLight = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.VCU_SysFaultLight = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_VCU_LVPowSupSYSAbn_lit(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.VCU_LVPowSupSYSAbn_lit = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.VCU_LVPowSupSYSAbn_lit = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_VCU_UserGearReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.VCU_UserGearReq = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.VCU_UserGearReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_VCU_PowerManageSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.VCU_PowerManageSt = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.VCU_PowerManageSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_range1_ComIn_VeCAN_vcu_PwroCrntTrip(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_range1_st.vcu_PwroCrntTrip_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_range1_st.vcu_PwroCrntTrip_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_range1_st.vcu_PwroCrntTrip_H = 0;
        p_VCU_range1_st.vcu_PwroCrntTrip_L = 0;
    }

    if (memcmp(&signal_bk, &p_VCU_range1_st, sizeof(p_VCU_range1_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_state(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x111_st_VCU_state signal_bk;
    memcpy(&signal_bk, &p_VCU_state_st, sizeof(p_VCU_state_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_state_ComIn_VeCAN_vcu_accelPos(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_state_st.vcu_accelPos_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_state_st.vcu_accelPos_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_state_st.vcu_accelPos_H = 0;
        p_VCU_state_st.vcu_accelPos_L = 0;
    }
    p_VCU_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_state_ComIn_VeCAN_vcu_BrakeWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_state_st.vcu_BrakeWarning = (uint8_t)(Read_Signal);
    } else {
        p_VCU_state_st.vcu_BrakeWarning = 0;
    }

    if (memcmp(&signal_bk, &p_VCU_state_st, sizeof(p_VCU_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_OBC_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x387_st_OBC_state signal_bk;
    memcpy(&signal_bk, &p_OBC_state_st, sizeof(p_OBC_state_st));

    bResult = Rte_Read_rpSR_CANMSG_OBC_state_ComIn_VeCAN_obc_CcResistance(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_OBC_state_st.obc_CcResistance = Read_Signal;
    } else {
        p_OBC_state_st.obc_CcResistance = 0;
    }
    p_OBC_state_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_OBC_state_st, sizeof(p_OBC_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_OBC_state1(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x407_st_OBC_state1 signal_bk;
    memcpy(&signal_bk, &p_OBC_state1_st, sizeof(p_OBC_state1_st));

    bResult = Rte_Read_rpSR_CANMSG_OBC_state1_ComIn_VeCAN_obc_DCVoltage(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_OBC_state1_st.obc_DCVoltage_H = (uint8_t)(Read_Signal >> 8);
        p_OBC_state1_st.obc_DCVoltage_L = (uint8_t)(Read_Signal);
    } else {
        p_OBC_state1_st.obc_DCVoltage_H = 0;
        p_OBC_state1_st.obc_DCVoltage_L = 0;
    }
    p_OBC_state1_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_OBC_state1_ComIn_VeCAN_obc_DCCurrent(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_OBC_state1_st.obc_DCCurrent_H = (uint8_t)(Read_Signal >> 8);
        p_OBC_state1_st.obc_DCCurrent_L = (uint8_t)(Read_Signal);
    } else {
        p_OBC_state1_st.obc_DCCurrent_H = 0;
        p_OBC_state1_st.obc_DCCurrent_L = 0;
    }

    if (memcmp(&signal_bk, &p_OBC_state1_st, sizeof(p_OBC_state1_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_DCDC_state(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x38D_st_DCDC_state signal_bk;
    memcpy(&signal_bk, &p_DCDC_state_st, sizeof(p_DCDC_state_st));

    bResult = Rte_Read_rpSR_CANMSG_DCDC_state_ComIn_VeCAN_dcdc_systemStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DCDC_state_st.dcdc_systemStatus = (uint8_t)(Read_Signal);
    } else {
        p_DCDC_state_st.dcdc_systemStatus = 0;
    }
    p_DCDC_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DCDC_state_ComIn_VeCAN_dcdc_deratingStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DCDC_state_st.dcdc_deratingStatus = (uint8_t)(Read_Signal);
    } else {
        p_DCDC_state_st.dcdc_deratingStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DCDC_state_ComIn_VeCAN_dcdc_realOutputCurrent(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DCDC_state_st.dcdc_realOutputCurrent_H = (uint8_t)(Read_Signal >> 8);
        p_DCDC_state_st.dcdc_realOutputCurrent_L = (uint8_t)(Read_Signal);
    } else {
        p_DCDC_state_st.dcdc_realOutputCurrent_H = 0;
        p_DCDC_state_st.dcdc_realOutputCurrent_L = 0;
    }

    if (memcmp(&signal_bk, &p_DCDC_state_st, sizeof(p_DCDC_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GSM_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x309_st_GSM_state signal_bk;
    memcpy(&signal_bk, &p_GSM_state_st, sizeof(p_GSM_state_st));

    bResult = Rte_Read_rpSR_CANMSG_GSM_state_ComIn_VeCAN_gsm_NoticeReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GSM_state_st.gsm_NoticeReq = Read_Signal;
    } else {
        p_GSM_state_st.gsm_NoticeReq = 0;
    }
    p_GSM_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GSM_state_ComIn_VeCAN_gsm_gearSelectorPos(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GSM_state_st.gsm_gearSelectorPos = Read_Signal;
    } else {
        p_GSM_state_st.gsm_gearSelectorPos = 0;
    }

    if (memcmp(&signal_bk, &p_GSM_state_st, sizeof(p_GSM_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GTW_mcur0_mcuf0_info(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x38A_st_GTW_mcur0_mcuf0_info signal_bk;
    memcpy(&signal_bk, &p_GTW_mcur0_mcuf0_info_st, sizeof(p_GTW_mcur0_mcuf0_info_st));

    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_mcuf0_info_ComIn_VeCAN_mcur0_torqueEst(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_mcuf0_info_st.mcur0_torqueEst_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcur0_mcuf0_info_st.mcur0_torqueEst_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_mcuf0_info_st.mcur0_torqueEst_H = 0;
        p_GTW_mcur0_mcuf0_info_st.mcur0_torqueEst_L = 0;
    }
    p_GTW_mcur0_mcuf0_info_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_mcuf0_info_ComIn_VeCAN_mcuf0_torqueEst(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_mcuf0_info_st.mcuf0_torqueEst_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcur0_mcuf0_info_st.mcuf0_torqueEst_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_mcuf0_info_st.mcuf0_torqueEst_H = 0;
        p_GTW_mcur0_mcuf0_info_st.mcuf0_torqueEst_L = 0;
    }

    if (memcmp(&signal_bk, &p_GTW_mcur0_mcuf0_info_st, sizeof(p_GTW_mcur0_mcuf0_info_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BMS_temperature(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x304_st_BMS_temperature signal_bk;
    memcpy(&signal_bk, &p_BMS_temperature_st, sizeof(p_BMS_temperature_st));

    bResult = Rte_Read_rpSR_CANMSG_BMS_temperature_ComIn_VeCAN_bms_packTempMax(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_temperature_st.bms_packTempMax_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_temperature_st.bms_packTempMax_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_temperature_st.bms_packTempMax_H = 0;
        p_BMS_temperature_st.bms_packTempMax_L = 0;
    }
    p_BMS_temperature_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_temperature_ComIn_VeCAN_bms_packTempMin(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_temperature_st.bms_packTempMin_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_temperature_st.bms_packTempMin_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_temperature_st.bms_packTempMin_H = 0;
        p_BMS_temperature_st.bms_packTempMin_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_temperature_ComIn_VeCAN_bms_packTempAvg(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_temperature_st.bms_packTempAvg_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_temperature_st.bms_packTempAvg_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_temperature_st.bms_packTempAvg_H = 0;
        p_BMS_temperature_st.bms_packTempAvg_L = 0;
    }

    if (memcmp(&signal_bk, &p_BMS_temperature_st, sizeof(p_BMS_temperature_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_Info(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x331_st_VCU_Info signal_bk;
    memcpy(&signal_bk, &p_VCU_Info_st, sizeof(p_VCU_Info_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_vcu_Rev_VehicleHVpower(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.vcu_Rev_VehicleHVpower_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_Info_st.vcu_Rev_VehicleHVpower_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.vcu_Rev_VehicleHVpower_H = 0;
        p_VCU_Info_st.vcu_Rev_VehicleHVpower_L = 0;
    }
    p_VCU_Info_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_vcu_stEgyFlowGenMotAndBatt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.vcu_stEgyFlowGenMotAndBatt = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.vcu_stEgyFlowGenMotAndBatt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_vcu_stEgyFlowEngAndGenMot(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.vcu_stEgyFlowEngAndGenMot = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.vcu_stEgyFlowEngAndGenMot = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_VCU_stEgyFlowMcuf0AndBatt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.VCU_stEgyFlowMcuf0AndBatt = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.VCU_stEgyFlowMcuf0AndBatt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_VCU_stEgyFlowMcur0AndBatt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.VCU_stEgyFlowMcur0AndBatt = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.VCU_stEgyFlowMcur0AndBatt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_VCU_IVI_HVDownRepairMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.VCU_IVI_HVDownRepairMode = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.VCU_IVI_HVDownRepairMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_VCU_LowSOC(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.VCU_LowSOC = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.VCU_LowSOC = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_vcu_obcDschrgAllow(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.vcu_obcDschrgAllow = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.vcu_obcDschrgAllow = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_Info_ComIn_VeCAN_vcu_obcDschrgFdbk(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_Info_st.vcu_obcDschrgFdbk = (uint8_t)(Read_Signal);
    } else {
        p_VCU_Info_st.vcu_obcDschrgFdbk = 0;
    }

    if (memcmp(&signal_bk, &p_VCU_Info_st, sizeof(p_VCU_Info_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_Diag_FuncReq(void)
{
    uint8_t bResult = FALSE;
    uint64_t Read_Signal = 0;
    struct package_0x7DF_st_Diag_FuncReq signal_bk;
    memcpy(&signal_bk, &p_Diag_FuncReq_st, sizeof(p_Diag_FuncReq_st));

    bResult = Rte_Read_rpSR_CANMSG_Diag_FuncReq_ComIn_VeCAN_Diag_FuncReq_Data(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_Diag_FuncReq_st.Diag_FuncReq_Data_8 = (uint8_t)(Read_Signal >> 56);
        p_Diag_FuncReq_st.Diag_FuncReq_Data_7 = (uint8_t)(Read_Signal >> 48);
        p_Diag_FuncReq_st.Diag_FuncReq_Data_6 = (uint8_t)(Read_Signal >> 40);
        p_Diag_FuncReq_st.Diag_FuncReq_Data_5 = (uint8_t)(Read_Signal >> 32);
        p_Diag_FuncReq_st.Diag_FuncReq_Data_4 = (uint8_t)(Read_Signal >> 24);
        p_Diag_FuncReq_st.Diag_FuncReq_Data_3 = (uint8_t)(Read_Signal >> 16);
        p_Diag_FuncReq_st.Diag_FuncReq_Data_2 = (uint8_t)(Read_Signal >> 8);
        p_Diag_FuncReq_st.Diag_FuncReq_Data_1 = (uint8_t)(Read_Signal);
    } else {
        p_Diag_FuncReq_st.Diag_FuncReq_Data_8 = 0;
        p_Diag_FuncReq_st.Diag_FuncReq_Data_7 = 0;
        p_Diag_FuncReq_st.Diag_FuncReq_Data_6 = 0;
        p_Diag_FuncReq_st.Diag_FuncReq_Data_5 = 0;
        p_Diag_FuncReq_st.Diag_FuncReq_Data_4 = 0;
        p_Diag_FuncReq_st.Diag_FuncReq_Data_3 = 0;
        p_Diag_FuncReq_st.Diag_FuncReq_Data_2 = 0;
        p_Diag_FuncReq_st.Diag_FuncReq_Data_1 = 0;
    }
    p_Diag_FuncReq_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_Diag_FuncReq_st, sizeof(p_Diag_FuncReq_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_pwr(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x301_st_VCU_pwr signal_bk;
    memcpy(&signal_bk, &p_VCU_pwr_st, sizeof(p_VCU_pwr_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_pwr_ComIn_VeCAN_vcu_avgPwrCurrentTrip(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_pwr_st.vcu_avgPwrCurrentTrip_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_pwr_st.vcu_avgPwrCurrentTrip_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_pwr_st.vcu_avgPwrCurrentTrip_H = 0;
        p_VCU_pwr_st.vcu_avgPwrCurrentTrip_L = 0;
    }
    p_VCU_pwr_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_pwr_ComIn_VeCAN_vcu_avgPwrSincelastcharge(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_pwr_st.vcu_avgPwrSincelastcharge_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_pwr_st.vcu_avgPwrSincelastcharge_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_pwr_st.vcu_avgPwrSincelastcharge_H = 0;
        p_VCU_pwr_st.vcu_avgPwrSincelastcharge_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_pwr_ComIn_VeCAN_vcu_avgPwroftripA(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_pwr_st.vcu_avgPwroftripA_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_pwr_st.vcu_avgPwroftripA_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_pwr_st.vcu_avgPwroftripA_H = 0;
        p_VCU_pwr_st.vcu_avgPwroftripA_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_pwr_ComIn_VeCAN_vcu_PwroftripB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_pwr_st.vcu_PwroftripB_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_pwr_st.vcu_PwroftripB_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_pwr_st.vcu_PwroftripB_H = 0;
        p_VCU_pwr_st.vcu_PwroftripB_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_pwr_ComIn_VeCAN_vcu_avgPwroftripB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_pwr_st.vcu_avgPwroftripB_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_pwr_st.vcu_avgPwroftripB_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_pwr_st.vcu_avgPwroftripB_H = 0;
        p_VCU_pwr_st.vcu_avgPwroftripB_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_pwr_ComIn_VeCAN_vcu_lowSocwarming(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_pwr_st.vcu_lowSocwarming = (uint8_t)(Read_Signal);
    } else {
        p_VCU_pwr_st.vcu_lowSocwarming = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_pwr_ComIn_VeCAN_VCU_SysFaulttext(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_pwr_st.VCU_SysFaulttext = (uint8_t)(Read_Signal);
    } else {
        p_VCU_pwr_st.VCU_SysFaulttext = 0;
    }

    if (memcmp(&signal_bk, &p_VCU_pwr_st, sizeof(p_VCU_pwr_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BMS_ASSt(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3A4_st_BMS_ASSt signal_bk;
    memcpy(&signal_bk, &p_BMS_ASSt_st, sizeof(p_BMS_ASSt_st));

    bResult = Rte_Read_rpSR_CANMSG_BMS_ASSt_ComIn_VeCAN_BMS_ThrmlRunawaySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_ASSt_st.BMS_ThrmlRunawaySt = Read_Signal;
    } else {
        p_BMS_ASSt_st.BMS_ThrmlRunawaySt = 0;
    }
    p_BMS_ASSt_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_ASSt_ComIn_VeCAN_BMS_ThrmlForecastersSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_ASSt_st.BMS_ThrmlForecastersSt = Read_Signal;
    } else {
        p_BMS_ASSt_st.BMS_ThrmlForecastersSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_ASSt_ComIn_VeCAN_BMS_AcFullChargeToWarmState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_ASSt_st.BMS_AcFullChargeToWarmState = Read_Signal;
    } else {
        p_BMS_ASSt_st.BMS_AcFullChargeToWarmState = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_ASSt_ComIn_VeCAN_BMS_3A4_RollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_ASSt_st.BMS_3A4_RollingCounter = Read_Signal;
    } else {
        p_BMS_ASSt_st.BMS_3A4_RollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_ASSt_ComIn_VeCAN_BMS_3A4_Checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_ASSt_st.BMS_3A4_Checksum = Read_Signal;
    } else {
        p_BMS_ASSt_st.BMS_3A4_Checksum = 0;
    }

    if (memcmp(&signal_bk, &p_BMS_ASSt_st, sizeof(p_BMS_ASSt_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_stateCha1(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3A1_st_VCU_stateCha1 signal_bk;
    memcpy(&signal_bk, &p_VCU_stateCha1_st, sizeof(p_VCU_stateCha1_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_driveMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_driveMode = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_driveMode = 0;
    }
    p_VCU_stateCha1_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_SuperPowerSavingModeSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_SuperPowerSavingModeSt = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_SuperPowerSavingModeSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_SuperPowerSavingModeReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_SuperPowerSavingModeReq = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_SuperPowerSavingModeReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_PercentInstantaneousPower(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_PercentInstantaneousPower = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_PercentInstantaneousPower = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_SuperPowerSavingModeFaultReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_SuperPowerSavingModeFaultReason = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_SuperPowerSavingModeFaultReason = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_towMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_towMode = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_towMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_ready(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_ready = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_ready = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_traveModeSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_traveModeSts = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_traveModeSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_highVoltagefaultSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_highVoltagefaultSts = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_highVoltagefaultSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_VehicleRepairModeFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_VehicleRepairModeFB = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_VehicleRepairModeFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_CampModeSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_CampModeSts = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_CampModeSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_RegenModeStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_RegenModeStatus = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_RegenModeStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_highVoltageSuccess(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_highVoltageSuccess = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_highVoltageSuccess = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_hvOnMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_hvOnMode = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_hvOnMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_VehicleMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_VehicleMode = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_VehicleMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_memoryStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_memoryStatus = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_memoryStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_ExhibitionRequest(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_ExhibitionRequest = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_ExhibitionRequest = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_VCU_TrailerModeSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.VCU_TrailerModeSts = Read_Signal;
    } else {
        p_VCU_stateCha1_st.VCU_TrailerModeSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha1_ComIn_VeCAN_vcu_ExhibitionMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha1_st.vcu_ExhibitionMode = Read_Signal;
    } else {
        p_VCU_stateCha1_st.vcu_ExhibitionMode = 0;
    }

    if (memcmp(&signal_bk, &p_VCU_stateCha1_st, sizeof(p_VCU_stateCha1_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_EPS_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x124_st_EPS_state signal_bk;
    memcpy(&signal_bk, &p_EPS_state_st, sizeof(p_EPS_state_st));

    bResult = Rte_Read_rpSR_CANMSG_EPS_state_ComIn_VeCAN_eps_warningLamp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_state_st.eps_warningLamp = Read_Signal;
    } else {
        p_EPS_state_st.eps_warningLamp = 0;
    }
    p_EPS_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_EPS_state_ComIn_VeCAN_eps_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_state_st.eps_rollingCounter = Read_Signal;
    } else {
        p_EPS_state_st.eps_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_EPS_state_ComIn_VeCAN_eps_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_state_st.eps_checksum = Read_Signal;
    } else {
        p_EPS_state_st.eps_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_EPS_state_st, sizeof(p_EPS_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_EPS_sas(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x144_st_EPS_sas signal_bk;
    memcpy(&signal_bk, &p_EPS_sas_st, sizeof(p_EPS_sas_st));

    bResult = Rte_Read_rpSR_CANMSG_EPS_sas_ComIn_VeCAN_eps_sasSteeringAngle(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_sas_st.eps_sasSteeringAngle_H = (uint8_t)(Read_Signal >> 8);
        p_EPS_sas_st.eps_sasSteeringAngle_L = (uint8_t)(Read_Signal);
    } else {
        p_EPS_sas_st.eps_sasSteeringAngle_H = 0;
        p_EPS_sas_st.eps_sasSteeringAngle_L = 0;
    }
    p_EPS_sas_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_EPS_sas_ComIn_VeCAN_eps_sasRawSteeringAngle(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_sas_st.eps_sasRawSteeringAngle_H = (uint8_t)(Read_Signal >> 8);
        p_EPS_sas_st.eps_sasRawSteeringAngle_L = (uint8_t)(Read_Signal);
    } else {
        p_EPS_sas_st.eps_sasRawSteeringAngle_H = 0;
        p_EPS_sas_st.eps_sasRawSteeringAngle_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_EPS_sas_ComIn_VeCAN_eps_sasSteeringAngleSpd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_sas_st.eps_sasSteeringAngleSpd_H = (uint8_t)(Read_Signal >> 8);
        p_EPS_sas_st.eps_sasSteeringAngleSpd_L = (uint8_t)(Read_Signal);
    } else {
        p_EPS_sas_st.eps_sasSteeringAngleSpd_H = 0;
        p_EPS_sas_st.eps_sasSteeringAngleSpd_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_EPS_sas_ComIn_VeCAN_eps_sasSteeringAngleSpdValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_sas_st.eps_sasSteeringAngleSpdValid = (uint8_t)(Read_Signal);
    } else {
        p_EPS_sas_st.eps_sasSteeringAngleSpdValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_EPS_sas_ComIn_VeCAN_eps_calibratedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_sas_st.eps_calibratedStatus = (uint8_t)(Read_Signal);
    } else {
        p_EPS_sas_st.eps_calibratedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_EPS_sas_ComIn_VeCAN_eps_sasSteeringAngleValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_EPS_sas_st.eps_sasSteeringAngleValid = (uint8_t)(Read_Signal);
    } else {
        p_EPS_sas_st.eps_sasSteeringAngleValid = 0;
    }

    if (memcmp(&signal_bk, &p_EPS_sas_st, sizeof(p_EPS_sas_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_wheelSpd_Front(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x142_st_ESC_wheelSpd_Front signal_bk;
    memcpy(&signal_bk, &p_ESC_wheelSpd_Front_st, sizeof(p_ESC_wheelSpd_Front_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Front_ComIn_VeCAN_esc_wheelSpeedFL(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFL_H = (uint8_t)(Read_Signal >> 8);
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFL_L = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFL_H = 0;
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFL_L = 0;
    }
    p_ESC_wheelSpd_Front_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Front_ComIn_VeCAN_esc_wheelSpeedFLValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFLValid = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFLValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Front_ComIn_VeCAN_esc_wheelSpeedFR(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFR_H = (uint8_t)(Read_Signal >> 8);
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFR_L = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFR_H = 0;
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFR_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Front_ComIn_VeCAN_esc_wheelSpeedFRValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFRValid = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Front_st.esc_wheelSpeedFRValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Front_ComIn_VeCAN_esc_142_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Front_st.esc_142_rollingCounter = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Front_st.esc_142_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Front_ComIn_VeCAN_esc_142_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Front_st.esc_142_checksum = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Front_st.esc_142_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_wheelSpd_Front_st, sizeof(p_ESC_wheelSpd_Front_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_wheelSpd_Rear(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x122_st_ESC_wheelSpd_Rear signal_bk;
    memcpy(&signal_bk, &p_ESC_wheelSpd_Rear_st, sizeof(p_ESC_wheelSpd_Rear_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Rear_ComIn_VeCAN_esc_wheelSpeedRL(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRL_H = (uint8_t)(Read_Signal >> 8);
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRL_L = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRL_H = 0;
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRL_L = 0;
    }
    p_ESC_wheelSpd_Rear_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Rear_ComIn_VeCAN_esc_wheelSpeedRLValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRLValid = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRLValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Rear_ComIn_VeCAN_esc_wheelSpeedRR(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRR_H = (uint8_t)(Read_Signal >> 8);
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRR_L = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRR_H = 0;
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRR_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Rear_ComIn_VeCAN_esc_wheelSpeedRRValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRRValid = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Rear_st.esc_wheelSpeedRRValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Rear_ComIn_VeCAN_esc_122_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Rear_st.esc_122_rollingCounter = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Rear_st.esc_122_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wheelSpd_Rear_ComIn_VeCAN_esc_122_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wheelSpd_Rear_st.esc_122_checksum = (uint8_t)(Read_Signal);
    } else {
        p_ESC_wheelSpd_Rear_st.esc_122_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_wheelSpd_Rear_st, sizeof(p_ESC_wheelSpd_Rear_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_state1(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x212_st_ESC_state1 signal_bk;
    memcpy(&signal_bk, &p_ESC_state1_st, sizeof(p_ESC_state1_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_vehicleSpeed(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_vehicleSpeed_H = (uint8_t)(Read_Signal >> 8);
        p_ESC_state1_st.esc_vehicleSpeed_L = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_vehicleSpeed_H = 0;
        p_ESC_state1_st.esc_vehicleSpeed_L = 0;
    }
    p_ESC_state1_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_vehicleSpeedValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_vehicleSpeedValid = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_vehicleSpeedValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_absFault(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_absFault = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_absFault = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_absActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_absActive = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_absActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_escActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_escActive = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_escActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_tcsActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_tcsActive = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_tcsActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_avhActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_avhActive = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_avhActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_avhStandby(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_avhStandby = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_avhStandby = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_avhAvailable(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_avhAvailable = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_avhAvailable = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_cdpActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_cdpActive = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_cdpActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_hdcStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_hdcStatus = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_hdcStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_hdcAvailable(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_hdcAvailable = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_hdcAvailable = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_hhcAvailable(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_hhcAvailable = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_hhcAvailable = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_ebdFault(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_ebdFault = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_ebdFault = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_offStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_offStatus = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_offStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_escFault(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_escFault = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_escFault = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_emergencyBrakeSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_emergencyBrakeSts = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_emergencyBrakeSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_212_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_212_rollingCounter = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_212_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state1_ComIn_VeCAN_esc_212_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state1_st.esc_212_checksum = (uint8_t)(Read_Signal);
    } else {
        p_ESC_state1_st.esc_212_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_state1_st, sizeof(p_ESC_state1_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_state2(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x2A2_st_ESC_state2 signal_bk;
    memcpy(&signal_bk, &p_ESC_state2_st, sizeof(p_ESC_state2_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_state2_ComIn_VeCAN_esc_hmiWarningOn(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state2_st.esc_hmiWarningOn = Read_Signal;
    } else {
        p_ESC_state2_st.esc_hmiWarningOn = 0;
    }
    p_ESC_state2_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state2_ComIn_VeCAN_esc_2A2_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state2_st.esc_2A2_rollingCounter = Read_Signal;
    } else {
        p_ESC_state2_st.esc_2A2_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_state2_ComIn_VeCAN_esc_2A2_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_state2_st.esc_2A2_checksum = Read_Signal;
    } else {
        p_ESC_state2_st.esc_2A2_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_state2_st, sizeof(p_ESC_state2_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_yawState(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x252_st_ESC_yawState signal_bk;
    memcpy(&signal_bk, &p_ESC_yawState_st, sizeof(p_ESC_yawState_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_yawState_ComIn_VeCAN_esc_longAcceleration(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_yawState_st.esc_longAcceleration_H = (uint8_t)(Read_Signal >> 8);
        p_ESC_yawState_st.esc_longAcceleration_L = (uint8_t)(Read_Signal);
    } else {
        p_ESC_yawState_st.esc_longAcceleration_H = 0;
        p_ESC_yawState_st.esc_longAcceleration_L = 0;
    }
    p_ESC_yawState_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_yawState_ComIn_VeCAN_esc_longAccelerationValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_yawState_st.esc_longAccelerationValid = (uint8_t)(Read_Signal);
    } else {
        p_ESC_yawState_st.esc_longAccelerationValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_yawState_ComIn_VeCAN_esc_yawRateValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_yawState_st.esc_yawRateValid = (uint8_t)(Read_Signal);
    } else {
        p_ESC_yawState_st.esc_yawRateValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_yawState_ComIn_VeCAN_esc_yawRate(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_yawState_st.esc_yawRate_H = (uint8_t)(Read_Signal >> 8);
        p_ESC_yawState_st.esc_yawRate_L = (uint8_t)(Read_Signal);
    } else {
        p_ESC_yawState_st.esc_yawRate_H = 0;
        p_ESC_yawState_st.esc_yawRate_L = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_yawState_st, sizeof(p_ESC_yawState_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_ESC_yawState(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3FB_st_GW_ESC_yawState signal_bk;
    memcpy(&signal_bk, &p_GW_ESC_yawState_st, sizeof(p_GW_ESC_yawState_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_ESC_yawState_ComIn_VeCAN_apa_funcSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_ESC_yawState_st.apa_funcSts = Read_Signal;
    } else {
        p_GW_ESC_yawState_st.apa_funcSts = 0;
    }
    p_GW_ESC_yawState_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_ESC_yawState_ComIn_VeCAN_APA_laeb_BrkReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_ESC_yawState_st.APA_laeb_BrkReq = Read_Signal;
    } else {
        p_GW_ESC_yawState_st.APA_laeb_BrkReq = 0;
    }

    if (memcmp(&signal_bk, &p_GW_ESC_yawState_st, sizeof(p_GW_ESC_yawState_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_wssFront(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x272_st_ESC_wssFront signal_bk;
    memcpy(&signal_bk, &p_ESC_wssFront_st, sizeof(p_ESC_wssFront_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_wssFront_ComIn_VeCAN_esc_wheelDirectionFLValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssFront_st.esc_wheelDirectionFLValid = Read_Signal;
    } else {
        p_ESC_wssFront_st.esc_wheelDirectionFLValid = 0;
    }
    p_ESC_wssFront_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssFront_ComIn_VeCAN_esc_wheelDirectionFRValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssFront_st.esc_wheelDirectionFRValid = Read_Signal;
    } else {
        p_ESC_wssFront_st.esc_wheelDirectionFRValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssFront_ComIn_VeCAN_esc_wheelDirectionFL(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssFront_st.esc_wheelDirectionFL = Read_Signal;
    } else {
        p_ESC_wssFront_st.esc_wheelDirectionFL = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssFront_ComIn_VeCAN_esc_wheelDirectionFR(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssFront_st.esc_wheelDirectionFR = Read_Signal;
    } else {
        p_ESC_wssFront_st.esc_wheelDirectionFR = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssFront_ComIn_VeCAN_esc_272_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssFront_st.esc_272_rollingCounter = Read_Signal;
    } else {
        p_ESC_wssFront_st.esc_272_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssFront_ComIn_VeCAN_esc_272_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssFront_st.esc_272_checksum = Read_Signal;
    } else {
        p_ESC_wssFront_st.esc_272_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_wssFront_st, sizeof(p_ESC_wssFront_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_wssRear(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x282_st_ESC_wssRear signal_bk;
    memcpy(&signal_bk, &p_ESC_wssRear_st, sizeof(p_ESC_wssRear_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_wssRear_ComIn_VeCAN_esc_wheelDirectionRLValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssRear_st.esc_wheelDirectionRLValid = Read_Signal;
    } else {
        p_ESC_wssRear_st.esc_wheelDirectionRLValid = 0;
    }
    p_ESC_wssRear_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssRear_ComIn_VeCAN_esc_wheelDirectionRRValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssRear_st.esc_wheelDirectionRRValid = Read_Signal;
    } else {
        p_ESC_wssRear_st.esc_wheelDirectionRRValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssRear_ComIn_VeCAN_esc_wheelDirectionRL(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssRear_st.esc_wheelDirectionRL = Read_Signal;
    } else {
        p_ESC_wssRear_st.esc_wheelDirectionRL = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_wssRear_ComIn_VeCAN_esc_wheelDirectionRR(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_wssRear_st.esc_wheelDirectionRR = Read_Signal;
    } else {
        p_ESC_wssRear_st.esc_wheelDirectionRR = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_wssRear_st, sizeof(p_ESC_wssRear_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ESC_epb(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x2C2_st_ESC_epb signal_bk;
    memcpy(&signal_bk, &p_ESC_epb_st, sizeof(p_ESC_epb_st));

    bResult = Rte_Read_rpSR_CANMSG_ESC_epb_ComIn_VeCAN_esc_epbFaultLamp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_epb_st.esc_epbFaultLamp = Read_Signal;
    } else {
        p_ESC_epb_st.esc_epbFaultLamp = 0;
    }
    p_ESC_epb_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_epb_ComIn_VeCAN_esc_epbParkingLamp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_epb_st.esc_epbParkingLamp = Read_Signal;
    } else {
        p_ESC_epb_st.esc_epbParkingLamp = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_epb_ComIn_VeCAN_esc_epbTextDisplay(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_epb_st.esc_epbTextDisplay = Read_Signal;
    } else {
        p_ESC_epb_st.esc_epbTextDisplay = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_epb_ComIn_VeCAN_esc_epbStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_epb_st.esc_epbStatus = Read_Signal;
    } else {
        p_ESC_epb_st.esc_epbStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_epb_ComIn_VeCAN_ESC_BrakeLevelAlarm(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_epb_st.ESC_BrakeLevelAlarm = Read_Signal;
    } else {
        p_ESC_epb_st.ESC_BrakeLevelAlarm = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_epb_ComIn_VeCAN_esc_2C2_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_epb_st.esc_2C2_rollingCounter = Read_Signal;
    } else {
        p_ESC_epb_st.esc_2C2_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ESC_epb_ComIn_VeCAN_esc_2C2_checkSum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ESC_epb_st.esc_2C2_checkSum = Read_Signal;
    } else {
        p_ESC_epb_st.esc_2C2_checkSum = 0;
    }

    if (memcmp(&signal_bk, &p_ESC_epb_st, sizeof(p_ESC_epb_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_acc(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x219_st_MRR_acc signal_bk;
    memcpy(&signal_bk, &p_MRR_acc_st, sizeof(p_MRR_acc_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_acc_ComIn_VeCAN_mrr_accMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_acc_st.mrr_accMode = Read_Signal;
    } else {
        p_MRR_acc_st.mrr_accMode = 0;
    }
    p_MRR_acc_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_acc_ComIn_VeCAN_mrr_RCTBOnOffStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_acc_st.mrr_RCTBOnOffStatus = Read_Signal;
    } else {
        p_MRR_acc_st.mrr_RCTBOnOffStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_acc_ComIn_VeCAN_mrr_219_RollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_acc_st.mrr_219_RollingCounter = Read_Signal;
    } else {
        p_MRR_acc_st.mrr_219_RollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_acc_ComIn_VeCAN_mrr_219_CheckSum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_acc_st.mrr_219_CheckSum = Read_Signal;
    } else {
        p_MRR_acc_st.mrr_219_CheckSum = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_acc_st, sizeof(p_MRR_acc_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_pss(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x239_st_MRR_pss signal_bk;
    memcpy(&signal_bk, &p_MRR_pss_st, sizeof(p_MRR_pss_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_EBAReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_EBAReq = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_EBAReq = 0;
    }
    p_MRR_pss_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_aebReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_aebReq = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_aebReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_aebOnOffStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_aebOnOffStatus = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_aebOnOffStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_accTakeOverReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_accTakeOverReq = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_accTakeOverReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_vSetDis(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_vSetDis_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_pss_st.mrr_vSetDis_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_vSetDis_H = 0;
        p_MRR_pss_st.mrr_vSetDis_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_PEBSWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_PEBSWarning = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_PEBSWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_timeGapSet(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_timeGapSet = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_timeGapSet = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_pcwOnOffStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_pcwOnOffStatus = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_pcwOnOffStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_textInfo(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_textInfo = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_textInfo = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_BlockedSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_BlockedSt = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_BlockedSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_SystemFailureSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_SystemFailureSt = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_SystemFailureSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_239_RollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_239_RollingCounter = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_239_RollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_pss_ComIn_VeCAN_mrr_239_CheckSum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_pss_st.mrr_239_CheckSum = (uint8_t)(Read_Signal);
    } else {
        p_MRR_pss_st.mrr_239_CheckSum = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_pss_st, sizeof(p_MRR_pss_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_hmi1(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x349_st_MRR_hmi1 signal_bk;
    memcpy(&signal_bk, &p_MRR_hmi1_st, sizeof(p_MRR_hmi1_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi1_ComIn_VeCAN_mrr_ACC_TargetType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi1_st.mrr_ACC_TargetType = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi1_st.mrr_ACC_TargetType = 0;
    }
    p_MRR_hmi1_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi1_ComIn_VeCAN_mrr_ACC_TargetDetection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi1_st.mrr_ACC_TargetDetection = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi1_st.mrr_ACC_TargetDetection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi1_ComIn_VeCAN_mrr_ACC_TargetRange(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi1_st.mrr_ACC_TargetRange_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi1_st.mrr_ACC_TargetRange_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi1_st.mrr_ACC_TargetRange_H = 0;
        p_MRR_hmi1_st.mrr_ACC_TargetRange_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi1_ComIn_VeCAN_mrr_ACC_RelevantTargetLatRange(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi1_st.mrr_ACC_RelevantTargetLatRange_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi1_st.mrr_ACC_RelevantTargetLatRange_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi1_st.mrr_ACC_RelevantTargetLatRange_H = 0;
        p_MRR_hmi1_st.mrr_ACC_RelevantTargetLatRange_L = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_hmi1_st, sizeof(p_MRR_hmi1_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_hmi2(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x369_st_MRR_hmi2 signal_bk;
    memcpy(&signal_bk, &p_MRR_hmi2_st, sizeof(p_MRR_hmi2_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_LeftTargetType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetType = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetType = 0;
    }
    p_MRR_hmi2_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_LeftTargetDetection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetDetection = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetDetection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_LeftTargetLngRange(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLngRange_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLngRange_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLngRange_H = 0;
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLngRange_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_LeftTargetLatRange(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLatRange_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLatRange_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLatRange_H = 0;
        p_MRR_hmi2_st.mrr_ACC_LeftTargetLatRange_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_RightTargetType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_RightTargetType = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_RightTargetType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_RightTargetLngRange(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_RightTargetLngRange_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi2_st.mrr_ACC_RightTargetLngRange_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_RightTargetLngRange_H = 0;
        p_MRR_hmi2_st.mrr_ACC_RightTargetLngRange_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_RightTargetLatRange(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_RightTargetLatRange_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi2_st.mrr_ACC_RightTargetLatRange_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_RightTargetLatRange_H = 0;
        p_MRR_hmi2_st.mrr_ACC_RightTargetLatRange_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi2_ComIn_VeCAN_mrr_ACC_RightTargetDetection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi2_st.mrr_ACC_RightTargetDetection = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi2_st.mrr_ACC_RightTargetDetection = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_hmi2_st, sizeof(p_MRR_hmi2_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_hmi3_34E(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x34E_st_MRR_hmi3_34E signal_bk;
    memcpy(&signal_bk, &p_MRR_hmi3_34E_st, sizeof(p_MRR_hmi3_34E_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi3_34E_ComIn_VeCAN_mrr_ACC_TargetType2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi3_34E_st.mrr_ACC_TargetType2 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi3_34E_st.mrr_ACC_TargetType2 = 0;
    }
    p_MRR_hmi3_34E_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi3_34E_ComIn_VeCAN_mrr_ACC_TargetDetection2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi3_34E_st.mrr_ACC_TargetDetection2 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi3_34E_st.mrr_ACC_TargetDetection2 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi3_34E_ComIn_VeCAN_mrr_ACC_TargetRange2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi3_34E_st.mrr_ACC_TargetRange2_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi3_34E_st.mrr_ACC_TargetRange2_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi3_34E_st.mrr_ACC_TargetRange2_H = 0;
        p_MRR_hmi3_34E_st.mrr_ACC_TargetRange2_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi3_34E_ComIn_VeCAN_mrr_ACC_RelevantTargetLatRange2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi3_34E_st.mrr_ACC_RelevantTargetLatRange2_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi3_34E_st.mrr_ACC_RelevantTargetLatRange2_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi3_34E_st.mrr_ACC_RelevantTargetLatRange2_H = 0;
        p_MRR_hmi3_34E_st.mrr_ACC_RelevantTargetLatRange2_L = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_hmi3_34E_st, sizeof(p_MRR_hmi3_34E_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_hmi4_34F(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x34F_st_MRR_hmi4_34F signal_bk;
    memcpy(&signal_bk, &p_MRR_hmi4_34F_st, sizeof(p_MRR_hmi4_34F_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_LeftTargetType2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetType2 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetType2 = 0;
    }
    p_MRR_hmi4_34F_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_LeftTargetDetection2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetDetection2 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetDetection2 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_LeftTargetLngRange2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLngRange2_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLngRange2_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLngRange2_H = 0;
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLngRange2_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_LeftTargetLatRange2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLatRange2_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLatRange2_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLatRange2_H = 0;
        p_MRR_hmi4_34F_st.mrr_ACC_LeftTargetLatRange2_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_RightTargetType2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetType2 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetType2 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_RightTargetLngRange2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLngRange2_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLngRange2_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLngRange2_H = 0;
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLngRange2_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_RightTargetLatRange2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLatRange2_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLatRange2_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLatRange2_H = 0;
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetLatRange2_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi4_34F_ComIn_VeCAN_mrr_ACC_RightTargetDetection2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetDetection2 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi4_34F_st.mrr_ACC_RightTargetDetection2 = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_hmi4_34F_st, sizeof(p_MRR_hmi4_34F_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_hmi5_355(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x355_st_MRR_hmi5_355 signal_bk;
    memcpy(&signal_bk, &p_MRR_hmi5_355_st, sizeof(p_MRR_hmi5_355_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi5_355_ComIn_VeCAN_mrr_ACC_TargetType3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi5_355_st.mrr_ACC_TargetType3 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi5_355_st.mrr_ACC_TargetType3 = 0;
    }
    p_MRR_hmi5_355_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi5_355_ComIn_VeCAN_mrr_ACC_TargetDetection3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi5_355_st.mrr_ACC_TargetDetection3 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi5_355_st.mrr_ACC_TargetDetection3 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi5_355_ComIn_VeCAN_mrr_ACC_TargetRange3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi5_355_st.mrr_ACC_TargetRange3_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi5_355_st.mrr_ACC_TargetRange3_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi5_355_st.mrr_ACC_TargetRange3_H = 0;
        p_MRR_hmi5_355_st.mrr_ACC_TargetRange3_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi5_355_ComIn_VeCAN_mrr_ACC_RelevantTargetLatRange3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi5_355_st.mrr_ACC_RelevantTargetLatRange3_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi5_355_st.mrr_ACC_RelevantTargetLatRange3_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi5_355_st.mrr_ACC_RelevantTargetLatRange3_H = 0;
        p_MRR_hmi5_355_st.mrr_ACC_RelevantTargetLatRange3_L = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_hmi5_355_st, sizeof(p_MRR_hmi5_355_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MRR_hmi6_356(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x356_st_MRR_hmi6_356 signal_bk;
    memcpy(&signal_bk, &p_MRR_hmi6_356_st, sizeof(p_MRR_hmi6_356_st));

    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_LeftTargetType3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetType3 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetType3 = 0;
    }
    p_MRR_hmi6_356_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_LeftTargetDetection3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetDetection3 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetDetection3 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_LeftTargetLngRange3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLngRange3_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLngRange3_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLngRange3_H = 0;
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLngRange3_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_LeftTargetLatRange3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLatRange3_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLatRange3_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLatRange3_H = 0;
        p_MRR_hmi6_356_st.mrr_ACC_LeftTargetLatRange3_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_RightTargetType3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetType3 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetType3 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_RightTargetLngRange3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLngRange3_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLngRange3_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLngRange3_H = 0;
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLngRange3_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_RightTargetLatRange3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLatRange3_H = (uint8_t)(Read_Signal >> 8);
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLatRange3_L = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLatRange3_H = 0;
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetLatRange3_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MRR_hmi6_356_ComIn_VeCAN_mrr_ACC_RightTargetDetection3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetDetection3 = (uint8_t)(Read_Signal);
    } else {
        p_MRR_hmi6_356_st.mrr_ACC_RightTargetDetection3 = 0;
    }

    if (memcmp(&signal_bk, &p_MRR_hmi6_356_st, sizeof(p_MRR_hmi6_356_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MPC_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x21A_st_MPC_state signal_bk;
    memcpy(&signal_bk, &p_MPC_state_st, sizeof(p_MPC_state_st));

    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_leftVisualization(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_leftVisualization = Read_Signal;
    } else {
        p_MPC_state_st.mpc_leftVisualization = 0;
    }
    p_MPC_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_rightVisualization(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_rightVisualization = Read_Signal;
    } else {
        p_MPC_state_st.mpc_rightVisualization = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_laneAssitType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_laneAssitType = Read_Signal;
    } else {
        p_MPC_state_st.mpc_laneAssitType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_slaSpeedLimitUnits(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_slaSpeedLimitUnits = Read_Signal;
    } else {
        p_MPC_state_st.mpc_slaSpeedLimitUnits = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_lasStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_lasStatus = Read_Signal;
    } else {
        p_MPC_state_st.mpc_lasStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_lasWarningModeSelection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_lasWarningModeSelection = Read_Signal;
    } else {
        p_MPC_state_st.mpc_lasWarningModeSelection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_adasTakeoverReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_adasTakeoverReq = Read_Signal;
    } else {
        p_MPC_state_st.mpc_adasTakeoverReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_IACCStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_IACCStatus = Read_Signal;
    } else {
        p_MPC_state_st.mpc_IACCStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_hmaStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_hmaStatus = Read_Signal;
    } else {
        p_MPC_state_st.mpc_hmaStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_hmaHighbeamReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_hmaHighbeamReq = Read_Signal;
    } else {
        p_MPC_state_st.mpc_hmaHighbeamReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_slaStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_slaStatus = Read_Signal;
    } else {
        p_MPC_state_st.mpc_slaStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_slaSpeedLimit(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_slaSpeedLimit = Read_Signal;
    } else {
        p_MPC_state_st.mpc_slaSpeedLimit = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_slaOnOffSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_slaOnOffSts = Read_Signal;
    } else {
        p_MPC_state_st.mpc_slaOnOffSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_hmaOnOffSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_hmaOnOffSts = Read_Signal;
    } else {
        p_MPC_state_st.mpc_hmaOnOffSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_rollingCounter = Read_Signal;
    } else {
        p_MPC_state_st.mpc_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_state_ComIn_VeCAN_mpc_checkSum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_state_st.mpc_checkSum = Read_Signal;
    } else {
        p_MPC_state_st.mpc_checkSum = 0;
    }

    if (memcmp(&signal_bk, &p_MPC_state_st, sizeof(p_MPC_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MPC_hmi(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x35A_st_MPC_hmi signal_bk;
    memcpy(&signal_bk, &p_MPC_hmi_st, sizeof(p_MPC_hmi_st));

    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_mpc_LAS_roadCurvature(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.mpc_LAS_roadCurvature = Read_Signal;
    } else {
        p_MPC_hmi_st.mpc_LAS_roadCurvature = 0;
    }
    p_MPC_hmi_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_mpc_LAS_LLaneDistance(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.mpc_LAS_LLaneDistance = Read_Signal;
    } else {
        p_MPC_hmi_st.mpc_LAS_LLaneDistance = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_mpc_LAS_RLaneDistance(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.mpc_LAS_RLaneDistance = Read_Signal;
    } else {
        p_MPC_hmi_st.mpc_LAS_RLaneDistance = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_mpc_LAS_LLaneMarkerType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.mpc_LAS_LLaneMarkerType = Read_Signal;
    } else {
        p_MPC_hmi_st.mpc_LAS_LLaneMarkerType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_mpc_LAS_RLaneMarkerType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.mpc_LAS_RLaneMarkerType = Read_Signal;
    } else {
        p_MPC_hmi_st.mpc_LAS_RLaneMarkerType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_FrontCameraeStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_FrontCameraeStatus = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_FrontCameraeStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_textinfor(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_textinfor = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_textinfor = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_TJAonoffStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_TJAonoffStatus = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_TJAonoffStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_LLLaneMarkerType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_LLLaneMarkerType = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_LLLaneMarkerType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_LLLaneDistance(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_LLLaneDistance = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_LLLaneDistance = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_RRLaneDistance(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_RRLaneDistance = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_RRLaneDistance = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_RRLaneMarkerType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_RRLaneMarkerType = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_RRLaneMarkerType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_LleftVisualization(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_LleftVisualization = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_LleftVisualization = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_RrightVisualization(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_RrightVisualization = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_RrightVisualization = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_ComIn_VeCAN_MPC_autododgeOnOffSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_st.MPC_autododgeOnOffSts = Read_Signal;
    } else {
        p_MPC_hmi_st.MPC_autododgeOnOffSts = 0;
    }

    if (memcmp(&signal_bk, &p_MPC_hmi_st, sizeof(p_MPC_hmi_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MPC_RoadState_359(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x359_st_MPC_RoadState_359 signal_bk;
    memcpy(&signal_bk, &p_MPC_RoadState_359_st, sizeof(p_MPC_RoadState_359_st));

    bResult = Rte_Read_rpSR_CANMSG_MPC_RoadState_359_ComIn_VeCAN_MPC_LaneEquationC1(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_RoadState_359_st.MPC_LaneEquationC1_H = (uint8_t)(Read_Signal >> 8);
        p_MPC_RoadState_359_st.MPC_LaneEquationC1_L = (uint8_t)(Read_Signal);
    } else {
        p_MPC_RoadState_359_st.MPC_LaneEquationC1_H = 0;
        p_MPC_RoadState_359_st.MPC_LaneEquationC1_L = 0;
    }
    p_MPC_RoadState_359_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_RoadState_359_ComIn_VeCAN_MPC_LaneEquationC2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_RoadState_359_st.MPC_LaneEquationC2_H = (uint8_t)(Read_Signal >> 8);
        p_MPC_RoadState_359_st.MPC_LaneEquationC2_L = (uint8_t)(Read_Signal);
    } else {
        p_MPC_RoadState_359_st.MPC_LaneEquationC2_H = 0;
        p_MPC_RoadState_359_st.MPC_LaneEquationC2_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_RoadState_359_ComIn_VeCAN_MPC_LaneEquationC3(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_RoadState_359_st.MPC_LaneEquationC3_H = (uint8_t)(Read_Signal >> 8);
        p_MPC_RoadState_359_st.MPC_LaneEquationC3_L = (uint8_t)(Read_Signal);
    } else {
        p_MPC_RoadState_359_st.MPC_LaneEquationC3_H = 0;
        p_MPC_RoadState_359_st.MPC_LaneEquationC3_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_RoadState_359_ComIn_VeCAN_MPC_LaneEquationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_RoadState_359_st.MPC_LaneEquationStatus = (uint8_t)(Read_Signal);
    } else {
        p_MPC_RoadState_359_st.MPC_LaneEquationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_RoadState_359_ComIn_VeCAN_MPC_RoadCurvatureNear(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_RoadState_359_st.MPC_RoadCurvatureNear = (uint8_t)(Read_Signal);
    } else {
        p_MPC_RoadState_359_st.MPC_RoadCurvatureNear = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_RoadState_359_ComIn_VeCAN_MPC_RoadCurvatureFar(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_RoadState_359_st.MPC_RoadCurvatureFar = (uint8_t)(Read_Signal);
    } else {
        p_MPC_RoadState_359_st.MPC_RoadCurvatureFar = 0;
    }

    if (memcmp(&signal_bk, &p_MPC_RoadState_359_st, sizeof(p_MPC_RoadState_359_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MPC_hmi_35D(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x35D_st_MPC_hmi_35D signal_bk;
    memcpy(&signal_bk, &p_MPC_hmi_35D_st, sizeof(p_MPC_hmi_35D_st));

    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ELKSet(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ELKSet = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ELKSet = 0;
    }
    p_MPC_hmi_35D_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ELKSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ELKSts = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ELKSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ISASet(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ISASet = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ISASet = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ISASts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ISASts = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ISASts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ISASpeedLimit_AddSignType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ISASpeedLimit_AddSignType = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ISASpeedLimit_AddSignType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ISAVisualWarnSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ISAVisualWarnSts = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ISAVisualWarnSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ISAAcousticWarnSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ISAAcousticWarnSts = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ISAAcousticWarnSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_ADS_ConditionalCheck(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.ADS_ConditionalCheck = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.ADS_ConditionalCheck = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_ADS_FactoryResetResult(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.ADS_FactoryResetResult = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.ADS_FactoryResetResult = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_ADS_FactoryResetTime(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.ADS_FactoryResetTime_H = (uint8_t)(Read_Signal >> 8);
        p_MPC_hmi_35D_st.ADS_FactoryResetTime_L = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.ADS_FactoryResetTime_H = 0;
        p_MPC_hmi_35D_st.ADS_FactoryResetTime_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_MPC_ISASpeedLimit_ModeStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.MPC_ISASpeedLimit_ModeStatus = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.MPC_ISASpeedLimit_ModeStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_mpc_ElksWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.mpc_ElksWarning = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.mpc_ElksWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_mpc_ISASpeedLimit(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.mpc_ISASpeedLimit = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.mpc_ISASpeedLimit = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MPC_hmi_35D_ComIn_VeCAN_ADS_MapCountryCode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MPC_hmi_35D_st.ADS_MapCountryCode = (uint8_t)(Read_Signal);
    } else {
        p_MPC_hmi_35D_st.ADS_MapCountryCode = 0;
    }

    if (memcmp(&signal_bk, &p_MPC_hmi_35D_st, sizeof(p_MPC_hmi_35D_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_SRR_R_state_22B(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x22B_st_SRR_R_state_22B signal_bk;
    memcpy(&signal_bk, &p_SRR_R_state_22B_st, sizeof(p_SRR_R_state_22B_st));

    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_ctaWarningReqRight(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_ctaWarningReqRight = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_ctaWarningReqRight = 0;
    }
    p_SRR_R_state_22B_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_bsdLCAWarningReqRight(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_bsdLCAWarningReqRight = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_bsdLCAWarningReqRight = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_displayInfo(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_displayInfo = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_displayInfo = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_bsdLCASts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_bsdLCASts = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_bsdLCASts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_ctaSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_ctaSts = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_ctaSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_dowSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_dowSts = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_dowSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_ctaWarningReqLeft(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_ctaWarningReqLeft = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_ctaWarningReqLeft = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_r_bsdLCAWarningReqLeft(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_r_bsdLCAWarningReqLeft = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_r_bsdLCAWarningReqLeft = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_R_DOWFrontLeftDoorWarn(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_R_DOWFrontLeftDoorWarn = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_R_DOWFrontLeftDoorWarn = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_R_DOWRearLeftDoorWarn(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_R_DOWRearLeftDoorWarn = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_R_DOWRearLeftDoorWarn = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_R_DOWFrontRightDoorWarn(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_R_DOWFrontRightDoorWarn = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_R_DOWFrontRightDoorWarn = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_R_DOWRearRightDoorWarn(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_R_DOWRearRightDoorWarn = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_R_DOWRearRightDoorWarn = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_SRR_RCTBOnOffStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.SRR_RCTBOnOffStatus = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.SRR_RCTBOnOffStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SRR_R_state_22B_ComIn_VeCAN_Rear_radar_RCTB_Waring(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SRR_R_state_22B_st.Rear_radar_RCTB_Waring = Read_Signal;
    } else {
        p_SRR_R_state_22B_st.Rear_radar_RCTB_Waring = 0;
    }

    if (memcmp(&signal_bk, &p_SRR_R_state_22B_st, sizeof(p_SRR_R_state_22B_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_ABM_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x380_st_ABM_state signal_bk;
    memcpy(&signal_bk, &p_ABM_state_st, sizeof(p_ABM_state_st));

    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_warningLampStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_warningLampStatus = Read_Signal;
    } else {
        p_ABM_state_st.acu_warningLampStatus = 0;
    }
    p_ABM_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_crashOutputStatusValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_crashOutputStatusValid = Read_Signal;
    } else {
        p_ABM_state_st.acu_crashOutputStatusValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_crashOutputStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_crashOutputStatus = Read_Signal;
    } else {
        p_ABM_state_st.acu_crashOutputStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_ABM_PassAirbSuppressionSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.ABM_PassAirbSuppressionSt = Read_Signal;
    } else {
        p_ABM_state_st.ABM_PassAirbSuppressionSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_driverSeatBeltStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_driverSeatBeltStatus = Read_Signal;
    } else {
        p_ABM_state_st.acu_driverSeatBeltStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_driverSeatBeltStatusValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_driverSeatBeltStatusValid = Read_Signal;
    } else {
        p_ABM_state_st.acu_driverSeatBeltStatusValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_passengerSeatBeltStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_passengerSeatBeltStatus = Read_Signal;
    } else {
        p_ABM_state_st.acu_passengerSeatBeltStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_passengerSeatBeltStatusValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_passengerSeatBeltStatusValid = Read_Signal;
    } else {
        p_ABM_state_st.acu_passengerSeatBeltStatusValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_rollingCounter = Read_Signal;
    } else {
        p_ABM_state_st.acu_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_ABM_state_ComIn_VeCAN_acu_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_ABM_state_st.acu_checksum = Read_Signal;
    } else {
        p_ABM_state_st.acu_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_ABM_state_st, sizeof(p_ABM_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_APA_35B(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x35B_st_APA_35B signal_bk;
    memcpy(&signal_bk, &p_APA_35B_st, sizeof(p_APA_35B_st));

    bResult = Rte_Read_rpSR_CANMSG_APA_35B_ComIn_VeCAN_APA_voice_reminder(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_APA_35B_st.APA_voice_reminder = Read_Signal;
    } else {
        p_APA_35B_st.APA_voice_reminder = 0;
    }
    p_APA_35B_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_APA_35B_ComIn_VeCAN_APA_textinfo(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_APA_35B_st.APA_textinfo = Read_Signal;
    } else {
        p_APA_35B_st.APA_textinfo = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_APA_35B_ComIn_VeCAN_APA_FinishReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_APA_35B_st.APA_FinishReason = Read_Signal;
    } else {
        p_APA_35B_st.APA_FinishReason = 0;
    }

    if (memcmp(&signal_bk, &p_APA_35B_st, sizeof(p_APA_35B_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_state2(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3B1_st_VCU_state2 signal_bk;
    memcpy(&signal_bk, &p_VCU_state2_st, sizeof(p_VCU_state2_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_state2_ComIn_VeCAN_VCU_CLTCEvRemainingMileage(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_state2_st.VCU_CLTCEvRemainingMileage_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_state2_st.VCU_CLTCEvRemainingMileage_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_state2_st.VCU_CLTCEvRemainingMileage_H = 0;
        p_VCU_state2_st.VCU_CLTCEvRemainingMileage_L = 0;
    }
    p_VCU_state2_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_VCU_state2_st, sizeof(p_VCU_state2_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BLE_FB(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x347_st_BLE_FB signal_bk;
    memcpy(&signal_bk, &p_BLE_FB_st, sizeof(p_BLE_FB_st));

    bResult = Rte_Read_rpSR_CANMSG_BLE_FB_ComIn_VeCAN_BLE_approachingUnlockFedb(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BLE_FB_st.BLE_approachingUnlockFedb = Read_Signal;
    } else {
        p_BLE_FB_st.BLE_approachingUnlockFedb = 0;
    }
    p_BLE_FB_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BLE_FB_ComIn_VeCAN_BLE_awayLockFeedback(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BLE_FB_st.BLE_awayLockFeedback = Read_Signal;
    } else {
        p_BLE_FB_st.BLE_awayLockFeedback = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BLE_FB_ComIn_VeCAN_BLE_RPAmodeReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BLE_FB_st.BLE_RPAmodeReq = Read_Signal;
    } else {
        p_BLE_FB_st.BLE_RPAmodeReq = 0;
    }

    if (memcmp(&signal_bk, &p_BLE_FB_st, sizeof(p_BLE_FB_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BLE_User_ID(void)
{
    uint8_t bResult = FALSE;
    uint64_t Read_Signal = 0;
    struct package_0x375_st_BLE_User_ID signal_bk;
    memcpy(&signal_bk, &p_BLE_User_ID_st, sizeof(p_BLE_User_ID_st));

    bResult = Rte_Read_rpSR_CANMSG_BLE_User_ID_ComIn_VeCAN_BLE_User_ID(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BLE_User_ID_st.BLE_User_ID_8 = (uint8_t)(Read_Signal >> 56);
        p_BLE_User_ID_st.BLE_User_ID_7 = (uint8_t)(Read_Signal >> 48);
        p_BLE_User_ID_st.BLE_User_ID_6 = (uint8_t)(Read_Signal >> 40);
        p_BLE_User_ID_st.BLE_User_ID_5 = (uint8_t)(Read_Signal >> 32);
        p_BLE_User_ID_st.BLE_User_ID_4 = (uint8_t)(Read_Signal >> 24);
        p_BLE_User_ID_st.BLE_User_ID_3 = (uint8_t)(Read_Signal >> 16);
        p_BLE_User_ID_st.BLE_User_ID_2 = (uint8_t)(Read_Signal >> 8);
        p_BLE_User_ID_st.BLE_User_ID_1 = (uint8_t)(Read_Signal);
    } else {
        p_BLE_User_ID_st.BLE_User_ID_8 = 0;
        p_BLE_User_ID_st.BLE_User_ID_7 = 0;
        p_BLE_User_ID_st.BLE_User_ID_6 = 0;
        p_BLE_User_ID_st.BLE_User_ID_5 = 0;
        p_BLE_User_ID_st.BLE_User_ID_4 = 0;
        p_BLE_User_ID_st.BLE_User_ID_3 = 0;
        p_BLE_User_ID_st.BLE_User_ID_2 = 0;
        p_BLE_User_ID_st.BLE_User_ID_1 = 0;
    }
    p_BLE_User_ID_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_BLE_User_ID_st, sizeof(p_BLE_User_ID_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_TBOX_Factory_360(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x360_st_TBOX_Factory_360 signal_bk;
    memcpy(&signal_bk, &p_TBOX_Factory_360_st, sizeof(p_TBOX_Factory_360_st));

    bResult = Rte_Read_rpSR_CANMSG_TBOX_Factory_360_ComIn_VeCAN_TBOX_ConditionalCheck(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_Factory_360_st.TBOX_ConditionalCheck = (uint8_t)(Read_Signal);
    } else {
        p_TBOX_Factory_360_st.TBOX_ConditionalCheck = 0;
    }
    p_TBOX_Factory_360_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_Factory_360_ComIn_VeCAN_TBOX_FactoryResetResult(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_Factory_360_st.TBOX_FactoryResetResult = (uint8_t)(Read_Signal);
    } else {
        p_TBOX_Factory_360_st.TBOX_FactoryResetResult = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_Factory_360_ComIn_VeCAN_TBOX_FactoryResetTime(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_Factory_360_st.TBOX_FactoryResetTime_H = (uint8_t)(Read_Signal >> 8);
        p_TBOX_Factory_360_st.TBOX_FactoryResetTime_L = (uint8_t)(Read_Signal);
    } else {
        p_TBOX_Factory_360_st.TBOX_FactoryResetTime_H = 0;
        p_TBOX_Factory_360_st.TBOX_FactoryResetTime_L = 0;
    }

    if (memcmp(&signal_bk, &p_TBOX_Factory_360_st, sizeof(p_TBOX_Factory_360_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_AC_ctrlFeedback(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3B6_st_AC_ctrlFeedback signal_bk;
    memcpy(&signal_bk, &p_AC_ctrlFeedback_st, sizeof(p_AC_ctrlFeedback_st));

    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_systemOnOffSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_systemOnOffSts = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_systemOnOffSts = 0;
    }
    p_AC_ctrlFeedback_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_autoStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_autoStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_autoStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_acStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_acStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_acStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_driverTempC(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_driverTempC = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_driverTempC = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_dualStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_dualStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_dualStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_frontDefrostStatus1(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_frontDefrostStatus1 = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_frontDefrostStatus1 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_recircStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_recircStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_recircStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_passengerTempC(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_passengerTempC = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_passengerTempC = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_blowerLvAUTOStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_blowerLvAUTOStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_blowerLvAUTOStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_AC_EnergySavingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.AC_EnergySavingSts = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.AC_EnergySavingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_modeAUTOStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_modeAUTOStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_modeAUTOStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_modeStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_modeStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_modeStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_ac_blowerLvStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.ac_blowerLvStatus = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.ac_blowerLvStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_AC_InigentizePurificationStSwitch(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.AC_InigentizePurificationStSwitch = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.AC_InigentizePurificationStSwitch = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_AC_InigentizePurificationSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.AC_InigentizePurificationSt = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.AC_InigentizePurificationSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_AC_InsidePM25Level(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.AC_InsidePM25Level = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.AC_InsidePM25Level = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_AC_PM25InCar(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.AC_PM25InCar_H = (uint8_t)(Read_Signal >> 8);
        p_AC_ctrlFeedback_st.AC_PM25InCar_L = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.AC_PM25InCar_H = 0;
        p_AC_ctrlFeedback_st.AC_PM25InCar_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_AC_PurificationQuikReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.AC_PurificationQuikReq = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.AC_PurificationQuikReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_ctrlFeedback_ComIn_VeCAN_AC_AutoDrySts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_ctrlFeedback_st.AC_AutoDrySts = (uint8_t)(Read_Signal);
    } else {
        p_AC_ctrlFeedback_st.AC_AutoDrySts = 0;
    }

    if (memcmp(&signal_bk, &p_AC_ctrlFeedback_st, sizeof(p_AC_ctrlFeedback_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_AC_state2(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x386_st_AC_state2 signal_bk;
    memcpy(&signal_bk, &p_AC_state2_st, sizeof(p_AC_state2_st));

    bResult = Rte_Read_rpSR_CANMSG_AC_state2_ComIn_VeCAN_ac_FrontDefrostLevelStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_state2_st.ac_FrontDefrostLevelStatus = Read_Signal;
    } else {
        p_AC_state2_st.ac_FrontDefrostLevelStatus = 0;
    }
    p_AC_state2_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_AC_state2_st, sizeof(p_AC_state2_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x2A1_st_BCM_state signal_bk;
    memcpy(&signal_bk, &p_BCM_state_st, sizeof(p_BCM_state_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_cruiseSW(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_cruiseSW = Read_Signal;
    } else {
        p_BCM_state_st.bcm_cruiseSW = 0;
    }
    p_BCM_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_cruiseSWValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_cruiseSWValid = Read_Signal;
    } else {
        p_BCM_state_st.bcm_cruiseSWValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_BCM_cruiseHeadway_increase_KeySts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.BCM_cruiseHeadway_increase_KeySts = Read_Signal;
    } else {
        p_BCM_state_st.BCM_cruiseHeadway_increase_KeySts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_BCM_cruiseHeadway_increase_KeyStsValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.BCM_cruiseHeadway_increase_KeyStsValid = Read_Signal;
    } else {
        p_BCM_state_st.BCM_cruiseHeadway_increase_KeyStsValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_hoodSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_hoodSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_hoodSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_hazardLightSwSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_hazardLightSwSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_hazardLightSwSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_leftTurnLampSwSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_leftTurnLampSwSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_leftTurnLampSwSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_leftTurnLampSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_leftTurnLampSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_leftTurnLampSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_rightTurnLampSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_rightTurnLampSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_rightTurnLampSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_rightTurnLampSwSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_rightTurnLampSwSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_rightTurnLampSwSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_doorFLSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_doorFLSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_doorFLSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_doorFRSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_doorFRSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_doorFRSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_doorRLSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_doorRLSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_doorRLSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_doorRRSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_doorRRSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_doorRRSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_doorFLLockSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_doorFLLockSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_doorFLLockSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_antiTheftSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_antiTheftSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_antiTheftSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_FuelTapStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_FuelTapStatus = Read_Signal;
    } else {
        p_BCM_state_st.bcm_FuelTapStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_frontWiperSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_frontWiperSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_frontWiperSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_chrgCapSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_chrgCapSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_chrgCapSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_BCM_cruiseHeadway_decrease_KeySts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.BCM_cruiseHeadway_decrease_KeySts = Read_Signal;
    } else {
        p_BCM_state_st.BCM_cruiseHeadway_decrease_KeySts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_BCM_cruiseHeadway_decrease_KeyStsValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.BCM_cruiseHeadway_decrease_KeyStsValid = Read_Signal;
    } else {
        p_BCM_state_st.BCM_cruiseHeadway_decrease_KeyStsValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state_ComIn_VeCAN_bcm_driverSeatDetectSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state_st.bcm_driverSeatDetectSts = Read_Signal;
    } else {
        p_BCM_state_st.bcm_driverSeatDetectSts = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_state_st, sizeof(p_BCM_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_state2(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3C1_st_BCM_state2 signal_bk;
    memcpy(&signal_bk, &p_BCM_state2_st, sizeof(p_BCM_state2_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_rearMirrorSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_rearMirrorSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_rearMirrorSts = 0;
    }
    p_BCM_state2_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_BCM_HighBeamModel(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.BCM_HighBeamModel = Read_Signal;
    } else {
        p_BCM_state2_st.BCM_HighBeamModel = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_windowLFSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_windowLFSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_windowLFSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_windowRFSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_windowRFSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_windowRFSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_windowLRSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_windowLRSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_windowLRSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_windowRRSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_windowRRSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_windowRRSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_rearDefrostSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_rearDefrostSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_rearDefrostSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_BCM_AutoRainWiperstatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.BCM_AutoRainWiperstatus = Read_Signal;
    } else {
        p_BCM_state2_st.BCM_AutoRainWiperstatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_rainSensorError(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_rainSensorError = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_rainSensorError = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_positionLampSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_positionLampSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_positionLampSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_autoLampSwSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_autoLampSwSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_autoLampSwSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_rsmSolarRight(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_rsmSolarRight = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_rsmSolarRight = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_rsmSolarLeft(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_rsmSolarLeft = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_rsmSolarLeft = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_lowBeamSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_lowBeamSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_lowBeamSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_highBeamSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_highBeamSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_highBeamSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_rearFogLampSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_rearFogLampSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_rearFogLampSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_lightSensorError(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_lightSensorError = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_lightSensorError = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state2_ComIn_VeCAN_bcm_roofLampSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state2_st.bcm_roofLampSts = Read_Signal;
    } else {
        p_BCM_state2_st.bcm_roofLampSts = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_state2_st, sizeof(p_BCM_state2_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_state3(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3C2_st_BCM_state3 signal_bk;
    memcpy(&signal_bk, &p_BCM_state3_st, sizeof(p_BCM_state3_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_NozzleHeatingSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_NozzleHeatingSt = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_NozzleHeatingSt = 0;
    }
    p_BCM_state3_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_VolOrSOCLowAlarm(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_VolOrSOCLowAlarm = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_VolOrSOCLowAlarm = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_ModeFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_ModeFB = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_ModeFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_FLWINOpenDegree(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_FLWINOpenDegree = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_FLWINOpenDegree = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_FRWINOpenDegree(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_FRWINOpenDegree = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_FRWINOpenDegree = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_PresentONState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_PresentONState = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_PresentONState = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_VSPReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_VSPReq = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_VSPReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_lockSoundSetfedb(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_lockSoundSetfedb = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_lockSoundSetfedb = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_brakeLightSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_brakeLightSts = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_brakeLightSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_RLWINOpenDegree(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_RLWINOpenDegree = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_RLWINOpenDegree = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_RRWINOpenDegree(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_RRWINOpenDegree = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_RRWINOpenDegree = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_NFC_PS_KeyReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_NFC_PS_KeyReq = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_NFC_PS_KeyReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_state3_ComIn_VeCAN_BCM_PowerState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state3_st.BCM_PowerState = Read_Signal;
    } else {
        p_BCM_state3_st.BCM_PowerState = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_state3_st, sizeof(p_BCM_state3_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_state4(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x305_st_BCM_state4 signal_bk;
    memcpy(&signal_bk, &p_BCM_state4_st, sizeof(p_BCM_state4_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_state4_ComIn_VeCAN_bcm_footLightSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_state4_st.bcm_footLightSwitchSts = Read_Signal;
    } else {
        p_BCM_state4_st.bcm_footLightSwitchSts = 0;
    }
    p_BCM_state4_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_BCM_state4_st, sizeof(p_BCM_state4_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_tpms(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x411_st_BCM_tpms signal_bk;
    memcpy(&signal_bk, &p_BCM_tpms_st, sizeof(p_BCM_tpms_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms_ComIn_VeCAN_bcm_tpmsLFStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms_st.bcm_tpmsLFStatus = Read_Signal;
    } else {
        p_BCM_tpms_st.bcm_tpmsLFStatus = 0;
    }
    p_BCM_tpms_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms_ComIn_VeCAN_bcm_tyreLFPressure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms_st.bcm_tyreLFPressure = Read_Signal;
    } else {
        p_BCM_tpms_st.bcm_tyreLFPressure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms_ComIn_VeCAN_bcm_tyreLFTemp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms_st.bcm_tyreLFTemp = Read_Signal;
    } else {
        p_BCM_tpms_st.bcm_tyreLFTemp = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms_ComIn_VeCAN_bcm_tpmsRFStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms_st.bcm_tpmsRFStatus = Read_Signal;
    } else {
        p_BCM_tpms_st.bcm_tpmsRFStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms_ComIn_VeCAN_bcm_tyreRFPressure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms_st.bcm_tyreRFPressure = Read_Signal;
    } else {
        p_BCM_tpms_st.bcm_tyreRFPressure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms_ComIn_VeCAN_bcm_tyreRFTemp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms_st.bcm_tyreRFTemp = Read_Signal;
    } else {
        p_BCM_tpms_st.bcm_tyreRFTemp = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms_ComIn_VeCAN_BCM_wipperMaintModeSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms_st.BCM_wipperMaintModeSts = Read_Signal;
    } else {
        p_BCM_tpms_st.BCM_wipperMaintModeSts = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_tpms_st, sizeof(p_BCM_tpms_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_tpms1(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x421_st_BCM_tpms1 signal_bk;
    memcpy(&signal_bk, &p_BCM_tpms1_st, sizeof(p_BCM_tpms1_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms1_ComIn_VeCAN_bcm_tpmsLRStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms1_st.bcm_tpmsLRStatus = Read_Signal;
    } else {
        p_BCM_tpms1_st.bcm_tpmsLRStatus = 0;
    }
    p_BCM_tpms1_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms1_ComIn_VeCAN_bcm_tyreLRPressure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms1_st.bcm_tyreLRPressure = Read_Signal;
    } else {
        p_BCM_tpms1_st.bcm_tyreLRPressure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms1_ComIn_VeCAN_bcm_tyreLRTemp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms1_st.bcm_tyreLRTemp = Read_Signal;
    } else {
        p_BCM_tpms1_st.bcm_tyreLRTemp = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms1_ComIn_VeCAN_bcm_tpmsRRStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms1_st.bcm_tpmsRRStatus = Read_Signal;
    } else {
        p_BCM_tpms1_st.bcm_tpmsRRStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms1_ComIn_VeCAN_bcm_tyreRRPressure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms1_st.bcm_tyreRRPressure = Read_Signal;
    } else {
        p_BCM_tpms1_st.bcm_tyreRRPressure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_tpms1_ComIn_VeCAN_bcm_tyreRRTemp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_tpms1_st.bcm_tyreRRTemp = Read_Signal;
    } else {
        p_BCM_tpms1_st.bcm_tyreRRTemp = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_tpms1_st, sizeof(p_BCM_tpms1_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_peps(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x2C1_st_BCM_peps signal_bk;
    memcpy(&signal_bk, &p_BCM_peps_st, sizeof(p_BCM_peps_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_pepsPowerMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_pepsPowerMode = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_pepsPowerMode = 0;
    }
    p_BCM_peps_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_ChildSafetyLockRRSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_ChildSafetyLockRRSts = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_ChildSafetyLockRRSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_pepsKeyNotInCarInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_pepsKeyNotInCarInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_pepsKeyNotInCarInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_pepsKeySerchFailInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_pepsKeySerchFailInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_pepsKeySerchFailInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_pepsKeyCloserInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_pepsKeyCloserInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_pepsKeyCloserInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_pepsFobLowBatWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_pepsFobLowBatWarning = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_pepsFobLowBatWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_pepsPowerRelayErrWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_pepsPowerRelayErrWarning = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_pepsPowerRelayErrWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_ChildSafetyLockSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_ChildSafetyLockSts = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_ChildSafetyLockSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_esclUnlockFailWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_esclUnlockFailWarning = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_esclUnlockFailWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_esclLockFailWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_esclLockFailWarning = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_esclLockFailWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_remoteMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_remoteMode = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_remoteMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_DriveDoorUnlockFedb(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_DriveDoorUnlockFedb = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_DriveDoorUnlockFedb = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_12VBatterySOC(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_12VBatterySOC = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_12VBatterySOC = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_pepsKeyInCarInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_pepsKeyInCarInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_pepsKeyInCarInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_lowBeamFailureInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_lowBeamFailureInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_lowBeamFailureInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_frontLeftTurnLightFailInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_frontLeftTurnLightFailInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_frontLeftTurnLightFailInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_frontRightTurnLightFailInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_frontRightTurnLightFailInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_frontRightTurnLightFailInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_rearFixLeftTurnLightFailInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_rearFixLeftTurnLightFailInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_rearFixLeftTurnLightFailInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_rearMoveLeftTurnLightFailInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_rearMoveLeftTurnLightFailInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_rearMoveLeftTurnLightFailInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_rearFixRightTurnLightFailInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_rearFixRightTurnLightFailInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_rearFixRightTurnLightFailInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_rearMoRightTurnLightFailInd(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_rearMoRightTurnLightFailInd = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_rearMoRightTurnLightFailInd = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_ChildSafetyLockRLSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_ChildSafetyLockRLSts = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_ChildSafetyLockRLSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_doorTopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_doorTopSwitchSts = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_doorTopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_approachingUnlockFedb(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_approachingUnlockFedb = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_approachingUnlockFedb = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_followMeHomeFedb(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_followMeHomeFedb = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_followMeHomeFedb = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_awayLockFeedback(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_awayLockFeedback = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_awayLockFeedback = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_peps_ComIn_VeCAN_bcm_MirrorAutoFoldUnfoldStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_peps_st.bcm_MirrorAutoFoldUnfoldStatus = Read_Signal;
    } else {
        p_BCM_peps_st.bcm_MirrorAutoFoldUnfoldStatus = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_peps_st, sizeof(p_BCM_peps_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_rsm(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3D1_st_BCM_rsm signal_bk;
    memcpy(&signal_bk, &p_BCM_rsm_st, sizeof(p_BCM_rsm_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_rsm_ComIn_VeCAN_BCM_apm_PassengeLockStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_rsm_st.BCM_apm_PassengeLockStatus = Read_Signal;
    } else {
        p_BCM_rsm_st.BCM_apm_PassengeLockStatus = 0;
    }
    p_BCM_rsm_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_rsm_ComIn_VeCAN_BCM_positionLightOnReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_rsm_st.BCM_positionLightOnReq = Read_Signal;
    } else {
        p_BCM_rsm_st.BCM_positionLightOnReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_rsm_ComIn_VeCAN_BCM_LockCloseWinFedb(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_rsm_st.BCM_LockCloseWinFedb = Read_Signal;
    } else {
        p_BCM_rsm_st.BCM_LockCloseWinFedb = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_rsm_st, sizeof(p_BCM_rsm_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BCM_RemotFB(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x5C3_st_BCM_RemotFB signal_bk;
    memcpy(&signal_bk, &p_BCM_RemotFB_st, sizeof(p_BCM_RemotFB_st));

    bResult = Rte_Read_rpSR_CANMSG_BCM_RemotFB_ComIn_VeCAN_BCM_LockFaultReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_RemotFB_st.BCM_LockFaultReason = Read_Signal;
    } else {
        p_BCM_RemotFB_st.BCM_LockFaultReason = 0;
    }
    p_BCM_RemotFB_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_RemotFB_ComIn_VeCAN_BCM_FRWINReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_RemotFB_st.BCM_FRWINReason = Read_Signal;
    } else {
        p_BCM_RemotFB_st.BCM_FRWINReason = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_RemotFB_ComIn_VeCAN_BCM_FLWINReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_RemotFB_st.BCM_FLWINReason = Read_Signal;
    } else {
        p_BCM_RemotFB_st.BCM_FLWINReason = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_RemotFB_ComIn_VeCAN_BCM_RLWINReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_RemotFB_st.BCM_RLWINReason = Read_Signal;
    } else {
        p_BCM_RemotFB_st.BCM_RLWINReason = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BCM_RemotFB_ComIn_VeCAN_BCM_RRWINReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BCM_RemotFB_st.BCM_RRWINReason = Read_Signal;
    } else {
        p_BCM_RemotFB_st.BCM_RRWINReason = 0;
    }

    if (memcmp(&signal_bk, &p_BCM_RemotFB_st, sizeof(p_BCM_RemotFB_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_LCU_32A(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x32A_st_LCU_32A signal_bk;
    memcpy(&signal_bk, &p_LCU_32A_st, sizeof(p_LCU_32A_st));

    bResult = Rte_Read_rpSR_CANMSG_LCU_32A_ComIn_VeCAN_LCU_danceOnOffSet_FB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_LCU_32A_st.LCU_danceOnOffSet_FB = Read_Signal;
    } else {
        p_LCU_32A_st.LCU_danceOnOffSet_FB = 0;
    }
    p_LCU_32A_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_LCU_32A_ComIn_VeCAN_LCU_unlockAnimatSet_FB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_LCU_32A_st.LCU_unlockAnimatSet_FB = Read_Signal;
    } else {
        p_LCU_32A_st.LCU_unlockAnimatSet_FB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_LCU_32A_ComIn_VeCAN_LCU_lockAnimatSet_FB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_LCU_32A_st.LCU_lockAnimatSet_FB = Read_Signal;
    } else {
        p_LCU_32A_st.LCU_lockAnimatSet_FB = 0;
    }

    if (memcmp(&signal_bk, &p_LCU_32A_st, sizeof(p_LCU_32A_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_PLG_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x394_st_PLG_state signal_bk;
    memcpy(&signal_bk, &p_PLG_state_st, sizeof(p_PLG_state_st));

    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_antipinchWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_antipinchWarning = Read_Signal;
    } else {
        p_PLG_state_st.PLG_antipinchWarning = 0;
    }
    p_PLG_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_tailgateOpenFailWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_tailgateOpenFailWarning = Read_Signal;
    } else {
        p_PLG_state_st.PLG_tailgateOpenFailWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_tailgateCloseFailWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_tailgateCloseFailWarning = Read_Signal;
    } else {
        p_PLG_state_st.PLG_tailgateCloseFailWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_tailgateOpenSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_tailgateOpenSts = Read_Signal;
    } else {
        p_PLG_state_st.PLG_tailgateOpenSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_antiPlayWarning(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_antiPlayWarning = Read_Signal;
    } else {
        p_PLG_state_st.PLG_antiPlayWarning = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_tailgateOpenSts2(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_tailgateOpenSts2 = Read_Signal;
    } else {
        p_PLG_state_st.PLG_tailgateOpenSts2 = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_OpenDegree(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_OpenDegree = Read_Signal;
    } else {
        p_PLG_state_st.PLG_OpenDegree = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PLG_state_ComIn_VeCAN_PLG_tailgateFaultReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PLG_state_st.PLG_tailgateFaultReason = Read_Signal;
    } else {
        p_PLG_state_st.PLG_tailgateFaultReason = 0;
    }

    if (memcmp(&signal_bk, &p_PLG_state_st, sizeof(p_PLG_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_Handle_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x335_st_GW_Handle_state signal_bk;
    memcpy(&signal_bk, &p_GW_Handle_state_st, sizeof(p_GW_Handle_state_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_Handle_state_ComIn_VeCAN_handle1_handlePosition(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_Handle_state_st.handle1_handlePosition = Read_Signal;
    } else {
        p_GW_Handle_state_st.handle1_handlePosition = 0;
    }
    p_GW_Handle_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_Handle_state_ComIn_VeCAN_handle2_handlePosition(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_Handle_state_st.handle2_handlePosition = Read_Signal;
    } else {
        p_GW_Handle_state_st.handle2_handlePosition = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_Handle_state_ComIn_VeCAN_handle3_handlePosition(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_Handle_state_st.handle3_handlePosition = Read_Signal;
    } else {
        p_GW_Handle_state_st.handle3_handlePosition = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_Handle_state_ComIn_VeCAN_handle4_handlePosition(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_Handle_state_st.handle4_handlePosition = Read_Signal;
    } else {
        p_GW_Handle_state_st.handle4_handlePosition = 0;
    }

    if (memcmp(&signal_bk, &p_GW_Handle_state_st, sizeof(p_GW_Handle_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_DSM_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3D5_st_DSM_state signal_bk;
    memcpy(&signal_bk, &p_DSM_state_st, sizeof(p_DSM_state_st));

    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_drSeatMassSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_drSeatMassSts = Read_Signal;
    } else {
        p_DSM_state_st.DSM_drSeatMassSts = 0;
    }
    p_DSM_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_passSeatMassSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_passSeatMassSts = Read_Signal;
    } else {
        p_DSM_state_st.DSM_passSeatMassSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_easyEntryStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_easyEntryStatus = Read_Signal;
    } else {
        p_DSM_state_st.DSM_easyEntryStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_MirrorAutoTurnDownStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_MirrorAutoTurnDownStatus = Read_Signal;
    } else {
        p_DSM_state_st.DSM_MirrorAutoTurnDownStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_DrMassgIntenSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_DrMassgIntenSt = Read_Signal;
    } else {
        p_DSM_state_st.DSM_DrMassgIntenSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_PsgMassgIntenSt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_PsgMassgIntenSt = Read_Signal;
    } else {
        p_DSM_state_st.DSM_PsgMassgIntenSt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_DSMStatustOutput(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_DSMStatustOutput = Read_Signal;
    } else {
        p_DSM_state_st.DSM_DSMStatustOutput = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_MemoryPosition(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_MemoryPosition = Read_Signal;
    } else {
        p_DSM_state_st.DSM_MemoryPosition = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_DevSupportSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_DevSupportSts = Read_Signal;
    } else {
        p_DSM_state_st.DSM_DevSupportSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_DevLinkSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_DevLinkSts = Read_Signal;
    } else {
        p_DSM_state_st.DSM_DevLinkSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_DevType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_DevType = Read_Signal;
    } else {
        p_DSM_state_st.DSM_DevType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_state_ComIn_VeCAN_DSM_ChargeSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_state_st.DSM_ChargeSts = Read_Signal;
    } else {
        p_DSM_state_st.DSM_ChargeSts = 0;
    }

    if (memcmp(&signal_bk, &p_DSM_state_st, sizeof(p_DSM_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_PSM_memory(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3D6_st_PSM_memory signal_bk;
    memcpy(&signal_bk, &p_PSM_memory_st, sizeof(p_PSM_memory_st));

    bResult = Rte_Read_rpSR_CANMSG_PSM_memory_ComIn_VeCAN_PSM_PassSeatRouteSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_memory_st.PSM_PassSeatRouteSetFB = Read_Signal;
    } else {
        p_PSM_memory_st.PSM_PassSeatRouteSetFB = 0;
    }
    p_PSM_memory_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_memory_ComIn_VeCAN_PSM_PassSeatbackrestSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_memory_st.PSM_PassSeatbackrestSetFB = Read_Signal;
    } else {
        p_PSM_memory_st.PSM_PassSeatbackrestSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_memory_ComIn_VeCAN_PSM_PassSeatCushionSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_memory_st.PSM_PassSeatCushionSetFB = Read_Signal;
    } else {
        p_PSM_memory_st.PSM_PassSeatCushionSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_memory_ComIn_VeCAN_PSM_PassSeatCushionAngleSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_memory_st.PSM_PassSeatCushionAngleSetFB = Read_Signal;
    } else {
        p_PSM_memory_st.PSM_PassSeatCushionAngleSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_memory_ComIn_VeCAN_PSM_LimitbackrestAngle(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_memory_st.PSM_LimitbackrestAngle = Read_Signal;
    } else {
        p_PSM_memory_st.PSM_LimitbackrestAngle = 0;
    }

    if (memcmp(&signal_bk, &p_PSM_memory_st, sizeof(p_PSM_memory_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_DSM_memory(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3D4_st_DSM_memory signal_bk;
    memcpy(&signal_bk, &p_DSM_memory_st, sizeof(p_DSM_memory_st));

    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_drSeatRouteSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_drSeatRouteSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_drSeatRouteSetFB = 0;
    }
    p_DSM_memory_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_drSeatbackrestSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_drSeatbackrestSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_drSeatbackrestSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_drSeatCushionSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_drSeatCushionSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_drSeatCushionSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_drSeatCushionAngleSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_drSeatCushionAngleSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_drSeatCushionAngleSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_LmirrorUDSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_LmirrorUDSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_LmirrorUDSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_LimitbackrestAngle(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_LimitbackrestAngle = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_LimitbackrestAngle = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_LmirrorLRSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_LmirrorLRSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_LmirrorLRSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_RmirrorUDSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_RmirrorUDSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_RmirrorUDSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_RmirrorLRSetFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_RmirrorLRSetFB = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_RmirrorLRSetFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_DSM_memory_ComIn_VeCAN_DSM_drSeatMovementSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_DSM_memory_st.DSM_drSeatMovementSts = Read_Signal;
    } else {
        p_DSM_memory_st.DSM_drSeatMovementSts = 0;
    }

    if (memcmp(&signal_bk, &p_DSM_memory_st, sizeof(p_DSM_memory_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_PSM_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x318_st_PSM_state signal_bk;
    memcpy(&signal_bk, &p_PSM_state_st, sizeof(p_PSM_state_st));

    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_drSeatHeatSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_drSeatHeatSts = Read_Signal;
    } else {
        p_PSM_state_st.PSM_drSeatHeatSts = 0;
    }
    p_PSM_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_drSeatVentSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_drSeatVentSts = Read_Signal;
    } else {
        p_PSM_state_st.PSM_drSeatVentSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_passSeatHeatSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_passSeatHeatSts = Read_Signal;
    } else {
        p_PSM_state_st.PSM_passSeatHeatSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_passSeatVentSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_passSeatVentSts = Read_Signal;
    } else {
        p_PSM_state_st.PSM_passSeatVentSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_DevSupportSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_DevSupportSts = Read_Signal;
    } else {
        p_PSM_state_st.PSM_DevSupportSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_DevLinkSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_DevLinkSts = Read_Signal;
    } else {
        p_PSM_state_st.PSM_DevLinkSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_DevType(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_DevType = Read_Signal;
    } else {
        p_PSM_state_st.PSM_DevType = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_PSM_state_ComIn_VeCAN_PSM_ChargeSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_PSM_state_st.PSM_ChargeSts = Read_Signal;
    } else {
        p_PSM_state_st.PSM_ChargeSts = 0;
    }

    if (memcmp(&signal_bk, &p_PSM_state_st, sizeof(p_PSM_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_LRSM_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x31A_st_LRSM_state signal_bk;
    memcpy(&signal_bk, &p_LRSM_state_st, sizeof(p_LRSM_state_st));

    bResult = Rte_Read_rpSR_CANMSG_LRSM_state_ComIn_VeCAN_LRSM_LSeatHeatSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_LRSM_state_st.LRSM_LSeatHeatSts = Read_Signal;
    } else {
        p_LRSM_state_st.LRSM_LSeatHeatSts = 0;
    }
    p_LRSM_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_LRSM_state_ComIn_VeCAN_LRSM_RSeatHeatSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_LRSM_state_st.LRSM_RSeatHeatSts = Read_Signal;
    } else {
        p_LRSM_state_st.LRSM_RSeatHeatSts = 0;
    }

    if (memcmp(&signal_bk, &p_LRSM_state_st, sizeof(p_LRSM_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_TBOX_infoCtrl(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x0A8_st_TBOX_infoCtrl signal_bk;
    memcpy(&signal_bk, &p_TBOX_infoCtrl_st, sizeof(p_TBOX_infoCtrl_st));

    bResult = Rte_Read_rpSR_CANMSG_TBOX_infoCtrl_ComIn_VeCAN_tbox_remotePetModeReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_infoCtrl_st.tbox_remotePetModeReq = Read_Signal;
    } else {
        p_TBOX_infoCtrl_st.tbox_remotePetModeReq = 0;
    }
    p_TBOX_infoCtrl_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_infoCtrl_ComIn_VeCAN_TBOX_SentryReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_infoCtrl_st.TBOX_SentryReq = Read_Signal;
    } else {
        p_TBOX_infoCtrl_st.TBOX_SentryReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_infoCtrl_ComIn_VeCAN_TBOX_TakeVideoPosReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_infoCtrl_st.TBOX_TakeVideoPosReq = Read_Signal;
    } else {
        p_TBOX_infoCtrl_st.TBOX_TakeVideoPosReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_infoCtrl_ComIn_VeCAN_TBOX_TakePhotoReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_infoCtrl_st.TBOX_TakePhotoReq = Read_Signal;
    } else {
        p_TBOX_infoCtrl_st.TBOX_TakePhotoReq = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_TBOX_infoCtrl_ComIn_VeCAN_TBOX_SentryTimeSet(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_TBOX_infoCtrl_st.TBOX_SentryTimeSet = Read_Signal;
    } else {
        p_TBOX_infoCtrl_st.TBOX_SentryTimeSet = 0;
    }

    if (memcmp(&signal_bk, &p_TBOX_infoCtrl_st, sizeof(p_TBOX_infoCtrl_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent1Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3C6_st_GW_vent1Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent1Sts_st, sizeof(p_GW_vent1Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1ErrorStatus = 0;
    }
    p_GW_vent1Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent1Sts_st.gw_ElVent1MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1MotorCurrentLocation_H = 0;
        p_GW_vent1Sts_st.gw_ElVent1MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent1Sts_ComIn_VeCAN_gw_ElVent1StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent1Sts_st.gw_ElVent1StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent1Sts_st.gw_ElVent1StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent1Sts_st, sizeof(p_GW_vent1Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent2Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3C7_st_GW_vent2Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent2Sts_st, sizeof(p_GW_vent2Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2ErrorStatus = 0;
    }
    p_GW_vent2Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent2Sts_st.gw_ElVent2MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2MotorCurrentLocation_H = 0;
        p_GW_vent2Sts_st.gw_ElVent2MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent2Sts_ComIn_VeCAN_gw_ElVent2StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent2Sts_st.gw_ElVent2StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent2Sts_st.gw_ElVent2StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent2Sts_st, sizeof(p_GW_vent2Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent3Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3C8_st_GW_vent3Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent3Sts_st, sizeof(p_GW_vent3Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3ErrorStatus = 0;
    }
    p_GW_vent3Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent3Sts_st.gw_ElVent3MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3MotorCurrentLocation_H = 0;
        p_GW_vent3Sts_st.gw_ElVent3MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent3Sts_ComIn_VeCAN_gw_ElVent3StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent3Sts_st.gw_ElVent3StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent3Sts_st.gw_ElVent3StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent3Sts_st, sizeof(p_GW_vent3Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent4Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3C9_st_GW_vent4Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent4Sts_st, sizeof(p_GW_vent4Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4ErrorStatus = 0;
    }
    p_GW_vent4Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent4Sts_st.gw_ElVent4MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4MotorCurrentLocation_H = 0;
        p_GW_vent4Sts_st.gw_ElVent4MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent4Sts_ComIn_VeCAN_gw_ElVent4StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent4Sts_st.gw_ElVent4StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent4Sts_st.gw_ElVent4StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent4Sts_st, sizeof(p_GW_vent4Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent5Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3CA_st_GW_vent5Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent5Sts_st, sizeof(p_GW_vent5Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5ErrorStatus = 0;
    }
    p_GW_vent5Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent5Sts_st.gw_ElVent5MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5MotorCurrentLocation_H = 0;
        p_GW_vent5Sts_st.gw_ElVent5MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent5Sts_ComIn_VeCAN_gw_ElVent5StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent5Sts_st.gw_ElVent5StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent5Sts_st.gw_ElVent5StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent5Sts_st, sizeof(p_GW_vent5Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent6Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3CB_st_GW_vent6Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent6Sts_st, sizeof(p_GW_vent6Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6ErrorStatus = 0;
    }
    p_GW_vent6Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent6Sts_st.gw_ElVent6MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6MotorCurrentLocation_H = 0;
        p_GW_vent6Sts_st.gw_ElVent6MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent6Sts_ComIn_VeCAN_gw_ElVent6StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent6Sts_st.gw_ElVent6StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent6Sts_st.gw_ElVent6StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent6Sts_st, sizeof(p_GW_vent6Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent7Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3CC_st_GW_vent7Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent7Sts_st, sizeof(p_GW_vent7Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7ErrorStatus = 0;
    }
    p_GW_vent7Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent7Sts_st.gw_ElVent7MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7MotorCurrentLocation_H = 0;
        p_GW_vent7Sts_st.gw_ElVent7MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent7Sts_ComIn_VeCAN_gw_ElVent7StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent7Sts_st.gw_ElVent7StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent7Sts_st.gw_ElVent7StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent7Sts_st, sizeof(p_GW_vent7Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_vent8Sts(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3CD_st_GW_vent8Sts signal_bk;
    memcpy(&signal_bk, &p_GW_vent8Sts_st, sizeof(p_GW_vent8Sts_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8ErrorStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8ErrorStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8ErrorStatus = 0;
    }
    p_GW_vent8Sts_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8OverHeatStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8OverHeatStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8OverHeatStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8ElectricalFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8ElectricalFailureSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8ElectricalFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8VoltageStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8VoltageStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8VoltageStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8EmergencyRunningSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8EmergencyRunningSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8EmergencyRunningSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8ObstructionDetect(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8ObstructionDetect = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8ObstructionDetect = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8ObstructionStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8ObstructionStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8ObstructionStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8ResetStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8ResetStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8ResetStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8CoilStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8CoilStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8CoilStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8LocationStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8LocationStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8LocationStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8SpeedStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8SpeedStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8SpeedStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8MotorCurrentLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8MotorCurrentLocation_H = (uint8_t)(Read_Signal >> 8);
        p_GW_vent8Sts_st.gw_ElVent8MotorCurrentLocation_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8MotorCurrentLocation_H = 0;
        p_GW_vent8Sts_st.gw_ElVent8MotorCurrentLocation_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8MotorDrivingDirection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8MotorDrivingDirection = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8MotorDrivingDirection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8TorqueKeepingSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8TorqueKeepingSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8TorqueKeepingSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8SpecialFunction(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8SpecialFunction = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8SpecialFunction = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8LocationActuator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8LocationActuator = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8LocationActuator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8EmgyStopSwitchSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8EmgyStopSwitchSts = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8EmgyStopSwitchSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8EmgyStopSLocation(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8EmgyStopSLocation = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8EmgyStopSLocation = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8RotationMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8RotationMode = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8RotationMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_vent8Sts_ComIn_VeCAN_gw_ElVent8StopStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_vent8Sts_st.gw_ElVent8StopStatus = (uint8_t)(Read_Signal);
    } else {
        p_GW_vent8Sts_st.gw_ElVent8StopStatus = 0;
    }

    if (memcmp(&signal_bk, &p_GW_vent8Sts_st, sizeof(p_GW_vent8Sts_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_BMS_meas(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x3DE_st_GW_BMS_meas signal_bk;
    memcpy(&signal_bk, &p_GW_BMS_meas_st, sizeof(p_GW_BMS_meas_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_BMS_meas_ComIn_VeCAN_bms_vPackBmu(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_BMS_meas_st.bms_vPackBmu_H = (uint8_t)(Read_Signal >> 8);
        p_GW_BMS_meas_st.bms_vPackBmu_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_BMS_meas_st.bms_vPackBmu_H = 0;
        p_GW_BMS_meas_st.bms_vPackBmu_L = 0;
    }
    p_GW_BMS_meas_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_BMS_meas_ComIn_VeCAN_bms_vPackBms(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_BMS_meas_st.bms_vPackBms_H = (uint8_t)(Read_Signal >> 8);
        p_GW_BMS_meas_st.bms_vPackBms_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_BMS_meas_st.bms_vPackBms_H = 0;
        p_GW_BMS_meas_st.bms_vPackBms_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_BMS_meas_ComIn_VeCAN_bms_iPack(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_BMS_meas_st.bms_iPack_H = (uint8_t)(Read_Signal >> 8);
        p_GW_BMS_meas_st.bms_iPack_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_BMS_meas_st.bms_iPack_H = 0;
        p_GW_BMS_meas_st.bms_iPack_L = 0;
    }

    if (memcmp(&signal_bk, &p_GW_BMS_meas_st, sizeof(p_GW_BMS_meas_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_BMS_state(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x31E_st_BMS_state signal_bk;
    memcpy(&signal_bk, &p_BMS_state_st, sizeof(p_BMS_state_st));

    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_state(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_state = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_state = 0;
    }
    p_BMS_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_dcChargeState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_dcChargeState = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_dcChargeState = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_acChargeState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_acChargeState = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_acChargeState = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_BMS_HVInterlock_Status(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.BMS_HVInterlock_Status = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.BMS_HVInterlock_Status = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_isolationState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_isolationState = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_isolationState = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_contactorState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_contactorState = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_contactorState = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_acChargeConnection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_acChargeConnection = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_acChargeConnection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_dcChargeConnection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_dcChargeConnection = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_dcChargeConnection = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_authenticationResult(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_authenticationResult = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_authenticationResult = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_alertLevel(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_alertLevel = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_alertLevel = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_BMS_state_ComIn_VeCAN_bms_pPack(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_BMS_state_st.bms_pPack_H = (uint8_t)(Read_Signal >> 8);
        p_BMS_state_st.bms_pPack_L = (uint8_t)(Read_Signal);
    } else {
        p_BMS_state_st.bms_pPack_H = 0;
        p_BMS_state_st.bms_pPack_L = 0;
    }

    if (memcmp(&signal_bk, &p_BMS_state_st, sizeof(p_BMS_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GTW_mcur0_info(void)
{
    uint8_t bResult = FALSE;
    uint32_t Read_Signal = 0;
    struct package_0x3AE_st_GTW_mcur0_info signal_bk;
    memcpy(&signal_bk, &p_GTW_mcur0_info_st, sizeof(p_GTW_mcur0_info_st));

    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_info_ComIn_VeCAN_mcur0_speed(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_info_st.mcur0_speed_H = (uint8_t)(Read_Signal >> 24);
        p_GTW_mcur0_info_st.mcur0_speed_MH = (uint8_t)(Read_Signal >> 16);
        p_GTW_mcur0_info_st.mcur0_speed_ML = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcur0_info_st.mcur0_speed_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_info_st.mcur0_speed_H = 0;
        p_GTW_mcur0_info_st.mcur0_speed_MH = 0;
        p_GTW_mcur0_info_st.mcur0_speed_ML = 0;
        p_GTW_mcur0_info_st.mcur0_speed_L = 0;
    }
    p_GTW_mcur0_info_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_info_ComIn_VeCAN_mcur0_iBus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_info_st.mcur0_iBus_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcur0_info_st.mcur0_iBus_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_info_st.mcur0_iBus_H = 0;
        p_GTW_mcur0_info_st.mcur0_iBus_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_info_ComIn_VeCAN_mcur0_vBus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_info_st.mcur0_vBus_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcur0_info_st.mcur0_vBus_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_info_st.mcur0_vBus_H = 0;
        p_GTW_mcur0_info_st.mcur0_vBus_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_info_ComIn_VeCAN_mcur0_stEgyFlowAndBatt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_info_st.mcur0_stEgyFlowAndBatt = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_info_st.mcur0_stEgyFlowAndBatt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_info_ComIn_VeCAN_mcur0_Fault_Light_Ctrl(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_info_st.mcur0_Fault_Light_Ctrl = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_info_st.mcur0_Fault_Light_Ctrl = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcur0_info_ComIn_VeCAN_mcur0_faultLevel(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcur0_info_st.mcur0_faultLevel = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcur0_info_st.mcur0_faultLevel = 0;
    }

    if (memcmp(&signal_bk, &p_GTW_mcur0_info_st, sizeof(p_GTW_mcur0_info_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GTW_mcuf0_info(void)
{
    uint8_t bResult = FALSE;
    uint32_t Read_Signal = 0;
    struct package_0x3BE_st_GTW_mcuf0_info signal_bk;
    memcpy(&signal_bk, &p_GTW_mcuf0_info_st, sizeof(p_GTW_mcuf0_info_st));

    bResult = Rte_Read_rpSR_CANMSG_GTW_mcuf0_info_ComIn_VeCAN_mcuf0_speed(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcuf0_info_st.mcuf0_speed_H = (uint8_t)(Read_Signal >> 24);
        p_GTW_mcuf0_info_st.mcuf0_speed_MH = (uint8_t)(Read_Signal >> 16);
        p_GTW_mcuf0_info_st.mcuf0_speed_ML = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcuf0_info_st.mcuf0_speed_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcuf0_info_st.mcuf0_speed_H = 0;
        p_GTW_mcuf0_info_st.mcuf0_speed_MH = 0;
        p_GTW_mcuf0_info_st.mcuf0_speed_ML = 0;
        p_GTW_mcuf0_info_st.mcuf0_speed_L = 0;
    }
    p_GTW_mcuf0_info_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcuf0_info_ComIn_VeCAN_mcuf0_iBus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcuf0_info_st.mcuf0_iBus_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcuf0_info_st.mcuf0_iBus_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcuf0_info_st.mcuf0_iBus_H = 0;
        p_GTW_mcuf0_info_st.mcuf0_iBus_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcuf0_info_ComIn_VeCAN_mcuf0_vBus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcuf0_info_st.mcuf0_vBus_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_mcuf0_info_st.mcuf0_vBus_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcuf0_info_st.mcuf0_vBus_H = 0;
        p_GTW_mcuf0_info_st.mcuf0_vBus_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcuf0_info_ComIn_VeCAN_mcuf0_stEgyFlowAndBatt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcuf0_info_st.mcuf0_stEgyFlowAndBatt = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcuf0_info_st.mcuf0_stEgyFlowAndBatt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcuf0_info_ComIn_VeCAN_mcuf0_Fault_Light_Ctrl(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcuf0_info_st.mcuf0_Fault_Light_Ctrl = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcuf0_info_st.mcuf0_Fault_Light_Ctrl = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_mcuf0_info_ComIn_VeCAN_mcuf0_faultLevel(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_mcuf0_info_st.mcuf0_faultLevel = (uint8_t)(Read_Signal);
    } else {
        p_GTW_mcuf0_info_st.mcuf0_faultLevel = 0;
    }

    if (memcmp(&signal_bk, &p_GTW_mcuf0_info_st, sizeof(p_GTW_mcuf0_info_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GTW_ecu_gcu_vcu_info(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x37E_st_GTW_ecu_gcu_vcu_info signal_bk;
    memcpy(&signal_bk, &p_GTW_ecu_gcu_vcu_info_st, sizeof(p_GTW_ecu_gcu_vcu_info_st));

    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_gcu_torqueEst(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.gcu_torqueEst_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_ecu_gcu_vcu_info_st.gcu_torqueEst_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.gcu_torqueEst_H = 0;
        p_GTW_ecu_gcu_vcu_info_st.gcu_torqueEst_L = 0;
    }
    p_GTW_ecu_gcu_vcu_info_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_ecu_engSpeed(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.ecu_engSpeed_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_ecu_gcu_vcu_info_st.ecu_engSpeed_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.ecu_engSpeed_H = 0;
        p_GTW_ecu_gcu_vcu_info_st.ecu_engSpeed_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_ecu_engCoolantTemp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.ecu_engCoolantTemp = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.ecu_engCoolantTemp = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_ecu_fuelComsump100ms(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.ecu_fuelComsump100ms_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_ecu_gcu_vcu_info_st.ecu_fuelComsump100ms_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.ecu_fuelComsump100ms_H = 0;
        p_GTW_ecu_gcu_vcu_info_st.ecu_fuelComsump100ms_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_ecu_milIndicator(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.ecu_milIndicator = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.ecu_milIndicator = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_vcu_coolantLevelLow(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.vcu_coolantLevelLow = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.vcu_coolantLevelLow = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_vcu_brakeLight(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.vcu_brakeLight = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.vcu_brakeLight = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_ecu_state(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.ecu_state = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.ecu_state = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_vcu_highVoltFail(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.vcu_highVoltFail = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.vcu_highVoltFail = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_ecu_gcu_vcu_info_ComIn_VeCAN_vcu_Regenmode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_ecu_gcu_vcu_info_st.vcu_Regenmode = (uint8_t)(Read_Signal);
    } else {
        p_GTW_ecu_gcu_vcu_info_st.vcu_Regenmode = 0;
    }

    if (memcmp(&signal_bk, &p_GTW_ecu_gcu_vcu_info_st, sizeof(p_GTW_ecu_gcu_vcu_info_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GTW_esc_eps_iB_info(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x223_st_GTW_esc_eps_iB_info signal_bk;
    memcpy(&signal_bk, &p_GTW_esc_eps_iB_info_st, sizeof(p_GTW_esc_eps_iB_info_st));

    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vehicleSpeed(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vehicleSpeed_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_esc_eps_iB_info_st.esc_vehicleSpeed_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vehicleSpeed_H = 0;
        p_GTW_esc_eps_iB_info_st.esc_vehicleSpeed_L = 0;
    }
    p_GTW_esc_eps_iB_info_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vehicleSpeedValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vehicleSpeedValid = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vehicleSpeedValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_absFault(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_absFault = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_absFault = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_avhActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_avhActive = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_avhActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_avhStandby(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_avhStandby = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_avhStandby = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_avhAvailable(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_avhAvailable = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_avhAvailable = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_hdcStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_hdcStatus = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_hdcStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_ebdFault(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_ebdFault = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_ebdFault = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_offStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_offStatus = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_offStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_escFault(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_escFault = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_escFault = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vlcTorqReq(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vlcTorqReq_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_esc_eps_iB_info_st.esc_vlcTorqReq_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vlcTorqReq_H = 0;
        p_GTW_esc_eps_iB_info_st.esc_vlcTorqReq_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vlcTorqReqActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vlcTorqReqActive = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vlcTorqReqActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vlcError(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vlcError = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vlcError = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vlcAvalible(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vlcAvalible = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vlcAvalible = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vlcInterTargetAx(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vlcInterTargetAx = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vlcInterTargetAx = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_vlcActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_vlcActive = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_vlcActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_eps_modeStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.eps_modeStatus = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.eps_modeStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_escActive(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_escActive = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_escActive = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_hdcAvailable(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_hdcAvailable = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_hdcAvailable = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_iB_hmiWarningOn(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.iB_hmiWarningOn = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.iB_hmiWarningOn = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_esc_eps_iB_info_ComIn_VeCAN_esc_hhcAvailable(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_esc_eps_iB_info_st.esc_hhcAvailable = (uint8_t)(Read_Signal);
    } else {
        p_GTW_esc_eps_iB_info_st.esc_hhcAvailable = 0;
    }

    if (memcmp(&signal_bk, &p_GTW_esc_eps_iB_info_st, sizeof(p_GTW_esc_eps_iB_info_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GW_EPS_state(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x353_st_GW_EPS_state signal_bk;
    memcpy(&signal_bk, &p_GW_EPS_state_st, sizeof(p_GW_EPS_state_st));

    bResult = Rte_Read_rpSR_CANMSG_GW_EPS_state_ComIn_VeCAN_eps_torsionBarTorque(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_EPS_state_st.eps_torsionBarTorque_H = (uint8_t)(Read_Signal >> 8);
        p_GW_EPS_state_st.eps_torsionBarTorque_L = (uint8_t)(Read_Signal);
    } else {
        p_GW_EPS_state_st.eps_torsionBarTorque_H = 0;
        p_GW_EPS_state_st.eps_torsionBarTorque_L = 0;
    }
    p_GW_EPS_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GW_EPS_state_ComIn_VeCAN_eps_torsionBarTorqueValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GW_EPS_state_st.eps_torsionBarTorqueValid = (uint8_t)(Read_Signal);
    } else {
        p_GW_EPS_state_st.eps_torsionBarTorqueValid = 0;
    }

    if (memcmp(&signal_bk, &p_GW_EPS_state_st, sizeof(p_GW_EPS_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_VCU_stateCha2(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x24E_st_VCU_stateCha2 signal_bk;
    memcpy(&signal_bk, &p_VCU_stateCha2_st, sizeof(p_VCU_stateCha2_st));

    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha2_ComIn_VeCAN_vcu_brakePedalSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha2_st.vcu_brakePedalSts = (uint8_t)(Read_Signal);
    } else {
        p_VCU_stateCha2_st.vcu_brakePedalSts = 0;
    }
    p_VCU_stateCha2_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha2_ComIn_VeCAN_vcu_brakePedalStsValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha2_st.vcu_brakePedalStsValid = (uint8_t)(Read_Signal);
    } else {
        p_VCU_stateCha2_st.vcu_brakePedalStsValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha2_ComIn_VeCAN_vcu_actualGearValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha2_st.vcu_actualGearValid = (uint8_t)(Read_Signal);
    } else {
        p_VCU_stateCha2_st.vcu_actualGearValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha2_ComIn_VeCAN_vcu_actualGear(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha2_st.vcu_actualGear = (uint8_t)(Read_Signal);
    } else {
        p_VCU_stateCha2_st.vcu_actualGear = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha2_ComIn_VeCAN_vcu_totalPowerConsumThisTrip(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha2_st.vcu_totalPowerConsumThisTrip_H = (uint8_t)(Read_Signal >> 8);
        p_VCU_stateCha2_st.vcu_totalPowerConsumThisTrip_L = (uint8_t)(Read_Signal);
    } else {
        p_VCU_stateCha2_st.vcu_totalPowerConsumThisTrip_H = 0;
        p_VCU_stateCha2_st.vcu_totalPowerConsumThisTrip_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha2_ComIn_VeCAN_vcu_241_rollingCounter(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha2_st.vcu_241_rollingCounter = (uint8_t)(Read_Signal);
    } else {
        p_VCU_stateCha2_st.vcu_241_rollingCounter = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_VCU_stateCha2_ComIn_VeCAN_vcu_241_checksum(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_VCU_stateCha2_st.vcu_241_checksum = (uint8_t)(Read_Signal);
    } else {
        p_VCU_stateCha2_st.vcu_241_checksum = 0;
    }

    if (memcmp(&signal_bk, &p_VCU_stateCha2_st, sizeof(p_VCU_stateCha2_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_AC_temp_pressure(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3CE_st_AC_temp_pressure signal_bk;
    memcpy(&signal_bk, &p_AC_temp_pressure_st, sizeof(p_AC_temp_pressure_st));

    bResult = Rte_Read_rpSR_CANMSG_AC_temp_pressure_ComIn_VeCAN_ac_ambientTemp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_temp_pressure_st.ac_ambientTemp = Read_Signal;
    } else {
        p_AC_temp_pressure_st.ac_ambientTemp = 0;
    }
    p_AC_temp_pressure_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_temp_pressure_ComIn_VeCAN_ac_cabinTemp(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_temp_pressure_st.ac_cabinTemp = Read_Signal;
    } else {
        p_AC_temp_pressure_st.ac_cabinTemp = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AC_temp_pressure_ComIn_VeCAN_ac_ambientTempValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AC_temp_pressure_st.ac_ambientTempValid = Read_Signal;
    } else {
        p_AC_temp_pressure_st.ac_ambientTempValid = 0;
    }

    if (memcmp(&signal_bk, &p_AC_temp_pressure_st, sizeof(p_AC_temp_pressure_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_WCM_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3AD_st_WCM_state signal_bk;
    memcpy(&signal_bk, &p_WCM_state_st, sizeof(p_WCM_state_st));

    bResult = Rte_Read_rpSR_CANMSG_WCM_state_ComIn_VeCAN_wcm_LeftchargingStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_WCM_state_st.wcm_LeftchargingStatus = Read_Signal;
    } else {
        p_WCM_state_st.wcm_LeftchargingStatus = 0;
    }
    p_WCM_state_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_WCM_state_ComIn_VeCAN_wcm_failureStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_WCM_state_st.wcm_failureStatus = Read_Signal;
    } else {
        p_WCM_state_st.wcm_failureStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_WCM_state_ComIn_VeCAN_wcm_workingStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_WCM_state_st.wcm_workingStatus = Read_Signal;
    } else {
        p_WCM_state_st.wcm_workingStatus = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_WCM_state_ComIn_VeCAN_wcm_selfCheckToIVI(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_WCM_state_st.wcm_selfCheckToIVI = Read_Signal;
    } else {
        p_WCM_state_st.wcm_selfCheckToIVI = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_WCM_state_ComIn_VeCAN_WCM_PhoneReminder(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_WCM_state_st.WCM_PhoneReminder = Read_Signal;
    } else {
        p_WCM_state_st.WCM_PhoneReminder = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_WCM_state_ComIn_VeCAN_wcm_onOffFeedback(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_WCM_state_st.wcm_onOffFeedback = Read_Signal;
    } else {
        p_WCM_state_st.wcm_onOffFeedback = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_WCM_state_ComIn_VeCAN_wcm_RightchargingStatus(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_WCM_state_st.wcm_RightchargingStatus = Read_Signal;
    } else {
        p_WCM_state_st.wcm_RightchargingStatus = 0;
    }

    if (memcmp(&signal_bk, &p_WCM_state_st, sizeof(p_WCM_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_AVM_state_484(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x484_st_AVM_state_484 signal_bk;
    memcpy(&signal_bk, &p_AVM_state_484_st, sizeof(p_AVM_state_484_st));

    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_apa_sts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_apa_sts = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_apa_sts = 0;
    }
    p_AVM_state_484_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_SentryModeFB(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_SentryModeFB = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_SentryModeFB = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_sysFailureSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_sysFailureSts = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_sysFailureSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_singleViewSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_singleViewSts = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_singleViewSts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_apa_FrontCameraFailure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_apa_FrontCameraFailure = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_apa_FrontCameraFailure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_apa_RearCameraFailure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_apa_RearCameraFailure = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_apa_RearCameraFailure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_apa_LeftCameraFailure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_apa_LeftCameraFailure = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_apa_LeftCameraFailure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_AVM_apa_RightCameraFailure(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.AVM_apa_RightCameraFailure = Read_Signal;
    } else {
        p_AVM_state_484_st.AVM_apa_RightCameraFailure = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_AVM_state_484_ComIn_VeCAN_APA_laeb_SW_Sts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_AVM_state_484_st.APA_laeb_SW_Sts = Read_Signal;
    } else {
        p_AVM_state_484_st.APA_laeb_SW_Sts = 0;
    }

    if (memcmp(&signal_bk, &p_AVM_state_484_st, sizeof(p_AVM_state_484_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_HUD_state(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x3FA_st_HUD_state signal_bk;
    memcpy(&signal_bk, &p_HUD_state_st, sizeof(p_HUD_state_st));

    bResult = Rte_Read_rpSR_CANMSG_HUD_state_ComIn_VeCAN_hud_onOffSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_HUD_state_st.hud_onOffSts = Read_Signal;
    } else {
        p_HUD_state_st.hud_onOffSts = 0;
    }
    p_HUD_state_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_HUD_state_st, sizeof(p_HUD_state_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MFW_Ctrl(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x0A9_st_MFW_Ctrl signal_bk;
    memcpy(&signal_bk, &p_MFW_Ctrl_st, sizeof(p_MFW_Ctrl_st));

    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_PRE_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_PRE_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_PRE_Key = 0;
    }
    p_MFW_Ctrl_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_NEXT_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_NEXT_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_NEXT_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_VolumeUp_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_VolumeUp_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_VolumeUp_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_VolumeDown_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_VolumeDown_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_VolumeDown_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_PlayPause_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_PlayPause_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_PlayPause_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_Answer_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_Answer_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_Answer_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_HangUp_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_HangUp_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_HangUp_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_APA_AVM_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_APA_AVM_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_APA_AVM_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_PageUP_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_PageUP_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_PageUP_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_PageDown_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_PageDown_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_PageDown_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_Interface_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_Interface_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_Interface_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_VoiceButton_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_VoiceButton_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_VoiceButton_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_CustomButton1_Key(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_CustomButton1_Key = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_CustomButton1_Key = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_ExhibitionMode(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_ExhibitionMode = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_ExhibitionMode = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_TJAICAACTIVEKeySts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_TJAICAACTIVEKeySts = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_TJAICAACTIVEKeySts = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_TJAICAACTIVEKeyStsValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_TJAICAACTIVEKeyStsValid = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_TJAICAACTIVEKeyStsValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_Ctrl_ComIn_VeCAN_MFW_IVI_Reset(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_Ctrl_st.MFW_IVI_Reset = Read_Signal;
    } else {
        p_MFW_Ctrl_st.MFW_IVI_Reset = 0;
    }

    if (memcmp(&signal_bk, &p_MFW_Ctrl_st, sizeof(p_MFW_Ctrl_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_MFW_KeySt(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x498_st_MFW_KeySt signal_bk;
    memcpy(&signal_bk, &p_MFW_KeySt_st, sizeof(p_MFW_KeySt_st));

    bResult = Rte_Read_rpSR_CANMSG_MFW_KeySt_ComIn_VeCAN_MFW_PRE_KeySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_KeySt_st.MFW_PRE_KeySt = Read_Signal;
    } else {
        p_MFW_KeySt_st.MFW_PRE_KeySt = 0;
    }
    p_MFW_KeySt_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_KeySt_ComIn_VeCAN_MFW_NEXT_KeySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_KeySt_st.MFW_NEXT_KeySt = Read_Signal;
    } else {
        p_MFW_KeySt_st.MFW_NEXT_KeySt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_KeySt_ComIn_VeCAN_MFW_PlayPause_KeySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_KeySt_st.MFW_PlayPause_KeySt = Read_Signal;
    } else {
        p_MFW_KeySt_st.MFW_PlayPause_KeySt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_KeySt_ComIn_VeCAN_MFW_Answer_KeySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_KeySt_st.MFW_Answer_KeySt = Read_Signal;
    } else {
        p_MFW_KeySt_st.MFW_Answer_KeySt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_KeySt_ComIn_VeCAN_MFW_HangUp_KeySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_KeySt_st.MFW_HangUp_KeySt = Read_Signal;
    } else {
        p_MFW_KeySt_st.MFW_HangUp_KeySt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_KeySt_ComIn_VeCAN_MFW_VoiceButton_KeySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_KeySt_st.MFW_VoiceButton_KeySt = Read_Signal;
    } else {
        p_MFW_KeySt_st.MFW_VoiceButton_KeySt = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_MFW_KeySt_ComIn_VeCAN_MFW_CustomButton1_KeySt(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_MFW_KeySt_st.MFW_CustomButton1_KeySt = Read_Signal;
    } else {
        p_MFW_KeySt_st.MFW_CustomButton1_KeySt = 0;
    }

    if (memcmp(&signal_bk, &p_MFW_KeySt_st, sizeof(p_MFW_KeySt_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_IVI_timeAndGPS(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x4F5_st_IVI_timeAndGPS signal_bk;
    memcpy(&signal_bk, &p_IVI_timeAndGPS_st, sizeof(p_IVI_timeAndGPS_st));

    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_timeInfoSecond(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_timeInfoSecond = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_timeInfoSecond = 0;
    }
    p_IVI_timeAndGPS_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_timeInfoMinute(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_timeInfoMinute = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_timeInfoMinute = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_timeInfoHour(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_timeInfoHour = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_timeInfoHour = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_timeInfoDay(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_timeInfoDay = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_timeInfoDay = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_timeInfoMonth(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_timeInfoMonth = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_timeInfoMonth = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_timeInfoYear(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_timeInfoYear = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_timeInfoYear = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_timeValid(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_timeValid = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_timeValid = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_longitude(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_longitude_H = (uint8_t)(Read_Signal >> 8);
        p_IVI_timeAndGPS_st.IVI_longitude_L = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_longitude_H = 0;
        p_IVI_timeAndGPS_st.IVI_longitude_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_IVI_timeAndGPS_ComIn_VeCAN_IVI_latitude(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_IVI_timeAndGPS_st.IVI_latitude_H = (uint8_t)(Read_Signal >> 8);
        p_IVI_timeAndGPS_st.IVI_latitude_L = (uint8_t)(Read_Signal);
    } else {
        p_IVI_timeAndGPS_st.IVI_latitude_H = 0;
        p_IVI_timeAndGPS_st.IVI_latitude_L = 0;
    }

    if (memcmp(&signal_bk, &p_IVI_timeAndGPS_st, sizeof(p_IVI_timeAndGPS_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_GTW_BMS_Rev(void)
{
    uint8_t bResult = FALSE;
    uint16_t Read_Signal = 0;
    struct package_0x35E_st_GTW_BMS_Rev signal_bk;
    memcpy(&signal_bk, &p_GTW_BMS_Rev_st, sizeof(p_GTW_BMS_Rev_st));

    bResult = Rte_Read_rpSR_CANMSG_GTW_BMS_Rev_ComIn_VeCAN_obc_acVoltage(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_BMS_Rev_st.obc_acVoltage_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_BMS_Rev_st.obc_acVoltage_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_BMS_Rev_st.obc_acVoltage_H = 0;
        p_GTW_BMS_Rev_st.obc_acVoltage_L = 0;
    }
    p_GTW_BMS_Rev_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_BMS_Rev_ComIn_VeCAN_obc_acCurrent(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_BMS_Rev_st.obc_acCurrent_H = (uint8_t)(Read_Signal >> 8);
        p_GTW_BMS_Rev_st.obc_acCurrent_L = (uint8_t)(Read_Signal);
    } else {
        p_GTW_BMS_Rev_st.obc_acCurrent_H = 0;
        p_GTW_BMS_Rev_st.obc_acCurrent_L = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_BMS_Rev_ComIn_VeCAN_CCU_CompressorState(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_BMS_Rev_st.CCU_CompressorState = (uint8_t)(Read_Signal);
    } else {
        p_GTW_BMS_Rev_st.CCU_CompressorState = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_BMS_Rev_ComIn_VeCAN_vcu_PTC_Request(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_BMS_Rev_st.vcu_PTC_Request = (uint8_t)(Read_Signal);
    } else {
        p_GTW_BMS_Rev_st.vcu_PTC_Request = 0;
    }

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_GTW_BMS_Rev_ComIn_VeCAN_bms_v2vChrgConnection(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_GTW_BMS_Rev_st.bms_v2vChrgConnection = (uint8_t)(Read_Signal);
    } else {
        p_GTW_BMS_Rev_st.bms_v2vChrgConnection = 0;
    }

    if (memcmp(&signal_bk, &p_GTW_BMS_Rev_st, sizeof(p_GTW_BMS_Rev_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_Diag_PhyReq_IVI(void)
{
    uint8_t bResult = FALSE;
    uint64_t Read_Signal = 0;
    struct package_0x725_st_Diag_PhyReq_IVI signal_bk;
    memcpy(&signal_bk, &p_Diag_PhyReq_IVI_st, sizeof(p_Diag_PhyReq_IVI_st));

    bResult = Rte_Read_rpSR_CANMSG_Diag_PhyReq_IVI_ComIn_VeCAN_Diag_PhyReq_IVI_Data(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_8 = (uint8_t)(Read_Signal >> 56);
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_7 = (uint8_t)(Read_Signal >> 48);
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_6 = (uint8_t)(Read_Signal >> 40);
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_5 = (uint8_t)(Read_Signal >> 32);
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_4 = (uint8_t)(Read_Signal >> 24);
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_3 = (uint8_t)(Read_Signal >> 16);
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_2 = (uint8_t)(Read_Signal >> 8);
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_1 = (uint8_t)(Read_Signal);
    } else {
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_8 = 0;
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_7 = 0;
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_6 = 0;
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_5 = 0;
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_4 = 0;
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_3 = 0;
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_2 = 0;
        p_Diag_PhyReq_IVI_st.Diag_PhyReq_IVI_Data_1 = 0;
    }
    p_Diag_PhyReq_IVI_st.data_status = bResult;

    if (memcmp(&signal_bk, &p_Diag_PhyReq_IVI_st, sizeof(p_Diag_PhyReq_IVI_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL getSignal_SWHC_400(void)
{
    uint8_t bResult = FALSE;
    uint8_t Read_Signal = 0;
    struct package_0x400_st_SWHC_400 signal_bk;
    memcpy(&signal_bk, &p_SWHC_400_st, sizeof(p_SWHC_400_st));

    bResult = Rte_Read_rpSR_CANMSG_SWHC_400_ComIn_VeCAN_SWHC_SterringWheelHeatSts(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SWHC_400_st.SWHC_SterringWheelHeatSts = Read_Signal;
    } else {
        p_SWHC_400_st.SWHC_SterringWheelHeatSts = 0;
    }
    p_SWHC_400_st.data_status = bResult;

    Read_Signal = 0;
    bResult = Rte_Read_rpSR_CANMSG_SWHC_400_ComIn_VeCAN_SWHC_SterringWheelHeatFaultReason(&Read_Signal);
    if (bResult == RTE_SIG_OK) {
        p_SWHC_400_st.SWHC_SterringWheelHeatFaultReason = Read_Signal;
    } else {
        p_SWHC_400_st.SWHC_SterringWheelHeatFaultReason = 0;
    }

    if (memcmp(&signal_bk, &p_SWHC_400_st, sizeof(p_SWHC_400_st)) == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}



