import cantools
import os
import glob
import sys
import tool_config
def make_file():
    # 获取当前目录
    current_dir = os.getcwd()

    # 指定格式的文件名
    file_pattern = "*.dbc"

    # 遍历当前目录下的所有文件，获取指定格式的文件名
    for file_name in glob.glob(os.path.join(current_dir, file_pattern)):
        print(file_name)

    # Load DBC file
    db = cantools.database.load_file(tool_config.dbc_name)
    if len(sys.argv) > 3:
        db1 = cantools.database.load_file(sys.argv[3])

    filename = "ivi_send.c"

    with open(tool_config.ivi_file_path + filename, "w") as f:
        text = """/**
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

#define BUF_MAX_SIZE 250"""
        f.write(text)
        f.write("\n")
        f.write("\n")

        cnt = 0
        cnt1 = 0
        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers

            if tool_config.senders in message_receivers :
                if message_name.startswith('NM') :
                    print(f"{message.name} 不写入")
                else :
                    f.write("BOOL getSignal_"+message_name+"(void);\n")
                    cnt += 1

        f.write("\n")

        if len(sys.argv) > 3:
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers

                if tool_config.senders in message_receivers :
                    if message_name.startswith('NM') :
                        print(f"{message.name} 不写入")
                    else :
                        f.write("BOOL getSignal_"+message_name+"_pri(void);\n")
                        cnt1 += 1

            f.write("\n")


        text = """
    typedef BOOL (*pGetSigFunc)(void);

    typedef struct STC_SIGNAL_INFO_
    {
        uint8_t*            pSigStc;
        pGetSigFunc         pSigFunc;
    } STC_SIGNAL_INFO;
    """
        f.write(text)
        f.write("\n")

        f.write("#define SIG_PUB_MAX_SIZE "+str(cnt)+"\n")

        text = """STC_SIGNAL_INFO gPubSigInfo[SIG_PUB_MAX_SIZE] =
    {"""
        f.write(text)
        f.write("\n")

        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers

            if tool_config.senders in message_receivers :
                # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                hex_str = hex(message.frame_id)[2:]
                # 使用zfill()方法在左侧填充0，使字符串长度为3
                hex_str_padded = hex_str.zfill(3)

                if message_name.startswith('NM') :
                    print(f"{message.name} 不写入")
                else :
                    strp = "p_"+message_name+"_st"
                    f.write("    {&"+strp+", getSignal_"+message_name+"},\n")
        f.write("};\n")

        if cnt1 != 0 :
            f.write("\n")
            f.write("#define SIG_PRI_MAX_SIZE "+str(cnt1)+"\n")

            text = """STC_SIGNAL_INFO gPriSigInfo[SIG_PRI_MAX_SIZE] =
    {"""
            f.write(text)
            f.write("\n")

            if len(sys.argv) > 3:
                for message in db1.messages:
                    # Get message name, sender, and receivers
                    message_name = message.name
                    message_sender = message.senders[0] if message.senders else None
                    message_receivers = message.receivers

                    if tool_config.senders in message_receivers :
                        # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                        hex_str = hex(message.frame_id)[2:]
                        # 使用zfill()方法在左侧填充0，使字符串长度为3
                        hex_str_padded = hex_str.zfill(3)

                        if message_name.startswith('NM') :
                            print(f"{message.name} 不写入")
                        else :
                            strp = "p_"+message_name+"_pri_st"
                            f.write("    {&"+strp+", getSignal_"+message_name+"_pri},\n")
                f.write("};\n")
                f.write("\n")
            f.write("};\n")

        text = """
    void printlog(uint8_t* buf, uint8_t size)
    {
        #if USE_TEST
        int i = 0;
        SystemApiLogPrintf(LOG_INFO_OUTPUT, "--------------  send2soc size:%d\\r\\n", size);
        for (i; i < size; i++) {
            SystemApiLogPrintf(LOG_INFO_OUTPUT, "0x%x ", buf[i]);
        }
        SystemApiLogPrintf(LOG_INFO_OUTPUT, "\\r\\n");
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
    """
        f.write(text)

        if cnt1 != 0 :
            f.write("    max_size = (MESSAGE_TX_SOC_IVI_REPORT_PUB == event_id) ? SIG_PUB_MAX_SIZE : SIG_PRI_MAX_SIZE;\n")
            f.write("    for (i; i < max_size; i++) {;\n")
            f.write("        STC_SIGNAL_INFO cursig = (MESSAGE_TX_SOC_IVI_REPORT_PUB == event_id) ? gPubSigInfo[i] : gPriSigInfo[i];\n")
        else :
            f.write("    max_size = SIG_PUB_MAX_SIZE;\n")
            f.write("    for (i; i < max_size; i++) {;\n")
            f.write("        STC_SIGNAL_INFO cursig = gPubSigInfo[i];\n")
        text = """        if(TRUE == (*cursig.pSigFunc)()) {
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
    }"""
        f.write(text)
        f.write("\n")
        f.write("\n")

        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers

            if tool_config.senders in message_receivers :
                # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                hex_str = hex(message.frame_id)[2:]
                # 使用zfill()方法在左侧填充0，使字符串长度为3
                hex_str_padded = hex_str.zfill(3)

                if message_name.startswith('NM') :
                    print(f"{message.name} 不写入")
                else :
                    strp = "package_0x"+hex_str_padded.upper()+"_st_"+message_name
                    str1 = "p_"+message_name+"_st"
                    f.write("BOOL getSignal_"+message_name+"(void)\n")
                    f.write("{\n")
                    f.write("    uint8_t bResult = FALSE;\n")

                    u8 = 0
                    u16 = 0
                    u32 = 0
                    u64 = 0
                    uTuyp = 0
                    for signal in message.signals :
                        length = signal.length
                        if length <= 8 :
                            u8 = 1
                        elif length <= 16 :
                            u16 = 1
                        elif length <= 32 :
                            u32 = 1
                        else :
                            u64 = 1
                    if u64 == 1 :
                        f.write("    uint64_t Read_Signal = 0;\n")
                        uTuyp = 1
                    elif u32 == 1 :
                        f.write("    uint32_t Read_Signal = 0;\n")
                        uTuyp = 1
                    elif u16 == 1 :
                        f.write("    uint16_t Read_Signal = 0;\n")
                        uTuyp = 1
                    else :
                        f.write("    uint8_t Read_Signal = 0;\n")

                    f.write("    struct "+strp+" signal_bk;\n")
                    f.write("    memcpy(&signal_bk, &"+str1+", sizeof("+str1+"));\n")
                    f.write("\n")

                    cnt = 0;
                    for signal in message.signals :
                        length = signal.length
                        if cnt != 0 :
                            f.write("    Read_Signal = 0;\n")
                        f.write("    bResult = Rte_Read_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"(&Read_Signal);\n")
                        f.write("    if (bResult == RTE_SIG_OK) {\n")
                        if length <= 8 :
                            if uTuyp == 1 :
                                f.write("        "+str1+"."+signal.name+" = (uint8_t)(Read_Signal);\n")
                            else :
                                f.write("        "+str1+"."+signal.name+" = Read_Signal;\n")
                        elif length <= 16 :
                            f.write("        "+str1+"."+signal.name+"_H = (uint8_t)(Read_Signal >> 8);\n")
                            f.write("        "+str1+"."+signal.name+"_L = (uint8_t)(Read_Signal);\n")
                        elif length <= 32 :
                            f.write("        "+str1+"."+signal.name+"_H = (uint8_t)(Read_Signal >> 24);\n")
                            f.write("        "+str1+"."+signal.name+"_MH = (uint8_t)(Read_Signal >> 16);\n")
                            f.write("        "+str1+"."+signal.name+"_ML = (uint8_t)(Read_Signal >> 8);\n")
                            f.write("        "+str1+"."+signal.name+"_L = (uint8_t)(Read_Signal);\n")
                        else :
                            f.write("        "+str1+"."+signal.name+"_8 = (uint8_t)(Read_Signal >> 56);\n")
                            f.write("        "+str1+"."+signal.name+"_7 = (uint8_t)(Read_Signal >> 48);\n")
                            f.write("        "+str1+"."+signal.name+"_6 = (uint8_t)(Read_Signal >> 40);\n")
                            f.write("        "+str1+"."+signal.name+"_5 = (uint8_t)(Read_Signal >> 32);\n")
                            f.write("        "+str1+"."+signal.name+"_4 = (uint8_t)(Read_Signal >> 24);\n")
                            f.write("        "+str1+"."+signal.name+"_3 = (uint8_t)(Read_Signal >> 16);\n")
                            f.write("        "+str1+"."+signal.name+"_2 = (uint8_t)(Read_Signal >> 8);\n")
                            f.write("        "+str1+"."+signal.name+"_1 = (uint8_t)(Read_Signal);\n")
                        f.write("    } else {\n")
                        if length <= 8 :
                            f.write("        "+str1+"."+signal.name+" = 0;\n")
                        elif length <= 16 :
                            f.write("        "+str1+"."+signal.name+"_H = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_L = 0;\n")
                        elif length <= 32 :
                            f.write("        "+str1+"."+signal.name+"_H = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_MH = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_ML = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_L = 0;\n")
                        else :
                            f.write("        "+str1+"."+signal.name+"_8 = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_7 = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_6 = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_5 = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_4 = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_3 = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_2 = 0;\n")
                            f.write("        "+str1+"."+signal.name+"_1 = 0;\n")
                        f.write("    }\n")

                        if cnt == 0 :
                            f.write("    "+str1+".data_status = bResult;\n")
                        f.write("\n")
                        cnt += 1

                    f.write("    if (memcmp(&signal_bk, &"+str1+", sizeof("+str1+")) == 0) {\n")
                    f.write("        return FALSE;\n")
                    f.write("    } else {\n")
                    f.write("        return TRUE;\n")
                    f.write("    }\n")
                    f.write("}\n")

                f.write("\n")

        if len(sys.argv) > 3:
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers

                if tool_config.senders in message_receivers :
                    # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                    hex_str = hex(message.frame_id)[2:]
                    # 使用zfill()方法在左侧填充0，使字符串长度为3
                    hex_str_padded = hex_str.zfill(3)

                    if message_name.startswith('NM') :
                        print(f"{message.name} 不写入")
                    else :
                        strp = "package_0x"+hex_str_padded.upper()+"_st_"+message_name+"_pri"
                        str1 = "p_"+message_name+"_pri_st"
                        f.write("BOOL getSignal_"+message_name+"_pri(void)\n")
                        f.write("{\n")
                        f.write("    uint8_t bResult = FALSE;\n")

                        u8 = 0
                        u16 = 0
                        u32 = 0
                        u64 = 0
                        uTuyp = 0
                        for signal in message.signals :
                            length = signal.length
                            if length <= 8 :
                                u8 = 1
                            elif length <= 16 :
                                u16 = 1
                            elif length <= 32 :
                                u32 = 1
                            else :
                                u64 = 1
                        if u64 == 1 :
                            f.write("    uint64_t Read_Signal = 0;\n")
                            uTuyp = 1
                        elif u32 == 1 :
                            f.write("    uint32_t Read_Signal = 0;\n")
                            uTuyp = 1
                        elif u16 == 1 :
                            f.write("    uint16_t Read_Signal = 0;\n")
                            uTuyp = 1
                        else :
                            f.write("    uint8_t Read_Signal = 0;\n")

                        f.write("    struct "+strp+" signal_bk;\n")
                        f.write("    memcpy(&signal_bk, &"+str1+", sizeof("+str1+"));\n")
                        f.write("\n")

                        cnt = 0;
                        for signal in message.signals :
                            length = signal.length
                            if cnt != 0 :
                                f.write("    Read_Signal = 0;\n")
                            f.write("    bResult = Rte_Read_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+signal.name+"_PRI(&Read_Signal);\n")
                            f.write("    if (bResult == RTE_SIG_OK) {\n")
                            if length <= 8 :
                                if uTuyp == 1 :
                                    f.write("        "+str1+"."+signal.name+" = (uint8_t)(Read_Signal);\n")
                                else :
                                    f.write("        "+str1+"."+signal.name+" = Read_Signal;\n")
                            elif length <= 16 :
                                f.write("        "+str1+"."+signal.name+"_H = (uint8_t)(Read_Signal >> 8);\n")
                                f.write("        "+str1+"."+signal.name+"_L = (uint8_t)(Read_Signal);\n")
                            elif length <= 32 :
                                f.write("        "+str1+"."+signal.name+"_H = (uint8_t)(Read_Signal >> 24);\n")
                                f.write("        "+str1+"."+signal.name+"_MH = (uint8_t)(Read_Signal >> 16);\n")
                                f.write("        "+str1+"."+signal.name+"_ML = (uint8_t)(Read_Signal >> 8);\n")
                                f.write("        "+str1+"."+signal.name+"_L = (uint8_t)(Read_Signal);\n")
                            else :
                                f.write("        "+str1+"."+signal.name+"_8 = (uint8_t)(Read_Signal >> 56);\n")
                                f.write("        "+str1+"."+signal.name+"_7 = (uint8_t)(Read_Signal >> 48);\n")
                                f.write("        "+str1+"."+signal.name+"_6 = (uint8_t)(Read_Signal >> 40);\n")
                                f.write("        "+str1+"."+signal.name+"_5 = (uint8_t)(Read_Signal >> 32);\n")
                                f.write("        "+str1+"."+signal.name+"_4 = (uint8_t)(Read_Signal >> 24);\n")
                                f.write("        "+str1+"."+signal.name+"_3 = (uint8_t)(Read_Signal >> 16);\n")
                                f.write("        "+str1+"."+signal.name+"_2 = (uint8_t)(Read_Signal >> 8);\n")
                                f.write("        "+str1+"."+signal.name+"_1 = (uint8_t)(Read_Signal);\n")
                            f.write("    } else {\n")
                            if length <= 8 :
                                f.write("        "+str1+"."+signal.name+" = 0;\n")
                            elif length <= 16 :
                                f.write("        "+str1+"."+signal.name+"_H = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_L = 0;\n")
                            elif length <= 32 :
                                f.write("        "+str1+"."+signal.name+"_H = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_MH = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_ML = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_L = 0;\n")
                            else :
                                f.write("        "+str1+"."+signal.name+"_8 = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_7 = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_6 = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_5 = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_4 = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_3 = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_2 = 0;\n")
                                f.write("        "+str1+"."+signal.name+"_1 = 0;\n")
                            f.write("    }\n")

                            if cnt == 0 :
                                f.write("    "+str1+".data_status = bResult;\n")
                            f.write("\n")
                            cnt += 1

                        f.write("    if (memcmp(&signal_bk, &"+str1+", sizeof("+str1+")) == 0) {\n")
                        f.write("        return FALSE;\n")
                        f.write("    } else {\n")
                        f.write("        return TRUE;\n")
                        f.write("    }\n")
                        f.write("}\n")

                    f.write("\n")

        f.write("\n")
        f.write("\n")

    print("Finish")

