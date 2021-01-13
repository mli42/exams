/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fireball.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:27:42 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:28:08 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fireball.hpp"

Fireball::Fireball(void) : ASpell("Fireball", "burnt to a crisp") {
	return ;
}

Fireball::Fireball(const Fireball &src) { *this = src; }

Fireball *Fireball::clone(void) const { return (new Fireball(*this)); }
