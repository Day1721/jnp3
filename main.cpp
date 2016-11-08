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
    
    Vector operator += (const Vector& v) {
        this->firstCord += v.firstCord;
        this->secondCord += v.secondCord;
        return *this; //czy na pewno * ??
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
    
    Rectangle operator += (Vector& v) {
        int leftDownX = get<0>(rPos);
        int leftDownY = get<1>(rPos);
        leftDownX += v.x();
        leftDownY += v.y();
        rPos = make_pair(leftDownX, leftDownY);
        return *this; //czy na pewno * ??
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

int main(int argc, const char * argv[]) {
    Rectangle rect1 = Rectangle(100, 200);
    pair<Rectangle, Rectangle> para = rect1.split_vertically(20);
    
    Rectangle rect2 = get<0>(para);
    Rectangle rect3 = get<1>(para);
    
    cout << get<0>(rect2.pos()) << "," << get<1>(rect2.pos()) << " h: " << rect2.height() << " w: "<< rect2.width() << endl;
    cout << get<0>(rect3.pos()) << "," << get<1>(rect3.pos()) << " h: " << rect3.height() << " w: "<< rect3.width() << endl;
    return 0;
}
