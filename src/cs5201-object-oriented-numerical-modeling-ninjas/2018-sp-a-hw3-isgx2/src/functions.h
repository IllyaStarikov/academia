//
//  functions.h
//  src
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

/** @file */

#ifndef functions_h
#define functions_h

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <algorithm>

namespace filesystem = std::experimental::filesystem;

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
void ensureEnoughArguments(const int argc);

/**
 *  @brief Feed an error to `stderr`, and terminate the program.
 *
 *  @warning This does terminate the program prematurely, meaning all subsequent
 *         after this function call will be ignored.
 *
 *  @pre   None.
 *  @post  See `warning`.
 **/
void displayErrorAndQuit(const std::string& output);

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
std::vector<std::string> split(const std::string& someString, const char delimiter);

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
 *  @return `someString` converted to an `int`.
 *
 *  @pre   See @p someString.
 *  @post  See `return`.
 **/
int stringToInt(const std::string& someString);

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
 *  @pre   See @p someString.
 *  @post  See `return`.
 **/
double stringToDouble(const std::string& someString);

/**
 *  @brief Determines if a file exists a specified path.
 *  @param filename The full or relative path where to check if a file
 *        exists.
 *  @return `true` if the file exists, `false` otherwise.
 *
 *  @pre   None.
 *  @post  See `return`
 **/
bool fileExists(const std::string& filename);

/**
 *  @brief Read into a `std::string` from a specified file.
 *
 *  @param path The path where file is to be read from. Can
 *         be relative or absolute.
 *
 *  @return An `std::string` with the entirety of the file contents
 *          in them (`n` and all).
 *
 *  @warning This does throw an exception if the file does not exist.
 *
 *  @pre  Check `warning`.
 *  @post See `return`.
 **/
std::string readFile(const filesystem::path& path);

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
std::string readInputFile(const std::string& filename);

/**
 *  @brief Parse out points from @p fileContents.
 *
 *  @param fileContents The string to parse the Polar Pairs from. This is
 *         intended to have the `\n` and all.
 *
 *  @warning This will throw if fileContents is not in the proper.
 *
 *  @return A `std::vector` of points of the form (x, y).
 *
 *  @pre  See `warning`.
*   @post See `return`.
**/
std::vector<std::pair<double, double>> parseFileContents(const std::string& fileContents);

#endif /* functions_h */

