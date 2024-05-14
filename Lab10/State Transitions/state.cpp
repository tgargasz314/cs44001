#include "state.hpp"


//
//Proccess Class Implementation
//
int Process::n_id_ = 0;

Process::Process() {
    id_ = n_id_;
    ++n_id_;
    state_ = NewState::instance();
}

void Process::admitted() {
    state_ -> admitted(this);
}

void Process::interrupt() {
    state_ -> interrupt(this);
}
void Process::io_event() {
    state_ -> io_event(this);
}

void Process::io_complete() {
    state_ -> io_complete(this);
}

void Process::dispatch() {
    state_ -> dispatch(this);
}

void Process::exit() {
    state_ -> exit(this);
}

void Process::print_state(std::ostream &out) {
    out << "Process " << id_ << " is ";
    state_ -> print_state(out);
}

//
//State Implementation
//

void NewState::admitted(Process *p) {
    p -> change_state(Ready::instance());
}

void Ready::dispatch(Process *p) {
    p -> change_state(Running::instance());
}

void Waiting::io_complete(Process *p) {
    p -> change_state(Ready::instance());
}

void Running::interrupt(Process *p) {
    p -> change_state(Ready::instance());
}

void Running::io_event(Process *p) {
    p -> change_state(Waiting::instance());
}

void Running::exit(Process *p){
	p->change_state(Terminated::instance());
}