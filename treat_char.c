/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 08:28:43 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/20 20:28:40 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_char_0(va_list ap, size_t length)
{
	int		i;

	i = 0;
	while (i++ < (int)length - 1)
		write(1, " ", 1);
	ft_putchar_fd(va_arg(ap, int), 1);
	return(i);
}

int		treat_char_1(va_list ap, size_t length)
{
	int		i;

	i = 0;
	ft_putchar_fd(va_arg(ap, int), 1);
	while (i++ < (int)length - 1)
		write (1, " ",  1);
	return (i);
}

int		print_char(va_list ap, char *saved)
{
	size_t	length;
	int		i;
	int		ret;

	i = 0;
	if (ft_strlen(saved) == 0 || is_flag(saved, i) == 2)
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		return (1);
	}
	ret = 0;
	length = get_length(ap, saved);
	if (is_flag(saved, i) == 0 || is_flag(saved, i) == 3)
		ret = ret + treat_char_0(ap, length);
	else
		ret = ret + treat_char_1(ap, length);
	return (ret);
}
