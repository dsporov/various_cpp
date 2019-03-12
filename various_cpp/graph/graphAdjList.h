#pragma once

#include "graph.h"

#include <unordered_map>

class GraphAdjList : public Graph {

private:
	std::unordered_map<int, Vertices> adjListsMap_;

	virtual void addVertexImpl() override;
	virtual void addEdgeImpl(int vertFrom, int vertTo) override;

	virtual void getOutNeighbors(int vert, Vertices &vertices) override;
	virtual void getInNeighbors(int vert, Vertices &vertices) override;
};
