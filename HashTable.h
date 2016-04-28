#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "EngWord.h"

template <typename HashEngWord>
class HashTable
{
private:
	// internal datastructure

	int nrOfEngWords;
	int hashTableSize;
	int myHash(const HashEngWord& EngWord) const 
	{ 
		static Hash<HashEngWord> hashFunc; 
		return hashFunc(EngWord) % hashTableSize; // hashFunc(EngWord) is a call of the defined operator() for HashEngWord
	}
public:
	HashTable(int hashTableSize = 101);
	HashTable(const HashTable& aTable) = delete;
	virtual ~HashTable();
	HashTable& operator=(const HashTable& aTable) = delete;
	int contains(const HashEngWord& EngWord) const; // returns index or -1
	bool insert(const HashEngWord& EngWord);
	bool remove(const HashEngWord& EngWord);
	const HashEngWord& get(int index) const; 
	void makeEmpty();
	double loadFactor() const;
	int getnrOfEngWords() const;
};

HashTable::HashTable(int hashTableSize)
{

}

HashTable::~HashTable() {

}
template <typename HashEngWord>
int HashTable::contains(const HashEngWord &EngWord) const
{
	return 0;
}
template <typename HashEngWord>
bool HashTable::insert(const HashEngWord &EngWord)
{
	return false;
}
template <typename HashEngWord>
bool HashTable::remove(const HashEngWord &EngWord)
{
	return false;
}
template <typename HashEngWord>
const HashEngWord &HashTable::get(int index) const
{
	return <#initializer#>;
}

void HashTable::makeEmpty()
{

}

double HashTable::loadFactor() const
{
	return 0;
}

int HashTable::getnrOfEngWords() const
{
	return 0;
}
#endif