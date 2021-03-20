/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:16:19 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/19 21:39:50 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int		treat_int_0_1(int precision, char *tmp, char *print, int i)
{
	int		j;

	j = 0;
	while (j++ < precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	i = ft_strlen(print);
	free(tmp);
	free(print);
	return (i);
}

int		treat_int_0(va_list ap, size_t length, int precision, const char *saved)
{
	char	*tmp;
	char	*print;
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = 0;
	tmp = ft_itoa(va_arg(ap, int));
	if (tmp[0] == '-')
		j = 1;
	tmp = is_negative(tmp, j);
	print = malloc_print_integer(length, tmp, precision, 0);
	if (saved[0] == '0' && precision == -1)
	{
		while (precision + i < (int)length &&
		i < (int)length - (int)ft_strlen(tmp))
			*(print + i++) = '0';
		ret = i - 1;
	}
	if (precision < 0)
		precision = ft_strlen(tmp);
	while (precision + i < (int)length &&
	i < (int)length - (int)ft_strlen(tmp))
		*(print + i++) = ' ';
	if (j == 1)
	{
		if (ft_strlen(tmp) >= length)
		{
			print[0] = '-';
			i++;
		}
		else if (i > 0)
			*(print + i - 1 - ret) = '-';
		else
		{
			write(1, "T", 1);
			*(print + i) = '-';
			i++;
		}
	}
	return (treat_int_0_1(precision, tmp, print, i));
}

int		treat_int_1(va_list ap, size_t length, int precision)
{
	char	*tmp;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	tmp = ft_itoa(va_arg(ap, int));
	if (tmp[0] == '-')
		j = 1;
	tmp = is_negative(tmp, j);
	print = malloc_print_integer(length, tmp, precision, 1);
	if (j == 1)
	{
		print[0] = '-';
		i++;
	}
	if (precision < 0)
		precision = ft_strlen(tmp);
	j = 0;
	while (j++ < precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	j = 0;
	while (precision + j++ < (int)length && i < (int)length)
		*(print + i++) = ' ';
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	i = 0;
	free(tmp);
	free(print);
	return (ret);
}

int		print_integer(va_list ap, char *saved)
{
	char	*print;
	size_t	precision;
	size_t	length;
	int		ret;

	if (ft_strlen(saved) == 0)
	{
		print = ft_itoa(va_arg(ap, int));
		if (print == NULL)
			print = "(null)";
		ft_putstr_fd(print, 1);
		ret = ft_strlen(print);
		free(print);
		return (ret);
	}
	ret = 0;
	length = get_length(ap, saved);
	precision = get_precision(ap, saved);
	if (precision == 0)
	{
		while (ret < (int)length)
		{
			write(1, " ", 1);
			ret++;
		}
		return (ret);
	}
	if (is_flag(saved, 0) != 1 && is_flag(saved, 1) != 1)
		ret = ret + treat_int_0(ap, length, precision, saved);
	else
		ret = ret + treat_int_1(ap, length, precision);
	return (ret);
}
