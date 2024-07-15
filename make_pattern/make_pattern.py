
def pattern_addr_add(start_hex, end_hex, txt_mode, txt_name):

    # 定义起始和结束的16进制字符串
    # start_hex = '02000000'
    # end_hex = '027fff00'

    # 将16进制字符串转换为整数
    start_int = int(start_hex, 16)
    end_int = int(end_hex, 16)

    #addr 递增加数
    step = 256

    # 打开文件进行写入
    with open(txt_name, txt_mode) as f:       
        # 循环生成序列并写入文件
        for i in range(start_int, end_int + 1, step):
            # 将整数转换为16进制字符串，去掉开头的'0x'并填充到8位
            hex_string = '{:08X}'.format(i)
            # 写入每个16进制字符串到文件，每个字符串占一行
            f.write(hex_string + '\n')

    print(f'已生成并写入到文件 "output.txt" 中，包含序列从 {start_hex} 到 {end_hex} 的所有地址递增数。')

def pattern_addr_sub(start_hex, end_hex, txt_mode, txt_name):
    
    # 定义起始和结束的16进制字符串
    # start_hex = '02000000'
    # end_hex = '027fff00'

    # 将16进制字符串转换为整数
    start_int = int(start_hex, 16)
    end_int = int(end_hex, 16)

    #addr 递减数
    step = 256

    # 打开文件进行写入
    with open(txt_name, txt_mode) as f:
        # 循环生成序列并写入文件
        for i in range(start_int, end_int - 1, -step):
            # 将整数转换为16进制字符串，去掉开头的'0x'并填充到8位
            hex_string = '{:08X}'.format(i)
            # 写入每个16进制字符串到文件，每个字符串占一行
            f.write(hex_string + '\n')

    print(f'已生成并写入到文件 "output.txt" 中，包含序列从 {start_hex} 到 {end_hex} 的所有地址递减数。')

# function for more step pattern 
def make_mix_pattern_2step(instruction1, data1, instruction2, data2, txt_mode, txt_name):

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

def make_mix_pattern_2step_sub(instruction1, data1, instruction2, data2, txt_mode, txt_name):

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

def make_mix_pattern_3step(instruction1, data1, instruction2, data2, instruction3, data3, txt_mode, txt_name):

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

def make_mix_pattern_3step_sub(instruction1, data1, instruction2, data2, instruction3, data3, txt_mode, txt_name):

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

# function for checkerboard 
def generate_sequence00(start, end):
    increments = [511, 1]
    current_index = 0
    
    current = start
    
    while current <= end:
        yield current
        current += increments[current_index]
        current_index = (current_index + 1) % len(increments)

def generate_sequenceff(start, end):
    increments = [1, 511]
    current_index = 0
    
    current = start
    
    while current <= end:
        yield current
        current += increments[current_index]
        current_index = (current_index + 1) % len(increments)

def checkerboard_wr00ff(filename, start, end, txt_mode):
    with open(filename, txt_mode) as f:
        for address in generate_sequence00(start, end):
            hex_string = format(address, '08x')
            f.write(hex_string + '\n')

def checkerboard_wrff00(filename, start, end, txt_mode):
    with open(filename, txt_mode) as f:
        for address in generate_sequenceff(start, end):
            hex_string = format(address, '08x')
            f.write(hex_string + '\n')





#---------------------------------------------------------pattern function------------------------------------------------#

# MSCAN
def make_mscan_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'mscan.hex')  #wr 0
    pattern_addr_add('03000000', '037fff00', 'a', 'mscan.hex')  #rd 0
    pattern_addr_add('020000ff', '027fffff', 'a', 'mscan.hex')  #wr 1
    pattern_addr_add('03000000', '037fff00', 'a', 'mscan.hex')  #rd 1

def make_mscan_result():
    pattern_addr_add('00000000', '007fff00', 'w', 'mscan_result.hex')  #rd 00
    pattern_addr_add('000000ff', '007fffff', 'a', 'mscan_result.hex')  #rd ff

# Checkboard
def make_checkerboard_pattern():
    checkerboard_wr00ff('checkerboard.hex', 0x02000000, 0x027fffff, 'w')  # wr 00 ff
    pattern_addr_add('03000000', '037fff00', 'a', 'checkerboard.hex')      # rd 00 ff
    checkerboard_wrff00('checkerboard.hex', 0x020000ff, 0x027fff00, 'a')  # wr ff 00
    pattern_addr_add('03000000', '037fff00', 'a', 'checkerboard.hex')      # rd ff 00

