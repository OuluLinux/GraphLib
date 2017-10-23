#include "GraphLib.h"

namespace GraphLib {

Spring::Spring(Graph& graph) : Layout(graph) {
	iterations = 500;
	maxRepulsiveForceDistance = 6;
	k = 2;
	c = 0.01;
	maxVertexMovement = 0.5;
}

double Spring::GetRandom() {
	if (random_cursor == randoms.GetCount()) {
		random_cursor++;
		return randoms.Add(Randomf());
	} else {
		return randoms[random_cursor++];
	}
}

void Spring::Randomize() {
	randoms.Clear();
}

void Spring::RefreshLayout() {
	LayoutPrepare();

	for (int i = 0; i < iterations; i++)
		LayoutIteration();

	LayoutCalcBounds();
}

void Spring::LayoutPrepare() {
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		node.layout_pos_x = 0;
		node.layout_pos_y = 0;
		node.layout_force_x = 0;
		node.layout_force_y = 0;
	}
	random_cursor = 0;
}

void Spring::LayoutIteration() {
	
	// Forces on nodes due to node-node repulsions
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node1 = graph->nodes[i];
		
		for(int j = 0; j < i; j++) {
			Node& node2 = graph->nodes[j];
			LayoutRepulsive(node1, node2);
		}
	}
	
	// Forces on nodes due to edge attractions
	for(int i = 0; i < graph->edges.GetCount(); i++) {
		Edge& edge = graph->edges[i];
		LayoutAttractive(edge);
	}
	
	// Move by the given force
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		
		double xmove = c * node.layout_force_x;
		double ymove = c * node.layout_force_y;
		double max   = maxVertexMovement;

		if (xmove > max)  xmove = +max;
		if (xmove < -max) xmove = -max;
		if (ymove > max)  ymove = +max;
		if (ymove < -max) ymove = -max;

		node.layout_pos_x += xmove;
		node.layout_pos_y += ymove;
		node.layout_force_x = 0;
		node.layout_force_y = 0;
	}
}

void Spring::LayoutRepulsive(Node& node1, Node& node2) {
	
	double dx = node2.layout_pos_x - node1.layout_pos_x;
	double dy = node2.layout_pos_y - node1.layout_pos_y;
	double d2 = dx * dx + dy * dy;

	if (d2 < 0.01) {
		dx = 0.1 * GetRandom() + 0.1;
		dy = 0.1 * GetRandom() + 0.1;
		d2 = dx * dx + dy * dy;
	}

	double d = sqrt(d2);

	if (d < maxRepulsiveForceDistance) {
		double repulsiveForce = k * k / d;
		node2.layout_force_x += repulsiveForce * dx / d;
		node2.layout_force_y += repulsiveForce * dy / d;
		node1.layout_force_x -= repulsiveForce * dx / d;
		node1.layout_force_y -= repulsiveForce * dy / d;
	}
}

void Spring::LayoutAttractive(Edge& edge) {
	Node& node1 = *edge.source;
	Node& node2 = *edge.target;
	double dx = node2.layout_pos_x - node1.layout_pos_x;
	double dy = node2.layout_pos_y - node1.layout_pos_y;
	double d2 = dx * dx + dy * dy;

	if (d2 < 0.01) {
		dx = 0.1 * GetRandom() + 0.1;
		dy = 0.1 * GetRandom() + 0.1;
		d2 = dx * dx + dy * dy;
	}

	double d = sqrt(d2);

	if (d > maxRepulsiveForceDistance) {
		d = maxRepulsiveForceDistance;
		d2 = d * d;
	}

	double attractiveForce = (d2 - k * k) / k;

	if (!edge.attraction)
		edge.attraction = 1;

	attractiveForce *= log((double)edge.attraction) * 0.5 + 1;
	node2.layout_force_x -= attractiveForce * dx / d;
	node2.layout_force_y -= attractiveForce * dy / d;
	node1.layout_force_x += attractiveForce * dx / d;
	node1.layout_force_y += attractiveForce * dy / d;
}

}
