#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open input file " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Could not open output file " << argv[2] << std::endl;
        return 1;
    }

    Dictionary dict;
    std::string line;
    int lineNum = 1;

    while (getline(inputFile, line)) {
        dict.setValue(line, lineNum++);
    }

    outputFile << dict;

    outputFile << "\n";

    outputFile << dict.pre_string();

    inputFile.close();
    outputFile.close();

    return 0;
}
