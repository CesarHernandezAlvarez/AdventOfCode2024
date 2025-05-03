#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <filesystem>

int main() {
    std::string txtFileName;
    std::cout << "Enter the name of the .txt file to read (suggestion: input_day03.txt): ";
    std::getline(std::cin, txtFileName);

    if (!std::filesystem::exists(txtFileName)) {
        std::cerr << "Error: File '" << txtFileName << "' not found.\n";
        return 1;
    }

    std::ifstream file(txtFileName);
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::regex do_dont_pattern(R"(do\(\)|don't\(\))");

    std::string part;
    std::cout << "Which part do you want to run? (1 or 2): ";
    std::getline(std::cin, part);

    if (part == "1") {
        // Part 1
        int resultMul = 0;
        std::sregex_iterator it(text.begin(), text.end(), mul_pattern);
        std::sregex_iterator end;
        for (; it != end; ++it) {
            int x = std::stoi((*it)[1]);
            int y = std::stoi((*it)[2]);
            resultMul += x * y;
        }
        std::cout << "The sum of all the multiplications is: " << resultMul << "\n";
    }
    else if (part == "2") {
        // Part 2
        int resultMul = 0;
        bool enabled = true;

        std::sregex_token_iterator token_it(text.begin(), text.end(), do_dont_pattern, {-1, 0});
        std::sregex_token_iterator end;
        for (; token_it != end; ++token_it) {
            std::string segment = token_it->str();
            if (segment == "do()") {
                enabled = true;
                continue;
            } else if (segment == "don't()") {
                enabled = false;
                continue;
            }

            if (enabled) {
                std::sregex_iterator match_it(segment.begin(), segment.end(), mul_pattern);
                std::sregex_iterator match_end;
                for (; match_it != match_end; ++match_it) {
                    int x = std::stoi((*match_it)[1]);
                    int y = std::stoi((*match_it)[2]);
                    resultMul += x * y;
                }
            }
        }
        std::cout << "The sum of all the multiplications is: " << resultMul << "\n";
    }
    else {
        std::cout << "Invalid selection. Please enter 1 or 2.\n";
    }

    std::cout << "\nPress Enter to exit.";
    std::cin.get();
    return 0;
}
