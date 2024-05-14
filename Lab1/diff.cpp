//Tyler Gargasz
//Lab 1:
//01-26-2021

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main(int argc, char* argv[]) {

    if(argc != 3) {
        std::cout << "Incorrect Number of Arguments!" << std::endl;
        exit(0);
    }

    std::string f1_Name = std::string(argv[1]);
    std::string f2_Name = std::string(argv[2]);

    std::ifstream first;
    first.open(f1_Name);    //Opens the first file.

    std::ifstream second;
    second.open(f2_Name);   //Opens the second file.

    std::string str1;       
    std::string str2;       
    int line_ctr = 1;       //Variable used to print what line differences are on.

    while(!first.eof() || !second.eof()) {  //Must be at end of BOTH files to exit loop.
    
        std::getline(first, str1);  
        std::getline(second, str2); //Gets next line from files.

        if (str1 != str2) { //Lines not equal.
            for(int i = 0; i < str1.length() || i < str2.length(); ++i) { //Checking char by char.
                if(str1[i] != str2[i]) {
                    
                    int line_char = line_ctr % 10 ? log10(line_ctr) + 1 : ceil(log10(line_ctr));    //Calcualtes num of digits of the line number.

                    int space_Length = f1_Name.length() + line_char + i + 4;    //Using 4 accounts for two ": " spacings.

                    std::cout << f1_Name << ": " << line_ctr << ": " << str1 << std::endl;
                    std::cout << f2_Name << ": " << line_ctr << ": " << str2 << std::endl; 
                    
                    std::string space_String(space_Length, ' ');
                    std::cout << space_String << '^' << std::endl;
                    
                    if(str1 > str2) {
                        i = str1.length();
                    } else {
                        i = str2.length();
                    }
                }
            }
        } ++line_ctr;
    }
    first.close();
    second.close();
}