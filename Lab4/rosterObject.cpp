// vector and list algorithms with objects in containers
// Tyler Gargasz
// 02/16/2021

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


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
   string print() const {
      string enrolled = "";
      for(auto& c : classes_) {
        enrolled += c + ' '; 
      }
      string entry = get_name() + ": " + enrolled;
      return entry;
  }

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }

   // needed for readRoster function
   string get_name() const { return firstName_ + ' ' + lastName_; }
   void add_class( string course) { classes_.push_back(course); }


private:
   string firstName_;
   string lastName_;
   list<string> classes_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1) { 
      cout << "usage: " << argv[0] << " list of courses, dropouts last" << endl; 
      exit(1);
   }

   // vector of courses of students
   list<Student> studentEntries; 

   //Iterate through every file given in the command line
   for(int i = 1; i < argc; ++i) {
      readRoster(studentEntries, argv[i]);
   }

   cout << "First Name, Last Name: Courses (rosterObject does not remove dropouts)" << endl;
   printRoster(studentEntries);
}


void readRoster(list<Student>& roster, string file_name){
   ifstream course(file_name);

   string course_name = file_name.substr(0, file_name.size() - 4); //The "-4" excludes the .txt extension

   string first_name, last_name;
    while(course >> first_name >> last_name) {
      bool repeat = false;
      for(auto& student : roster) {
         if(student.get_name() == first_name + ' ' + last_name){
            repeat = true;
            student.add_class(course_name);
         }            
      }

      if(!repeat) {
         Student new_person(first_name, last_name);
         new_person.add_class(course_name);
         roster.push_back(new_person);
      }
   }

   course.close();
} 

// printing a list out
void printRoster(const list<Student>& roster){
   for(const Student& student : roster)
      cout << student.print() << endl;
}
