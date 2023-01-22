#include "plotter.h"
#include "node.h"
#include "path.h"
#include "../imgui/implot.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>



bool Plotter::start_plot(ImVec2 winsize) {
    if(ImPlot::BeginPlot("Scatter Plot", winsize, ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoChild)){
        ImPlot::SetupAxis(ImAxis_X1, "X", ImPlotAxisFlags_NoDecorations | ImPlotAxisFlags_NoHighlight | ImPlotAxisFlags_Lock);
        ImPlot::SetupAxis(ImAxis_Y1, "Y", ImPlotAxisFlags_NoDecorations | ImPlotAxisFlags_NoHighlight | ImPlotAxisFlags_Lock);
        ImPlot::SetupAxisLimits(ImAxis_Y1, _lower_y-2, _upper_y+2);
        ImPlot::SetupAxisLimits(ImAxis_X1, _lower_x-2, _upper_x+2);

        return true;
    }
    
    return false;
}


void Plotter::plot_nodes(const std::vector<Node> nodes, bool draw) {


    const int size = nodes.size();
    
    float xs[size];
    float ys[size];

    for(int i = 0; i < size; i++){
        xs[i] = nodes[i].get_x();
        ys[i] = nodes[i].get_y();

    }

    if(draw){
        ImPlot::SetCurrentContext(pctx);


        ImPlot::PlotScatter("Nodes", xs, ys, size);


        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(1));
        ImPlot::PopStyleVar();
    }
    
     
}

void Plotter::plot_path(const Path &path) {
    raw_plot_path(path);
}

void Plotter::plot_path(const Path &path, const ImVec4& col) {
    ImPlot::SetCurrentContext(pctx);
    ImPlot::SetNextLineStyle(col);

    raw_plot_path(path);
    
    ImPlot::SetNextLineStyle(IMPLOT_AUTO_COL);
}

void Plotter::raw_plot_path(const Path &path){
    int size = path.size();

    float xs[size+1];
    float ys[size+1];
    
    for (int i = 0; i < size; i++){
        Node n = path[i];
        xs[i] = n.get_x();
        ys[i] = n.get_y();
    }
    Node n = path[0];
    xs[size] = n.get_x();
    ys[size] = n.get_y();
    
    // get label with cost
    std::string label = "Path (" + std::to_string(path.get_cost()) + ")";
    
    ImPlot::SetCurrentContext(pctx);
    ImPlot::PlotLine(label.c_str(), xs, ys, size+1);

}

void Plotter::load_bounds(const Manager & m) {
    _lower_x = m.get_lower_x();
    _upper_x = m.get_upper_x();
    _lower_y = m.get_lower_y();
    _upper_y = m.get_upper_y();
}