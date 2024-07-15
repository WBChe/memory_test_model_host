def make_mix_pattern_4step(instruction1, data1, instruction2, data2, instruction3, data3, instruction4, data4, txt_mode, txt_name):

    # 定义起始和结束的16进制字符串
    # start_hex = '02000000'
    # end_hex = '027fff00'

    # 将16进制字符串转换为整数
    start_int = int('0x0000', 16)
    end_int = int('0x7fff', 16)

    # 打开文件进行写入
    with open(txt_name, txt_mode) as f:       
        # 循环生成序列并写入文件
        for i in range(start_int, end_int + 1, 1):

            hex_string = instruction1 + '{:04X}'.format(i) + data1   # 将整数转换为16进制字符串，去掉开头的'0x'并填充到8位               
            f.write(hex_string + '\n')  # 写入每个16进制字符串到文件，每个字符串占一行

            hex_string = instruction2 + '{:04X}'.format(i) + data2
            f.write(hex_string + '\n')

            hex_string = instruction3 + '{:04X}'.format(i) + data3
            f.write(hex_string + '\n')

            hex_string = instruction4 + '{:04X}'.format(i) + data4
            f.write(hex_string + '\n')

def make_mix_pattern_4step_sub(instruction1, data1, instruction2, data2, instruction3, data3, instruction4, data4, txt_mode, txt_name):

    # 定义起始和结束的16进制字符串
    # start_hex = '02000000'
    # end_hex = '027fff00'

    # 将16进制字符串转换为整数
    start_int = int('0x7fff', 16)
    end_int = int('0x0000', 16)

    # 打开文件进行写入
    with open(txt_name, txt_mode) as f:       
        # 循环生成序列并写入文件
        for i in range(start_int, end_int - 1, -1):

            hex_string = instruction1 + '{:04X}'.format(i) + data1   # 将整数转换为16进制字符串，去掉开头的'0x'并填充到8位               
            f.write(hex_string + '\n')  # 写入每个16进制字符串到文件，每个字符串占一行

            hex_string = instruction2 + '{:04X}'.format(i) + data2
            f.write(hex_string + '\n')

            hex_string = instruction3 + '{:04X}'.format(i) + data3
            f.write(hex_string + '\n')

            hex_string = instruction4 + '{:04X}'.format(i) + data4
            f.write(hex_string + '\n')



if __name__ == "__main__":
    

    # make_mix_pattern_3step('03', '00', '02', '00', 'a', 'output.hex') # rd ff wr 00
    make_mix_pattern_4step('03', '00', '02', 'ff', '02', '00', '02', 'ff', 'w', 'output.hex') # rd 00 wr ff wr 00 wr ff


    print(f"Sequence generated and written to {'output.hex'}.")
