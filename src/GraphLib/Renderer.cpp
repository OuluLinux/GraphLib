#include "GraphLib.h"

namespace GraphLib {

Renderer::Renderer(Graph& graph) {
	this->graph = &graph;
	border = 40;
	factor_x = 0;
	factor_y = 0;
	pt_sz = Size(1,1);
}

Renderer::~Renderer() {}

Node* Renderer::FindNode(Point pt) {
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& n = graph->nodes[i];
		if (n.GetBoundingBox().Contains(pt))
			return &n;
	}
	return NULL;
}

void Renderer::SetBorder(int i) {border = i;}

void Renderer::SetImageSize(Size sz, int border) {
	if (border == -1)
		border = min(sz.cx, sz.cy) * 0.2;
	this->border = border;
	
	//Rect r(sz);
	
	pt_sz = sz;
	int width = sz.cx;
	int height = sz.cy;
	
	factor_x = (double)(width - border * 2)  / (graph->layout_max_x - graph->layout_min_x);
	factor_y = (double)(height - border * 2) / (graph->layout_max_y - graph->layout_min_y);
	
	
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		node.point = Translate(Pointf(node.layout_pos_x, node.layout_pos_y));
		//ASSERT(node.layout_pos_x >= graph->layout_min_x && node.layout_pos_x <= graph->layout_max_x);
		//ASSERT(node.layout_pos_y >= graph->layout_min_y && node.layout_pos_y <= graph->layout_max_y);
		//ASSERT(r.Contains(node.point));
	}
}

// Scale the nodes within the canvas dimensions
// Keep a distance to the canvas edges of half a node radius
void Renderer::Paint(Draw& id) {
	id.DrawRect(pt_sz, White());
	
	for(int i = 0; i < graph->edges.GetCount(); i++) {
		Edge& edge = graph->edges[i];
		DrawEdge(id, edge);
	}
	
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		DrawNode(id, node);
	}
}

Pointf Renderer::Translate(Pointf point) {
	return Pointf(
					((point.x - graph->layout_min_x) * factor_x) + border,
					((point.y - graph->layout_min_y) * factor_y) + border
	);
}


// coordinates for potential connection coordinates from/to the objects
void Renderer::GetConnectionPoints(const Node& obj1, const Node& obj2, Vector<Point>& pts) {
	
	// get bounding boxes of target and source
	Rect bb1 = obj1.GetBoundingBox();
	Rect bb2 = obj2.GetBoundingBox();
	int bb1_width = bb1.GetWidth();
	int bb2_width = bb2.GetWidth();
	int bb1_height = bb1.GetHeight();
	int bb2_height = bb2.GetHeight();
	int bb1_x = bb1.left;
	int bb2_x = bb2.left;
	int bb1_y = bb1.top;
	int bb2_y = bb2.top;
	int off1 = 0;
	int off2 = 0;
	
	pts.SetCount(8);
	
	// NORTH 1
	pts[0] = Point(bb1_x + bb1_width / 2, bb1_y - off1);
	
	// SOUTH 1
	pts[1] = Point(bb1_x + bb1_width / 2, bb1_y + bb1_height + off1);
	
	// WEST  1
	pts[2] = Point(bb1_x - off1, bb1_y + bb1_height / 2 );
	
	// EAST  1
	pts[3] = Point(bb1_x + bb1_width + off1, bb1_y + bb1_height / 2 );
	
	// NORTH 2
	pts[4] = Point(bb2_x + bb2_width / 2, bb2_y - off2 );
	
	// SOUTH 2
	pts[5] = Point(bb2_x + bb2_width / 2, bb2_y + bb2_height + off2 );
	
	// WEST  2
	pts[6] = Point(bb2_x - off2, bb2_y + bb2_height / 2 );
	
	// EAST  2
	pts[7] = Point(bb2_x + bb2_width + off2, bb2_y + bb2_height / 2 );
}


void Renderer::DrawNode(Draw& w, Node& node) {
	int width = node.sz.cx;
	int height = node.sz.cy;
	
	Pointf pt = node.point;
	pt.x -= width / 2;
	pt.y -= height / 2;
	
	if (node.shape == Node::SHAPE_ELLIPSE)
		w.DrawEllipse(pt.x, pt.y, width, height, node.fill_clr, 2, node.line_clr);
	else if (node.shape == Node::SHAPE_RECT) {
		w.DrawRect(pt.x - 2, pt.y - 2, width + 4, height + 4, node.line_clr);
		w.DrawRect(pt.x, pt.y, width, height, node.fill_clr);
	}
	else if (node.shape == Node::SHAPE_DIAMOND) {
		diam.SetCount(5);
		diam[0].x = pt.x + width / 2;
		diam[0].y = pt.y;
		diam[1].x = pt.x + width;
		diam[1].y = pt.y + height / 2;
		diam[2].x = pt.x + width / 2;
		diam[2].y = pt.y + height;
		diam[3].x = pt.x;
		diam[3].y = pt.y + height / 2;
		diam[4] = diam[0];
		
		w.DrawPolygon(diam, node.fill_clr, 2, node.line_clr);
	}
	
	const String& lbl = node.label.IsEmpty() ? node.id : node.label;
	
	Font fnt(Arial(12));
	Size txt_sz = GetTextSize(lbl, fnt);
	
	w.DrawText(
		pt.x + (width - txt_sz.cx) / 2,
		pt.y + (height - txt_sz.cy) / 2,
		lbl,
		fnt, Black());
	
	// TODO update / cache shape
	// if (node.shape) {
	//   node.shape.Translate(node.point[0], node.point[1])
	//   return
	// }
	/*if (node.render)
		node.shape = node.render(canvas, node);
	else {
		node.shape = this->canvas.set();
		node.shape
		.push(this->canvas.ellipse(0, 0, 30, 20)
			  .attr({ stroke: color, 'stroke-width': 2, fill: color, 'fill-opacity': 0 }))
		.push(this->canvas.text(0, 30, node.label || node.id))
		.Translate(node.point[0], node.point[1]);
	}

	node.shape.connections = [];
	dragify(node.shape);*/
}

