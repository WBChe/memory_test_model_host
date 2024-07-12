def reverse_elements_in_list(lst):
    return [element[::-1] for element in lst]

def swap_characters(s):
    if len(s) < 2:
        return s
    else:
        swapped = s[1] + s[0] + swap_characters(s[2:])
        return swapped

def swap_characters_in_list(lst):
    return [swap_characters(element) for element in lst]

def hex_to_bin(hex_file, bin_file):
    with open(hex_file, 'r') as f:
        lines = f.readlines()

    # 去除列表中每个元素最后一个字符 /n
    modified_lines = [x[:-1] for x in lines]
    # 列表中每个元素倒序排列
    reversed_list = reverse_elements_in_list(modified_lines)
    # 列表中每个元素的字符两两交换
    swapped_list = swap_characters_in_list(reversed_list)
    # add : 每个元素最前面添加:
    list1 = [':' + item for item in swapped_list]

    data = []
    for line in list1:
        if line.startswith(':'):    # remove :
            # line = line.strip()
            data += [int(line[i:i + 2], 16) for i in range(1, len(line), 2)]

    with open(bin_file, 'wb') as f:
        f.write(bytearray(data))

    print(f'Hex file "{hex_file}" converted to bin file "{bin_file}".')


# 使用示例 main
hex_file = '/home/cwb/work_py/make_pattern/mscan_result.hex'
bin_file = '/home/cwb/work_py/make_pattern/mscan_result.bin'
hex_to_bin(hex_file, bin_file)


print("hex2bin done")

