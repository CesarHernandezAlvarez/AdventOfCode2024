#!/usr/bin/env python
# coding: utf-8

import numpy as np
import os

txtFileName = input("Enter the name of the .txt file to read (suggestion: input_day04.txt): ").strip()
if not os.path.exists(txtFileName):
    print(f"Error: File '{txtFileName}' not found.")
    exit(1)

with open(txtFileName, "r") as file:
    lines = file.readlines()

lines = [list(line.strip()) for line in lines]
xmasArray = np.array(lines)
rows, cols = xmasArray.shape

part = input("Which part do you want to run? (1 or 2): ").strip()

if part == "1":
    # Part 1
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1),(-1, -1), (-1, 1), (1, -1), (1, 1)]
    count = 0

    for i in range(rows):
        for j in range(cols):
            if xmasArray[i, j] == 'X':
                for dx, dy in directions:
                    if (0 <= i + dx < rows and 0 <= j + dy < cols and xmasArray[i + dx, j + dy] == 'M' and
                        0 <= i + 2*dx < rows and 0 <= j + 2*dy < cols and xmasArray[i + 2*dx, j + 2*dy] == 'A' and
                        0 <= i + 3*dx < rows and 0 <= j + 3*dy < cols and xmasArray[i + 3*dx, j + 3*dy] == 'S'):
                        count += 1
    print("The number of all XMAS instances is: {}".format(count))
elif part == "2":
    # Part 2
    count = 0
    for i in range(rows):
        for j in range(cols):
            if xmasArray[i, j] == 'A':
                if (0 <= i - 1 and i + 1 < rows and 0 <= j - 1 and j + 1 < cols): 
                    if ((xmasArray[i-1, j-1] == 'M' and xmasArray[i+1, j+1] == 'S' and xmasArray[i+1, j-1] == 'M' and xmasArray[i-1, j+1] == 'S') or
                        (xmasArray[i-1, j-1] == 'M' and xmasArray[i+1, j+1] == 'S' and xmasArray[i-1, j+1] == 'M' and xmasArray[i+1, j-1] == 'S') or
                        (xmasArray[i-1, j-1] == 'S' and xmasArray[i+1, j+1] == 'M' and xmasArray[i+1, j-1] == 'S' and xmasArray[i-1, j+1] == 'M') or
                        (xmasArray[i-1, j-1] == 'S' and xmasArray[i+1, j+1] == 'M' and xmasArray[i-1, j+1] == 'S' and xmasArray[i+1, j-1] == 'M')):
                        count += 1
    print("The number of all X-MAS instances is: {}".format(count))
else:
    print("Invalid selection. Please enter 1 or 2.")

input("\nPress Enter to exit.")