/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:10:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/15 10:16:23 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_flag(const char *saved, int i)
{
	if (saved[i] == '-')
		return (1);
	if (saved[i] == '.')
		return (2);
	if (saved[i] == '0')
		return (3);
	return (0);
}

int		get_length(va_list ap, const char *saved)
{
	char	*length;
	int		ret;
	int		i;
	int		j;

	i = 0;
	if (is_flag(saved, i) == 2)
		return (-1);
	while (is_flag(saved, i) != 0)
		i++;
	if (saved[i] == '*')
		return (va_arg(ap, int));
	j = 0;
	while (ft_isdigit(saved[j]))
		j++;
	length = malloc(j * sizeof(char));
	j = 0;
	while (ft_isdigit(saved[i]))
		*(length + j++) = *(saved + i++);
	ret = ft_atoi(length);
	free(length);
	return (ret);
}

int		get_precision(va_list ap, const char *saved)
{
	char	*precision;
	int		ret;
	int		i;
	int		j;

	i = 0;
	while (is_flag(saved, i) != 2 && saved[i])
		i++;
	if (is_flag(saved, i) == 2)
		i++;
	else
		return (-1);
	if (saved[i] == '*')
		return (va_arg(ap, int));
	j = i;
	while (ft_isdigit(saved[j]))
		j++;
	precision = malloc(j * sizeof(char));
	j = i;
	i = 0;
	while (ft_isdigit(saved[j]))
		*(precision + i++) = *(saved + j++);
	ret = ft_atoi(precision);
	free(precision);
	return (ret);
	
}

int		treat_case_0(va_list ap, size_t length, int precision)
{
	char	*tmp;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	tmp = va_arg(ap, char*);
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
	{
		*(print + i) = ' ';
		i++;
	}
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
		ft_putstr_fd(print, 1);
		return (ft_strlen(print));
	}
	ret = 0;
	length = get_length(ap, saved);
	precision = get_precision(ap, saved);
	i = 0;
	if (is_flag(saved, i) == 0)
		ret = ret + treat_case_0(ap, length, precision);
	else
		ret = ret + treat_case_1(ap, length, precision);
	return (ret);
}