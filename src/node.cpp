#include "node.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

float Node::distance(const Node &n) const {
    float dx = abs(n._x - _x);
    float dy = abs(n._y - _y);
    return sqrt(pow(dx, 2) + pow(dy,2));
}

float distance(const Node &n1, const Node &n2) {
    float dx = abs(n1.get_x() - n2.get_x());
    float dy = abs(n1.get_y() - n2.get_y());
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

std::ostream& operator<<(std::ostream& os, const Node& n) {
    os << "(" << n._x << ", " << n._y << ")";
    return os;
}