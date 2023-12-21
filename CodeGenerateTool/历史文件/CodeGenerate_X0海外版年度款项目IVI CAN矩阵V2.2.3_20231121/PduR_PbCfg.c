/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by APPSYS and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with APPSYS in writing by applicable law.
 */
/**
 * @file    PduR_PbCfg.c
 * @brief   brief function description.
 * @details detailed function description.
 * @version 1.0
 * @author  wenzc
 * @date    2019-05-21
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2019-05-21               appsys             Create it.
 */

#include "PduR.h"
#include "MemMap.h"
#include "PduR_Cfg.h"
#include "PduR_PbCfg.h"
#if PDUR_CANIF_SUPPORT == STD_ON
#include "CanIf.h"
#include "CanIf_PBCfg.h"
#endif
#if PDUR_CANNM_SUPPORT == STD_ON
#include "CanNm.h"
#include "CanNm_PBCfg.h"
#endif
#if PDUR_UDPNM_SUPPORT == STD_ON
#include "UdpNm.h"
#include "UdpNm_PBCfg.h"
#endif
#if PDUR_CANTP_SUPPORT == STD_ON
#include "CanTp.h"
#include "CanTp_PBCfg.h"
#endif
#if PDUR_LINIF_SUPPORT == STD_ON
#include "LinIf.h"
#endif
#if PDUR_CDD_LINSLV_SUPPORT == STD_ON
#include "CDD_LinSlv.h"
#endif
#if PDUR_CDDPDUR_SUPPORT == STD_ON
#include "CddPduR.h"
#endif
#if PDUR_COM_SUPPORT == STD_ON
#include "Com.h"
#include "Com_PbCfg.h"
#endif
#if PDUR_DCM_SUPPORT == STD_ON
#include "Dcm.h"
#endif
#if PDUR_SOAD_SUPPORT == STD_ON
#include "SoAd.h"
#endif
#if PDUR_J1939TP_SUPPORT == STD_ON
#include "J1939Tp.h"
#endif
#if PDUR_IPDUM_SUPPORT == STD_ON
#include "IpduM.h"
#endif
#if PDUR_SECOC_SUPPORT == STD_ON
#include "SecOC.h"
#endif
#if PDUR_FRIF_SUPPORT == STD_ON
#include "FrIf.h"
#include "FrIf_PBcfg.h"
#endif
#if PDUR_FRNM_SUPPORT == STD_ON
#include "FrNm.h"
#include "FrNm_Cfg.h"
#endif
#if PDUR_FRTP_SUPPORT == STD_ON
#include "FrTp.h"
#include "FrTp_PBCfg.h"
#endif
#if PDUR_LDCOM_SUPPORT == STD_ON
#include "LdCom.h"
#include "LdCom_PBCfg.h"
#endif

PduR_RoutingPathGroupIdType Pdur_RoutingPathGroupRefs[PDUR_MAX_NOF_ROUTING_PATH_GROUPS];
const PduR_RoutingPathGroupType Pdur_RoutingPathGroups = {
    .Destinations = NULL,
    .NofDestinations = NULL,
    .EnabledAtInit = 1
};


const PduRDestPdu_type PduRDestination_TBOX_chargeSet_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x35F_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BMS_metric_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x514_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BMS_tboxRequest_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x574_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_range_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x561_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_range1_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x351_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x111_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_OBC_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x387_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_OBC_state1_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x407_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_DCDC_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x38D_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GSM_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x309_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GTW_mcur0_mcuf0_info_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x38A_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BMS_temperature_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x304_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_Info_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x331_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_Diag_FuncReq_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_DCM,
    .DestPduId      = DCM_PDU_ID_DIAGFUNCTIONALRX,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_info_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x4F3_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_pwr_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x301_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_RevV2V_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x330_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BMS_ASSt_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3A4_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_stateCha1_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3A1_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_EPS_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x124_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_EPS_sas_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x144_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_wheelSpd_Front_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x142_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_wheelSpd_Rear_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x122_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_state1_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x212_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_state2_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x2A2_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_yawState_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x252_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_ESC_yawState_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3FB_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_wssFront_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x272_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_wssRear_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x282_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ESC_epb_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x2C2_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_acc_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x219_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_pss_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x239_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_hmi1_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x349_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_hmi2_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x369_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_hmi3_34E_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x34E_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_hmi4_34F_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x34F_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_hmi5_355_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x355_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MRR_hmi6_356_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x356_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MPC_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x21A_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MPC_hmi_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x35A_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MPC_RoadState_359_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x359_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MPC_hmi_35D_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x35D_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_SRR_R_state_22B_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x22B_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_ABM_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x380_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_APA_35B_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x35B_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_SLA_408_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x408_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_state2_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3B1_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BLE_FB_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x347_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BLE_User_ID_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x375_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_User_ID_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x376_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_TBOX_Factory_360_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x360_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_AC_ctrlFeedback_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3B6_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_AC_state2_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x386_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x2A1_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_state2_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3C1_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_state3_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3C2_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_state4_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x305_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_tpms_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x411_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_tpms1_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x421_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_peps_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x2C1_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_rsm_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3D1_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BCM_RemotFB_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x5C3_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_096_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x096_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_LCU_32A_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x32A_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_PLG_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x394_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_Handle_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x335_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_DSM_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3D5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_PSM_memory_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3D6_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_DSM_memory_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3D4_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_PSM_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x318_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_LRSM_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x31A_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_TBOX_infoCtrl_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x0A8_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_control_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x075_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_comfortSet_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x095_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_pwrSet_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x0A5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_chassisSet1_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x1D5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_chassisSet_065_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x065_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_dvrSet_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x105_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_dsmmSet_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x098_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_dsmmSet2_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x093_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_infoSet_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x0C5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VSP_state_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3A0_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_infoSet2_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x0C6_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_AVMSet_3D2_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3D2_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_scuSet_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x0F5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent1Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x31C_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent2Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x31D_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent3Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x325_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent4Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x328_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent5Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x33A_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent6Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x33B_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent7Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x34A_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_vent8Ctrl_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x34B_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent1Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3C6_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent2Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3C7_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent3Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3C8_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent4Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3C9_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent5Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3CA_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent6Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3CB_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent7Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3CC_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_vent8Sts_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3CD_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_NaviChrgSt_33D_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x33D_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_NaviChrgSt_33E_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x33E_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_engineOFF_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x052_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_faultSum_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x5FD_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_infoSet_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3F2_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_3F8_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3F8_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_state3_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x4F4_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_Warning_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x571_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_Warningfb_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x570_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_BMS_meas_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3DE_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_BMS_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x31E_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GTW_mcur0_info_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3AE_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GTW_mcuf0_info_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3BE_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GTW_ecu_gcu_vcu_info_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x37E_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GTW_esc_eps_iB_info_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x223_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GW_EPS_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x353_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_VCU_stateCha2_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x24E_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_AC_temp_pressure_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3CE_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_WCM_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3AD_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_AVM_state_484_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x484_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_HUD_state_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x3FA_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MFW_Ctrl_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x0A9_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_MFW_KeySt_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x498_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_state_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x2F2_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_info2_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3F7_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_state1_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x482_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_EnergyConsumption_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x491_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_state2_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x492_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_state4_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x493_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_state5_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x494_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_StatusAndNotify_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x495_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_hmi_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x496_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_State_5F0_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x5F0_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IC_RequestAndStatus_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x4A2_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_set_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3B5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_timeAndGPS_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x4F5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_navi_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x485_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_NaviDirection_LaneX_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x486_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_media_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x395_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_naviText_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3C5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_TelSongText_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3A5_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_GTW_BMS_Rev_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x35E_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_Diag_PhyReq_IVI_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_DCM,
    .DestPduId      = DCM_PDU_ID_DIAGPHYSICALRX,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_Diag_Resp_IVI_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANTP,
    .DestPduId      = CANTP_PDU_ID_DIAGPHYSICALTX,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_IVI_ADAS_3E1_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x3E1_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_Wacc_500_INFO_Tx_PduRDestPdu = {
    .DestModule     = AS_PDUR_CANIF,
    .DestPduId      = CANIF_PDU_ID_0x500_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};
