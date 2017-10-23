#ifndef _GraphLib_Dijkstra_h_
#define _GraphLib_Dijkstra_h_

#include "BinaryHeapMap.h"

//    Path-finding algorithm Dijkstra
//
//    - worst-case running time is O((|E| + |V|) · log |V| ) thus better than
//     Bellman-Ford for sparse graphs (with less edges), but cannot handle
//     negative edge weights

namespace GraphLib {

void Dijkstra(Graph& g, Node& source);

}

#endif
