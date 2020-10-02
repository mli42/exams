/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:49 by mli               #+#    #+#             */
/*   Updated: 2020/10/02 10:20:34 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>

char	**getNextOpe(char **current);
char	**getPrevOpe(char **current);
char	**getNextcmd(char **current);
char	**getPrevcmd(char **current);

int		isOpe(char *str);

#endif
