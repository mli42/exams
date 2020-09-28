/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:10 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 21:13:55 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

char	**g_argv;
int		g_i;

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

	if (*(NextOpe = getNextOpe(current)))
		return (NextOpe + 1);
	return (NULL);
}

char	**getPrevcmd(char **current)
{
	char **PrevOpe;

	if (*(PrevOpe = getPrevOpe(current)))
	{
		PrevOpe = getPrevOpe(PrevOpe);
		return (PrevOpe + 1);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	g_i = 0;
	argv[0] = NULL;
	g_argv = &argv[1];
	printf("%s\n", getStr(getNextcmd(g_argv)));
	printf("%s\n", getStr(getPrevcmd(&g_argv[argc - 2])));
//	for (int i = 0; i <= argc; i++)
//		printf("END: [%3d] [%ld] [%s]\n", i, (long int)&argv[i], argv[i]);
	(void)argc; (void)argv;
}
