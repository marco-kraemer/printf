/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 09:13:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 11:55:58 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_adr_0(va_list ap, size_t length, int precision, const char *saved)
{
	char	*tmp;
	char	*print;
	char	*tmp1;
	int		i;
	int		j;
	int		k;
	int		ret;

	i = 0;
	j = 0;
	k = 0;
	tmp = get_address(va_arg(ap, unsigned long long), precision);
	if (precision > (int)ft_strlen(tmp))
	{
		tmp1 = ft_substr(tmp, 2, (ft_strlen(tmp) - 2));
		free(tmp);
		tmp = ft_strdup(tmp1);
		free(tmp1);
		write(1, "0x", 2);
		k = 2;
	}
	ret = 0;
	if (length > ft_strlen(tmp) && (int)length > precision)
		print = malloc(length * sizeof(char));
	else if (precision > (int)ft_strlen(tmp) && precision > (int)length)
		print = malloc(precision * sizeof(char));
	else
		print = malloc(ft_strlen(tmp) * sizeof(char));
	if (saved[0] == '0' && precision == -1)
	{
		while (precision + i < (int)length && i < (int)length - (int) ft_strlen(tmp))
			*(print + i++) = '0';
		ret = i - 1;
	}
	while (precision + i < (int)length && i < (int)length - (int) ft_strlen(tmp))
		*(print + i++) = ' ';
	j = 0;
	while (j++ < precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	i = 0;
	free(tmp);
	free(print);
	return (ret + k);
}

int		treat_adr_1(va_list ap, size_t length, int precision)
{
	char	*tmp;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	tmp = get_address(va_arg(ap, unsigned long long), precision);
	ret = 0;
	if (length > ft_strlen(tmp) && (int)length > precision)
		print = malloc(length * sizeof(char));
	else if (precision > (int)ft_strlen(tmp) && precision > (int)length)
		print = malloc(precision * sizeof(char));
	else
		print = malloc(ft_strlen(tmp) * sizeof(char));
	if (precision < 0)
		precision = ft_strlen(tmp);
	j = 0;
	while (j++ < precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	j = 0;
	while (j < (int)ft_strlen(tmp))
		*(print + i++) = *(tmp + j++);
	j = 0;
	while (precision + j++ < (int)length && i < (int)length)
		*(print + i++) = ' ';
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	i = 0;
	free(tmp);
	free(print);
	return (ret);
}

int		print_address(va_list ap, char *saved)
{
	char	*print;
	size_t	precision;
	size_t	length;
	int		ret;

	if (ft_strlen(saved) == 0)
	{
		print = get_address(va_arg(ap, unsigned long long), -1);
		ft_putstr_fd(print, 1);
		ret = ft_strlen(print);
		free(print);
		return (ret);
	}
	ret = 0;
	length = get_length(ap, saved);
	precision = get_precision(ap, saved);
	if (is_flag(saved, 0) != 1 && is_flag(saved, 1) != 1)
		ret = ret + treat_adr_0(ap, length, precision, saved);
	else
		ret = ret + treat_adr_1(ap, length, precision);
	return (ret);
}
