#ifndef _GraphLib_TopologicalSort_h_
#define _GraphLib_TopologicalSort_h_

#include "Graph.h"

namespace GraphLib {

class TopologicalSort {
	Vector<Node*>* processed;
	Vector<Node*> unprocessed;
	Vector<Node*> queue;
	Graph* graph;
public:
	
	TopologicalSort();
	void ProcessStartingPoint(Node* node);
	void PopulateIndegreesAndUnprocessed();
	//    @param {Graph} graph
	//    @returns {Array}
	void Sort(Graph& graph, Vector<Node*>& processed);
};

}

#endif
