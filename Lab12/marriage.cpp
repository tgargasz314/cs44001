// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko, Editted By: Tyler Gargasz
// 10/28/2015, 04-08-21

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string; 
using std::vector;

class Person{ // component
public:
    Person(string firstName, Person *spouse, Person *father, Person *mother):
        firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
    const string & getFirstName(){return firstName_;}
    Person *getSpouse(){return spouse_;}
    void setSpouse(Person *spouse){spouse_=spouse;}
    Person *getFather(){return father_;}
    Person *getMother(){return mother_;}

    virtual string getFullName()=0;

    virtual void accept(class PersonVisitor *)=0;  
    virtual ~Person(){}
private:
    const string firstName_;
    Person *spouse_;
    Person *father_;
    Person *mother_;
};


// leaf
// man has a last name 
class Man: public Person{
public:
    Man(string lastName, string firstName, Person *spouse, 
        Person *father, Person *mother): 
        lastName_(lastName), 
        Person(firstName, spouse, father, mother){}
    const string & getLastName(){return lastName_;}
    void accept(class PersonVisitor *visitor) override;

    string getFullName() override {
        return getFirstName() + ' ' + getLastName();
    }

private:
    const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public: 
    Woman(vector<Person *> children, 
        string firstName, 
        Person *spouse, 
        Person *father, Person *mother): 
        children_(children),
        Person(firstName, spouse, father, mother){}
    const vector<Person *> & getChildren() {return children_;}
    void setChildren(const vector<Person *> &children){ children_ = children;}
    void accept(class PersonVisitor *visitor) override;

    string getFullName() override {
        if(getSpouse() != nullptr) {
            return getFirstName() + ' ' + static_cast<Man*>(getSpouse()) -> getLastName();
        } else if (getFather() != nullptr) {
            return getFirstName() + ' ' + static_cast<Man*>(getFather()) -> getLastName();
        } else {
            return getFirstName();
        }
    }


private:
    vector<Person *> children_;
}; 

