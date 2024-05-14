//Lab 11, Milestone 2 Main
//Tyler Gargasz
//04-05-21

#include "shop.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    Barista *bar = new JuniorBarista(new SeniorBarista(new Manager));
    srand(time(nullptr));

    bar -> take_order();

    while((bar -> num_orders()) != 0) {

        //std::cout << "FLAG TOP WHILE" << std::endl;

        if(rand()%2 == 0 && !(bar -> is_empty())) {                         //Barista randomly makes an order...
            bar -> call_order();
        } else {                                                            //...or takes an order
            bar -> take_order();
        }
    }   
}