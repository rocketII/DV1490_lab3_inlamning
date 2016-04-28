#ifndef ELEMENT_H
#define ELEMENT_H

#include "Hash.h"
//definera här
class EngWord
{
private:
	// membervariables
public:
	// constructors, destructor, ...
	EngWord();
    ~EngWord();
	// memberfunctions
	// definition of == operator and != operator 
};

template<>
class Hash<EngWord>
{
public:
	int operator()(const EngWord & elem) const
	{
		// to be implement
		// the integer returned is calculated from data in HashElement
		return -1;
	}
};

#endif