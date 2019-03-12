#pragma once

#include <vector>

#include "../various_cpp.h"

interface IGraph {
	using Vertices = std::vector<int>;

	virtual ~IGraph() = default;

	virtual int getNumVertices() const = 0;
	virtual int getNumEdges() const = 0;

	virtual int addVertex() = 0;
	virtual void addEdge(int vertFrom, int vertTo) = 0;

	virtual void getOutNeighbors(int vert, Vertices &vertices) = 0;
	virtual void getInNeighbors(int vert, Vertices &vertices) = 0;

	// todo: do we need get vertex degree pure vurtuala method?
};

class Graph : public IGraph {
public:
	Graph() : numEdges_(0), numVertices_(0) {};

	virtual int getNumVertices() const { return numVertices_; }
	virtual int getNumEdges() const { return numEdges_; };

	virtual int addVertex() {
		addVertexImpl();
		++numVertices_;
		return numVertices_;
	}

	virtual void addEdge(int vertFrom, int vertTo) {
		if (vertFrom >= numVertices_ || vertTo >= numVertices_) {
			throw std::runtime_error("Vertex index is out of bouds");
		}

		++numEdges_;
		addEdgeImpl(vertFrom, vertTo);
	}

private:
	virtual void addVertexImpl() = 0;
	virtual void addEdgeImpl(int vertFrom, int vertTo) = 0;

	int numEdges_, numVertices_;
};
