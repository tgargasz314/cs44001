//
//Tyler Gargasz
//Lab 4, Milestone 1 
//02-11-2021
//

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<list<string>>&, string);  

// printing a list out
void printRoster(const list<list<string>>&); 

//main function
int main(int argc, char* argv[]) {
   
   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl; exit(1);
   }

   //Vector of students, then their courses
   list<list<string>> studentEntries;

   //Iterate through every file given in the command line
   for(int i = 1; i < argc; ++i) {
      readRoster(studentEntries, argv[i]);
   }

   //Prints First Name, Last Name: Courses
   cout << "First Name, Last Name: Courses (roster.cpp does not remove dropouts)" << endl;
   printRoster(studentEntries);
}

void readRoster(list<list<string>>& students, string file_name) {
   ifstream course(file_name);

   string course_name = file_name.substr(0, file_name.size() - 4); //The "-4" excludes the .txt extension
   
   string first_name, last_name;
   while(course >> first_name >> last_name) {
      string full_name = first_name + ' ' + last_name + ":"; //Constructs a full name
      bool repeat = false;

      for(auto& lst : students) {
         if(lst.front() == full_name) {   //If name is in list
            lst.push_back(course_name);   //Just add course to student
            repeat = true;                
            break;
         }
      } 

      if(!repeat) {                          //If name is *not* in list
         list<string> new_person;            //Create new entry
         new_person.push_back(full_name);    //Add name to entry
         new_person.push_back(course_name);  //Add course to entry
         students.push_back(new_person);     //Add entry to roster
      }
   }

   course.close();
}

void printRoster(const list<list<string>>& roster) {
   for(const auto& lst : roster) {  //Iterate through roster
      for(const auto& str: lst) {   //Iterate thorogh entries
         cout << str << ' ';        //Output *everything*
      }
      cout << endl;
   }
} 