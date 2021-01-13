/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BrickWall.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:32:03 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:32:20 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BrickWall.hpp"

BrickWall::BrickWall(void) : ATarget("Inconspicuous Red-brick Wall") {
	return ;
}

BrickWall::BrickWall(const BrickWall &src) { *this = src; }

BrickWall::~BrickWall(void) { }

BrickWall *BrickWall::clone(void) const { return (new BrickWall(*this)); }
