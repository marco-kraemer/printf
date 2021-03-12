/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:24 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/12 10:43:08 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int		print(const char *s, int i, va_list ap)
{
	va_list aq;
	int	ret;

	va_copy(aq, ap);
	if (s[i] == 's')
	{
		ret = ft_strlen(va_arg(aq, char *));
		ft_putstr_fd(va_arg(ap, char *), 1);
	}
	else if (s[i] == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		ret  = 1;
	}
	else if (s[i] == 'i' || s[i] == 'd' || s[i] == 'u')
	{
		ret = ft_strlen(ft_itoa(va_arg(aq, int)));
		ft_putnbr_fd(va_arg(ap, int), 1);
	}
	else if (s[i] == 'x' || s[i] == 'X')
	{
		char *hex;
		hex = print_hex(va_arg(ap, int), s, i);
		ft_putstr_fd(hex, 1);
		ret = ft_strlen(hex);
		free(hex);
	}
	else
	{
		write(1, "%", 1);
		ret = 1;
	}
	va_end(aq);
	return (ret - 1);
}

int		ft_printf(const char *s, ...)
{
	int		i;
	int		ret;
	va_list	ap;

	ret = 0;
	va_start(ap, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (((s[i] == '*' && s[i + 1] == 's') || (s[i] == '-' &&
			s[i + 1] == '*' && s[i + 2] == 's')) && !(ft_isdigit(s[i + 1])))
				ret = ret + flags_string(ap, s, i);
			else if ((s[i] == '*' || s[i] == '-' || s[i] == '0' || s[i] == '.') && !(ft_isdigit(s[i + 1])))
				ret = ret + flags_else(ap, s, i);
			else if (((s[i] == '-' || s[i] == '0' || s[i] == '.') && ft_isdigit(s[i + 1]))
			|| (ft_isdigit(s[i]) ))
				ret = ret + width_no_asterisk(ap, s, i);
			else
				ret = ret + print(s, i, ap);
			while (s[i] == '-' || s[i] == '0' || s[i] == '.' || s[i] == '*' || ft_isdigit(s[i]))
				i++;
		}
		else
			write(1, s + i, 1);
		ret++;
		i++;
	}
	return (ret);
}
