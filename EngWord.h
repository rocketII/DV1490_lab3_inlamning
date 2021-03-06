// Klassen EngWord: OK
//Hanterar att klara kombinationer av insättning, borttagning och sökning: OK, genom att använda en parallell array med status vilket hanteras mha enum
//Cirkulär sondering/probning: nästan ok men antalet element kan inte vara gränsen för när det är dags att börja om på 0
// Not Created but edited by Roderik Bauhn.
//tested
#ifndef ELEMENT_H
#define ELEMENT_H
#include "Hash.h"
#include <string>
using namespace std;
//definera här
class EngWord
{
private:
	// membervariables
    string holder=" ";
public:


// constructors, destructor, ...
	EngWord(string word = "empty");
    ~EngWord();
	// memberfunctions
    const string &getHolder() const
    {
        return holder;
    }

    void setHolder(const string &holder)
    {
        EngWord::holder = holder;
    }
	// definition of == operator and != operator
    bool operator==(const EngWord& word);
    bool operator!=(const EngWord& word);
};

template<>
class Hash<EngWord>
{
public:
	int operator()(const EngWord & elem) const
	{
        //calc value modulus numberOfSockets
		// to be implement
		// the integer returned is calculated from data in HashElement
        //EngWord obj handles strings so we calculate some characteristically number based on ASCII values casted from string char.
		string first = elem.getHolder();
        //
        //cout << "word: "<< first<<endl;
        int first_ = (int) first[0];
        int second_=2;
        int third_=3;
        if(first.length() > 1)
        {
            second_ =(int) first[1]*10;
            if(first.length() > 2)
            {
                second_ =(int) first[2] * 20;
            }
        }
        //man bör tänka på datatypen ints max värdet.
        //DBG
        //cout << "word: "<< first<<" got hash:"<< (first_ * second_ + third_)<<endl;
		return (first_ * second_ + third_);
	}
};
EngWord::EngWord(const string word)
{
    this->setHolder(word);
}

EngWord::~EngWord()
{
    ;//I really don't know what to do here :3
}

bool EngWord::operator==(const EngWord &word)
{
    //true if equal false if diff.
    return this->getHolder() == word.getHolder();
}

bool EngWord::operator!=(const EngWord &word)
{
    //true if diff false if equal.
    return this->getHolder() != word.getHolder();
}

#endif