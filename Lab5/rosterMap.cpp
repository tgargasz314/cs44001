// vector and list algorithms with objects in containers
// Tyler Gargasz
// 02/18/2021
//Lab5

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::map;
using std::pair;

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

private:
   string firstName_;
   string lastName_;
};

// reading a list from a fileName
void readRoster(map<Student, list<string>>& roster, string fileName);  
// printing a list out
void printRoster(const map<Student, list<string>>& roster); 

int main(int argc, char* argv[]){

    if (argc <= 1) { 
        cout << "usage: " << argv[0] << " list of courses" << endl; 
        exit(1);
    }

    // vector of courses of students
    map<Student, list<string>> studentEntries;

    //Iterate through every file given in the command line
    for(int i = 1; i < argc; ++i) {
        readRoster(studentEntries, argv[i]);
    }

    cout << "First Name, Last Name: Courses (rosterMap does not remove dropouts)" << endl;
    printRoster(studentEntries);

}

void readRoster(map<Student, list<string>>& roster, string file_name){
    ifstream course(file_name);

    string course_name = file_name.substr(0, file_name.size() - 4); //The "-4" excludes the .txt extension

    string first_name, last_name;
    while(course >> first_name >> last_name) {
        auto itr = roster.find(Student(first_name, last_name)); //Searches to find student...this is boolean?
        if(itr == roster.end()) {                               //Student not found, add student
            roster.insert(pair<Student, list<string>>(Student(first_name, last_name), list<string>({course_name})));    //pair<Student, list<string>> ([Student] constructor, [list<string>] course)...yikes!
        } else {                                                //Student found, just add class
            (itr -> second).push_back(course_name);
        }
    }

    course.close();
}

void printRoster(const map<Student, list<string>>& roster) {
    for(auto itr = roster.cbegin(); itr != roster.cend(); ++itr) {  //Note to self: cbegin and cend are constants
        cout << (itr -> first).get_name() << ": ";                  //Iterate through map
        for(auto c : itr -> second) {                               //Iterate through list
            cout << c << ' ';
        } 
     cout << endl; 
    }
} 