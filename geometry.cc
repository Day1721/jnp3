#include <iostream>

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
            return Vector(secondCord, firstCord); // czy na pewno dobrze ??
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
            this->firstCord += v.x();
            this->secondCord += v.y();
            return *this;
        }
        
        Position reflection() {
            return Position(secondCord, firstCord); // czy na pewno dobrze ??
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
        int rWidth;
        int rHeight;
        pair<int, int> rPos;
    
    public:
        Rectangle(int width, int height) {
            this->rWidth = width;
            this->rHeight = height;
            this->rPos = make_pair(0, 0);
        }
        
        Rectangle(int width, int height, pair<int, int> pos) {
            this->rWidth = width;
            this->rHeight = height;
            this->rPos = pos;
        }
        
        bool operator == (const Rectangle& r) const {
            return (this->rWidth == r.rWidth && this->rHeight == r.rHeight && this->rPos == r.rPos);
        }
        
        Rectangle& operator += (Vector& v) {
            int leftDownX = get<0>(rPos);
            int leftDownY = get<1>(rPos);
            leftDownX += v.x();
            leftDownY += v.y();
            rPos = make_pair(leftDownX, leftDownY);
            return *this;
        }
        
        Rectangle reflection() {
            int leftDownX = get<0>(rPos);
            int leftDownY = get<1>(rPos);
            int rightDownX = leftDownX + rWidth;
            int rightUpY = leftDownY + rHeight;
            return Rectangle(rWidth, rHeight, make_pair(-rightDownX, -rightUpY)); // czy dobrze ??
        }
        
        int area() {
            return rWidth*rHeight;
        }
        
        pair<Rectangle, Rectangle> split_horizontally(int place) {
            int leftDownX = get<0>(rPos);
            int leftDownY = get<1>(rPos) + place;
            pair<int, int> newPos = make_pair(leftDownX, leftDownY);
            
            return make_pair(Rectangle(rWidth, place, rPos), Rectangle(rWidth, rHeight-place, newPos));
        }
        
        pair<Rectangle, Rectangle> split_vertically(int place) {
            int leftDownX = get<0>(rPos) + place;
            int leftDownY = get<1>(rPos);
            pair<int, int> newPos = make_pair(leftDownX, leftDownY);
            
            return make_pair(Rectangle(place, rHeight, rPos), Rectangle(rWidth-place, rHeight, newPos));
        }
        
        int width() {
            return rWidth;
        }
        
        int height() {
            return rHeight;
        }
        
        pair<int, int> pos() {
            return rPos;
        }
};

class Rectangles
{
    // TODO
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

Rectangles operator + (Rectangles r, Vector v) {
    return Rectangles(); // TODO
}

Rectangles operator + (Vector v, Rectangles r) {
    return Rectangles(); // TODO
}

void merge_horizontally(Rectangle rect1, Rectangle rect2) {
    // TODO
}

void merge_vertically(Rectangle rect1, Rectangle rect2) {
    // TODO
}

int main(int argc, const char * argv[]) {
    return 0;
}
