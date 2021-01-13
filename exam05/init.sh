#!/usr/bin/env bash

function init () {
	echo >> $1.hpp "
#ifndef $1_HPP
# define $1_HPP

# include <iostream>
# include <string>

class $1 {
	private:
		$1(void);
		$1(const $1 &src);
		$1 &operator=(const $1 &src);

	public:
		~$1(void);
};

#endif
	"
}
