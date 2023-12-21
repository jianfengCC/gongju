/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by APPSYS and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with APPSYS in writing by applicable law.
 */
/**
 * @file    CanIf_PBCfg.c
 * @brief   brief function description.
 * @details detailed function description.
 * @version 1.0
 * @author  appsys
 * @date    2019-05-21
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2019-05-21               appsys             Create it.
 */

#include "Can_Cfg.h"
#include "CanIf.h"
#include "CanIf_PBCfg.h"
#include "CanTp_PBCfg.h"
#include "OsekNm_PBCfg.h"
#include "PduR.h"
#include "PduR_PbCfg.h"
#include "MemMap.h"
#include "CanNm_PBCfg.h"
#include "Com_As_Types.h"
#include "Com_Internal.h"
#include "NvmControl.h"

#define CanIfInitHohCfg_CanIfHrhCfg_INDEX 0u
Com_As_IPdu_type Com_As_IPdu[COM_MAX_N_IPDUS];
Com_As_Signal_type Com_As_Signal[COM_MAX_N_SIGNALS];
Com_BufferPduStateType Com_BufferPduState[COM_MAX_N_IPDUS]={{0,0}};
uint8_t Com_PduErrStatus[COM_MAX_N_IPDUS];
uint8_t Com_SignalErrStatus[COM_MAX_N_SIGNALS];
uint8_t Com_SignalExitErrCnt[COM_MAX_N_SIGNALS];
uint8_t Com_As_Buffer[COM_MAX_BUFFER_SIZE];
CanIf_As_BufferEntryType TxPduBuffer[CANIF_AS_MAX_NUM_LPDU_TX_BUF];
uint16_t canif_max_num_tx_buf = CANIF_AS_MAX_NUM_LPDU_TX_BUF;
uint16_t BufferStartIndex[CANIF_AS_MAX_NOF_TX_BUFFERS];
uint16_t canif_max_nof_tx_buf = CANIF_AS_MAX_NOF_TX_BUFFERS;
CanIfDlcErrorType CanIfDlcError[CANIF_NUM_RX_LPDU];
CanIf_LPduType RxBuffer[CANIF_NUM_RX_LPDU];
CanIf_NotifStatusType TxNotifStatusBuffer[CANIF_NUM_RX_LPDU];
CanIf_NotifStatusType RxNotifStatusBuffer[CANIF_NUM_TX_LPDU];
uint16_t gcanif_num_rx_lpdu = CANIF_NUM_RX_LPDU;
uint16_t gcanif_num_tx_lpdu = CANIF_NUM_TX_LPDU;
uint16_t gSignal_Igninionsts = COMCONF_COMSIGNAL_BCM_IGNITIONSTS_0X365_INFO;
uint16_t gVehicleSpeedValid = COMCONF_COMSIGNAL_ESP_VEHICLESPEEDVALID_0X1F9_INFO;
uint16_t gVehicleSpeed = COMCONF_COMSIGNAL_ESP_VEHICLESPEED_0X1F9_INFO;
uint16_t gDidStorDataBlock = STOR_DATABLK_27SERVICE;




