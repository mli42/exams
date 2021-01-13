/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:28:37 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:29:13 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Polymorph_HPP
# define Polymorph_HPP

# include <iostream>
# include <string>

# include "ASpell.hpp"

class Polymorph : public ASpell {
	public:
		Polymorph(void);
		Polymorph(const Polymorph &src);

		virtual Polymorph *clone(void) const;
};

#endif
