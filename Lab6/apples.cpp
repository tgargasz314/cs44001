// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Tyler Gargasz
// 03/02/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
    double weight; // oz
    string color;  // red or green
    void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
    srand(time(nullptr));
    const double minWeight = 3.;
    const double maxWeight = 8.;

    cout << "Input crate size: ";
    int size;
    cin >> size;

    vector <Apples> crate(size);

/*
    //assign random weight and color to apples in the crate
    //replace with generate()
    for(auto it = crate.begin(); it != crate.end(); ++it){
        it->weight = minWeight + 
	           static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        it->color = rand() % 2 == 1 ? "green" : "red";
    }
*/

    std::generate(crate.begin(), crate.end(), 
        [minWeight, maxWeight](){                                                               //Needs these variables (these are called out-of-scope variables?)
        Apples a;                                                                               //Make an apple
        a.weight = minWeight + static_cast<double>(rand())/RAND_MAX * (maxWeight - minWeight);  //Given function, creates random weight for apples
        a.color = rand() % 2 == 1 ? "green" : "red";                                            //Given function, creates random color for apples
        return a;                                                                               //Put apple in crate
    });

 
    cout << "Enter weight to find: ";
    double toFind;
    cin >> toFind;

/*
    //count_if()
    int cnt = 0;
    for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
        if(it->weight > toFind) ++cnt;
*/

    int cnt = std::count_if(crate.cbegin(), crate.cend(), [toFind](Apples a){return a.weight > toFind;}); //requires toFind, and increments whenever return is true

    cout << "There are " << cnt << " apples heavier than " 
	    << toFind << " oz" <<  endl;

/*
   // find_if()
   cout << "at positions ";
   for(int i=0; i < size; ++i)
      if(crate[i].weight > toFind)
	 cout << i << ", ";
   cout << endl;
*/

    cout << "at positions " << endl;
    auto itr = std::find_if(crate.cbegin(), crate.cend(), [toFind](Apples a){return a.weight > toFind;});   //itr gets set to first true instance
    while(itr != crate.cend()){                                                                             //iterate through crate
        itr->print();                                                                                       //call print (color, weight)?
        itr = std::find_if(itr + 1, crate.cend(), [toFind](Apples a){return a.weight > toFind;});           //go to next true
    }
    cout << endl;

/*
    // max_element()
    double heaviest = crate[0].weight;
    for(int i=1; i < size; ++i)
        if(crate[i].weight > heaviest) heaviest = crate[i].weight; 
    cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;
*/

    itr = std::max_element(crate.begin(), crate.end(), [](Apples a, Apples b){return a.weight < b.weight;});
    cout << "Heaviest apple weighs: " << itr -> weight << " oz" << endl;

/*
    // for_each() or accumulate()
    double sum = 0;
    for(int i=0; i < size; ++i)
        sum += crate[i].weight;
    cout << "Total apple weight is: " << sum << " oz" << endl;
*/

    double sum = 0;
    std::for_each(crate.begin(), crate.end(), [&sum](Apples a){sum += a.weight;});
    cout << "Total apple weight is: " << sum << " oz" << endl;


/*
    // transform();
    cout << "How much should they grow: ";
    double toGrow;
    cin >> toGrow;
    for(int i=0; i < crate.size(); ++i)
        crate[i].weight += toGrow;
*/

    cout << "How much should they grow: ";
    double toGrow;
    cin >> toGrow;
    std::transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples a){Apples grown;
                                                                grown.weight = a.weight + toGrow;
                                                                grown.color = a.color;
                                                                return grown;});

/*
    // remove_if()
    cout << "Input minimum acceptable weight: ";
    double minAccept;
    cin >> minAccept;
   
    for(auto it=crate.begin(); it != crate.end(); )
        if(it->weight < minAccept)
	    it = crate.erase(it);
        else
	    ++it;
*/

    cout << "Input minimum acceptable weight: ";
    double minAccept;
    cin >> minAccept;

    crate.erase(std::remove_if(crate.begin(), crate.end(), [minAccept](Apples &a){return a.weight < minAccept;}), crate.end());

    cout << "removed " << size - crate.size() << " elements" << endl;

