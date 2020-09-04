/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:50:40 by mli               #+#    #+#             */
/*   Updated: 2020/09/03 16:51:06 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

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
	float w;
	float h;
	char c;
}				t_line;

FILE *file = NULL;
char	**canvas = NULL;
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
		while (--tcan.height >= 0)
			free(canvas[tcan.height]);
	free(canvas);
	return (ret);
}

int		ft_error(char *error)
{
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return (ft_exit(1));
}

int		get_canvas()
{
	int height;

	if (fscanf(file, "%d %d %c", &tcan.width, &tcan.height, &tcan.bg) == -1)
		return (0);
	if (tcan.width <= 0 || tcan.width > 300 ||
			tcan.height <= 0 || tcan.height > 300)
		return (0);
	if (!(canvas = calloc(tcan.height, sizeof(char *))))
		return (0);
	height = tcan.height;
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
	ret = fscanf(file, "\n%c %f %f %f %f %c", &tline.type, &tline.x, &tline.y, \
			&tline.w, &tline.h, &tline.c);
	if (tline.type == '\0')
		return (2);
	if (ret == -1)
		return (0);
	if (tline.w <= 0 || tline.h <= 0 || (tline.type != 'R' && tline.type != 'r'))
		return (0);
	return (1);
}

int		ft_isinrect(int x, int y)
{
	if (x >= tline.x && x <= (int)(tline.x + tline.w) &&
			y >= tline.y && y <= (int)(tline.y + tline.h))
		return (1);
	return (0);
}

int		ft_isinborder(int x, int y)
{
	if (ft_isinrect(x, y) && (
			(x <= (int)(tline.x + 1) || x >= (int)(tline.x + tline.w)) ||
			(y <= (int)(tline.y + 1) || y >= (int)(tline.y + tline.h))))
		return (1);
	return (0);
}

int		process_lines()
{
	int ret; int i; int j;

	while ((ret = ft_getline()) == 1)
	{
		j = -1;
		while (++j < tcan.width)
		{
			i = -1;
			while (++i < tcan.height)
			{
				if ((tline.type == 'R' && ft_isinrect(j, i)) ||
					(tline.type == 'r' && ft_isinborder(j, i)))
					canvas[i][j] = tline.c;
			}
		}
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		return(ft_error("Error: argument"));
	if (!(file = fopen(argv[1], "r")))
		return(ft_error("Error: Operation file corrupted"));
	memset(&tcan, 0, sizeof(tcan));
	if (!get_canvas())
		return(ft_error("Error: Operation file corrupted"));
	if (!process_lines())
		return(ft_error("Error: Operation file corrupted"));
	print_canvas();
	return (ft_exit(0));
}
