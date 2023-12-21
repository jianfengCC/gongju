import xlrd   #引入库
import tool_config

type_map = {"ONCHANGE" : "COM_TRIGGERED_ON_CHANGE",
"ONWRITEWITHREPETITION" : "COM_TRIGGERED",
"CYCLE" : "COM_PENDING",
"ONWRITE" :"COM_PENDING",
"ONCHANGEWITHREPETITION" :"COM_TRIGGERED_ON_CHANGE"}
all_sig_id_list = []
sig_send_type_map = {}
all_sig_name_list = []
sig_init_value_map = {}

msg_list = []
msg_id_map = {}
msg_cycle_map = {}
msg_sig_map = {}

def send_type_conversion(type_in_excel):
    return type_map[type_in_excel.upper()]
    pass

def parser_excel():

    fp = xlrd.open_workbook(tool_config.excel_name)
    # sheet_num = fp.nsheets
    # sheet_names = fp.sheet_names()
    sheet=fp.sheet_by_name('Matrix')
    rows=sheet.nrows   #获取sheet页的行数，一共有几行
    columns=sheet.ncols   #获取sheet页的列数，一共有几列
    send_type_col = 0
    SignalName_col = 0
    msg_name_col = 0
    msg_id_col = 0
    msg_cyc_time_col = 0
    sig_init_val_col = 0
    for col_index in range(columns):
        if 'SignalName' in str(sheet.cell(0,col_index).value):
            # print(col_index)
            SignalName_col = col_index
        elif'Signal Send Type' in str(sheet.cell(0,col_index).value):
            send_type_col = col_index
        elif 'Msg Name' in str(sheet.cell(0,col_index).value):
            msg_name_col = col_index
        elif 'Msg ID' in str(sheet.cell(0,col_index).value):
            msg_id_col = col_index
        elif 'Msg Cycle Time' in str(sheet.cell(0,col_index).value):
            msg_cyc_time_col = col_index
        elif 'Initial ValueHex' in str(sheet.cell(0,col_index).value):
            sig_init_val_col = col_index
    for row in range(1,rows):

        if sheet.cell(row,msg_name_col).ctype != 0 or sheet.cell(row,msg_name_col).value != '':
            sig_name_list = []
            msg_name = sheet.cell(row,msg_name_col).value
            msg_id = sheet.cell(row,msg_id_col).value
            if msg_id != tool_config.NM_Msg_CAN_ID:
                if sheet.cell(row,msg_cyc_time_col).ctype != 0 or sheet.cell(row,msg_cyc_time_col).value != '':
                    msg_cycle = int(sheet.cell(row,msg_cyc_time_col).value)
                else:
                    msg_cycle = 0
                for i in range(row+1,rows):

                    # print(sheet.cell(row,SignalName_col).value)
                    if sheet.cell(i,SignalName_col).ctype != 0 or sheet.cell(i,SignalName_col).value != '':

                        sig_name = sheet.cell(i,SignalName_col).value.replace(" ","").strip()
                        # print(sig_name)
                        sig_send_type = send_type_conversion(sheet.cell(i,send_type_col).value)
                        sig_init_val = sheet.cell(i,sig_init_val_col).value
                        if not sig_name in sig_name_list:
                            sig_name_list.append(sig_name)
                        all_sig_name_list.append(sig_name)
                        sig_id = sig_name + msg_id.upper()
                        if not sig_id in all_sig_id_list:
                            all_sig_id_list.append(sig_id)
                        sig_send_type_map[sig_id] = sig_send_type
                        sig_init_value_map[sig_id] = sig_init_val
                    else:
                        break
            if not msg_name in msg_list:
                msg_list.append(msg_name)
            msg_id_map[msg_name] = msg_id
            msg_cycle_map[msg_name] = msg_cycle
            msg_sig_map[msg_name] = sig_name_list
    # for row_index in range(1,rows):
    #     if sheet.cell(row_index,SignalName_col).ctype == 0 or sheet.cell(row_index,SignalName_col).value == '':
    #         pass
    #     else:
    #         sig_name = sheet.cell(row_index,SignalName_col).value
    #         sig_name = sig_name.replace(" ","")
    #         # if ' ' in sig_name:
    #             # print(sig_name)
    #         sig_name_list.append(sig_name)
    #         sig_send_type_in_excel = sheet.cell(row_index,send_type_col).value

    #         sig_send_type = send_type_conversion(sig_send_type_in_excel)
    #         sig_send_type_map[sig_name] = sig_send_type

    # print(sig_send_type_map)
        # print(sig_name)
def get_sig_send_type_map():
    return sig_send_type_map

def get_sig_name_list():
    return all_sig_name_list

def get_sig_id_list():
    # print(all_sig_id_list)
    return all_sig_id_list

def get_sig_init_val_list():
    return sig_init_value_map

def get_msg_list():
    return msg_list

def get_msg_id_list():
    return msg_id_map

def get_msg_sig_list():
    return msg_sig_map