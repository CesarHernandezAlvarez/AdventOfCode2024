#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>

bool is_sorted_or_reverse(const std::vector<int>& report) {
    return std::is_sorted(report.begin(), report.end()) || std::is_sorted(report.rbegin(), report.rend());
}

bool all_differences_less_than_4(const std::vector<int>& report) {
    for (size_t i = 0; i < report.size() - 1; ++i) {
        int diff = std::abs(report[i] - report[i + 1]);
        if (diff <= 0 || diff >= 4)
            return false;
    }
    return true;
}

int main() {
    std::string txtFileName;
    std::cout << "Enter the name of the .txt file to read (suggestion: input_day02.txt): ";
    std::getline(std::cin, txtFileName);

    if (!std::filesystem::exists(txtFileName)) {
        std::cerr << "Error: File '" << txtFileName << "' not found.\n";
        return 1;
    }

    std::string csvFileName = txtFileName;
    size_t pos = csvFileName.find(".txt");
    if (pos != std::string::npos) {
        csvFileName.replace(pos, 4, ".csv");
    }

    std::ifstream inputFile(txtFileName);
    std::ofstream outputFile(csvFileName);
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;
        bool first = true;
        while (iss >> token) {
            if (!first) outputFile << ",";
            outputFile << token;
            first = false;
        }
        outputFile << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::vector<std::vector<int>> reportsList;
    std::ifstream file(csvFileName);
    while (std::getline(file, line)) {
        std::vector<int> report;
        std::stringstream ss(line);
        std::string num;
        while (std::getline(ss, num, ',')) {
            report.push_back(std::stoi(num));
        }
        reportsList.push_back(report);
    }

    std::string part;
    std::cout << "Which part do you want to run? (1 or 2): ";
    std::getline(std::cin, part);

    if (part == "1") {
        int safeReports = 0;
        for (const auto& report : reportsList) {
            if (is_sorted_or_reverse(report) && all_differences_less_than_4(report)) {
                safeReports++;
            }
        }
        std::cout << "The number of safe reports are: " << safeReports << "\n";
    } else if (part == "2") {
        int safeReports = 0;
        for (const auto& report : reportsList) {
            if (is_sorted_or_reverse(report) && all_differences_less_than_4(report)) {
                safeReports++;
                continue;
            }
            for (size_t i = 0; i < report.size(); ++i) {
                std::vector<int> temp(report);
                temp.erase(temp.begin() + i);
                if (is_sorted_or_reverse(temp) && all_differences_less_than_4(temp)) {
                    safeReports++;
                    break;
                }
            }
        }
        std::cout << "The number of safe reports using the Problem Dampener are: " << safeReports << "\n";
    } else {
        std::cout << "Invalid selection. Please enter 1 or 2.\n";
    }

    std::cout << "\nPress Enter to exit.";
    std::cin.get();
    return 0;
}
