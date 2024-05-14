//Wordlist Main File for Lab 2
//Tyler Gargasz
//02-20-2021

#include <iostream>
#include <fstream>
#include <cctype>
#include "WordList.hpp"

int main( int argc, char* argv[]) {

    if(argc != 2) {
    std::cout << "Incorrect Number of Arguments!" << std::endl;
    exit(0);
    }

    std::ifstream f(argv[1]);   //Opens file.
    if (!f) { std::cout << "Couldn't open " << argv[1] << std::endl; exit(0);}

    WordList w;
    std::string word;
    char ch;
    while(!f.eof()) {
        f.get(ch);


        if ((isspace(ch) || ispunct(ch)) && word != "") {
            w.addWord(word);
            word = "";
        } else if(isalnum(ch) || ch == '\'') { //Allows for contractions.
            word += ch;
        } 
    }

    w.print();

    f.close();
}