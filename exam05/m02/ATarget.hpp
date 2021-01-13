/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:11:51 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 17:42:24 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATarget_HPP
# define ATarget_HPP

# include <iostream>
# include <string>

# include "ASpell.hpp"

class ATarget {
	private:
	protected:
		std::string type;

	public:
		ATarget(void);
		ATarget(const ATarget &src);
		ATarget &operator=(const ATarget &src);
		ATarget(std::string const &type);
		~ATarget(void);

		std::string const	&getType(void) const;
		void				getHitBySpell(const ASpell &spell) const;

		virtual ATarget *clone(void) const = 0;
};

#endif
