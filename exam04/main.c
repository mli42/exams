/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:10 by mli               #+#    #+#             */
/*   Updated: 2020/09/30 17:03:16 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

char	**g_argv;
int		g_argc;

char	**first_last[2];

int		g_do_pipe = 0;

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

int		isPipe(char **token)
{
	if (!token || !*token || **token != '|')
		return (0);
	return (1);
}

int		isSemi(char **token)
{
	if (!token || !*token || **token != ';')
		return (0);
	return (1);
}

void	exec(char **token);

static char **PrevChild(char **token)
{
	char **res;

	if (*(res = getPrevOpe(token)) == NULL && !isPipe(res))
		res = getPrevcmd(token);
	if (res == token)
		return (NULL);
	return (res);
}

static char **NextChild(char **token)
{
	return (token + 1);
}

static void	ft_do_pipe(char **token)
{
	pid_t	pid;
	int		fildes[2];

	if (pipe(fildes) == -1)
		;
	if ((pid = fork()) == 0)
	{
		close(fildes[0]);
		//printf("left [%s %s]\n", *PrevChild(token), *(PrevChild(token) + 1));
		dup2(fildes[1], 1);
		exec(getPrevcmd(token));
		close(fildes[1]);
	}
	else
	{
		close(fildes[1]);
		//printf("right [%s %s]\n", *NextChild(token), *(NextChild(token) + 1));
		dup2(fildes[0], 0);
		exec(getNextcmd(token));
		close(fildes[0]);
		waitpid(pid, NULL, 0);
	}
	(void)token;
	exit(0);
(void)PrevChild; (void)NextChild;
}

void	exec_pipe(char **token)
{
	pid_t	pid;
	char	**lastpipe = token;
	char	**tmp;

	if (g_do_pipe == 0 && ++g_do_pipe)
		while (*(tmp = getNextOpe(lastpipe)) && !strcmp(*tmp, "|"))
			lastpipe = tmp;
//	printf("%s | %s\n", getStr(getPrevcmd(lastpipe)), getStr(getNextcmd(lastpipe)));
	if ((pid = fork()) == 0)
		ft_do_pipe(lastpipe);
	else
		waitpid(pid, NULL, 0);
	(void)ft_do_pipe;
	//g_do_pipe = 0;
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
	if (!token || !*token || isOpe(*token))
		return ;
	printf("cmd [%s]\n", *token);
	if (!strcmp(*token, "cd"))
		ft_cd(token);
	else
		ft_binary(token);
}

void	exec(char **token)
{
	if (!token || !*token)
		return ;
	char **NextOpe = getNextOpe(token);

	if (!isPipe(NextOpe))
	{
		exec_cmd(token);
		if (*NextOpe)
			exec(NextOpe + 1);
	}
	else if (isPipe(NextOpe))
		exec_pipe(token);
}

int		main(int argc, char **argv)
{
	argv[0] = NULL;
	g_argc = argc;
	g_argv = &argv[1];
	first_last[0] = argv; first_last[1] = &argv[argc];
	exec(g_argv);
//	printf("%s\n", getStr(getNextcmd(g_argv)));
//	printf("%s\n", getStr(getPrevcmd(&g_argv[argc - 2])));
//	for (int i = 0; i <= argc; i++)
//		printf("END: [%3d] [%ld] [%s]\n", i, (long int)&argv[i], argv[i]);
	(void)argc; (void)argv;
}
