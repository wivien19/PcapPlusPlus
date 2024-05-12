import re


def search_structures(file):
    with open(file, 'r', encoding='utf8') as f:
        content = f.read()
        pattern = r'pragma pack.*?pragma pack'
        matches = re.findall(pattern, content, re.DOTALL)
    return matches


def search_structure_name(file):
    with open(file, 'r', encoding='utf8') as f:
        read_text = f.read()
        pattern = r'struct\s+(\w+)\s*{'
        match = re.search(pattern, read_text)
        if match:
            return match.group(1)
        else:
            pattern = r'}\s*(\w+)\s*;'
            match = re.search(pattern, read_text)
            if match:
                return match.group(1)
            else:
                return None


def search_protocol_name(file_name):
    with open(file_name, 'r', encoding='utf8') as f:
        read_text = f.read()
        pattern = r'class \s*(\w+)\s*:'
        match = re.search(pattern, read_text)
        if match:
            return match.group(1)
        return ''
