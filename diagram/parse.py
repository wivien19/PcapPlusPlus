import os
import re


def list_files(file_dir):
    return [os.path.join(file_dir, file) for file in os.listdir(file_dir)]


def get_number_of_bits(string):
    number = ''.join(filter(str.isdigit, string))
    return int(number) if number else 0


def parse_line(fil):
    name_size = {}
    protocol_name = ''
    with open(fil, 'r', encoding='utf8') as file:
        for line in file:
            parts = line.strip().split()
            if 'protocol name' in line:
                pattern = r'protocol name: \s*(\w+)\s*;'
                match = re.search(pattern, line)
                protocol_name = match.group(1)

            if 'uint' in line and len(parts) >= 2:
                data_type = parts[0]
                variable_name = parts[1].rstrip(';')
                name_size[variable_name] = get_number_of_bits(data_type)
        return protocol_name, name_size
