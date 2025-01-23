#pragma once
template <class KType, class VType>
class IDictionary
{
protected:
	size_t size;
public:
	int GetCount()
	{
		return size;
	}

	virtual VType Get(KType key) = 0;
	
	virtual int GetCapacity() = 0;

	virtual bool ContainsKey(KType key) = 0;
	
	virtual void Add(KType key, VType element) = 0;

	virtual void erase(KType key) = 0;
};