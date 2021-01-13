/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BrickWall.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:31:43 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:31:53 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BrickWall_HPP
# define BrickWall_HPP

# include <iostream>
# include <string>

# include "ATarget.hpp"

class BrickWall : public ATarget {
	public:
		BrickWall(void);
		BrickWall(const BrickWall &src);
		~BrickWall(void);

		virtual BrickWall *clone(void) const;
};

#endif
