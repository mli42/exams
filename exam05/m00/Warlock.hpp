/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:09:12 by mli               #+#    #+#             */
/*   Updated: 2021/01/06 23:44:54 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <string>

class Warlock {
	public:
		Warlock(const std::string name, const std::string title) : _name(name), _title(title) {
			// <NAME>: This looks like another boring day.
			std::cout << name << ": This looks like another boring day." << std::endl;
		};
		virtual ~Warlock(void) {
			// <NAME>: My job here is done!
			std::cout << this->_name << ": My job here is done!" << std::endl;
		};

		void	introduce(void) const {
			// <NAME>: I am <NAME>, <TITLE> !
			std::cout << this->_name << ": I am " << this->_name << ", " <<  this->_title << "!"  << std::endl;
		};

		void	setTitle(const std::string &new_title) {
			this->_title = new_title;
		};

		std::string		getName(void) const { return this->_name; };
		std::string		getTitle(void) const { return this->_title; };

	private:
		Warlock(void) { };
		Warlock(const Warlock &rhs) { *this = rhs; };
		Warlock	&operator=(const Warlock &rhs) {
			if (this == &rhs)
				return (*this);
			this->_name = rhs._name;
			this->_title = rhs._title;
			return (*this);
		};

		std::string		_name;
		std::string		_title;
};

#endif
