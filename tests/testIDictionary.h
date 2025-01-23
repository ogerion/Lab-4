#pragma once
#include "./UnorderedMapDictionary.h"
#include "cassert"
void testIDictionary()
{
	UnorderedMapDictionary<int, int> mydict;
	mydict.Add(1, 2);
	mydict.Add(2, 3);
	mydict.Add(4, 5);
	mydict.Add(5, 6);

	int r = mydict.Get(4);

	assert(r == 5);
	assert(mydict.ContainsKey(1));
	mydict.erase(2);
	assert(mydict.GetCount() == 3);
}
