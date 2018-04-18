//
//  functions.cpp
//  src
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

#include "functions.h"

/**
 *  @brief Ensures there are enough parameters for the main function.
 *
 *  @param argc The number of parameters passed into main (typically named
 *         @p argc).
 *
 *  @warning Because the number of parameters is *critical* for the program
 *         functioning correctly, if there are not enough parameters, the
 *         program will terminate prematurely and print out the error to
 *         `stderr`.
 *
 *  @pre    @p argc must at least 2.
 *  @post   See `warning`
 **/
void ensureEnoughArguments(const int argc) {
    if (argc < 1) {
        displayErrorAndQuit("Not enough parameters. Terminating.");
    }
}

/**
 *  @brief Feed an error to `stderr`, and terminate the program.
 *
 *  @warning This does terminate the program prematurely, meaning all subsequent
 *         after this function call will be ignored.
 *
 *  @pre   None.
 *  @post  See `warning`.
 **/
void displayErrorAndQuit(const std::string& output) {
    std::cerr << output << std::endl;
    exit(-1);
}

/**
 *  @brief Converts a string to an integer.
 *
 *  @param someString The string to convert to an `int`. Note that if
 *  `someString` cannot explicitly be converted to an `int`, i.e., if
 *  ```
 *  stringToInt("forty-two"); // invalid
 *  stringToInt("forty-two-42"); // invalid
 *  stringToInt(""); // invalid
 *  stringToInt(".0"); // invalid
 *  ```
 *  an exception will be thrown.
 *
 *  @throws  InvalidArgument If the string cannot be converted to an `int`.
 *
 *  @return `someString` converted to an `int`.
 *
 *  @pre   See @p someString.
 *  @post  See `return`.
 **/
int stringToInt(const std::string& someString) {
    return std::stoi(someString); // stoi is just not descriptive enough for me.
}

/**
 *  @brief Converts a string to an integer.
 *  @param someString The string to convert to a `float`. Note that if
 *  `someString` cannot explicitly be converted to an `float`, i.e., if
 *  ```
 *  stringToInt("forty-two-dot-two"); // invalid
 *  stringToInt("forty-two-0.0"); // invalid
 *  stringToInt(""); // invalid
 *  stringToInt(".0"); // invalid
 *  ```
 *  an exception will be thrown.
 *  @return `someString` converted to an `float`.
 *
 *  @throws  InvalidArgument If the string cannot be converted to an `double`.
 *
 *  @pre   See @p someString.
 *  @post  See `return`.
 **/
double stringToDouble(const std::string& someString) {
    // stod  is just not descriptive enough for me.
    // and it sounds like an noun...
    return std::stod(someString);
}

/**
 *  @brief Split the input at @p delimiter (if multiple `delimiter`s) into
 *  multiple strings.
 *
 *  @param someString The spring that is to be split into multiple strings.
 *  @param delimiter The `char` that @p someString will be split at.
 *
 *  @return A `vector` with whose entries are associated with both sides of
 *  the string after removing @p delimiter and appending the left and right
 *  hand side of the split.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/

std::vector<std::string> split(const std::string& someString, const char delimiter) {
    auto stream = std::stringstream(someString);
    std::string segment;
    std::vector<std::string> splitText;

    while(std::getline(stream, segment, delimiter)) {
       splitText.push_back(segment);
    }

    return splitText;
}

/**
 *  @brief Determines if a file exists a specified path.
 *  @param filename The full or relative path where to check if a file
 *        exists.
 *  @return `true` if the file exists, `false` otherwise.
 *
 *  @pre   None.
 *  @post  See `return`
 **/
bool fileExists(const std::string& filename) {
    // is_regular_file because exists checks for files and directories
    return filesystem::exists(filename) && filesystem::is_regular_file(filename);
}

/**
 *  @brief Read into a `std::string` from a specified file.
 *
 *  @param path The path where file is to be read from. Can
 *         be relative or absolute.
 *
 *  @return An `std::string` with the entirety of the file contents
 *          in them (`n` and all).
 *
 *
 *  @pre  Check `warning`.
 *  @post See `return`.
 **/
std::string readFile(const filesystem::path& path) {
    const auto size = filesystem::file_size(path);

    std::ifstream fin{ path };
    std::string contents(size, ' ');

    fin.read(contents.data(), size);
    fin.close();

    return contents;
}

/**
 *  @brief Read the specified input file and ensure proper
 *         data format.
 *
 *  @param filename The filename where file is to be read from. Can
 *         be relative or absolute.
 *
 *  @return An `std::string` with the entirety of the file contents
 *          in them (`n` and all).
 *
 *  @warning This does terminate prematurely if the file contents is not
 *        in the proper format.
 *
 *  @pre  Check `warning`.
 *  @post See `return`.
 **/
std::string readInputFile(const std::string& filename) {
    if (!fileExists(filename)) {
        // I miss String.Format :(
        displayErrorAndQuit("File " + filename + " does not exists. Terminating.");
    }

    auto fileContents = readFile(filename);
    auto stringStream = std::ostringstream();

    auto DIGIT         = R"(\d+)";
    auto FLOAT         = R"(-?\d+\.\d+)";
    auto SPACE         = R"(\s)";
    auto NEWLINE       = R"(\n)";

    stringStream << DIGIT << NEWLINE << "(" << FLOAT << SPACE << ")+";

    auto regexString = stringStream.str();
    auto regex       = std::regex(regexString);

    if (!std::regex_search(fileContents, regex)) {
        displayErrorAndQuit("Data is not in proper format. Terminating.");
    }

    return fileContents;
}

/**
 *  @brief Parse out points from @p fileContents.
 *
 *  @param fileContents The string to parse the Polar Pairs from. This is
 *         intended to have the `\n` and all.
 *
 *  @warning This will throw if fileContents is not in the proper.
 *
 *
 *  @return A `std::vector` of points of the form (x, y).
 *
 *  @pre  See `warning`.
*   @post See `return`.
**/
std::pair<SymmetricMatrix<double>, Vector<double>> parseFileContents(const std::string& fileContents) {
    auto inputSplit = split(fileContents, '\n');
    std::remove_if(inputSplit.begin(), inputSplit.end(), [](std::string string) { return string == "" || string == "\t"; });

    size_t dimension = stringToInt(inputSplit[0]);

    auto aMatrix = SymmetricMatrix<double>(dimension, dimension);
    auto bVector = Vector<double>(dimension);

    for (unsigned i = 1; i < dimension + 1; i++) {
        auto line = inputSplit[i];

        auto rowVector = split(line, ' ');
    std::remove_if(rowVector.begin(), rowVector.end(), [](std::string string) { return string == "" || string == "\t"; });

        for (unsigned j = 0; j < dimension; j++) {
            aMatrix(i - 1, j) = stringToDouble(rowVector[j]);
        }
    }


    auto line = inputSplit[dimension + 1];
    auto rowVector = split(line, ' ');
    std::remove_if(rowVector.begin(), rowVector.end(), [](std::string string) { return string == "" || string == "\t"; });

    for (unsigned i = 0; i < dimension; i++) {
        bVector[i] = stringToDouble(rowVector[i]);
    }

    return std::make_pair(aMatrix, bVector);
}
