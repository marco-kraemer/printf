/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 20:53:20 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 20:47:54 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_unsigned_0_1(t_flags flags, char *tmp, char *print, int i)
{
	int		j;

	j = 0;
	while (j++ < flags.precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	i = ft_strlen(print);
	free(tmp);
	free(print);
	return (i);
}

int		treat_unsigned_0(va_list ap, t_flags flags, const char *saved)
{
	char		*tmp;
	char		*print;
	int			i;
	static int	j;

	i = 0;
	flags.k = 0;
	tmp = ft_itoa_unsigned(va_arg(ap, int));
	if (tmp[0] == '-')
		j = 1;
	tmp = is_negative(tmp, j);
	print = malloc_print_integer(flags.width, tmp, flags.precision, 0);
	if (saved[0] == '0' && flags.precision == -1)
	{
		while (flags.precision + i < (int)flags.width &&
		i < (int)flags.width - (int)ft_strlen(tmp))
			*(print + i++) = '0';
		flags.k = i - 1;
	}
	while (flags.precision + i < (int)flags.width &&
	i < (int)flags.width - (int)ft_strlen(tmp))
		*(print + i++) = ' ';
	if (j == 1)
		i = treat_int_0_negative(tmp, print, flags, i);
	return (treat_unsigned_0_1(flags, tmp, print, i));
}

int		treat_unsigned_1_1(t_flags flags, char *tmp, int i, char *print)
{
	int		j;
	int		ret;

	if (flags.precision < 0)
		flags.precision = ft_strlen(tmp);
	j = 0;
	while (j++ < flags.precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	j = 0;
	while (flags.precision + j++ < (int)flags.width && i < (int)flags.width)
		*(print + i++) = ' ';
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	i = 0;
	free(tmp);
	free(print);
	return (ret);
}

int		treat_unsigned_1(va_list ap, t_flags flags)
{
	char	*tmp;
	char	*print;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_itoa_unsigned(va_arg(ap, int));
	if (tmp[0] == '-')
		j = 1;
	tmp = is_negative(tmp, j);
	print = malloc_print_integer(flags.width, tmp, flags.precision, 1);
	if (j == 1)
	{
		print[0] = '-';
		i++;
	}
	return (treat_unsigned_1_1(flags, tmp, i, print));
}

int		print_unsigned(va_list ap, char *saved)
{
	char	*print;
	t_flags	flags;

	flags.width = get_length(ap, saved);
	flags.precision = get_precision(ap, saved);
	if (ft_strlen(saved) == 0)
	{
		print = ft_itoa_unsigned(va_arg(ap, int));
		if (print == NULL)
			print = "(null)";
		ft_putstr_fd(print, 1);
		flags.k = ft_strlen(print);
		free(print);
		return (flags.k);
	}
	if (flags.precision == 0)
		return (no_precision(flags, ap));
	if (is_flag(saved, 0) != 1 && is_flag(saved, 1) != 1)
		return (treat_unsigned_0(ap, flags, saved));
	return (treat_unsigned_1(ap, flags));
}
