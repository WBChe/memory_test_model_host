def make_mix_pattern_MATS1(txt_mode, txt_name):

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

            hex_string = '03' + '{:04X}'.format(i) + '00'   # 将整数转换为16进制字符串，去掉开头的'0x'并填充到8位               
            f.write(hex_string + '\n')  # 写入每个16进制字符串到文件，每个字符串占一行

            hex_string = '02' + '{:04X}'.format(i) + 'ff'
            f.write(hex_string + '\n')





if __name__ == "__main__":
   
    make_mix_pattern_MATS1('w', 'output.hex')
    print(f"Sequence generated and written to {'output.hex'}.")
