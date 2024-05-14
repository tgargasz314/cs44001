// testing the implementation of templated list collection
// Mikhail Nesterenko
// 9/10/2015

#include <iostream>
#include <string>
#include "Collection.hpp" // template definition

using std::cout; using std::endl;
using std::string;

int main(){

   // manipulating integers
   Collection<int> cone;
   cout << "Integer collection: " << endl;
   cone.add(1); cone.add(2); cone.add(3);
   cone.print();

   cone.remove(2);
   cone.print();

   if(equal(cone, cone))
      cout << "cone is equal to itself" << endl;


    // uncomment when you debug the code above
    

   // manipulating strings
   string sa[] = {"yellow", "orange", "green", "blue"};
   Collection<string> ctwo;

   for(auto s : sa)
      ctwo.add(s);

   cout << "String collection: " << endl; //Tyler G added an "endl"
   ctwo.print();


   // manipulating character collections

   // individal collections
   Collection<char> a2g, h2n, o2u;
   for(char c='a'; c <='g'; ++c) a2g.add(c);
   for(char c='h'; c <='n'; ++c) h2n.add(c);
   for(char c='o'; c <='u'; ++c) o2u.add(c);

   if(!equal(a2g, h2n))
      cout << "a2g is not equal to h2n" << endl;

   // collection of collections
   Collection<Collection<char>> cpile;

   // adding individual collections
   cpile.add(a2g);
   cpile.add(h2n);
   cpile.add(o2u);

   // printing characters from last collection added
   cout << "Last added character collection: " << endl; //Tyler G added an "endl"
   cpile.last().print(); 

   
}
