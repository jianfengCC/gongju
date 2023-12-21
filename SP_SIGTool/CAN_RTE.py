import cantools
import sys
import tool_config

def make_file():
    filename = "RTE.h"

    with open(tool_config.ivi_file_path + filename, "w") as f:
        text = """/**
* Copyright (c) 2018-2023 ThunderSoft
* All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
* You may not use, copy, distribute, modify, transmit in any form this file
* except in compliance with ThunderSoft in writing by applicable law.
*
*/
#ifndef _RTE_H_
#define _RET_H_

#include "Com_Cfg.h"
#include "r_typedefs.h"


/* return of RTE function
write return : ok, busy,    available
read  return : ok, timeout, available
*/
#define  RTE_SIG_OK                     (0U)
#define  RTE_SIG_TIMEOUT                (0x82U)
#define  RTE_SIG_BUSY                   (0x81U)
#define  RTE_SIG_NOT_AVAILABLE          (0x80U)

extern uint8_t Com_SendSignal(uint16_t SignalId, const void *SignalDataPtr);
extern uint8_t Com_ReceiveSignal(uint16_t SignalId, void* SignalDataPtr);"""
        f.write(text)

        f.write("\n")
        f.write("\n")

        f.write("// Public can signal\n")
        # Load the DBC file
        db = cantools.database.Database()
        db.add_dbc_file(tool_config.dbc_name)

        f.write("/*----CAN write InterFace----*/\n")
        # Print all signals in the database
        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers
            if message_sender.startswith(tool_config.senders) :
                for signal in message.signals:
                    str1 = f"{signal.name}"
                    if str1.startswith('NM') :
                        print(f"{message.name}, {signal.name} 不写入")
                    else :
                        # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                        hex_str = hex(message.frame_id)[2:]
                        # 使用zfill()方法在左侧填充0，使字符串长度为3
                        hex_str_padded = hex_str.zfill(3)
                        str2 = f"{hex_str_padded}"
                        s =  f"COMCONF_COMSIGNAL_"+str1+"_0X"+str2+"_INFO"
                        s_upper = s.upper() #大写
                        f.write("#define Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+str1+"(data) Com_SendSignal("+s_upper+",data)\n")

        f.write("/*----CAN Read  InterFace----*/\n")
        # Print all signals in the database
        for message in db.messages:
            # Get message name, sender, and receivers
            message_name = message.name
            message_sender = message.senders[0] if message.senders else None
            message_receivers = message.receivers
            if tool_config.senders in message_receivers :
                for signal in message.signals:
                    str1 = f"{signal.name}"
                    if str1.startswith('NM') :
                        print(f"{message.name}, {signal.name} 不写入")
                    else :
                        # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                        hex_str = hex(message.frame_id)[2:]
                        # 使用zfill()方法在左侧填充0，使字符串长度为3
                        hex_str_padded = hex_str.zfill(3)
                        str2 = f"{hex_str_padded}"
                        s =  f"COMCONF_COMSIGNAL_"+str1+"_0X"+str2+"_INFO"
                        s_upper = s.upper() #大写
                        f.write("#define Rte_Read_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+str1+"(data) Com_ReceiveSignal("+s_upper+",data)\n")

        if len(sys.argv) > 3:
            f.write("// Privite can signal\n")
            # Load the DBC file
            db1 = cantools.database.Database()
            db1.add_dbc_file(sys.argv[3])

            f.write("/*----CAN write InterFace----*/\n")
            # Print all signals in the database
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers
                if message_sender.startswith(tool_config.senders) :
                    for signal in message.signals:
                        str1 = f"{signal.name}"
                        if str1.startswith('NM') :
                            print(f"{message.name}, {signal.name} 不写入")
                        else :
                            # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                            hex_str = hex(message.frame_id)[2:]
                            # 使用zfill()方法在左侧填充0，使字符串长度为3
                            hex_str_padded = hex_str.zfill(3)
                            str2 = f"{hex_str_padded}"
                            s =  f"COMCONF_COMSIGNAL_"+str1+"_0X"+str2+"_INFO"
                            s_upper = s.upper() #大写
                            f.write("#define Rte_Write_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+str1+"_PRI(data) Com_SendSignal("+s_upper+"_PRI,data)\n")

            f.write("/*----CAN Read  InterFace----*/\n")
            # Print all signals in the database
            for message in db1.messages:
                # Get message name, sender, and receivers
                message_name = message.name
                message_sender = message.senders[0] if message.senders else None
                message_receivers = message.receivers
                if tool_config.senders in message_receivers :
                    for signal in message.signals:
                        str1 = f"{signal.name}"
                        if str1.startswith('NM') :
                            print(f"{message.name}, {signal.name} 不写入")
                        else :
                            # 使用hex()将10进制转换成16进制字符串，并去掉前缀'0x'
                            hex_str = hex(message.frame_id)[2:]
                            # 使用zfill()方法在左侧填充0，使字符串长度为3
                            hex_str_padded = hex_str.zfill(3)
                            str2 = f"{hex_str_padded}"
                            s =  f"COMCONF_COMSIGNAL_"+str1+"_0X"+str2+"_INFO"
                            s_upper = s.upper() #大写
                            f.write("#define Rte_Read_rpSR_CANMSG_"+message_name+"_ComIn_VeCAN_"+str1+"_PRI(data) Com_ReceiveSignal("+s_upper+"_PRI,data)\n")

        f.write("\n")
        f.write("\n")

        f.write("#endif /* end of \"#ifndef _RTE_H_\" */\n")

    print("Finish")

