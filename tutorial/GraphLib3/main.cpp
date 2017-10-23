#include "GraphLib3.h"

class Example : public TopWindow {
	
	SpringGraph g;
	
public:
	Example() {
		Title("GraphLib tutorial 3");
		Icon(CtrlImg::Diskette());
		Add(g.SizePos());
		Sizeable();
		
		g.SetFillColor(Color(0xff, 0xAA, 0x88));
		
		// add a simple node
		g.AddNode("strawberry");
		g.AddNode("cherry");
		
		// add a node with a customized label
		g.AddNode("1").SetLabel("Tomato").SetShapeDiamond();
		
		// add a node with a customized shape
		g.AddNode("id35").SetLabel("meat and greed").SetShapeRectangle();
		
		g.AddEdge("kiwi", "penguin").SetDirected().SetLabel("Label");
		
		// connect nodes with edges
		g.AddEdge("strawberry", "cherry").SetDirected();
		g.AddEdge("cherry", "apple");
		g.AddEdge("cherry", "apple");
		g.AddEdge("1", "id35");
		g.AddEdge("penguin", "id35");
		g.AddEdge("penguin", "apple");
		g.AddEdge("kiwi", "id35");
		
		// a directed connection, using an arrow
		g.AddEdge("1", "cherry").SetDirected();
		
		// customize the colors of that edge
		g.AddNode("apple").SetFill(Color(0x55,0x66,0xff));
		g.AddEdge("id35", "apple")
			.SetStroke(2, Color(0xbb,0xff,0xaa))
			.SetLabel("Meat-to-apple");
		
		
		// add an unknown node implicitly by adding an edge
		g.AddEdge("strawberry", "apple");
		
	}
};

GUI_APP_MAIN {
	Example().Run();
}
