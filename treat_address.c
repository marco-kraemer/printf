/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 09:13:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 16:59:51 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_adr_0_1(t_flags flags, char *tmp, char *print)
{
	int		j;
	int		i;

	i = flags.k;
	while (flags.precision + i < (int)flags.width &&
	i < (int)flags.width - (int)ft_strlen(tmp))
		*(print + i++) = ' ';
	j = 0;
	while (j++ < flags.precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	flags.k = ft_strlen(print);
	free(tmp);
	free(print);
	return (flags.k);
}

int		treat_adr_0(va_list ap, t_flags flags)
{
	char	*tmp;
	char	*print;
	char	*tmp1;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tmp = get_address(va_arg(ap, unsigned long long), flags.precision);
	if (flags.precision > (int)ft_strlen(tmp))
	{
		tmp1 = ft_substr(tmp, 2, (ft_strlen(tmp) - 2));
		free(tmp);
		tmp = ft_strdup(tmp1);
		free(tmp1);
		write(1, "0x", 2);
		k = 2;
	}
	flags.k = i;
	print = malloc_print_integer(flags.width, tmp, flags.precision, 0);
	return (treat_adr_0_1(flags, tmp, print) + k);
}

int		treat_adr_1_1(t_flags flags, char *tmp, char *print, int i)
{
	int		j;

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
	flags.k = ft_strlen(print);
	i = 0;
	free(tmp);
	free(print);
	return (flags.k);
}

int		treat_adr_1(va_list ap, t_flags flags)
{
	char	*tmp;
	char	*print;
	int		i;

	i = 0;
	tmp = get_address(va_arg(ap, unsigned long long), flags.precision);
	flags.k = 0;
	print = malloc_print_integer(flags.width, tmp, flags.precision, 0);
	return (treat_adr_1_1(flags, tmp, print, i));
}

int		print_address(va_list ap, char *saved)
{
	char	*print;
	t_flags	flags;

	if (ft_strlen(saved) == 0)
	{
		print = get_address(va_arg(ap, unsigned long long), -1);
		ft_putstr_fd(print, 1);
		flags.k = ft_strlen(print);
		free(print);
		return (flags.k);
	}
	flags.k = 0;
	flags.width = get_length(ap, saved);
	flags.precision = get_precision(ap, saved);
	if (is_flag(saved, 0) != 1 && is_flag(saved, 1) != 1)
		flags.k = flags.k + treat_adr_0(ap, flags);
	else
		flags.k = flags.k + treat_adr_1(ap, flags);
	return (flags.k);
}
