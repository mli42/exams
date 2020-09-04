/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:50:40 by mli               #+#    #+#             */
/*   Updated: 2020/09/03 21:43:59 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef struct	s_canvas
{
	int width;
	int height;
	char bg;
}				t_canvas;

typedef struct	s_line
{
	char type;
	float x;
	float y;
	float rad;
	char c;
}				t_line;

FILE *file = NULL;
char **canvas = NULL;
t_canvas tcan;
t_line tline;

int		ft_strlen(char *str)
{
	int i = -1;
	while (str[++i])
		;
	return (i);
}

int		ft_exit(int ret)
{
	if (!file)
		fclose(file);
	if (canvas)
	{
		while (--tcan.height >= 0)
			free(canvas[tcan.height]);
		free(canvas);
	}
	return (ret);
}

int		ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (ft_exit(1));
}

int		get_canvas()
{
	if (fscanf(file, "%d %d %c", &tcan.width, &tcan.height, &tcan.bg) < 1)
		return (0);
	if (tcan.width <= 0 || tcan.width > 300 ||
			tcan.height <= 0 || tcan.height > 300)
		return (0);
	if (!(canvas = calloc(tcan.height, sizeof(char *))))
		return (0);
	int height = tcan.height;
	while (--height >= 0)
	{
		if (!(canvas[height] = malloc(sizeof(char) * tcan.width)))
			return (0);
		memset(canvas[height], tcan.bg, tcan.width);
	}
	return (1);
}

void	print_canvas()
{
	int i = -1;
	while (++i < tcan.height)
	{
		write(1, canvas[i], tcan.width);
		write(1, "\n", 1);
	}
}

int		ft_getline()
{
	int ret;

	memset(&tline, 0, sizeof(tline));
	ret = fscanf(file, "\n%c %f %f %f %c", &tline.type, &tline.x, &tline.y, \
			&tline.rad, &tline.c);
	if (tline.type == '\0')
		return (2);
	if (ret < 1)
		return (0);
	if (tline.rad <= 0 || (tline.type != 'C' && tline.type != 'c'))
		return (0);
	return (1);
}

float	ft_ptdist(float xa, float ya, float xb, float yb)
{
	const float dist = sqrtf((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
	return (dist);
}

int		do_color(int i, int j)
{
	const float dist = ft_ptdist(i, j, tline.x, tline.y);

	if (dist > tline.rad)
		return (0);
	if (tline.type == 'C')
		return (1);
	else
	{
		if (dist > tline.rad - 1)
			return (1);
	}
	return (0);
}

int		process_lines()
{
	int ret; int i; int j;

	while ((ret = ft_getline()) == 1)
	{
		j = -1;
		while (++j < tcan.height)
		{
			i = -1;
			while (++i < tcan.width)
			{
				if (do_color(i, j))
					canvas[j][i] = tline.c;
			}
		}
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	memset(&tcan, 0, sizeof(tcan));
	memset(&tline, 0, sizeof(tline));
	if (argc != 2)
		return(ft_error("Error: argument"));
	if (!(file = fopen(argv[1], "r")))
		return(ft_error("Error: Operation file corrupted"));
	if (!get_canvas())
		return(ft_error("Error: Operation file corrupted"));
	if (!process_lines())
		return(ft_error("Error: Operation file corrupted"));
	print_canvas();
	return (ft_exit(0));
}
