#include <iostream>
#include <fstream>
#include <string>

#include "Config.h"

//using namespace std;
//
//// writing on a text file
//int main () {
//  ofstream myfile ("example.txt");
//  if (myfile.is_open())
//  {
//    myfile << "This is a line.\n";
//    myfile << "This is another line.\n";
//    myfile.close();
//  }
//  else cout << "Unable to open file";
//  return 0;
//}
//
//// reading a text file
//int main ()
//{
//  string line;
//  ifstream myfile("example.txt");
//
//  if (myfile.is_open())
//  {
//    while(getline(myfile,line))
//    {
//      cout << line << endl;
//    }
//    myfile.close();
//  }
//  else
//	  cout << "Unable to open file"; 
//  return 0;
//}

//int main() {
//  vector<string> v;
//  ifstream in("Fillvector.cpp");
//  string line;
//  while(getline(in, line))
//    v.push_back(line); // Add the line to the end
//  // Add line numbers:
//  for(int i = 0; i < v.size(); i++)
//    cout << i << ": " << v[i] << endl;
//} ///:~