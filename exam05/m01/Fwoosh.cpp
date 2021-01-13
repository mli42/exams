/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:39:28 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 22:37:05 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fwoosh.hpp"

Fwoosh::Fwoosh(void) : ASpell("Fwoosh", "fwooshed") {
	return ;
}

Fwoosh::Fwoosh(const Fwoosh &src) { *this = src; }

Fwoosh *Fwoosh::clone(void) const { return (new Fwoosh(*this)); }
