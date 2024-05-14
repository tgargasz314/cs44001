// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
    Fill(char border, char inside): border_(border), inside_(inside) {}
    virtual char getBorder()=0;
    virtual char getInternal()=0;
    virtual ~Fill() {}
protected:
    char border_;
    char inside_;
};

// concrete body
class Hollow: public Fill{
public:
    Hollow(char border): Fill(border, ' ') {}
    char getBorder() override { return border_; }
    char getInternal() override { return inside_; }
    ~Hollow(){}
};


// another concrete body
class Filled: public Fill {
public:
    Filled(char fillChar): Fill(fillChar, fillChar) {}
    char getBorder() override { return border_; }
    char getInternal() override { return inside_; }
    ~Filled(){}
};


// enhanced fill
class EnhancedFill: public Fill {
public:
    EnhancedFill(char bdr, char ins): Fill(bdr, ins) {}
    char getBorder() override { return border_; }
    char getInternal() override { return inside_; }
    ~EnhancedFill() {}
};


// abstract handle
class Figure {
public:
    Figure(int size, Fill* fill): size_(size), fill_(fill){}
    virtual void draw() =0;

    void changeFill(Fill *nf) {
        if(fill_ != nullptr) { delete fill_; }
        fill_ = nf;
    }

    virtual ~Figure(){}
protected:
    int size_;
    Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};


void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}


int main(){
   
    Fill* hollowPaintY = new Hollow('^');
    Fill* filledPaintStar = new Filled('*');

   
    Figure *smallBox = new Square(5, filledPaintStar);
    Figure *bigBox = new Square(10, hollowPaintY);

    smallBox->draw();
    cout << endl;
    bigBox -> draw();
   

    // ask user for figure parameters
    cout << "Enter fill character: "; 
                char fchar; cin >> fchar;
    cout << "Filled or hollow? [f/h] "; 
            char ifFilled; cin >> ifFilled;
    cout << "Enter size: "; int size; cin >> size;

    Figure *userBox1 = new Square(size, ifFilled == 'f'? 
	        static_cast<Fill *>(new Filled(fchar)):
	        static_cast<Fill *>(new Hollow(fchar))
	        ); 


   /*
   Figure *userBox = ifFilled == 'f'?
      new Square(size, new Filled(fchar)):
      new Square(size, new Hollow(fchar));
   */

    userBox1 -> draw();
    cout << endl;

    cout << "Enhanced Fill (using +):" << endl;
    Figure *userBox2 = new Square(size, static_cast<Fill *>(new EnhancedFill(fchar, '+')));
    userBox2 -> draw();

}
