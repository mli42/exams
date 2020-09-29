/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:10 by mli               #+#    #+#             */
/*   Updated: 2020/09/29 15:07:20 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

char	**g_argv;
int		g_argc;

char	**first_last[2];

void	exec_pipe(char **token)
{

}

void	exec_cmd(char **token)
{
}

void	exec(char **token)
{
	if (!token)
		return ;
	if (!isOpe(*token))
		exec_cmd(token);
	else if (!*token || !strcmp(*token, ";"))
	{
		exec(getPrevOpe(token));
		exec(getNextOpe(token));
	}
	else if (!strcmp(*token, "|"))
		exec_pipe(token);
}

int		main(int argc, char **argv)
{
	argv[0] = NULL;
	g_argc = argc;
	g_argv = &argv[1];
	first_last[0] = argv; first_last[1] = &argv[argc];
	printf("%s\n", getStr(getNextcmd(g_argv)));
	printf("%s\n", getStr(getPrevcmd(&g_argv[argc - 2])));
//	for (int i = 0; i <= argc; i++)
//		printf("END: [%3d] [%ld] [%s]\n", i, (long int)&argv[i], argv[i]);
	(void)argc; (void)argv;
}
