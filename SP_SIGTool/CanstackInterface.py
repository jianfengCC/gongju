##################################################
#  tool version  #   Author     #    date        #
##################################################
#  V.0.01        # liu.jiankang #  2023.8.24     #
##################################################
import parser_dbc
import parser_txt
import tool_config
head_text = '''
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
'''

def make_func_SpecialSignalProcessing(fp):
    text = '''void SpecialSignalProcessing(PduIdType PduId)
{
    boolean signalChanged = FALSE;
    const ComIPdu_type *IPdu = GET_IPdu(PduId);


    /*Changed by Limh20190724 for "ClearOdometerReq" logic and other event signal processing  where valid values are cleared once sent*/
    for (uint16_t i = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[i] != NULL); i++) {
        Com_As_Signal_type *As_Signal = GET_AsSignal(IPdu->ComIPduSignalRef[i]->ComHandleId);
        const Com_As_IPdu_type *As_IPdu = GET_AsIPdu(IPdu->ComIPduSignalRef[i]->ComIPduHandleId);
        if ((TRUE == IPdu->ComIPduSignalRef[i]->ComSignalAsUseUpdateBit)&&(As_Signal->ComSignalUpdated == TRUE)) {
            /*lint -e{9016} Array indexing couldn't be implemented, as parameters are of different data types */
            //CLEARBIT(As_IPdu->ComIPduDataPtr, IPdu->ComIPduSignalRef[i]->ComUpdateBitPosition);'''
    sp_data = parser_txt.get_txt()
    msg_list = parser_dbc.get_tx_msg_list()
    counter = 0
    for msg in msg_list:
        for sig in msg.signals:
            if sig.name.upper() in sp_data:
                counter  = counter + 1
                msg_num = str(hex(msg.frame_id).upper()).split('X')[1]
                while(len(msg_num) < 3):
                    msg_num = '0' + msg_num
                msg_id = '0X'+ msg_num
                text = text + '\n\
#ifdef COMCONF_COMSIGNAL_'+ sig.name.upper() +'_'+ msg_id +'_INFO\n'
                if counter == 1:
                    text = text + '\
            if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_'+ sig.name.upper() +'_'+ msg_id +'_INFO)\n'
                else:
                    text = text + '\
            else if(IPdu->ComIPduSignalRef[i]->ComHandleId == COMCONF_COMSIGNAL_'+ sig.name.upper() +'_'+ msg_id +'_INFO)\n'
                text = text + '\
            {\n\
                eventSendCnt[E_'+ sig.name.upper() +'_'+ msg_id +'_INFO] += 1;\n\
                if (eventSendCnt[E_'+ sig.name.upper() +'_'+ msg_id +'_INFO] >= SENT_CNT_TO_RESET) {\n\
                Com_Misc_WriteSignalDataToPdu(\n\
                    IPdu->ComIPduSignalRef[i]->ComSignalInitValue,\n\
                    IPdu->ComIPduSignalRef[i]->ComSignalType,\n\
                    As_IPdu->ComIPduDataPtr,\n\
                    IPdu->ComIPduSignalRef[i]->ComBitPosition,\n\
                    IPdu->ComIPduSignalRef[i]->ComBitSize,\n\
                    IPdu->ComIPduSignalRef[i]->ComSignalEndianess,\n\
                    &signalChanged);\n\
                    As_Signal->ComSignalUpdated = FALSE;\n\
                    eventSendCnt[E_'+ sig.name.upper() +'_'+ msg_id +'_INFO] = 0;\n\
                }\n\
            }\n\
#endif'
    text = text + '''
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
}'''
    fp.write(text)

def make_func_SpecialSignalSend(fp):
    text = '''
void SpecialSignalSend(Com_SignalIdType SignalId, const void *SignalDataPtr, boolean dataChanged)
{
    const ComSignal_type * Signal = GET_Signal(SignalId);
    const Com_As_IPdu_type *As_IPdu = GET_AsIPdu(Signal->ComIPduHandleId);
    Com_As_Signal_type *As_Signal = GET_AsSignal(SignalId);
    uint8_t *comIPduDataPtr = As_IPdu->ComIPduDataPtr;
    if (TRUE == Signal->ComSignalAsUseUpdateBit) {'''
    sp_data = parser_txt.get_txt()
    msg_list = parser_dbc.get_tx_msg_list()
    counter = 0
    for msg in msg_list:
        for sig in msg.signals:
            if sig.name.upper() in sp_data:
                msg_num = str(hex(msg.frame_id).upper()).split('X')[1]
                while(len(msg_num) < 3):
                    msg_num = '0' + msg_num
                msg_id = '0X'+ msg_num
                text = text + '\n\
#ifdef COMCONF_COMSIGNAL_'+ sig.name.upper() +'_'+ msg_id +'_INFO\n\
        if(SignalId == COMCONF_COMSIGNAL_'+ sig.name.upper() +'_'+ msg_id +'_INFO)\n\
        {\n\
            eventSendCnt[E_'+ sig.name.upper() +'_'+ msg_id +'_INFO] = 0;\n\
        }\n\
#endif'
    text = text + '''
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
'''
    fp.write(text)
def make_file():
    # print('='*16 + ' Start make CanstackInterface.c ' + '='*16)
    write_f = open((tool_config.file_path+'CanstackInterface.c'), "w",encoding= 'UTF-8')
    write_f.write(head_text)
    print('Wait...')
    make_func_SpecialSignalProcessing(write_f)

    make_func_SpecialSignalSend(write_f)

    print('='*16 + ' Success make CanstackInterface.c ' + '='*16)