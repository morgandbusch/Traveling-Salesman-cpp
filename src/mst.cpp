#include "mst.h"
#include <cassert>
#include <algorithm>
#include <vector>


void mstnode_connect(MST_Node &n1, MST_Node &n2){
    n1._connections.push_back(&n2);
    n2._connections.push_back(&n1);
}

void MST_Node::disconnect(MST_Node n) {
    for(auto itr = _connections.begin(); itr != _connections.end(); itr++){
        if(**itr == n){
            _connections.erase(itr);
            return;
        }
    }
}

MST::MST(const std::vector<Node> &nodes) {
    assert(("Nodes exist", nodes.size() > 0));
    for( auto node : nodes) {
        _nodes.push_back(MST_Node(node));
    }
    _nodes[0].set_priority(0);
    prim();
}

bool mst_greater(MST_Node *n1, MST_Node *n2){
    return( *n1 > *n2);
}

void MST::prim() {
    // create list of notes we can work with
    std::vector<MST_Node*> node_ptrs;
    for(int i = 0; i < _nodes.size(); i++){
        node_ptrs.push_back(&_nodes[i]);
    }

    // get first node
    MST_Node *current_node = node_ptrs[0];
    node_ptrs.erase(node_ptrs.begin());

    while(node_ptrs.size() > 0){

        // assign priority
        for (MST_Node *n : node_ptrs) {
            float current_priority = current_node->distance(*n);
            float previous_priority = n->get_priority();

            if(previous_priority > current_priority){
                n->set_priority(current_priority);
                n->set_closest(current_node);
            }
        }

        // make min heap
        std::make_heap(node_ptrs.begin(), node_ptrs.end(), mst_greater);

        // consider node closest to MST
        std::pop_heap(node_ptrs.begin(), node_ptrs.end(), mst_greater);
        current_node = node_ptrs.back();
        node_ptrs.pop_back();

        // add u to MST by connecting it to closest node
        mstnode_connect(*current_node, *(current_node->get_closest()));

    }

}