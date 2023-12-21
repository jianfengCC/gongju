##################################################
#  tool version  #   Author     #    date        #
##################################################
#  V.0.01        # liu.jiankang #  2023.8.24     #
##################################################
import tool_config
data = []
def openreadtxt():
    file = open(tool_config.Sp_Sig_txt,'r',encoding='utf-8')  #打开文件
    file_data = file.readlines() #读取所有行
    for line in file_data:
        line = line.strip()
        data.append(line.upper()) #将每行数据插入data中
    # print(data)

def get_txt():
    return data
