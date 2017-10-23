#ifndef _GraphLib_Graph_h
#define _GraphLib_Graph_h

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace GraphLib {
struct Node;

struct Edge : Moveable<Edge> {
	
	Node *source, *target;
	Color stroke_clr;
	String label;
	double weight;
	int line_width;
	bool attraction;
	bool directed;
	
	Edge() : source(NULL), target(NULL), attraction(false), weight(1), directed(false) {
		stroke_clr = Black();
		line_width = 1;
		weight = 1;
	}
	
	Edge& SetDirected(bool b=true) {directed = b; return *this;}
	Edge& SetLabel(String lbl) {label = lbl; return *this;}
	Edge& SetStroke(int line_width, Color clr) {this->line_width = line_width; stroke_clr = clr; return *this;}
	Edge& SetWeight(double d) {weight = d; return *this;}
	
	double GetWeight() const {return weight;}
	
};

inline Size MinFactor(Size sz, int w, int h) {
	sz *= 2.2;
	double factor = (double)sz.cx / sz.cy;
	double target = (double)w / h;
	if (factor < target)
		sz.cx = sz.cy * target;
	return sz;
}

struct Node : Moveable<Node> {
	Node* predecessor;
	String id, label;
	Color line_clr, fill_clr;
	Pointf point;
	double layout_pos_x, layout_pos_y;
	double layout_force_x, layout_force_y;
	double distance;
	int line_width;
	int shape;
	int sort_importance;
	Size sz;
	bool optimized;
	Vector<Edge*> edges;
	
	enum {SHAPE_ELLIPSE, SHAPE_RECT, SHAPE_DIAMOND};
	
	Node();
	Node(const Node& src);
	
	Rect GetBoundingBox() const {return RectC(point.x - sz.cx/2, point.y - sz.cy/2, sz.cx, sz.cy);}
	
	Node& SetSize(Size sz) {this->sz = sz; return *this;}
	Node& SetLabel(String s);
	Node& SetShapeEllipse() {shape = SHAPE_ELLIPSE; return *this;}
	Node& SetShapeRectangle() {shape = SHAPE_RECT; return *this;}
	Node& SetShapeDiamond() {shape = SHAPE_DIAMOND; return *this;}
	Node& SetStroke(int line_width, Color clr) {this->line_width = line_width; line_clr = clr; return *this;}
	Node& SetFill(Color clr) {fill_clr = clr; return *this;}
	
};


// Graph Data Structure
class Graph {
	
protected:
	friend class Renderer;
	friend class Layout;
	friend class TournamentTree;
	friend class TopologicalSort;
	friend class Spring;
	friend class TournamentTree;
	friend class OrderedTree;
	friend void Dijkstra(Graph& g, Node& source);
	
	ArrayMap<String, Node> nodes;
	Array<Edge> edges;
	Color fill_clr, border_clr, line_clr;
	double layout_max_x, layout_min_x;
	double layout_max_y, layout_min_y;
	int node_line_width, edge_line_width;
	
public:
	Graph();


	Graph& SetFillColor(Color clr) {fill_clr = clr; return *this;}
	Graph& SetNodeStroke(int line_width, Color clr) {node_line_width = line_width; border_clr = clr; return *this;}
	Graph& SetEdgeStroke(int line_width, Color clr) {edge_line_width = line_width; line_clr = clr; return *this;}
	
	int GetEdgeCount() const {return edges.GetCount();}
	int GetNodeCount() const {return nodes.GetCount();}
	Edge& GetEdge(int i) {return edges[i];}
	Node& GetNode(int i) {return nodes[i];}
	
	//    Add node if it doesn't exist yet.
	//
	//    This method does not update an existing node.
	//    If you want to update a node, just update the node object.
	//
	//    @param {string|number|object} id or node data
	//    @param {object|} node_data (optional)
	//    @returns {Node} the new or existing node
	Node& AddNode(String id, Node* copy_data_from=NULL);

	//    @param {string|number|object} source node or ID
	//    @param {string|number|object} target node or ID
	//    @param {object|} (optional) edge data, e.g. styles
	//    @returns {Edge}
	
	Edge& AddEdge(int source, int target, double weight=1.0, Edge* copy_data_from=NULL);
	Edge& AddEdge(String source, String target, double weight=1.0, Edge* copy_data_from=NULL);

	//    @param {string|number|Node} node node or ID
	//    @return {Node}
	void RemoveNode(String id);

	//    Remove an edge by providing either two nodes (or ids) or the edge instance
	//    @param {string|number|Node|Edge} node edge, node or ID
	//    @param {string|number|Node} node node or ID
	//    @return {Edge}
	void RemoveEdge(Edge& source_edge);
	
	
	void Clear();
};

}

#endif