// abstract visitor
class PersonVisitor{
public:
    virtual void visit(Man*)=0;
    virtual void visit(Woman*)=0;
    virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
    visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor){ 
   // children traversal through mother only
   // father's children are not traversed so as not 
   // to traverse them twice: for mother and father

    visitor->visit(this);
   // traversing descendants
    for(auto child : children_) {
        child->accept(visitor);
        if((child -> getSpouse()) != nullptr) {
            (child -> getSpouse()) -> accept(visitor);
        }
    }
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor{
public:
    void visit(Man *m) override {
        cout << m->getFirstName() << " " << m->getLastName() << endl;
    }
    void visit(Woman *w) override {
        cout << w->getFirstName() << " ";
        if (w->getSpouse() != nullptr)
        cout << static_cast<Man *> (w->getSpouse())->getLastName();
        else if (w->getFather() != nullptr)
        cout << static_cast<Man *> (w->getFather())->getLastName();
        else
        cout << "Doe";
        cout << endl;
    }
};


class ChildrenPrinter: public PersonVisitor{
public:
    void visit(Man *m) override {
        cout << m->getFirstName() << ": ";
        Woman *spouse = static_cast<Woman *>(m->getSpouse());
        if(spouse != nullptr)
        printNames(spouse->getChildren());
        cout << endl;
    }
    void visit(Woman *w) override {
        cout << w->getFirstName() << ": ";
        printNames(w->getChildren());
        cout << endl;
    }
private:
   void printNames(const vector<Person *> &children){
        for(const auto c: children)
            cout << c->getFirstName() << ", ";
    }
};


class MaindenNamePrinter : public PersonVisitor {
public: 

    void visit(Man *m) override {}

    void visit(Woman *w) override {
        cout << w -> getFirstName() << ' ';
        if(w -> getFather() != nullptr) {
            cout << static_cast<Man *>(w -> getFather()) -> getLastName();
        } else {
            cout << "has no maiden name.";
        }

        cout << endl;
    }

};


class MatchMaker : public PersonVisitor {
public:
    MatchMaker(string p1, string p2) : p1_(p1), p2_(p2) {}
    
    //
    //Check Man
    //
    void visit(Man *m) override {

        //Undefined??
        if(m -> getFullName() != p1_ && m -> getFullName() != p2_) { return; }

        //Cannot marry oneself
        if(p1_ == p2_) {
            match_ = false;
            return;
        }

        //Cannot marry siblings
        if(m -> getFullName() == p1_ && m -> getMother() != nullptr) {              //First Person
            for(auto c : static_cast<Woman*>(m -> getMother()) -> getChildren()) {
                if (c -> getFullName() == p2_) {
                    match_ = false;
                    return;
                }
            }
        } else if (m -> getFullName() == p2_ && m -> getMother() != nullptr) {      //Second Person
            for(auto c : static_cast<Woman*>(m -> getMother()) -> getChildren()) {
                if (c -> getFullName() == p1_) {
                    match_ = false;
                    return;
                }
            }
        }

        //Cannot Marry Parents
        if(m -> getFullName() == p1_ && m -> getMother() != nullptr) {              //First Person, Check Mother
            if((m -> getMother()) -> getFullName() == p2_) {
                match_ = false;
                return;
            }
        } else if(m -> getFullName() == p1_ && m -> getFather() != nullptr) {       //First Person, Check Father
            if((m -> getFather()) -> getFullName() == p2_) {
                match_ = false;
                return;
            }
        }

        if(m -> getFullName() == p2_ && m -> getMother() != nullptr) {              //Second Person, Check Mother
            if((m -> getMother()) -> getFullName() == p1_) {
                match_ = false;
                return;
            }
        } else if(m -> getFullName() == p2_ && m -> getFather() != nullptr) {       //Second Person, Check Father
            if((m -> getFather()) -> getFullName() == p1_) {
                match_ = false;
                return;
            }
        }        

        //Cannot marry children
        //For a man to have kids, he MUST already be married (no need to check)
        //

        //Cannot marry an Aunt/Uncle
        if(m -> getFullName() == p1_ && m -> getMother() != nullptr && (m -> getMother()) -> getMother() != nullptr) {      //First Person, Mother Siblings
            for(auto c : static_cast<Woman*>(m -> getMother() -> getMother()) -> getChildren()) {
                if(c -> getFullName() == p2_) {
                    match_ = false;
                    return;
                }
            }
        } else if(m -> getFullName() == p1_ && m -> getFather() != nullptr && (m -> getFather()) -> getMother() != nullptr) { //First Person, Father Siblings
            for(auto c : static_cast<Woman*>(m -> getFather() -> getMother()) -> getChildren()){
                if(c -> getFullName() == p2_) {
                    match_ = false;
                    return;
                }
            }           
        }

        if(m -> getFullName() == p2_ && m -> getMother() != nullptr && (m -> getMother()) -> getMother() != nullptr) {      //Second Person, Mother Siblings
            for(auto c : static_cast<Woman*>(m -> getMother() -> getMother()) -> getChildren()) {
                if(c -> getFullName() == p1_) {
                    match_ = false;
                    return;
                }
            }
        } else if(m -> getFullName() == p2_ && m -> getFather() != nullptr && (m -> getFather()) -> getMother() != nullptr) { //Second Person, Father Siblings
            for(auto c : static_cast<Woman*>(m -> getFather() -> getMother()) -> getChildren()){
                if(c -> getFullName() == p1_) {
                    match_ = false;
                    return;
                }
            }           
        }    

        //Cannot marry again
        if ((m -> getFullName()== p1_ || m -> getFullName() == p2_) && m -> getSpouse() != nullptr) {
            match_ = false;
            //cout << "FLAG MAN: ALREADY MARRIED\n";
            return;
        }


    }

    //
    //Check Woman
    //
    void visit(Woman *w) override {
        
        //Cannot marry oneself
        if(p1_ == p2_) {
            match_ = false;
            return;
        }

        //Cannot marry siblings
        if(w -> getFullName() == p1_ && w -> getMother() != nullptr) {              //First Person
            for(auto c : static_cast<Woman*>(w -> getMother()) -> getChildren()) {
                if (c -> getFullName() == p2_) {
                    match_ = false;
                    //cout << "FLAG WOMAN: SIBLINGS 1\n";
                    return;
                }
            }
        } else if (w -> getFullName() == p2_ && w -> getMother() != nullptr) {      //Second Person
            for(auto c : static_cast<Woman*>(w -> getMother()) -> getChildren()) {
                if (c -> getFullName() == p1_) {
                    match_ = false;
                    //cout << "FLAG WOMAN: SIBLINGS 2\n";
                    return;
                }
            }
        }

        //Cannot marry Parents
        if(w -> getFullName() == p1_ && w -> getMother() != nullptr) {              //First Person, Check Mother
            if((w -> getMother()) -> getFullName() == p2_) {
                match_ = false;
                //cout << "FLAG WOMAN: PARENTS 1\n";
                return;
            }
        } else if(w -> getFullName() == p1_ && w -> getFather() != nullptr) {       //First Person, Check Father
            if((w -> getFather()) -> getFullName() == p2_) {
                match_ = false;
                //cout << "FLAG WOMAN: PARENTS 2\n";
                return;
            }
        }

        if(w -> getFullName() == p2_ && w -> getMother() != nullptr) {              //Second Person, Check Mother
            if((w -> getMother()) -> getFullName() == p1_) {
                match_ = false;
                //cout << "FLAG WOMAN: PARENTS 3\n";
                return;
            }
        } else if(w -> getFullName() == p2_ && w -> getFather() != nullptr) {       //Second Person, Check Father
            if((w -> getFather()) -> getFullName() == p1_) {
                match_ = false;
                //cout << "FLAG WOMAN: PARENTS 4\n";
                return;
            }
        }   

        //Cannot marry children
        if(w -> getFullName() == p1_) {             //First Person
            for(auto c : w -> getChildren()) {
                if(c -> getFullName() == p2_) {
                    match_ = false;
                    //cout << "FLAG WOMAN: CHILDREN 1\n";
                    return;
                }
            }
        } else if(w -> getFullName() == p2_) {      //Second Person
            for(auto c : w -> getChildren()) {
                if(c -> getFullName() == p1_) {
                    match_ = false;
                    //cout << "FLAG WOMAN: CHILDREN 2\n";
                    return;
                }
            }
        }

        //Cannot marry an Aunt/Uncle
        if(w -> getFullName() == p1_ && w -> getMother() != nullptr && (w -> getMother()) -> getMother() != nullptr) {      //First Person, Mother Siblings
            for(auto c : static_cast<Woman*>(w -> getMother() -> getMother()) -> getChildren()) {
                if(c -> getFullName() == p2_) {
                    match_ = false;
                    //cout << "FLAG WOMAN: AU 1\n";
                    return;
                }
            }
        } else if(w -> getFullName() == p1_ && w -> getFather() != nullptr && (w -> getFather()) -> getMother() != nullptr) { //First Person, Father Siblings
            for(auto c : static_cast<Woman*>(w -> getFather() -> getMother()) -> getChildren()){
                if(c -> getFullName() == p2_) {
                    match_ = false;
                    //out << "FLAG WOMAN: AU 2\n";
                    return;
                }
            }           
        }

        if(w -> getFullName() == p2_ && w -> getMother() != nullptr && (w -> getMother()) -> getMother() != nullptr) {      //Second Person, Mother Siblings
            for(auto c : static_cast<Woman*>(w -> getMother() -> getMother()) -> getChildren()) {
                if(c -> getFullName() == p1_) {
                    match_ = false;
                    //cout << "FLAG WOMAN: AU 3\n";
                    return;
                }
            }
        } else if( w ->getFullName() == p2_ && w -> getFather() != nullptr && (w -> getFather()) -> getMother() != nullptr) { //Second Person, Father Siblings
            for(auto c : static_cast<Woman*>(w -> getFather() -> getMother()) -> getChildren()){
                if(c -> getFullName() == p1_) {
                    match_ = false;
                    //cout << "FLAG WOMAN: AU 4\n";
                    return;
                }
            }           
        }    

        //Cannot marry again
        if ((w -> getFullName() == p1_ || w -> getFullName() == p2_) && w -> getSpouse() != nullptr) {
            match_ = false;
            //cout << w -> getFullName() << " is already married.\n";
            //cout << w -> getSpouse();
            //cout << "FLAG WOMAN: ALREADY MARRIED\n";
            return;
        }


    }

    bool getMatch() { return match_; }

private:
    bool match_ = true;
    string p1_;
    string p2_;
};




// demonstrating the operation
int main(){

    // setting up the genealogical tree      
    // the tree is as follows
    //    
    //
    //       James Smith  <--spouse-->   Mary 
    //	                                  |
    //	                                 children -------------------------
    //	                                  |              |                |
    //	                                  |              |                |
    //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
    //	                                  |
    //	                                 children------------
    //	                                  |                 |
    //                                    |                 |
    //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
    //	       |
    //	     children
    //	       |
    //         |
    //	     Susan


    // first generation
    Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);

    // second generation
    Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
    Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);

    vector<Person *> marysKids  = {ps,
                        new Man("Smith", "Robert", nullptr, js, ms),
                        new Woman({}, "Linda", nullptr, js, ms)};
    ms->setChildren(marysKids);

    // third generation
    Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person *> patsKids   = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
    ps->setChildren(patsKids);

    Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person *> jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);
    

    // defining two visitors
    ChildrenPrinter *cp = new ChildrenPrinter;
    NamePrinter *np = new NamePrinter;

    // executing the traversal with the composite
    // and the specific visitor

    cout << "\nNAME LIST\n";
    ms->accept(np);

    cout << endl << endl;

    cout << "CHILDREN LIST\n";
    ms->accept(cp);
    
    cout << "\nJAMES' CHILDREN\n";
    js->accept(cp);


    //Maiden Name Printer

    cout << "\nMAIDEN NAMES OF WOMEN\n";

    MaindenNamePrinter *mnp = new MaindenNamePrinter;
    ms -> accept(mnp);


    //Matchmaker

    cout << "\nMATCHMAKER\n";

    string p1, p2;
    cout << "Enter first person: ";
    std::getline(std::cin, p1);     //Must use this, as names have spaces

    cout << "Enter second person: ";
    std::getline(std::cin, p2);

    MatchMaker *mm = new MatchMaker(p1, p2);
    ms -> accept(mm);

    bool match = mm -> getMatch();

    if(match) {
        cout << "They can marry.\n";
    } else { 
        cout << "They cannot marry.\n";
    }
}