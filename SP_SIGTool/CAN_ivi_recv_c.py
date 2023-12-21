import cantools
import os
import glob
import sys
import tool_config
import parser_txt
import parser_dbc
def make_file():
# 获取当前目录
    current_dir = os.getcwd()
    sp_data = parser_txt.get_txt()
    msg_list = parser_dbc.get_tx_msg_list()
    # 指定格式的文件名
    file_pattern = "*.dbc"

    # 遍历当前目录下的所有文件，获取指定格式的文件名
    for file_name in glob.glob(os.path.join(current_dir, file_pattern)):
        print(file_name)

    # Load DBC file
    db = cantools.database.load_file(tool_config.dbc_name)
    if len(sys.argv) > 3:
        db1 = cantools.database.load_file(sys.argv[3])

    filename = "ivi_recv.c"

    with open(tool_config.ivi_file_path+filename, "w") as f:
        text = """/**
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
#define READFLASHOK     1"""
        f.write(text)
        f.write("\n")

        for msg in msg_list:
            for sig in msg.signals:
                if sig.name.upper() in sp_data:
                    hex_str = hex(msg.frame_id)[2:]
                    # 使用zfill()方法在左侧填充0，使字符串长度为3
                    hex_str_padded = hex_str.zfill(3)
                    sig_type = parser_dbc.get_date_type(parser_dbc.get_sig_type(sig.name))
                    f.write('extern const '+ sig_type +' Com_SignalInitValue_'+sig.name+'_0x'+hex_str_padded.upper()+'_INFO_Message;\n')

        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers

            if message_sender.startswith(tool_config.senders) :
                if message_name.startswith('NM') :
                    print(f"{message.name} 不写入")
                else :
                    f.write("void setSignal_"+message_name+"(uint8_t *sigbuff, uint8_t len);\n")

        if len(sys.argv) > 3:
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers

                if message_sender.startswith(tool_config.senders) :
                    if message_name.startswith('NM') :
                        print(f"{message.name} 不写入")
                    else :
                        f.write("void setSignal_"+message_name+"_pri(uint8_t *sigbuff, uint8_t len);\n")
        f.write('void setIVISignal_IVI_infoSet_ivi_ICIllumiLevelSet(uint8_t par);')

        txt = """
static struct package_0x0E6_st_IVI_EPA_VOL p_IVI_EPA_VOL_bk = {0};
static struct package_0x0E7_st_IVI_EPA_ADAS_VOL p_IVI_EPA_ADAS_VOL_bk = {0};
static struct package_0x0E9_st_IVI_EPA_CONTROL p_IVI_EPA_CONTROL_bk = {0};
static struct package_0x0EA_st_IVI_EPA_GEQ_GAIN p_IVI_EPA_GEQ_GAIN_bk = {0};
uint8_t invm_data_temp[E_APP_DATA_TYPE_Max] = {0};
static uint8_t s_u8FirstPowerOnFlag = 0;

static uint8_t s_invm_data[E_APP_DATA_TYPE_Max] = {0};
const uint8_t audio_par_default[E_APP_DATA_TYPE_Max] = {
                        0x23, 0x19, 0x23, 0x23, 0x23, 0x23, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, \\
                                                                    // len 17, p_IVI_EPA_VOL_st
                        0x0, 0x0, 0x0, 0x19, \\
                                                                    // len 4, p_IVI_EPA_ADAS_VOL_st
                        0x7, 0x7, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0, \\
                                                                    // len 13, p_IVI_EPA_CONTROL_st
                        0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, \\
                                                                    // len 7, p_IVI_EPA_GEQ_GAIN_st
                        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // not use
};

void Interaction_Init() {
    uint8_t ret = 0;
    ret = NvmReadDataFlash(STOR_DATABLK_SIGNALS, (uint8_t *)&s_invm_data, sizeof(s_invm_data));
    if (ret != READFLASHOK) {
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"checksum error / NVM empty :\\r\\n");
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
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,"first power on send fail :0x%x\\r\\n", bResult);
    }
}
"""
        f.write(txt)

        text = """
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
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"can_id error, can_id:0x%x\\r\\n", can_id);
            break;
        }
        if (0 == len) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"len == 0\\r\\n");
            break;
        }
        if (startpos + len + 3 > msg.len) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"len error, can_id:0x%x, startpos:%d, len:%d, msg.len:%d\\r\\n", can_id, startpos, len+3, msg.len);
            break;
        }
        if (status != RTE_SIG_OK) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"status not ok, can_id:0x%x, status:%d\\r\\n", can_id, status);
            startpos = startpos + len + 3;
            continue;
        }
        if (len - 1 > IVI_SIG_BUF_MAX) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT,"sig len over long:%d\\r\\n", len - 1);
            startpos = startpos + len + 3;
            continue;
        }
        /* set signal */
        uint8_t sigbuff[IVI_SIG_BUF_MAX];
        memcpy(sigbuff, &tempBuffer[startpos + 4], len - 1);
        if (IVI_SIG_PUB == type) {
            switch (can_id) {"""
        f.write(text)
        f.write("\n")

        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers

            if message_sender.startswith(tool_config.senders) :
                # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                hex_str = hex(message.frame_id)[2:]
                # 使用zfill()方法在左侧填充0，使字符串长度为3
                hex_str_padded = hex_str.zfill(3)

                if message_name.startswith('NM') :
                    print(f"{message.name} 不写入")
                else :
                    f.write("            case 0x"+hex_str_padded.upper()+":\n")
                    f.write("                setSignal_"+message_name+"(sigbuff, len - 1);\n")
                    f.write("                break;\n")
        text = """            default:
                break;
            }
        } else if (IVI_SIG_PRI == type) {
            switch (can_id) {"""
        f.write(text)
        f.write("\n")
        #私有CAN
        if len(sys.argv) > 3:
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers

                if message_sender.startswith(tool_config.senders) :
                    # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                    hex_str = hex(message.frame_id)[2:]
                    # 使用zfill()方法在左侧填充0，使字符串长度为3
                    hex_str_padded = hex_str.zfill(3)

                    if message_name.startswith('NM') :
                        print(f"{message.name} 不写入")
                    else :
                        f.write("            case 0x"+hex_str_padded.upper()+":\n")
                        f.write("                setSignal_"+message_name+"(sigbuff, len - 1);\n")
                        f.write("                break;\n")
        text = """            default:
                break;
            }
        }
        startpos = startpos + len + 3;
    }
    if (0 != memcmp(s_invm_data, invm_data_temp, E_APP_DATA_TYPE_Max)) {
        uint8_t writeRes = 0;
        memcpy(s_invm_data, invm_data_temp, E_APP_DATA_TYPE_Max);
        SystemApiLogPrintf(LOG_ERROR_OUTPUT,">>> Update interaction nvm , checksum = %d\\r\\n", s_invm_data[E_APP_CheckSumNum]);
        writeRes = NvmWriteDataFlash(STOR_DATABLK_SIGNALS, s_invm_data);
        if (DATAFLASH_WRITE_NG == writeRes) {
            SystemApiLogPrintf(LOG_ERROR_OUTPUT, "Failed to save SIGNALS \\r\\n");
        }
    }
}"""
        f.write(text)

        f.write("\n")
        f.write("\n")

        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers

            if message_sender.startswith(tool_config.senders) :
                # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                hex_str = hex(message.frame_id)[2:]
                # 使用zfill()方法在左侧填充0，使字符串长度为3
                hex_str_padded = hex_str.zfill(3)

                if message_name.startswith('NM'):
                    print(f"{message.name} 不写入")
                else :
                    str = "p_"+message_name+"_st"
                    f.write("void setSignal_"+message_name+"(uint8_t *sigbuff, uint8_t len)\n")
                    f.write("{\n")
                    f.write("    uint8_t bResult = RTE_SIG_OK;\n")

                    for signal in message.signals:
                        length = signal.length
                        if length <= 8 :
                            nop = 0
                        elif length <= 16 :
                            f.write("    uint16_t u16"+signal.name+" = 0;\n")
                        elif length <= 32 :
                            f.write("    uint32_t u32"+signal.name+" = 0;\n")
                        else :
                            f.write("    uint64_t u64"+signal.name+" = 0;\n")

                    f.write("    if ("+str+".data_len - 1 != len) {\n")
                    f.write("        SystemApiLogPrintf(LOG_ERROR_OUTPUT,\"sig len error:%d\\r\\n\", len);\n")
                    f.write("        return;\n")
                    f.write("    }\n")
                    f.write("    memcpy(((uint8_t*)&"+str+") + 4, sigbuff, len);\n")

                    f.write("\n")

                    for signal in message.signals:
                        length = signal.length
                        if signal.name.upper() in sp_data:
                            if length <= 8 :
                                f.write("    if("+str+"."+signal.name+" != Com_SignalInitValue_"+signal.name+'_0x'+hex_str_padded.upper()+"_INFO_Message){\n")
                                f.write("        bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&"+str+"."+signal.name+");\n")
                                f.write("    }\n")
                            elif length <= 16 :
                                f.write("    u16"+signal.name+" = (((uint16_t)"+str+"."+signal.name+"_H) << 8) + \n")
                                f.write("                                ((uint16_t)"+str+"."+signal.name+"_L);\n")
                                f.write("    if("+str+"."+signal.name+" != Com_SignalInitValue_"+signal.name+'_0x'+hex_str_padded.upper()+"_INFO_Message){\n")
                                f.write("       bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&u16"+signal.name+");\n")
                                f.write("    }\n")

                            elif length <= 32 :
                                f.write("    u32"+signal.name+" = (((uint32_t)"+str+"."+signal.name+"_H) << 24) + \n")
                                f.write("                                (((uint32_t)"+str+"."+signal.name+"_MH) << 16) + \n")
                                f.write("                                (((uint32_t)"+str+"."+signal.name+"_ML) << 8) + \n")
                                f.write("                                ((uint32_t)"+str+"."+signal.name+"_L);\n")
                                f.write("    if("+str+"."+signal.name+" != Com_SignalInitValue_"+signal.name+'_0x'+hex_str_padded.upper()+"_INFO_Message){\n")
                                f.write("       bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&u32"+signal.name+");\n")
                                f.write("    }\n")
                            else :
                                f.write("    u64"+signal.name+" = (((uint64_t)"+str+"."+signal.name+"_8) << 56) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_7) << 48) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_6) << 40) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_5) << 32) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_4) << 24) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_3) << 16) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_2) << 8) + \n")
                                f.write("                                ((uint64_t)"+str+"."+signal.name+"_1);\n")
                                f.write("    if("+str+"."+signal.name+" != Com_SignalInitValue_"+signal.name+'_0x'+hex_str_padded.upper()+"_INFO_Message){\n")
                                f.write("       bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&u64"+signal.name+");\n")
                                f.write("    }\n")
                            pass
                        else:
                            if length <= 8 :
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&"+str+"."+signal.name+");\n")
                            elif length <= 16 :
                                f.write("    u16"+signal.name+" = (((uint16_t)"+str+"."+signal.name+"_H) << 8) + \n")
                                f.write("                                ((uint16_t)"+str+"."+signal.name+"_L);\n")
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&u16"+signal.name+");\n")

                            elif length <= 32 :
                                f.write("    u32"+signal.name+" = (((uint32_t)"+str+"."+signal.name+"_H) << 24) + \n")
                                f.write("                                (((uint32_t)"+str+"."+signal.name+"_MH) << 16) + \n")
                                f.write("                                (((uint32_t)"+str+"."+signal.name+"_ML) << 8) + \n")
                                f.write("                                ((uint32_t)"+str+"."+signal.name+"_L);\n")
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&u32"+signal.name+");\n")
                            else :
                                f.write("    u64"+signal.name+" = (((uint64_t)"+str+"."+signal.name+"_8) << 56) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_7) << 48) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_6) << 40) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_5) << 32) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_4) << 24) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_3) << 16) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_2) << 8) + \n")
                                f.write("                                ((uint64_t)"+str+"."+signal.name+"_1);\n")
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&u64"+signal.name+");\n")

                    f.write("\n")

                    f.write("    if (bResult != RTE_SIG_OK) {\n")
                    f.write("        SystemApiLogPrintf(LOG_ERROR_OUTPUT,\"setSignal_"+message_name+" error bResult:0x%x\\r\\n\", bResult);\n")
                    f.write("    }\n")
                    f.write("}\n")

                f.write("\n")

        if len(sys.argv) > 3:
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers

                if message_sender.startswith(tool_config.senders) :
                    # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                    hex_str = hex(message.frame_id)[2:]
                    # 使用zfill()方法在左侧填充0，使字符串长度为3
                    hex_str_padded = hex_str.zfill(3)

                    if message_name.startswith('NM') :
                        print(f"{message.name} 不写入")
                    else :
                        str = "p_"+message_name+"_pri_st"
                        f.write("void setSignal_"+message_name+"_pri(uint8_t *sigbuff, uint8_t len)\n")
                        f.write("{\n")
                        f.write("    uint8_t bResult = RTE_SIG_OK;\n")

                        for signal in message.signals:
                            length = signal.length
                            if length <= 8 :
                                nop = 0
                            elif length <= 16 :
                                f.write("    uint16_t u16"+signal.name+" = 0;\n")
                            elif length <= 32 :
                                f.write("    uint32_t u32"+signal.name+" = 0;\n")
                            else :
                                f.write("    uint64_t u64"+signal.name+" = 0;\n")

                        f.write("    if ("+str+".data_len - 1 != len) {\n")
                        f.write("        SystemApiLogPrintf(LOG_ERROR_OUTPUT,\"sig len error:%d\\r\\n\", len);\n")
                        f.write("        return;\n")
                        f.write("    }\n")
                        f.write("    memcpy(((uint32_t)&"+str+") + 4, sigbuff, len);\n")

                        f.write("\n")

                        for signal in message.signals:
                            length = signal.length
                            if length <= 8 :
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"_PRI(&"+str+"."+signal.name+");\n")
                            elif length <= 16 :
                                f.write("    u16"+signal.name+" = (((uint16_t)"+str+"."+signal.name+"_H) << 8) + \n")
                                f.write("                                ((uint16_t)"+str+"."+signal.name+"_L);\n")
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"_PRI(&u16"+signal.name+");\n")
                            elif length <= 32 :
                                f.write("    u32"+signal.name+" = (((uint32_t)"+str+"."+signal.name+"_H) << 24) + \n")
                                f.write("                                (((uint32_t)"+str+"."+signal.name+"_MH) << 16) + \n")
                                f.write("                                (((uint32_t)"+str+"."+signal.name+"_ML) << 8) + \n")
                                f.write("                                ((uint32_t)"+str+"."+signal.name+"_L);\n")
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"_PRI(&u32"+signal.name+");\n")
                            else :
                                f.write("    u64"+signal.name+" = (((uint64_t)"+str+"."+signal.name+"_8) << 56) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_7) << 48) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_6) << 40) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_5) << 32) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_4) << 24) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_3) << 16) + \n")
                                f.write("                                (((uint64_t)"+str+"."+signal.name+"_2) << 8) + \n")
                                f.write("                                ((uint64_t)"+str+"."+signal.name+"_1);\n")
                                f.write("    bResult |= Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"_PRI(&u32"+signal.name+");\n")

                        f.write("\n")

                        f.write("    if (bResult != RTE_SIG_OK) {\n")
                        f.write("        SystemApiLogPrintf(LOG_ERROR_OUTPUT,\"setSignal_"+message_name+"_pri error bResult:0x%x\\r\\n\", bResult);\n")
                        f.write("    }\n")
                        f.write("}\n")

                    f.write("\n")

        f.write("\n")
        f.write("\n")
        f.write('''
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
}''')
    print("Finish")

