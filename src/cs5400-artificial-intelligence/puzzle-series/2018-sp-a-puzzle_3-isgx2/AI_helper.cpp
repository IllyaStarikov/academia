#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

// This is how you can take arguments from command line with c++
// argv is the number of arguments (including the executable itself)
// argc is the 2D array of characters that stores arguments
//   ./AI_helper puzzle1.txt solution1.txt
//     argv    : 3
//     argc[0] : "./AI_helper"
//     argc[1] : "puzzle1.txt"
//     argc[2] : "solution1.txt" 
int main(int argv, char** argc)
{
  int first;  // variable to store first value in puzzle file
  string PUZZLE_FILE = argc[argv-2];  // puzzle file name
  string SOLUTION_FILE = argc[argv-1];  // solution file name
  ifstream fin; // file input stream
  ofstream fout; // file output stream

  // open puzzle file, get first value in file, and close file
  fin.open(PUZZLE_FILE.c_str());
  fin >> first;
  fin.close();

  // create solution file, output to file, and close file
  fout.open(SOLUTION_FILE.c_str());
  fout << "This is solution file " << SOLUTION_FILE << "\n"
       << "The first value in " << PUZZLE_FILE << " is : " << first << "\n";
  fout.close();

  return 0;
}
