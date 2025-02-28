#ifndef MUTANTMAP_HPP
# define MUTANTMAP_HPP

#include <iostream>
#include <stack>

template <typename Key, typename Value>

class MutantMap : public std::map<Key, Value>
{
public:
	typedef typename std::map<Key, Value>::iterator iterator;

	MutantMap();
	~MutantMap();
	MutantMap(MutantMap const &src);
	MutantMap &operator=(MutantMap const &src);
	Value findValue(const Key &key);
	Value GetValueIndx(unsigned index);

private:
};

#include "../srcs/MutantMap.tpp"
#endif