/*
    // bubble sort, replace with sort()
    bool swapped;
    do{
        swapped = false;
        for(int i=0; i < crate.size()-1; ++i)
	    if(crate[i].weight > crate[i+1].weight){
	        std::swap(crate[i], crate[i+1]);
	        swapped = true;
	    }
    }while(swapped);
*/

    std::sort(crate.begin(), crate.end(), [](Apples a, Apples b){return a.weight < b.weight;}); //Lambda functions are the best

/*
    // moving all red apples from crate to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    deque<Apples> peck;
    for(auto it=crate.begin(); it != crate.end();)
        if(it->color == "red"){
	    peck.push_front(std::move(*it));
	    it=crate.erase(it);
    }else
	    ++it;
*/

    deque<Apples> peck;
    std::remove_copy_if(crate.begin(), crate.end(), front_inserter(peck), [](Apples &a){return a.color != "red";});
    crate.erase(std::remove_if(crate.begin(), crate.end(), [](Apples &b){return b.color == "red";}), crate.end());

    //crate.erase(std::remove_copy_if(crate.begin(), crate.end(), front_inserter(peck), [](Apples &a){return a.color == "red";}), crate.end());

/*
    // for_each() possibly
    cout << "apples in the create"<< endl;
    for(const auto &e: crate) {
        e.print(); 
    }
*/
    cout << "apples in the crate"<< endl;
    std::for_each(crate.begin(), crate.end(), [](Apples &a){a.print();});

    cout << endl;

/*
    // for_each() possibly
    cout << "apples in the peck"<< endl;
    for(const auto &e: peck) {
        e.print();
    } 
*/

    cout << "apples in the peck"<< endl;
    std::for_each(peck.begin(), peck.end(), [](Apples &a){ if(a.color != "") {a.print();}});

    // prints every "space" apple in the peck
    // 
    const int space=3; 
    cout << "\nevery " << space << "\'d apple in the peck"<< endl;

/*
    // replace with advance()/next()/distance()
    // no iterator arithmetic
    auto it=peck.cbegin(); int i = 0;   
    while(it != peck.cend()){
        if(i == space){
	        it->print();
	        i=0;
        }
        ++i; 
        ++it;
    }
*/

    int i = 1;
    auto dit = peck.begin();
    while(dit != peck.end()){
        if(dit -> color != "" && i % space == 0) {dit -> print();} //space could in theory be changed?
        std::advance(dit, 1);
        ++i;
    }

/*
   // putting all small green apples in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0; 
   for(auto it=crate.begin(); it != crate.end();)
      if(it->weight < weightToJam){
	 jamWeight += it->weight;
	 it=crate.erase(it);
      }else
	 ++it;

   cout << "Weight of jam is: " << jamWeight << endl;
*/

class press {
public:
    press(){weight_ = 0;}
    void operator() (vector<Apples> green, double max_weight) {
        //cout << "Flag 1" << endl;
        for(auto& it : green) {
            //cout << "Flag 2" << endl;
            //cout << max_weight << ' ' << it.weight << endl;
	        if(it.weight < max_weight) {
                //cout << "Weight Added " << it.weight << endl;
                //cout << "Total Weight " << weight_ << endl;
	            weight_ += it.weight;
	        }
        }
        cout << "Weight of jam is: " << get_weight() << endl;

    }

    double get_weight() { return weight_; }

private:
    double weight_;
};

    const double weightToJam = 10.0;
    //double jamWeight = 0; 

    press jammer;
    auto j = bind(jammer, crate, std::placeholders::_1);

    j(weightToJam);

    //cout << "Weight of jam is: " << jammer.get_weight() << endl;  //Had issues with thia, reviewing with tutors as to why
                                                                    //This only ever printed zero, although i debugged my functor

}