const PduRDestPdu_type PduRDestination_SWHC_400_INFO_Rx_PduRDestPdu = {
    .DestModule     = AS_PDUR_COM,
    .DestPduId      = ComConf_ComIPdu_0x400_INFO,
    .NofGroupRefs = 0,
    .RoutingPathGroupRefs = NULL,
    .DataProvision  = PDUR_NO_PROVISION,
    .TxBufferId     =  PDUR_NO_BUFFER
};


const PduRDestPdu_type * const PduRDestinations_TBOX_chargeSet_INFO_Rx[] = {
    &PduRDestination_TBOX_chargeSet_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BMS_metric_INFO_Rx[] = {
    &PduRDestination_BMS_metric_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BMS_tboxRequest_INFO_Rx[] = {
    &PduRDestination_BMS_tboxRequest_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_range_INFO_Rx[] = {
    &PduRDestination_VCU_range_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_range1_INFO_Rx[] = {
    &PduRDestination_VCU_range1_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_state_INFO_Rx[] = {
    &PduRDestination_VCU_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_OBC_state_INFO_Rx[] = {
    &PduRDestination_OBC_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_OBC_state1_INFO_Rx[] = {
    &PduRDestination_OBC_state1_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_DCDC_state_INFO_Rx[] = {
    &PduRDestination_DCDC_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GSM_state_INFO_Rx[] = {
    &PduRDestination_GSM_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GTW_mcur0_mcuf0_info_INFO_Rx[] = {
    &PduRDestination_GTW_mcur0_mcuf0_info_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BMS_temperature_INFO_Rx[] = {
    &PduRDestination_BMS_temperature_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_Info_INFO_Rx[] = {
    &PduRDestination_VCU_Info_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_Diag_FuncReq_INFO_Rx[] = {
    &PduRDestination_Diag_FuncReq_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_info_INFO_Tx[] = {
    &PduRDestination_IC_info_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_pwr_INFO_Rx[] = {
    &PduRDestination_VCU_pwr_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_RevV2V_INFO_Rx[] = {
    &PduRDestination_VCU_RevV2V_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BMS_ASSt_INFO_Rx[] = {
    &PduRDestination_BMS_ASSt_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_stateCha1_INFO_Rx[] = {
    &PduRDestination_VCU_stateCha1_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_EPS_state_INFO_Rx[] = {
    &PduRDestination_EPS_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_EPS_sas_INFO_Rx[] = {
    &PduRDestination_EPS_sas_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_wheelSpd_Front_INFO_Rx[] = {
    &PduRDestination_ESC_wheelSpd_Front_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_wheelSpd_Rear_INFO_Rx[] = {
    &PduRDestination_ESC_wheelSpd_Rear_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_state1_INFO_Rx[] = {
    &PduRDestination_ESC_state1_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_state2_INFO_Rx[] = {
    &PduRDestination_ESC_state2_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_yawState_INFO_Rx[] = {
    &PduRDestination_ESC_yawState_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_ESC_yawState_INFO_Rx[] = {
    &PduRDestination_GW_ESC_yawState_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_wssFront_INFO_Rx[] = {
    &PduRDestination_ESC_wssFront_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_wssRear_INFO_Rx[] = {
    &PduRDestination_ESC_wssRear_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ESC_epb_INFO_Rx[] = {
    &PduRDestination_ESC_epb_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_acc_INFO_Rx[] = {
    &PduRDestination_MRR_acc_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_pss_INFO_Rx[] = {
    &PduRDestination_MRR_pss_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_hmi1_INFO_Rx[] = {
    &PduRDestination_MRR_hmi1_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_hmi2_INFO_Rx[] = {
    &PduRDestination_MRR_hmi2_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_hmi3_34E_INFO_Rx[] = {
    &PduRDestination_MRR_hmi3_34E_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_hmi4_34F_INFO_Rx[] = {
    &PduRDestination_MRR_hmi4_34F_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_hmi5_355_INFO_Rx[] = {
    &PduRDestination_MRR_hmi5_355_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MRR_hmi6_356_INFO_Rx[] = {
    &PduRDestination_MRR_hmi6_356_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MPC_state_INFO_Rx[] = {
    &PduRDestination_MPC_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MPC_hmi_INFO_Rx[] = {
    &PduRDestination_MPC_hmi_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MPC_RoadState_359_INFO_Rx[] = {
    &PduRDestination_MPC_RoadState_359_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MPC_hmi_35D_INFO_Rx[] = {
    &PduRDestination_MPC_hmi_35D_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_SRR_R_state_22B_INFO_Rx[] = {
    &PduRDestination_SRR_R_state_22B_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_ABM_state_INFO_Rx[] = {
    &PduRDestination_ABM_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_APA_35B_INFO_Rx[] = {
    &PduRDestination_APA_35B_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_SLA_408_INFO_Tx[] = {
    &PduRDestination_IVI_SLA_408_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_state2_INFO_Rx[] = {
    &PduRDestination_VCU_state2_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BLE_FB_INFO_Rx[] = {
    &PduRDestination_BLE_FB_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BLE_User_ID_INFO_Rx[] = {
    &PduRDestination_BLE_User_ID_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_User_ID_INFO_Tx[] = {
    &PduRDestination_IVI_User_ID_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_TBOX_Factory_360_INFO_Rx[] = {
    &PduRDestination_TBOX_Factory_360_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_AC_ctrlFeedback_INFO_Rx[] = {
    &PduRDestination_AC_ctrlFeedback_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_AC_state2_INFO_Rx[] = {
    &PduRDestination_AC_state2_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_state_INFO_Rx[] = {
    &PduRDestination_BCM_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_state2_INFO_Rx[] = {
    &PduRDestination_BCM_state2_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_state3_INFO_Rx[] = {
    &PduRDestination_BCM_state3_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_state4_INFO_Rx[] = {
    &PduRDestination_BCM_state4_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_tpms_INFO_Rx[] = {
    &PduRDestination_BCM_tpms_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_tpms1_INFO_Rx[] = {
    &PduRDestination_BCM_tpms1_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_peps_INFO_Rx[] = {
    &PduRDestination_BCM_peps_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_rsm_INFO_Rx[] = {
    &PduRDestination_BCM_rsm_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BCM_RemotFB_INFO_Rx[] = {
    &PduRDestination_BCM_RemotFB_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_096_INFO_Tx[] = {
    &PduRDestination_IVI_096_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_LCU_32A_INFO_Rx[] = {
    &PduRDestination_LCU_32A_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_PLG_state_INFO_Rx[] = {
    &PduRDestination_PLG_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_Handle_state_INFO_Rx[] = {
    &PduRDestination_GW_Handle_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_DSM_state_INFO_Rx[] = {
    &PduRDestination_DSM_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_PSM_memory_INFO_Rx[] = {
    &PduRDestination_PSM_memory_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_DSM_memory_INFO_Rx[] = {
    &PduRDestination_DSM_memory_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_PSM_state_INFO_Rx[] = {
    &PduRDestination_PSM_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_LRSM_state_INFO_Rx[] = {
    &PduRDestination_LRSM_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_TBOX_infoCtrl_INFO_Rx[] = {
    &PduRDestination_TBOX_infoCtrl_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_control_INFO_Tx[] = {
    &PduRDestination_IVI_control_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_comfortSet_INFO_Tx[] = {
    &PduRDestination_IVI_comfortSet_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_pwrSet_INFO_Tx[] = {
    &PduRDestination_IVI_pwrSet_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_chassisSet1_INFO_Tx[] = {
    &PduRDestination_IVI_chassisSet1_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_chassisSet_065_INFO_Tx[] = {
    &PduRDestination_IVI_chassisSet_065_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_dvrSet_INFO_Tx[] = {
    &PduRDestination_IVI_dvrSet_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_dsmmSet_INFO_Tx[] = {
    &PduRDestination_IVI_dsmmSet_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_dsmmSet2_INFO_Tx[] = {
    &PduRDestination_IVI_dsmmSet2_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_infoSet_INFO_Tx[] = {
    &PduRDestination_IVI_infoSet_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VSP_state_INFO_Tx[] = {
    &PduRDestination_VSP_state_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_infoSet2_INFO_Tx[] = {
    &PduRDestination_IVI_infoSet2_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_AVMSet_3D2_INFO_Tx[] = {
    &PduRDestination_IVI_AVMSet_3D2_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_scuSet_INFO_Tx[] = {
    &PduRDestination_IVI_scuSet_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent1Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent1Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent2Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent2Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent3Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent3Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent4Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent4Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent5Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent5Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent6Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent6Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent7Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent7Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_vent8Ctrl_INFO_Tx[] = {
    &PduRDestination_IVI_vent8Ctrl_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent1Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent1Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent2Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent2Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent3Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent3Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent4Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent4Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent5Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent5Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent6Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent6Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent7Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent7Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_vent8Sts_INFO_Rx[] = {
    &PduRDestination_GW_vent8Sts_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_NaviChrgSt_33D_INFO_Tx[] = {
    &PduRDestination_IVI_NaviChrgSt_33D_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_NaviChrgSt_33E_INFO_Tx[] = {
    &PduRDestination_IVI_NaviChrgSt_33E_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_engineOFF_INFO_Tx[] = {
    &PduRDestination_IC_engineOFF_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_faultSum_INFO_Tx[] = {
    &PduRDestination_IC_faultSum_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_infoSet_INFO_Tx[] = {
    &PduRDestination_IC_infoSet_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_3F8_INFO_Tx[] = {
    &PduRDestination_IC_3F8_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_state3_INFO_Tx[] = {
    &PduRDestination_IC_state3_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_Warning_INFO_Tx[] = {
    &PduRDestination_IC_Warning_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_Warningfb_INFO_Tx[] = {
    &PduRDestination_IC_Warningfb_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_BMS_meas_INFO_Rx[] = {
    &PduRDestination_GW_BMS_meas_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_BMS_state_INFO_Rx[] = {
    &PduRDestination_BMS_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GTW_mcur0_info_INFO_Rx[] = {
    &PduRDestination_GTW_mcur0_info_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GTW_mcuf0_info_INFO_Rx[] = {
    &PduRDestination_GTW_mcuf0_info_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GTW_ecu_gcu_vcu_info_INFO_Rx[] = {
    &PduRDestination_GTW_ecu_gcu_vcu_info_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GTW_esc_eps_iB_info_INFO_Rx[] = {
    &PduRDestination_GTW_esc_eps_iB_info_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GW_EPS_state_INFO_Rx[] = {
    &PduRDestination_GW_EPS_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_VCU_stateCha2_INFO_Rx[] = {
    &PduRDestination_VCU_stateCha2_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_AC_temp_pressure_INFO_Rx[] = {
    &PduRDestination_AC_temp_pressure_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_WCM_state_INFO_Rx[] = {
    &PduRDestination_WCM_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_AVM_state_484_INFO_Rx[] = {
    &PduRDestination_AVM_state_484_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_HUD_state_INFO_Rx[] = {
    &PduRDestination_HUD_state_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MFW_Ctrl_INFO_Rx[] = {
    &PduRDestination_MFW_Ctrl_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_MFW_KeySt_INFO_Rx[] = {
    &PduRDestination_MFW_KeySt_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_state_INFO_Tx[] = {
    &PduRDestination_IC_state_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_info2_INFO_Tx[] = {
    &PduRDestination_IC_info2_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_state1_INFO_Tx[] = {
    &PduRDestination_IC_state1_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_EnergyConsumption_INFO_Tx[] = {
    &PduRDestination_IC_EnergyConsumption_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_state2_INFO_Tx[] = {
    &PduRDestination_IC_state2_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_state4_INFO_Tx[] = {
    &PduRDestination_IC_state4_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_state5_INFO_Tx[] = {
    &PduRDestination_IC_state5_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_StatusAndNotify_INFO_Tx[] = {
    &PduRDestination_IVI_StatusAndNotify_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_hmi_INFO_Tx[] = {
    &PduRDestination_IVI_hmi_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_State_5F0_INFO_Tx[] = {
    &PduRDestination_IVI_State_5F0_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IC_RequestAndStatus_INFO_Tx[] = {
    &PduRDestination_IC_RequestAndStatus_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_set_INFO_Tx[] = {
    &PduRDestination_IVI_set_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_timeAndGPS_INFO_Rx[] = {
    &PduRDestination_IVI_timeAndGPS_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_navi_INFO_Tx[] = {
    &PduRDestination_IVI_navi_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_NaviDirection_LaneX_INFO_Tx[] = {
    &PduRDestination_IVI_NaviDirection_LaneX_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_media_INFO_Tx[] = {
    &PduRDestination_IVI_media_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_naviText_INFO_Tx[] = {
    &PduRDestination_IVI_naviText_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_TelSongText_INFO_Tx[] = {
    &PduRDestination_IVI_TelSongText_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_GTW_BMS_Rev_INFO_Rx[] = {
    &PduRDestination_GTW_BMS_Rev_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_Diag_PhyReq_IVI_INFO_Rx[] = {
    &PduRDestination_Diag_PhyReq_IVI_INFO_Rx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_Diag_Resp_IVI_INFO_Tx[] = {
    &PduRDestination_Diag_Resp_IVI_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_IVI_ADAS_3E1_INFO_Tx[] = {
    &PduRDestination_IVI_ADAS_3E1_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_Wacc_500_INFO_Tx[] = {
    &PduRDestination_Wacc_500_INFO_Tx_PduRDestPdu,
    NULL
};
const PduRDestPdu_type * const PduRDestinations_SWHC_400_INFO_Rx[] = {
    &PduRDestination_SWHC_400_INFO_Rx_PduRDestPdu,
    NULL
};


const PduRRoutingPath_type PduRRoutingPath_TBOX_chargeSet_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x35F_INFO,
    .PduRDestPdus = PduRDestinations_TBOX_chargeSet_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BMS_metric_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x514_INFO,
    .PduRDestPdus = PduRDestinations_BMS_metric_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BMS_tboxRequest_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x574_INFO,
    .PduRDestPdus = PduRDestinations_BMS_tboxRequest_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_range_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x561_INFO,
    .PduRDestPdus = PduRDestinations_VCU_range_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_range1_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x351_INFO,
    .PduRDestPdus = PduRDestinations_VCU_range1_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x111_INFO,
    .PduRDestPdus = PduRDestinations_VCU_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_OBC_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x387_INFO,
    .PduRDestPdus = PduRDestinations_OBC_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_OBC_state1_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x407_INFO,
    .PduRDestPdus = PduRDestinations_OBC_state1_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_DCDC_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x38D_INFO,
    .PduRDestPdus = PduRDestinations_DCDC_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GSM_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x309_INFO,
    .PduRDestPdus = PduRDestinations_GSM_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GTW_mcur0_mcuf0_info_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x38A_INFO,
    .PduRDestPdus = PduRDestinations_GTW_mcur0_mcuf0_info_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BMS_temperature_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x304_INFO,
    .PduRDestPdus = PduRDestinations_BMS_temperature_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_Info_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x331_INFO,
    .PduRDestPdus = PduRDestinations_VCU_Info_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_Diag_FuncReq_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANTP,
    .SrcPduId = CANTP_PDU_ID_DIAGFUNCTIONALRX,
    .PduRDestPdus = PduRDestinations_Diag_FuncReq_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_info_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x4F3_INFO,
    .PduRDestPdus = PduRDestinations_IC_info_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_pwr_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x301_INFO,
    .PduRDestPdus = PduRDestinations_VCU_pwr_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_RevV2V_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x330_INFO,
    .PduRDestPdus = PduRDestinations_VCU_RevV2V_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BMS_ASSt_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3A4_INFO,
    .PduRDestPdus = PduRDestinations_BMS_ASSt_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_stateCha1_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3A1_INFO,
    .PduRDestPdus = PduRDestinations_VCU_stateCha1_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_EPS_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x124_INFO,
    .PduRDestPdus = PduRDestinations_EPS_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_EPS_sas_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x144_INFO,
    .PduRDestPdus = PduRDestinations_EPS_sas_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_wheelSpd_Front_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x142_INFO,
    .PduRDestPdus = PduRDestinations_ESC_wheelSpd_Front_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_wheelSpd_Rear_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x122_INFO,
    .PduRDestPdus = PduRDestinations_ESC_wheelSpd_Rear_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_state1_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x212_INFO,
    .PduRDestPdus = PduRDestinations_ESC_state1_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_state2_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x2A2_INFO,
    .PduRDestPdus = PduRDestinations_ESC_state2_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_yawState_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x252_INFO,
    .PduRDestPdus = PduRDestinations_ESC_yawState_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_ESC_yawState_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3FB_INFO,
    .PduRDestPdus = PduRDestinations_GW_ESC_yawState_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_wssFront_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x272_INFO,
    .PduRDestPdus = PduRDestinations_ESC_wssFront_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_wssRear_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x282_INFO,
    .PduRDestPdus = PduRDestinations_ESC_wssRear_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ESC_epb_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x2C2_INFO,
    .PduRDestPdus = PduRDestinations_ESC_epb_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_acc_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x219_INFO,
    .PduRDestPdus = PduRDestinations_MRR_acc_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_pss_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x239_INFO,
    .PduRDestPdus = PduRDestinations_MRR_pss_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_hmi1_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x349_INFO,
    .PduRDestPdus = PduRDestinations_MRR_hmi1_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_hmi2_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x369_INFO,
    .PduRDestPdus = PduRDestinations_MRR_hmi2_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_hmi3_34E_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x34E_INFO,
    .PduRDestPdus = PduRDestinations_MRR_hmi3_34E_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_hmi4_34F_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x34F_INFO,
    .PduRDestPdus = PduRDestinations_MRR_hmi4_34F_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_hmi5_355_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x355_INFO,
    .PduRDestPdus = PduRDestinations_MRR_hmi5_355_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MRR_hmi6_356_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x356_INFO,
    .PduRDestPdus = PduRDestinations_MRR_hmi6_356_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MPC_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x21A_INFO,
    .PduRDestPdus = PduRDestinations_MPC_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MPC_hmi_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x35A_INFO,
    .PduRDestPdus = PduRDestinations_MPC_hmi_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MPC_RoadState_359_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x359_INFO,
    .PduRDestPdus = PduRDestinations_MPC_RoadState_359_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MPC_hmi_35D_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x35D_INFO,
    .PduRDestPdus = PduRDestinations_MPC_hmi_35D_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_SRR_R_state_22B_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x22B_INFO,
    .PduRDestPdus = PduRDestinations_SRR_R_state_22B_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_ABM_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x380_INFO,
    .PduRDestPdus = PduRDestinations_ABM_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_APA_35B_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x35B_INFO,
    .PduRDestPdus = PduRDestinations_APA_35B_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_SLA_408_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x408_INFO,
    .PduRDestPdus = PduRDestinations_IVI_SLA_408_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_state2_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3B1_INFO,
    .PduRDestPdus = PduRDestinations_VCU_state2_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BLE_FB_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x347_INFO,
    .PduRDestPdus = PduRDestinations_BLE_FB_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BLE_User_ID_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x375_INFO,
    .PduRDestPdus = PduRDestinations_BLE_User_ID_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_User_ID_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x376_INFO,
    .PduRDestPdus = PduRDestinations_IVI_User_ID_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_TBOX_Factory_360_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x360_INFO,
    .PduRDestPdus = PduRDestinations_TBOX_Factory_360_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_AC_ctrlFeedback_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3B6_INFO,
    .PduRDestPdus = PduRDestinations_AC_ctrlFeedback_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_AC_state2_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x386_INFO,
    .PduRDestPdus = PduRDestinations_AC_state2_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x2A1_INFO,
    .PduRDestPdus = PduRDestinations_BCM_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_state2_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3C1_INFO,
    .PduRDestPdus = PduRDestinations_BCM_state2_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_state3_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3C2_INFO,
    .PduRDestPdus = PduRDestinations_BCM_state3_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_state4_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x305_INFO,
    .PduRDestPdus = PduRDestinations_BCM_state4_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_tpms_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x411_INFO,
    .PduRDestPdus = PduRDestinations_BCM_tpms_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_tpms1_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x421_INFO,
    .PduRDestPdus = PduRDestinations_BCM_tpms1_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_peps_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x2C1_INFO,
    .PduRDestPdus = PduRDestinations_BCM_peps_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_rsm_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3D1_INFO,
    .PduRDestPdus = PduRDestinations_BCM_rsm_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BCM_RemotFB_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x5C3_INFO,
    .PduRDestPdus = PduRDestinations_BCM_RemotFB_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_096_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x096_INFO,
    .PduRDestPdus = PduRDestinations_IVI_096_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_LCU_32A_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x32A_INFO,
    .PduRDestPdus = PduRDestinations_LCU_32A_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_PLG_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x394_INFO,
    .PduRDestPdus = PduRDestinations_PLG_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_Handle_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x335_INFO,
    .PduRDestPdus = PduRDestinations_GW_Handle_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_DSM_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3D5_INFO,
    .PduRDestPdus = PduRDestinations_DSM_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_PSM_memory_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3D6_INFO,
    .PduRDestPdus = PduRDestinations_PSM_memory_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_DSM_memory_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3D4_INFO,
    .PduRDestPdus = PduRDestinations_DSM_memory_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_PSM_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x318_INFO,
    .PduRDestPdus = PduRDestinations_PSM_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_LRSM_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x31A_INFO,
    .PduRDestPdus = PduRDestinations_LRSM_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_TBOX_infoCtrl_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x0A8_INFO,
    .PduRDestPdus = PduRDestinations_TBOX_infoCtrl_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_control_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x075_INFO,
    .PduRDestPdus = PduRDestinations_IVI_control_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_comfortSet_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x095_INFO,
    .PduRDestPdus = PduRDestinations_IVI_comfortSet_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_pwrSet_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x0A5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_pwrSet_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_chassisSet1_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x1D5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_chassisSet1_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_chassisSet_065_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x065_INFO,
    .PduRDestPdus = PduRDestinations_IVI_chassisSet_065_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_dvrSet_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x105_INFO,
    .PduRDestPdus = PduRDestinations_IVI_dvrSet_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_dsmmSet_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x098_INFO,
    .PduRDestPdus = PduRDestinations_IVI_dsmmSet_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_dsmmSet2_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x093_INFO,
    .PduRDestPdus = PduRDestinations_IVI_dsmmSet2_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_infoSet_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x0C5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_infoSet_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VSP_state_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3A0_INFO,
    .PduRDestPdus = PduRDestinations_VSP_state_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_infoSet2_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x0C6_INFO,
    .PduRDestPdus = PduRDestinations_IVI_infoSet2_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_AVMSet_3D2_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3D2_INFO,
    .PduRDestPdus = PduRDestinations_IVI_AVMSet_3D2_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_scuSet_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x0F5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_scuSet_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent1Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x31C_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent1Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent2Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x31D_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent2Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent3Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x325_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent3Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent4Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x328_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent4Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent5Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x33A_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent5Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent6Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x33B_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent6Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent7Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x34A_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent7Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_vent8Ctrl_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x34B_INFO,
    .PduRDestPdus = PduRDestinations_IVI_vent8Ctrl_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent1Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3C6_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent1Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent2Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3C7_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent2Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent3Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3C8_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent3Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent4Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3C9_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent4Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent5Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3CA_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent5Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent6Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3CB_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent6Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent7Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3CC_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent7Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_vent8Sts_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3CD_INFO,
    .PduRDestPdus = PduRDestinations_GW_vent8Sts_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_NaviChrgSt_33D_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x33D_INFO,
    .PduRDestPdus = PduRDestinations_IVI_NaviChrgSt_33D_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_NaviChrgSt_33E_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x33E_INFO,
    .PduRDestPdus = PduRDestinations_IVI_NaviChrgSt_33E_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_engineOFF_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x052_INFO,
    .PduRDestPdus = PduRDestinations_IC_engineOFF_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_faultSum_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x5FD_INFO,
    .PduRDestPdus = PduRDestinations_IC_faultSum_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_infoSet_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3F2_INFO,
    .PduRDestPdus = PduRDestinations_IC_infoSet_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_3F8_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3F8_INFO,
    .PduRDestPdus = PduRDestinations_IC_3F8_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_state3_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x4F4_INFO,
    .PduRDestPdus = PduRDestinations_IC_state3_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_Warning_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x571_INFO,
    .PduRDestPdus = PduRDestinations_IC_Warning_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_Warningfb_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x570_INFO,
    .PduRDestPdus = PduRDestinations_IC_Warningfb_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_BMS_meas_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3DE_INFO,
    .PduRDestPdus = PduRDestinations_GW_BMS_meas_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_BMS_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x31E_INFO,
    .PduRDestPdus = PduRDestinations_BMS_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GTW_mcur0_info_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3AE_INFO,
    .PduRDestPdus = PduRDestinations_GTW_mcur0_info_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GTW_mcuf0_info_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3BE_INFO,
    .PduRDestPdus = PduRDestinations_GTW_mcuf0_info_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GTW_ecu_gcu_vcu_info_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x37E_INFO,
    .PduRDestPdus = PduRDestinations_GTW_ecu_gcu_vcu_info_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GTW_esc_eps_iB_info_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x223_INFO,
    .PduRDestPdus = PduRDestinations_GTW_esc_eps_iB_info_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GW_EPS_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x353_INFO,
    .PduRDestPdus = PduRDestinations_GW_EPS_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_VCU_stateCha2_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x24E_INFO,
    .PduRDestPdus = PduRDestinations_VCU_stateCha2_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_AC_temp_pressure_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3CE_INFO,
    .PduRDestPdus = PduRDestinations_AC_temp_pressure_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_WCM_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3AD_INFO,
    .PduRDestPdus = PduRDestinations_WCM_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_AVM_state_484_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x484_INFO,
    .PduRDestPdus = PduRDestinations_AVM_state_484_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_HUD_state_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x3FA_INFO,
    .PduRDestPdus = PduRDestinations_HUD_state_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MFW_Ctrl_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x0A9_INFO,
    .PduRDestPdus = PduRDestinations_MFW_Ctrl_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_MFW_KeySt_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x498_INFO,
    .PduRDestPdus = PduRDestinations_MFW_KeySt_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_state_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x2F2_INFO,
    .PduRDestPdus = PduRDestinations_IC_state_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_info2_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3F7_INFO,
    .PduRDestPdus = PduRDestinations_IC_info2_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_state1_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x482_INFO,
    .PduRDestPdus = PduRDestinations_IC_state1_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_EnergyConsumption_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x491_INFO,
    .PduRDestPdus = PduRDestinations_IC_EnergyConsumption_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_state2_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x492_INFO,
    .PduRDestPdus = PduRDestinations_IC_state2_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_state4_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x493_INFO,
    .PduRDestPdus = PduRDestinations_IC_state4_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_state5_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x494_INFO,
    .PduRDestPdus = PduRDestinations_IC_state5_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_StatusAndNotify_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x495_INFO,
    .PduRDestPdus = PduRDestinations_IVI_StatusAndNotify_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_hmi_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x496_INFO,
    .PduRDestPdus = PduRDestinations_IVI_hmi_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_State_5F0_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x5F0_INFO,
    .PduRDestPdus = PduRDestinations_IVI_State_5F0_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IC_RequestAndStatus_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x4A2_INFO,
    .PduRDestPdus = PduRDestinations_IC_RequestAndStatus_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_set_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3B5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_set_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_timeAndGPS_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x4F5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_timeAndGPS_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_navi_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x485_INFO,
    .PduRDestPdus = PduRDestinations_IVI_navi_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_NaviDirection_LaneX_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x486_INFO,
    .PduRDestPdus = PduRDestinations_IVI_NaviDirection_LaneX_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_media_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x395_INFO,
    .PduRDestPdus = PduRDestinations_IVI_media_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_naviText_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3C5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_naviText_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_TelSongText_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3A5_INFO,
    .PduRDestPdus = PduRDestinations_IVI_TelSongText_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_GTW_BMS_Rev_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x35E_INFO,
    .PduRDestPdus = PduRDestinations_GTW_BMS_Rev_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_Diag_PhyReq_IVI_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANTP,
    .SrcPduId = CANTP_PDU_ID_DIAGPHYSICALRX,
    .PduRDestPdus = PduRDestinations_Diag_PhyReq_IVI_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_Diag_Resp_IVI_INFO_Tx = {
    .SrcModule     = AS_PDUR_DCM,
    .SrcPduId = DCM_PDU_ID_DIAGPHYSICALTX,
    .PduRDestPdus = PduRDestinations_Diag_Resp_IVI_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_IVI_ADAS_3E1_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x3E1_INFO,
    .PduRDestPdus = PduRDestinations_IVI_ADAS_3E1_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_Wacc_500_INFO_Tx = {
    .SrcModule     = AS_PDUR_COM,
    .SrcPduId = ComConf_ComIPdu_0x500_INFO,
    .PduRDestPdus = PduRDestinations_Wacc_500_INFO_Tx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};
const PduRRoutingPath_type PduRRoutingPath_SWHC_400_INFO_Rx = {
    .SrcModule     = AS_PDUR_CANIF,
    .SrcPduId = CANIF_PDU_ID_0x400_INFO,
    .PduRDestPdus = PduRDestinations_SWHC_400_INFO_Rx,
    .PduRDirectGateway = TRUE,
    .PduRTpThreshld = 0,
};


const PduRRoutingPath_type * const PduRRoutingPaths[] = {
    &PduRRoutingPath_Diag_PhyReq_IVI_INFO_Rx,
    &PduRRoutingPath_Diag_FuncReq_INFO_Rx,
    &PduRRoutingPath_TBOX_chargeSet_INFO_Rx,
    &PduRRoutingPath_BMS_metric_INFO_Rx,
    &PduRRoutingPath_BMS_tboxRequest_INFO_Rx,
    &PduRRoutingPath_VCU_range_INFO_Rx,
    &PduRRoutingPath_VCU_range1_INFO_Rx,
    &PduRRoutingPath_VCU_state_INFO_Rx,
    &PduRRoutingPath_OBC_state_INFO_Rx,
    &PduRRoutingPath_OBC_state1_INFO_Rx,
    &PduRRoutingPath_DCDC_state_INFO_Rx,
    &PduRRoutingPath_GSM_state_INFO_Rx,
    &PduRRoutingPath_GTW_mcur0_mcuf0_info_INFO_Rx,
    &PduRRoutingPath_BMS_temperature_INFO_Rx,
    &PduRRoutingPath_VCU_Info_INFO_Rx,
    &PduRRoutingPath_VCU_pwr_INFO_Rx,
    &PduRRoutingPath_VCU_RevV2V_INFO_Rx,
    &PduRRoutingPath_BMS_ASSt_INFO_Rx,
    &PduRRoutingPath_VCU_stateCha1_INFO_Rx,
    &PduRRoutingPath_EPS_state_INFO_Rx,
    &PduRRoutingPath_EPS_sas_INFO_Rx,
    &PduRRoutingPath_ESC_wheelSpd_Front_INFO_Rx,
    &PduRRoutingPath_ESC_wheelSpd_Rear_INFO_Rx,
    &PduRRoutingPath_ESC_state1_INFO_Rx,
    &PduRRoutingPath_ESC_state2_INFO_Rx,
    &PduRRoutingPath_ESC_yawState_INFO_Rx,
    &PduRRoutingPath_GW_ESC_yawState_INFO_Rx,
    &PduRRoutingPath_ESC_wssFront_INFO_Rx,
    &PduRRoutingPath_ESC_wssRear_INFO_Rx,
    &PduRRoutingPath_ESC_epb_INFO_Rx,
    &PduRRoutingPath_MRR_acc_INFO_Rx,
    &PduRRoutingPath_MRR_pss_INFO_Rx,
    &PduRRoutingPath_MRR_hmi1_INFO_Rx,
    &PduRRoutingPath_MRR_hmi2_INFO_Rx,
    &PduRRoutingPath_MRR_hmi3_34E_INFO_Rx,
    &PduRRoutingPath_MRR_hmi4_34F_INFO_Rx,
    &PduRRoutingPath_MRR_hmi5_355_INFO_Rx,
    &PduRRoutingPath_MRR_hmi6_356_INFO_Rx,
    &PduRRoutingPath_MPC_state_INFO_Rx,
    &PduRRoutingPath_MPC_hmi_INFO_Rx,
    &PduRRoutingPath_MPC_RoadState_359_INFO_Rx,
    &PduRRoutingPath_MPC_hmi_35D_INFO_Rx,
    &PduRRoutingPath_SRR_R_state_22B_INFO_Rx,
    &PduRRoutingPath_ABM_state_INFO_Rx,
    &PduRRoutingPath_APA_35B_INFO_Rx,
    &PduRRoutingPath_VCU_state2_INFO_Rx,
    &PduRRoutingPath_BLE_FB_INFO_Rx,
    &PduRRoutingPath_BLE_User_ID_INFO_Rx,
    &PduRRoutingPath_TBOX_Factory_360_INFO_Rx,
    &PduRRoutingPath_AC_ctrlFeedback_INFO_Rx,
    &PduRRoutingPath_AC_state2_INFO_Rx,
    &PduRRoutingPath_BCM_state_INFO_Rx,
    &PduRRoutingPath_BCM_state2_INFO_Rx,
    &PduRRoutingPath_BCM_state3_INFO_Rx,
    &PduRRoutingPath_BCM_state4_INFO_Rx,
    &PduRRoutingPath_BCM_tpms_INFO_Rx,
    &PduRRoutingPath_BCM_tpms1_INFO_Rx,
    &PduRRoutingPath_BCM_peps_INFO_Rx,
    &PduRRoutingPath_BCM_rsm_INFO_Rx,
    &PduRRoutingPath_BCM_RemotFB_INFO_Rx,
    &PduRRoutingPath_LCU_32A_INFO_Rx,
    &PduRRoutingPath_PLG_state_INFO_Rx,
    &PduRRoutingPath_GW_Handle_state_INFO_Rx,
    &PduRRoutingPath_DSM_state_INFO_Rx,
    &PduRRoutingPath_PSM_memory_INFO_Rx,
    &PduRRoutingPath_DSM_memory_INFO_Rx,
    &PduRRoutingPath_PSM_state_INFO_Rx,
    &PduRRoutingPath_LRSM_state_INFO_Rx,
    &PduRRoutingPath_TBOX_infoCtrl_INFO_Rx,
    &PduRRoutingPath_GW_vent1Sts_INFO_Rx,
    &PduRRoutingPath_GW_vent2Sts_INFO_Rx,
    &PduRRoutingPath_GW_vent3Sts_INFO_Rx,
    &PduRRoutingPath_GW_vent4Sts_INFO_Rx,
    &PduRRoutingPath_GW_vent5Sts_INFO_Rx,
    &PduRRoutingPath_GW_vent6Sts_INFO_Rx,
    &PduRRoutingPath_GW_vent7Sts_INFO_Rx,
    &PduRRoutingPath_GW_vent8Sts_INFO_Rx,
    &PduRRoutingPath_GW_BMS_meas_INFO_Rx,
    &PduRRoutingPath_BMS_state_INFO_Rx,
    &PduRRoutingPath_GTW_mcur0_info_INFO_Rx,
    &PduRRoutingPath_GTW_mcuf0_info_INFO_Rx,
    &PduRRoutingPath_GTW_ecu_gcu_vcu_info_INFO_Rx,
    &PduRRoutingPath_GTW_esc_eps_iB_info_INFO_Rx,
    &PduRRoutingPath_GW_EPS_state_INFO_Rx,
    &PduRRoutingPath_VCU_stateCha2_INFO_Rx,
    &PduRRoutingPath_AC_temp_pressure_INFO_Rx,
    &PduRRoutingPath_WCM_state_INFO_Rx,
    &PduRRoutingPath_AVM_state_484_INFO_Rx,
    &PduRRoutingPath_HUD_state_INFO_Rx,
    &PduRRoutingPath_MFW_Ctrl_INFO_Rx,
    &PduRRoutingPath_MFW_KeySt_INFO_Rx,
    &PduRRoutingPath_IVI_timeAndGPS_INFO_Rx,
    &PduRRoutingPath_GTW_BMS_Rev_INFO_Rx,
    &PduRRoutingPath_SWHC_400_INFO_Rx,

    &PduRRoutingPath_Diag_Resp_IVI_INFO_Tx,
    &PduRRoutingPath_IC_info_INFO_Tx,
    &PduRRoutingPath_IVI_SLA_408_INFO_Tx,
    &PduRRoutingPath_IVI_User_ID_INFO_Tx,
    &PduRRoutingPath_IVI_096_INFO_Tx,
    &PduRRoutingPath_IVI_control_INFO_Tx,
    &PduRRoutingPath_IVI_comfortSet_INFO_Tx,
    &PduRRoutingPath_IVI_pwrSet_INFO_Tx,
    &PduRRoutingPath_IVI_chassisSet1_INFO_Tx,
    &PduRRoutingPath_IVI_chassisSet_065_INFO_Tx,
    &PduRRoutingPath_IVI_dvrSet_INFO_Tx,
    &PduRRoutingPath_IVI_dsmmSet_INFO_Tx,
    &PduRRoutingPath_IVI_dsmmSet2_INFO_Tx,
    &PduRRoutingPath_IVI_infoSet_INFO_Tx,
    &PduRRoutingPath_VSP_state_INFO_Tx,
    &PduRRoutingPath_IVI_infoSet2_INFO_Tx,
    &PduRRoutingPath_IVI_AVMSet_3D2_INFO_Tx,
    &PduRRoutingPath_IVI_scuSet_INFO_Tx,
    &PduRRoutingPath_IVI_vent1Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_vent2Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_vent3Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_vent4Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_vent5Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_vent6Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_vent7Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_vent8Ctrl_INFO_Tx,
    &PduRRoutingPath_IVI_NaviChrgSt_33D_INFO_Tx,
    &PduRRoutingPath_IVI_NaviChrgSt_33E_INFO_Tx,
    &PduRRoutingPath_IC_engineOFF_INFO_Tx,
    &PduRRoutingPath_IC_faultSum_INFO_Tx,
    &PduRRoutingPath_IC_infoSet_INFO_Tx,
    &PduRRoutingPath_IC_3F8_INFO_Tx,
    &PduRRoutingPath_IC_state3_INFO_Tx,
    &PduRRoutingPath_IC_Warning_INFO_Tx,
    &PduRRoutingPath_IC_Warningfb_INFO_Tx,
    &PduRRoutingPath_IC_state_INFO_Tx,
    &PduRRoutingPath_IC_info2_INFO_Tx,
    &PduRRoutingPath_IC_state1_INFO_Tx,
    &PduRRoutingPath_IC_EnergyConsumption_INFO_Tx,
    &PduRRoutingPath_IC_state2_INFO_Tx,
    &PduRRoutingPath_IC_state4_INFO_Tx,
    &PduRRoutingPath_IC_state5_INFO_Tx,
    &PduRRoutingPath_IVI_StatusAndNotify_INFO_Tx,
    &PduRRoutingPath_IVI_hmi_INFO_Tx,
    &PduRRoutingPath_IVI_State_5F0_INFO_Tx,
    &PduRRoutingPath_IC_RequestAndStatus_INFO_Tx,
    &PduRRoutingPath_IVI_set_INFO_Tx,
    &PduRRoutingPath_IVI_navi_INFO_Tx,
    &PduRRoutingPath_IVI_NaviDirection_LaneX_INFO_Tx,
    &PduRRoutingPath_IVI_media_INFO_Tx,
    &PduRRoutingPath_IVI_naviText_INFO_Tx,
    &PduRRoutingPath_IVI_TelSongText_INFO_Tx,
    &PduRRoutingPath_IVI_ADAS_3E1_INFO_Tx,
    &PduRRoutingPath_Wacc_500_INFO_Tx,
    NULL
};

// Tx buffer default value pointer list (sorted in the same order as Tx buffer IDs)
const uint8_t * const PduRTxBufferDefaultValues[] =
{
    NULL
};
// Tx buffer default value length list (sorted in the same order as Tx buffer IDs)
const uint32_t * const PduRTxBufferDefaultValueLengths[] =
{
    NULL
};
// Exported config
const PduR_PBConfigType PduR_Config = {
    .PduRConfigurationId = 0,
    .RoutingPaths = PduRRoutingPaths,
    .NRoutingPaths = PDUR_MAX_ROUTE_COUNT,
    .DefaultValues = PduRTxBufferDefaultValues,
    .DefaultValueLengths = PduRTxBufferDefaultValueLengths,
    .NofRoutingPathGroups = PDUR_MAX_NOF_ROUTING_PATH_GROUPS,
    .RoutingPathGroups = &Pdur_RoutingPathGroups,
};


