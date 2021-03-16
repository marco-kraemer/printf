/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:10:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/15 15:27:20 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_case_0(va_list ap, size_t length, int precision)
{
	char	*tmp;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	tmp = va_arg(ap, char*);
	if (tmp == NULL)
	{
		tmp = "(null)";
		if (precision > 0 && precision < 6)
			precision = 0;
	}
	if (length > ft_strlen(tmp))
		print = malloc(length * sizeof(char));
	else
		print = malloc(ft_strlen(tmp) * sizeof(char));
	if (precision > (int)ft_strlen(tmp) || precision < 0)
		precision = ft_strlen(tmp);
	while (i < ((int)length - (int)ft_strlen(tmp)) + ((int)(ft_strlen(tmp)) - precision))
		*(print + i++) = ' ';
	j = 0;
	while (j < precision)
		*(print + i++) = *(tmp + j++);
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	free(print);
	return (ret);
}

int		treat_case_1(va_list ap, size_t length, int precision)
{
	char	*tmp;
	char	*print;
	int		i;
	int		ret;

	i = 0;
	tmp = va_arg(ap, char*);
	if (tmp == NULL)
	{
		tmp = "(null)";
		if (precision > 0 && precision < 6)
			precision = 0;
	}
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
	if (precision > (int)ft_strlen(tmp) || precision < 0)
		precision = ft_strlen(tmp);
	while (i < precision)
	{
		*(print + i) = *(tmp + i);
		i++;
	}
	while (i < (int)length)
		*(print + i++) = ' ';
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	return (ret);
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
		ret = ret + treat_case_0(ap, length, precision);
	else
		ret = ret + treat_case_1(ap, length, precision);
	return (ret);
}
