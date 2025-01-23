#pragma once
#include "sequence/LinkedListSequence.h"
#include <functional>
template <class KType,class VType>
class UnorderedMap
{
private:
	template<class KType, class VType>
	class HashNode
	{
	public:
		KType key;
		VType value;
		HashNode(KType k, VType v) : key(k), value(v) {}
		HashNode(HashNode<KType,VType> &n) : key(n.key), value(n.value){}
		HashNode() : key(), value() {}
	};

	LinkedListSequence<HashNode<KType,VType>> ** table;
	size_t current_size;
	float max_load_factor;
	int tableLenght;
	size_t hash(const KType& key) const
	{
		return std::hash<KType>()(key) % tableLenght;
	}
	void rehash() {
		size_t new_size = tableLenght * 2;
		LinkedListSequence<HashNode<KType,VType>> ** new_table = new LinkedListSequence<HashNode<KType, VType>> * [new_size];
		for (int i = 0; i < new_size; i++)
		{
			new_table[i] = new LinkedListSequence<HashNode<KType,VType>>();
		}
		for (int i = 0; i < current_size; i++)
		{
			for (int j = 0; j < table[i]->GetLenght(); j++)
			{
				size_t new_index = hash(table[i]->Get(j).key);
				HashNode<KType, VType> temp(
					table[i]->Get(j).key,
					table[i]->Get(j).value

				);
				new_table[new_index]->Append(temp);
			}
		}
		for (int i = 0; i < current_size; i++)
		{
			delete table[i];
		}
		delete [] table;
		table = std::move(new_table);
		tableLenght = new_size;
	}

public:
	UnorderedMap(size_t initial_size=10000, float load_factor = 0.9) {
		current_size = 0;
		max_load_factor = load_factor;
		table = new LinkedListSequence<HashNode<KType, VType>> * [initial_size];
		for (int i = 0; i < initial_size; i++)
		{
			table[i] = new LinkedListSequence<HashNode<KType, VType>>();
		}
		tableLenght = initial_size;
	}


    void insert(KType key,VType value) {
        if ((float)current_size / tableLenght >= max_load_factor) {
            rehash();
        }

        size_t index = hash(key);
		for (int j = 0; j < table[index]->GetLenght(); j++)
		{
			if (table[index]->Get(j).key == key)
			{
				table[index]->Get(j).value = value;
				return;
			}
		}
		HashNode<KType, VType> temp(key, value);
        table[index]->Append(temp);
        ++current_size;
    }

    bool find(const KType& key, VType& value) const {
		size_t index = hash(key);
		for (int j = 0; j < table[index]->GetLenght(); j++)
		{
			if (table[index]->Get(j).key == key)
			{
				value = table[index]->Get(j).value;
				return true;
			}
		}
        return false;
    }

	bool find(const KType& key) const {
		VType temp;
		return this->find(key, temp);
	}

    void erase(const KType& key) {
        size_t index = hash(key);
		for (int j = 0; j < table[index]->GetLenght(); j++)
		{
			if (table[index]->Get(j).key == key)
			{
				LinkedListSequence<HashNode<KType, VType>> * new_bucket = new LinkedListSequence<HashNode<KType,VType>>();
				for (int k = 0; k < table[index]->GetLenght(); k++)
				{
					if (k != j)
					{
						new_bucket->Append(*(new HashNode<KType, VType>(
							table[index]->Get(j).key,
							table[index]->Get(j).value
						)));
					}
					
				}
				current_size--;
				table[index] = std::move(new_bucket);
				return;
			}
		}
		return;
    }

    size_t size() const {
        return current_size;
    }

    bool empty() const {
        return current_size == 0;
    }

	int capacity()
	{
		return ((float)current_size / tableLenght - current_size);
	}
};

