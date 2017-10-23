#include "GraphLib.h"

namespace GraphLib {

Layout::Layout(Graph& graph) {
	this->graph = &graph;
}

Layout::~Layout() {}

void Layout::Randomize() {}

void Layout::RefreshLayout() {
	InitCoords();
	LayoutPrepare();
	LayoutCalcBounds();
}

void Layout::InitCoords() {
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		node.layout_pos_x = 0;
		node.layout_pos_y = 0;
	};
}

void Layout::LayoutPrepare() {
	throw Exc("not implemented");
}

void Layout::LayoutCalcBounds() {
	double minx = +DBL_MAX;
	double maxx = -DBL_MAX;
	double miny = +DBL_MAX;
	double maxy = -DBL_MAX;
	
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		double x = node.layout_pos_x;
		double y = node.layout_pos_y;
		if (x > maxx) maxx = x;
		if (x < minx) minx = x;
		if (y > maxy) maxy = y;
		if (y < miny) miny = y;
	}
	ASSERT(minx != maxx);
	ASSERT(miny != maxy);
	graph->layout_min_x = minx;
	graph->layout_max_x = maxx;
	graph->layout_min_y = miny;
	graph->layout_max_y = maxy;
}

}
