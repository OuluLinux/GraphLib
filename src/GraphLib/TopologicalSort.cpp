#include "GraphLib.h"

namespace GraphLib {

TopologicalSort::TopologicalSort() {
	graph = NULL;
	processed = NULL;
}

void TopologicalSort::ProcessStartingPoint(Node* node) {
	if (node == NULL)
		throw Exc("You have a cycle!!");
	node->sort_importance -= node->edges.GetCount();
	processed->Add(node);
}


void TopologicalSort::PopulateIndegreesAndUnprocessed() {
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& n = graph->nodes[i];
		unprocessed.Add(&n);
		n.sort_importance = n.edges.GetCount();
	}
}


//    @param {Graph} graph
//    @returns {Array}
void TopologicalSort::Sort(Graph& graph, Vector<Node*>& processed) {
	this->graph = &graph;
	this->processed = &processed;
	
	processed.SetCount(0);
	unprocessed.SetCount(0);
	queue.SetCount(0);
	
	PopulateIndegreesAndUnprocessed();

	while (unprocessed.GetCount() > 0) {
		for (int i = 0; i < unprocessed.GetCount(); i++) {
			Node& node = *unprocessed[i];

			if (node.sort_importance == 0) {
				queue.Add(&node);
				unprocessed.Remove(i); // Remove this node, its all done.
				i--;// decrement i since we just removed that index from the iterated list;
			}
			else {
				node.sort_importance--;
				ASSERT(node.sort_importance >= 0);
			}
		}

		while (queue.GetCount() > 0) {
			Node* n = queue[0];
			queue.Remove(0);
			ProcessStartingPoint(n);
		}
	}
}

}
