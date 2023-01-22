#pragma once
#include "node.h"
#include <vector>

class Path{
    public:
        Path(std::vector<const Node *> nodes): _nodes(nodes) {}
        Path(): Path(std::vector<const Node *>()) {}

        inline Path copy() const {return Path(_nodes);}

        float get_cost() const;
        void add_node(const Node * n) {_nodes.push_back(n);}
        
        const Node operator[](int i) const {return *_nodes[i];}
        int size() const {return _nodes.size();}
        void swap_connection(int a, int b);
        float try_swap(int a, int b);
        float try_swap(int is[], int n);

        bool operator==(const Path &p) const {return _nodes == p._nodes;}

        void print() const;

    private:
        std::vector<const Node *> _nodes;
};