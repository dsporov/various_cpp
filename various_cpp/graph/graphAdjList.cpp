#include "graphAdjList.h"

void GraphAdjList::addVertexImpl() {
	int v = getNumVertices();
	adjListsMap_[v] = Vertices();
}

void GraphAdjList::addEdgeImpl(int vertFrom, int vertTo) {
	adjListsMap_[vertFrom].push_back(vertTo);
}

Graph::Vertices GraphAdjList::getOutNeighbors(int vert) {
	return adjListsMap_[vert];
}

Graph::Vertices GraphAdjList::getInNeighbors(int vert) {
	Vertices inNeighbors;

	for (auto const& p : adjListsMap_) {
		int vertIter = p.first;
		Vertices const& outVertIter = p.second;
		for (int v : outVertIter) {
			if (v == vert) {
				inNeighbors.push_back(vertIter);
				break;
			}
		}
	}

	return inNeighbors;
}
