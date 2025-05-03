#!/usr/bin/env python
# coding: utf-8

import re
import os

txtFileName = input("Enter the name of the .txt file to read (suggestion: input_day03.txt): ").strip()
if not os.path.exists(txtFileName):
    print(f"Error: File '{txtFileName}' not found.")
    exit(1)

with open(txtFileName, "r") as file:
    text = file.read()

mul = r"mul\((\d{1,3}),(\d{1,3})\)"

part = input("Which part do you want to run? (1 or 2): ").strip()

if part == "1":
    # Part 1
    matches = re.findall(mul, text)
    resultMul = sum(int(x) * int(y) for x, y in matches)
    print("The sum of all the multiplications is: {}".format(resultMul))
elif part == "2":
    # Part 2
    enabled = True
    resultMul = 0
    sections = re.split(r"(do\(\)|don\'t\(\))", text)
    
    for section in sections:
        if 'do()' in section:
            enabled = True
        elif 'don\'t()' in section:
            enabled = False

        for match in re.findall(mul,section):
            x,y = match
            if enabled:
                resultMul += int(x)*int(y)
    print("The sum of all the multiplications is: {}".format(resultMul))
else:
    print("Invalid selection. Please enter 1 or 2.")

input("\nPress Enter to exit.")