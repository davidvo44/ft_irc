/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantMap.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:58:37 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/03 13:58:40 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
MutantMap<Key, Value> &MutantMap<Key, Value>::operator=(MutantMap const &src)
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

template <typename Key, typename Value>
Value MutantMap<Key, Value>::GetValueIndex(unsigned index)
{
	if (this->empty() == true)
		return NULL;
	MutantMap<Key, Value>::iterator it = this->begin();
	unsigned nb_it = 0;
	while (nb_it < index)
	{
		if (it == this->end())
			return NULL;
		it++;
		nb_it++;
	}
	if (it == this->end())
		return NULL;
	return it->second;
}
