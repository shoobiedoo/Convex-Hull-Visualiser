#include <bits/stdc++.h>
#include <algorithm>
#include <climits>
#include "daa.h"
using namespace std;
//using namespace std::chrono;
#define point pair <double,double>

int mainss(string filename);


int main(int argc, char ** argv) {
int p;
string filename="";
for(p=0;p<strlen(argv[2]);p++)
{
    filename.push_back(argv[2][p]);                                           /// Accepting filename of the file
}

int n;
  vector < point > points;

  ifstream file(filename);
  if (!file) {                                                                  ///Printing error when the file cannot be opened
    cout << "unable to open file";
    return 0;
  }
  std :: string  sent;
  while (getline(file, sent))                                            ///reading the points from lines in the input file and feeding them in an array
  {
   cout << sent << endl;
   std :: string  d="";
   d.clear();
   int i=0;
while(sent[i]!=',')
{
d+=sent[i];
   i++;
}
i++;
double x=stod(d);
d.clear();
while(sent[i]!='\n')
{
d+=sent[i];
i++;
}
double y=stod(d);
points.push_back(make_pair(x,y));


}
      clock_t start = clock();                                         ///starts the timer
      Line_seg l(points,atoi(argv[1]));                             ///creating a line segment object by passing the points as arguments
      l.daa2();                                                     ///calling the least segmented squares algorithm on the line segment object
       clock_t stop=clock();                              ///stops the timer
      double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
       cout<<"Time taken by algo is"<<elapsed<<"milliseconds"<<endl;                 ///prints time taken by the algorithm
	return 0;
        }



