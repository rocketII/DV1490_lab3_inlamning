/*
 *
Övrigt i hashtabellen:
done    Fix
        codes    details
--------------------------------------------------------------------
1        0x0     Destruktorn ska ha [] efter delete

0        0x1     Contains är inte ok eftersomden utför linjärsökning från position 0 och framåt, hashtabeller ska ha låg kostnad för alla operationer (nära konstant tid), ingen typomvandling krävs efersom == och != är definierad för klasstypen EngWord, däremot ska du använda elem i parameterlistan för att inte få konflikter vid instantieringen när HashElement ersätts av EngWord

0        0x2     I insert är det inte korrekt att vid sonderingen/probningen använda antalet element som gräns, du behöver inom en och samma iteration undersöka om den plats om undersöks är oanvänd eller borttagen eftersom det i dessa båda fall är dags att placera in det nya elementet

1        0x3     I makeEmpty behövs ingen avallokeraing av arrayerna för att därefter nyallokeras, sätt status för alla till oanvänd och glöm inte att sätta antalet element till 0
 */
// Not created but edited by Roderik Bauhn.
// not tested
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>


using namespace std;
enum Marker
{
    OCCUPIED =0, DELETED, UNTOUCHED
};
template <typename HashElement>
class HashTable
{
private:

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
	int contains(const HashElement & elem) const; // returns index or -1
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
    delete[] this->array;
    delete[] this->MarkerArray;
}
template <typename HashElement>
//fix code:  0x1
// Contains är inte ok eftersomden utför linjärsökning från position 0 och framåt,
// hashtabeller ska ha låg kostnad för alla operationer (nära konstant tid),
// ingen typomvandling krävs efersom == och != är definierad för klasstypen EngWord,
// däremot ska du använda elem i parameterlistan för att inte få konflikter
// vid instantieringen när HashElement ersätts av EngWord

int HashTable<HashElement>::contains(const HashElement &elem) const
{
    int atIndex = -1;
    int i =-2;
    bool flag=true;
    i = this->myHash(elem);
    do
    {

        if((this->MarkerArray[i] == Marker::OCCUPIED) && this->array[i] == elem)
        {
            atIndex = i;
            flag=false;
        }
        else
        {
            i++;
        }
    }while(flag && i >-1 && this->MarkerArray[i] == Marker::OCCUPIED );
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
        //error: ‘EngWord’ does not name a type dynamic_cast<EngWord>
        //                                                       ^
        if (this->MarkerArray[insertAtIndex] == Marker::OCCUPIED)
        {
            //error: ‘EngWord’ does not name a type dynamic_cast<EngWord>
            //                                                       ^
            if ((static_cast<HashElement>(this->array[insertAtIndex]) != (static_cast<HashElement>(EngWord))))
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
                for (int i = 0; i < insertAtIndex; ++i)
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
    bool flag = false;
    int rmAtIndex;
    rmAtIndex = myHash(EngWord);
    //error: ‘EngWord’ does not name a type dynamic_cast<EngWord>
    //                                                       ^
    if(this->MarkerArray[rmAtIndex] == Marker::OCCUPIED)
    {
        //error: ‘EngWord’ does not name a type dynamic_cast<EngWord>
        //                                                       ^
            if ((static_cast<HashElement>(this->array[rmAtIndex]) != (static_cast<HashElement>(EngWord))))
            {
                //linear probing. Meaning search for empty space to place obj
                for (int i = rmAtIndex; i < this->getnrOfElements(); ++i)
                {
                    if(this->MarkerArray[i] == Marker::OCCUPIED)
                    {
                        //error: ‘EngWord’ does not name a type dynamic_cast<EngWord>
                        //                                                       ^
                        if((static_cast<HashElement>(this->array[rmAtIndex]) == (static_cast<HashElement>(EngWord))))
                        {
                            flag = true;
                            this->array[rmAtIndex] = HashElement();
                            this->MarkerArray[i] = Marker::DELETED;
                            this->nrOfElements--;
                            return flag;
                        }
                    }
                }
                for (int i = 0; i < rmAtIndex; ++i)
                {
                    if(this->MarkerArray[i] == Marker::OCCUPIED)
                    {

                        if((static_cast<HashElement>(this->array[rmAtIndex]) == (static_cast<HashElement>(EngWord))))
                        {
                            flag = true;
                            this->array[rmAtIndex] = HashElement();
                            this->MarkerArray[i] = Marker::DELETED;
                            this->nrOfElements--;
                            return flag;
                        }
                    }
                }
            }


    }
    return flag;
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
    for(int r=0; r < this->hashTableSize;r++)
    {
        this->array[r]=Marker::UNTOUCHED;
    }
    this->nrOfElements=0;
}
template <typename HashElement>
double HashTable<HashElement>::loadFactor() const
{
    double loadFactor = ((double)this->nrOfElements / (double)this->hashTableSize);
	return loadFactor;
}
template <typename HashElement>
int HashTable<HashElement>::getnrOfElements() const
{
	return this->nrOfElements;
}
#endif