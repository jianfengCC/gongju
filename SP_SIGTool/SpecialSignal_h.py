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
 * @file    SpecialSignal.h
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

#ifndef SPECIALSIGNAL_H
#define SPECIALSIGNAL_H

'''
def write_enum(fp):
    sp_data = parser_txt.get_txt()
    msg_list = parser_dbc.get_tx_msg_list()
    text = 'typedef enum { \n'
    for msg in msg_list:
        for sig in msg.signals:
            if sig.name.upper() in sp_data:
                msg_num = str(hex(msg.frame_id).upper()).split('X')[1]
                while(len(msg_num) < 3):
                    msg_num = '0' + msg_num
                msg_id = '0X'+ msg_num
                text = text + '\
    E_'+ sig.name.upper() +'_'+ msg_id +'_INFO,\n'

    text = text + \
'    E_MAX\n\
}CanSignal_special_e;\n\
#endif'
    fp.write(text)


def make_file():
    # print('='*16 + ' Start make SpecialSignal.h ' + '='*16)
    write_f = open((tool_config.file_path+'SpecialSignal.h'), "w",encoding= 'UTF-8')
    write_f.write(head_text)
    print('Wait...')
    write_enum(write_f)
    write_f.close()
    print('='*16 + ' Success make SpecialSignal.h ' + '='*16)