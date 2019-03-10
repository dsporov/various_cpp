#pragma once

#include "graph.h"

class GraphAdjMatrix : public Graph {
private:
	std::vector<std::vector<int>> adjMatrix_;

	virtual void addVertexImpl() override;
	virtual void addEdgeImpl(int vertFrom, int vertTo) override;

	virtual Vertices getOutNeighbors(int vert) override;
	virtual Vertices getInNeighbors(int vert) override;

	void incSize();
};

