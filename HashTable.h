// not tested
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "EngWord.h"

using namespace std;
template <typename HashElement>
class HashTable
{
private:
    enum Marker
    {
      OCCUPIED =0, DELETED, UNTOUCHED
    };
	// internal datastructure    insert array.
    HashElement* array;
    Marker *MarkerArray;
	int nrOfElements;
	int hashTableSize;
	int myHash(const HashElement &elem) const
	{ 
		static Hash<HashElement> hashFunc;
		return hashFunc(elem) % hashTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}
public:
	HashTable(int hashTableSize = 101);
	HashTable(const HashTable& aTable) = delete;
	virtual ~HashTable();
	HashTable& operator=(const HashTable& aTable) = delete;
	int contains(const HashElement & EngWord) const; // returns index or -1
	bool insert(const HashElement & EngWord);//anrop my hash sen leta efter existerande om ny lägg till.
	bool remove(const HashElement & EngWord);//leta sen markera
	const HashElement & get(int index) const;
	void makeEmpty();
	double loadFactor() const;
	int getnrOfElements() const;
};
template <typename HashElement>
HashTable<HashElement>::HashTable(int hashTableSize)
{
    this->hashTableSize = hashTableSize;
    Marker guard;
    guard = Marker::UNTOUCHED;
    this->array = new HashElement[this->hashTableSize];
    this->MarkerArray = new Marker[this->hashTableSize];
    for (int i = 0; i < this->hashTableSize ; ++i)
    {
        this->MarkerArray[i] = guard ;
    }
}
template <typename HashElement>
HashTable<HashElement>::~HashTable()
{
    delete this->array;
    delete this->MarkerArray;
}
template <typename HashElement>
int HashTable<HashElement>::contains(const HashElement &EngWord) const
{
    int atIndex = -1;
    for (int i = 0; i < this->nrOfElements ; ++i)
    {
        if((static_cast<EngWord>(this->array[i])) == (static_cast<EngWord>(EngWord)))
        {
            atIndex = i;
        }
    }
	return atIndex;
}
template <typename HashElement>
bool HashTable<HashElement>::insert(const HashElement &EngWord)
{
    bool flag = false;
    int insertAtIndex;
	insertAtIndex = myHash(EngWord);
    if(this->getnrOfElements() == 0)
    {
        this->array[insertAtIndex] = EngWord;
        this->MarkerArray[insertAtIndex] = Marker::OCCUPIED;
        flag = true;
        this->nrOfElements++;
        return flag;
    }
    else
    {
        if (this->MarkerArray[insertAtIndex] == Marker::OCCUPIED)
        {
            if ((static_cast<EngWord>(this->array[insertAtIndex]) != (static_cast<EngWord>(EngWord))))
            {
                //linear probing. Meaning search for empty space to place obj
                for (int i = insertAtIndex; i < this->getnrOfElements(); ++i)
                {
                    if(this->MarkerArray[i] == Marker::UNTOUCHED)
                    {
                        flag = true;
                        this->array[insertAtIndex] = EngWord;
                        this->MarkerArray[i] = Marker::OCCUPIED;
                        this->nrOfElements++;
                        return flag;
                    }
                }
            }
            //else don't insert copy!
        }
    }
	return flag;
}
template <typename HashElement>
bool HashTable<HashElement>::remove(const HashElement &EngWord)
{
    this->nrOfElements--;
	return false;
}
template <typename HashElement>
const HashElement &HashTable<HashElement>::get(int index) const
{
    if( index < this->nrOfElements || index > -1)
    {
        if (this->MarkerArray[index] == Marker::OCCUPIED)
        {
            return this->array[index];
        }
        //else throw nothing to fetch
    }
    //else throw out of bounds
}
template <typename HashElement>
void HashTable<HashElement>::makeEmpty()
{
    delete this->array;
    delete this->MarkerArray;
    this->array = new HashElement[this->hashTableSize];
    this->MarkerArray = new Marker[this->hashTableSize];
}
template <typename HashElement>
double HashTable<HashElement>::loadFactor() const
{
    double loadFactor = (this->nrOfElements / this->hashTableSize);
	return loadFactor;
}
template <typename HashElement>
int HashTable<HashElement>::getnrOfElements() const
{
	return this->nrOfElements;
}
#endif