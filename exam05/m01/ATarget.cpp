/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:23:42 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 17:26:31 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"

ATarget::ATarget(void) { }

ATarget::ATarget(const ATarget &src) {
	*this = src;
}

ATarget &ATarget::operator=(const ATarget &src) {
	if (this == &src)
		return (*this);
	this->type = src.type;
	return (*this);
}

ATarget::~ATarget(void) { }

ATarget::ATarget(std::string const &type) : type(type) {
	return ;
}

std::string const &ATarget::getType(void) const { return this->type; }

void			ATarget::getHitBySpell(const ASpell &spell) const {
	std::cout << this->type << " has been " << spell.getEffects() << "!" << std::endl;
}
