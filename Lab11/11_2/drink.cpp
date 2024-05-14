#include "drink.hpp"

double Drink::getPrice() const { return price_; }

string Drink::getSize() const { 
    switch(type_) {
        case DrinkType::small : return "small";
        case DrinkType::medium : return "medium";
        case DrinkType::large : return "large";
    }
}

void Drink::set_name(string n) {
    order_name_ = n;
}

string Drink::getName() const {
    return order_name_;
}


//Coffee
double Coffee::getPrice() const { return Drink::getPrice(); }

string Coffee::getSize() const { return Drink::getSize() + " coffee"; }


//
//Decorators
//

//Sprinkles
double Sprinkles::getPrice() const { 
    return wrapped_ -> getPrice() + .5;
}

string Sprinkles::getSize() const {
    string n = wrapped_ -> getSize();
    string lastWord = n.substr(n.find_last_of(' ')+1, string::npos);

/*
    if(lastWord == "coffee") { 
        return n + " with sprinkles";
    } else {
        return n + ", sprinkles";
    }
*/

    return n + (lastWord == "coffee" ? " with " : ", ") + "sprinkles";
}

//Foam
double Foam::getPrice() const {
    return wrapped_ -> getPrice() + .4;
}

string Foam::getSize() const {
    string n = wrapped_ -> getSize();
    string lastWord = n.substr(n.find_last_of(' ')+1, string::npos);

    return n + (lastWord == "coffee" ? " with " : ", ") + "milk foam";
}

//Ice
double Ice::getPrice() const {
    return wrapped_ -> getPrice() + .1;
}

string Ice::getSize() const {
    string n = wrapped_ -> getSize();
    string lastWord = n.substr(n.find_last_of(' ')+1, string::npos);

    return n + (lastWord == "coffee" ? " with " : ", ") + "ice";
}

//Caramel
double Caramel::getPrice() const {
    return wrapped_ -> getPrice() + .2;
}

string Caramel::getSize() const {
    string n = wrapped_ -> getSize();
    string lastWord = n.substr(n.find_last_of(' ')+1, string::npos);

    return n + (lastWord == "coffee" ? " with " : ", ") + "caramel";
}
