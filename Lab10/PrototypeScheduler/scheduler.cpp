//Tyler Gargasz
//Prototype Scheduler
//04-01-21

#include "state.hpp"
#include <queue>
#include <cstdlib>
#include <deque>
#include <algorithm>


class Scheduler {
public:
    Scheduler() {
        pt = new Process();
    }

    void print(std::ostream&);
    void create_process();
    void execute(int);


private:
    Process* pt;
    std::queue<Process*> ready;
    std::queue<Process*> waiting; 
    std::deque<Process*> every;
};

void Scheduler::print(std::ostream& out) {
    for(Process *p : every) {
        if(p != nullptr) {
            p -> print_state(out);
        }
    }
}

void Scheduler::create_process() {
    Process *tmp = pt -> clone();
    tmp -> admitted();
    ready.push(tmp);
    every.push_back(tmp);
}

void Scheduler::execute(int n) {
    srand(time(nullptr));
    //srand(1);

    //std::cout << "FLAG EXECUTE BEGIN" << std::endl;

    //CREATE PROCESSES
    for(int i; i < n; ++i) { create_process(); }

    print(std::cout);
    
    //READY TASK FROM WAITING
    while(!ready.empty() || !waiting.empty()) {
        if(rand()%2 == 0 && !waiting.empty()) {
            //std::cout << "FLAG TOP WAITING" << std::endl;

            Process *w = waiting.front();
            waiting.pop();
            w -> io_complete();
            ready.push(w);
            std::cout << "Process " << w -> get_id() << " IO_Complete" << endl;

            //std::cout << "FLAG WAITING" << std::endl;
        }

        if(!ready.empty()) {
            //std::cout << "FLAG AFTER IF" <<std::endl;

            Process *p = ready.front();
            ready.pop();

            //std::cout << "FLAG LINE 76; " << p << std::endl;

            
            p -> dispatch();

            //std::cout << "FLAG AFTER DISPATCH" << std::endl;

            p -> print_state(std::cout);
            
            int action = rand() % 3;
            std::cout << "Action: " << action << '\t';

            switch(action) {
                case 0: {       //TERMINATE

                    std::cout << "Process " << p -> get_id() << " is Terminated" << endl;
                    
                    //ready.pop();
                    p -> exit();


                    //std::cout << "FLAG CASE 0 (TERMINATE)" << std::endl;
                    //auto it = std::find(every.begin(), every.end(), p);
                    //every.erase(it);
                    break;
                }                

                case 1: {       //IO_EVENT

                    std::cout << "Process " << p -> get_id() << " has IO_EVENT" << endl;

                    p -> io_event();
                    waiting.push(p);
                    //ready.pop();

                    //std::cout << "FLAG CASE 1 (IO_EVENT)" << std::endl;

                    break;
                }                                   

                case 2: {       //INTERRUPT

                    //std::cout << "Process " << p -> get_id() << " is Interrupted" << endl;

                    p -> interrupt();
                    ready.push(p);
                    //ready.pop();

                    //std::cout << "FLAG CASE 2 (INTERRUPT)" << std::endl;

                    break;
                }
            }

            print(std::cout);

            //std::cout << "FLAG WHILE LOOP" << std::endl;
        }
    }
}


int main() {
    Scheduler s;
    s.execute(5);
}