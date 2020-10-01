/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:10 by mli               #+#    #+#             */
/*   Updated: 2020/10/01 23:43:12 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

extern char	**first_last[2];

int		isOpe(char *str)
{
	if (!str)
		return (0);
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
	if (current == first_last[0] || (*current && isOpe(*current)))
		current++;
	while (*current && !isOpe(*current))
		current++;
	return (current);
}

char	**getPrevOpe(char **current)
{
	if (current == first_last[1] || (*current && isOpe(*current)))
		current--;
	while (*current && !isOpe(*current))
		current--;
	return (current);
}

char	**getNextcmd(char **current)
{
	if (!current || (*current == NULL && current != first_last[0]))
		return (NULL);
	if (!*current || isOpe(*current))
		return (current + 1);
	return (NULL);
}

char	**getPrevcmd(char **current)
{
	if (!current || (*current == NULL && current != first_last[1]))
		return (NULL);
	if (!*current || isOpe(*current))
		return (getPrevOpe(current) + 1);
	return (NULL);
}
