#pragma once
#include "node.h"
#include "path.h"
#include "manager.h"
#include "mst.h"
#include "../imgui/implot.h"
#include <vector>


class Plotter {
    public:
        Plotter();

        bool start_plot(ImVec2 size);


        void plot_nodes(const std::vector<Node> nodes);
        void plot_path(const Path &path);
        void plot_path(const Path &path, const ImVec4& col);
        void plot_mst(const MST &m);


        void end_plot() {ImPlot::EndPlot();}

        void load_bounds(const Manager & m);

    private:

        void raw_plot_path(const Path &path);
        ImPlotContext *pctx;

        float _lower_x;
        float _lower_y;
        float _upper_x;
        float _upper_y;
};

Plotter::Plotter() {
    pctx = ImPlot::CreateContext(); 
    
    _lower_x = 0;
    _lower_y = 0;
    _upper_x = 20;
    _upper_y = 20;
}