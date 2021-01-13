/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:37:00 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:41:03 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SpellBook.hpp"

SpellBook::SpellBook(void) : _content() { }

SpellBook::SpellBook(const SpellBook &src) { *this = src; }

SpellBook &SpellBook::operator=(const SpellBook &src) {
	if (this == &src)
		return (*this);
	return (*this);
}

SpellBook::~SpellBook(void) {
	SpellBookType::iterator it = this->_content.begin();
	SpellBookType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		delete *it;
	this->_content.clear();
}

void				SpellBook::learnSpell(ASpell *spell) {
	SpellBookType::iterator it = this->_content.begin();
	SpellBookType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == spell->getName())
			return ;
	this->_content.push_back(spell->clone());
}

void				SpellBook::forgetSpell(std::string const &spell) {
	SpellBookType::iterator it = this->_content.begin();
	SpellBookType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == spell)
		{
			delete *it;
			this->_content.erase(it);
			return ;
		}
}

ASpell				*SpellBook::createSpell(std::string const &spell) {
	SpellBookType::iterator it = this->_content.begin();
	SpellBookType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == spell)
			return (*it);
	return NULL;
}
