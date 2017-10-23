#ifndef _GraphLib_OrderedTree_h_
#define _GraphLib_OrderedTree_h_

#include "Layout.h"
#include "TopologicalSort.h"

//    OrderedTree is like Ordered but assumes there is one root
//    This way we can give non random positions to nodes on the Y-axis
//    It assumes the ordered nodes are of a perfect binary tree
namespace GraphLib {

class OrderedTree : public Layout {
	Vector<Node*> order;
	bool src_graph;
	
public:
	OrderedTree(Graph& graph);
	OrderedTree(Graph& graph, const Vector<Node*>& order);
	void RefreshOrders();
	virtual void RefreshLayout();
	void LayoutPrepare();
	void Sort();
};

}

#endif
