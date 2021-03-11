/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_asterisk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:10:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/11 12:29:48 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	treat_char(va_list ap, const char *s, int i, int space)
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
}

void	treat_string(va_list ap, const char *s, int i, int space)
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
}

void	treat_numbers(va_list ap, const char *s, int i, int space)
{
	size_t		j;
	int		value;
	char		*str_value;
	va_list		aq;

	va_copy(aq, ap);
	value = va_arg(ap, int);
	j = 0;
	if (s[i] == 'i' || s[i] == 'd' || s[i] == 'u')
		str_value = ft_itoa(value);
	if (s[i] == 'x' || s[i] == 'X')
		str_value = print_hex(value, s, i);
	if ((size_t) space >= ft_strlen(str_value))
		while (j++ < space - ft_strlen(str_value))
			write(1, "0", 1);
	free(str_value);
	print(s, i, aq);
	va_end(aq);
}

void	check_flags(va_list ap, const char *s, int i, int space)
{
	if (s[i] == '0' || s[i] == '.')
	{
		while (ft_isdigit(s[i]) || s[i] == '.')
			i++;
		if (s[i] == 'i' || s[i] == 'u' || s[i] == 'd' || s[i] == 'x' || s[i] == 'X')
			treat_numbers(ap, s, i, space);
	}
	else
	{
		while (ft_isdigit(s[i]) || s[i] == '-')
			i++;
		if (s[i] == 'c')
			treat_char(ap, s, i, space);
		else if (s[i] == 's')
			treat_string(ap, s, i, space);
	}
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
	{
		ret++;
		i++;
	}
	j = i;
	while (ft_isdigit(s[j++]))
		ret++;
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
	check_flags(ap, s, k, space);
	return (ret);
}