/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:33:00 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 23:15:50 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock(void) {
	return ;
}

Warlock::Warlock(const Warlock &src) {
	*this = src;
}

Warlock &Warlock::operator=(const Warlock &src) {
	if (this == &src)
		return (*this);
	this->name = src.name;
	this->title = src.title;
	return (*this);
}

Warlock::~Warlock(void) {
	std::cout << this->name << ": My job here is done!" << std::endl;
	SpellBookType::iterator it = this->spellbook.begin();
	SpellBookType::iterator ite = this->spellbook.end();

	for (; it != ite; ++it)
		delete *it;
	this->spellbook.clear();
}

Warlock::Warlock(const std::string &name, const std::string &title) : name(name), title(title) {
	std::cout << this->name << ": This looks like another boring day." << std::endl;
}

std::string const	&Warlock::getName(void) const { return this->name; }
std::string const	&Warlock::getTitle(void) const { return this->title; }

void				Warlock::setTitle(std::string const &new_title) { this->title = new_title; }
void				Warlock::introduce(void) const {
	std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
}

void                Warlock::learnSpell(ASpell *spell) {
	SpellBookType::iterator it = this->spellbook.begin();
	SpellBookType::iterator ite = this->spellbook.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == spell->getName())
			return ;
	this->spellbook.push_back(spell->clone());
}

void                Warlock::forgetSpell(std::string const &spell) {
	SpellBookType::iterator it = this->spellbook.begin();
	SpellBookType::iterator ite = this->spellbook.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == spell)
		{
			delete *it;
			this->spellbook.erase(it);
			return ;
		}
}

void                Warlock::launchSpell(std::string const &spell, const ATarget &target) {
	SpellBookType::iterator it = this->spellbook.begin();
	SpellBookType::iterator ite = this->spellbook.end();

	for (; it != ite; ++it)
		if ((*it)->getName() == spell)
		{
			(*it)->launch(target);
			return ;
		}
}
