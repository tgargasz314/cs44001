// demoes hashmap implementation
// Tyler Gargasz
// 03/04/2021

#include "hashmap.hpp"
#include <iostream>

using std::cin; using std::cout; using std::endl;

int main() {
    hashmap<int, int> test;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto t1 = test.insert(make_pair(1, 2));
    auto t2 = test.insert(make_pair(3, 4));
    auto t3 = test.insert(make_pair(5, 6));
    auto t4 = test.insert(make_pair(7, 8));
    auto t5 = test.insert(make_pair(9, 10));

    cout << "Testing insert() (success is 1, failure is 0):" << endl;
    cout << "\tFresh Inserts:" << endl;

    cout << "\t\tt1 pair: " << 
                            "<<" << t1.first -> first << ", " << t1.first -> second << ">, "    //pair of <key, value> 
                            << t1.second << '>' << endl;                                        //insert return of <<key, value>, success/fail bool>

    cout << "\t\tt4 pair: " << 
                            "<<" << t4.first -> first << ", " << t4.first -> second << ">, "    //pair of <key, value> 
                            << t4.second << '>' << endl;                                        //insert return of <<key, value>, success/fail bool>
    
    cout << "\tRepeat Key (should fail):" << endl;
    auto t6 = test.insert(make_pair(7, 22));

    cout << "\t\tt4 pair: " << 
                            "<<" << t6.first -> first << ", " << t6.first -> second << ">, "    //pair of <key, value> 
                            << t6.second << '>' << endl;   

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Testing find(): " << endl; 

    auto f1 = test.find(7);
    if (f1 != nullptr) { 
        cout << "\tKey 7 is mapped to: " << f1 -> second << endl;
    } else {
        cout << "\tKey 7 not found" << endl;
    }

    auto f2 = test.find(22);
    if (f2 != nullptr) { 
        cout << "\tKey 22 is mapped to: " << f2 -> second << endl;
    } else {
        cout << "\tKey 22 not found" << endl;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Testing [] operator: " << endl;

    test[69] = 96;
    cout << "\ttest[69] = 96: " << test[69] << endl;

    test[69] = 420;
    cout << "\ttest[69] = 420: " << test[69] << endl;

    auto t7 = test.find(69);
    if(t7 != nullptr) {
        cout << "\t69 (t7) maps to: " << t7 -> second << endl;
    } else {
        cout << "69 not found" << endl;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Testing erase(): " << endl;

    auto rmv = test.erase(1);
    if(rmv.second) {                //erase should return success or failure as second
        cout << "\tErased!" << endl;
        //cout << "\t" << rmv.first << endl;
        if(rmv.first == nullptr) {  //first should now be empty and return next bucket
            cout << "\tNext is: " << rmv.first -> second << endl;
        } else {
            cout << "\tNo next!" << endl;
        }
    } else {
        cout << "\tErase failed! Does not exist!" << endl;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Testing rehash(): " << endl;
    test.rehash(99);
    test.rehash(300);

}