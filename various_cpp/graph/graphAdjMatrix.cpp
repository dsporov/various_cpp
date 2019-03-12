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

void GraphAdjMatrix::getOutNeighbors(int vert, Vertices &vertices) {
	vertices.clear();
	
	for (int i = 0; i < getNumVertices(); i++) {
		for (int j = 0; j < adjMatrix_[vert][i]; j++) {
			vertices.push_back(i);
		}
	}
}

void GraphAdjMatrix::getInNeighbors(int vert, Vertices &vertices) {
	vertices.clear();

	for (int i = 0; i < getNumVertices(); i++) {
		for (int j = 0; j < adjMatrix_[i][vert]; j++) {
			vertices.push_back(i);
		}
	}
}
