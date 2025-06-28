#ifndef TRIANGLEPRINTER_H
#define TRIANGLEPRINTER_H 

// http://www.cplusplus.com/reference/vector/vector/
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

class TrianglePrinter
{
  public:
    // Create a TrianglePrinter with one empty row
    TrianglePrinter(): rows(1) {}

    // Print out the current triangle
    // Pre: Rows must be vaguely triangle-shaped (go from smallest to largest)
    // Post: Triangle is printed to STDOUT
    void print();

    // Add a new element to the current row
    void add(unsigned long n);

    // Create a new row
    void newrow();

  private:
    vector<vector<unsigned long> > rows;
};

#endif
