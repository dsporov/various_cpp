#include "graphAdjMatrix.h"

void GraphAdjMatrix::incSize() {
	size_t newSize = adjMatrix_.empty() ? 16 : adjMatrix_.size() * 2;
	adjMatrix_.resize(newSize);
	for (Vertices &vertices : adjMatrix_) {
		vertices.resize(newSize);
	}
}

void GraphAdjMatrix::addVertexImpl() {
	if (getNumVertices() >= adjMatrix_.size())
		incSize();
}

void GraphAdjMatrix::addEdgeImpl(int vertFrom, int vertTo) {
	adjMatrix_[vertFrom][vertTo]++;
}

Graph::Vertices GraphAdjMatrix::getOutNeighbors(int vert) {
	Vertices outNeighbors;
	
	for (int i = 0; i < getNumVertices(); i++) {
		for (int j = 0; j < adjMatrix_[vert][i]; j++) {
			outNeighbors.push_back(i);
		}
	}

	return outNeighbors;
}

Graph::Vertices GraphAdjMatrix::getInNeighbors(int vert) {
	Vertices inNeighbors;

	for (int i = 0; i < getNumVertices(); i++) {
		for (int j = 0; j < adjMatrix_[i][vert]; j++) {
			inNeighbors.push_back(i);
		}
	}

	return inNeighbors;
}
