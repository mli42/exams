/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 10:56:27 by mli               #+#    #+#             */
/*   Updated: 2020/10/06 14:35:40 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**first_last[2];
int		exit_status;

int		isPipe(char **str)
{
	if (!str || !*str || strcmp(*str, "|"))
		return (0);
	return (1);
}

int		isSemi(char **str)
{
	if (!str || !*str || strcmp(*str, ";"))
		return (0);
	return (1);
}

int		isOpe(char *str)
{
	if (isPipe(&str) || isSemi(&str))
		return (1);
	return (0);
}

int		ft_strlen(const char *const str)
{
	const char *tmp = str;

	while (*tmp)
		tmp++;
	return (tmp - str);
}

void	ft_putendl_fd(int const fd, char const *const str, const int newline)
{
	write(fd, str, ft_strlen(str));
	if (newline)
		write(fd, "\n", 1);
}

char	**getNextOpe(char **token)
{
	if (token == first_last[0] || (*token && isOpe(*token)))
		token++;
	while (*token && !isOpe(*token))
		token++;
	return (token);
}

char	**getPrevOpe(char **token)
{
	if (token == first_last[1] || (*token && isOpe(*token)))
		token--;
	while (*token && !isOpe(*token))
		token--;
	return (token);
}

char	**getNextCmd(char **token)
{
	if (!token || (*token == NULL && token != first_last[0]))
		return (NULL);
	return (token + 1);
}

char	**getPrevCmd(char **token)
{
	if (!token || (*token == NULL && token != first_last[1]))
		return (NULL);
	return (getPrevOpe(token) + 1);
}

// ########################################################################## //

void	fatal_error(void)
{
	ft_putendl_fd(2, "error: fatal", 1);
	exit(1);
}

int		ft_fork(pid_t *pid)
{
	if ((*pid = fork()) == -1)
		return (0);
	return (1);
}

void	ft_waitpid(const pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 2;
}

// ########################################################################## //

char	**PrevChild(char **token)
{
	char **res;

	if (*(res = getPrevOpe(token)) == NULL || !isPipe(res))
		res = getPrevCmd(token);
	return (res);
}

char	**NextChild(char **token)
{
	return (token + 1);
}

void	exec(char **token);

void	ft_do_pipe(char **token)
{
	int		fildes[2];
	pid_t	pid;

	if (pipe(fildes) == -1)
		fatal_error();
	if (!ft_fork(&pid))
		fatal_error();
	if (pid == 0)
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
		ft_waitpid(pid);
	}
	exit(0);
}

void	exec_pipe(char **token)
{
	static char **pipe = NULL;
	char **last_pipe = token;
	char **tmp;
	pid_t pid;

	if (!pipe)
	{
		while (*(tmp = getNextOpe(last_pipe)) && isPipe(tmp))
			last_pipe = tmp;
		pipe = last_pipe;
	}
	if (!ft_fork(&pid))
		fatal_error();
	if (pid == 0)
		ft_do_pipe(last_pipe);
	else
		ft_waitpid(pid);
	if (last_pipe == pipe)
	{
		pipe = NULL;
		if (*(getNextOpe(last_pipe)))
			exec(getNextOpe(last_pipe));
	}
}

void	ft_binary(char **token)
{
	 pid_t pid;
	 extern char **environ;

	 if (!ft_fork(&pid))
		 fatal_error();
	 if (pid != 0)
	 {
		 ft_waitpid(pid);
		 return ;
	 }
	 *getNextOpe(token) = NULL;
	 execve(*token, token, environ);
	 ft_putendl_fd(2, "error: cannot execute ", 0);
	 ft_putendl_fd(2, *token, 1);
	 exit(1);
}

void	ft_cd(char **token)
{
	char **argv1 = token + 1;

	if (!*argv1 || isOpe(*argv1) || (*(argv1 + 1) && !isOpe(*(argv1 + 1))))
		ft_putendl_fd(2, "error: cd: bad arguments", 1);
	else if (chdir(*argv1) == -1)
	{
		ft_putendl_fd(2, "error: cd: cannot change directory to ", 0);
		ft_putendl_fd(2, *argv1, 1);
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
		exec_cmd(*token ? token : getPrevCmd(token));
	else if (!isPipe(token))
	{
		if (!isPipe(getPrevOpe(token)))
			exec_cmd(getPrevCmd(token));
		exec(getNextOpe(token));
	}
	else if (isPipe(token))
		exec_pipe(token);
}

int		main(int argc, char **argv)
{
	argv[0] = NULL;
	exit_status = 0;
	first_last[0] = argv; first_last[1] = &argv[argc];
	exec(getNextOpe(argv));
	return (exit_status);
}
