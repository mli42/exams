/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:06:39 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 17:29:54 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"

ASpell::ASpell(void) { }

ASpell::ASpell(const ASpell &src) {
	*this = src;
}

ASpell &ASpell::operator=(const ASpell &src) {
	if (this == &src)
		return (*this);
	this->name = src.name;
	this->effects = src.effects;
	return (*this);
}

ASpell::~ASpell(void) { }

ASpell::ASpell(std::string const &name, std::string const &effects) : name(name), effects(effects) {
	return ;
}

void			ASpell::launch(const ATarget &target) const {
	target.getHitBySpell(*this);
}

std::string const &ASpell::getName(void) const { return this->name; }
std::string const &ASpell::getEffects(void) const { return this->effects; }
