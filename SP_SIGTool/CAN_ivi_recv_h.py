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

    filename = "ivi_recv.h"

    with open(tool_config.ivi_file_path + filename, "w") as f:
        text = """/**
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
typedef unsigned char   BOOL;"""
        f.write(text)
        f.write("\n")

        f.write("\n")

        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers

            data_len = 1
            if message_sender.startswith(tool_config.senders) :
                # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                hex_str = hex(message.frame_id)[2:]
                # 使用zfill()方法在左侧填充0，使字符串长度为3
                hex_str_padded = hex_str.zfill(3)
                if message_name.startswith('NM') :
                    print(f"{message.name} 不写入")
                else :
                    f.write("struct package_0x"+hex_str_padded.upper()+"_st_"+message_name+"\n")
                    f.write("{\n")
                    f.write("    uint8_t canid_high;\n")
                    f.write("    uint8_t canid_low;\n")
                    f.write("    uint8_t data_len;\n")
                    f.write("    uint8_t data_status;\n")
                    for signal in message.signals:
                        length = signal.length
                        if length <= 8 :
                            f.write("    uint8_t "+signal.name+";\n")
                            data_len += 1
                        elif length <= 16 :
                            f.write("    uint8_t "+signal.name+"_H;\n")
                            f.write("    uint8_t "+signal.name+"_L;\n")
                            data_len += 2
                        elif length <= 32 :
                            f.write("    uint8_t "+signal.name+"_H;\n")
                            f.write("    uint8_t "+signal.name+"_MH;\n")
                            f.write("    uint8_t "+signal.name+"_ML;\n")
                            f.write("    uint8_t "+signal.name+"_L;\n")
                            data_len += 4
                        else :
                            f.write("    uint8_t "+signal.name+"_8;\n")
                            f.write("    uint8_t "+signal.name+"_7;\n")
                            f.write("    uint8_t "+signal.name+"_6;\n")
                            f.write("    uint8_t "+signal.name+"_5;\n")
                            f.write("    uint8_t "+signal.name+"_4;\n")
                            f.write("    uint8_t "+signal.name+"_3;\n")
                            f.write("    uint8_t "+signal.name+"_2;\n")
                            f.write("    uint8_t "+signal.name+"_1;\n")
                            data_len += 8
                    hex_str_padded = hex_str.zfill(4)
                    f.write("}p_"+message_name+"_st = {0x"+hex_str_padded[:2].upper()+", 0x"+hex_str_padded[2:4].upper()+", "+str(data_len)+"};\n")
                    f.write("\n")

        f.write("\n")
        f.write("\n")

        if len(sys.argv) > 3:
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers

                data_len = 1
                if message_sender.startswith(tool_config.senders) :
                    # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                    hex_str = hex(message.frame_id)[2:]
                    # 使用zfill()方法在左侧填充0，使字符串长度为3
                    hex_str_padded = hex_str.zfill(3)

                    if message_name.startswith('NM') :
                        print(f"{message.name} 不写入")
                    else :
                        f.write("struct package_0x"+hex_str_padded.upper()+"_st_"+message_name+"_pri\n")
                        f.write("{\n")
                        f.write("    uint8_t canid_high;\n")
                        f.write("    uint8_t canid_low;\n")
                        f.write("    uint8_t data_len;\n")
                        f.write("    uint8_t data_status;\n")
                        for signal in message.signals:
                            length = signal.length
                            if length <= 8 :
                                f.write("    uint8_t "+signal.name+";\n")
                                data_len += 1
                            elif length <= 16 :
                                f.write("    uint8_t "+signal.name+"_H;\n")
                                f.write("    uint8_t "+signal.name+"_L;\n")
                                data_len += 2
                            elif length <= 32 :
                                f.write("    uint8_t "+signal.name+"_H;\n")
                                f.write("    uint8_t "+signal.name+"_MH;\n")
                                f.write("    uint8_t "+signal.name+"_ML;\n")
                                f.write("    uint8_t "+signal.name+"_L;\n")
                                data_len += 4
                            else :
                                f.write("    uint8_t "+signal.name+"_8;\n")
                                f.write("    uint8_t "+signal.name+"_7;\n")
                                f.write("    uint8_t "+signal.name+"_6;\n")
                                f.write("    uint8_t "+signal.name+"_5;\n")
                                f.write("    uint8_t "+signal.name+"_4;\n")
                                f.write("    uint8_t "+signal.name+"_3;\n")
                                f.write("    uint8_t "+signal.name+"_2;\n")
                                f.write("    uint8_t "+signal.name+"_1;\n")
                                data_len += 8
                        hex_str_padded = hex_str.zfill(4)
                        f.write("}p_"+message_name+"_pri_st = {0x"+hex_str_padded[:2].upper()+", 0x"+hex_str_padded[2:4].upper()+", "+str(data_len)+"};\n")
                        f.write("\n")

            f.write("\n")
            f.write("\n")

        f.write("#endif")

    print("Finish")

