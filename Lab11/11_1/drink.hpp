// drink class to be used in Coffee Shack lab
// Tyler Gargasz
// 04-01-21

#include <string>

using std::string;

enum class DrinkType {small, medium, large}; //small =1 ? 

//ABSTRACT COMPONENT
class Drink{
public:
    Drink(DrinkType type = DrinkType::small, double price = 0):
                 type_(type), price_(price) {}

    virtual double getPrice() const;
    virtual string getSize() const;

private: 
    double price_;
    DrinkType type_;
};

//CONCRETE COMPONENT
class Coffee : public Drink {
public:
    Coffee(DrinkType type = DrinkType::small, double price = 0) : Drink(type, price) {}

    double getPrice() const override;
    string getSize()  const override;
};

//DECORATORS
class Sprinkles : public Drink {
public:
    Sprinkles(const Drink *wrapped) : 
        wrapped_(wrapped) {}

    double getPrice() const override;
    string getSize() const override;

private:
    const Drink *wrapped_;
};

class Foam : public Drink {
public:
    Foam(const Drink *wrapped) :
        wrapped_(wrapped) {}

    double getPrice() const override;
    string getSize() const override;

private:
    const Drink *wrapped_;
};

class Ice : public Drink {
public: 
    Ice(const Drink *wrapped) :
        wrapped_(wrapped) {}    

    double getPrice() const override;
    string getSize() const override;
private:
    const Drink *wrapped_;
};

class Caramel : public Drink {
public: 
    Caramel(const Drink *wrapped) :
        wrapped_(wrapped) {}    

    double getPrice() const override;
    string getSize() const override;
private:
    const Drink *wrapped_;
};
