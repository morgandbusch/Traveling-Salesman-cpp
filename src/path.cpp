#include "path.h"
#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>

float Path::get_cost() const {
    const int size = _nodes.size();
    float cost = _nodes[0]->distance(*(_nodes[size-1]));

    for(int i = 1; i < size; i++){
        cost += _nodes[i]->distance(*(_nodes[i-1]));
    }

    return cost;
}

void Path::swap_connection(int a, int b) {
    int i = std::min(a, b);
    int j = std::max(a, b);
    std::vector<const Node *> new_nodes = _nodes;

    std::reverse(new_nodes.begin() + i+1, new_nodes.begin() + j + 1);

    _nodes = new_nodes;
    return;
}

//Returns cost
float Path::try_swap(int a, int b) {
    float cost = this->get_cost();
    Path p = this->copy();
    p.swap_connection(a, b);
    float new_cost = p.get_cost();

    if(new_cost < cost){
        _nodes = p._nodes;
        return new_cost;
    }
    return cost;
}

//Returns cost
float Path::try_swap(int is[], int n){
    float cost = this->get_cost();
    Path p = this->copy();

    p.swap_connection(is[0], is[n-1]);
    for(int i = 0; i < n+1; i++){
        p.swap_connection(is[n-i-1], is[n-i]);
    }
    float new_cost = p.get_cost();

    if(new_cost < cost){
        _nodes = p._nodes;
        return new_cost;
    }
    return cost;
}

void Path::print() const {
    for(const Node * n : _nodes) {
        std::cout << *n << " ";
    }
}

