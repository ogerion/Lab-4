#pragma once
#include "./UnorderedMapGraph.h"
#include <cassert>
#include <vector>
#include "./UnorderedMapDictionary.h"
void testGraph()
{
	UnorderedMapGraph<int> graph = UnorderedMapGraph<int>();
	graph.addVertex(1);
	graph.addVertex(2);
	graph.addVertex(3);
	graph.addVertex(4);
	graph.addEdge(1, 2, 1);
	graph.addEdge(2, 3, 1);
	graph.addEdge(2, 4, 1);
	graph.addEdge(4, 3, 1);
	std::vector<int> sorted(graph.topologicalSort());
	assert(sorted[0] == 1);
	assert(sorted[1] == 2);
	assert(sorted[2] == 4);
	assert(sorted[3] == 3);

	UnorderedMapDictionary<int, int> color(graph.paintGraph());
	assert(color.Get(1) == 0);
	assert(color.Get(2) == 1);
	assert(color.Get(3) == 2);
	assert(color.Get(4) == 0);
}