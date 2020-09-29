/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:10 by mli               #+#    #+#             */
/*   Updated: 2020/09/29 15:13:05 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

extern char	**first_last[2];

int		isOpe(char *str)
{
	if (!strcmp(str, "|") || !strcmp(str, ";"))
		return (1);
	return (0);
}

char	*getStr(char **array)
{
	return (array ? *array : NULL);
}

char	**getNextOpe(char **current)
{
	if (*current && isOpe(*current))
		current++;
	while (*current && !isOpe(*current))
		current++;
	return (current);
}

char	**getPrevOpe(char **current)
{
	if (*current && isOpe(*current))
		current--;
	while (*current && !isOpe(*current))
		current--;
	return (current);
}

char	**getNextcmd(char **current)
{
	char **NextOpe;

	if (*(NextOpe = getNextOpe(current)) || NextOpe == first_last[0])
		return (NextOpe + 1);
	return (NULL);
}

char	**getPrevcmd(char **current)
{
	char **PrevOpe;

	if (*(PrevOpe = getPrevOpe(current)) || PrevOpe == first_last[1])
	{
		PrevOpe = getPrevOpe(PrevOpe);
		return (PrevOpe + 1);
	}
	return (NULL);
}
