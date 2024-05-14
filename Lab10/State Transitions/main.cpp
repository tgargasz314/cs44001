#include "state.hpp"

using std::cout;

int main() {
    Process q;

    q.print_state(cout);        //q New

    q.admitted();                   

    q.print_state(cout);        //q Ready

    Process r;

    r.print_state(cout);        //r New 

    q.dispatch();

    q.print_state(cout);        //q Running
    
    r.admitted();

    r.print_state(cout);        //r Ready

    q.io_event();

    q.print_state(cout);        //q Waiting

    r.dispatch();               

    r.print_state(cout);        //r Running

    r.interrupt();

    r.print_state(cout);        //r Ready

    r.dispatch();               

    r.print_state(cout);        //r Running

    r.exit();  

    r.print_state(cout);        //r Terminated

    q.io_complete();

    q.print_state(cout);        //q Ready

    q.dispatch();

    q.print_state(cout);        //q Running

    q.exit();

    q.print_state(cout);         //q Terminated
}