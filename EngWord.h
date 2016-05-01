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
    const string &getHolder() const {
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
        int first_ = (int) first[0];
        int second_=-1;
        if(first.length() > 1)
        {
            second_ =(int) first[2];
        }

		return (first_ * second_);
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