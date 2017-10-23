#include "GraphLib.h"

namespace GraphLib {

Node::Node() : layout_pos_x(0), layout_pos_y(0), sort_importance(0), optimized(false) {
	predecessor = NULL;
	sz = Size(60, 40);
	shape = SHAPE_ELLIPSE;
	line_clr = Red();
	fill_clr = White();
	line_width = 1;
	distance = 1;
	point.x = 0;
	point.y = 0;
	layout_force_x = 0;
	layout_force_y = 0;
}

Node::Node(const Node& src) {
	predecessor = NULL;
	
	#define COPY(x) x = src.x
	COPY(id);
	COPY(line_clr);
	COPY(fill_clr);
	COPY(point);
	COPY(layout_pos_x);
	COPY(layout_pos_y);
	COPY(layout_force_x);
	COPY(layout_force_y);
	COPY(distance);
	COPY(line_width);
	COPY(shape);
	COPY(sort_importance);
	COPY(sz);
	COPY(optimized);
	edges <<= edges;
	#undef COPY
}

Node& Node::SetLabel(String s) {
	label = s;
	sz = MinFactor(GetTextSize(label, Arial(12)), 4, 3);
	return *this;
}








Graph::Graph() {
	layout_max_x = 1920;
	layout_min_x = 320;
	layout_max_y = 1080;
	layout_min_y = 240;
	fill_clr = White();
	border_clr = Red();
	line_clr = Black();
	node_line_width = 2;
	edge_line_width = 1;
}

Node& Graph::AddNode(String id, Node* copy_data_from) {
	if (nodes.Find(id) != -1)
		return nodes.Get(id);
	Node& n = !copy_data_from ? nodes.Add(id) : nodes.Add(id, *copy_data_from);
	if (!copy_data_from) {
		n.fill_clr = fill_clr;
		n.line_clr = border_clr;
		n.line_width = node_line_width;
	}
	n.id = id;
	n.sz = MinFactor(GetTextSize(id, Arial(12)), 4, 3); // one time only
	return n;
}

Edge& Graph::AddEdge(int source, int target, double weight, Edge* copy_data_from) {
	return AddEdge(IntStr(source), IntStr(target), weight, copy_data_from);
}

Edge& Graph::AddEdge(String source, String target, double weight, Edge* copy_data_from) {
	ASSERT_(weight > 0.0, "Only positive weight is allowed");
	Node& source_node = AddNode(source);
	Node& target_node = AddNode(target);
	Edge& e = !copy_data_from ? edges.Add() : edges.Add(*copy_data_from);
	if (!copy_data_from) {
		e.stroke_clr = line_clr;
		e.line_width = edge_line_width;
	}
	e.weight = weight;
	e.source = &source_node;
	e.target = &target_node;
	source_node.edges.Add(&e);
	target_node.edges.Add(&e);
	return e;
}

void Graph::RemoveNode(String id) {
	int i = nodes.Find(id);
	Node& node = nodes[i];
	
	// Delete node from all the edges
	for(int i = 0; i < edges.GetCount(); i++) {
		Edge& edge = edges[i];
		if (edge.source == &node || edge.target == &node)
			RemoveEdge(edge);
	}
	
	// Delete node from index
	nodes.Remove(i);
}

void Graph::RemoveEdge(Edge& source_edge) {
	Edge* found = NULL;
	int found_pos = -1;
	Node* target = source_edge.target;
	Node* source = source_edge.source;
	
	// Find and remove edge
	for(int i = 0; i < edges.GetCount(); i++) {
		Edge& edge = edges[i];
		if (edge.source->id == source->id && edge.target->id == target->id) {
			found = &edge;
			found_pos = i;
			break;
		}
	}
	
	if (found) {
		for(int i = 0; i < found->source->edges.GetCount(); i++) {
			if (found->source->edges[i] == found) {
				found->source->edges.Remove(i);
				i--;
			}
		}
		for(int i = 0; i < found->target->edges.GetCount(); i++) {
			if (found->target->edges[i] == found) {
				found->target->edges.Remove(i);
				i--;
			}
		}
		edges.Remove(found_pos);
	}
}

void Graph::Clear() {
	nodes.Clear();
	edges.Clear();
}

}
