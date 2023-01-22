#include "path.h"
#include "node.h"
#include <cassert>
#include <vector>
#include <iostream>

int main(){
    Node n0 = Node(0.0, 0.0);
    Node n1 = Node(1.0, 1.0);
    Node n2 = Node(2.0, 2.0);
    Node n3 = Node(3.0, 3.0);

    Path p1 = Path({&n0, &n1, &n2, &n3});
    p1.swap_connection(0, 3);
    std::cout << p1[0] << std::endl;
    p1.print();

    assert(p1 == (Path({&n0, &n3, &n2, &n1})));

    Node n4 = Node(4.0, 4.0);
    Node n5 = Node(5.0, 5.0);

    p1 = Path({&n0, &n1, &n2, &n3, &n4, &n5});
    //p1.swap_connection(1, 4);
    //p1.print();
    //assert(p1 == (Path({&n0, &n1, &n4, &n3, &n2, &n5})));

    return 0;
}