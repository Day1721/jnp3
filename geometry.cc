#include <iostream>
#include <vector>

using namespace std;

class Vector
{
    private:
        int firstCord;
        int secondCord;

    public:
        Vector(int x, int y) {
            this->firstCord = x;
            this->secondCord = y;
        }
        
        bool operator == (const Vector& v) const {
            return (this->firstCord == v.firstCord && this->secondCord == v.secondCord);
        }
        
        Vector& operator += (const Vector& v) {
            this->firstCord += v.firstCord;
            this->secondCord += v.secondCord;
            return *this;
        }
        
        Vector reflection() {
            return Vector(secondCord, firstCord);
        }
        
        int x(void) {
            return firstCord;
        }
        
        int y(void) {
            return secondCord;
        }
};

class Position
{
    private:
        int firstCord;
        int secondCord;
    
    public:
        Position(int x, int y) {
            this->firstCord = x;
            this->secondCord = y;
        }
        
        bool operator == (const Position& p) const {
            return (this->firstCord == p.firstCord && this->secondCord == p.secondCord);
        }
        
        Position& operator += (Vector& v) {
            if (firstCord != 0 && secondCord != 0) {
                this->firstCord += v.x();
                this->secondCord += v.y();
            }
            return *this;
        }
        
        Position reflection() {
            return Position(secondCord, firstCord);
        }
        
        int x(void) {
            return firstCord;
        }
        
        int y(void) {
            return secondCord;
        }
        
        static Position origin() {
            return Position(0, 0); // czy dobrze ??
        }
};

class Rectangle
{
    private:
        int widthValue;
        int heightValue;
        Position position;
    
    public:
        Rectangle(int width, int height) : position(Position(0, 0)) {
            this->widthValue = width;
            this->heightValue = height;
        }
        
        Rectangle(int width, int height, Position pos) : position(pos) {
            this->widthValue = width;
            this->heightValue = height;
            this->position = pos;
        }
        
        bool operator == (const Rectangle& r) const {
            return (this->widthValue == r.widthValue && this->heightValue == r.heightValue && this->position == r.position);
        }
        
        Rectangle& operator += (Vector& v) {
            position += v;
            return *this;
        }
        
        Rectangle reflection() { // czy dobrze ??
            int rightDownX = position.x() + widthValue;
            int rightUpY = position.y() + heightValue;
            return Rectangle(widthValue, heightValue, Position(-rightDownX, -rightUpY));
        }
        
        long long area() {
            return widthValue * heightValue;
        }
        
        pair<Rectangle, Rectangle> split_horizontally(int place) {
            int leftDownX = position.x();
            int leftDownY = position.y() + place;
            Position newPos = Position(leftDownX, leftDownY);
            
            return make_pair(Rectangle(widthValue, place, position), Rectangle(widthValue, heightValue-place, newPos));
        }
        
        pair<Rectangle, Rectangle> split_vertically(int place) {
            int leftDownX = position.x() + place;
            int leftDownY = position.y();
            Position newPos = Position(leftDownX, leftDownY);
            
            return make_pair(Rectangle(place, heightValue, position), Rectangle(widthValue-place, heightValue, newPos));
        }
        
        int width() {
            return widthValue;
        }
        
        int height() {
            return heightValue;
        }
        
        Position pos() {
            return position;
        }
};

class Rectangles
{
    private:
        vector<Rectangle> recsVector;
    
    public:
        Rectangles() {}

        Rectangles(vector<Rectangle> recsVector) {
            this->recsVector = recsVector;
        }

        bool operator == (const Rectangles& recsObj) const {
            return (this->recsVector == recsObj.recsVector);
        }

        Rectangles& operator += (Vector& v) {
            for (int i = 0; i < recsVector.size(); i++) {
                recsVector[i] += v;
            }
            return *this;
        }

        Rectangle& operator [] (int i) {
            return recsVector[i];
        }
        
        size_t size() {
            return recsVector.size();
        }

        void split_horizontally(int idx, int place) {
            pair<Rectangle, Rectangle> result = recsVector[idx].split_horizontally(place);
            recsVector.erase(recsVector.begin()+idx);
            recsVector.insert(recsVector.begin()+idx, get<0>(result));
            recsVector.insert(recsVector.begin()+idx+1, get<1>(result));
        }

        void split_vertically(int idx, int place) {
            pair<Rectangle, Rectangle> result = recsVector[idx].split_vertically(place);
            recsVector.erase(recsVector.begin()+idx);
            recsVector.insert(recsVector.begin()+idx, get<0>(result));
            recsVector.insert(recsVector.begin()+idx+1, get<1>(result));
        }
};

Position operator + (Position p, Vector &v) {
    return p += v;
}

Position operator + (Vector &v, Position p) {
    return p += v;
}

Vector operator + (Vector v1, Vector v2) {
    return v1 += v2;
}

Rectangle operator + (Rectangle r, Vector& v) {
    return r += v;
}

Rectangle operator + (Vector& v, Rectangle r) {
    return r += v;
}

Rectangles operator + (Rectangles r, Vector &v) {
    return r += v;
}

Rectangles operator + (Vector &v, Rectangles r) {
    return r += v;
}

void merge_horizontally(Rectangle rect1, Rectangle rect2) {
    // TODO
}

void merge_vertically(Rectangle rect1, Rectangle rect2) {
    // TODO
}

int main(int argc, const char * argv[]) {
    Vector v1 = Vector(10, 10);
    Position p1 = Position(1, 1);
    Rectangle r1 = Rectangle(100, 100, p1);
    Rectangle r2 = Rectangle(200, 200, p1);
    Rectangle r3 = Rectangle(300, 300, p1);
    Rectangles recs = Rectangles({r1, r2, r3});
    
    
    recs += v1;
    
    recs.split_horizontally(1, 10);
    
    Rectangle r4 = recs[1];
    Rectangle r5 = recs[2];
    Position p4 = r4.pos();
    Position p5 = r5.pos();
    
    cout << r4.width() << " " << r4.height() << endl;
    cout << p4.x() << " " << p4.y() << endl;
    cout << r5.width() << " " << r5.height() << endl;
    cout << p5.x() << " " << p5.y() << endl;
    
    cout << recs.size() << endl;
    
    return 0;
}

/*
 - funkcja origin w klasie Position
 - funkcja reflection w klasie Rectangle
 - funkcje merge_horizontally i merge_vertically
 - plik naglowkowy .h
 - r-value
 - sprawdzenie poprawnosci argumentow (assert?)
*/
