//
//  functions.cpp
//  cs5201 - Numerical Modeling
//
//  Created by Illya Starikov on 01/29/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "functions.h"

bool enoughParametersPassed(const int argc) {
    return argc > 1;
}

void displayErrorAndQuit(const std::string output) {
    std::cout << output << std::endl;
    exit(-1);
}

std::vector<std::pair<double, double>> parseFileContents(const std::string filename) {
    if (!fileExists(filename)) {
        // I miss String.Format :(
        displayErrorAndQuit("File " + filename + " does not exists. Terminating.");
    }

    auto file = readFile(filename);
    auto fileSplitOnNewline = split(file, '\n');
    auto polarPairs = std::vector<std::pair<double, double>>();

    if (fileSplitOnNewline.size() == 0) {
        displayErrorAndQuit("File " + filename + " is empty. Nice try, Nathan. Terminating.");
    } else {
        try {
            auto numberOfParameter = stringToInt(fileSplitOnNewline[0]);

            // Static cast to get ride of unsigned int/int comparison warning
            if (numberOfParameter < static_cast<int>(fileSplitOnNewline.size()) - 1) {
                displayErrorAndQuit("Not enough polar pairs in input file. Terminating.");
            } else if (numberOfParameter < 0) {
                displayErrorAndQuit("Number of polar pairs cannot be negative. Terminating.");
            }

            for (int i = 1; i < numberOfParameter; i++) {
                auto inputSplit = split(fileSplitOnNewline[i], ' ');

                if (inputSplit.size() < 2) throw std::logic_error("Freaking too little input");

                auto pair = std::make_pair(stringToDouble(inputSplit[0]), stringToDouble(inputSplit[1]));
                polarPairs.push_back(pair);
            }
        } catch(const std::logic_error error) {
            displayErrorAndQuit("Data is not in proper format. Terminating.");
        }
    }

    return polarPairs;
}

int stringToInt(const std::string someString) {
    return std::stoi(someString); // stoi is just not descriptive enough for me.
}

double stringToDouble(const std::string someString) {
    // stod  is just not descriptive enough for me.
    // and it sounds like an noun...
    return std::stod(someString);
}

std::vector<std::string> split(const std::string someString, const char delimiter) {
    auto stream = std::stringstream(someString);
    std::string segment;
    std::vector<std::string> splitText;

    while(std::getline(stream, segment, delimiter)) {
       splitText.push_back(segment);
    }

    return splitText;
}


bool fileExists(const std::string filename) {
    // is_regular_file because exists checks for files and directories
    return filesystem::exists(filename) && filesystem::is_regular_file(filename);
}

std::string readFile(filesystem::path path) {
    const auto size = filesystem::file_size(path);

    std::ifstream fin{ path };
    std::string contents(size, ' ');

    fin.read(contents.data(), size);
    fin.close();

    return contents;
}

