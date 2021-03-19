/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 09:13:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/19 10:38:01 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_adr_0(va_list ap, size_t length, int precision, const char *saved, char type)
{
	char	*tmp;
	char	*tmp1;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	if (precision < 0)
		tmp = get_address(va_arg(ap, int), type);
	else
		tmp = get_address3(va_arg(ap, int), type);
	ret = 0;
	if (tmp[0] == '-')
	{
		tmp1 = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		free(tmp);
		j = 1;
		tmp = ft_strdup(tmp1);
		free(tmp1);
	}
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
	if (precision < 0)
		precision = ft_strlen(tmp);
	while (precision + i < (int)length && i < (int)length - (int) ft_strlen(tmp))
		*(print + i++) = ' ';
	if (j == 1)
	{
		if (ft_strlen(tmp) >= length)
		{
			print[0] = '-';
			i++;
		}
		else if (i > 0)
			*(print + i - 1 - ret) = '-';
		else
		{
			*(print + i) = '-';
			i++;
		}
	}
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
	return (ret);
}

int		treat_adr_1(va_list ap, size_t length, int precision, char type)
{
	char	*tmp;
	char	*tmp1;
	char	*print;
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	write(1, "T", 1);
	tmp = get_address2(va_arg(ap, int), type);
	ret = 0;
	if (tmp[0] == '-')
	{
		tmp1 = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		free(tmp);
		j = 1;
		tmp = ft_strdup(tmp1);
		free(tmp1);
	}
	if (length > ft_strlen(tmp) && (int)length > precision)
		print = malloc(length * sizeof(char));
	else if (precision > (int)ft_strlen(tmp) && precision > (int)length)
		print = malloc(precision * sizeof(char));
	else
		print = malloc(ft_strlen(tmp) * sizeof(char));
	if (j == 1)
	{
		print[0] = '-';
		i++;
	}
	if (precision < 0)
		precision = ft_strlen(tmp);
	j = 0;
	while (j++ < precision - (int)ft_strlen(tmp))
		*(print + i++) = '0';
	print[i] = '0';
	print[i + 1] = 'x';
	j = 0;
	while (j < (int)ft_strlen(tmp) + 2)
		*(print + (i++ + 2)) = *(tmp + j++);
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

int		print_address(va_list ap, const char *saved)
{
	char	*print;
	size_t	precision;
	size_t	length;
	int		ret;

	if (ft_strlen(saved) == 0)
	{
		print = get_address(va_arg(ap, int), 'x');
		if (print == NULL)
		{
			free(print);
			print = "0x0";
			ft_putstr_fd(print, 1);
			ret = ft_strlen(print);
		}
		else
		{
			ft_putstr_fd(print, 1);
			ret = ft_strlen(print);
			free(print);
		}
		return (ret);
	}
	ret = 0;
	length = get_length(ap, saved);
	precision = get_precision(ap, saved);
	if (is_flag(saved, 0) != 1 && is_flag(saved, 1) != 1)
		ret = ret + treat_adr_0(ap, length, precision, saved, 'x');
	else
		ret = ret + treat_adr_1(ap, length, precision, 'x');
	return (ret);
}
