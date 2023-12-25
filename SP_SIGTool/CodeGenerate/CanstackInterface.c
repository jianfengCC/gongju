
/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by APPSYS and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with APPSYS in writing by applicable law.
 *
 */
/**
 * @file    CanstckInterface.c
 * @brief   brief function description.
 * @details detailed function description.
 * @version 1.0
 * @author  wzc
 * @date    2023-08-23
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2023-08-23               wzc             Create it.
 *
 */
#include "CanstackInterface.h"
#include "r_typedefs.h"
#include "Com_Cfg.h"
#include "Com_As_Types.h"
#include "Com_Internal.h"

#define SENT_CNT_TO_RESET 3
void SpecialSignalProcessing(PduIdType PduId)
{
    boolean signalChanged = FALSE;
    const ComIPdu_type *IPdu = GET_IPdu(PduId);


    /*Changed by Limh20190724 for "ClearOdometerReq" logic and other event signal processing  where valid values are cleared once sent*/
    for (uint16_t i = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[i] != NULL); i++) {
        Com_As_Signal_type *As_Signal = GET_AsSignal(IPdu->ComIPduSignalRef[i]->ComHandleId);
        const Com_As_IPdu_type *As_IPdu = GET_AsIPdu(IPdu->ComIPduSignalRef[i]->ComIPduHandleId);
        if ((TRUE == IPdu->ComIPduSignalRef[i]->ComSignalAsUseUpdateBit)&&(As_Signal->ComSignalUpdated == TRUE)) {
            /*lint -e{9016} Array indexing couldn't be implemented, as parameters are of different data types */
            //CLEARBIT(As_IPdu->ComIPduDataPtr, IPdu->ComIPduSignalRef[i]->ComUpdateBitPosition);
#ifdef COMCONF_COMSIGNAL_IVI_CURRENTROADTYPE_0X408_INFO
            if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CURRENTROADTYPE_0X408_INFO)
            {
                eventSendCnt[E_IVI_CURRENTROADTYPE_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_CURRENTROADTYPE_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CURRENTROADTYPE_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO)
            {
                eventSendCnt[E_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODESTS_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODESTS_0X408_INFO)
            {
                eventSendCnt[E_IVI_VEHICLEREPAIRMODESTS_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_VEHICLEREPAIRMODESTS_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VEHICLEREPAIRMODESTS_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO)
            {
                eventSendCnt[E_IVI_USERGEARFB_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_USERGEARFB_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_USERGEARFB_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CARSEARCHSTS_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CARSEARCHSTS_0X408_INFO)
            {
                eventSendCnt[E_IVI_CARSEARCHSTS_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_CARSEARCHSTS_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CARSEARCHSTS_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CARSEARCHCONTROL_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CARSEARCHCONTROL_0X408_INFO)
            {
                eventSendCnt[E_IVI_CARSEARCHCONTROL_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_CARSEARCHCONTROL_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CARSEARCHCONTROL_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTORAINWIPERREQ_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AUTORAINWIPERREQ_0X408_INFO)
            {
                eventSendCnt[E_IVI_AUTORAINWIPERREQ_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_AUTORAINWIPERREQ_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AUTORAINWIPERREQ_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEPOSITION_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VEHICLEPOSITION_0X408_INFO)
            {
                eventSendCnt[E_IVI_VEHICLEPOSITION_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_VEHICLEPOSITION_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VEHICLEPOSITION_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACCOUNTLOGINSTATUS_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ACCOUNTLOGINSTATUS_0X408_INFO)
            {
                eventSendCnt[E_IVI_ACCOUNTLOGINSTATUS_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_ACCOUNTLOGINSTATUS_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ACCOUNTLOGINSTATUS_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANGUAGESET1_0X408_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LANGUAGESET1_0X408_INFO)
            {
                eventSendCnt[E_IVI_LANGUAGESET1_0X408_INFO] += 1;
                if (eventSendCnt[E_IVI_LANGUAGESET1_0X408_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LANGUAGESET1_0X408_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DANCEONOFFSET_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DANCEONOFFSET_0X096_INFO)
            {
                eventSendCnt[E_IVI_DANCEONOFFSET_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_DANCEONOFFSET_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DANCEONOFFSET_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_UNLOCKANIMATSET_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_UNLOCKANIMATSET_0X096_INFO)
            {
                eventSendCnt[E_IVI_UNLOCKANIMATSET_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_UNLOCKANIMATSET_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_UNLOCKANIMATSET_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOCKANIMATSET_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LOCKANIMATSET_0X096_INFO)
            {
                eventSendCnt[E_IVI_LOCKANIMATSET_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_LOCKANIMATSET_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LOCKANIMATSET_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FLWINOPENDEGREERE_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FLWINOPENDEGREERE_0X096_INFO)
            {
                eventSendCnt[E_IVI_FLWINOPENDEGREERE_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_FLWINOPENDEGREERE_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FLWINOPENDEGREERE_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FRWINOPENDEGREERE_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FRWINOPENDEGREERE_0X096_INFO)
            {
                eventSendCnt[E_IVI_FRWINOPENDEGREERE_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_FRWINOPENDEGREERE_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FRWINOPENDEGREERE_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RLWINOPENDEGREERE_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RLWINOPENDEGREERE_0X096_INFO)
            {
                eventSendCnt[E_IVI_RLWINOPENDEGREERE_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_RLWINOPENDEGREERE_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RLWINOPENDEGREERE_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RRWINOPENDEGREERE_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RRWINOPENDEGREERE_0X096_INFO)
            {
                eventSendCnt[E_IVI_RRWINOPENDEGREERE_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_RRWINOPENDEGREERE_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RRWINOPENDEGREERE_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_BCMLOCKSOUNDSET_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_BCMLOCKSOUNDSET_0X096_INFO)
            {
                eventSendCnt[E_IVI_BCMLOCKSOUNDSET_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_BCMLOCKSOUNDSET_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_BCMLOCKSOUNDSET_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOCKCLOSEWINSET_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LOCKCLOSEWINSET_0X096_INFO)
            {
                eventSendCnt[E_IVI_LOCKCLOSEWINSET_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_LOCKCLOSEWINSET_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LOCKCLOSEWINSET_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FRONTDEFROSTLEVELSET_0X096_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FRONTDEFROSTLEVELSET_0X096_INFO)
            {
                eventSendCnt[E_IVI_FRONTDEFROSTLEVELSET_0X096_INFO] += 1;
                if (eventSendCnt[E_IVI_FRONTDEFROSTLEVELSET_0X096_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FRONTDEFROSTLEVELSET_0X096_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHILDLOCKCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHILDLOCKCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_CHILDLOCKCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_CHILDLOCKCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHILDLOCKCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CENTRALLOCKCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CENTRALLOCKCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_CENTRALLOCKCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_CENTRALLOCKCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CENTRALLOCKCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FUELPORTCAPOPENCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FUELPORTCAPOPENCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_FUELPORTCAPOPENCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_FUELPORTCAPOPENCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FUELPORTCAPOPENCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOWBEAMONOFFCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LOWBEAMONOFFCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_LOWBEAMONOFFCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_LOWBEAMONOFFCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LOWBEAMONOFFCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_V2VCHRGONOFFSET_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_V2VCHRGONOFFSET_0X075_INFO)
            {
                eventSendCnt[E_IVI_V2VCHRGONOFFSET_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_V2VCHRGONOFFSET_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_V2VCHRGONOFFSET_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_OBCDSCHRGONOFFSET_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_OBCDSCHRGONOFFSET_0X075_INFO)
            {
                eventSendCnt[E_IVI_OBCDSCHRGONOFFSET_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_OBCDSCHRGONOFFSET_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_OBCDSCHRGONOFFSET_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ROOFLAMPONOFFCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ROOFLAMPONOFFCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_ROOFLAMPONOFFCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_ROOFLAMPONOFFCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ROOFLAMPONOFFCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NORMALHVOFFREQUEST_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_NORMALHVOFFREQUEST_0X075_INFO)
            {
                eventSendCnt[E_IVI_NORMALHVOFFREQUEST_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_NORMALHVOFFREQUEST_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_NORMALHVOFFREQUEST_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TAILGATECTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TAILGATECTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_TAILGATECTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_TAILGATECTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TAILGATECTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MIRRORSW_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_MIRRORSW_0X075_INFO)
            {
                eventSendCnt[E_IVI_MIRRORSW_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_MIRRORSW_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_MIRRORSW_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REARDEFROSTCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_REARDEFROSTCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_REARDEFROSTCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_REARDEFROSTCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_REARDEFROSTCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO)
            {
                eventSendCnt[E_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO)
            {
                eventSendCnt[E_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_V2VCHRGOPTCURNTSET_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_V2VCHRGOPTCURNTSET_0X075_INFO)
            {
                eventSendCnt[E_IVI_V2VCHRGOPTCURNTSET_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_V2VCHRGOPTCURNTSET_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_V2VCHRGOPTCURNTSET_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AWAYLOCKCTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AWAYLOCKCTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_AWAYLOCKCTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_AWAYLOCKCTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AWAYLOCKCTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WIPPERMAINTMODECTRL_0X075_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_WIPPERMAINTMODECTRL_0X075_INFO)
            {
                eventSendCnt[E_IVI_WIPPERMAINTMODECTRL_0X075_INFO] += 1;
                if (eventSendCnt[E_IVI_WIPPERMAINTMODECTRL_0X075_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_WIPPERMAINTMODECTRL_0X075_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NOZZLEHEATINGSW_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_NOZZLEHEATINGSW_0X095_INFO)
            {
                eventSendCnt[E_IVI_NOZZLEHEATINGSW_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_NOZZLEHEATINGSW_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_NOZZLEHEATINGSW_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO)
            {
                eventSendCnt[E_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ONEKEYMODESET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ONEKEYMODESET_0X095_INFO)
            {
                eventSendCnt[E_IVI_ONEKEYMODESET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_ONEKEYMODESET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ONEKEYMODESET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO)
            {
                eventSendCnt[E_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO)
            {
                eventSendCnt[E_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LIMITMODESET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LIMITMODESET_0X095_INFO)
            {
                eventSendCnt[E_IVI_LIMITMODESET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_LIMITMODESET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LIMITMODESET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DOORTOPSWITCH_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DOORTOPSWITCH_0X095_INFO)
            {
                eventSendCnt[E_IVI_DOORTOPSWITCH_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_DOORTOPSWITCH_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DOORTOPSWITCH_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO)
            {
                eventSendCnt[E_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FOLLOWMEHOMESET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FOLLOWMEHOMESET_0X095_INFO)
            {
                eventSendCnt[E_IVI_FOLLOWMEHOMESET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_FOLLOWMEHOMESET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FOLLOWMEHOMESET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINLFCTRLRQST_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_WINLFCTRLRQST_0X095_INFO)
            {
                eventSendCnt[E_IVI_WINLFCTRLRQST_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_WINLFCTRLRQST_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_WINLFCTRLRQST_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINRFCTRLRQST_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_WINRFCTRLRQST_0X095_INFO)
            {
                eventSendCnt[E_IVI_WINRFCTRLRQST_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_WINRFCTRLRQST_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_WINRFCTRLRQST_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINLRCTRLRQST_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_WINLRCTRLRQST_0X095_INFO)
            {
                eventSendCnt[E_IVI_WINLRCTRLRQST_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_WINLRCTRLRQST_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_WINLRCTRLRQST_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINRRCTRLRQST_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_WINRRCTRLRQST_0X095_INFO)
            {
                eventSendCnt[E_IVI_WINRRCTRLRQST_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_WINRRCTRLRQST_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_WINRRCTRLRQST_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHILDLOCKRLCTRL_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHILDLOCKRLCTRL_0X095_INFO)
            {
                eventSendCnt[E_IVI_CHILDLOCKRLCTRL_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_CHILDLOCKRLCTRL_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHILDLOCKRLCTRL_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHILDLOCKRRCTRL_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHILDLOCKRRCTRL_0X095_INFO)
            {
                eventSendCnt[E_IVI_CHILDLOCKRRCTRL_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_CHILDLOCKRRCTRL_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHILDLOCKRRCTRL_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO)
            {
                eventSendCnt[E_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTODRYSET_0X095_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AUTODRYSET_0X095_INFO)
            {
                eventSendCnt[E_IVI_AUTODRYSET_0X095_INFO] += 1;
                if (eventSendCnt[E_IVI_AUTODRYSET_0X095_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AUTODRYSET_0X095_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRIPARESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TRIPARESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_TRIPARESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_TRIPARESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TRIPARESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRIPBRESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TRIPBRESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_TRIPBRESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_TRIPBRESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TRIPBRESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEMODESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VEHICLEMODESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_VEHICLEMODESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_VEHICLEMODESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VEHICLEMODESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REGENMODESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_REGENMODESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_REGENMODESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_REGENMODESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_REGENMODESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRAVEMODESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TRAVEMODESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_TRAVEMODESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_TRAVEMODESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TRAVEMODESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGECONTROL_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGECONTROL_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGECONTROL_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGECONTROL_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGECONTROL_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKINGCHARGEREQ_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PARKINGCHARGEREQ_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_PARKINGCHARGEREQ_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_PARKINGCHARGEREQ_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PARKINGCHARGEREQ_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TOWMODESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TOWMODESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_TOWMODESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_TOWMODESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TOWMODESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MAXCHRGSOCSET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_MAXCHRGSOCSET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_MAXCHRGSOCSET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_MAXCHRGSOCSET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_MAXCHRGSOCSET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEFORMSET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGEFORMSET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGEFORMSET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGEFORMSET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGEFORMSET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REMAINNINGMILMODESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_REMAINNINGMILMODESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_REMAINNINGMILMODESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_REMAINNINGMILMODESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_REMAINNINGMILMODESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKINGCHARGEMODESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PARKINGCHARGEMODESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_PARKINGCHARGEMODESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_PARKINGCHARGEMODESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PARKINGCHARGEMODESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESETVALID_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGESETVALID_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGESETVALID_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGESETVALID_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGESETVALID_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RESETCURRENTTRIP_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RESETCURRENTTRIP_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_RESETCURRENTTRIP_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_RESETCURRENTTRIP_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RESETCURRENTTRIP_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEVALID_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEVALID_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGEENDTIMEVALID_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGEENDTIMEVALID_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGEENDTIMEVALID_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRIVEMODESET_0X0A5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRIVEMODESET_0X0A5_INFO)
            {
                eventSendCnt[E_IVI_DRIVEMODESET_0X0A5_INFO] += 1;
                if (eventSendCnt[E_IVI_DRIVEMODESET_0X0A5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRIVEMODESET_0X0A5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO)
            {
                eventSendCnt[E_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO] += 1;
                if (eventSendCnt[E_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EXHIBITIONMODECTRL_0X1D5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_EXHIBITIONMODECTRL_0X1D5_INFO)
            {
                eventSendCnt[E_IVI_EXHIBITIONMODECTRL_0X1D5_INFO] += 1;
                if (eventSendCnt[E_IVI_EXHIBITIONMODECTRL_0X1D5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_EXHIBITIONMODECTRL_0X1D5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DCDCAUTOCHARGESET_0X1D5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DCDCAUTOCHARGESET_0X1D5_INFO)
            {
                eventSendCnt[E_IVI_DCDCAUTOCHARGESET_0X1D5_INFO] += 1;
                if (eventSendCnt[E_IVI_DCDCAUTOCHARGESET_0X1D5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DCDCAUTOCHARGESET_0X1D5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVDOWNREPAIRMODE_0X1D5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVDOWNREPAIRMODE_0X1D5_INFO)
            {
                eventSendCnt[E_IVI_HVDOWNREPAIRMODE_0X1D5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVDOWNREPAIRMODE_0X1D5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVDOWNREPAIRMODE_0X1D5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EPSMODESET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_EPSMODESET_0X065_INFO)
            {
                eventSendCnt[E_IVI_EPSMODESET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_EPSMODESET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_EPSMODESET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ESCOFFSW_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ESCOFFSW_0X065_INFO)
            {
                eventSendCnt[E_IVI_ESCOFFSW_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_ESCOFFSW_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ESCOFFSW_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HDCONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HDCONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_HDCONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_HDCONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HDCONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AEBONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AEBONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_AEBONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_AEBONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AEBONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_IBMODESET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_IBMODESET_0X065_INFO)
            {
                eventSendCnt[E_IVI_IBMODESET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_IBMODESET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_IBMODESET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LCABSDONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LCABSDONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_LCABSDONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_LCABSDONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LCABSDONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RCTAONOFFSETRESERVED_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RCTAONOFFSETRESERVED_0X065_INFO)
            {
                eventSendCnt[E_IVI_RCTAONOFFSETRESERVED_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_RCTAONOFFSETRESERVED_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RCTAONOFFSETRESERVED_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DOWONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DOWONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_DOWONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_DOWONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DOWONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_STARTREVSOCSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_STARTREVSOCSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_STARTREVSOCSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_STARTREVSOCSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_STARTREVSOCSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HMAONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HMAONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_HMAONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_HMAONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HMAONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDLIMITONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_SPEEDLIMITONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_SPEEDLIMITONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_SPEEDLIMITONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_SPEEDLIMITONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ASCHEIGHTMODESELECTED_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ASCHEIGHTMODESELECTED_0X065_INFO)
            {
                eventSendCnt[E_IVI_ASCHEIGHTMODESELECTED_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_ASCHEIGHTMODESELECTED_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ASCHEIGHTMODESELECTED_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ASCMOVEMODECONTROL_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ASCMOVEMODECONTROL_0X065_INFO)
            {
                eventSendCnt[E_IVI_ASCMOVEMODECONTROL_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_ASCMOVEMODECONTROL_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ASCMOVEMODECONTROL_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANEASSISTFUNCSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LANEASSISTFUNCSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_LANEASSISTFUNCSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_LANEASSISTFUNCSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LANEASSISTFUNCSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LASWARNINGMODESELECTION_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LASWARNINGMODESELECTION_0X065_INFO)
            {
                eventSendCnt[E_IVI_LASWARNINGMODESELECTION_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_LASWARNINGMODESELECTION_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LASWARNINGMODESELECTION_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_TRAILERMODEREQ_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_TRAILERMODEREQ_0X065_INFO)
            {
                eventSendCnt[E_TRAILERMODEREQ_0X065_INFO] += 1;
                if (eventSendCnt[E_TRAILERMODEREQ_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_TRAILERMODEREQ_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RCTBONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RCTBONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_RCTBONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_RCTBONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RCTBONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ELKONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ELKONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_ELKONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_ELKONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ELKONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVHONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVHONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_AVHONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_AVHONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVHONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PCWONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PCWONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_PCWONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_PCWONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PCWONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TJAFUNCSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TJAFUNCSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_TJAFUNCSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_TJAFUNCSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TJAFUNCSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTODODGEONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AUTODODGEONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_AUTODODGEONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_AUTODODGEONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AUTODODGEONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRAILERMODEONOFFSET_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TRAILERMODEONOFFSET_0X065_INFO)
            {
                eventSendCnt[E_IVI_TRAILERMODEONOFFSET_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_TRAILERMODEONOFFSET_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TRAILERMODEONOFFSET_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO)
            {
                eventSendCnt[E_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAONOFFREQ_0X065_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_APAONOFFREQ_0X065_INFO)
            {
                eventSendCnt[E_IVI_APAONOFFREQ_0X065_INFO] += 1;
                if (eventSendCnt[E_IVI_APAONOFFREQ_0X065_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_APAONOFFREQ_0X065_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAFUNCSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_APAFUNCSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_APAFUNCSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_APAFUNCSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_APAFUNCSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RPAFUNCSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RPAFUNCSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_RPAFUNCSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_RPAFUNCSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RPAFUNCSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APADRVSPEEDSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_APADRVSPEEDSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_APADRVSPEEDSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_APADRVSPEEDSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_APADRVSPEEDSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMVIEWSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMVIEWSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_AVMVIEWSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMVIEWSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMVIEWSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMCARBODYTRANSPSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMCARBODYTRANSPSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_AVMCARBODYTRANSPSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMCARBODYTRANSPSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMCARBODYTRANSPSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMTRIGBYSENSORSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMTRIGBYSENSORSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_AVMTRIGBYSENSORSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMTRIGBYSENSORSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMTRIGBYSENSORSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PDCSOUNDSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PDCSOUNDSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_PDCSOUNDSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_PDCSOUNDSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PDCSOUNDSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PDCMUTEREQ_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PDCMUTEREQ_0X066_INFO)
            {
                eventSendCnt[E_IVI_PDCMUTEREQ_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_PDCMUTEREQ_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PDCMUTEREQ_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LAEB_SW_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LAEB_SW_0X066_INFO)
            {
                eventSendCnt[E_IVI_LAEB_SW_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_LAEB_SW_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LAEB_SW_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FRONTPDCALARMSET_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FRONTPDCALARMSET_0X066_INFO)
            {
                eventSendCnt[E_IVI_FRONTPDCALARMSET_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_FRONTPDCALARMSET_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FRONTPDCALARMSET_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAPARKINTYPESEL_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_APAPARKINTYPESEL_0X066_INFO)
            {
                eventSendCnt[E_IVI_APAPARKINTYPESEL_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_APAPARKINTYPESEL_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_APAPARKINTYPESEL_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKSCENERECONSW_0X066_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PARKSCENERECONSW_0X066_INFO)
            {
                eventSendCnt[E_IVI_PARKSCENERECONSW_0X066_INFO] += 1;
                if (eventSendCnt[E_IVI_PARKSCENERECONSW_0X066_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PARKSCENERECONSW_0X066_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICAONOFFSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ICAONOFFSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_ICAONOFFSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_ICAONOFFSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ICAONOFFSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANECHANGESTALY_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LANECHANGESTALY_0X067_INFO)
            {
                eventSendCnt[E_IVI_LANECHANGESTALY_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_LANECHANGESTALY_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LANECHANGESTALY_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTOLANECHANGESET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AUTOLANECHANGESET_0X067_INFO)
            {
                eventSendCnt[E_IVI_AUTOLANECHANGESET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_AUTOLANECHANGESET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AUTOLANECHANGESET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RAMPFOLLOWCARSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RAMPFOLLOWCARSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_RAMPFOLLOWCARSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_RAMPFOLLOWCARSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RAMPFOLLOWCARSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NCAONOFFSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_NCAONOFFSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_NCAONOFFSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_NCAONOFFSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_NCAONOFFSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDLIMITSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_SPEEDLIMITSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_SPEEDLIMITSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_SPEEDLIMITSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_SPEEDLIMITSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VOICEBROADCASTSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VOICEBROADCASTSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_VOICEBROADCASTSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_VOICEBROADCASTSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VOICEBROADCASTSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDPROPORTIONSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_SPEEDPROPORTIONSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_SPEEDPROPORTIONSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_SPEEDPROPORTIONSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_SPEEDPROPORTIONSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDVALUESET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_SPEEDVALUESET_0X067_INFO)
            {
                eventSendCnt[E_IVI_SPEEDVALUESET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_SPEEDVALUESET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_SPEEDVALUESET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANECHANGSTYLESET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LANECHANGSTYLESET_0X067_INFO)
            {
                eventSendCnt[E_IVI_LANECHANGSTYLESET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_LANECHANGSTYLESET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LANECHANGSTYLESET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TARGETSPEEDOFFSETSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TARGETSPEEDOFFSETSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_TARGETSPEEDOFFSETSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_TARGETSPEEDOFFSETSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TARGETSPEEDOFFSETSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NCAFUNCSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_NCAFUNCSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_NCAFUNCSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_NCAFUNCSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_NCAFUNCSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICAFUNCSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ICAFUNCSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_ICAFUNCSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_ICAFUNCSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ICAFUNCSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ALCFUNCSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ALCFUNCSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_ALCFUNCSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_ALCFUNCSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ALCFUNCSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANECHANGECONFIRMSET_0X067_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LANECHANGECONFIRMSET_0X067_INFO)
            {
                eventSendCnt[E_IVI_LANECHANGECONFIRMSET_0X067_INFO] += 1;
                if (eventSendCnt[E_IVI_LANECHANGECONFIRMSET_0X067_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LANECHANGECONFIRMSET_0X067_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SLAFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_SLAFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_SLAFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_SLAFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_SLAFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANEASSISTTYPESET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LANEASSISTTYPESET_0X069_INFO)
            {
                eventSendCnt[E_IVI_LANEASSISTTYPESET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_LANEASSISTTYPESET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LANEASSISTTYPESET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LASWARNMODESET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LASWARNMODESET_0X069_INFO)
            {
                eventSendCnt[E_IVI_LASWARNMODESET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_LASWARNMODESET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LASWARNMODESET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ELKFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ELKFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_ELKFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_ELKFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ELKFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FCWFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FCWFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_FCWFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_FCWFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FCWFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AEBFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AEBFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_AEBFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_AEBFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AEBFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LAEBFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LAEBFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_LAEBFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_LAEBFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LAEBFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RCWFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RCWFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_RCWFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_RCWFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RCWFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_BSDLCAFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_BSDLCAFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_BSDLCAFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_BSDLCAFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_BSDLCAFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DOWFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DOWFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_DOWFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_DOWFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DOWFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_STARTREMFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_STARTREMFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_STARTREMFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_STARTREMFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_STARTREMFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HMAFUNCSET_0X069_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HMAFUNCSET_0X069_INFO)
            {
                eventSendCnt[E_IVI_HMAFUNCSET_0X069_INFO] += 1;
                if (eventSendCnt[E_IVI_HMAFUNCSET_0X069_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HMAFUNCSET_0X069_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_X_0X068_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_X_0X068_INFO)
            {
                eventSendCnt[E_IVI_AVMROTATIONANGLE_X_0X068_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMROTATIONANGLE_X_0X068_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMROTATIONANGLE_X_0X068_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_Y_0X068_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_Y_0X068_INFO)
            {
                eventSendCnt[E_IVI_AVMROTATIONANGLE_Y_0X068_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMROTATIONANGLE_Y_0X068_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMROTATIONANGLE_Y_0X068_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RPAAPASWITCH_0X068_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RPAAPASWITCH_0X068_INFO)
            {
                eventSendCnt[E_IVI_RPAAPASWITCH_0X068_INFO] += 1;
                if (eventSendCnt[E_IVI_RPAAPASWITCH_0X068_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RPAAPASWITCH_0X068_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAFUNCREQ_0X068_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_APAFUNCREQ_0X068_INFO)
            {
                eventSendCnt[E_IVI_APAFUNCREQ_0X068_INFO] += 1;
                if (eventSendCnt[E_IVI_APAFUNCREQ_0X068_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_APAFUNCREQ_0X068_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMVIEWSELECT_0X068_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AVMVIEWSELECT_0X068_INFO)
            {
                eventSendCnt[E_IVI_AVMVIEWSELECT_0X068_INFO] += 1;
                if (eventSendCnt[E_IVI_AVMVIEWSELECT_0X068_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AVMVIEWSELECT_0X068_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO)
            {
                eventSendCnt[E_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO] += 1;
                if (eventSendCnt[E_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_STERRINGWHEELHEATSW_0X105_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_STERRINGWHEELHEATSW_0X105_INFO)
            {
                eventSendCnt[E_IVI_STERRINGWHEELHEATSW_0X105_INFO] += 1;
                if (eventSendCnt[E_IVI_STERRINGWHEELHEATSW_0X105_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_STERRINGWHEELHEATSW_0X105_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATROUTESET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRSEATROUTESET_0X098_INFO)
            {
                eventSendCnt[E_IVI_DRSEATROUTESET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_DRSEATROUTESET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRSEATROUTESET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATBACKRESTSET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRSEATBACKRESTSET_0X098_INFO)
            {
                eventSendCnt[E_IVI_DRSEATBACKRESTSET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_DRSEATBACKRESTSET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRSEATBACKRESTSET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONSET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONSET_0X098_INFO)
            {
                eventSendCnt[E_IVI_DRSEATCUSHIONSET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_DRSEATCUSHIONSET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRSEATCUSHIONSET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONANGLESET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONANGLESET_0X098_INFO)
            {
                eventSendCnt[E_IVI_DRSEATCUSHIONANGLESET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_DRSEATCUSHIONANGLESET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRSEATCUSHIONANGLESET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LMIRRORUDSET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LMIRRORUDSET_0X098_INFO)
            {
                eventSendCnt[E_IVI_LMIRRORUDSET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_LMIRRORUDSET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LMIRRORUDSET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LMIRRORLRSET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LMIRRORLRSET_0X098_INFO)
            {
                eventSendCnt[E_IVI_LMIRRORLRSET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_LMIRRORLRSET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LMIRRORLRSET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RMIRRORUDSET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RMIRRORUDSET_0X098_INFO)
            {
                eventSendCnt[E_IVI_RMIRRORUDSET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_RMIRRORUDSET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RMIRRORUDSET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RMIRRORLRSET_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RMIRRORLRSET_0X098_INFO)
            {
                eventSendCnt[E_IVI_RMIRRORLRSET_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_RMIRRORLRSET_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RMIRRORLRSET_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DSMCHARGECTRL_0X098_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DSMCHARGECTRL_0X098_INFO)
            {
                eventSendCnt[E_IVI_DSMCHARGECTRL_0X098_INFO] += 1;
                if (eventSendCnt[E_IVI_DSMCHARGECTRL_0X098_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DSMCHARGECTRL_0X098_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATROUTESET_0X093_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSSEATROUTESET_0X093_INFO)
            {
                eventSendCnt[E_IVI_PASSSEATROUTESET_0X093_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSSEATROUTESET_0X093_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSSEATROUTESET_0X093_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATBACKRESTSET_0X093_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSSEATBACKRESTSET_0X093_INFO)
            {
                eventSendCnt[E_IVI_PASSSEATBACKRESTSET_0X093_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSSEATBACKRESTSET_0X093_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSSEATBACKRESTSET_0X093_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONSET_0X093_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONSET_0X093_INFO)
            {
                eventSendCnt[E_IVI_PASSSEATCUSHIONSET_0X093_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSSEATCUSHIONSET_0X093_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSSEATCUSHIONSET_0X093_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO)
            {
                eventSendCnt[E_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRIPSWITCHRESERVED_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TRIPSWITCHRESERVED_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_TRIPSWITCHRESERVED_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_TRIPSWITCHRESERVED_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TRIPSWITCHRESERVED_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HUDONOFFSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HUDONOFFSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_HUDONOFFSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_HUDONOFFSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HUDONOFFSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_THEMESETRESERVED_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_THEMESETRESERVED_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_THEMESETRESERVED_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_THEMESETRESERVED_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_THEMESETRESERVED_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WCMONOFFSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_WCMONOFFSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_WCMONOFFSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_WCMONOFFSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_WCMONOFFSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PDCONOFFSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PDCONOFFSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_PDCONOFFSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_PDCONOFFSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PDCONOFFSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FACTORYRESETCOMMAND_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_FACTORYRESETCOMMAND_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_FACTORYRESETCOMMAND_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_FACTORYRESETCOMMAND_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_FACTORYRESETCOMMAND_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICILLUMILEVELSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ICILLUMILEVELSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_ICILLUMILEVELSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_ICILLUMILEVELSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ICILLUMILEVELSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LAEB_SW_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LAEB_SW_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_LAEB_SW_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_LAEB_SW_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LAEB_SW_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VSPONOFFSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VSPONOFFSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_VSPONOFFSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_VSPONOFFSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VSPONOFFSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_UNLOCKSOUNDSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_UNLOCKSOUNDSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_UNLOCKSOUNDSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_UNLOCKSOUNDSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_UNLOCKSOUNDSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOCKSOUNDSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LOCKSOUNDSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_LOCKSOUNDSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_LOCKSOUNDSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LOCKSOUNDSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ISAONOFFSET_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ISAONOFFSET_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_ISAONOFFSET_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_ISAONOFFSET_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ISAONOFFSET_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO)
            {
                eventSendCnt[E_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO] += 1;
                if (eventSendCnt[E_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHMNTNMILECLEA_0X0C6_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VEHMNTNMILECLEA_0X0C6_INFO)
            {
                eventSendCnt[E_IVI_VEHMNTNMILECLEA_0X0C6_INFO] += 1;
                if (eventSendCnt[E_IVI_VEHMNTNMILECLEA_0X0C6_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VEHMNTNMILECLEA_0X0C6_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_OILMNTNMILECLEA_0X0C6_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_OILMNTNMILECLEA_0X0C6_INFO)
            {
                eventSendCnt[E_IVI_OILMNTNMILECLEA_0X0C6_INFO] += 1;
                if (eventSendCnt[E_IVI_OILMNTNMILECLEA_0X0C6_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_OILMNTNMILECLEA_0X0C6_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_OILFILMNTNMILECLEA_0X0C6_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_OILFILMNTNMILECLEA_0X0C6_INFO)
            {
                eventSendCnt[E_IVI_OILFILMNTNMILECLEA_0X0C6_INFO] += 1;
                if (eventSendCnt[E_IVI_OILFILMNTNMILECLEA_0X0C6_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_OILFILMNTNMILECLEA_0X0C6_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO)
            {
                eventSendCnt[E_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO] += 1;
                if (eventSendCnt[E_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHMNTNTIMECLEA_0X0C6_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_VEHMNTNTIMECLEA_0X0C6_INFO)
            {
                eventSendCnt[E_IVI_VEHMNTNTIMECLEA_0X0C6_INFO] += 1;
                if (eventSendCnt[E_IVI_VEHMNTNTIMECLEA_0X0C6_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_VEHMNTNTIMECLEA_0X0C6_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_IVITHEMESET1_0X3D2_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_IVITHEMESET1_0X3D2_INFO)
            {
                eventSendCnt[E_IVI_IVITHEMESET1_0X3D2_INFO] += 1;
                if (eventSendCnt[E_IVI_IVITHEMESET1_0X3D2_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_IVITHEMESET1_0X3D2_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO)
            {
                eventSendCnt[E_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO] += 1;
                if (eventSendCnt[E_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ALARMLISTREQUEST_0X3D2_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ALARMLISTREQUEST_0X3D2_INFO)
            {
                eventSendCnt[E_IVI_ALARMLISTREQUEST_0X3D2_INFO] += 1;
                if (eventSendCnt[E_IVI_ALARMLISTREQUEST_0X3D2_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ALARMLISTREQUEST_0X3D2_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EASYENTRYSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_EASYENTRYSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_EASYENTRYSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_EASYENTRYSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_EASYENTRYSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATHEATLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRSEATHEATLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_DRSEATHEATLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_DRSEATHEATLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRSEATHEATLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATVENTLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRSEATVENTLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_DRSEATVENTLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_DRSEATVENTLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRSEATVENTLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATMASSLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRSEATMASSLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_DRSEATMASSLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_DRSEATMASSLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRSEATMASSLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RLSEATHEATLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RLSEATHEATLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_RLSEATHEATLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_RLSEATHEATLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RLSEATHEATLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRMASSGINTENSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRMASSGINTENSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_DRMASSGINTENSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_DRMASSGINTENSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRMASSGINTENSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PSGMASSGINTENSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PSGMASSGINTENSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_PSGMASSGINTENSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_PSGMASSGINTENSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PSGMASSGINTENSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DSMMEMORYREQ_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DSMMEMORYREQ_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_DSMMEMORYREQ_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_DSMMEMORYREQ_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DSMMEMORYREQ_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RRSEATHEATLEVELSET_0X0F5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RRSEATHEATLEVELSET_0X0F5_INFO)
            {
                eventSendCnt[E_IVI_RRSEATHEATLEVELSET_0X0F5_INFO] += 1;
                if (eventSendCnt[E_IVI_RRSEATHEATLEVELSET_0X0F5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RRSEATHEATLEVELSET_0X0F5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO)
            {
                eventSendCnt[E_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO] += 1;
                if (eventSendCnt[E_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_SONGFAULTNUM_0X052_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_SONGFAULTNUM_0X052_INFO)
            {
                eventSendCnt[E_IC_SONGFAULTNUM_0X052_INFO] += 1;
                if (eventSendCnt[E_IC_SONGFAULTNUM_0X052_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_SONGFAULTNUM_0X052_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_SONGWARNINGSTS_0X052_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_SONGWARNINGSTS_0X052_INFO)
            {
                eventSendCnt[E_IC_SONGWARNINGSTS_0X052_INFO] += 1;
                if (eventSendCnt[E_IC_SONGWARNINGSTS_0X052_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_SONGWARNINGSTS_0X052_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_HUDILLUMILVSET_0X3F2_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_HUDILLUMILVSET_0X3F2_INFO)
            {
                eventSendCnt[E_IC_HUDILLUMILVSET_0X3F2_INFO] += 1;
                if (eventSendCnt[E_IC_HUDILLUMILVSET_0X3F2_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_HUDILLUMILVSET_0X3F2_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO)
            {
                eventSendCnt[E_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_ALARMLISTFLAG_0X571_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_ALARMLISTFLAG_0X571_INFO)
            {
                eventSendCnt[E_IC_ALARMLISTFLAG_0X571_INFO] += 1;
                if (eventSendCnt[E_IC_ALARMLISTFLAG_0X571_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_ALARMLISTFLAG_0X571_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS_0X571_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS_0X571_INFO)
            {
                eventSendCnt[E_IC_WARNINGSTATUS_0X571_INFO] += 1;
                if (eventSendCnt[E_IC_WARNINGSTATUS_0X571_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_WARNINGSTATUS_0X571_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS2_0X571_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS2_0X571_INFO)
            {
                eventSendCnt[E_IC_WARNINGSTATUS2_0X571_INFO] += 1;
                if (eventSendCnt[E_IC_WARNINGSTATUS2_0X571_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_WARNINGSTATUS2_0X571_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS3_0X571_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS3_0X571_INFO)
            {
                eventSendCnt[E_IC_WARNINGSTATUS3_0X571_INFO] += 1;
                if (eventSendCnt[E_IC_WARNINGSTATUS3_0X571_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_WARNINGSTATUS3_0X571_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS4_0X571_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS4_0X571_INFO)
            {
                eventSendCnt[E_IC_WARNINGSTATUS4_0X571_INFO] += 1;
                if (eventSendCnt[E_IC_WARNINGSTATUS4_0X571_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_WARNINGSTATUS4_0X571_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS5_0X571_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS5_0X571_INFO)
            {
                eventSendCnt[E_IC_WARNINGSTATUS5_0X571_INFO] += 1;
                if (eventSendCnt[E_IC_WARNINGSTATUS5_0X571_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_WARNINGSTATUS5_0X571_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS6_0X571_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS6_0X571_INFO)
            {
                eventSendCnt[E_IC_WARNINGSTATUS6_0X571_INFO] += 1;
                if (eventSendCnt[E_IC_WARNINGSTATUS6_0X571_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_WARNINGSTATUS6_0X571_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_DMS_DISTRACTIONICONFB_0X570_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_DMS_DISTRACTIONICONFB_0X570_INFO)
            {
                eventSendCnt[E_IC_DMS_DISTRACTIONICONFB_0X570_INFO] += 1;
                if (eventSendCnt[E_IC_DMS_DISTRACTIONICONFB_0X570_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_DMS_DISTRACTIONICONFB_0X570_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_DMS_FATIGUEICONFB_0X570_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_DMS_FATIGUEICONFB_0X570_INFO)
            {
                eventSendCnt[E_IC_DMS_FATIGUEICONFB_0X570_INFO] += 1;
                if (eventSendCnt[E_IC_DMS_FATIGUEICONFB_0X570_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_DMS_FATIGUEICONFB_0X570_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_VEHMNTNMILERMNREQ_0X492_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_VEHMNTNMILERMNREQ_0X492_INFO)
            {
                eventSendCnt[E_IC_VEHMNTNMILERMNREQ_0X492_INFO] += 1;
                if (eventSendCnt[E_IC_VEHMNTNMILERMNREQ_0X492_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_VEHMNTNMILERMNREQ_0X492_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_VEHMNTNTIMERMNREQ_0X492_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_VEHMNTNTIMERMNREQ_0X492_INFO)
            {
                eventSendCnt[E_IC_VEHMNTNTIMERMNREQ_0X492_INFO] += 1;
                if (eventSendCnt[E_IC_VEHMNTNTIMERMNREQ_0X492_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_VEHMNTNTIMERMNREQ_0X492_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_REMNTNRMNREQ_0X492_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_REMNTNRMNREQ_0X492_INFO)
            {
                eventSendCnt[E_IC_REMNTNRMNREQ_0X492_INFO] += 1;
                if (eventSendCnt[E_IC_REMNTNRMNREQ_0X492_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_REMNTNRMNREQ_0X492_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IC_POWERRESET_0X492_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IC_POWERRESET_0X492_INFO)
            {
                eventSendCnt[E_IC_POWERRESET_0X492_INFO] += 1;
                if (eventSendCnt[E_IC_POWERRESET_0X492_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IC_POWERRESET_0X492_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_IC_SYNC_0X495_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_IC_SYNC_0X495_INFO)
            {
                eventSendCnt[E_IVI_IC_SYNC_0X495_INFO] += 1;
                if (eventSendCnt[E_IVI_IC_SYNC_0X495_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_IC_SYNC_0X495_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SENTRYREQ_0X495_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_SENTRYREQ_0X495_INFO)
            {
                eventSendCnt[E_IVI_SENTRYREQ_0X495_INFO] += 1;
                if (eventSendCnt[E_IVI_SENTRYREQ_0X495_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_SENTRYREQ_0X495_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MODEREQ_0X495_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_MODEREQ_0X495_INFO)
            {
                eventSendCnt[E_IVI_MODEREQ_0X495_INFO] += 1;
                if (eventSendCnt[E_IVI_MODEREQ_0X495_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_MODEREQ_0X495_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RANGEEXTENDERDISENABLE_0X495_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_RANGEEXTENDERDISENABLE_0X495_INFO)
            {
                eventSendCnt[E_IVI_RANGEEXTENDERDISENABLE_0X495_INFO] += 1;
                if (eventSendCnt[E_IVI_RANGEEXTENDERDISENABLE_0X495_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_RANGEEXTENDERDISENABLE_0X495_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HCUCONTROL_0X495_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HCUCONTROL_0X495_INFO)
            {
                eventSendCnt[E_IVI_HCUCONTROL_0X495_INFO] += 1;
                if (eventSendCnt[E_IVI_HCUCONTROL_0X495_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HCUCONTROL_0X495_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DMS_DISTRACTIONICON_0X496_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DMS_DISTRACTIONICON_0X496_INFO)
            {
                eventSendCnt[E_IVI_DMS_DISTRACTIONICON_0X496_INFO] += 1;
                if (eventSendCnt[E_IVI_DMS_DISTRACTIONICON_0X496_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DMS_DISTRACTIONICON_0X496_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DMS_FATIGUEICON_0X496_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DMS_FATIGUEICON_0X496_INFO)
            {
                eventSendCnt[E_IVI_DMS_FATIGUEICON_0X496_INFO] += 1;
                if (eventSendCnt[E_IVI_DMS_FATIGUEICON_0X496_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DMS_FATIGUEICON_0X496_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CAMPMODEREQ_0X496_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_CAMPMODEREQ_0X496_INFO)
            {
                eventSendCnt[E_IVI_CAMPMODEREQ_0X496_INFO] += 1;
                if (eventSendCnt[E_IVI_CAMPMODEREQ_0X496_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_CAMPMODEREQ_0X496_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACDEFROSTMODE_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVACDEFROSTMODE_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_HVACDEFROSTMODE_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVACDEFROSTMODE_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVACDEFROSTMODE_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACONOFFREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVACONOFFREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_HVACONOFFREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVACONOFFREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVACONOFFREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACAUTOMODEREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVACAUTOMODEREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_HVACAUTOMODEREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVACAUTOMODEREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVACAUTOMODEREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACRECIRCMODEREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVACRECIRCMODEREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_HVACRECIRCMODEREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVACRECIRCMODEREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVACRECIRCMODEREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACENERGYSAVINGREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ACENERGYSAVINGREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_ACENERGYSAVINGREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_ACENERGYSAVINGREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ACENERGYSAVINGREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACMODEREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVACMODEREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_HVACMODEREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVACMODEREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVACMODEREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRIVERTEMPCSET_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_DRIVERTEMPCSET_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_DRIVERTEMPCSET_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_DRIVERTEMPCSET_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_DRIVERTEMPCSET_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACBLOWLVREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVACBLOWLVREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_HVACBLOWLVREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVACBLOWLVREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVACBLOWLVREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSENGERTEMPCSET_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_PASSENGERTEMPCSET_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_PASSENGERTEMPCSET_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_PASSENGERTEMPCSET_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_PASSENGERTEMPCSET_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACDUALMODE_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_HVACDUALMODE_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_HVACDUALMODE_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_HVACDUALMODE_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_HVACDUALMODE_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_ACREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_ACREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_ACREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_ACREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SCREENOUTREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_SCREENOUTREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_SCREENOUTREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_SCREENOUTREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_SCREENOUTREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_INTERFACESWITCHREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_INTERFACESWITCHREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_INTERFACESWITCHREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_INTERFACESWITCHREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_INTERFACESWITCHREQ_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANGUAGESET_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_LANGUAGESET_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_LANGUAGESET_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_LANGUAGESET_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_LANGUAGESET_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_INTPUFICATIONSW_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_INTPUFICATIONSW_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_INTPUFICATIONSW_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_INTPUFICATIONSW_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_INTPUFICATIONSW_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NATURALWINDSW_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_NATURALWINDSW_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_NATURALWINDSW_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_NATURALWINDSW_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_NATURALWINDSW_0X3B5_INFO] = 0;
                }
            }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TAKEPHOTOREQ_0X3B5_INFO
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_TAKEPHOTOREQ_0X3B5_INFO)
            {
                eventSendCnt[E_IVI_TAKEPHOTOREQ_0X3B5_INFO] += 1;
                if (eventSendCnt[E_IVI_TAKEPHOTOREQ_0X3B5_INFO] >= SENT_CNT_TO_RESET) {
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                    As_Signal->ComSignalUpdated = FALSE;
                    eventSendCnt[E_IVI_TAKEPHOTOREQ_0X3B5_INFO] = 0;
                }
            }
#endif
        }
        else
        {
#if 0//del by wzc nornal signal need not init
                Com_Misc_WriteSignalDataToPdu(
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,
                    IPdu->ComIPduSignalRef[i]->ComSignalType,
                    As_IPdu->ComIPduDataPtr,
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,
                    IPdu->ComIPduSignalRef[i]->ComBitSize,
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,
                    &signalChanged);
                As_Signal->ComSignalUpdated = FALSE;
#endif
        }
    }
}
void SpecialSignalSend(Com_SignalIdType SignalId, const void *SignalDataPtr, boolean dataChanged)
{
    const ComSignal_type * Signal = GET_Signal(SignalId);
    const Com_As_IPdu_type *As_IPdu = GET_AsIPdu(Signal->ComIPduHandleId);
    Com_As_Signal_type *As_Signal = GET_AsSignal(SignalId);
    uint8_t *comIPduDataPtr = As_IPdu->ComIPduDataPtr;
    if (TRUE == Signal->ComSignalAsUseUpdateBit) {
#ifdef COMCONF_COMSIGNAL_IVI_CURRENTROADTYPE_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CURRENTROADTYPE_0X408_INFO)
        {
            eventSendCnt[E_IVI_CURRENTROADTYPE_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO)
        {
            eventSendCnt[E_IVI_VEHICLEREPAIRMODEREQ_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODESTS_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VEHICLEREPAIRMODESTS_0X408_INFO)
        {
            eventSendCnt[E_IVI_VEHICLEREPAIRMODESTS_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO)
        {
            eventSendCnt[E_IVI_USERGEARFB_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CARSEARCHSTS_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CARSEARCHSTS_0X408_INFO)
        {
            eventSendCnt[E_IVI_CARSEARCHSTS_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CARSEARCHCONTROL_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CARSEARCHCONTROL_0X408_INFO)
        {
            eventSendCnt[E_IVI_CARSEARCHCONTROL_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTORAINWIPERREQ_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AUTORAINWIPERREQ_0X408_INFO)
        {
            eventSendCnt[E_IVI_AUTORAINWIPERREQ_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEPOSITION_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VEHICLEPOSITION_0X408_INFO)
        {
            eventSendCnt[E_IVI_VEHICLEPOSITION_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACCOUNTLOGINSTATUS_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ACCOUNTLOGINSTATUS_0X408_INFO)
        {
            eventSendCnt[E_IVI_ACCOUNTLOGINSTATUS_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANGUAGESET1_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LANGUAGESET1_0X408_INFO)
        {
            eventSendCnt[E_IVI_LANGUAGESET1_0X408_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DANCEONOFFSET_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DANCEONOFFSET_0X096_INFO)
        {
            eventSendCnt[E_IVI_DANCEONOFFSET_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_UNLOCKANIMATSET_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_UNLOCKANIMATSET_0X096_INFO)
        {
            eventSendCnt[E_IVI_UNLOCKANIMATSET_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOCKANIMATSET_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LOCKANIMATSET_0X096_INFO)
        {
            eventSendCnt[E_IVI_LOCKANIMATSET_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FLWINOPENDEGREERE_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FLWINOPENDEGREERE_0X096_INFO)
        {
            eventSendCnt[E_IVI_FLWINOPENDEGREERE_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FRWINOPENDEGREERE_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FRWINOPENDEGREERE_0X096_INFO)
        {
            eventSendCnt[E_IVI_FRWINOPENDEGREERE_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RLWINOPENDEGREERE_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RLWINOPENDEGREERE_0X096_INFO)
        {
            eventSendCnt[E_IVI_RLWINOPENDEGREERE_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RRWINOPENDEGREERE_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RRWINOPENDEGREERE_0X096_INFO)
        {
            eventSendCnt[E_IVI_RRWINOPENDEGREERE_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_BCMLOCKSOUNDSET_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_BCMLOCKSOUNDSET_0X096_INFO)
        {
            eventSendCnt[E_IVI_BCMLOCKSOUNDSET_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOCKCLOSEWINSET_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LOCKCLOSEWINSET_0X096_INFO)
        {
            eventSendCnt[E_IVI_LOCKCLOSEWINSET_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FRONTDEFROSTLEVELSET_0X096_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FRONTDEFROSTLEVELSET_0X096_INFO)
        {
            eventSendCnt[E_IVI_FRONTDEFROSTLEVELSET_0X096_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHILDLOCKCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHILDLOCKCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_CHILDLOCKCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CENTRALLOCKCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CENTRALLOCKCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_CENTRALLOCKCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FUELPORTCAPOPENCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FUELPORTCAPOPENCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_FUELPORTCAPOPENCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOWBEAMONOFFCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LOWBEAMONOFFCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_LOWBEAMONOFFCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_V2VCHRGONOFFSET_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_V2VCHRGONOFFSET_0X075_INFO)
        {
            eventSendCnt[E_IVI_V2VCHRGONOFFSET_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_OBCDSCHRGONOFFSET_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_OBCDSCHRGONOFFSET_0X075_INFO)
        {
            eventSendCnt[E_IVI_OBCDSCHRGONOFFSET_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_REARFOGLAMPONOFFCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ROOFLAMPONOFFCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ROOFLAMPONOFFCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_ROOFLAMPONOFFCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_CHRGPORTCAPOPENCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NORMALHVOFFREQUEST_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NORMALHVOFFREQUEST_0X075_INFO)
        {
            eventSendCnt[E_IVI_NORMALHVOFFREQUEST_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TAILGATECTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TAILGATECTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_TAILGATECTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MIRRORSW_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_MIRRORSW_0X075_INFO)
        {
            eventSendCnt[E_IVI_MIRRORSW_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REARDEFROSTCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_REARDEFROSTCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_REARDEFROSTCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_FOOTLIGHTSWITCHCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO)
        {
            eventSendCnt[E_IVI_MAXFUELCONSUMPTIONSW_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO)
        {
            eventSendCnt[E_IVI_MAXFUELCONSUMPTIONMODESW_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_V2VCHRGOPTCURNTSET_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_V2VCHRGOPTCURNTSET_0X075_INFO)
        {
            eventSendCnt[E_IVI_V2VCHRGOPTCURNTSET_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_APPROACHINGUNLOCKCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AWAYLOCKCTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AWAYLOCKCTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_AWAYLOCKCTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WIPPERMAINTMODECTRL_0X075_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_WIPPERMAINTMODECTRL_0X075_INFO)
        {
            eventSendCnt[E_IVI_WIPPERMAINTMODECTRL_0X075_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NOZZLEHEATINGSW_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NOZZLEHEATINGSW_0X095_INFO)
        {
            eventSendCnt[E_IVI_NOZZLEHEATINGSW_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO)
        {
            eventSendCnt[E_IVI_AMBIENTLIGHTONOFFSET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ONEKEYMODESET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ONEKEYMODESET_0X095_INFO)
        {
            eventSendCnt[E_IVI_ONEKEYMODESET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO)
        {
            eventSendCnt[E_IVI_AMBIENTLIGHTCOLORSET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO)
        {
            eventSendCnt[E_IVI_AMBIENTLIGHTLUMILVSET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LIMITMODESET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LIMITMODESET_0X095_INFO)
        {
            eventSendCnt[E_IVI_LIMITMODESET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DOORTOPSWITCH_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DOORTOPSWITCH_0X095_INFO)
        {
            eventSendCnt[E_IVI_DOORTOPSWITCH_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO)
        {
            eventSendCnt[E_IVI_RVMIRRORAUTOTURNDOWNSET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FOLLOWMEHOMESET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FOLLOWMEHOMESET_0X095_INFO)
        {
            eventSendCnt[E_IVI_FOLLOWMEHOMESET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINLFCTRLRQST_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_WINLFCTRLRQST_0X095_INFO)
        {
            eventSendCnt[E_IVI_WINLFCTRLRQST_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINRFCTRLRQST_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_WINRFCTRLRQST_0X095_INFO)
        {
            eventSendCnt[E_IVI_WINRFCTRLRQST_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINLRCTRLRQST_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_WINLRCTRLRQST_0X095_INFO)
        {
            eventSendCnt[E_IVI_WINLRCTRLRQST_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WINRRCTRLRQST_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_WINRRCTRLRQST_0X095_INFO)
        {
            eventSendCnt[E_IVI_WINRRCTRLRQST_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHILDLOCKRLCTRL_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHILDLOCKRLCTRL_0X095_INFO)
        {
            eventSendCnt[E_IVI_CHILDLOCKRLCTRL_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHILDLOCKRRCTRL_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHILDLOCKRRCTRL_0X095_INFO)
        {
            eventSendCnt[E_IVI_CHILDLOCKRRCTRL_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO)
        {
            eventSendCnt[E_IVI_DRIVEDOORUNLOCKCTRL_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTODRYSET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AUTODRYSET_0X095_INFO)
        {
            eventSendCnt[E_IVI_AUTODRYSET_0X095_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRIPARESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TRIPARESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_TRIPARESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRIPBRESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TRIPBRESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_TRIPBRESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHICLEMODESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VEHICLEMODESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_VEHICLEMODESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REGENMODESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_REGENMODESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_REGENMODESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRAVEMODESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TRAVEMODESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_TRAVEMODESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGECONTROL_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGECONTROL_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGECONTROL_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKINGCHARGEREQ_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PARKINGCHARGEREQ_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_PARKINGCHARGEREQ_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TOWMODESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TOWMODESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_TOWMODESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MAXCHRGSOCSET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_MAXCHRGSOCSET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_MAXCHRGSOCSET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEFORMSET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGEFORMSET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGEFORMSET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REMAINNINGMILMODESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_REMAINNINGMILMODESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_REMAINNINGMILMODESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKINGCHARGEMODESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PARKINGCHARGEMODESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_PARKINGCHARGEMODESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESETVALID_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGESETVALID_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGESETVALID_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGEENDTIMEHOUR_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGEENDTIMEMINUTE_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RESETCURRENTTRIP_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RESETCURRENTTRIP_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_RESETCURRENTTRIP_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_ACFULLCHARGETOWARMSET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEVALID_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGEENDTIMEVALID_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGEENDTIMEVALID_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGESTARTTIMEVALID_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRIVEMODESET_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRIVEMODESET_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_DRIVEMODESET_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO)
        {
            eventSendCnt[E_IVI_EMERGENCYHVOFFREQUESTRESERVED_0X1D5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EXHIBITIONMODECTRL_0X1D5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_EXHIBITIONMODECTRL_0X1D5_INFO)
        {
            eventSendCnt[E_IVI_EXHIBITIONMODECTRL_0X1D5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DCDCAUTOCHARGESET_0X1D5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DCDCAUTOCHARGESET_0X1D5_INFO)
        {
            eventSendCnt[E_IVI_DCDCAUTOCHARGESET_0X1D5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVDOWNREPAIRMODE_0X1D5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVDOWNREPAIRMODE_0X1D5_INFO)
        {
            eventSendCnt[E_IVI_HVDOWNREPAIRMODE_0X1D5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EPSMODESET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_EPSMODESET_0X065_INFO)
        {
            eventSendCnt[E_IVI_EPSMODESET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ESCOFFSW_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ESCOFFSW_0X065_INFO)
        {
            eventSendCnt[E_IVI_ESCOFFSW_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HDCONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HDCONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_HDCONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AEBONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AEBONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_AEBONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_IBMODESET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_IBMODESET_0X065_INFO)
        {
            eventSendCnt[E_IVI_IBMODESET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LCABSDONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LCABSDONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_LCABSDONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RCTAONOFFSETRESERVED_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RCTAONOFFSETRESERVED_0X065_INFO)
        {
            eventSendCnt[E_IVI_RCTAONOFFSETRESERVED_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DOWONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DOWONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_DOWONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_STARTREVSOCSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_STARTREVSOCSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_STARTREVSOCSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HMAONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HMAONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_HMAONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDLIMITONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_SPEEDLIMITONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_SPEEDLIMITONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ASCHEIGHTMODESELECTED_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ASCHEIGHTMODESELECTED_0X065_INFO)
        {
            eventSendCnt[E_IVI_ASCHEIGHTMODESELECTED_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ASCMOVEMODECONTROL_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ASCMOVEMODECONTROL_0X065_INFO)
        {
            eventSendCnt[E_IVI_ASCMOVEMODECONTROL_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANEASSISTFUNCSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LANEASSISTFUNCSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_LANEASSISTFUNCSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LASWARNINGMODESELECTION_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LASWARNINGMODESELECTION_0X065_INFO)
        {
            eventSendCnt[E_IVI_LASWARNINGMODESELECTION_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_TRAILERMODEREQ_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_TRAILERMODEREQ_0X065_INFO)
        {
            eventSendCnt[E_TRAILERMODEREQ_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RCTBONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RCTBONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_RCTBONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ELKONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ELKONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_ELKONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVHONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVHONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_AVHONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PCWONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PCWONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_PCWONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TJAFUNCSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TJAFUNCSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_TJAFUNCSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTODODGEONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AUTODODGEONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_AUTODODGEONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRAILERMODEONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TRAILERMODEONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_TRAILERMODEONOFFSET_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO)
        {
            eventSendCnt[E_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAONOFFREQ_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_APAONOFFREQ_0X065_INFO)
        {
            eventSendCnt[E_IVI_APAONOFFREQ_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAFUNCSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_APAFUNCSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_APAFUNCSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RPAFUNCSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RPAFUNCSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_RPAFUNCSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APADRVSPEEDSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_APADRVSPEEDSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_APADRVSPEEDSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMVIEWSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMVIEWSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_AVMVIEWSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMCARBODYTRANSPSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMCARBODYTRANSPSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_AVMCARBODYTRANSPSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_AVMTRIGBYTURNNINGSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_AVMTRAJECTORYDISPLAYSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMTRIGBYSENSORSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMTRIGBYSENSORSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_AVMTRIGBYSENSORSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PDCSOUNDSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PDCSOUNDSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_PDCSOUNDSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PDCMUTEREQ_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PDCMUTEREQ_0X066_INFO)
        {
            eventSendCnt[E_IVI_PDCMUTEREQ_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LAEB_SW_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LAEB_SW_0X066_INFO)
        {
            eventSendCnt[E_IVI_LAEB_SW_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FRONTPDCALARMSET_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FRONTPDCALARMSET_0X066_INFO)
        {
            eventSendCnt[E_IVI_FRONTPDCALARMSET_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAPARKINTYPESEL_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_APAPARKINTYPESEL_0X066_INFO)
        {
            eventSendCnt[E_IVI_APAPARKINTYPESEL_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKSCENERECONSW_0X066_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PARKSCENERECONSW_0X066_INFO)
        {
            eventSendCnt[E_IVI_PARKSCENERECONSW_0X066_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICAONOFFSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ICAONOFFSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_ICAONOFFSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANECHANGESTALY_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LANECHANGESTALY_0X067_INFO)
        {
            eventSendCnt[E_IVI_LANECHANGESTALY_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AUTOLANECHANGESET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AUTOLANECHANGESET_0X067_INFO)
        {
            eventSendCnt[E_IVI_AUTOLANECHANGESET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RAMPFOLLOWCARSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RAMPFOLLOWCARSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_RAMPFOLLOWCARSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NCAONOFFSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NCAONOFFSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_NCAONOFFSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDLIMITSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_SPEEDLIMITSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_SPEEDLIMITSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VOICEBROADCASTSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VOICEBROADCASTSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_VOICEBROADCASTSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDPROPORTIONSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_SPEEDPROPORTIONSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_SPEEDPROPORTIONSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SPEEDVALUESET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_SPEEDVALUESET_0X067_INFO)
        {
            eventSendCnt[E_IVI_SPEEDVALUESET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANECHANGSTYLESET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LANECHANGSTYLESET_0X067_INFO)
        {
            eventSendCnt[E_IVI_LANECHANGSTYLESET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TARGETSPEEDOFFSETSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TARGETSPEEDOFFSETSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_TARGETSPEEDOFFSETSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NCAFUNCSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NCAFUNCSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_NCAFUNCSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICAFUNCSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ICAFUNCSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_ICAFUNCSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ALCFUNCSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ALCFUNCSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_ALCFUNCSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANECHANGECONFIRMSET_0X067_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LANECHANGECONFIRMSET_0X067_INFO)
        {
            eventSendCnt[E_IVI_LANECHANGECONFIRMSET_0X067_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SLAFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_SLAFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_SLAFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_TRAFFICLIGHTREMFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANEASSISTTYPESET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LANEASSISTTYPESET_0X069_INFO)
        {
            eventSendCnt[E_IVI_LANEASSISTTYPESET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LASWARNMODESET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LASWARNMODESET_0X069_INFO)
        {
            eventSendCnt[E_IVI_LASWARNMODESET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ELKFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ELKFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_ELKFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FCWFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FCWFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_FCWFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AEBFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AEBFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_AEBFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LAEBFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LAEBFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_LAEBFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RCWFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RCWFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_RCWFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_BSDLCAFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_BSDLCAFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_BSDLCAFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DOWFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DOWFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_DOWFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_STARTREMFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_STARTREMFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_STARTREMFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HMAFUNCSET_0X069_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HMAFUNCSET_0X069_INFO)
        {
            eventSendCnt[E_IVI_HMAFUNCSET_0X069_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_X_0X068_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_X_0X068_INFO)
        {
            eventSendCnt[E_IVI_AVMROTATIONANGLE_X_0X068_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_Y_0X068_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMROTATIONANGLE_Y_0X068_INFO)
        {
            eventSendCnt[E_IVI_AVMROTATIONANGLE_Y_0X068_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RPAAPASWITCH_0X068_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RPAAPASWITCH_0X068_INFO)
        {
            eventSendCnt[E_IVI_RPAAPASWITCH_0X068_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_APAFUNCREQ_0X068_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_APAFUNCREQ_0X068_INFO)
        {
            eventSendCnt[E_IVI_APAFUNCREQ_0X068_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AVMVIEWSELECT_0X068_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AVMVIEWSELECT_0X068_INFO)
        {
            eventSendCnt[E_IVI_AVMVIEWSELECT_0X068_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO)
        {
            eventSendCnt[E_IVI_PARKSPCGRDLOCKCFIM_0X068_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_STERRINGWHEELHEATSW_0X105_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_STERRINGWHEELHEATSW_0X105_INFO)
        {
            eventSendCnt[E_IVI_STERRINGWHEELHEATSW_0X105_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATROUTESET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRSEATROUTESET_0X098_INFO)
        {
            eventSendCnt[E_IVI_DRSEATROUTESET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATBACKRESTSET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRSEATBACKRESTSET_0X098_INFO)
        {
            eventSendCnt[E_IVI_DRSEATBACKRESTSET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONSET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONSET_0X098_INFO)
        {
            eventSendCnt[E_IVI_DRSEATCUSHIONSET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONANGLESET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRSEATCUSHIONANGLESET_0X098_INFO)
        {
            eventSendCnt[E_IVI_DRSEATCUSHIONANGLESET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LMIRRORUDSET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LMIRRORUDSET_0X098_INFO)
        {
            eventSendCnt[E_IVI_LMIRRORUDSET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LMIRRORLRSET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LMIRRORLRSET_0X098_INFO)
        {
            eventSendCnt[E_IVI_LMIRRORLRSET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RMIRRORUDSET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RMIRRORUDSET_0X098_INFO)
        {
            eventSendCnt[E_IVI_RMIRRORUDSET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RMIRRORLRSET_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RMIRRORLRSET_0X098_INFO)
        {
            eventSendCnt[E_IVI_RMIRRORLRSET_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DSMCHARGECTRL_0X098_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DSMCHARGECTRL_0X098_INFO)
        {
            eventSendCnt[E_IVI_DSMCHARGECTRL_0X098_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATROUTESET_0X093_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATROUTESET_0X093_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATROUTESET_0X093_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATBACKRESTSET_0X093_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATBACKRESTSET_0X093_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATBACKRESTSET_0X093_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONSET_0X093_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONSET_0X093_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATCUSHIONSET_0X093_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATCUSHIONANGLESET_0X093_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_DARKILLUMILEVELSETRESERVED_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TRIPSWITCHRESERVED_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TRIPSWITCHRESERVED_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_TRIPSWITCHRESERVED_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_REARSEATBELTVOICEWARNINGSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HUDONOFFSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HUDONOFFSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_HUDONOFFSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_THEMESETRESERVED_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_THEMESETRESERVED_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_THEMESETRESERVED_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_WCMONOFFSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_WCMONOFFSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_WCMONOFFSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PDCONOFFSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PDCONOFFSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_PDCONOFFSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_ICTHEMEGANGEDSETRESERVED_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_FACTORYRESETCOMMAND_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_FACTORYRESETCOMMAND_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_FACTORYRESETCOMMAND_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ICILLUMILEVELSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ICILLUMILEVELSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_ICILLUMILEVELSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LAEB_SW_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LAEB_SW_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_LAEB_SW_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VSPONOFFSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VSPONOFFSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_VSPONOFFSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_VSP_SOUNDCONFIGURE_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_UNLOCKSOUNDSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_UNLOCKSOUNDSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_UNLOCKSOUNDSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LOCKSOUNDSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LOCKSOUNDSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_LOCKSOUNDSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ISAONOFFSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ISAONOFFSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_ISAONOFFSET_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_ILLUMILEVELSETRESERVED_0X0C5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHMNTNMILECLEA_0X0C6_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VEHMNTNMILECLEA_0X0C6_INFO)
        {
            eventSendCnt[E_IVI_VEHMNTNMILECLEA_0X0C6_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_OILMNTNMILECLEA_0X0C6_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_OILMNTNMILECLEA_0X0C6_INFO)
        {
            eventSendCnt[E_IVI_OILMNTNMILECLEA_0X0C6_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_OILFILMNTNMILECLEA_0X0C6_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_OILFILMNTNMILECLEA_0X0C6_INFO)
        {
            eventSendCnt[E_IVI_OILFILMNTNMILECLEA_0X0C6_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO)
        {
            eventSendCnt[E_IVI_AIRFILMNTNMILECLEA_0X0C6_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_VEHMNTNTIMECLEA_0X0C6_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_VEHMNTNTIMECLEA_0X0C6_INFO)
        {
            eventSendCnt[E_IVI_VEHMNTNTIMECLEA_0X0C6_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_IVITHEMESET1_0X3D2_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_IVITHEMESET1_0X3D2_INFO)
        {
            eventSendCnt[E_IVI_IVITHEMESET1_0X3D2_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO)
        {
            eventSendCnt[E_IVI_TAKEINVIDEOPOSREQ_0X3D2_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ALARMLISTREQUEST_0X3D2_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ALARMLISTREQUEST_0X3D2_INFO)
        {
            eventSendCnt[E_IVI_ALARMLISTREQUEST_0X3D2_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_EASYENTRYSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_EASYENTRYSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_EASYENTRYSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATHEATLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRSEATHEATLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_DRSEATHEATLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATVENTLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRSEATVENTLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_DRSEATVENTLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATVENTLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRSEATMASSLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRSEATMASSLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_DRSEATMASSLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATMASSLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_MIRRORAUTOFOLDUNFOLDSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RLSEATHEATLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RLSEATHEATLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_RLSEATHEATLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_DSMSETMEMORYREQRESERVED_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRMASSGINTENSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRMASSGINTENSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_DRMASSGINTENSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PSGMASSGINTENSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PSGMASSGINTENSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_PSGMASSGINTENSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DSMMEMORYREQ_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DSMMEMORYREQ_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_DSMMEMORYREQ_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RRSEATHEATLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RRSEATHEATLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_RRSEATHEATLEVELSET_0X0F5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO)
        {
            eventSendCnt[E_IVI_NAVIGCHRGPOSTREQ_0X33E_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_SONGFAULTNUM_0X052_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_SONGFAULTNUM_0X052_INFO)
        {
            eventSendCnt[E_IC_SONGFAULTNUM_0X052_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_SONGWARNINGSTS_0X052_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_SONGWARNINGSTS_0X052_INFO)
        {
            eventSendCnt[E_IC_SONGWARNINGSTS_0X052_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_HUDILLUMILVSET_0X3F2_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_HUDILLUMILVSET_0X3F2_INFO)
        {
            eventSendCnt[E_IC_HUDILLUMILVSET_0X3F2_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO)
        {
            eventSendCnt[E_IVI_PASSAIRBSUPPRESSIONSTSET_0X3F8_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_ALARMLISTFLAG_0X571_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_ALARMLISTFLAG_0X571_INFO)
        {
            eventSendCnt[E_IC_ALARMLISTFLAG_0X571_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS_0X571_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS_0X571_INFO)
        {
            eventSendCnt[E_IC_WARNINGSTATUS_0X571_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS2_0X571_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS2_0X571_INFO)
        {
            eventSendCnt[E_IC_WARNINGSTATUS2_0X571_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS3_0X571_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS3_0X571_INFO)
        {
            eventSendCnt[E_IC_WARNINGSTATUS3_0X571_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS4_0X571_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS4_0X571_INFO)
        {
            eventSendCnt[E_IC_WARNINGSTATUS4_0X571_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS5_0X571_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS5_0X571_INFO)
        {
            eventSendCnt[E_IC_WARNINGSTATUS5_0X571_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_WARNINGSTATUS6_0X571_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_WARNINGSTATUS6_0X571_INFO)
        {
            eventSendCnt[E_IC_WARNINGSTATUS6_0X571_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_DMS_DISTRACTIONICONFB_0X570_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_DMS_DISTRACTIONICONFB_0X570_INFO)
        {
            eventSendCnt[E_IC_DMS_DISTRACTIONICONFB_0X570_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_DMS_FATIGUEICONFB_0X570_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_DMS_FATIGUEICONFB_0X570_INFO)
        {
            eventSendCnt[E_IC_DMS_FATIGUEICONFB_0X570_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_VEHMNTNMILERMNREQ_0X492_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_VEHMNTNMILERMNREQ_0X492_INFO)
        {
            eventSendCnt[E_IC_VEHMNTNMILERMNREQ_0X492_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_VEHMNTNTIMERMNREQ_0X492_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_VEHMNTNTIMERMNREQ_0X492_INFO)
        {
            eventSendCnt[E_IC_VEHMNTNTIMERMNREQ_0X492_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_REMNTNRMNREQ_0X492_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_REMNTNRMNREQ_0X492_INFO)
        {
            eventSendCnt[E_IC_REMNTNRMNREQ_0X492_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IC_POWERRESET_0X492_INFO
        if(SignalId == COMCONF_COMSIGNAL_IC_POWERRESET_0X492_INFO)
        {
            eventSendCnt[E_IC_POWERRESET_0X492_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_IC_SYNC_0X495_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_IC_SYNC_0X495_INFO)
        {
            eventSendCnt[E_IVI_IC_SYNC_0X495_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SENTRYREQ_0X495_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_SENTRYREQ_0X495_INFO)
        {
            eventSendCnt[E_IVI_SENTRYREQ_0X495_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_MODEREQ_0X495_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_MODEREQ_0X495_INFO)
        {
            eventSendCnt[E_IVI_MODEREQ_0X495_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_RANGEEXTENDERDISENABLE_0X495_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_RANGEEXTENDERDISENABLE_0X495_INFO)
        {
            eventSendCnt[E_IVI_RANGEEXTENDERDISENABLE_0X495_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HCUCONTROL_0X495_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HCUCONTROL_0X495_INFO)
        {
            eventSendCnt[E_IVI_HCUCONTROL_0X495_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DMS_DISTRACTIONICON_0X496_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DMS_DISTRACTIONICON_0X496_INFO)
        {
            eventSendCnt[E_IVI_DMS_DISTRACTIONICON_0X496_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DMS_FATIGUEICON_0X496_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DMS_FATIGUEICON_0X496_INFO)
        {
            eventSendCnt[E_IVI_DMS_FATIGUEICON_0X496_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CAMPMODEREQ_0X496_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CAMPMODEREQ_0X496_INFO)
        {
            eventSendCnt[E_IVI_CAMPMODEREQ_0X496_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACDEFROSTMODE_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACDEFROSTMODE_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACDEFROSTMODE_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACONOFFREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACONOFFREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACONOFFREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACAUTOMODEREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACAUTOMODEREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACAUTOMODEREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACRECIRCMODEREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACRECIRCMODEREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACRECIRCMODEREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACENERGYSAVINGREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ACENERGYSAVINGREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_ACENERGYSAVINGREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACMODEREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACMODEREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACMODEREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_DRIVERTEMPCSET_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_DRIVERTEMPCSET_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_DRIVERTEMPCSET_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACBLOWLVREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACBLOWLVREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACBLOWLVREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_PASSENGERTEMPCSET_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSENGERTEMPCSET_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_PASSENGERTEMPCSET_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_HVACDUALMODE_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACDUALMODE_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACDUALMODE_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_ACREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ACREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_ACREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_NAVIGATIORECIRCREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_SCREENOUTREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_SCREENOUTREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_SCREENOUTREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_INTERFACESWITCHREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_INTERFACESWITCHREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_INTERFACESWITCHREQ_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_LANGUAGESET_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_LANGUAGESET_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_LANGUAGESET_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_INTPUFICATIONSW_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_INTPUFICATIONSW_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_INTPUFICATIONSW_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_NATURALWINDSW_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NATURALWINDSW_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_NATURALWINDSW_0X3B5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_TAKEPHOTOREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_TAKEPHOTOREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_TAKEPHOTOREQ_0X3B5_INFO] = 0;
        }
#endif
    }
    else
    {
        Com_Misc_WriteSignalDataToPdu(
            (const uint8_t *)SignalDataPtr,
            Signal->ComSignalType,
            comIPduDataPtr,
            Signal->ComBitPosition,
            Signal->ComBitSize,
            Signal->ComSignalEndianess,
            &dataChanged);
    }
    if (TRUE == Signal->ComSignalAsUseUpdateBit) {
        As_Signal->ComSignalUpdated = TRUE;
    }
}
