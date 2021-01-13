/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:50:17 by mli               #+#    #+#             */
/*   Updated: 2021/01/14 00:52:28 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TargetGenerator_HPP
# define TargetGenerator_HPP

# include <iostream>
# include <string>

# include <vector>
# include "ATarget.hpp"

class TargetGenerator {
	private:
		typedef std::vector<ATarget*> TargetGeneratorType;
		TargetGeneratorType	_content;

		TargetGenerator(const TargetGenerator &src);
		TargetGenerator &operator=(const TargetGenerator &src);
	public:
		TargetGenerator(void);
		~TargetGenerator(void);

		void				learnTargetType(ATarget *target);
		void				forgetTargetType(std::string const &target);
		ATarget				*createTarget(std::string const &target);
};

#endif
