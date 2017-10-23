#include "GraphLib.h"

namespace GraphLib {

OrderedTree::OrderedTree(Graph& graph) : Layout(graph) {
	src_graph = true;
	RefreshOrders();
}

OrderedTree::OrderedTree(Graph& graph, const Vector<Node*>& order) : Layout(graph) {
	src_graph = false;
	this->order <<= order;
}

void OrderedTree::RefreshOrders() {
	Sort();
}

void OrderedTree::RefreshLayout() {
	if (src_graph) RefreshOrders();
	LayoutPrepare();
	LayoutCalcBounds();
}

void OrderedTree::LayoutPrepare() {
	// To reverse the order of rendering, we need to find out the
	// absolute number of levels we have. simple log math applies.
	int node_count = order.GetCount();
	int level_count = log((double)node_count+1.0) / log((double)2);
	int counter = 1;
	for (int i = 0; i < order.GetCount(); i++) {
		Node& node = *order[i];
		
		// Rank aka x coordinate
		int rank = log((double)counter) / log((double)2);
		
		// File relative to top
		int file = counter - pow((double)rank, 2);
		node.layout_pos_x = rank;
		node.layout_pos_y = file;
		counter++;
	}
}

void OrderedTree::Sort() {
	TopologicalSort top;
	top.Sort(*graph, order);
}

}
