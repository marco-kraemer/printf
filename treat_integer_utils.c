/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_integer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:03:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 20:50:20 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*malloc_print_integer(size_t length, char *tmp, int pre, int function)
{
	char	*print;

	if (function == 0)
	{
		if (length > ft_strlen(tmp) && (int)length > pre)
			print = malloc(length * sizeof(char));
		else if (pre > (int)ft_strlen(tmp) && pre > (int)length)
			print = malloc(pre * sizeof(char));
		else
			print = malloc(ft_strlen(tmp) * sizeof(char));
	}
	else
	{
		if (length > ft_strlen(tmp) && (int)length > pre)
			print = malloc(length * sizeof(char));
		else if (pre > (int)ft_strlen(tmp) && pre > (int)length)
			print = malloc(pre * sizeof(char));
		else
			print = malloc(ft_strlen(tmp) * sizeof(char));
	}
	return (print);
}

char	*is_negative(char *tmp, int j)
{
	char	*tmp1;

	if (j == 1)
	{
		tmp1 = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		free(tmp);
		j = 1;
		tmp = ft_strdup(tmp1);
		free(tmp1);
	}
	return (tmp);
}

int		treat_int_0_negative(char *tmp, char *print, t_flags flags, int i)
{
	if ((int)ft_strlen(tmp) >= flags.width)
		print[0] = '-';
	else if (i > 0)
	{
		*(print + i - 1 - flags.k) = '-';
		i--;
	}
	else
		*(print + i) = '-';
	i++;
	return (i);
}

int		no_precision(t_flags flags, va_list ap)
{
	char	*print;

	flags.k = 0;
	print = ft_itoa(va_arg(ap, int));
	if (print[0] == '0')
	{
		while (flags.k++ < (int)flags.width)
			write(1, " ", 1);
	}
	else
	{
		while (flags.k++ < (int)flags.width - (int)ft_strlen(print))
			write(1, " ", 1);
		ft_putstr_fd(print, 1);
	}
	return (flags.k - 1);
}
