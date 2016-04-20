#ifndef HASHTABLE_H
#define HASHTABLE_H



template <typename HashElement>
class HashTable
{
private:
	// internal datastructure

	int nrOfElements;
	int hashTableSize;
	int myHash(const HashElement& elem) const 
	{ 
		static Hash<HashElement> hashFunc; 
		return hashFunc(elem) % hashTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}
public:
	HashTable(int hashTableSize = 101);
	HashTable(const HashTable& aTable) = delete;
	virtual ~HashTable();
	HashTable& operator=(const HashTable& aTable) = delete;
	int contains(const HashElement& elem) const; // returns index or -1
	bool insert(const HashElement& elem);
	bool remove(const HashElement& elem);
	const HashElement& get(int index) const; 
	void makeEmpty();
	double loadFactor() const;
	int getNrOfElements() const;
};

#endif