/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:01:44 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/19 14:13:17 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_percent(va_list ap, const char *saved)
{
	int		length;
	int		i;
	if (ft_strlen(saved) == 0)
	{
		write(1, "%", 1);
		return (1);
	}
	length = get_length(ap, saved);
	i = 0;
	if (is_flag(saved, 0) == 0 || is_flag(saved, 0) == 3)
	{
		if (is_flag(saved, 0) == 0)
			while (i++ < length - 1)
				write(1, " ", 1);
		else
			while (i++ < length - 1)
				write(1, "0", 1);
		write (1, "%", 1);
		return (i);
	}
	else
	{
		write (1, "%", 1);
		while (i++ < length - 1)
			write(1, " ", 1);
		return (i);
	}
}
