/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:33:35 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:36:52 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SpellBook_HPP
# define SpellBook_HPP

# include <iostream>
# include <string>

# include <vector>
# include "ASpell.hpp"

class SpellBook {
	private:
		typedef std::vector<ASpell*> SpellBookType;
		SpellBookType	_content;

		SpellBook(const SpellBook &src);
		SpellBook &operator=(const SpellBook &src);
	public:
		SpellBook(void);
		~SpellBook(void);

		void				learnSpell(ASpell *spell);
		void				forgetSpell(std::string const &spell);
		ASpell				*createSpell(std::string const &spell);
};

#endif