def make_checkerboard_result():
    checkerboard_wr00ff('checkerboard_result.hex', 0x00000000, 0x007fffff, 'w')  # rd 00 ff
    checkerboard_wrff00('checkerboard_result.hex', 0x000000ff, 0x007fff00, 'a')  # rd ff 00
    
# MATS
def make_mats_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'mats.hex')  #wr 00
    make_mix_pattern_2step('03', '00', '02', 'ff', 'a', 'mats.hex') # rd 00 wr ff
    pattern_addr_sub('037fff00', '03000000', 'a', 'mats.hex') # rd ff 

def make_mats_pattern_result():
    pattern_addr_add('00000000', '007fff00', 'w', 'mats_result.hex')  #rd 00
    pattern_addr_sub('007fffff', '000000ff', 'a', 'mats_result.hex') # rd ff 

# MATS+ (matsp)plus
def make_matsp_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'mats+.hex')  #wr 00
    make_mix_pattern_2step('03', '00', '02', 'ff', 'a', 'mats+.hex') # rd 00 wr ff
    make_mix_pattern_2step_sub('03', '00', '02', '00', 'a', 'mats+.hex') # rd ff wr 00

def make_matsp_pattern_result():
    pattern_addr_add('00000000', '007fff00', 'w', 'mats+_result.hex')  #rd 00
    pattern_addr_sub('007fffff', '000000ff', 'a', 'mats+_result.hex') # rd ff 

# MATS++ (matspp)plus plus
def make_matspp_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'mats++.hex')  #wr 00
    make_mix_pattern_2step('03', '00', '02', 'ff', 'a', 'mats++.hex') # rd 00 wr ff
    make_mix_pattern_3step_sub('03', '00', '02', '00', '03', '00','a', 'mats++.hex') # rd ff wr 00 rd 00

def make_matspp_pattern_result():
    pattern_addr_add('00000000', '007fff00', 'w', 'mats++_result.hex')  #rd 00
    make_mix_pattern_2step_sub('00', 'ff', '00', '00', 'a', 'mats++_result.hex') # rd ff rd 00

# March A
def make_marchA_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'March_A.hex')  #wr 00
    make_mix_pattern_4step('03', '00', '02', 'ff', '02', '00', '02', 'ff', 'a', 'March_A.hex') # rd 00 wr ff wr 00 wr ff
    make_mix_pattern_3step('03', '00', '02', '00', '02', 'ff', 'a', 'March_A.hex') # rd ff wr 00 wr ff
    make_mix_pattern_4step_sub('03', '00', '02', '00', '02', 'ff', '02', '00', 'a', 'March_A.hex') 
    make_mix_pattern_3step_sub('03', '00', '02', 'ff', '02', '00', 'a', 'March_A.hex')

def make_marchA_pattern_result():
    pattern_addr_add('00000000', '007fff00', 'w', 'March_A_result.hex')  #rd 00
    pattern_addr_add('000000ff', '007fffff', 'a', 'March_A_result.hex')  #rd ff
    pattern_addr_sub('007fffff', '000000ff', 'a', 'March_A_result.hex') # rd ff
    pattern_addr_sub('007fff00', '00000000', 'a', 'March_A_result.hex') # rd 00

# March B
def make_marchB_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'March_B.hex')  #wr 00

# March C
def make_marchC_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'March_C.hex')  #wr 00
    make_mix_pattern_2step('03', '00', '02', 'ff', 'a', 'March_C.hex') # rd 00 wr ff
    make_mix_pattern_2step('03', '00', '02', '00', 'a', 'March_C.hex')
    pattern_addr_add('03000000', '037fff00', 'a', 'March_C.hex')  #rd 0
    make_mix_pattern_2step_sub('03', '00', '02', 'ff', 'a', 'March_C.hex') # rd 00 wr ff
    make_mix_pattern_2step_sub('03', '00', '02', '00', 'a', 'March_C.hex')
    pattern_addr_add('03000000', '037fff00', 'a', 'March_C.hex')  #rd 0

def make_marchC_pattern_result():
    pattern_addr_add('00000000', '007fff00', 'w', 'March_C_result.hex')  #rd 00
    pattern_addr_add('000000ff', '007fffff', 'a', 'March_C_result.hex')  #rd ff
    pattern_addr_add('00000000', '007fff00', 'a', 'March_C_result.hex')  #rd 00
    pattern_addr_sub('007fff00', '00000000', 'a', 'March_C_result.hex')  #rd 00
    pattern_addr_sub('007fffff', '000000ff', 'a', 'March_C_result.hex')  #rd ff
    pattern_addr_add('00000000', '007fff00', 'a', 'March_C_result.hex')  #rd 00

