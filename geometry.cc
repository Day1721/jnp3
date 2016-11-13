#include <iostream>
#include <utility>
#include <vector>
#include <assert.h>
#include "geometry.h"

using namespace std;

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
    assert(width > 0 && height > 0);
    this->widthValue = width;
    this->heightValue = height;
}

Rectangle::Rectangle(int width, int height, Position pos) : position(pos) {
    assert(width > 0 && height > 0);
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
    assert(place < heightValue);
    int leftDownX = position.x();
    int leftDownY = position.y() + place;
    Position newPos = Position(leftDownX, leftDownY);

    return std::make_pair(Rectangle(widthValue, place, position), Rectangle(widthValue, heightValue - place, newPos));
}

std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int place) {
    assert(place < widthValue);
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

//--------------------------------- Rectangles --------------------------------

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
    assert(i < recsVector.size());
    return recsVector[i];
}

size_t Rectangles::size() {
    return recsVector.size();
}

void Rectangles::split_horizontally(int idx, int place) {
    assert(idx < recsVector.size());
    std::pair<Rectangle, Rectangle> result = recsVector[idx].split_horizontally(place);
    recsVector.erase(recsVector.begin() + idx);
    recsVector.insert(recsVector.begin() + idx, get<0>(result));
    recsVector.insert(recsVector.begin() + idx + 1, get<1>(result));
}

void Rectangles::split_vertically(int idx, int place) {
    assert(idx < recsVector.size());
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

Rectangle merge_horizontally(Rectangle& rect1, Rectangle& rect2) {
    Position pos1 = rect1.pos();
    Position pos2 = rect2.pos();
    assert(rect1.width() == rect2.width() && rect1.height()+pos1.y() == pos2.y() && pos1.x() == pos2.x());
    
    return Rectangle(rect1.width(), rect1.height()+rect2.height(), pos1);
}

Rectangle merge_vertically(Rectangle& rect1, Rectangle& rect2) {
    Position pos1 = rect1.pos();
    Position pos2 = rect2.pos();
    assert(rect1.height() == rect2.height() && rect1.width()+pos1.x() == pos2.x() && pos1.y() == pos2.y());
    
    return Rectangle(rect1.width()+rect2.width(), rect1.height(), pos1);
}

int main(int argc, const char* argv[]) {

    return 0;
}
