#ifndef _GraphLib_Renderer_h_
#define _GraphLib_Renderer_h_

namespace GraphLib {


//    Base class for rendering nodes
//
//    Can transform coordinates to fit onto the canvas
class Renderer {
	Vector<Point> bezier_path, diam, arrow;
	
protected:
	Graph* graph;
	double factor_x, factor_y;
	Size pt_sz;
	int border;
	
public:

	Renderer(Graph& graph);
	virtual ~Renderer();
	
	Node* FindNode(Point pt);
	void SetBorder(int i);
	void SetImageSize(Size sz, int border=-1);
	
	// Scale the nodes within the canvas dimensions
	// Keep a distance to the canvas edges of half a node radius
	void Paint(Draw& id);
	
	Pointf Translate(Pointf point);
	
	// coordinates for potential connection coordinates from/to the objects
	void GetConnectionPoints(const Node& obj1, const Node& obj2, Vector<Point>& pts);
	virtual void DrawNode(Draw& w, Node& node);
	virtual void DrawEdge(Draw& w, Edge& edge);
	
};

}

#endif
