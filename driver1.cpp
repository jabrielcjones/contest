// file name -- filename.cpp


// ============================== header files ===================================
#include <iostream>                 // for console I/O
#include <sketch.h>                 // for sketch library
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;


// ============================== named constants =============================
   int const MINUTE_PER_HOUR = 60;

// ============================== function prototypes ==============================


int main()
{
   int position, total_minutes;
   string hour, minute, time = "6:12";

   string one = time;
   cout << "one = "
        << one
        << endl;

   position = one.find(":");
   cout << "Position: "
        << position
        << endl;

   position -= 1;
   cout << "Position: "
        << position
        << endl;

   hour = one.substr(position, 1);  //obtain the string
   cout << "Hours: "
        << hour
        << endl;

   minute = one.substr(position + 2, 2);
   cout << "Minutes: "
        << minute
        << endl;

   total_minutes = atoi(hour.c_str()) * MINUTE_PER_HOUR + atoi(minute.c_str());

   cout << "Total Minutes: "
        << total_minutes
        << endl
        << "Hours: "
        << hour.c_str()
        << endl
        << "Minutes: "
        << minute.c_str()
        << endl;
   return total_minutes;

   return 0;
} //function main
