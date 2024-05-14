#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

//
// Tyler Gargasz
// 02-09-2021
//

#include <iostream>

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:

  node(): next_(nullptr) {}

  // functions can be inlined
  T getData()const{return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

private:
  T data_;
  node<T> *next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext()const{
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
   next_=next;
}



//Collection Class
template <typename G>
class Collection {
public:

    Collection(): first_(nullptr), last_(nullptr) {}

    void add(G thing) {
        if (first_ == nullptr) {    //if empty collection.
        //std::cout << std::endl << "First Add" << std::endl;
        
        first_ = new node<G>;
        first_ -> setData(thing);
        last_ = first_;

        //std::cout << std::endl << last_ -> getData() << std::endl;

    } else {                        //if collection is not empty
        last_ -> setNext(new node<G>);
        last_ = last_ -> getNext();
        last_ -> setData(thing);

        //std::cout << last_ -> getData() << std::endl;
    }
    }

    void print() {
        if (first_ == nullptr) { return; }

        node<G> *itr = first_;
        while(itr -> getNext() != nullptr) {
        std::cout << itr -> getData() << std::endl;
        itr = itr -> getNext();
    }

    std::cout << itr -> getData() << std::endl; //Last node
    }

    void remove(G thing) {
        if(first_ == nullptr) { return; }

        node<G>* prev = nullptr;
        node<G>* here = first_;

        while(here -> getNext() != nullptr) {
          if(here -> getData() == thing) {
            if(here == first_){             //If first obj is instance of thing
              first_ = first_ -> getNext();
              delete here;
              here = first_;
            } else {                        //If any other obj is instance of thing
              prev -> setNext(here -> getNext());
              delete here;
              here = prev -> getNext();
            }
          } else {                          //Move to next node
            prev = here;
            here = here -> getNext();
          }
        }

        if(here -> getData() == thing) {
          if (here == first_) {
            first_ = prev;
          }

          last_ = prev;

          if(last_ != nullptr) {
            last_ -> setNext(nullptr);
          }

          delete here;
        }
    }

    G last() { return last_ -> getData(); }

    friend bool equal (const Collection& lhs, const Collection& rhs) {
      if(&lhs == &rhs) { return true; } //If collection is itself

      bool result = true;
      node<G>* lhs_here = lhs.first_; 
      node<G>* rhs_here = rhs.first_;

      while(lhs_here -> getNext() != nullptr && rhs_here -> getNext() != nullptr) { //Iterate through both collections
        if(lhs_here -> getData() != rhs_here -> getData()){ //Collctions do not match
          result = false;
          break;
        } else { //Else, move to next nodes
          lhs_here = lhs_here -> getNext();
          rhs_here = rhs_here -> getNext();
        }
      }

      if (lhs_here -> getData() != rhs_here -> getData()) { result = false; } //Check last nodes

      if(lhs_here -> getNext() != nullptr || rhs_here -> getNext() != nullptr) { result = false; } //Collections have different lengths

      return result;
    }



private:
    node<G> *first_;
    node<G> *last_;

};

#endif