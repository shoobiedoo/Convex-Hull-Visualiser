#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#define MAX_N 501
using namespace std;
typedef long long lld;
#include <bits/stdc++.h>
using namespace std;
#define point pair <double,double>

class LineSegments                        ///parent class for line segments
{
public: vector <point> A;                         ///vector containing all points
public : int c1;                          /// where c1 is the cost for each new line segment
};

class Line_seg : public LineSegments                       ///child class inheriting parent class LineSegments
{
public:
    Line_seg(vector <point> arr,int cost){                      ///public constructor taking the points and cost as arguments
A=arr;
c1=cost;
}

int n = 1, c=c1;
struct Point                                         ///defining a struct to represent points
{
    int x, y;
    bool operator <(const Point &p) const                        ///defining a struct to represent points
    {
        return (x < p.x);
    }
};
Point co_ordinates[MAX_N];                                 ///array containing all the points

double err[MAX_N][MAX_N];                                  ///2D array containing error for all possible line segments
double a[MAX_N][MAX_N];                                    ///2D array containing slopes for all possible lines
double b[MAX_N][MAX_N];                                    ///2D array containing intercepts for all possible lines
int xySums[MAX_N], mu_x[MAX_N], mu_y[MAX_N], mu_x_2[MAX_N], mu_y_2[MAX_N];           ///arrays used to calculate the errors
double minCost[MAX_N];                                     ///array to store optimal cost of line segments
int pos[MAX_N];                                            ///the final possible segment in the optimal case

struct Lines                                               ///defining a struct for lines
{
    double x1, y1, x2, y2;
    Lines()                                                ///default constructor
    {
        this->x1 = 0;
        this->y1 = 0;
        this->x2 = 0;
        this->y2 = 0;
    }
    Lines(double x1, double y1, double x2, double y2)      ///constructor when coordinates for the end points are given
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
};
vector<Lines> ret;                                                ///vector containing the final result
void processing()                                                 ///function to calculate slope of lines and error of lines
{
    sort(co_ordinates+1, co_ordinates+n+1);                       ///sorting the points by x co-ordinates

    for (int loop=1;loop<=n;loop++)
    {
        mu_x[loop] = mu_x[loop-1] + co_ordinates[loop].x;
        mu_y[loop] = mu_y[loop-1] + co_ordinates[loop].y;
        mu_x_2[loop] = mu_x_2[loop-1] + co_ordinates[loop].x * co_ordinates[loop].x;
        xySums[loop] = xySums[loop-1] + co_ordinates[loop].x * co_ordinates[loop].y;
        mu_y_2[loop] = mu_y_2[loop-1] + co_ordinates[loop].y * co_ordinates[loop].y;
    }

    for (int loop=1;loop<=n;loop++)
    {
        for (int j=loop+1;j<=n;j++)
        {
            int nn = j - loop + 1;
            int xySum = xySums[j] - xySums[loop-1];
            int xSum = mu_x[j] - mu_x[loop-1];
            int ySum = mu_y[j] - mu_y[loop-1];
            int xSqrSum = mu_x_2[j] - mu_x_2[loop-1];
            int ySqrSum = mu_y_2[j] - mu_y_2[loop-1];

            a[loop][j] = ((nn * xySum - xSum * ySum) * 1.0) / ((nn * xSqrSum - xSum * xSum) * 1.0);
            b[loop][j] = ((ySum - a[loop][j] * xSum) * 1.0) / (nn * 1.0);

            err[loop][j] = a[loop][j] * a[loop][j] * xSqrSum + 2.0 * a[loop][j] * b[loop][j] * xSum - 2.0 * a[loop][j] * xySum + nn * b[loop][j] * b[loop][j] - 2.0 * b[loop][j] * ySum + ySqrSum;
        }
    }
}
 void final_lines()                                         ///function to select line segments which give overall minimum cost
{
    stack<Lines> vect;
    int presentInd = n;
    while (presentInd > 1)                                  /// basically j==0 in the code
    {
        int new_elem = pos[presentInd];
        if (new_elem == presentInd)
        {
            vect.push(Lines(co_ordinates[presentInd-1].x, co_ordinates[presentInd-1].y, co_ordinates[presentInd].x, co_ordinates[presentInd].y));
        }
        else
        {
            double x1 = co_ordinates[new_elem].x;
            double y1 = x1 * a[new_elem][presentInd] + b[new_elem][presentInd];
            double x2 = co_ordinates[presentInd].x;
            double y2 = x2 * a[new_elem][presentInd] + b[new_elem][presentInd];
            vect.push(Lines(x1, y1, x2, y2));
        }
        presentInd = new_elem - 1;
    }
    while (!vect.empty())
    {
        ret.push_back(vect.top());
        vect.pop();
    }
}

 double SegmentedLeastSquares()                                          ///function to calculate minimum cost of line segments
{
    for (int j=1;j<=n;j++)
    {
        minCost[j] = err[1][j] + c;
        pos[j] = 1;

        for (int loop=2;loop<=j;loop++)
        {
            if (minCost[loop-1] + err[loop][j] + c < minCost[j])
            {
                minCost[j] = minCost[loop-1] + err[loop][j] + c;
                pos[j] = loop;
            }
        }
    }

    return minCost[n];
}



void daa2()                                                                   ///function to implement the Least Segmented Squares algorithm
{
n=A.size();

int loop=0;
while(loop<n)
{co_ordinates[loop].x=A[loop].first;
co_ordinates[loop].y=A[loop].second;
loop++;
}
    c=c1;
    processing();
    SegmentedLeastSquares();
    final_lines();
     std :: ofstream myfile;
       myfile.open("output.csv");
    for (int loop=0;loop<ret.size();loop++)                                     ///writes the result points in the output file
    {
        myfile<<ret[loop].x1<<","<<ret[loop].y1<<"\n";
        myfile<<ret[loop].x2<<","<<ret[loop].y2<<"\n";
    }
    myfile.close();

}
};

