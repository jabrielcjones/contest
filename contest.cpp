// assign03 -- assign03.cpp
// Jabriel C. Jones
// The purpose of this program is to recieve data for a programming contest via a file, 
// organize the results, and outputs them in the form of a table.


// ============================== header files ===================================
#include <iostream>                 // for console I/O
#include <fstream>                  // for files
#include <string>                   // for string functions
#include <cstdlib>
#include <iomanip>                  // for output manipulation
using namespace std;


// ============================== named constants =============================
   int const MAX_PROBLEM = 8;
   int const CONTEST_START = 90;
   int const PENALTY = 20;
   int const NAME_SIZE = 100;
   int const MINUTE_PER_HOUR = 60;

// ============================== stuctures =====================================
   struct Team
   {
      string name;
      int assess_time[MAX_PROBLEM];
      int problems_solved;
      int total_assess_time;
      int rank;
   }; // struct Team

// ============================== function prototypes ==============================
   void readData(ifstream&, Team**&, int&);
   void openFile(ifstream&);
   void processData(ifstream&, Team**&, int);
   void rankTeams(Team**&, int);
   int convertTime(string);
   void outputTable(Team**, int);


int main()
{
   ifstream infile;
   Team** teams;
   int size;


   openFile(infile);
   readData(infile, teams, size);
   processData(infile, teams, size);
   rankTeams(teams, size);
   outputTable(teams, size);
   

   return 0;
}  // end of function main



void openFile(ifstream& infile)
/**
   purpose: opens the file entered by user

   preconditions: none

   postconditions:   file is opened
**/
{
   char file_name[NAME_SIZE];
   do
   {
      cout << "Enter input data file name: ";
      cin >> file_name;
      infile.open(file_name);
      if (!infile)
      {
         cout << file_name
              << " was not opened successfully."
              << endl;
      }
   }while(!infile);  // opens file
}  // end of openFile



void readData(ifstream& infile,
              Team**& teams,
              int& size)
/**
   purpose: Reads data from the file and allocates the necessary memory
            to store data.

   preconditions: file must be opened

   postconditions:   member variables of the struct are initialized with base values
**/
{
   infile >> size;
   teams = new Team*[size];

   for(int index = 0; index < size; index++)
   {
      teams[index] = new Team;
      infile >> teams[index] -> name;
      teams[index] -> problems_solved = 0;
      teams[index] -> total_assess_time = 0;
      teams[index] -> rank = size;

      for(int i = 0; i < MAX_PROBLEM; i++)
         teams[index] -> assess_time[i] = 0;
   }  // initialize members of each struct
}



void processData(ifstream& infile,
                 Team**& teams,
                 int size)
/**
   purpose: Reads the rest of the data from the file stores it into
            the proper members of the various Team structs.

   preconditions: member variables of the struct must be initialized with base values

   postconditions:   data from file is save in corresponding member variables of the struct
**/
{
   string input_name, input_time;
   int problem_number;
   char result;

   infile >> input_name;
   while(infile)
   {
      infile >> input_time;
      infile >> problem_number;
      infile >> result;


      for(int index = 0; index < size; index++)
         if(input_name == teams[index] -> name)
         {
            if(toupper(result) == 'C')
            {
               switch(teams[index] -> assess_time[problem_number - 1])
               {
                  case 0:
                     teams[index] -> assess_time[problem_number - 1] = convertTime(input_time);
                     teams[index] -> problems_solved++;
                     break;
                  case 1:
                     teams[index] -> assess_time[problem_number - 1] = convertTime(input_time) + PENALTY;
                     teams[index] -> problems_solved++;
                     break;
                  case 2:
                     teams[index] -> assess_time[problem_number - 1] = convertTime(input_time) + (PENALTY * 2);
                     teams[index] -> problems_solved++;
                     break;
                  default:
                     break;
               }  // end of swith; saves times into corresponding struct members

               teams[index] -> total_assess_time += teams[index] -> assess_time[problem_number - 1];
            }  // end of nested if
            else
            {
               teams[index] -> assess_time[problem_number - 1]++;
            }  // end of nested else
            index = size;
         }  // end of if
      infile >> input_name;
   }  // end of while loop
}  // end of processData function



void outputTable(Team** teams, int size)
/**
   purpose: Outputs the data organized in the Team structs in the form of a table.

   preconditions: member variables of the struct must be initialized

   postconditions:   Table is oupted to the screen
**/
{
   cout << setw(25) << 1;
   for(int i = 1; i < MAX_PROBLEM; i++)
      cout << setw(10) << i + 1;

   cout << setw(10) << "# SOLVED"
        << setw(10) << "TIME"
        << setw(10) << "RANK" << endl;

   for(int i = 1; i < MAX_PROBLEM * 2; i++)
      cout << "---------";
   cout << endl;  // formats the base table


   for(int index = 0; index < size; index++)
   {
      cout << setw(15) << teams[index] -> name;

      for(int i = 0; i < MAX_PROBLEM; i++)
      {
         cout << setw(10) << teams[index] -> assess_time[i];
      }  // end of nested for loop

      cout << setw(10)
           << teams[index] -> problems_solved
           << setw(10)
           << teams[index] -> total_assess_time
           << setw(10)
           << teams[index] -> rank
           << endl;
   }  // end of for loop
   cout << endl;
}  // end of outputTable function



void rankTeams(Team**& teams, int size)
/**
   purpose: Ranks the teams based on the number of problems completed and
            total assessment times.

   preconditions: member variables of the struct must be initialized

   postconditions:   teams are ranked
**/
{
   int highest_index, first, index;
   Team* temp;

   for(index = 0; index < size - 1; index++)
   {
      highest_index = index;

      for(first = index + 1; first < size; first++)
      {
         if(teams[highest_index] -> problems_solved < teams[first] -> problems_solved)
            highest_index = first;
         else if(teams[highest_index] -> problems_solved == teams[first] -> problems_solved)
            if(teams[highest_index] -> total_assess_time > teams[first] -> total_assess_time)
               highest_index = first;
      }

      temp = teams[index];
      teams[index] = teams[highest_index];
      teams[highest_index] = temp;
   }  // end of for loop; selection sort

   for(int index = 0; index < size - 1; index++)
   {
      if(teams[index] -> problems_solved == teams[index+1] -> problems_solved && teams[index] -> total_assess_time == teams[index+1] -> total_assess_time)
      {
         teams[index] -> rank = index + 1;
         teams[index+1] -> rank = index + 1;
      }  // end of nested if
      else
      {
         teams[index] -> rank = index + 1;
         teams[index+1] -> rank = index + 2;
      }  // end of nested else
   }  // end of for loop
}  // end of rankTeams function



int convertTime(string time)
/**
   purpose: Converts times from the data type string type to integer type.

   preconditions: time must have a value fomated as such : "HH:MM'

   postconditions: time is returned in terms of minutes
**/
{
   int position, total_minutes;
   string hour, minute;

   string one = time;

   position = one.find(":");
   position -= 1;
   hour = one.substr(position, 1);  //obtain the string

   minute = one.substr(position + 2, 2);

   total_minutes = atoi(hour.c_str()) * MINUTE_PER_HOUR + atoi(minute.c_str());

   total_minutes = total_minutes - CONTEST_START;

   return total_minutes;
}  // end of convertTime function
