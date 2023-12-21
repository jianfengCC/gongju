##################################################
#  tool version  #   Author     #    date        #
##################################################
#  V.0.01        # liu.jiankang #  2023.8.24     #
##################################################

import cantools
import tool_config

can_messages = []


def parse_dbc():
    print('\n*使用的dbc文件: ' + tool_config.dbc_name + '*\n')
    db = cantools.database.Database()
    db.add_dbc_file(tool_config.dbc_name)

    for message in db.messages:
        can_messages.append(message)
        # print(message)
        # for signal in message.signals:
        #     pass
        # if message.frame_id == 0x3f2:
        #     for sig in message.signals:
        #         if sig.name == 'ic_hudHeightSet':
        #             print((sig.initial))
def get_can_msg():
    return can_messages

def get_tx_msg_list():
    tx_msg_list = []
    for msg in can_messages:
        message_sender = msg.senders[0] if msg.senders else None
        if message_sender.startswith(tool_config.senders) :
            tx_msg_list.append(msg)
    return tx_msg_list

def get_rx_msg_counter():
    counter = 0
    for msg in can_messages:
        message_receivers = msg.receivers
        if tool_config.receivers in message_receivers :
            counter = counter + 1
    return counter

def get_tx_msg_counter():
    counter = 0
    for msg in can_messages:
        message_sender = msg.senders[0] if msg.senders else None
        if message_sender.startswith(tool_config.senders) :
            counter = counter + 1
    return counter

def get_signals_counter():
    counter = 0
    for msg in can_messages:
        if str(hex(msg.frame_id).upper()).split('X')[1] == tool_config.NM_Msg_CAN_ID.split('x')[1]:
            pass
        else:
            for sig in msg.signals:
                counter = counter + 1
    # print(counter)
    return counter

def get_all_buffer_size():
    counter = 0
    for msg in can_messages:
        # print(msg)
        if str(hex(msg.frame_id).upper()).split('X')[1] == tool_config.NM_Msg_CAN_ID.split('x')[1]:
            # print(hex(msg.frame_id))
            pass
        else:
            for sig in msg.signals:
                # print(hex(msg.frame_id))
                counter = counter + sig.length
    print(counter)
    return counter

def get_signals():
    signals = []
    for msg in can_messages:
        # print(msg)
        for sig in msg.signals:
            signals.append(sig)
    # print(counter)
    return signals

def get_sig_type(signal_name):
    sig_type = ''
    for msg in can_messages:
        # print(msg)
        for sig in msg.signals:
            if signal_name == sig.name:
                if(sig.is_signed):
                    if sig.length <= 8:
                        sig_type = 'COM_SINT8'
                    elif sig.length <= 16:
                        sig_type = 'COM_SINT16'
                    elif sig.length <= 32:
                        sig_type = 'COM_SINT32'
                    else:
                        sig_type = 'COM_SINT64'
                else:
                    if sig.length <= 8:
                        sig_type = 'COM_UINT8'
                    elif sig.length <= 16:
                        sig_type = 'COM_UINT16'
                    elif sig.length <= 32:
                        sig_type = 'COM_UINT32'
                    else:
                        sig_type = 'COM_UINT64'
    return sig_type

def get_date_type(sig_type):
    if sig_type == 'COM_UINT8':
        return 'uint8_t'
    elif sig_type == 'COM_UINT16':
        return 'uint16_t'
    elif sig_type == 'COM_UINT32':
        return 'uint32_t'
    elif sig_type == 'COM_UINT64':
        return 'uint64_t'
    elif sig_type == 'COM_SINT8':
        return 'int8_t'
    elif sig_type == 'COM_SINT16':
        return 'int16_t'
    elif sig_type == 'COM_SINT32':
        return 'int32_t'
    elif sig_type == 'COM_SINT64':
        return 'int64_t'

def Is_Msg_Send(message_name):
    for msg in can_messages:
        if message_name == msg.name:
            message_sender = msg.senders[0] if msg.senders else None
            if message_sender.startswith(tool_config.senders) :
                return True
    return False