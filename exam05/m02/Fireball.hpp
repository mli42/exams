/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fireball.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:26:40 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:27:03 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Fireball_HPP
# define Fireball_HPP

# include <iostream>
# include <string>

# include "ASpell.hpp"

class Fireball : public ASpell {
	public:
		Fireball(void);
		Fireball(const Fireball &src);

		virtual Fireball *clone(void) const;
};

#endif
