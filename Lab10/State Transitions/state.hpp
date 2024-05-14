#ifndef __STATE__
#define __STATE__

#include <iostream>
#include <string>

using std::cout; using std::endl;

class State;    //Forward Class Declaration

class Process {
public:
    Process();

    void admitted();
	void interrupt();
	void io_event();
	void io_complete();
	void dispatch();
    void exit();

    void change_state(State* ns) { state_ = ns; }

    void print_state(std::ostream&);

private:
    static int n_id_;
    int id_;
    State *state_;
};

//Abstract State
class State {
public:
    virtual void admitted(Process*) {}
	virtual void interrupt(Process*) {}
	virtual void io_event(Process*) {}
	virtual void io_complete(Process*) {}
	virtual void dispatch(Process*) {}
    virtual void exit(Process*) {}

    virtual void print_state(std::ostream&) = 0;

    void change_state(Process *p, State *s) {
        p -> change_state(s);
    }
};



class NewState : public State {
public:
    static State* instance() {                  
        static State* only = new NewState();
        return only;
    }

    void admitted(Process *p) override;

    void print_state(std::ostream &out) override {
        out << "New" << endl;
    }

private:
    NewState(){}
};

class Ready : public State {
public:
    static State* instance() {                  
        static State* only = new Ready();
        return only;
    }

    void dispatch(Process *p) override;

    void print_state(std::ostream &out) override {
        out << "Ready" << endl;
    }

private:
    Ready(){}
};

class Waiting : public State {
public:
    static State* instance() {                  
    static State* only = new Waiting();
        return only;
    }

    void io_complete(Process *p) override;
   
    void print_state(std::ostream &out) override {
        out << "Waiting" << endl;
    }

private:
    Waiting(){}
};

class Running : public State {
public:    
    static State* instance() {                  
    static State* only = new Running();
        return only;
    }    

    void interrupt(Process *p) override;
    void io_event(Process *p) override;
    void exit(Process *p) override;

    void print_state(std::ostream &out) override {
        out << "Running" << endl;
    }

private:
    Running(){}
};

class Terminated : public State {
public:    
    static State* instance() {                  
    static State* only = new Terminated();
        return only;
    }    

    void print_state(std::ostream &out) override {
        out << "Terminated" << endl;
    }

private:
    Terminated(){}    
};

#endif