const CanIf_RxPduConfigType HrhRxPdu_CanIfHrhCfg[] = {
  /* 0 */
   {
       .CanIfCanRxPduId            = CANTP_PDU_ID_DIAGPHYSICALRX,
       .CanIfCanRxPduLowerCanId    = 0x725,
       .CanIfCanRxPduUpperCanId    = 0x725,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = CANTP_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },

  /* 1 */
   {
       .CanIfCanRxPduId            = CANTP_PDU_ID_DIAGFUNCTIONALRX,
       .CanIfCanRxPduLowerCanId    = 0x7DF,
       .CanIfCanRxPduUpperCanId    = 0x7DF,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = CANTP_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 2 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_TBOX_chargeSet_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x35F,
       .CanIfCanRxPduUpperCanId    = 0x35F,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 3 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BMS_metric_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x514,
       .CanIfCanRxPduUpperCanId    = 0x514,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 4 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BMS_tboxRequest_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x574,
       .CanIfCanRxPduUpperCanId    = 0x574,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 5 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_range_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x561,
       .CanIfCanRxPduUpperCanId    = 0x561,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 6 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_range1_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x351,
       .CanIfCanRxPduUpperCanId    = 0x351,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 7 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x111,
       .CanIfCanRxPduUpperCanId    = 0x111,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 8 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_OBC_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x387,
       .CanIfCanRxPduUpperCanId    = 0x387,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 9 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_OBC_state1_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x407,
       .CanIfCanRxPduUpperCanId    = 0x407,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 10 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_DCDC_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x38D,
       .CanIfCanRxPduUpperCanId    = 0x38D,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 11 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GSM_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x309,
       .CanIfCanRxPduUpperCanId    = 0x309,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 12 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GTW_mcur0_mcuf0_info_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x38A,
       .CanIfCanRxPduUpperCanId    = 0x38A,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 13 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BMS_temperature_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x304,
       .CanIfCanRxPduUpperCanId    = 0x304,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 14 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_Info_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x331,
       .CanIfCanRxPduUpperCanId    = 0x331,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 15 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_pwr_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x301,
       .CanIfCanRxPduUpperCanId    = 0x301,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 16 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_RevV2V_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x330,
       .CanIfCanRxPduUpperCanId    = 0x330,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 17 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BMS_ASSt_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3A4,
       .CanIfCanRxPduUpperCanId    = 0x3A4,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 18 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_stateCha1_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3A1,
       .CanIfCanRxPduUpperCanId    = 0x3A1,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 19 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_EPS_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x124,
       .CanIfCanRxPduUpperCanId    = 0x124,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 20 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_EPS_sas_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x144,
       .CanIfCanRxPduUpperCanId    = 0x144,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 21 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_wheelSpd_Front_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x142,
       .CanIfCanRxPduUpperCanId    = 0x142,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 22 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_wheelSpd_Rear_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x122,
       .CanIfCanRxPduUpperCanId    = 0x122,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 23 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_state1_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x212,
       .CanIfCanRxPduUpperCanId    = 0x212,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 24 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_state2_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x2A2,
       .CanIfCanRxPduUpperCanId    = 0x2A2,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 25 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_yawState_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x252,
       .CanIfCanRxPduUpperCanId    = 0x252,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 26 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_ESC_yawState_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3FB,
       .CanIfCanRxPduUpperCanId    = 0x3FB,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 27 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_wssFront_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x272,
       .CanIfCanRxPduUpperCanId    = 0x272,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 28 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_wssRear_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x282,
       .CanIfCanRxPduUpperCanId    = 0x282,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 29 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ESC_epb_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x2C2,
       .CanIfCanRxPduUpperCanId    = 0x2C2,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 30 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_acc_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x219,
       .CanIfCanRxPduUpperCanId    = 0x219,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 31 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_pss_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x239,
       .CanIfCanRxPduUpperCanId    = 0x239,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 32 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_hmi1_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x349,
       .CanIfCanRxPduUpperCanId    = 0x349,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 33 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_hmi2_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x369,
       .CanIfCanRxPduUpperCanId    = 0x369,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 34 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_hmi3_34E_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x34E,
       .CanIfCanRxPduUpperCanId    = 0x34E,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 35 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_hmi4_34F_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x34F,
       .CanIfCanRxPduUpperCanId    = 0x34F,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 36 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_hmi5_355_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x355,
       .CanIfCanRxPduUpperCanId    = 0x355,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 37 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MRR_hmi6_356_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x356,
       .CanIfCanRxPduUpperCanId    = 0x356,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 38 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MPC_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x21A,
       .CanIfCanRxPduUpperCanId    = 0x21A,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 39 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MPC_hmi_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x35A,
       .CanIfCanRxPduUpperCanId    = 0x35A,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 40 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MPC_RoadState_359_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x359,
       .CanIfCanRxPduUpperCanId    = 0x359,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 41 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MPC_hmi_35D_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x35D,
       .CanIfCanRxPduUpperCanId    = 0x35D,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 42 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_SRR_R_state_22B_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x22B,
       .CanIfCanRxPduUpperCanId    = 0x22B,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 43 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_ABM_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x380,
       .CanIfCanRxPduUpperCanId    = 0x380,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 44 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_APA_35B_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x35B,
       .CanIfCanRxPduUpperCanId    = 0x35B,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 45 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_state2_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3B1,
       .CanIfCanRxPduUpperCanId    = 0x3B1,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 46 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BLE_FB_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x347,
       .CanIfCanRxPduUpperCanId    = 0x347,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 47 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BLE_User_ID_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x375,
       .CanIfCanRxPduUpperCanId    = 0x375,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 48 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_TBOX_Factory_360_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x360,
       .CanIfCanRxPduUpperCanId    = 0x360,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 49 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_AC_ctrlFeedback_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3B6,
       .CanIfCanRxPduUpperCanId    = 0x3B6,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 50 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_AC_state2_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x386,
       .CanIfCanRxPduUpperCanId    = 0x386,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 51 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x2A1,
       .CanIfCanRxPduUpperCanId    = 0x2A1,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 52 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_state2_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3C1,
       .CanIfCanRxPduUpperCanId    = 0x3C1,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 53 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_state3_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3C2,
       .CanIfCanRxPduUpperCanId    = 0x3C2,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 54 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_state4_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x305,
       .CanIfCanRxPduUpperCanId    = 0x305,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 55 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_tpms_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x411,
       .CanIfCanRxPduUpperCanId    = 0x411,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 56 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_tpms1_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x421,
       .CanIfCanRxPduUpperCanId    = 0x421,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 57 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_peps_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x2C1,
       .CanIfCanRxPduUpperCanId    = 0x2C1,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 58 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_rsm_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3D1,
       .CanIfCanRxPduUpperCanId    = 0x3D1,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 59 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BCM_RemotFB_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x5C3,
       .CanIfCanRxPduUpperCanId    = 0x5C3,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 60 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_LCU_32A_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x32A,
       .CanIfCanRxPduUpperCanId    = 0x32A,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 61 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_PLG_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x394,
       .CanIfCanRxPduUpperCanId    = 0x394,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 62 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_Handle_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x335,
       .CanIfCanRxPduUpperCanId    = 0x335,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 63 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_DSM_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3D5,
       .CanIfCanRxPduUpperCanId    = 0x3D5,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 64 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_PSM_memory_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3D6,
       .CanIfCanRxPduUpperCanId    = 0x3D6,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 65 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_DSM_memory_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3D4,
       .CanIfCanRxPduUpperCanId    = 0x3D4,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 66 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_PSM_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x318,
       .CanIfCanRxPduUpperCanId    = 0x318,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 67 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_LRSM_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x31A,
       .CanIfCanRxPduUpperCanId    = 0x31A,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 68 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_TBOX_infoCtrl_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x0A8,
       .CanIfCanRxPduUpperCanId    = 0x0A8,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 69 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent1Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3C6,
       .CanIfCanRxPduUpperCanId    = 0x3C6,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 70 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent2Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3C7,
       .CanIfCanRxPduUpperCanId    = 0x3C7,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 71 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent3Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3C8,
       .CanIfCanRxPduUpperCanId    = 0x3C8,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 72 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent4Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3C9,
       .CanIfCanRxPduUpperCanId    = 0x3C9,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 73 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent5Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3CA,
       .CanIfCanRxPduUpperCanId    = 0x3CA,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 74 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent6Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3CB,
       .CanIfCanRxPduUpperCanId    = 0x3CB,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 75 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent7Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3CC,
       .CanIfCanRxPduUpperCanId    = 0x3CC,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 76 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_vent8Sts_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3CD,
       .CanIfCanRxPduUpperCanId    = 0x3CD,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 77 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_BMS_meas_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3DE,
       .CanIfCanRxPduUpperCanId    = 0x3DE,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 78 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_BMS_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x31E,
       .CanIfCanRxPduUpperCanId    = 0x31E,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 79 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GTW_mcur0_info_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3AE,
       .CanIfCanRxPduUpperCanId    = 0x3AE,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 80 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GTW_mcuf0_info_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3BE,
       .CanIfCanRxPduUpperCanId    = 0x3BE,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 81 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GTW_ecu_gcu_vcu_info_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x37E,
       .CanIfCanRxPduUpperCanId    = 0x37E,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 82 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GTW_esc_eps_iB_info_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x223,
       .CanIfCanRxPduUpperCanId    = 0x223,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 83 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GW_EPS_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x353,
       .CanIfCanRxPduUpperCanId    = 0x353,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 84 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_VCU_stateCha2_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x24E,
       .CanIfCanRxPduUpperCanId    = 0x24E,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 85 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_AC_temp_pressure_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3CE,
       .CanIfCanRxPduUpperCanId    = 0x3CE,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 86 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_WCM_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3AD,
       .CanIfCanRxPduUpperCanId    = 0x3AD,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 87 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_AVM_state_484_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x484,
       .CanIfCanRxPduUpperCanId    = 0x484,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 88 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_HUD_state_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x3FA,
       .CanIfCanRxPduUpperCanId    = 0x3FA,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 89 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MFW_Ctrl_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x0A9,
       .CanIfCanRxPduUpperCanId    = 0x0A9,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 90 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_MFW_KeySt_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x498,
       .CanIfCanRxPduUpperCanId    = 0x498,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 91 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_IVI_timeAndGPS_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x4F5,
       .CanIfCanRxPduUpperCanId    = 0x4F5,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 92 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_GTW_BMS_Rev_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x35E,
       .CanIfCanRxPduUpperCanId    = 0x35E,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 93 */
   {
       .CanIfCanRxPduId            = PDUR_PDU_ID_SWHC_400_INFO_CANIF,
       .CanIfCanRxPduLowerCanId    = 0x400,
       .CanIfCanRxPduUpperCanId    = 0x400,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = PDUR_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
  /* 94 */
   {
       .CanIfCanRxPduId            = CANIF_PDU_ID_CANNMRX,
       .CanIfCanRxPduLowerCanId    = 0x600,
       .CanIfCanRxPduUpperCanId    = 0x6FF,
       .CanIfCanRxPduDlc           = 8,
#if ( CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON )
       .CanIfReadRxPduData         = FALSE,
#endif
#if ( CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON )
       .CanIfReadRxPduNotifyStatus = FALSE,
#endif
      .CanIdIsExtended            = FALSE,
      .CanIfUserRxIndication      = CANNM_CALLOUT,
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
      .OsekNmRxIndicationSupport  = STD_OFF,
#endif
  },
};


const CanIf_HthConfigType CanIfHthConfigData_CanIfInitHohCfg[] =
{
    {
        .CanIfHthType               = CANIF_HANDLE_TYPE_BASIC,
        .CanIfCanControllerIdRef    = CanIfConf_CanIfCtrlCfg_CanIfCtrlCfg,
        .CanIfHthIdSymRef           = CanConf_CanHardwareObject_Ctrl_0_Tx_0,
    },
    {
        .CanIfHthType               = CANIF_HANDLE_TYPE_BASIC,
        .CanIfCanControllerIdRef    = CanIfConf_CanIfCtrlCfg_CanIfCtrlCfg,
        .CanIfHthIdSymRef           = CanConf_CanHardwareObject_Ctrl_0_Tx_1,
    },
};
const uint16_t CanIfCanHohToCanIfHrhMap_CanIfInitHohCfg[] = {
    [CanConf_CanHardwareObject_Ctrl_0_Rx_0] = CanIfInitHohCfg_CanIfHrhCfg_INDEX,
    [CanConf_CanHardwareObject_Ctrl_0_Tx_0] = NO_CANIF_HRH,
};

const CanIf_HrhConfigType CanIfHrhConfigData_CanIfInitHohCfg[] =
{
    [CanIfInitHohCfg_CanIfHrhCfg_INDEX] = {
        .CanIfHrhType               = CANIF_HANDLE_TYPE_BASIC,
        .CanIfSoftwareFilterHrh     = TRUE,
        .CanIfHrhCanCtrlIdRef       = CanIfConf_CanIfCtrlCfg_CanIfCtrlCfg,
        .RxPduList                  = HrhRxPdu_CanIfHrhCfg,
        .NofRxPdus                  = CANIF_NUM_RX_LPDU,
    },
};
const CanIf_InitHohConfigType CanIfHohConfigData[] = {
    {
        .HrhListSize            = sizeof(CanIfCanHohToCanIfHrhMap_CanIfInitHohCfg)/sizeof(CanIfCanHohToCanIfHrhMap_CanIfInitHohCfg[0]),
        .CanHohToCanIfHrhMap    = CanIfCanHohToCanIfHrhMap_CanIfInitHohCfg,
        .CanIfHrhConfig         = CanIfHrhConfigData_CanIfInitHohCfg,
        .CanIfHthConfig         = CanIfHthConfigData_CanIfInitHohCfg,
    },
};


const CanIf_TxBufferConfigType CanIfBufferCfgData[] = {
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 0
    },

    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 1
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 2
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 3
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 4
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 5
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 6
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 7
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 8
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 9
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 10
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 11
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 12
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 13
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 14
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 15
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 16
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 17
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 18
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 19
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 20
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 21
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 22
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 23
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 24
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 25
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 26
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 27
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 28
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 29
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 30
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 31
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 32
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 33
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 34
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 35
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 36
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 37
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 38
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 39
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 40
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 41
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 42
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 43
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 44
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 45
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 46
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 47
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 48
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 49
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 50
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 51
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 52
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 53
    },
    {
        .CanIfBufferSize = 1,
        .CanIfBufferHthRef = &CanIfHthConfigData_CanIfInitHohCfg[0],
        .CanIf_As_BufferId = 54
    },
};


