#pragma once
#include "node.h"
#include "path.h"
#include "manager.h"
#include "mst.h"
#include "../imgui/implot.h"
#include <vector>


class Plotter {
    public:
        Plotter(Manager *manager);

        bool start_plot(ImVec2 size);


        void plot_nodes() const;
        void plot_current_path();
        void plot_best_path();
        void plot_mst();


        void end_plot() {ImPlot::EndPlot();}

        void load_bounds(const Manager & m);

    private:

        const ImVec4 NODE_COLOR = ImVec4(0,.5,.7,1);

        const ImVec4 CURRENT_PATH_COLOR = ImVec4(0, .33f, 1, 1);
        const ImVec4 BEST_PATH_COLOR = ImVec4(.75, .7, 0, .05);
        const int BEST_PATH_WIDTH = 15;
        const ImVec4 MST_COLOR = ImVec4(0,.5f,.2f,1);

        void raw_plot_path(const Path &path);
        ImPlotContext *pctx;
        Manager *_manager;

        float _lower_x;
        float _lower_y;
        float _upper_x;
        float _upper_y;
};

Plotter::Plotter(Manager *manager) {
    pctx = ImPlot::CreateContext(); 
    _manager = manager;

    _lower_x = 0;
    _lower_y = 0;
    _upper_x = 20;
    _upper_y = 20;
}