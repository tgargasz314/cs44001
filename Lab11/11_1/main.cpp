//Tyler Gargasz
//Lab 11, Milestone 1
//04-01-21

#include "drink.hpp"
#include <iostream>

int main() {
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

    std::cout << n + ", your " << b -> getSize() << " is ready. It will be $" << b -> getPrice() << ", please.\n";
}