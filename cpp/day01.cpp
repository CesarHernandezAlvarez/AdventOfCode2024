#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>

int main() {
    std::string txtFileName;
    std::cout << "Enter the name of the .txt file to read (suggestion: input_day01.txt): ";
    std::getline(std::cin, txtFileName);

    std::ifstream inputFile(txtFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: File '" << txtFileName << "' not found.\n";
        return 1;
    }

    std::string csvFileName = txtFileName;
    size_t pos = csvFileName.find(".txt");
    if (pos != std::string::npos) {
        csvFileName.replace(pos, 4, ".csv");
    }

    std::ofstream outputFile(csvFileName);
    std::vector<int> array_a, array_b;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int a, b;
        if (iss >> a >> b) {
            outputFile << a << "," << b << "\n";
            array_a.push_back(a);
            array_b.push_back(b);
        }
    }

    inputFile.close();
    outputFile.close();

    std::string part;
    std::cout << "Which part do you want to run? (1 or 2): ";
    std::getline(std::cin, part);

    if (part == "1") {
        std::vector<int> sorted_a = array_a;
        std::vector<int> sorted_b = array_b;
        std::sort(sorted_a.begin(), sorted_a.end());
        std::sort(sorted_b.begin(), sorted_b.end());

        int totalDistance = 0;
        for (size_t i = 0; i < sorted_a.size(); ++i) {
            totalDistance += std::abs(sorted_a[i] - sorted_b[i]);
        }

        std::cout << "The total distance between the lists is: " << totalDistance << "\n";
    } else if (part == "2") {
        int similarityScore = 0;
        for (size_t i = 0; i < array_a.size(); ++i) {
            int count = std::count(array_b.begin(), array_b.end(), array_a[i]);
            similarityScore += array_a[i] * count;
        }

        std::cout << "The similarity score between the lists is: " << similarityScore << "\n";
    } else {
        std::cout << "Invalid selection. Please enter 1 or 2.\n";
    }

    std::cout << "\nPress Enter to exit.";
    std::cin.ignore();

    return 0;
}
