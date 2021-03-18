/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:10:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/17 14:17:54 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*null_and_malloc(char *tmp, size_t length, int precision, int rule)
{
	char	*print;

	if (rule == 0)
	{
		if (length > ft_strlen(tmp))
			print = malloc(length * sizeof(char));
		else
			print = malloc(ft_strlen(tmp) * sizeof(char));
	}
	else
	{
		if ((int)length < 0)
		{
			if (precision > (int)ft_strlen(tmp))
				length = ft_strlen(tmp);
			else
				length = precision;
		}
		if (length > ft_strlen(tmp))
			print = malloc(length * sizeof(char));
		else
			print = malloc(ft_strlen(tmp) * sizeof(char));
	}
	return (print);
}

int		treat_case_0(va_list ap, size_t length, int precision, int j)
{
	char	*tmp;
	char	*print;
	int		i;

	i = 0;
	tmp = va_arg(ap, char*);
	if (tmp == NULL)
	{
		tmp = "(null)";
		if (precision > 0 && precision < 6)
			precision = 0;
	}
	print = null_and_malloc(tmp, length, precision, 0);
	if (precision > (int)ft_strlen(tmp) || precision < 0)
		precision = ft_strlen(tmp);
	while (i < ((int)length - precision))
		*(print + i++) = ' ';
	j = 0;
	while (j < precision)
		*(print + i++) = *(tmp + j++);
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	i = ft_strlen(print);
	free(print);
	return (i);
}

int		treat_case_1(va_list ap, size_t length, int precision)
{
	char	*tmp;
	char	*print;
	int		i;

	tmp = va_arg(ap, char*);
	if (tmp == NULL)
	{
		tmp = "(null)";
		if (precision > 0 && precision < 6)
			precision = 0;
	}
	print = null_and_malloc(tmp, length, precision, 1);
	if (precision > (int)ft_strlen(tmp) || precision < 0)
		precision = ft_strlen(tmp);
	i = -1;
	while (i++ < precision)
		*(print + i) = *(tmp + i);
	i = i - 1;
	while (i < (int)length)
		*(print + i++) = ' ';
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	i = ft_strlen(print);
	free(print);
	return (i);
}

int		print_string(va_list ap, const char *saved)
{
	char	*print;
	size_t	precision;
	size_t	length;
	int		i;
	int		ret;

	if (ft_strlen(saved) == 0)
	{
		print = va_arg(ap, char*);
		if (print == NULL)
			print = "(null)";
		ft_putstr_fd(print, 1);
		return (ft_strlen(print));
	}
	ret = 0;
	length = get_length(ap, saved);
	precision = get_precision(ap, saved);
	i = 0;
	if (is_flag(saved, i) == 0 || is_flag(saved, i) == 3)
		ret = ret + treat_case_0(ap, length, precision, 0);
	else
		ret = ret + treat_case_1(ap, length, precision);
	return (ret);
}
