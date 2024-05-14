//Customer, Barista implementation
//Tyler Gargasz
//04-04-21

#include "shop.hpp"
#include <iostream>

using std::cout; using std::endl;

//
//Customer Implementation
//


void Customer::on_notification() {
    if(name_ == (b_ -> get_made_order()) -> getName()) {
        cout << name_ << " took their drink." << std::endl;    
    }
}

//
//Barista Implementation
//

void Barista::take_order() {
    //std::cout << "Flag TAKE ORDER" << std::endl;
            
    std::cout << "Welcome to Coffee Shack, can I get " << 
                    "you a [l]arge, [m]edium, or [s]mall coffee? ";

    char c;
    std::cin >> c;
        DrinkType size;
        double price;

        switch(c) {
            case 'l':  
                size = DrinkType::large; 
                price = 3.;
                break;
            case 'm':
                size = DrinkType::medium; 
                price = 2.;
                break;
            case 's':
                size = DrinkType::small; 
                price = 1.;
                break;
        }

        Drink* b = new Coffee(size, price);

        while(c != 'n') {
            std::cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
            std::cin >> c;

            switch(c) {
                case 's':
                    b = new Sprinkles(b); break;
                case 'c':
                    b = new Caramel(b); break;
                case 'f':
                    b = new Foam(b); break;
                case 'i':
                    b = new Ice(b); 
            }
        }

        std::cout << "Can I get your name? ";
        string n;
        std::cin >> n;

        Customer *cust = new Customer(this, n, b);
        b -> set_name(n);

        //Barsita needs to add drink to vector
        add_order(b);
        add_customer(cust);

}

void Barista::call_order() {
    //std::cout << "Flag CALL ORDER" << std::endl;

    int i = rand() % num_orders();
    made_order_ = get_drink_from_list(i);

    handleRequest(made_order_);
    cout << made_order_ -> getName() << ", your " << made_order_ -> getSize();
    cout << " is ready. It will be $" << made_order_ -> getPrice() << ", please." << endl;

    notify();

    remove_customer(customers_[i]);
    remove_order(made_order_);
}

void Barista::notify() {
    for(auto c : customers_) { c -> on_notification(); }
}

void Barista::add_customer(Customer *c) {
   customers_.push_back(c);
}

void Barista::remove_customer(Customer* c) {
    auto it = std::remove(customers_.begin(), customers_.end(), c);
    customers_.erase(it, customers_.end());
}

void Barista::add_order(Drink *d) {
    orders_.push_back(d);
}

void Barista::remove_order(Drink* d) {
    auto it = std::remove(orders_.begin(), orders_.end(), d);
    orders_.erase(it, orders_.end());
}


