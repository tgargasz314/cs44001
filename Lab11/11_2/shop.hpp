//Barista and Customer for Lab 11, Milestone 2
//Tyler Gargasz
//04-04-21

#include "drink.hpp"
#include <vector>
#include <algorithm>

using std::vector;

class Barista;          //Forward Class Declaration

//Observer
class Customer {
public: 

    Customer(class Barista *b, string name = "", Drink* c = new Drink()) : name_(name), c_(c), b_(b) {}

    void on_notification();
    void check_drink();

private:
    string name_;
    Drink *c_;
    Barista *b_;
};

//Subject
class Barista { 
public:
    Barista() {}

    void add_customer(Customer*);
    void remove_customer(Customer*);

    void add_order(Drink*);
    void remove_order(Drink*);

    void take_order();
    void call_order();


    bool is_empty() {
        return customers_.empty();
    }

    void notify();
    Drink* get_made_order() const {
        return made_order_;
    }

    int num_orders() { return orders_.size(); }

    Drink* get_drink_from_list(int i) const { return orders_[i]; }


private:
    Drink* made_order_;
    vector<Customer*> customers_;
    vector<Drink*> orders_;
};