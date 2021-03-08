/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:24 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/08 16:28:58 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void	print_hex(int i, const char *s, int k)
{
	int		j;
	int		temp;
	char	hex[100];
	char	reverse[100];

	j = 0;
	while (i != 0)
	{
		temp = i % 16;
		if (temp < 10)
			temp = temp + 48;
		else
		{
			if (s[k] == 'X')
				temp = temp + 55;
			else
				temp = temp + 87;
		}
		hex[j++] = temp;
		i = i / 16;
	}
	i = 0;
	j--;
	while (j >= 0)
		reverse[i++] = hex[j--];
	reverse[i] = '\0';
	ft_putstr_fd(reverse, 1);
}

void	print(const char *s, int i, va_list ap)
{
	if (s[i] == 's')
		ft_putstr_fd(va_arg(ap, char *), 1);
	if (s[i] == 'c')
		ft_putchar_fd(va_arg(ap, int), 1);
	if (s[i] == 'i' || s[i] == 'd' || s[i] == 'u')
		ft_putnbr_fd(va_arg(ap, int), 1);
	//if (s[i] == 'p')
	//	print_adress(va_arg(ap, int));
	if (s[i] == 'x' || s[i] == 'X')
		print_hex(va_arg(ap, int), s, i);
	if (s[i] == '%')
		write(1, "%", 1);
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
				write (1, " ", 1);
		ft_putstr_fd(value, 1);
		return (1);
	}
	ft_putstr_fd(value, 1);
	if (space >= ft_strlen(value))
		while (j++ < space - ft_strlen(value))
			write (1, " ", 1);
	return (2);
}

int		flags_numbers (size_t space, int value, size_t length, const char *s, int i)
{
	size_t	j;

	j = 0;
	if (s[i] == '*' && (s[i + 1] == 'i' || s[i + 1] == 'd' || s[i + 1] == 'u'))
	{
		if (space >= length)
			while (j++ < space - length)
				write (1, " ", 1);
		ft_putstr_fd(ft_itoa(value), 1);
		return (1);
	}
	if (s[i] == '-' && (s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u'))
	{
		ft_putstr_fd(ft_itoa(value), 1);
		if (space >= length)
			while (j++ < space - length)
				write (1, " ", 1);
		return (2);
	}
	if ((s[i] == '0' || s[i] == '.') && (s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u'))
	{
		if (space >= length)
			while (j++ < space - length)
				write (1, "0", 1);
		ft_putstr_fd(ft_itoa(value), 1);
		return (2);
	}
	return (0);
}

int		flags_char (size_t space, int value, size_t length, const char *s, int i)
{
	size_t	j;

	j = 0;
	if (s[i] == '*' && (s[i + 1] == 'c'))
	{
		if (space >= length)
			while (j++ < space - 1)
				write (1, " ", 1);
		ft_putchar_fd(value, 1);
		return (1);
	}
	if (s[i] == '-' && (s[i + 2] == 'c'))
	{
		ft_putchar_fd(value, 1);
		if (space >= length)
			while (j++ < space - 1)
				write (1, " ", 1);
		return (2);
	}
	return (0);
}

int		flags_hex (size_t space, int value, size_t length, const char *s, int i)
{
	size_t	j;

	j = 0;
	if (s[i] == '*' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
	{
		if (space >= length)
			while (j++ < space - length)
				write (1, " ", 1);	
		print_hex(value, s, i + 1);
		return (1);
	}
	if (s[i] == '-' && (s[i + 2] == 'x' || s[i + 2] == 'X'))
	{
		print_hex(value, s, i + 2);
		if (space >= length)
			while (j++ < space - length)
				write (1, " ", 1);
		return (2);
	}
	if ((s[i] == '0' || s[i] == '.') && (s[i + 2] == 'x' || s[i + 2] == 'X'))
	{
		if (space >= length)
			while (j++ < space - length)
				write (1, "0", 1);
		print_hex(value, s, i + 2);
		return (2);
	}
	return (0);
}

int		flags_else(va_list ap, const char *s, int i)
{
	size_t	space;
	size_t	length;
	int		value;

	space = va_arg(ap, int);
	value = va_arg(ap, int);
	length = ft_strlen(ft_itoa(value));
	// INT
	if ((s[i] == '*' && (s[i + 1] == 'i' || s[i + 1] == 'd' || s[i + 1] == 'u')) ||
	(s[i] == '-' && (s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u')) ||
	((s[i] == '0' || s[i] == '.') && (s[i + 2] == 'i' || s[i + 2] == 'd' || s[i + 2] == 'u')))
		return flags_numbers(space, value, length, s, i);
	// CHAR
	if ((s[i] == '*' && (s[i + 1] == 'c')) || (s[i] == '-' && (s[i + 2] == 'c')))
		return flags_char(space, value, length, s, i);
	// HEX
	if ((s[i] == '-' && (s[i + 2] == 'x' || s[i + 2] == 'X')) ||
	((s[i] == '0' || s[i] == '.') && (s[i + 2] == 'x' || s[i + 2] == 'X')) ||
	(s[i] == '*' && (s[i + 1] == 'x' || s[i + 1] == 'X')))
		return flags_hex(space, value, length, s, i);
	return (0);
}

int		ft_printf(const char *s, ...)
{
	int		i;
	va_list	ap;

	va_start(ap, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if ((s[i] == '*' && s[i + 1] == 's') || (s[i] == '-' && s[i + 1] == '*' && s[i + 2] == 's'))
				i = i + flags_string(ap, s, i);
			else if (s[i] == '*' || s[i] == '-' || s[i] == '0' || s[i] == '.')
				i = i + flags_else(ap, s, i);
			else
				print(s, i, ap);
		}
		else
			write(1, s + i, 1);
		i++;
	}
	return (0);
}