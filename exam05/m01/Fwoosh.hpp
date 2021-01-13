/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:12:03 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 17:37:50 by mli              ###   ########.fr       */
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
		~Fwoosh(void);

		virtual Fwoosh *clone(void) const;
};

#endif
