#include "WordList.hpp"

//
//WordOccurrence
//
bool WordOccurrence::matchWord(const std::string & checkThis) {
    if(word_ == checkThis) {return true;}
    return false;
}


//
//WordList
//
bool compare (WordOccurrence lhs, WordOccurrence rhs) {
    return lhs.getNum() < rhs.getNum();
    }

void WordList::sortList() {
    std::sort(wordArray_, wordArray_ + size_, compare);
    }


void WordList::addWord(const std::string & lst) {
    //std::cout << lst << std::endl;
    
    for(int i = 0; i < size_; ++i) {
        //std::cout << i << std::endl;
        // std::cout << wordArray_[i].getWord();
        if(wordArray_[i].getWord() == lst) {
            //std::cout << "Matches!" << std::endl;
            wordArray_[i].increment(); 
            return;
        }
    }

    WordOccurrence *temp = new WordOccurrence[size_+1];
    for(int i = 0; i < size_; ++i) {
        temp[i] = wordArray_[i];
    }

    temp[size_] = WordOccurrence(lst, 1);
    ++size_;
    delete [] wordArray_;
    wordArray_ = temp;

    sortList();
}


//Copy Constructor
WordList::WordList(const WordList & rhs){
    size_ = rhs.size_;
    wordArray_ = size_ > 0 ? new WordOccurrence[size_] : nullptr;
    std::copy(rhs.wordArray_, rhs.wordArray_ + size_, wordArray_);
}

void WordList::print() {
    for(int i = 0; i < size_; ++i) {
        std::cout << wordArray_[i].getWord() << ' ' << wordArray_[i].getNum() << std::endl;
    }
}


bool equal(const WordList& rhs, const WordList& lhs){
    if(lhs.size_ != rhs.size_) {return false;}

    for(int i; i < rhs.size_; ++i) {
        if(lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord()) {return false;}
    }

    return true;
} 
