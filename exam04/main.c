/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:29:10 by mli               #+#    #+#             */
/*   Updated: 2020/10/02 14:26:43 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

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

	if (*(res = getPrevOpe(token)) == NULL || !isPipe(res))
		res = getPrevcmd(token);
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
		dup2(fildes[1], 1);
		exec(PrevChild(token));
		close(fildes[1]);
	}
	else
	{
		close(fildes[1]);
		dup2(fildes[0], 0);
		exec(NextChild(token));
		close(fildes[0]);
		waitpid(pid, NULL, 0);
	}
	exit(0);
}

void	exec_pipe(char **token)
{
	pid_t	pid;
	char	**lastpipe = token;
	char	**tmp;
	static char **pipe = NULL;

	if (pipe == NULL)
	{
		while (*(tmp = getNextOpe(lastpipe)) && !strcmp(*tmp, "|"))
			lastpipe = tmp;
		pipe = lastpipe;
	}
	if ((pid = fork()) == 0)
		ft_do_pipe(lastpipe);
	else
		waitpid(pid, NULL, 0);
	if (lastpipe == pipe)
	{
		pipe = NULL;
		if (getNextOpe(lastpipe) != first_last[1])
			exec(getNextOpe(lastpipe));
	}
}

static void ft_cd(char **token)
{
	char	**argv1 = token + 1;

	if (!*argv1 || isOpe(*argv1) || (*(argv1 + 1) && !isOpe(*(argv1 + 1))))
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
	if (!strcmp(*token, "cd"))
		ft_cd(token);
	else
		ft_binary(token);
}

void	exec(char **token)
{
	if (!token || (!*token && token != first_last[1]))
		return ;

	if (!isOpe(*token))
		exec_cmd(*token ? token : getPrevcmd(token));
	else if (!isPipe(token))
	{
		if (!isPipe(getPrevOpe(token)))
			exec_cmd(getPrevcmd(token));
		exec(getNextOpe(token));
	}
	else if (isPipe(token))
		exec_pipe(token);
}

int		main(int argc, char **argv)
{
	argv[0] = NULL;
	first_last[0] = argv; first_last[1] = &argv[argc];
	exec(getNextOpe(argv));
}

/*
./microshell /bin/echo lol "|" /bin/cat "|" /bin/cat -e ";" /bin/echo hey "|" /bin/cat -e "|" /usr/bin/env pbcopy ";" /bin/echo mdr ";" /bin/echo lolxd "|" /bin/cat -e ";" /bin/echo xdptdr ";"
*/
