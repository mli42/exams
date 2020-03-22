/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 22:01:56 by mli               #+#    #+#             */
/*   Updated: 2020/03/22 02:33:14 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct	s_win
{
	int		win[2];
	char	back;
}				t_win;

typedef struct	s_circle
{
	char	c_type;
	float	x;
	float	y;
	float	rad;
	char	draw;
}				t_circle;

int		ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int		ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (1);
}

char	**ft_init_canvas(FILE *file, t_win *win)
{
	int j = -1;
	char **canvas;

	if (!fscanf(file, "%d %d %c", &win->win[0], &win->win[1], &win->back) ||
	win->win[0] <= 0 || win->win[0] > 300 || win->win[1] <= 0 || win->win[1] > 300)
		return (NULL);
	if (!(canvas = (char **)calloc(sizeof(char *), win->win[1])))
		return (NULL);
	while (++j < win->win[1])
	{
		if (!(canvas[j] = (char *)calloc(sizeof(char), win->win[0])))
			return (NULL);
		memset(canvas[j], win->back, win->win[0]);
	}
	return (canvas);
}

float	ft_dist_pt(t_circle *circle, int i, int j)
{
	return (sqrtf((circle->x - i) * (circle->x - i) + (circle->y - j) * (circle->y - j)));
}

void	ft_empty_c(char **canvas, t_win *win, t_circle *circle)
{
	int j = -1; int i;
	float dist;

	while (++j < win->win[1])
	{
		i = -1;
		while (++i < win->win[0])
		{
			dist = ft_dist_pt(circle, i, j);
			if (dist >= circle->rad - 1 && dist <= circle->rad)
				canvas[j][i] = circle->draw;
		}
	}
}

void	ft_full_c(char **canvas, t_win *win, t_circle *circle)
{
	int j = -1; int i;

	while (++j < win->win[1])
	{
		i = -1;
		while (++i < win->win[0])
		{
			if (ft_dist_pt(circle, i, j) <= circle->rad)
				canvas[j][i] = circle->draw;
		}
	}
}

int		ft_painter(FILE *file)
{
	int			ret;
	t_win		win;
	t_circle	circle;
	char		**canvas;

	if (!(canvas = ft_init_canvas(file, &win)))
		return (1);
	while ((ret = fscanf(file, "%s %f %f %f %s", &circle.c_type,
		&circle.x, &circle.y, &circle.rad, &circle.draw)) > 0)
	{
		if (circle.c_type == 'c')
			ft_empty_c(canvas, &win, &circle);
		else if (circle.c_type == 'C')
			ft_full_c(canvas, &win, &circle);
		else
			break ;
//		printf("%c %f %f %f %c\n", circle.c_type, circle.x, circle.y, circle.rad, circle.draw);
	}
	if (ret != EOF)
		return (ft_error("Error: Operation file corrupted"));
	int j = -1;
	while (++j < win.win[1])
	{
		write(1, canvas[j], win.win[0]);
		write(1, "\n", 1);
		free(canvas[j]);
	}
	free(canvas);
	fclose(file);
	return (0);
}

int		main(int argc, char **argv)
{
	FILE	*file;

	if (argc != 2)
		return (ft_error("Error: argument"));
	if (!(file = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted"));
	return (ft_painter(file));
}