# March C- (mins)
def make_marchCm_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'March_C-.hex')  #wr 00
    make_mix_pattern_2step('03', '00', '02', 'ff', 'a', 'March_C-.hex') # rd 00 wr ff
    make_mix_pattern_2step('03', '00', '02', '00', 'a', 'March_C-.hex')
    # pattern_addr_add('03000000', '037fff00', 'a', 'March_C.hex')  #rd 0
    make_mix_pattern_2step_sub('03', '00', '02', 'ff', 'a', 'March_C-.hex') # rd 00 wr ff
    make_mix_pattern_2step_sub('03', '00', '02', '00', 'a', 'March_C-.hex')
    pattern_addr_add('03000000', '037fff00', 'a', 'March_C-.hex')  #rd 0

def make_marchCm_pattern_result():
    pattern_addr_add('00000000', '007fff00', 'w', 'March_C-_result.hex')  #rd 00
    pattern_addr_add('000000ff', '007fffff', 'a', 'March_C-_result.hex')  #rd ff
    # pattern_addr_add('00000000', '007fff00', 'a', 'March_C_result.hex')  #rd 00
    pattern_addr_sub('007fff00', '00000000', 'a', 'March_C-_result.hex')  #rd 00
    pattern_addr_sub('007fffff', '000000ff', 'a', 'March_C-_result.hex')  #rd ff
    pattern_addr_add('00000000', '007fff00', 'a', 'March_C-_result.hex')  #rd 00

# March C+ (plus)
def make_marchCp_pattern():
    pattern_addr_add('02000000', '027fff00', 'w', 'March_C+.hex')  #wr 00
    make_mix_pattern_3step('03', '00', '02', 'ff', '03', '00', 'a', 'March_C+.hex') # rd 00 wr ff rd ff
    make_mix_pattern_3step('03', '00', '02', '00', '03', '00', 'a', 'March_C+.hex')

    make_mix_pattern_3step_sub('03', '00', '02', 'ff', '03', '00', 'a', 'March_C+.hex') # rd 00 wr ff
    make_mix_pattern_3step_sub('03', '00', '02', '00', '03', '00', 'a', 'March_C+.hex')
    pattern_addr_add('03000000', '037fff00', 'a', 'March_C+.hex')  #rd 0

def make_marchCp_pattern_result():
    make_mix_pattern_2step('00', '00', '00', 'ff', 'w', 'March_C+_result.hex') # rd 00 rd ff
    make_mix_pattern_2step('00', 'ff', '00', '00', 'a', 'March_C+_result.hex') # rd ff rd 00
    make_mix_pattern_2step_sub('00', '00', '00', 'ff', 'a', 'March_C+_result.hex') # rd 00 rd ff
    make_mix_pattern_2step_sub('00', 'ff', '00', '00', 'a', 'March_C+_result.hex') # rd ff rd 00
    pattern_addr_add('00000000', '007fff00', 'a', 'March_C+_result.hex')  #rd 00





#-------------------------------------------------------------main---------------------------------------------------------#

if __name__ == "__main__":

    # parameter: (start_hex, end_hex, txt_mode, txt_name)
    # function select: add / sub
    # w：重新覆盖写   a：原有基础上继续写

    # # MSCAN pattern
    # make_mscan_pattern()
    # make_mscan_result()

    # # Checkerboard pattern
    # make_checkerboard_pattern()
    # make_checkerboard_result()

    # # MATS pattern
    # make_mats_pattern()
    # make_mats_pattern_result()

    # # MATS+ pattern
    # make_matsp_pattern()
    # make_matsp_pattern_result()

    # # MATS++ pattern
    # make_matspp_pattern()
    # make_matspp_pattern_result()

    # # March_A pattern
    # make_marchA_pattern()
    # make_marchA_pattern_result()

    # # March_C pattern
    # make_marchC_pattern()
    # make_marchC_pattern_result()

    # # March_C- pattern
    # make_marchCm_pattern()
    # make_marchCm_pattern_result()

    # # March_C+ pattern
    # make_marchCp_pattern()
    # make_marchCp_pattern_result()

    print('make pattern ok')
