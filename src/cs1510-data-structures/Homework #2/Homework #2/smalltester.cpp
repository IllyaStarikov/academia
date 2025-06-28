#include <iostream>
#include "arraylist.h"

using namespace std;

int main () {
  ArrayList<string> start_grid;
  ArrayList<string> race;
  ArrayList<string> retired;
  int ix;
  string s;
  
  cout << "Hello World!!, This is the Small Tester" << endl << endl; 
  
  start_grid.insert_back("Mario");
  start_grid.insert_back("Koopa");
  start_grid.insert_back("Bowser");  
  start_grid.insert_back("Luigi");
  start_grid.insert_back("Toad");
  start_grid.insert_back("DonkeyKong");  
  start_grid.insert_back("P.Peach");
  start_grid.insert_back("Yoshi");
  

  cout << "Starting Grid" << endl;
  cout << start_grid << endl;
  
  race = start_grid;
  
  cout << "After first Lap" << endl;
  cout << race << endl << endl;

  cout << "Bowser drops a Banana" << endl;
  ix = race.find("Bowser");
  race.swap(ix+1, ix+2);
  cout << race << endl << endl;

  cout << "Yoshi takes a Boost Pad" << endl;
  ix = race.find("Yoshi");
  race.swap(ix, ix-1);
  cout << race << endl << endl;
  
  cout << "Luigi uses a red shell" << endl;
  ix = race.find("Luigi");
  race.swap(ix, ix-1);
  cout << race << endl << endl;
  
  cout << "Toad uses a blue shell" << endl; // bug
  s = race.first();
  race.remove(0);
  race.insert(s, 4);
  cout << race << endl << endl;
 
  cout << "P.Peach retires with engine failure" << endl;
  ix = race.find("P.Peach");
  race.remove(ix);
  retired.insert_back("P.Peach");
  cout << race << endl << endl;
 
  cout << "Koopa drops a banana" << endl;
  ix = race.find("Koopa");
  race.swap(ix+1, ix+2);
  cout << race << endl << endl;
 
  cout << "DonkeyKong uses a star" << endl;
  ix = race.find("DonkeyKong");
  race.swap(ix, ((ix-5 < 0)? 0 : ix-5) );
  cout << race << endl << endl;
 
  
  cout << endl;
  cout << "**** RACE RESULTS **** " << endl;
  cout << "Starting Grid:" << endl;
  cout << start_grid << endl << endl;
  cout << "Final Standings:" << endl;
  cout << race << endl << endl;
  cout << "DNF:" << endl;
  cout << retired << endl;
 
  cin.clear ();
  cout << "Press Any Key to Continue" << endl;
  cin.get();
    
  return 0;
}