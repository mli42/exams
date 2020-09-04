/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:01:16 by exam              #+#    #+#             */
/*   Updated: 2019/12/03 10:08:00 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		not_seen(char *s, int max, char c)
{
	int i = 0;

	while (s[i] && i < max)
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_inter(char *a, char *b)
{
	int i = -1;
	int j = -1;

	while (a[++i])
	{
		j = -1;
		while (b[++j])
			if (b[j] == a[i] && not_seen(a, i, a[i]))
			{
				write(1, &a[i], 1);
				break ;
			}
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
