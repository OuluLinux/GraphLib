#include "GraphLib4.h"

class Example : public TopWindow {
	
	SpringGraph g;
	
public:
	Example() {
		Title("GraphLib tutorial 4 :: Try clicking nodes");
		Icon(CtrlImg::Diskette());
		Add(g.SizePos());
		Sizeable();
		
		// Showcase of the Dijkstra search algorithm finding shortest paths
		// from one point to every node
		
		// creating nodes and passing the new renderer function to overwrite the default one
		g.AddNode("New York");
		g.AddNode("Berlin");
		g.AddNode("Tel Aviv");
		g.AddNode("Tokyo");
		g.AddNode("Roma");
		g.AddNode("Madrid");

		// modify the AddEdge function to attach random weights
		//g.AddEdge2 = g.AddEdge;
		//g.AddEdge = function(from, to, style) { !style && (style={}); style.weight = Math.floor(Math.random()*10) + 1; g.AddEdge2(from, to, style); };
		
		// connections
		g.AddEdge("Tokyo", "Tel Aviv")		.SetWeight(1+Random(10)); //, {weight:9, directed: true, stroke : "#bfa"} // also supports directed graphs, but currently doesn't look that nice
		g.AddEdge("Tokyo", "New York")		.SetWeight(1+Random(10));
		g.AddEdge("Tokyo", "Berlin")		.SetWeight(1+Random(10));
		g.AddEdge("Tel Aviv", "Berlin")		.SetWeight(1+Random(10));
		g.AddEdge("Tel Aviv", "New York")	.SetWeight(1+Random(10));
		g.AddEdge("Tel Aviv", "Roma")		.SetWeight(1+Random(10));
		g.AddEdge("Roma", "New York")		.SetWeight(1+Random(10));
		g.AddEdge("Berlin", "New York")		.SetWeight(1+Random(10));
		g.AddEdge("Madrid", "New York")		.SetWeight(1+Random(10));
		g.AddEdge("Madrid", "Roma")			.SetWeight(1+Random(10));
		g.AddEdge("Madrid", "Tokyo")		.SetWeight(1+Random(10));
		
		g.RouteWeights(); // enable dijkstra update by clicking nodes
		g.Dijkstra(g.AddNode("Berlin")); // route initial dijkstra
		
	}
};

GUI_APP_MAIN {
	Example().Run();
}


	#if 0
GUI_APP_MAIN {
	
	var redraw;
	var height = 300;
	var width = 400;

	window.onload = function() {

		
		
		/*  */

		/* We need to write a new node renderer function to display the computed
		   distance.
		   (the Raphael graph drawing implementation of Dracula can draw this shape,
		   please consult the RaphaelJS reference for details http://raphaeljs.com/) */
		var render = function(r, n) {
		        /* the Raphael set is obligatory, containing all you want to display */
		        var set = r.set().push(
		            /* custom objects go here */
		            r.rect(n.point[0]-30, n.point[1]-13, 60, 44).attr({"fill": "#feb", r : "12px", "stroke-width" : n.distance == 0 ? "3px" : "1px" })).push(
		            r.text(n.point[0], n.point[1] + 10, (n.label || n.id) + "\n(" + (n.distance == undefined ? "Infinity" : n.distance) + ")"));
		        return set;
		    };
		
		var g = new Graph();
		

		/* random edge weights (our undirected graph is modelled as a bidirectional graph) */
	/*    for(e in g.edges)
		    if(g.edges[e].backedge != undefined) {
		        g.edges[e].weight = Math.floor(Math.random()*10) + 1;
		        g.edges[e].backedge.weight = g.edges[e].weight;
		    }
	*/
		/* layout the graph using the Spring layout implementation */
		var layouter = new Graph.Layout.Spring(g);
		layouter.layout();
		
		/* draw the graph using the RaphaelJS draw implementation */
		var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);


		/
		
		renderer.draw();

		redraw = function() {
		    layouter.layout();
		    renderer.draw();
		};
	};

}
	#endif
	
