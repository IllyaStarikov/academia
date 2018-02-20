//
//  functions.cpp
//  cs5201 - Numerical Modeling
//
//  Created by Illya Starikov on 01/29/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "functions.h"

void ensureEnoughArguments(const int argc) {
    if (argc < 2) {
        displayErrorAndQuit("Not enough parameters. Terminating.");
    }
}

void displayErrorAndQuit(const std::string& output) {
    std::cerr << output << std::endl;
    exit(-1);
}

int stringToInt(const std::string& someString) {
    return std::stoi(someString); // stoi is just not descriptive enough for me.
}

double stringToDouble(const std::string& someString) {
    // stod  is just not descriptive enough for me.
    // and it sounds like an noun...
    return std::stod(someString);
}


std::vector<std::string> split(const std::string& someString, const char delimiter) {
    auto stream = std::stringstream(someString);
    std::string segment;
    std::vector<std::string> splitText;

    while(std::getline(stream, segment, delimiter)) {
       splitText.push_back(segment);
    }

    return splitText;
}


bool fileExists(const std::string& filename) {
    // is_regular_file because exists checks for files and directories
    return filesystem::exists(filename) && filesystem::is_regular_file(filename);
}

std::string readFile(const filesystem::path& path) {
    const auto size = filesystem::file_size(path);

    std::ifstream fin{ path };
    std::string contents(size, ' ');

    fin.read(contents.data(), size);
    fin.close();

    return contents;
}

std::string readInputFile(const std::string& filename) {
    if (!fileExists(filename)) {
        // I miss String.Format :(
        displayErrorAndQuit("File " + filename + " does not exists. Terminating.");
    }

    auto fileContents = readFile(filename);
    auto stringStream = std::ostringstream();

    auto FLOAT        = R"([-+]?[0-9]*\.?[0-9]*)";
    auto WHITESPACE   = R"(\s*)";

    stringStream << "(" << FLOAT << WHITESPACE << "*)*";

    auto regexString = stringStream.str();
    auto regex       = std::regex(regexString);
    auto match       = std::smatch();

    if (!std::regex_search(fileContents, match, regex)) {
        displayErrorAndQuit("Data is not in proper format. Terminating.");
    }

    return fileContents;
}