const CanIf_TxPduConfigType CanIfTxPduConfigData[] = {
    /* 0 */
 {
     .CanIfTxPduId               = CANTP_PDU_ID_DIAGPHYSICALTX,
     .CanIfCanTxPduIdCanId       = 0x7A5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = CANTP_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[0],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },

    /* 1 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_info_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x4F3,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[1],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 2 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_SLA_408_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x408,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[2],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 3 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_User_ID_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x376,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[3],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 4 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_096_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x096,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[4],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 5 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_control_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x075,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[5],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 6 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_comfortSet_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x095,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[6],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 7 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_pwrSet_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x0A5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[7],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 8 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_chassisSet1_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x1D5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[8],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 9 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_chassisSet_065_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x065,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[9],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 10 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_dvrSet_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x105,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[10],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 11 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_dsmmSet_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x098,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[11],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 12 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_dsmmSet2_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x093,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[12],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 13 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_infoSet_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x0C5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[13],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 14 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_VSP_state_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3A0,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[14],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 15 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_infoSet2_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x0C6,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[15],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 16 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_AVMSet_3D2_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3D2,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[16],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 17 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_scuSet_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x0F5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[17],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 18 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent1Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x31C,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[18],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 19 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent2Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x31D,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[19],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 20 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent3Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x325,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[20],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 21 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent4Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x328,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[21],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 22 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent5Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x33A,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[22],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 23 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent6Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x33B,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[23],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 24 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent7Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x34A,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[24],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 25 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_vent8Ctrl_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x34B,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[25],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 26 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_NaviChrgSt_33D_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x33D,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[26],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 27 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_NaviChrgSt_33E_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x33E,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[27],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 28 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_engineOFF_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x052,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[28],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 29 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_faultSum_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x5FD,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[29],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 30 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_infoSet_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3F2,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[30],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 31 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_3F8_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3F8,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[31],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 32 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_state3_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x4F4,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[32],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 33 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_Warning_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x571,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[33],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 34 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_Warningfb_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x570,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[34],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 35 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_state_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x2F2,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[35],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 36 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_info2_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3F7,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[36],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 37 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_state1_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x482,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[37],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 38 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_EnergyConsumption_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x491,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[38],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 39 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_state2_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x492,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[39],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 40 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_state4_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x493,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[40],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 41 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_state5_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x494,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[41],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 42 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_StatusAndNotify_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x495,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[42],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 43 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_hmi_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x496,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[43],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 44 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_State_5F0_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x5F0,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[44],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 45 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IC_RequestAndStatus_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x4A2,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[45],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 46 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_set_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3B5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[46],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 47 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_navi_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x485,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[47],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 48 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_NaviDirection_LaneX_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x486,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[48],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 49 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_media_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x395,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[49],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 50 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_naviText_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3C5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[50],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 51 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_TelSongText_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3A5,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[51],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 52 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_IVI_ADAS_3E1_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x3E1,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[52],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 53 */
 {
     .CanIfTxPduId               = PDUR_PDU_ID_Wacc_500_INFO_CANIF,
     .CanIfCanTxPduIdCanId       = 0x500,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = PDUR_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[53],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
    /* 54 */
 {
     .CanIfTxPduId               = CANIF_PDU_ID_CANNMTX,
     .CanIfCanTxPduIdCanId       = 0x622,
     .CanIfCanTxPduIdDlc         = 8,
     .CanIfCanTxPduType          = CANIF_PDU_TYPE_STATIC,
     .CanIfTxPduPnFilterEnable   = STD_OFF,
#if ( CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON )
     .CanIfReadTxPduNotifyStatus = FALSE,
#endif
     .CanIfTxPduIdCanIdType      = CANIF_CAN_ID_TYPE_11,
        .CanIfUserTxConfirmation    = CANNM_CALLOUT,
        .CanIfTxPduBufferRef        = &CanIfBufferCfgData[54],
#if ( CANIF_OSEKNM_SUPPORT == STD_ON )
        .OsekNmTxConfirmationSupport = STD_OFF,
#endif
    },
};


const CanIf_TxBufferConfigType *const CanIfCtrlCfg_BufferList[] = {
    &CanIfBufferCfgData[0],
    &CanIfBufferCfgData[1],
    &CanIfBufferCfgData[2],
    &CanIfBufferCfgData[3],
    &CanIfBufferCfgData[4],
    &CanIfBufferCfgData[5],
    &CanIfBufferCfgData[6],
    &CanIfBufferCfgData[7],
    &CanIfBufferCfgData[8],
    &CanIfBufferCfgData[9],
    &CanIfBufferCfgData[10],
    &CanIfBufferCfgData[11],
    &CanIfBufferCfgData[12],
    &CanIfBufferCfgData[13],
    &CanIfBufferCfgData[14],
    &CanIfBufferCfgData[15],
    &CanIfBufferCfgData[16],
    &CanIfBufferCfgData[17],
    &CanIfBufferCfgData[18],
    &CanIfBufferCfgData[19],
    &CanIfBufferCfgData[20],
    &CanIfBufferCfgData[21],
    &CanIfBufferCfgData[22],
    &CanIfBufferCfgData[23],
    &CanIfBufferCfgData[24],
    &CanIfBufferCfgData[25],
    &CanIfBufferCfgData[26],
    &CanIfBufferCfgData[27],
    &CanIfBufferCfgData[28],
    &CanIfBufferCfgData[29],
    &CanIfBufferCfgData[30],
    &CanIfBufferCfgData[31],
    &CanIfBufferCfgData[32],
    &CanIfBufferCfgData[33],
    &CanIfBufferCfgData[34],
    &CanIfBufferCfgData[35],
    &CanIfBufferCfgData[36],
    &CanIfBufferCfgData[37],
    &CanIfBufferCfgData[38],
    &CanIfBufferCfgData[39],
    &CanIfBufferCfgData[40],
    &CanIfBufferCfgData[41],
    &CanIfBufferCfgData[42],
    &CanIfBufferCfgData[43],
    &CanIfBufferCfgData[44],
    &CanIfBufferCfgData[45],
    &CanIfBufferCfgData[46],
    &CanIfBufferCfgData[47],
    &CanIfBufferCfgData[48],
    &CanIfBufferCfgData[49],
    &CanIfBufferCfgData[50],
    &CanIfBufferCfgData[51],
    &CanIfBufferCfgData[52],
    &CanIfBufferCfgData[53],
    &CanIfBufferCfgData[54],
};


const CanIf_As_ChannelConfigType CanIf_As_ChannelConfig[CANIF_CHANNEL_CNT] = {
    {
        /* CanIfCtrlCfg */
        .CanControllerId        = (uint32_t)CanConf_CanController_CanController0,
        .NofTxBuffers           = CANIF_AS_MAX_NOF_TX_BUFFERS,
        .TxBufferRefList        = CanIfCtrlCfg_BufferList,
#if (CANIF_OSEKNM_SUPPORT == STD_ON)
        .CanIfOsekNmNetId       = OSEKNMNETWORKHANDLE, /* OsekNm network identifier */
        .CanIfOsekNmNodeIdMask  = OSEKNMNODEIDMASK, /* OsekNM source node Id mask */
#endif
        .CanIfCtrlWakeUpSupport = STD_OFF,
        .CanIfCtrlWakeUpSrc     = 0,
        .CanIfCtrlPnFilterSet   = STD_OFF,
    },
};
// This container contains the init parameters of the CAN
const CanIf_InitConfigType CanIfInitConfig =
{
    .CanIfConfigSet                     = 0, // Not used
    .CanIfNumberOfCanRxPduIds           = CANIF_NUM_RX_LPDU,
    .CanIfNumberOfCanTXPduIds           = CANIF_NUM_TX_LPDU,
    .CanIfNumberOfDynamicCanTXPduIds    = 0, // Not used
    .CanIfNumberOfTxBuffers             = CANIF_AS_MAX_NOF_TX_BUFFERS,
    // Containers
    .CanIfBufferCfgPtr                  = CanIfBufferCfgData,
    .CanIfHohConfigPtr                  = CanIfHohConfigData,
    .CanIfTxPduConfigPtr                = CanIfTxPduConfigData,
};
// This container includes all necessary configuration sub-containers
// according the CAN Interface configuration structure.
const CanIf_ConfigType CanIf_Config =
{
    .InitConfig                     = &CanIfInitConfig,
    .CanIfTransceiverConfig         = NULL,
.As_ChannelConfig               = CanIf_As_ChannelConfig,
};


