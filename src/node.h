#pragma once
#include <iostream>

class MST_Node;

class Node{
    friend class MST_Node;
    public:
        Node(float x, float y): _x(x), _y(y) {}
        Node(): Node(0, 0) {};

        float get_x() const {return _x;}
        float get_y() const {return _y;}

        float distance(const Node &n) const;

        friend std::ostream& operator<<(std::ostream& os, const Node& n);
        inline friend bool operator==(const Node & n1, const Node & n2);

    private:
        float _x;
        float _y;
};

inline bool operator==(const Node & n1, const Node & n2){
    return (n1._x == n2._x) && (n1._y == n2._y);
}