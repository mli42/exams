/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gvp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:49 by mli               #+#    #+#             */
/*   Updated: 2020/10/19 17:12:04 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GVP_H
# define GVP_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
// # include <signal.h>

enum	e_type
{
	EMPTY, PIPE, SEMI
};

typedef struct	s_cmd
{
	int				argc;
	char			**argv;
	enum e_type		type;
	int				fds[2];
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

#endif
