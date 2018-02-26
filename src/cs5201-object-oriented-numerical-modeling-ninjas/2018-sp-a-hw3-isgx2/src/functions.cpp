//
//  functions.cpp
//  src
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
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

    auto FLOAT         = R"(([-+]?[0-9]*\.?[0-9]*))";
    auto DIGIT         = R"(\d+)";
    auto WHITESPACE    = R"(\s+)";
    auto SPACE         = R"([\t ]*)";
    auto NEWLINE       = R"(\n)";

    stringStream << DIGIT << NEWLINE << "(" << FLOAT << WHITESPACE << FLOAT << SPACE << NEWLINE  << ")+" << FLOAT << WHITESPACE <<  FLOAT << NEWLINE;

    auto regexString = stringStream.str();
    auto regex       = std::regex(regexString);

    if (!std::regex_search(fileContents, regex)) {
        displayErrorAndQuit("Data is not in proper format. Terminating.");
    }

    return fileContents;
}

std::vector<std::pair<double, double>> parseFileContents(const std::string& fileContents) {
    auto inputSplit = split(fileContents, '\n');
    auto pairs = std::vector<std::pair<double, double>>();

    double x, y;
    std::remove_if(inputSplit.begin(), inputSplit.end(), [](std::string string) { return string == "" || string == "\t"; });

        auto numberOfParameter = stringToInt(inputSplit[0]);

        for (int i = 1; i <= numberOfParameter; i++) {
            auto line = inputSplit[i];

            // Just matches to see if there is no digit behind the decimal point. `stringToDecimal` will throw an exception if this is the case.
            auto nonPaddedZeroRegex = std::regex(R"(((\s|^)[+-]?)\.([0-9]*))");
            auto toReplaceWith = R"($010.$3)";
            line = std::regex_replace(line, nonPaddedZeroRegex, toReplaceWith);

            auto stringStream = std::ostringstream();
            auto FLOAT         = R"(([-+]?[0-9]*\.?[0-9]*))";
            auto WHITESPACE    = R"(\s+)";

            stringStream << FLOAT << WHITESPACE << FLOAT;

            auto regexString = stringStream.str();
            auto regex       = std::regex(regexString);
            auto match       = std::smatch();

            std::regex_search(line, match, regex);

            x = stringToDouble(match[1]);
            y = stringToDouble(match[2]);

            pairs.push_back(std::make_pair(x, y));
        }

        return pairs;
}
