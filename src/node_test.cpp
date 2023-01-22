#include "node.h"
#include <cassert>
#include <cmath>
#include <iostream>

int main(){
    Node n1 = Node(0.0, 0.0);
    Node n2 = Node(0.0, 0.0);

    assert(n1.distance(n2) == 0.0);

    n2 = Node(3.0, 4.0);
    float x = n1.distance(n2);

    assert(n1.distance(n2) == 5.0);

    n1 = Node(1.3, 5.6);
    n2 = Node(5.4, 7.1);

    assert(round(n1.distance(n2) * 100) == round(4.36577599059*100));

    return 0;
}