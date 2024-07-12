
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
# def make_mats_pattern():


#-------------------------------------------------------------main---------------------------------------------------------#

if __name__ == "__main__":

    # parameter: (start_hex, end_hex, txt_mode, txt_name)
    # function select: add / sub
    # w：重新覆盖写   a：原有基础上继续写

    # MSCAN pattern
    # make_mscan_pattern()
    # make_mscan_result()

    # Checkerboard pattern
    make_checkerboard_pattern()
    make_checkerboard_result()

    print('make pattern ok')
