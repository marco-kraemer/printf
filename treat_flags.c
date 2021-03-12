/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:28:26 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/12 09:44:16 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flags_numbers(size_t space, int value, const char *s, int i)
{
	size_t	j;
	size_t	length;

	length = ft_strlen(ft_itoa(value));
	j = 0;
	if (s[i] == '*' && (s[i + 1] == 'i' || s[i + 1] == 'd' || s[i + 1] == 'u'))
	{
		if (space >= length)
			while (j++ < space - length)
				write(1, " ", 1);
		ft_putstr_fd(ft_itoa(value), 1);
	}
	if (s[i] == '-' && (s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u'))
	{
		ft_putstr_fd(ft_itoa(value), 1);
		if (space >= length)
			while (j++ < space - length)
				write(1, " ", 1);
	}
	if ((s[i] == '0' || s[i] == '.') &&
	(s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u'))
	{
		if (space >= length)
			while (j++ < space - length)
				write(1, "0", 1);
		ft_putstr_fd(ft_itoa(value), 1);
	}
	if ((size_t)space > length)
		return (space - 1);
	return (length - 1);
}

int		flags_char(size_t space, int value, const char *s, int i)
{
	size_t	j;
	size_t	length;

	length = ft_strlen(ft_itoa(value));
	j = 0;
	if (s[i] == '*' && (s[i + 1] == 'c'))
	{
		if (space >= length)
			while (j++ < space - 1)
				write(1, " ", 1);
		ft_putchar_fd(value, 1);
	}
	if (s[i] == '-' && (s[i + 2] == 'c'))
	{
		ft_putchar_fd(value, 1);
		if (space >= length)
			while (j++ < space - 1)
				write(1, " ", 1);
	}
	if (space < 1)
		return (0);
	return (space - 1);
}

int		flags_hex(size_t space, int value, const char *s, int i)
{
	char	*hex;
	size_t	length;
	size_t	k;
	size_t	j;
	
	j = 0;
	k = 0;
	while (s[i + k] != 'X' && s[i + k] != 'x')
		k++;
	hex = print_hex(value, s, i + k);
	if (s[i] == '*' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
	{
		if (space >= ft_strlen(hex))
			while (j++ < space - ft_strlen(hex))
				write(1, " ", 1);
		ft_putstr_fd(hex, 1);
	}
	if (s[i] == '-' && (s[i + 2] == 'x' || s[i + 2] == 'X'))
	{
		ft_putstr_fd(hex, 1);
		if (space >= ft_strlen(hex))
			while (j++ < space - ft_strlen(hex))
				write(1, " ", 1);
	}
	if ((s[i] == '0' || s[i] == '.') && (s[i + 2] == 'x' || s[i + 2] == 'X'))
	{
		if (space >= ft_strlen(hex))
			while (j++ < space - ft_strlen(hex))
				write(1, "0", 1);
		ft_putstr_fd(hex, 1);		
	}
	length = ft_strlen(hex);
	free (hex);
	if ((size_t)space > length)
		return (space - 1);
	return (length - 1);
}

int		flags_string(va_list ap, const char *s, int i)
{
	size_t	space;
	size_t	j;
	char	*value;

	space = va_arg(ap, int);
	value = va_arg(ap, char *);
	j = 0;
	if (s[i] == '*' && s[i + 1] == 's')
	{
		if (space >= ft_strlen(value))
			while (j++ < space - ft_strlen(value))
				write(1, " ", 1);
		ft_putstr_fd(value, 1);
	}
	else
	{
		ft_putstr_fd(value, 1);
		if (space >= ft_strlen(value))
			while (j++ < space - ft_strlen(value))
				write(1, " ", 1);
	}
	if ((size_t)space > ft_strlen(value))
		return (space - 1);
	return (ft_strlen(value) - 1);
}

int		flags_else(va_list ap, const char *s, int i)
{
	size_t	space;
	int		value;

	space = va_arg(ap, int);
	value = va_arg(ap, int);
	if ((s[i] == '*' &&
	(s[i + 1] == 'i' || s[i + 1] == 'd' || s[i + 1] == 'u')) ||
	(s[i] == '-' &&
	(s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u')) ||
	((s[i] == '0' || s[i] == '.') &&
	(s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u')))
		return (flags_numbers(space, value, s, i));
	if ((s[i] == '*' && (s[i + 1] == 'c'))
	|| (s[i] == '-' && (s[i + 2] == 'c')))
		return (flags_char(space, value, s, i));
	if ((s[i] == '-' && (s[i + 2] == 'x' || s[i + 2] == 'X')) ||
	((s[i] == '0' || s[i] == '.') && (s[i + 2] == 'x' || s[i + 2] == 'X')) ||
	(s[i] == '*' && (s[i + 1] == 'x' || s[i + 1] == 'X')))
		return (flags_hex(space, value, s, i));
	return (0);
}