#include "GraphLib1.h"


class Example : public TopWindow {
	
	TournamentTreeGraph g;
	
public:
	Example() {
		Title("GraphLib tutorial 1");
		Icon(CtrlImg::Diskette());
		Add(g.SizePos());
		Sizeable();
		
		g.SetFillColor(Color(0xff, 0xAA, 0x88));
		
		g.AddEdge( 2, 1);
		g.AddEdge( 3, 1);
		g.AddEdge( 5, 2);
		g.AddEdge( 4, 2);
		g.AddEdge( 7, 3);
		g.AddEdge( 6, 3);
		
		g.SetFillColor(Color(0xAA, 0xff, 0x88)); // affects nodes added after this
		
		g.AddEdge( 8, 4);
		g.AddEdge( 9, 4);
		g.AddEdge(10, 5);
		g.AddEdge(11, 5);
		g.AddEdge(12, 6);
		g.AddEdge(13, 6);
		g.AddEdge(14, 7);
		g.AddEdge(15, 7);
	}
};

GUI_APP_MAIN {
	Example().Run();
}
