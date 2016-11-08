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
        return Vector(secondCord, firstCord);
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
    
};

int main(int argc, const char * argv[]) {
    Vector wektor = Vector(100, 200);
    Vector wektor2 = Vector(400, 100);
    wektor += wektor2;
    cout << wektor.x() << endl;
    cout << wektor.y() << endl;
    return 0;
}
