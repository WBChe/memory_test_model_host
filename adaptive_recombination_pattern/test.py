import binascii

#compare bin file and output list_compare
def read_bin_file(filename):
    with open(filename, 'rb') as f:
        content = f.read()
    return content

def bin_to_hex(bin_data):
    hex_str = binascii.hexlify(bin_data).decode('utf-8')
    return hex_str

def get_fault_addr(file_result, file_check):
    differences = compare_bin_files(file_result, file_check)
    # 列表中每个元素倒序排列
    reversed_list = reverse_elements_in_list(differences)
    # 列表中每个元素的字符两两交换
    new_compare_data = swap_characters_in_list(reversed_list)
    # 去掉前两个字符和后两个字符
    fault_addr = transform_list(new_compare_data)
    # string 2 int hex
    fault_addr_hex = [int(element, 16) for element in fault_addr]   

    return fault_addr_hex

#remove 2head 2tile
def remove_first_last_two(input_str):
    # 去掉前两个字符和后两个字符
    return input_str[2:-2]

def transform_list(lst):
    transformed_list = [remove_first_last_two(item) for item in lst]
    return transformed_list

def compare_bin_files(file1, file2):
    bin_data1 = read_bin_file(file1)
    bin_data2 = read_bin_file(file2)

    hex_data1 = bin_to_hex(bin_data1)
    hex_data2 = bin_to_hex(bin_data2)

    # Compare every 8 characters (4 bytes) in the hex strings
    index = 0
    differences = []

    while index < len(hex_data1) and index < len(hex_data2):
        if hex_data1[index:index+8] != hex_data2[index:index+8]:
            # differences.append(hex_data1[index:index+8])
            differences.append(hex_data2[index:index+8])
        index += 8

    return differences

#reverse list
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

# get range
def get_label(element):
    # 定义范围和对应的标号
    ranges = get_range_block(0x0000, 0x7fff, 1024)  #----------------------------------------------------------you can change block divide
    print(ranges)
    
    # 遍历范围，查找匹配的标号
    for start, end, label in ranges:
        if start <= element <= end: # detect range
            return label
    
    # 如果没有找到匹配的范围，返回 None 或者其他你认为合适的值
    return None


def get_range_block(start_hex, end_hex, num_parts): 

    # Define the range in hexadecimal
    # start_hex = 0x0000
    # end_hex = 0x7fff

    # # Number of parts to split into
    # num_parts = 1024

    # Convert hexadecimal to decimal for calculations
    start_decimal = int(start_hex)
    end_decimal = int(end_hex)

    # Split the range into parts with start, end, and index
    split_parts = split_range_into_parts(start_decimal, end_decimal, num_parts)

    # Convert the results to the desired output format
    desired_output = [(start, end, index) for (start, end, index) in split_parts]

    return desired_output

# prepare for get range
def split_range_into_parts(start, end, parts):
    # Calculate the step size
    step = (end - start + 1) / parts  # Adding 1 to end makes end inclusive
    
    # Generate the split points
    split_points = []
    current = start
    for i in range(parts):
        start_val = int(current)
        current += step
        end_val = int(current) - 1  # end_val is inclusive
        split_points.append((start_val, end_val, i + 1))  # i + 1 to make index start from 1
    
    return split_points

def get_mutifile_fault(algorithm_name, test_num):
    one_fault_addr_array = [[] for _ in range(test_num)] # creat 2d list
    one_algorithm_fault_block = [] # creat 2d list
    for i in range(0, test_num): # algorithm_num+1
        print('now algorithm is : ' + algorithm_name )   
        algorithm_result_bin = './result/' + algorithm_name +'_result.bin'
        algorithm_check_bin = './check/' + algorithm_name + '_check_' + str(i) + '.bin'

        one_fault_addr_array[i] = get_fault_addr(algorithm_result_bin, algorithm_check_bin)
        print(one_fault_addr_array[i])

        # get block list 
        for elem in one_fault_addr_array[i]:
            label = get_label(elem)     # block decide
            if label is not None:
                one_algorithm_fault_block.append(label)
    
    return one_algorithm_fault_block

def get_muti_algorithm_fault(algorithm_name_list, test_num):
    muti_algorithm_fault_block = []
    for name in algorithm_name_list:
        one_algorithm_fault_block = get_mutifile_fault(name, test_num)
        muti_algorithm_fault_block.append(one_algorithm_fault_block)
    return muti_algorithm_fault_block

algorithm_name = ['MSCAN', 'Checkerboard', 'MATS', 'MATS+', 'MATS++', 'March A', 'March B', 'March C', 'March C-', 'March C+', 'March U', 'March LR', 'March SR', 'March SS']

algorithm_name_list = ['mscan', 'checkerboard']
test_num = 2

muti_algorithm_fault_block = get_muti_algorithm_fault(algorithm_name_list, test_num)
# for name in algorithm_name2:
#     one_algorithm_fault_block = get_mutifile_fault(name, 2)
#     muti_algorithm_fault_block.append(one_algorithm_fault_block)

print(muti_algorithm_fault_block)
print(len(muti_algorithm_fault_block))