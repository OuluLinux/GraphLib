#ifndef _GraphLib_Spring_h_
#define _GraphLib_Spring_h_

#include "Layout.h"

//    TODO take ratio into account
//    TODO use integers for speed
namespace GraphLib {

class Spring : public Layout {
	Vector<double> randoms;
	int random_cursor;
	double maxRepulsiveForceDistance;
	double maxVertexMovement;
	double c;
	int iterations;
	int k;
	
	double GetRandom();
	
public:
	Spring(Graph& graph);
	virtual void Randomize();
	virtual void RefreshLayout();
	virtual void LayoutPrepare();
	void LayoutIteration();
	void LayoutRepulsive(Node& node1, Node& node2);
	void LayoutAttractive(Edge& edge);
};

}

#endif
