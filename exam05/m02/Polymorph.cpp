/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:29:48 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:30:00 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Polymorph.hpp"

Polymorph::Polymorph(void) : ASpell("Polymorph", "turned into critter") {
	return ;
}

Polymorph::Polymorph(const Polymorph &src) { *this = src; }

Polymorph *Polymorph::clone(void) const { return (new Polymorph(*this)); }
