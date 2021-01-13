/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:33:00 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 16:27:00 by mli              ###   ########.fr       */
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

