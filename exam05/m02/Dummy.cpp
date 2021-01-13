/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:41:12 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 17:43:19 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dummy.hpp"

Dummy::Dummy(void) : ATarget("Target Practice Dummy") {
	return ;
}

Dummy::Dummy(const Dummy &src) { *this = src; }

Dummy::~Dummy(void) { }

Dummy *Dummy::clone(void) const { return (new Dummy(*this)); }
