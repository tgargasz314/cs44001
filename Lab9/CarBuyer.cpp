// needed for lab
// Mikhail Nesterenko
// 3/14/2016

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot{
public:
    CarLot();
    //Car *testDriveCar(){return car4sale_;}

    // if a car is bought, requests a new one
    Car *buyCar(){ 
        Car *bought = car4sale_;
        car4sale_[next_] = 
            *(factories_[rand() % factories_.size()] -> requestCar());
        return bought;
    }
		     
    Car* nextCar() {
        //cout << "Flag 1" << endl;

        ++next_;
        if(next_ == SIZE_) { next_ = 0; }    //Stays in lot
        Car* c = &car4sale_[next_];          //Ready next car
        return c;                           //Return next car
    }

    int getSize() { return SIZE_; }

private:
    static int next_;                           //Cars 0-9 in lot (10 cars total)
    static const int SIZE_ = 10;                //Locked lot size
    Car car4sale_[SIZE_];                       //Now and array of cars (10)
    vector<CarFactory *> factories_;
};
int CarLot::next_ = 0;


CarLot::CarLot(){
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());   
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

/*
    // gets the first car for sale
    car4sale_ = factories_[rand() % factories_.size()] -> requestCar();
*/

    //Fill lot with random cars
    for(int i = 0; i < SIZE_; ++i) {   
        car4sale_[i] = *(factories_[rand() % factories_.size()] -> requestCar());
    }
}


CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
    if(carLotPtr == nullptr)
        carLotPtr = new CarLot();

    //Car *toBuy = carLotPtr -> testDriveCar(); 

    //sstd::string wantModel = 

    for(int i; i < carLotPtr -> getSize(); ++i) {
        Car* testRide = carLotPtr -> nextCar();
        cout << id << " is test driving a: " 
            << testRide -> getMake() << ' '
             << testRide -> getModel() << endl;

        if(testRide -> getMake() == "Toyota") {
            cout << " love it! buying it!" << endl;
            carLotPtr -> buyCar(); 
            break;
        } else {
            cout << " did not like it!" << endl;
        }
    }


/*
   cout << "Buyer " << id << endl;
   cout << "test driving " 
	<< toBuy->getMake() << " "
	<< toBuy->getModel();

   if (toBuy->getMake() == "Toyota"){
      cout << " love it! buying it!" << endl;
      carLotPtr -> buyCar();
   } else
      cout << " did not like it!" << endl;
*/
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
    if(carLotPtr == nullptr)
        carLotPtr = new CarLot();

    //Car *toBuy = carLotPtr -> testDriveCar();


    for(int i; i < carLotPtr -> getSize(); ++i) {
        Car* testRide = carLotPtr -> nextCar();
        cout << id << " is test driving a: " 
            << testRide -> getMake() << ' '
             << testRide -> getModel() << endl;

        if(testRide -> getMake() == "Ford") {
            cout << " love it! buying it!" << endl;
            carLotPtr -> buyCar(); 
            break;
        } else {
            cout << " did not like it!" << endl;
        }
    }


/*
   cout << "Buyer " << id << endl;
   cout << "test driving "
	<< toBuy->getMake() << " "
        << toBuy->getModel();
   
   if (toBuy->getMake() == "Ford"){
      cout << " love it! buying it!" << endl;
      carLotPtr -> buyCar();
   } else
      cout << " did not like it!" << endl;
*/
}



int main() {
   srand(time(nullptr));

//cout << "Flag 2" << endl;
   const int numBuyers=10;
   for(int i=0; i < numBuyers; ++i)
      if(rand()% 2 == 0)
	 toyotaLover(i);
      else
	 fordLover(i);
  
}
