#include <algorithm>
#include <functional>

#include "graph/graphAdjList.h"
#include "graph/graphAdjMatrix.h"

void fillTestGrah(IGraph &graph) {
	static const int numVerts = 10;
	static const int numEdges = 50;

	for (int v = 0; v < numVerts; ++v)
		graph.addVertex();

	for (int e = 0; e < numEdges; ++e) {
		graph.addEdge((e*31 + 19) / 3 % numVerts, (e * 31 + numEdges + 19) / 2 % numVerts);
	}

}

void testVetrices(IGraph &graph1, IGraph &graph2, int v, void (IGraph::*neighbFunc)(int, IGraph::Vertices&)) {
	IGraph::Vertices vertices1, vertices2;
	(graph1.*neighbFunc)(v, vertices1);
	(graph2.*neighbFunc)(v, vertices2);

	std::sort(vertices1.begin(), vertices1.end());
	std::sort(vertices2.begin(), vertices2.end());

	if (vertices1 != vertices2) {
		throw std::logic_error("Neighbours are not equal");
	}
}

void ensureGraphsEqual(IGraph &graph1, IGraph &graph2) {
	if (graph1.getNumVertices() != graph2.getNumVertices())
		throw std::logic_error("Num of vertices are not equal");

	if (graph1.getNumEdges() != graph2.getNumEdges())
		throw std::logic_error("Num of edges are not equal");

	for (int v = 0; v < graph1.getNumVertices(); ++v) {
		testVetrices(graph1, graph2, v, &Graph::getInNeighbors);
		testVetrices(graph1, graph2, v, &Graph::getOutNeighbors);
	}
}


void testGraphImplementation() {
	GraphAdjList graphList;
	GraphAdjMatrix graphMatrix;

	fillTestGrah(graphList);
	fillTestGrah(graphMatrix);
	ensureGraphsEqual(graphList, graphMatrix);
}

void test_graphs() {
	testGraphImplementation();
}
