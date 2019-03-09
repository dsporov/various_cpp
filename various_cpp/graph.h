#pragma once

#include "various_cpp.h"

interface IGraph {
public:
	virtual void addVertex() = 0;
	virtual void addEdge() = 0;
};

class Graph : public IGraph {

};
