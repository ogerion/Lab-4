#pragma once
#include "IGraph.h"
#include "UnorderedMapDictionary.h"
#include <iostream>
#include <queue>
#include <unordered_set>

template<class T>
class UnorderedMapGraph : public IGraph<T>
{
protected:
	UnorderedMapDictionary<T, std::vector<std::pair<T, float>>> adjacencyList;
public:
	UnorderedMapGraph() : adjacencyList()
	{
		this->size = 0;
		this->vertexList = std::vector<T>();
	}
	
	void addVertex(T vertex) override;

	void addEdge(T vertex1, T vertex2, float weight) override;

	float getEdgeWeight(T vertex1, T vertex2) override;
	
	void removeVertex(T vertex) override;
	
	void removeEdge(T vertex1, T vertex2) override;

	std::vector<std::pair<T, float>> getNeigbours(T vertex) override;

	bool containsEdge(T, T) override;

	bool containsVertex(T) override;

	std::vector<T> topologicalSort();

	UnorderedMapDictionary<T, int> paintGraph();
};

template <class T>
void UnorderedMapGraph<T>::addVertex(T vertex)
{
	if (!adjacencyList.ContainsKey(vertex))
	{
		adjacencyList.Add(vertex, std::vector<std::pair<T, float>>());
		this->vertexList.emplace_back(vertex);
		this->size += 1;
	}
}

template <class T>
void UnorderedMapGraph<T>::addEdge(T vertex1, T vertex2, float weight)
{
	if ((!adjacencyList.ContainsKey(vertex1) ||
		!adjacencyList.ContainsKey(vertex2)))
	{
		throw "There're no such vertex in graph";
	}
	std::vector<std::pair<T, float>> temp1(adjacencyList.Get(vertex1));
	for (int i = 0; i < temp1.size(); i++)
	{
		if (temp1[i].first == vertex2)
		{
			temp1[i].second = weight;
			adjacencyList.erase(vertex1);
			adjacencyList.Add(vertex1,temp1);
			return;
		}
	}
	temp1.emplace_back(std::pair<T, float>(vertex2, weight));
	adjacencyList.erase(vertex1);
	adjacencyList.Add(vertex1,temp1);
}

template <class T>
float UnorderedMapGraph<T>::getEdgeWeight(T vertex1, T vertex2)
{
	if (!adjacencyList.ContainsKey(vertex1) ||
		!adjacencyList.ContainsKey(vertex2))
	{
		throw "This graph doesnt include one/two of these elements";
	}
	std::vector<std::pair<T, float>> temp(adjacencyList.Get(vertex1));
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i].first == vertex2)
		{
			return temp[i].second;
		}
	}
	throw "There're no edge between these vertexes";
}

template <class T>
void UnorderedMapGraph<T>::removeVertex(T vertex)
{
	if (!adjacencyList.ContainsKey(vertex))
	{
		throw "There're no such vertex in graph";
	}

	std::vector<std::pair<T, float>> temp1(adjacencyList.Get(vertex));

	for (int i = 0; i < temp1.size(); i++)
	{
		std::vector<std::pair<T, float>> temp2(adjacencyList.Get(temp1[i].first));
		for (int j = 0; j < temp2.size(); j++)
		{
			if (temp2[j].first == vertex)
			{
				temp2.erase(temp2.begin() +j);
				adjacencyList.erase(temp1[i].first);
				adjacencyList.Add(temp1[i].first, temp2);
				break;
			}
		}
	}
	adjacencyList.erase(vertex);
	this->size -= 1;
}

template <class T>
void UnorderedMapGraph<T>::removeEdge(T vertex1, T vertex2)
{
	if (!adjacencyList.ContainsKey(vertex1) ||
		!adjacencyList.ContainsKey(vertex2))
	{
		throw "There're no such vertex in graph";
	}

	std::vector<std::pair<T, float>> temp1(adjacencyList.Get(vertex1));

	for (int i = 0; i < temp1.size(); i++)
	{
		if (temp1[i].first == vertex2)
		{
			temp1.erase(temp1.begin() +i);
			adjacencyList.erase(vertex1);
			adjacencyList.Add(vertex1, temp1);
			break;
		}
	}

}

template<class T>
std::vector<std::pair<T, float>> UnorderedMapGraph<T>::getNeigbours(T vertex)
{
	if (!adjacencyList.ContainsKey(vertex))
	{
		throw "There're no such vertex in graph";
	}
	return std::vector<std::pair<T, float>>(adjacencyList.Get(vertex));
}

template<class T>
bool UnorderedMapGraph<T>::containsEdge(T vertex1, T vertex2)
{
	std::vector<std::pair<T, float>> temp(adjacencyList.Get(vertex1));
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i].first == vertex2)
		{
			return true;
		}
	}
	return false;
}

template<class T>
bool UnorderedMapGraph<T>::containsVertex(T vertex)
{
	return adjacencyList.ContainsKey(vertex);
}

template<class T>
std::vector<T> UnorderedMapGraph<T>::topologicalSort()
{
	std::vector<T> degree = std::vector<T>();
	for (int i = 0; i < this->size; i++)
	{
		int r = 0;
		for (int j = 0; j < this->size; j++)
		{
			if (containsEdge(this->vertexList[i], this->vertexList[j]))
			{
				r++;
			}
		}
		degree.emplace_back(r);
	}

	std::queue<T> q;
	for (int i = 0; i < this->size; i++)
	{
		if (degree[i] == 0)
		{
			q.push(this->vertexList[i]);
		}
	}
	std::vector<T> result;

	while (!q.empty())
	{
		T u = q.front();
		q.pop();
		result.insert(result.begin(), u);

		for (int i = 0; i < this->size; i++)
		{
			if (containsEdge(this->vertexList[i], u))
			{
				degree[i]--;
				if (degree[i] == 0)
				{
					q.push(this->vertexList[i]);
				}
			}
		}
	}
	
	if (result.size() != this->size)
	{
		throw "There are cycles in graph";
	}
	return result;
}

template<class T>
UnorderedMapDictionary<T, int> UnorderedMapGraph<T>::paintGraph()
{
	UnorderedMapDictionary<T, int> result = UnorderedMapDictionary<T, int>();
	std::vector<T> sorted(topologicalSort());
	for (int i = 0; i < this->vertexList.size(); i++)
	{
		result.Add(this->vertexList[i], -1);
	}
	for (int i = 0; i < sorted.size(); i++)
	{
		std::unordered_set<T> neigbourColor = std::unordered_set<T>();

		for (int j = 0; j < this->vertexList.size(); j++)
		{
			if (containsEdge(this->vertexList[j], sorted[i]) &&
				result.Get(this->vertexList[j]) != -1)
			{
				neigbourColor.insert(result.Get(this->vertexList[j]));
			}
		}

		int c = 0;

		while (neigbourColor.count(c))
		{
			c++;
		}

		result.erase(sorted[i]);
		result.Add(sorted[i], c);

	}
	return result;
}
