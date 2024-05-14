//Barista and Customer for Lab 11, Milestone 2
//Tyler Gargasz
//04-04-21

#include "drink.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using std::cout; using std::endl;
using std::string;
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

//Subject and Administrator
class Barista { 
public:
    Barista(Barista *admin = nullptr) : admin_(admin) {}

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

    virtual void handleRequest (Drink* order) {
        if(admin_ != nullptr) {
            //cout << "FLAG HANDLE REQUEST" << endl;

            admin_ -> handleRequest(order);
        } else {
            cout << "No one can make this order!" << endl;
        }
    }

protected:
    Drink* made_order_;
    vector<Drink*> orders_;
    Barista *admin_;

private:
    vector<Customer*> customers_;

};

//Chain of Responsibility
class JuniorBarista : public Barista {
public: 
    JuniorBarista(Barista *admin = nullptr) : Barista(admin) {}

    void handleRequest (Drink* order) override {
        string s_order = order -> getSize();
        
        //cout << "FLAG JUNIOR BARISTA 1" << endl;

        if(s_order.find("sprinkles") == -1 && s_order.find("caramel") == -1 
            && s_order.find("ice") == -1 && s_order.find("milk foam") == -1) {
            cout << "This drink was made by a Junior Barista." << std::endl;
        } else {
            Barista::handleRequest(order);
        }
    }
};

class SeniorBarista : public Barista {
public: 
    SeniorBarista(Barista *admin = nullptr) : Barista(admin) {}
    
    void handleRequest (Drink* order) override {
        string s_order = order -> getSize();

        //cout << "FLAG SENIOR BARISTA 1" << endl;
         
        if(s_order.find("milk foam") == -1) {
            cout << "This drink was made by a Senior Barista." << std::endl;
        } else {
            Barista::handleRequest(order);
        }
    }   

};

class Manager : public Barista {
public:
    Manager(Barista *admin = nullptr) : Barista(admin) {}

    void handleRequest (Drink* order) override {
        string s_order = order -> getSize();

        //cout << "FLAG MANAGER 1" << endl;
        
        if(s_order.find("milk foam")) {
            cout << "This drink was made by the Manager." << std::endl;
        } else {
            Barista::handleRequest(order);
        }
    }
};