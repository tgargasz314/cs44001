#ifndef __WORD_COUNT__
#define __WORD_COUNT__

#include <iostream>
#include <string>
#include <algorithm>

class WordOccurrence {
public:
    WordOccurrence(const std::string& word="", int num=0) {word_ = word; num_ = num;}
    bool matchWord(const std::string &); // returns true if word matches stored
    void increment() {++num_;} // increments number of occurrences
    std::string getWord() const {return word_;}
    int getNum() const {return num_;}

    friend bool compare(WordOccurrence, WordOccurrence);

private:
    std::string word_;
    int num_;
};

class WordList{
public:

    WordList() {wordArray_ = new WordOccurrence[0]; size_ = 0;}
    
    //Copy Constructor 
    WordList(const WordList& rhs);
    
    //Destructor
    ~WordList(){delete[] wordArray_;}

    //Overloaded Assignment
    friend void swap(WordList& lhs, WordList& rhs){
        std::swap(lhs.size_,  rhs.size_);
        std::swap(lhs.wordArray_, rhs.wordArray_);
    }

    WordList& operator=(WordList rhs){
    swap(*this, rhs);
    return *this;
  }

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void sortList();

    void addWord(const std::string &);
    void print();
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};

#endif