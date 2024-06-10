#pragma once
#include "node.h"
#include "path.h"
#include "manager.h"
#include "mst.h"
#include "implot.h"
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

        void draw_bounds();

    private:

        const ImVec4 NODE_COLOR = ImVec4(0,.5,.7,1);

        const ImVec4 CURRENT_PATH_COLOR = ImVec4(0, .33f, 1, 1);
        const ImVec4 BEST_PATH_COLOR = ImVec4(.75, .7, 0, .05);
        const int BEST_PATH_WIDTH = 15;
        const ImVec4 MST_COLOR = ImVec4(0,.5f,.2f,1);

        const ImVec4 BOUNDS_COLOR = ImVec4(1, 0, 0, 1);

        void raw_plot_path(const Path &path);
        ImPlotContext *pctx;
        Manager *_manager;

        
};

Plotter::Plotter(Manager *manager) {
    pctx = ImPlot::CreateContext(); 
    _manager = manager;
}
