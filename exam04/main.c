/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:10 by mli               #+#    #+#             */
/*   Updated: 2020/09/30 10:25:49 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

char	**g_argv;
int		g_argc;

char	**first_last[2];

static int	ft_strlen(const char *const str)
{
	const char *tmp = str;

	while (*tmp)
		tmp++;
	return (tmp - str);
}

static void	ft_putendl_fd(const char *const str, int const fd, const int newline)
{
	write(fd, str, ft_strlen(str));
	if (newline)
		write(fd, "\n", 1);
}

void	exec_pipe(char **token)
{
	ft_putendl_fd("Lol. Do pipes", 1, 1);
	(void)token;
}

static void ft_cd(char **token)
{
	char	**argv1 = token + 1;

	if (!*argv1 || isOpe(*argv1) || *(argv1 + 1))
		ft_putendl_fd("error: cd: bad arguments", 2, 1);
	else if (chdir(*argv1) == -1)
	{
		ft_putendl_fd("error: cd: cannot change directory to ", 2, 0);
		ft_putendl_fd(*argv1, 2, 1);
	}
}

static void	ft_binary(char **token)
{
	extern char **environ;
	pid_t		pid;

	if ((pid = fork()) != 0)
	{
		waitpid(pid, NULL, 0);
		return ;
	}
	*getNextOpe(token) = NULL;
	if (execve(*token, token, environ) == -1)
	{
		ft_putendl_fd("error: cannot execute ", 2, 0);
		ft_putendl_fd(*token, 2, 1);
		exit(1);
	}
}

void	exec_cmd(char **token)
{
	if (!token || !*token)
		return ;
	if (!strcmp(*token, "cd"))
		ft_cd(token);
	else
		ft_binary(token);
}

void	exec(char **token)
{
	static int i = 0;

	if (!token || (i != 0 && !*token))
		return ;
	if (!*token || !strcmp(*token, ";"))
	{
		i++;
		exec(getPrevcmd(token));
		exec(getNextcmd(token));
	}
	else if (!strcmp(*token, "|"))
		exec_pipe(token);
	else if (!isOpe(*token))
		exec_cmd(token);
}

int		main(int argc, char **argv)
{
	argv[0] = NULL;
	g_argc = argc;
	g_argv = &argv[1];
	first_last[0] = argv; first_last[1] = &argv[argc];
	exec(getNextOpe(g_argv));
//	printf("%s\n", getStr(getNextcmd(g_argv)));
//	printf("%s\n", getStr(getPrevcmd(&g_argv[argc - 2])));
//	for (int i = 0; i <= argc; i++)
//		printf("END: [%3d] [%ld] [%s]\n", i, (long int)&argv[i], argv[i]);
	(void)argc; (void)argv;
}
