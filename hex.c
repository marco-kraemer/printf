/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 22:08:00 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/19 20:14:01 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_hex_0(va_list ap, size_t length, int precision, const char *saved, char type)
{
	char	*tmp;
	char	*tmp1;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	tmp = get_hex(va_arg(ap, int), type);
	ret = 0;
	if (tmp[0] == '-')
	{
		tmp1 = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		free(tmp);
		j = 1;
		tmp = ft_strdup(tmp1);
		free(tmp1);
	}
	if (length > ft_strlen(tmp) && (int)length > precision)
		print = malloc(length * sizeof(char));
	else if (precision > (int)ft_strlen(tmp) && precision > (int)length)
		print = malloc(precision * sizeof(char));
	else
		print = malloc(ft_strlen(tmp) * sizeof(char));
	if (saved[0] == '0' && precision == -1)
	{
		while (precision + i < (int)length && i < (int)length - (int) ft_strlen(tmp))
			*(print + i++) = '0';
		ret = i - 1;
	}
	if (precision < 0)
		precision = ft_strlen(tmp);
	while (precision + i < (int)length && i < (int)length - (int) ft_strlen(tmp))
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
			*(print + i) = '-';
			i++;
		}
	}
	j = 0;
	while (j++ < precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	i = 0;
	free(tmp);
	free(print);
	return (ret);
}

int		treat_hex_1(va_list ap, size_t length, int precision, char type)
{
	char	*tmp;
	char	*tmp1;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	tmp = get_hex(va_arg(ap, int), type);
	ret = 0;
	if (tmp[0] == '-')
	{
		tmp1 = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		free(tmp);
		j = 1;
		tmp = ft_strdup(tmp1);
		free(tmp1);
	}
	if (length > ft_strlen(tmp) && (int)length > precision)
		print = malloc(length * sizeof(char));
	else if (precision > (int)ft_strlen(tmp) && precision > (int)length)
		print = malloc(precision * sizeof(char));
	else
		print = malloc(ft_strlen(tmp) * sizeof(char));
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

int		print_hex(va_list ap, char *saved, char type)
{
	char	*print;
	size_t	precision;
	size_t	length;
	int		ret;

	if (ft_strlen(saved) == 0)
	{
		print = get_hex(va_arg(ap, int), type);
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
		ret = ret + treat_hex_0(ap, length, precision, saved, type);
	else
		ret = ret + treat_hex_1(ap, length, precision, type);
	return (ret);
}
