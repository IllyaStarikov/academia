#include "TrianglePrinter.h"

void TrianglePrinter::print()
{
  // Delete blank rows
  while(rows.back().size() == 0)
  {
    rows.pop_back();
  }

  // Calculate maximum line length
  unsigned int maxlen = 0;
  for(unsigned int i = 0; i < rows.back().size(); i++)
  {
    stringstream ss; 
    ss << rows.back()[i];
    if(maxlen < ss.str().length()) 
    {
      maxlen = ss.str().length();
    }
  }

  maxlen = (maxlen + 2) * rows.back().size() + maxlen;

  // Print out each line
  for(unsigned int i = 0; i < rows.size(); i++)
  {
    unsigned int maxspaces = maxlen / (rows[i].size() + 1); // Split line into n + 1 segments
    unsigned int extraidx = rows[i].size() + 1 - maxlen % (rows[i].size() + 1); // Index after which to add extra spaces

    unsigned int lastlen = 0;

    for(unsigned int j = 0; j < rows[i].size(); j++)
    {
      stringstream ss;
      ss << rows[i][j];

      unsigned int spaces = maxspaces;
      spaces -= ceil(ss.str().length()/2.0); // Remove half the space this element will take up
      spaces -= floor(lastlen/2.0); // Remove half the space the last element took up

      if(j >= extraidx) { // Account for spaces that would otherwise be lost
        spaces++;
      }

      for(unsigned int k = 0; k < spaces; k++)
      {
        cout << " ";
      }

      cout << ss.str();

      lastlen = ss.str().length();
    }

    cout << endl;
  }
}

void TrianglePrinter::add(unsigned long n)
{
  rows.back().push_back(n);
}

void TrianglePrinter::newrow()
{
  vector<unsigned long> row;
  rows.push_back(row);
}
