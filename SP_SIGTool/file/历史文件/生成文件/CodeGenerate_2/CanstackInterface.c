
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
#ifdef COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO
            if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO)
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
#ifdef COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_USERGEARFB_0X408_INFO)
        {
            eventSendCnt[E_IVI_USERGEARFB_0X408_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_NOZZLEHEATINGSW_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_NOZZLEHEATINGSW_0X095_INFO)
        {
            eventSendCnt[E_IVI_NOZZLEHEATINGSW_0X095_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_AUTODRYSET_0X095_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_AUTODRYSET_0X095_INFO)
        {
            eventSendCnt[E_IVI_AUTODRYSET_0X095_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGESTARTTIMEHOUR_0X0A5_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO)
        {
            eventSendCnt[E_IVI_CHARGESTARTTIMEMINUTE_0X0A5_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_HMAONOFFSET_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HMAONOFFSET_0X065_INFO)
        {
            eventSendCnt[E_IVI_HMAONOFFSET_0X065_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO)
        {
            eventSendCnt[E_IVI_ESC_EPBBUTTONRELEASE_0X065_INFO] = 0;
        }
#endif
#ifdef COMCONF_COMSIGNAL_IVI_STERRINGWHEELHEATSW_0X105_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_STERRINGWHEELHEATSW_0X105_INFO)
        {
            eventSendCnt[E_IVI_STERRINGWHEELHEATSW_0X105_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_PDCONOFFSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PDCONOFFSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_PDCONOFFSET_0X0C5_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_ISAONOFFSET_0X0C5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_ISAONOFFSET_0X0C5_INFO)
        {
            eventSendCnt[E_IVI_ISAONOFFSET_0X0C5_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO)
        {
            eventSendCnt[E_IVI_PASSSEATHEATLEVELSET_0X0F5_INFO] = 0;
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
#ifdef COMCONF_COMSIGNAL_IVI_HVACONOFFREQ_0X3B5_INFO
        if(SignalId == COMCONF_COMSIGNAL_IVI_HVACONOFFREQ_0X3B5_INFO)
        {
            eventSendCnt[E_IVI_HVACONOFFREQ_0X3B5_INFO] = 0;
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
