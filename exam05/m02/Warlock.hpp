/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:29:53 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:43:53 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <string>

# include "ASpell.hpp"
# include "ATarget.hpp"
# include <vector>
# include "SpellBook.hpp"

class Warlock {
	private:
		Warlock(void);
		Warlock(const Warlock &src);
		Warlock &operator=(const Warlock &src);

		std::string name;
		std::string title;

		SpellBook	spellbook;
	public:
		Warlock(const std::string &name, const std::string &title);
		~Warlock(void);

		std::string const	&getName(void) const;
		std::string const	&getTitle(void) const;

		void				setTitle(std::string const &new_title);
		void				introduce(void) const;

		void				learnSpell(ASpell *spell);
		void				forgetSpell(std::string const &spell);
		void				launchSpell(std::string const &spell, const ATarget &target);
};

#endif
