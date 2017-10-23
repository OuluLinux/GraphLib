#ifndef _GraphLib_Snap_h_
#define _GraphLib_Snap_h_

import SnapSvg from 'snapsvg'
import Renderer from './renderer'

class RaphaelRenderer : public Renderer {

public:
	RaphaelRenderer(element, graph, width, height) :
		Renderer(element, graph, width, height) {
		//this->canvas = new SnapSvg(this->width, this->height, element);
		/*  this->lineStyle = {
			stroke: '#abcdef'
				,
			'stroke-width': '2px'
				,
		    };*/
	}

	DrawNode(node) {
		// TODO update / cache shape
		//node.shape = this->canvas.circle(node.point[0], node.point[1], 10);
	}

	DrawEdge(edge) {
		/*const p1 = edge.source.point;
		const p2 = edge.target.point;
		edge.shape = this->canvas.line(p1[0], p1[1], p2[0], p2[1]);
		edge.shape.attr(this->lineStyle);*/
	}

}

#endif
