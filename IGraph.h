#pragma once
#include "sequence/LinkedListSequence.h"
template<class T>
class IGraph
{
protected:
	size_t size;
	std::vector<T> vertexList;
public:
	virtual void addVertex(T) = 0;

	virtual void addEdge(T,T,float) = 0;

	virtual float getEdgeWeight(T, T) = 0;

	virtual void removeVertex(T) = 0;

	virtual void removeEdge(T, T) = 0;

	virtual std::vector<std::pair<T,float>> getNeigbours(T) = 0;

	virtual bool containsEdge(T,T) = 0;

	virtual bool containsVertex(T) = 0;
};