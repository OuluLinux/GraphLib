#include "GraphLib.h"

namespace GraphLib {

TournamentTree::TournamentTree(Graph& graph) : Layout(graph) {
	src_graph = true;
	RefreshOrders();
}

TournamentTree::TournamentTree(Graph& graph, const Vector<Node*>& order) : Layout(graph) {
	src_graph = false;
	this->order <<= order;
}

void TournamentTree::RefreshOrders() {
	order.Clear();
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		order.Add(&graph->nodes[i]);
	}
}

void TournamentTree::RefreshLayout() {
	if (src_graph) RefreshOrders();
	LayoutPrepare();
	LayoutCalcBounds();
}

void TournamentTree::LayoutPrepare() {
	for (int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		node.layout_pos_x = 0;
		node.layout_pos_y = 0;
	}
	
	// To reverse the order of rendering, we need to find out the
	// absolute number of levels we have. simple log math applies.
	int node_count = order.GetCount();
	int level_count = log((double)node_count + 1.0) / log((double)2);
	int counter = 1;
	
	for (int i = 0; i < order.GetCount(); i++) {
		Node& node = *order[i];
		int depth = log((double)counter) / log(2.0);
		int offset = pow(2.0, (double)(level_count - depth));
		int final_x = offset + (counter - pow(2.0, (double)depth)) * pow(2.0, (double)(level_count - depth) + 1.0);
		node.layout_pos_x = final_x;
		node.layout_pos_y = depth;
		counter++;
	}
}

}
