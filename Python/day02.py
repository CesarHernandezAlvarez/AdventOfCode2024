#!/usr/bin/env python
# coding: utf-8

import numpy as np
import csv
import os

txtFileName = input("Enter the name of the .txt file to read (suggestion: input_day02.txt): ").strip()
if not os.path.exists(txtFileName):
    print(f"Error: File '{txtFileName}' not found.")
    exit(1)

csvFileName = txtFileName.replace(".txt", ".csv")
with open(txtFileName, "r") as inputFile, open(csvFileName, "w") as outputFile:
    for line in inputFile:
        values = line.strip().split()
        outputFile.write(",".join(values) + "\n")

reportsList = []
with open(csvFileName, "r") as file:
    readFile = csv.reader(file)
    for row in readFile:
        reportSingle = [int(x) for x in row]
        reportsList.append(reportSingle)

part = input("Which part do you want to run? (1 or 2): ").strip()

if part == "1":
    # Part 1
    safeReports = sum(all(0 < abs(report[i] - report[i + 1]) < 4 for i in range(len(report) - 1))
                      for report in reportsList if report == sorted(report) or report == sorted(report,reverse=True))
    print("The number of safe reports are: {}".format(safeReports))
elif part == "2":
    # Part 2
    safeReports = 0
    
    for report in reportsList:
        if report == sorted(report) or report == sorted(report, reverse=True):
            if all(0 < abs(report[i] - report[i + 1]) < 4 for i in range(len(report) - 1)):
                safeReports += 1
                continue
        
        for i in range(len(report)):
            temp = report[:i] + report[i+1:]
            if temp == sorted(temp) or temp == sorted(temp, reverse=True):
                if all(0 < abs(temp[j] - temp[j + 1]) < 4 for j in range(len(temp) - 1)):
                    safeReports += 1
                    break
    
    print("The number of safe reports using the Problem Dampener are: {}".format(safeReports))
else:
    print("Invalid selection. Please enter 1 or 2.")

input("\nPress Enter to exit.")