// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }

      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 3; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

class Dice : public Game {
public:
    void initializeGame() {
        playersCount_ = numPlayers_;
        for (int i = 0; i < 6; ++i) {
            roll[0][i] = 0;             //Initialize Bot
            roll[1][i] = 0;             //Initialize Player
        } 
        srand(time(nullptr));           //RNG

/*
        for(int i = 0; i < 5; ++i) {                                    //DUBUGGING
            cout <<  "Computer: " << roll[0][i] << ' ';
        }
        cout << endl;
        for(int i = 0; i < 5; ++i) {                                    //DEBUGGING
            cout << "Player: " << roll[1][i] << ' ';
        }
*/

        //cout << "Initialized!" << endl;
    }

    void print() {
        cout << "Computer Rolled: ";        //Print Computer Rolls
        for(int i = 0; i < 5; ++i) {
            cout << roll[0][i] << ' ';
            
            //cout << "Print 1" << endl;
        } 
        cout << ", Total: " << roll[0][5] << endl;

        cout << "You Rolled: ";             //Print Player Rolls
        for(int i = 0; i < 5; ++i) {
            cout << roll[1][i] << ' ';

            //cout << "Print 2" << endl;
        }
        cout << ", Total: " << roll[1][5] << endl;

    }

    void makeMove(int player) { 
        //print();                    //Print Turns

        if(player == 0) {                               //Computer Turn
            
            if(rand() % 2 == 0) {                       //Computer Passes
                cout << "Computer Passes!" << endl;
                ++pass_;
            } else {                                    //Computer makes 6 rolls
                pass_ = 0; 
                int total = 0;
                for(int i = 0; i < 5; ++i) {
                    roll[0][i] = rolling();
                    total += roll[0][i];
                }
                roll[0][5] = total;
                cout << endl;
                //print();
            }
        } else {
            char p = 'n';
            cout << "Pass Your Turn? [y/n]: ";  //Player can pass
            std::cin >> p;
            if(p == 'N' || p == 'n') {
                pass_ = 0; 
                int total = 0;
                for(int i = 0; i < 5; ++i) {            //Player Rolls
                    roll[1][i] = rolling();
                    total += roll[1][i];
                }
                cout << endl;
                roll[1][5] = total;
                print();
            } else {                                    //Player Passes
                cout << "Player Passes!" << endl;
                ++pass_;
            }
        } 
        //print();
    }

	int rolling() {                                        //Rolls random 1-6
        int r = rand() % 6 + 1;
        //cout << r << ' ';
        return r;
	}

    void printWinner() {
        if(roll[0][5] < roll[1][5]) {                   //Player Wins
            cout << "Player Wins!" << endl;
        } else if (roll[0][5] == roll[1][5]) {          //Tie
            cout << "Computer Wins! (Tie)" << endl;
        } else {                                        //Computer Wins
            cout << "Computer Wins!" << endl;
        }
    }


    bool endOfGame() {
        if(movesCount_ == 3 || pass_ >= 2) {
            return true;
        }
        return false;
    }

private:
    static const int numPlayers_ = 2;
    int roll[2][6];
    int pass_ = 0;
};




int main() {
   srand(time(nullptr));

   Game* gp = nullptr;
/*
   // play chess 10 times
   for (int i = 0; i < 10; ++i){ 
      gp = new Chess;
      gp->playGame(); 
      delete gp;
   }
      

   // play monopoly 5 times
   for (int i = 0; i < 5; ++i){
      gp = new Monopoly;
      gp->playGame(); 
      delete gp;
   }
*/

    //play dice game
        gp = new Dice;
        gp ->playGame();
        delete gp;
}




