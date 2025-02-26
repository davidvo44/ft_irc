#include "MutantMap.hpp"

template <typename Key, typename Value>
MutantMap<Key, Value>::MutantMap() : std::map<Key, Value>() 
{
}

template <typename Key, typename Value>
MutantMap<Key, Value>::MutantMap(MutantMap const &src)
{
	(void)src;
}

template <typename Key, typename Value>
MutantMap<Key, Value>::~MutantMap()
{

}

template <typename Key, typename Value>
MutantMap<Key, Value>&  MutantMap<Key, Value>::operator=(MutantMap const & src)
{
	this = src.c;
	return (*this);
}

template <typename Key, typename Value>
Value MutantMap<Key, Value>::findValue(const Key &key)
{
	MutantMap<Key, Value>::iterator it = this->find(key);
	if (this->empty() == true || it == this->end())
		return NULL;
	return it->second;
}