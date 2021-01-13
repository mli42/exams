/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:52:50 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:55:10 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(void) : _content() { }

TargetGenerator::TargetGenerator(const TargetGenerator &src) { *this = src; }

TargetGenerator &TargetGenerator::operator=(const TargetGenerator &src) {
	if (this == &src)
		return (*this);
	return (*this);
}

TargetGenerator::~TargetGenerator(void) {
	TargetGeneratorType::iterator it = this->_content.begin();
	TargetGeneratorType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		delete *it;
	this->_content.clear();
}

void				TargetGenerator::learnTargetType(ATarget *target) {
	TargetGeneratorType::iterator it = this->_content.begin();
	TargetGeneratorType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		if ((*it)->getType() == target->getType())
			return ;
	this->_content.push_back(target->clone());
}

void				TargetGenerator::forgetTargetType(std::string const &target) {
	TargetGeneratorType::iterator it = this->_content.begin();
	TargetGeneratorType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		if ((*it)->getType() == target)
		{
			delete *it;
			this->_content.erase(it);
			return ;
		}
}

ATarget				*TargetGenerator::createTarget(std::string const &target) {
	TargetGeneratorType::iterator it = this->_content.begin();
	TargetGeneratorType::iterator ite = this->_content.end();

	for (; it != ite; ++it)
		if ((*it)->getType() == target)
			return (*it);
	return NULL;
}
