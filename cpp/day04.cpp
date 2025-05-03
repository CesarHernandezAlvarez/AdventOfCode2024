#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

bool inBounds(int i, int j, int rows, int cols) {
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

int main() {
    std::string txtFileName;
    std::cout << "Enter the name of the .txt file to read (suggestion: input_day04.txt): ";
    std::getline(std::cin, txtFileName);

    if (!std::filesystem::exists(txtFileName)) {
        std::cerr << "Error: File '" << txtFileName << "' not found.\n";
        return 1;
    }

    std::ifstream file(txtFileName);
    std::string line;
    std::vector<std::vector<char>> xmasArray;

    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        xmasArray.push_back(row);
    }
    file.close();

    int rows = xmasArray.size();
    int cols = rows > 0 ? xmasArray[0].size() : 0;

    std::string part;
    std::cout << "Which part do you want to run? (1 or 2): ";
    std::getline(std::cin, part);

    if (part == "1") {
        // Part 1: Search for "XMAS" in 8 directions
        std::vector<std::pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };

        int count = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (xmasArray[i][j] == 'X') {
                    for (const auto& [dx, dy] : directions) {
                        int i1 = i + dx, j1 = j + dy;
                        int i2 = i + 2*dx, j2 = j + 2*dy;
                        int i3 = i + 3*dx, j3 = j + 3*dy;
                        if (inBounds(i1, j1, rows, cols) && xmasArray[i1][j1] == 'M' &&
                            inBounds(i2, j2, rows, cols) && xmasArray[i2][j2] == 'A' &&
                            inBounds(i3, j3, rows, cols) && xmasArray[i3][j3] == 'S') {
                            count++;
                        }
                    }
                }
            }
        }
        std::cout << "The number of all XMAS instances is: " << count << "\n";
    }
    else if (part == "2") {
        // Part 2: Search for symmetric "X-MAS" patterns around an 'A'
        int count = 0;
        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                if (xmasArray[i][j] == 'A') {
                    char nw = xmasArray[i - 1][j - 1];
                    char ne = xmasArray[i - 1][j + 1];
                    char sw = xmasArray[i + 1][j - 1];
                    char se = xmasArray[i + 1][j + 1];

                    bool pattern1 = (nw == 'M' && ne == 'S' && sw == 'M' && se == 'S');
                    bool pattern2 = (nw == 'M' && ne == 'S' && sw == 'S' && se == 'M');
                    bool pattern3 = (nw == 'S' && ne == 'M' && sw == 'S' && se == 'M');
                    bool pattern4 = (nw == 'S' && ne == 'M' && sw == 'M' && se == 'S');

                    if (pattern1 || pattern2 || pattern3 || pattern4) {
                        count++;
                    }
                }
            }
        }
        std::cout << "The number of all X-MAS instances is: " << count << "\n";
    }
    else {
        std::cout << "Invalid selection. Please enter 1 or 2.\n";
    }

    std::cout << "\nPress Enter to exit.";
    std::cin.get();
    return 0;
}
