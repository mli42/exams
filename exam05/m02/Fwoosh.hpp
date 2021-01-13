/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:12:03 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 22:36:56 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Fwoosh_HPP
# define Fwoosh_HPP

# include <iostream>
# include <string>

# include "ASpell.hpp"

class Fwoosh : public ASpell {
	public:
		Fwoosh(void);
		Fwoosh(const Fwoosh &src);

		virtual Fwoosh *clone(void) const;
};

#endif
