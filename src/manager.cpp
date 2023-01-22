#include "manager.h"
#include "algs.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>


void Manager::add_nodes(int n){
    for(int i = 0; i < n; i++){
        // std::cout << "i=" << i << std::endl;
        Node node;
        do{
            float x = randrange(_lower_x, _upper_x);
            float y = randrange(_lower_y, _upper_y);
            node = Node(x, y);
        } while (exists(node));
        // std::cout << "adding node" << std::endl;
        _nodes.push_back(node);
    }
}


void Manager::populate(int n) {
    _nodes = std::vector<Node>(n);
    add_nodes(n);
}

bool Manager::exists(const Node & node){
    for(const Node & n : _nodes){
        if(n == node){
            return true;
        }
    }
    return false;
}

void Manager::reset_current_path() {
    int size = _nodes.size();
    std::vector<const Node*> pnodes = std::vector<const Node*>(size);

    for(int i = 0; i < size; i++){
        pnodes[i] = &_nodes[i];
    }

    _current_path = Path(pnodes);
}

void Manager::reset_best_path() {
    _best_path = _current_path.copy();
    _best_cost = _best_path.get_cost();
}

void Manager::reset_paths(){
    this->reset_current_path();
    _best_path = _current_path.copy();
    _best_cost = _best_path.get_cost();
}


void Manager::random_2swap(float p) {
    int upper = _current_path.size() - 1;
    
    //Generate unique indices a and b for _nodes vector
    int a = std::round(randrange(0, upper));
    int b = std::round(randrange(0, upper));
    while(b == a){
        b = std::floor(randrange(0, upper));
    }

    //Accept even if worse path with probability p
    //Note: May be redundant to try swap then force, but try_swap sets best_path if better
    float rng = std::rand() / (float) RAND_MAX;
    float cost = _current_path.try_swap(a, b);

    if( cost <= _best_cost ){
        _best_path = _current_path.copy();
        _best_cost = cost;
    }


    if(rng <= p){ 
        _current_path.swap_connection(a, b);
    }
}