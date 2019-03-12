#include "graphAdjList.h"

void GraphAdjList::addVertexImpl() {
	int v = getNumVertices();
	adjListsMap_[v] = Vertices();
}

void GraphAdjList::addEdgeImpl(int vertFrom, int vertTo) {
	adjListsMap_[vertFrom].push_back(vertTo);
}

void GraphAdjList::getOutNeighbors(int vert, Vertices &vertices) {
	vertices = adjListsMap_[vert];
}

void GraphAdjList::getInNeighbors(int vert, Vertices &vertices) {
	vertices.clear();

	for (auto const& p : adjListsMap_) {
		int vertIter = p.first;
		Vertices const& outVertIter = p.second;
		for (int v : outVertIter) {
			if (v == vert) {
				vertices.push_back(vertIter);
			}
		}
	}
}
