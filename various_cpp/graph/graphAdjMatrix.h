#pragma once

#include "graph.h"

class GraphAdjMatrix : public Graph {
private:
	std::vector<std::vector<int>> adjMatrix_;

	virtual void addVertexImpl() override;
	virtual void addEdgeImpl(int vertFrom, int vertTo) override;

	virtual void getOutNeighbors(int vert, Vertices &vertices) override;
	virtual void getInNeighbors(int vert, Vertices &vertices) override;

	void incSize();
};

