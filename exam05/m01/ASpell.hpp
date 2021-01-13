/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:06:35 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 22:37:44 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASpell_HPP
# define ASpell_HPP

# include <iostream>
# include <string>

class ATarget;

class ASpell {
	private:
	protected:
		std::string	name;
		std::string	effects;

	public:
		ASpell(void);
		ASpell(const ASpell &src);
		ASpell &operator=(const ASpell &src);
		ASpell(std::string const &name, std::string const &effects);
		virtual ~ASpell(void);

		std::string const &getName(void) const;
		std::string const &getEffects(void) const;

		void			launch(const ATarget &target) const;

		virtual ASpell *clone(void) const = 0;
};

# include "ATarget.hpp"

#endif
