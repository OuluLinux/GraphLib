#include "GraphLib2.h"

class Example : public TopWindow {
	
	OrderedTreeGraph g;
	
public:
	Example() {
		Title("GraphLib tutorial 2");
		Icon(CtrlImg::Diskette());
		Add(g.SizePos());
		Sizeable();
		
		g.SetFillColor(Color(0xff, 0xAA, 0x88));
		
		// Show UCLA CS class dependencies (not complete)
		g.AddEdge("CS 31","CS 32");
		g.AddEdge("CS 32","CS 33");
		g.AddEdge("CS 33","CS 35L");
		g.AddNode("CS M51A");
		g.AddEdge("CS 32", "CS 111");
		g.AddEdge("CS 33", "CS 111");
		g.AddEdge("CS 35L", "CS 111");
		g.AddEdge("CS 32", "CS 118");
		g.AddEdge("CS 33", "CS 118");
		g.AddEdge("CS 35L", "CS 118");
		g.AddEdge("CS 111", "CS 118");
		g.AddEdge("CS 32", "CS 131");
		g.AddEdge("CS 33", "CS 131");
		g.AddEdge("CS 35L", "CS 131");
	}
};

GUI_APP_MAIN {
	Example().Run();
}
