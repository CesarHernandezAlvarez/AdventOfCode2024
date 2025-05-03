#!/usr/bin/env python
# coding: utf-8

import numpy as np
import os

txtFileName = input("Enter the name of the .txt file to read(suggestion: input_day01.txt): ").strip()
if not os.path.exists(txtFileName):
    print(f"Error: File '{txtFileName}' not found.")
    exit(1)

csvFileName = txtFileName.replace(".txt", ".csv")
with open(txtFileName, "r") as inputFile, open(csvFileName, "w") as outputFile:
    for line in inputFile:
        values = line.strip().split()
        outputFile.write(",".join(values) + "\n")

data = np.loadtxt("input_day01.csv", delimiter=",", dtype=int)
array_a = data[:,0]
array_b = data[:,1]

part = input("Which part do you want to run? (1 or 2): ").strip()

if part == "1":
    # Part 1
    array_a_sort = np.sort(array_a)
    array_b_sort = np.sort(array_b)
    totalDistance = np.sum(np.abs(array_a_sort-array_b_sort))
    print("The total distance between the lists is: {}".format(totalDistance))
elif part == "2":
    # Part 2
    similarityArray = np.array([np.sum(array_b == x) for x in array_a])
    similarityScore = np.sum(array_a*similarityArray)
    print("The similarity score between the lists is: {}".format(similarityScore))
else:
    print("Invalid selection. Please enter 1 or 2.")

input("\nPress Enter to exit.")