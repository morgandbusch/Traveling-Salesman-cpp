#pragma once
#include <vector>
#include <cmath>
#include "node.h"
#include "path.h"
#include "mst.h"

class Manager {
    public:
        Manager() {
            _lower_x = 0;
            _lower_y = 0;
            _upper_x = 20;
            _upper_y = 20;

            _nodes = std::vector<Node>(); 
            reset_current_path();
        }

        void populate(int n);
        bool exists(const Node & node);
        const std::vector<Node> & get_nodes() const {return _nodes;}
        void reset_current_path();
        void reset_best_path();
        void reset_paths();

        Path get_current_path() const {return _current_path;}
        Path get_best_path() const {return _best_path;}
        float get_best_cost() const {return _best_cost;}
        MST get_mst() const {return _mst;}



        void random_2swap(float p);

        void add_nodes(int n);

        float get_lower_x() const {return _lower_x;}
        float get_upper_x() const {return _upper_x;}
        float get_lower_y() const {return _lower_y;}
        float get_upper_y() const {return _upper_y;}

    private:
        void nodes_modified();

        float _lower_x;
        float _lower_y;
        float _upper_x;
        float _upper_y;

        Path _current_path;
        Path _best_path;

        float _best_cost;

        std::vector<Node> _nodes;

        MST _mst;
};