void Renderer::DrawEdge(Draw& w, Edge& edge) {
	Vector<Point> p;
	GetConnectionPoints(*edge.source, *edge.target, p);
	
	// distances between objects and according coordinates connection
	typedef Tuple2<int, int> Comb;
	Vector<Comb> d;
	Vector<int> dis;
	int dx;
	int dy;

	// find out the best connection coordinates by trying all possible ways
	
	// loop the first object's connection coordinates
	for (int i = 0; i < 4; i++) {
		
		// loop the second object's connection coordinates
		for (int j = 4; j < 8; j++) {
			dx = abs(p[i].x - p[j].x);
			dy = abs(p[i].y - p[j].y);

			if ((i == j - 4) || (((i != 3 && j != 6) || p[i].x < p[j].x) &&
								 ((i != 2 && j != 7) || p[i].x > p[j].x) &&
								 ((i != 0 && j != 5) || p[i].y > p[j].y) &&
								 ((i != 1 && j != 4) || p[i].y < p[j].y))
			   ) {
				dis.Add(sqrt((double)(dx * dx + dy * dy)));
				Comb& c = d.Add();
				c.a = i;
				c.b = j;
			}
		}
	}
	
	int min_d = INT_MAX;
	int min_pos = -1;
	for(int i = 0; i < dis.GetCount(); i++) {
		if (dis[i] < min_d) {
			min_d = dis[i];
			min_pos = i;
		}
	}
	
	Comb res;
	if (dis.IsEmpty()) {
		res.a = 0;
		res.b = 4;
	}
	else {
		res = d[min_pos];
	}
	
	// bezier path
	int x1 = p[res.a].x;
	int y1 = p[res.a].y;
	int x4 = p[res.b].x;
	int y4 = p[res.b].y;
	dx = max(abs(x1 - x4) / 2, 10);
	dy = max(abs(y1 - y4) / 2, 10);
	int x2, y2, x3, y3;
	switch (res.a) {
		case 0: x2 = x1; y2 = y1 - dy; break;
		case 1: x2 = x1; y2 = y1 + dy; break;
		case 2: x2 = x1 - dx; y2 = y1; break;
		case 3: x2 = x1 + dx; y2 = y1; break;
		default: Panic("error");
	}
	switch (res.b) {
		case 0:
		case 1:
		case 2:
		case 3:
			x3 = 0; y3 = 0; break;
		
		case 4: x3 = x4; y3 = y1 + dy; break;
		case 5: x3 = x4; y3 = y1 - dy; break;
		case 6: x3 = x4 - dx; y3 = y4; break;
		case 7: x3 = x4 + dx; y3 = y4; break;
		default: Panic("error");
	}
	
	// assemble path and arrow
	#define GET_POINT(n1 , n2 , perc) (n1 + ( (n2 - n1) * perc ))
	
	bezier_path.SetCount(0);
	for (double i = 0 ; i <= 1.01 ; i += 0.05) {
		// The Green Line
		double xa = GET_POINT(x1, x2, i);
		double ya = GET_POINT(y1, y2, i);
		double xb = GET_POINT(x2, x3, i);
		double yb = GET_POINT(y2, y3, i);
		double xc = GET_POINT(x3, x4, i);
		double yc = GET_POINT(y3, y4, i);
		
		double xd = GET_POINT(xa, xb, i);
		double yd = GET_POINT(ya, yb, i);
		double xe = GET_POINT(xb, xc, i);
		double ye = GET_POINT(yb, yc, i);
		
		double xf = GET_POINT(xd, xe, i);
		double yf = GET_POINT(yd, ye, i);
		
		bezier_path.Add(Point(xf,yf));
	}
	
	w.DrawPolyline(bezier_path, edge.line_width, edge.stroke_clr);
	
	
	// arrow
	if (edge.directed) {
		
		// magnitude, length of the last path vector
		double mag = sqrt((double)((y4 - y3) * (y4 - y3) + (x4 - x3) * (x4 - x3)));
		
		// vector normalisation to specified length
		#define norm(x) (double)(-(x) * 10 / mag)
		arrow.SetCount(3);
		arrow[0].x = norm(x4 - x3) + norm(y4 - y3) + x4;
		arrow[0].y = norm(y4 - y3) + norm(x4 - x3) + y4;
		arrow[1].x = x4;
		arrow[1].y = y4;
		arrow[2].x = norm(x4 - x3) - norm(y4 - y3) + x4;
		arrow[2].y = norm(y4 - y3) - norm(x4 - x3) + y4;
		w.DrawPolyline(arrow, edge.line_width, edge.stroke_clr);
	}
	
	// setting label
	if (!edge.label.IsEmpty()) {
		Font fnt(Arial(12));
		Size txt_sz = GetTextSize(edge.label, fnt);
		w.DrawText((x1 + x4 - txt_sz.cx) / 2, (y1 + y4 - txt_sz.cy) / 2, edge.label, fnt, Black());
	}
}

}
