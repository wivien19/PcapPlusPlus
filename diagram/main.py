import matplotlib.pyplot as plt

from search import search_structure_name, search_protocol_name, search_structures
from diagram import survey
from parse import list_files, parse_line

if __name__ == '__main__':
    directory_header = '../Packet++/header'
    for file_path in list_files(directory_header):
        protocol_header = search_structure_name(file_path)
        protocol_name = search_protocol_name(file_path)

        if protocol_name != '' and protocol_header is not None and search_structures(file_path) != []:
            with open('output/' + protocol_header + '.txt', 'w', encoding='utf8') as file:
                file.write('protocol name: ' + protocol_name + ';' + '\n')
                file.write(protocol_header + '\n')
            with open('output/' + protocol_header + '.txt', 'a', encoding='utf8') as file:
                for key in search_structures(file_path):
                    file.write(key)
                    file.write('\n')
                    print(key)

    directory = 'output/'

    for file_path in list_files(directory):
        print(file_path)
        protocol_name, datas = parse_line(file_path)
        print(datas)

        survey({protocol_name: list(datas.values())}, list(datas.keys()))
        plt.savefig('diagram/' + protocol_name + '.pdf', format='pdf', bbox_inches="tight")
        plt.show()

    from PyPDF2 import PdfWriter

    merger = PdfWriter()
    directory = 'diagram/'
    for pdf in list(list_files(directory)):
        merger.append(pdf)

    merger.write('all_diagrams.pdf')
    merger.close()
