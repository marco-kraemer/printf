/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:24 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/11 12:32:05 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void	print(const char *s, int i, va_list ap)
{
	if (s[i] == 's')
		ft_putstr_fd(va_arg(ap, char *), 1);
	if (s[i] == 'c')
		ft_putchar_fd(va_arg(ap, int), 1);
	if (s[i] == 'i' || s[i] == 'd' || s[i] == 'u')
		ft_putnbr_fd(va_arg(ap, int), 1);
	if (s[i] == 'x' || s[i] == 'X')
	{
		char *hex;
		hex = print_hex(va_arg(ap, int), s, i);
		ft_putstr_fd(hex, 1);
		free(hex);
	}
	if (s[i] == '%')
		write(1, "%", 1);
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
			if (((s[i] == '*' && s[i + 1] == 's') || (s[i] == '-' &&
			s[i + 1] == '*' && s[i + 2] == 's')) && !(ft_isdigit(s[i + 1])))
				i = i + flags_string(ap, s, i);
			else if ((s[i] == '*' || s[i] == '-' || s[i] == '0' || s[i] == '.') && !(ft_isdigit(s[i + 1])))
				i = i + flags_else(ap, s, i);
			else if (((s[i] == '-' || s[i] == '0' || s[i] == '.') && ft_isdigit(s[i + 1]))
			|| (ft_isdigit(s[i]) ))
				i = i + width_no_asterisk(ap, s, i);
			else
				print(s, i, ap);
		}
		else
			write(1, s + i, 1);
		i++;
	}
	return (0);
}
