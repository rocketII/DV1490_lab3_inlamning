// Not created by Roderik Bauhn
#ifndef HASH_H
#define HASH_H
//får ej modifieras
//tested
template <typename Key>
class Hash
{
public:
	int operator()(const Key & key) const; 
};

#endif
