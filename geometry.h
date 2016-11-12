#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>

class Vector {
private:
    int firstCord;
    int secondCord;

public:
    Vector(int x, int y);

    bool operator ==(const Vector& v) const;

    Vector& operator +=(const Vector& v);

    Vector reflection();

    int x() const;

    int y() const;
};

class Position {
private:
    int firstCord;
    int secondCord;

public:
    Position(int x, int y);

    bool operator ==(const Position& p) const;

    Position& operator +=(const Vector& v) {
        this->firstCord += v.x();
        this->secondCord += v.y();
        return *this;
    }

    Position reflection();

    int x() const;

    int y() const;

    static Position origin();
};

class Rectangle {
private:
    int widthValue;
    int heightValue;
    Position position;

public:
    Rectangle(int width, int height);

    Rectangle(int width, int height, Position pos);

    bool operator ==(const Rectangle& r) const;

    Rectangle& operator +=(Vector& v);

    Rectangle reflection();

    long long area();

    std::pair<Rectangle, Rectangle> split_horizontally(int place);

    std::pair<Rectangle, Rectangle> split_vertically(int place);

    int width();

    int height();

    Position pos();
};

class Rectangles {
private:
    std::vector<Rectangle> recsVector;

public:
    Rectangles();

    Rectangles(std::initializer_list<Rectangle> list);

    bool operator ==(const Rectangles& recsObj) const;

    Rectangles& operator +=(Vector& v);

    Rectangle& operator [](int i);

    size_t size();

    void split_horizontally(int idx, int place);

    void split_vertically(int idx, int place);
};

Position operator +(Position p, Vector& v);

Position operator +(Vector& v, Position p);

Vector operator +(Vector v1, Vector v2);

Rectangle operator +(Rectangle r, Vector& v);

Rectangle operator +(Vector& v, Rectangle r);

Rectangles operator +(Rectangles r, Vector& v);

Rectangles operator +(Vector& v, Rectangles r);

void merge_horizontally(Rectangle rect1, Rectangle rect2);

void merge_vertically(Rectangle rect1, Rectangle rect2);

// TODO

#endif // GEOMETRY_H
