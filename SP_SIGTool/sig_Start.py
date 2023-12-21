##################################################
#  tool version  #   Author     #    date        #
##################################################
#  V.0.01        # liu.jiankang #  2023.8.24     #
##################################################

import parser_txt
import SpecialSignal_h
import parser_dbc
import CanstackInterface
import parser_excel
import Com_PbCfg_CodeGenerate_c
import CAN_ivi_recv_c
import CAN_ivi_recv_h
import CAN_ivi_send_c
import CAN_ivi_send_h
import CAN_RTE
import tool_config
import os
import time
import sys
# import keyboard
tool_msg = '''
-----------------------------------------------
|   Version     |   Author     |   Date       |
-----------------------------------------------
|    V.0.01     | liu.jiankang | 2023.8.24    |
-----------------------------------------------
'''

if __name__=="__main__":
    print(tool_msg)
    if not os.path.exists(tool_config.file_path):
        os.mkdir(tool_config.file_path)
    if not os.path.exists(tool_config.ivi_file_path):
        os.mkdir(tool_config.ivi_file_path)
    parser_dbc.parse_dbc()
    parser_txt.openreadtxt()
    parser_excel.parser_excel()
    # if 'ivi_epsModeSet' in data:
        # print('OK')
    # print(data)
    SpecialSignal_h.make_file()
    # print('Wait...')
    CanstackInterface.make_file()
    Com_PbCfg_CodeGenerate_c.make_file()

    CAN_ivi_recv_c.make_file()
    CAN_ivi_recv_h.make_file()
    CAN_ivi_send_c.make_file()
    CAN_ivi_send_h.make_file()
    CAN_RTE.make_file()
    print("按'Enter'键退出程序...\n")
    data = input()
    # print('按下 E 键退出程序')1
    sleep_counter = 0
    while(1):
        if sleep_counter >= 2:
        # if keyboard.is_pressed('e'):
            sys.exit()
        sleep_counter = sleep_counter + 1
