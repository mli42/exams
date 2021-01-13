/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:40:43 by mli               #+#    #+#             */
/*   Updated: 2021/01/13 17:41:47 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Dummy_HPP
# define Dummy_HPP

# include <iostream>
# include <string>

# include "ATarget.hpp"

class Dummy : public ATarget {
	public:
		Dummy(void);
		Dummy(const Dummy &src);
		~Dummy(void);

		virtual Dummy *clone(void) const;
};

#endif
