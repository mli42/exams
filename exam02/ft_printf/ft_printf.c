/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:10:36 by exam              #+#    #+#             */
/*   Updated: 2019/12/03 11:28:44 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_printf
{
	int width;
	int precision;
	int type;
}				t_printf;

long int	power(long int nb)
{
	return ((long int)1 << nb);
}

int		ft_strlen(const char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int		ft_size(long int nb, int base_len)
{
	int size = 1;

	while (nb >= base_len)
	{
		size++;
		nb /= base_len;
	}
	return (size);
}

void	ft_swap(char *r, int max)
{
	int i = 0;
	int	swap;

	while (i < max)
	{
		swap = r[i];
		r[i++] = r[max];
		r[max--] = swap;
	}
}

char	*ft_convert(const char *base, unsigned long int nbr)
{
	int		i = 0;
	int		size;
	unsigned long int	base_len;
	char	*res;

	base_len = (unsigned long int)ft_strlen(base);
	size = ft_size(nbr, base_len);
	if (!(res = malloc(sizeof(char) * size)))
		return (NULL);
	while (nbr >= base_len)
	{
		res[i++] = base[nbr % base_len];
		nbr /= base_len;
	}
	res[i] = base[nbr % base_len];
	res[i + 1] = '\0';
	ft_swap(res, i);
	return (res);
}

int		ft_width(const char *str, int *i)
{
	int ret = 0;

	if (!(str[*i] >= '0' && str[*i] <= '9'))
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
		ret = (ret * 10) + str[(*i)++] - 48;
	return (ret);
}

int		ft_precision(const char *str, int *i)
{
	int ret = 0;

	if (str[*i] != '.')
		return (-1);
	(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
		ret = (ret * 10) + str[(*i)++] - 48;
	return (ret);
}

int		ft_type(const char *str, int *i)
{
	int j = -1;
	const char *s = "sdx";

	while (s[++j])
		if (s[j] == str[*i])
		{
			(*i)++;
			return (s[j]);
		}
	return (-1);
}

////////////////////////////////////////////////////////////////

int		ft_s(t_printf *args, int *to_ret, const char *s)
{
	int i = 0;
	int len = 0;
	int max;

	while ((args->precision == -1 || args->precision > len) && s[len])
		len++;
	max = (args->width > len ? args->width : len);
	*to_ret += max;
	while (i++ < max - len)
		write(1, " ", 1);
	write(1, s, len);
	return (1);
}

int		ft_isz(t_printf *args, int *to_ret)
{
	int i = 0;

	while (i++ < args->width)
		write(1, " ", 1);
	*to_ret += args->width;
	return (1);
}

int		ft_d(t_printf *args, int *to_ret, long int d)
{
	int i = 0;
	int		res_len;
	int		len;
	int		max;
	int		flags = ' ';
	char	*r;

	if (d == 0 && args->precision == 0)
		return (ft_isz(args, to_ret));
	if (!(r = ft_convert((args->type == 'd' ? "0123456789" : "0123456789abcdef"),
					   (d > 0 ? d : -d))))
		return (-1);
	res_len = ft_strlen(r);
	len = (args->precision > res_len ? args->precision : res_len);
	max = (args->width > len ? args->width : len);
	*to_ret += max + (d < 0  && (args->width < len + 1)? 1 : 0);
	max -= (d < 0 ? 1 : 0);
	while (i++ < max - len)
		write(1, &flags, 1);
	if (d < 0)
		write(1, "-", 1);
	i = 0;
	while (i++ < len - res_len)
		write(1, "0", 1);
	write(1, r, res_len);
	free(r);
	return (1);
}

int		ft_do(t_printf *args, int *to_ret, va_list ap)
{
	int ret = -1;

	if (args->type == 's')
		ret = ft_s(args, to_ret, va_arg(ap, char *));
	else if (args->type == 'd')
		ret = ft_d(args, to_ret, (int)va_arg(ap, int));
	else if (args->type == 'x')
		ret = ft_d(args, to_ret, (long int)va_arg(ap, unsigned int) % power((int)sizeof(unsigned int) * 8));
	return (ret);
}

int		ft_found(const char *str, int *i, int *to_ret, va_list ap)
{
	int			err = 1;
	t_printf	*args;

	(*i)++;
	if (!(args = (t_printf *)malloc(sizeof(t_printf))))
		return (-1);
	args->width = ft_width(str, i);
	args->precision = ft_precision(str, i);
	if ((args->type = ft_type(str, i)) == -1)
	{
		free(args);
		return (-1);
	}
	if (ft_do(args, to_ret, ap) == -1)
		err = -1;
	free(args);
	return (err);
}

int		ft_printf(const char *str, ...)
{
	int i = 0;
	int j = 0;
	int ret = 0;
	va_list ap;

	va_start(ap, str);
	while (str[i] && ret >= 0)
	{
		j = 0;
		while (str[i] && str[i] != '%')
		{
			i++;
			j++;
		}
		if (j)
			ret += write(1, &str[i - j], j);
		if (str[i] == '%')
			if (ft_found(str, &i, &ret, ap) == -1)
				ret = -1;
	}
	va_end(ap);
	return (ret);
}
