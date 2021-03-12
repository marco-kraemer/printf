/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_asterisk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:10:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/12 08:08:43 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_char(va_list ap, const char *s, int i, int space)
{
	int		j;
	int		cp;

	cp = i - 1;
	j = 0;
	while (ft_isdigit(s[cp]))
		cp--;
	if (s[cp] == '-')
	{
		print(s, i, ap);
		while (j++ < space - 1)
			write(1, " ", 1);
	}
	else
	{
		while (j++ < space - 1)
			write(1, " ", 1);
		print(s, i, ap);
	}
	if (space > 1)
		return (space - 1);
	return (0);
}

int		treat_string(va_list ap, const char *s, int i, int space)
{
	size_t		j;
	int		cp;
	char		*value;
	va_list		aq;

	va_copy(aq, ap);
	value = va_arg(ap, char *);
	cp = i - 1;
	j = 0;
	while (ft_isdigit(s[cp]))
		cp--;
	if (s[cp] == '-')
	{
		print(s, i, aq);
		if ((size_t) space >= ft_strlen(value))
			while (j++ < space - ft_strlen(value))
				write(1, " ", 1);
	}
	else
	{
		if ((size_t) space >= ft_strlen(value))
			while (j++ < space - ft_strlen(value))
				write(1, " ", 1);
		print(s, i, aq);
	}
	va_end(aq);
	if ((size_t)space > ft_strlen(value))
		return (space - 1);
	return (ft_strlen(value) - 1);
}

int		treat_numbers(va_list ap, const char *s, int i, int space, int rule)
{
	size_t		j;
	int		value;
	size_t		length;
	char		*str_value;
	va_list		aq;
	int		cp;
	
	cp = i - 1;
	va_copy(aq, ap);
	value = va_arg(ap, int);
	j = 0;
	while (ft_isdigit(s[cp]))
		cp--;
	if (s[i] == 'i' || s[i] == 'd' || s[i] == 'u')
		str_value = ft_itoa(value);
	if (s[i] == 'x' || s[i] == 'X')
		str_value = print_hex(value, s, i);
	if (s[cp] != '-')
	{
		if ((size_t) space >= ft_strlen(str_value) && rule == 1)
			while (j++ < space - ft_strlen(str_value))
				write(1, "0", 1);
		if ((size_t) space >= ft_strlen(str_value) && rule == 0)
			while (j++ < space - ft_strlen(str_value))
				write(1, " ", 1);
		print(s, i, aq);
	}
	else
	{
		print(s, i, aq);
		if ((size_t) space >= ft_strlen(str_value) && rule == 0)
			while (j++ < space - ft_strlen(str_value))
				write(1, " ", 1);
	}
	length = ft_strlen(str_value);
	free(str_value);
	va_end(aq);
	if ((size_t)space > length)
		return (space - 1);
	return (length - 1);
}

int		check_flags(va_list ap, const char *s, int i, int space)
{
	int		ret;
	int		k;

	ret = 0;
	k = i;
	while (s[k++])
		if (s[k] == '%')
			print(s, k, ap);
	if (s[i] == '0' || s[i] == '.')
	{
		while (ft_isdigit(s[i]) || s[i] == '.')
			i++;
		if (s[i] == 'i' || s[i] == 'u' || s[i] == 'd' || s[i] == 'x' || s[i] == 'X')
			ret = ret + treat_numbers(ap, s, i, space, 1);
	}
	else
	{
		while (ft_isdigit(s[i]) || s[i] == '-')
			i++;
		if (s[i] == 'c')
			ret = ret + treat_char(ap, s, i, space);
		else if (s[i] == 's')
			ret = ret + treat_string(ap, s, i, space);
		else if (s[i] == 'i' || s[i] == 'u' || s[i] == 'd' || s[i] == 'x' || s[i] == 'X')
			ret = ret + treat_numbers(ap, s, i, space, 0);
	}
	return (ret);
}

int		width_no_asterisk(va_list ap, const char *s, int k)
{
	int		ret;
	int		j;
	char		*width;
	int		space;
	int		i;

	i = k;
	ret = 0;
	while (s[i] == '0' || s[i] == '.' || s[i] == '-')
		i++;
	j = i;
	if (!(width = malloc(ret * sizeof(char))))
		return (-1);
	j = 0; 
	while (ft_isdigit(s[i]))
	{
		*(width + j) = *(s + i);
		i++;
		j++;
	}
	space = ft_atoi(width);
	free(width);
	ret = check_flags(ap, s, k, space);
	return (ret);
}