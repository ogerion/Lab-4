#pragma once
#include "IDictionary.h"
#include "UnorderedMap.h"

template <class KType, class VType>
class UnorderedMapDictionary : public IDictionary<KType, VType>
{
private:
	UnorderedMap<KType, VType> data;
public:
	UnorderedMapDictionary() 
	{
		this->data =UnorderedMap<KType,VType>();
		this->size = 0;
	};

	VType Get(KType key) override;

	int GetCapacity() override;

	bool ContainsKey(KType key) override;

	void Add(KType key, VType element) override;

	void erase(KType key) override;
};
	
template<class KType, class VType>
VType UnorderedMapDictionary<KType,VType>::Get(KType key)
{
	if (data.find(key))
	{
		VType el;
		data.find(key, el);
		return el;
	}
	throw "There're no elements with this key!";
}

template<class KType, class VType>
int UnorderedMapDictionary<KType, VType>::GetCapacity()
{
	return data.capacity();
}

template<class KType, class VType>
bool UnorderedMapDictionary<KType, VType>::ContainsKey(KType key)
{
	return data.find(key);
}

template<class KType, class VType>
void UnorderedMapDictionary<KType, VType>::Add(KType key, VType element)
{
	data.insert(key, element);
	this->size += 1;
}

template<class KType, class VType>
void UnorderedMapDictionary<KType, VType>::erase(KType key)
{
	data.erase(key);
	this->size -= 1;
}
