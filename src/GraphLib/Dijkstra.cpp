#include "GraphLib.h"

namespace GraphLib {

void Dijkstra(Graph& g, Node& source) {
	
	// initially, all distances are infinite and all predecessors are null
	for(int i = 0; i < g.nodes.GetCount(); i++) {
		Node& n = g.nodes[i];
		n.distance = DBL_MAX;
		n.optimized = false;
	}

	// g.snapShot('Initially, all distances are infinite and all predecessors are null.');
	source.distance = 0;
	
	//  set of unoptimized nodes, sorted by their distance (but a Fibonacci heap
	//  would be better)
	BinaryMinHeap q(g.nodes);

	//  get the node with the smallest distance
	//  as long as we have unoptimized nodes. q.GetMin() can have O(log n).
	while (q.GetMin()) {
		
		// remove the latest
		Node& node = *q.ExtractMin();
		node.optimized = true;

		// no nodes accessible from this one, should not happen
		if (node.distance == DBL_MAX)
			throw Exc("Orphaned node!");

		// for each neighbour of node
		for(int i = 0; i < node.edges.GetCount(); i++) {
			Edge& e = *node.edges[i];
			
			Node& other = (&node == e.target) ? *e.source : *e.target;

			if (other.optimized)
				continue;

			// look for an alternative route
			double alt = node.distance + e.weight;

			// update distance and route if a better one has been found
			if (alt < other.distance) {
				
				// update distance of neighbour
				other.distance = alt;
				
				// update priority queue
				q.Heapify();
				
				// update path
				other.predecessor = &node;
			}
		}
	}
}

}
