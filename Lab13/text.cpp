// implements command history 
// (multiple undos)
// demonstrates command pattern
// Mikhail Nesterenko
// 11/22/2014
// Tyler Gargasz
// 04-22-21

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// receiver
class Document {
public:

    Document(const vector <string> & lines={}) : lines_(lines){}

    // actions
    void insert(int line, const string &str) {
        const int index = line-1;
        if (index <= lines_.size()) {
	        lines_.insert(lines_.begin() + index, str); 
        } else {
	        cout << "line out of range" << endl;
        } 
    }

    string remove(int line) {
        const int index = line-1;
        string deletedLine="";
        if(index < lines_.size()) {
	        deletedLine = lines_[index];
	        lines_.erase(lines_.begin() + index); 
        } else {
	        cout << "line out of range" << endl;
        }
        return deletedLine;
    } 

    void show() {
        for(int i = 0; i < lines_.size(); ++i) {
	        cout << i + 1 << ". " << lines_[i] << endl;
        } 
   }

private:
   vector<string> lines_; 
}; 

// abstract command
class Command{
public:
    Command(Document *doc) : doc_(doc){}
    virtual void execute() = 0; 
    virtual void unexecute() = 0; 
    virtual void print() = 0;
    virtual ~Command(){}
protected:
    Document *doc_; 
}; 

// two concrete commands
class InsertCommand : public Command {
public:
    InsertCommand(Document *doc, int line, const string &str) : Command(doc), line_(line),  str_(str) {}
    void execute() override { doc_ -> insert(line_, str_); }
    void unexecute() override { doc_ -> remove(line_); }

    void print() override {
        cout << "insert " << str_ << " at line " << line_;
    }

private:
    int line_; 
    string str_; 
}; 


class EraseCommand : public Command {
public:
    EraseCommand(Document *doc, int line) : Command(doc), line_(line), str_("") {}
    void execute() override { str_ = doc_ -> remove(line_); }
    void unexecute() override { doc_ -> insert(line_, str_); }

    void print() override {
        cout << "erase line " << line_;
    }

private:
    int line_;
    string str_;
};

// client
class SaveState;    //Forward Class Declaration

class DocumentWithHistory {
public:
    DocumentWithHistory(const vector<string> & text={}) : doc_(text){}

    void insert(int line, string str) {
        Command *com = new InsertCommand(&doc_, line, str); 
        com -> execute(); 
        doneCommands_.push(com); 
    }

    void erase(int line) {
        Command *com = new EraseCommand(&doc_, line);
        com->execute();
        doneCommands_.push(com);
    }

    void undo() {
        if(doneCommands_.size() != 0) {
	        Command *com = doneCommands_.top(); 
	        doneCommands_.pop(); 
	        com -> unexecute();
	        delete com; // don't forget to delete command
        } else {
	        cout << "no commands to undo" << endl;
        } 
    }

    SaveState* createSaveState() const; 

    void rollBack(SaveState *mem);

    void history() {
        std::stack<Command*> tmp;
        int line = 0;
        while(!doneCommands_.empty()) {
            ++line;
            Command *c = doneCommands_.top();
            doneCommands_.pop();
            cout << line << ". ";
            c -> print();
            cout << '\n';
            tmp.push(c);
        }
        cout << "\n\n";
        while(!tmp.empty()) {
            Command *c = tmp.top();
            tmp.pop();
            doneCommands_.push(c);
        }
    }

    void redo(int i) {
        Command *c;
        std::stack<Command*> tmp;
        for(int j = 0; j < i; ++j) {
            c = doneCommands_.top();
            doneCommands_.pop();
            tmp.push(c);
        }
        c -> execute();
        for(int j = 0; j < i; ++j) {
            doneCommands_.push(tmp.top());
            tmp.pop();
        }
        doneCommands_.push(c);
    }


    void show() { doc_.show(); }

private:
    Document doc_;
    std::stack<Command*> doneCommands_; 
}; 

class SaveState {
public:
    SaveState(const DocumentWithHistory& doc): doc_(doc) {}
    const DocumentWithHistory& getState() const { return doc_; }  
private:
    const DocumentWithHistory doc_;
};
 
SaveState *DocumentWithHistory::createSaveState() const {
    // copying the Document itself
    return new SaveState(*this);
}

void DocumentWithHistory::rollBack(SaveState *mem) {
    *this = mem->getState();  // copying back
}



// invoker
int main() {
    DocumentWithHistory his({
	    "Lorem Ipsum is simply dummy text of the printing and typesetting",
	    "industry. Lorem Ipsum has been the industry's standard dummy text",
	    "ever since the 1500s, when an unknown printer took a galley of",
	    "type and scrambled it to make a type specimen book. It has",
	    "survived five centuries."}); 

    char option; SaveState *s;
    while(option != 'q' || option == 'Q') {
        his.show(); 
        cout << endl;

        cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command, ";
        cout << "(c)heckpoint, roll (b)ack, (h)istory, (r)edo, or (q)uit: ";
        cin >> option; 

        int line; string str; 
        switch(option) {
            case 'i': {
	            cout << "line number to insert: "; 
	            cin >> line; 
	            cout << "line to insert: "; 
	            cin.get(); // removes end-of-line character so getline() works correctly
	            getline(cin, str); 
	            his.insert(line, str); 
	            break;
            }

            case 'e': {
	            cout << "line number to remove: ";
	            cin >> line;
	            his.erase(line);
	            break;
            }

            case 'u': {
	            his.undo(); 
	            break; 
            }

            case 'c': {
                s = his.createSaveState();
                break;
            }

            case 'b': {
                his.rollBack(s);
                break;
            }


            case 'h': {
                his.history();
                break;
            }

            case 'r': {
                int i;
                cout << "Enter the line of the command to redo: ";
                cin >> i;
                his.redo(i);
                break;
            }
        }
    }
}
