#include <iostream>
#include <utility>
#include <vector>
#include "geometry.h"

using namespace std;

/*
 - funkcja origin w klasie Position
 - funkcja reflection w klasie Rectangle
 - funkcje merge_horizontally i merge_vertically
 - plik naglowkowy .h
 - r-value
 - sprawdzenie poprawnosci argumentow (assert?)
*/

//---------------------------------- VECTOR ----------------------------------

Vector::Vector(int x, int y) {
    this->firstCord = x;
    this->secondCord = y;
}

bool Vector::operator ==(const Vector& v) const {
    return (this->firstCord == v.firstCord && this->secondCord == v.secondCord);
}

Vector& Vector::operator +=(const Vector& v) {
    this->firstCord += v.firstCord;
    this->secondCord += v.secondCord;
    return *this;
}

Vector Vector::reflection() {
    return Vector(secondCord, firstCord);
}

int Vector::x() const {
    return firstCord;
}

int Vector::y() const {
    return secondCord;
}

//--------------------------------- Position ---------------------------------

Position::Position(int x, int y) {
    this->firstCord = x;
    this->secondCord = y;
}

bool Position::operator ==(const Position& p) const {
    return (this->firstCord == p.firstCord && this->secondCord == p.secondCord);
}

Position Position::reflection() {
    return Position(secondCord, firstCord);
}

int Position::x() const {
    return firstCord;
}

int Position::y() const {
    return secondCord;
}

Position Position::origin() {
    return Position(0, 0); // czy dobrze ?? TAK
}

//--------------------------------- Rectangle ---------------------------------

Rectangle::Rectangle(int width, int height) : position(Position(0, 0)) {
    this->widthValue = width;
    this->heightValue = height;
}

Rectangle::Rectangle(int width, int height, Position pos) : position(pos) {
    this->widthValue = width;
    this->heightValue = height;
    this->position = pos;
}

bool Rectangle::operator ==(const Rectangle& r) const {
    return (this->widthValue == r.widthValue && this->heightValue == r.heightValue && this->position == r.position);
}

Rectangle& Rectangle::operator +=(Vector& v) {
    position += v;
    return *this;
}

Rectangle Rectangle::reflection() { // czy dobrze ??
    int rightDownX = position.x() + widthValue;
    int rightUpY = position.y() + heightValue;
    return Rectangle(widthValue, heightValue, Position(-rightDownX, -rightUpY));
}

long long Rectangle::area() {
    return widthValue * heightValue;
}

std::pair<Rectangle, Rectangle> Rectangle::split_horizontally(int place) {
    int leftDownX = position.x();
    int leftDownY = position.y() + place;
    Position newPos = Position(leftDownX, leftDownY);

    return std::make_pair(Rectangle(widthValue, place, position), Rectangle(widthValue, heightValue - place, newPos));
}

std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int place) {
    int leftDownX = position.x() + place;
    int leftDownY = position.y();
    Position newPos = Position(leftDownX, leftDownY);

    return std::make_pair(Rectangle(place, heightValue, position), Rectangle(widthValue - place, heightValue, newPos));
}

int Rectangle::width() {
    return widthValue;
}

int Rectangle::height() {
    return heightValue;
}

Position Rectangle::pos() {
    return position;
}

Rectangles::Rectangles() {
    recsVector = std::vector<Rectangle>();
}

Rectangles::Rectangles(std::initializer_list<Rectangle> list) {
    this->recsVector = std::vector<Rectangle>(list);
}

bool Rectangles::operator ==(const Rectangles& recsObj) const {
    return (this->recsVector == recsObj.recsVector);
}

Rectangles& Rectangles::operator +=(Vector& v) {
    for (int i = 0; i < recsVector.size(); i++) {
        recsVector[i] += v;
    }
    return *this;
}

Rectangle& Rectangles::operator [](int i) {
    return recsVector[i];
}

size_t Rectangles::size() {
    return recsVector.size();
}

void Rectangles::split_horizontally(int idx, int place) {
    std::pair<Rectangle, Rectangle> result = recsVector[idx].split_horizontally(place);
    recsVector.erase(recsVector.begin() + idx);
    recsVector.insert(recsVector.begin() + idx, get<0>(result));
    recsVector.insert(recsVector.begin() + idx + 1, get<1>(result));
}

void Rectangles::split_vertically(int idx, int place) {
    std::pair<Rectangle, Rectangle> result = recsVector[idx].split_vertically(place);
    recsVector.erase(recsVector.begin() + idx);
    recsVector.insert(recsVector.begin() + idx, get<0>(result));
    recsVector.insert(recsVector.begin() + idx + 1, get<1>(result));
}

Position operator +(Position p, Vector& v) {  //IMO jest źle, bo + nie powinien zmieniać żadnego parametru wejściowego
    return p += v;
}

Position operator +(Vector& v, Position p) {
    return p += v;
}

Vector operator +(Vector v1, Vector v2) {
    return v1 += v2;
}

Rectangle operator +(Rectangle r, Vector& v) {
    return r += v;
}

Rectangle operator +(Vector& v, Rectangle r) {
    return r += v;
}

Rectangles operator +(Rectangles r, Vector& v) {
    return r += v;
}

Rectangles operator +(Vector& v, Rectangles r) {
    return r += v;
}

void merge_horizontally(Rectangle rect1, Rectangle rect2) {
    // TODO
}

void merge_vertically(Rectangle rect1, Rectangle rect2) {
    // TODO
}

int main(int argc, const char* argv[]) {
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