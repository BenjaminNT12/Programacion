

import pandas as pd
from io import StringIO

# data = """
# -2.25330.0127029-0.00543951
# -2.30770.0141329-0.00649435
# -2.361740.0141769-0.00654311
# -2.41540.0140769-0.0066418
# """

with open("/home/nicolas/Github/Programacion/Python/datos4error.txt", "r") as file:
    data = file.read()
# Convert the string to a StringIO object
rows = data.split('\n')

# Open the output file
with open("/home/nicolas/Github/Programacion/Python/datos4processed.txt", "w") as outfile:
    # Print each row
    for row in rows:
        # Find the positions of the dots
        index_minus = 0
        index_dot = 0
        # print(type(row))
        for i in range(2):
            index_minus = row.find('-', index_minus+3)
            if index_minus != -1:
                row = row[:index_minus] + ' ' + row[index_minus:]
                continue
        for i in range(3):
            index_dot = row.find('.', index_dot+5)
            if index_dot != -1:
                row = row[:index_dot-1] + ' ' + row[index_dot-1:]
                continue
        for i in range(2):
            index_minus = row.find('-', index_minus+3)
            if index_minus != -1:
                row = row[:index_minus] + '-' +row[index_minus+2:]
                continue
        print(row)
        # Write the processed row to the output file
        outfile.write(row + '\n')
