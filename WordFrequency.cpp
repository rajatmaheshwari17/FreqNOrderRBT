#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Could not open input file." << std::endl;
        return 1;
    }

    Dictionary dict;
    std::string line;

    std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    while (getline(inFile, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of(delim, prev)) != std::string::npos) {
            if (pos > prev) {
                std::string word = line.substr(prev, pos - prev);
                if (dict.contains(word)) {
                    dict.getValue(word) += 1;
                } else {
                    dict.setValue(word, 1);
                }
            }
            prev = pos + 1;
        }

        if (prev < line.length()) {
            std::string word = line.substr(prev, std::string::npos);
            if (dict.contains(word)) {
                dict.getValue(word) += 1;
            } else {
                dict.setValue(word, 1);
            }
        }
    }

    inFile.close();

    std::ofstream outFile(argv[2]);
    if (!outFile) {
        std::cerr << "Could not open output file." << std::endl;
        return 1;
    }

    outFile << dict;

    outFile.close();

    return 0;
}
