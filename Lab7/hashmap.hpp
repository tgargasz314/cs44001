// implementation basic hashmap (unordered container)
// Tyler Gargasz
// 03/04/2021

#include <iostream> //used solely in rehash
#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
   DefaultHash(size_t numBuckets = defaultNumBuckets);
   size_t hash(const T& key) const;
   size_t numBuckets() const { return numBuckets_; }

private:
   // default number of buckets in the hash
   static const size_t defaultNumBuckets = 101; 
   size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets): numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
// note, this function does not work for C++ strings
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
   size_t res = 0;
   for (size_t i = 0; i < sizeof(key); ++i) {
      const unsigned char b = 
      *(reinterpret_cast<const unsigned char *>(&key) + i);
      res += b;
   }
   return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value, 
          typename Compare = std::equal_to<Key>,
          typename Hash = DefaultHash<Key>>
class hashmap{

public:
   typedef pair<const Key, Value> Element;

   // constructor
   // invokes constructors for comparison and hash objects
   hashmap(const Compare& comp = Compare(), 
	   const Hash& hash = Hash());

   Element* find(const Key& x);      // returns pointer to element with key x,
                                     // nullptr if not found

   pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> 
   insert(const Element& x);    // inserts the key/value pair

   pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> 
   erase(const Key& x);         // erases element with key x, if exists
   
   Value& operator[] (const Key& x); // returns reference on value of
                                     // element with key, inserts if does not exist

   void rehash(size_t s);

private:

   // helper function for various searches
   typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

   size_t size_;   // number of elements in the container
   Compare comp_;  // comparison functor, equal_to by default
   Hash hash_;     // hash functor 

   // hash contents: vector of buckets
   // each bucket is a list containing key->value pairs
   vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
   hashmap<Key, Value, Compare, Hash>::hashmap(
   const Compare& comp, const Hash& hash):
   size_(0), comp_(comp), hash_(hash) {
      elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value, 
          typename Compare, typename Hash>
   typename list<pair<const Key, Value>>::iterator // return type
   hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket){

   // look for the key in the bucket
   for (auto it =  elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
      if (comp_(it->first, x))
	 return it;

   return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
   typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
   hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

   size_t bucket = hash_.hash(x);
   auto it=findElement(x, bucket);    // use the findElement() helper   

   if (it != elems_[bucket].end())
      // found the element. Return a pointer to it.
      return &(*it); // dereference the iterator to list 
                     // then take the address of list element
   
   else // didn't find the element -- return nullptr
      return nullptr;
}


// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>           //added return value type (return pair)
hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {

    size_t bucket = hash_.hash(x.first);   
    auto it = findElement(x.first, bucket);    // try to find the element

    // if not found, insert a new one.
    if (it == elems_[bucket].end()) {
        ++size_;                            //increase number of elements by one
        elems_[bucket].push_back(x);        //add this element to the end
        it = (--elems_[bucket].end());         //set iterator (it) to this new element
        return make_pair(&(*it), true);     //return pair <value, bool> (the dereference reference returns actual value, the bool is success to add)
   } else {
        return make_pair(&(*it), false);    //return pair <value, bool> (the dereference reference returns actual value, the bool is failure to add)
   }
}


// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>
hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {
/*
   size_t bucket = hash_.hash(x);
   auto it = findElement(x, bucket);    // try to find the element
   if (it != elems_[bucket].end()) {    // the element exists, erase it
      elems_[bucket].erase(it);
      --size_;
   }
*/

   size_t bucket = hash_.hash(x);
   auto it = findElement(x, bucket);

   if(it != elems_[bucket].end()) {
      --size_;

      if(size_ == 0) {                                      //Last element in bucket
         elems_[bucket].erase(it);
         return make_pair(nullptr, true);
      }

      if(++it != elems_[bucket].end()) {                     //NOT last element in bucket
         it = elems_[bucket].erase(--it);
			return make_pair(&(*it), true);

      } else {                                              //Next non-empty bucket
         int nxt = bucket + 1;                              //Next bucket
         if(nxt >= hash_.numBuckets()) {                     //Loop to beginning of hash/(of buckets?)
            nxt = 0;
         }
         while(elems_[nxt].empty()) { ++nxt; }              //Find non-empty bucket

         return make_pair(&(*elems_[nxt].begin()), true);   //Found non-empty bucket
      }

      return make_pair(nullptr, false);                     //Did not find non-empty bucket
   }
   return make_pair(nullptr, false);
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {
/*
   Element* found = find(x);
   if (found == nullptr) { // if key not found, create new element with empty value
      insert(make_pair(x, Value())); // calling default constructor on Value
      found = find(x); // inefficient but avoids code duplication
   }
   return found->second;
*/

   auto pair = insert(make_pair(x, Value()));   //insert was rewritten to safely do this...why not just use it?
   return pair.first -> second;

}


template <typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t s){
   if(s <= hash_.numBuckets()) { 
      std::cout << "\t" << s << " too small! Failed!" << std::endl;
      return; 
   } 

   std::cout << "\tRehash with size: " << s << std::endl;

   hash_ = DefaultHash<Key>(s);                             //New hash with new size

   std::vector<Element> tmp;                                //Copy the entire hashmap
   for(auto& where : elems_) {
      for(auto& here : where) {
         tmp.push_back(here);
      }
   }

   elems_.empty();                                          //Actually empty hashmap
   elems_.resize(s);


	for(auto& it : tmp){
		size_t b = hash_.hash(it.first);
      std::cout << b << std::endl;
		elems_[b].push_back(it);
	}

   std::cout << "\t\tRehashed successfully!" << std::endl;
}

