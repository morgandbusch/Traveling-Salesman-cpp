#pragma once
#include <cmath>
#include <vector>
#include "node.h"

class MST_Node : public Node{
    public: 
        MST_Node(const Node &n, float priority){
            _x = n._x;
            _y = n._y;
            _priority = priority;
        }

        MST_Node(const Node &n): MST_Node(n, INFINITY) {}

        friend void mstnode_connect(MST_Node &n1, MST_Node &n2);
        void disconnect(MST_Node n);
        void set_priority(float p) {_priority = p;}
        void set_closest(MST_Node *n) {_closest = n;}
        MST_Node* get_closest() const {return _closest;}
        std::vector<MST_Node *> get_connections() {return _connections;}
        float get_priority() const {return _priority;}

        bool operator>(MST_Node n) {return _priority > n._priority;}
        bool operator<(MST_Node n) {return _priority < n._priority;}
    private:
        float _priority;
        MST_Node * _closest;
        std::vector<MST_Node *> _connections;
};

class MST {
    public:
        MST(){}
        MST(const std::vector<Node> &nodes);
        std::vector<MST_Node> get_nodes() const {return _nodes;}
        
    private:
        void prim();

        std::vector<MST_Node> _nodes;
        float _cost;
};