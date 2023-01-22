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


void Plotter::plot_nodes(const std::vector<Node> nodes) {


    const int size = nodes.size();
    
    float xs[size];
    float ys[size];

    for(int i = 0; i < size; i++){
        xs[i] = nodes[i].get_x();
        ys[i] = nodes[i].get_y();

    }

    ImPlot::SetCurrentContext(pctx);

    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4, ImVec4(0,.5,.7,1), IMPLOT_AUTO, ImVec4(0,.5,.7,1));
    ImPlot::PlotScatter("Nodes", xs, ys, size);
    
    
     
}

void Plotter::plot_path(const Path &path) {
    raw_plot_path(path);
}

void Plotter::plot_path(const Path &path, const ImVec4& col) {
    ImPlot::SetCurrentContext(pctx);
    ImPlot::SetNextLineStyle(col);

    raw_plot_path(path);
    
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


void Plotter::plot_mst(const MST &m){
    ImPlot::SetCurrentContext(pctx);
    
    std::vector<MST_Node> nodes = m.get_nodes();
    for(MST_Node n1 : nodes){
        for(MST_Node *n2: n1.get_connections()){
            float x1 = n1.get_x();
            float y1 = n1.get_y();
            float x2 = n2->get_x();
            float y2 = n2->get_y();

            float xs[2] = {x1, x2};
            float ys[2] = {y1, y2};

            ImPlot::SetNextLineStyle(ImVec4(0,.5f,.2f,1));
            ImPlot::PlotLine("MST", xs, ys, 2);
        }
    }
}



void Plotter::load_bounds(const Manager & m) {
    _lower_x = m.get_lower_x();
    _upper_x = m.get_upper_x();
    _lower_y = m.get_lower_y();
    _upper_y = m.get_upper_y();
}