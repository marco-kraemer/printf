/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 08:28:43 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/19 20:13:55 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		treat_char_0(va_list ap, size_t length)
{
	char	tmp;
	char	*print;
	int		i;
	int		ret;

	i = 0;
	tmp = va_arg(ap, int);
	if (length > 1)
		print = malloc(length * sizeof(char));
	else
		print = malloc(1 * sizeof(char));
	while (i < ((int)length))
		*(print + i++) = ' ';
	*(print + i - 1) = tmp;
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	ret = ft_strlen(print);
	if (tmp == '\0')
		ret++;
	free(print);
	return (ret);
}

int		treat_char_1(va_list ap, size_t length)
{
	char	tmp;
	char	*print;
	int		i;
	int		ret;

	i = 0;
	tmp = va_arg(ap, int);
	if (length > 1)
		print = malloc(length * sizeof(char));
	else
		print = malloc(1 * sizeof(char));
	*(print + i) = tmp;
	i++;
	while (i < (int)length)
		*(print + i++) = ' ';
	*(print + i) = '\0';
	ft_putstr_fd(print, 1);
	if (tmp == '\0')
		return(length);
	ret = ft_strlen(print);
	free(print);
	return (ret);
}

int		print_char(va_list ap, char *saved)
{
	char	print;
	size_t	length;
	int		i;
	int		ret;

	if (ft_strlen(saved) == 0)
	{
		print = va_arg(ap, int);
		ft_putchar_fd(print, 1);
		return (1);
	}
	ret = 0;
	length = get_length(ap, saved);
	i = 0;
	if (is_flag(saved, i) == 0 || is_flag(saved, i) == 3)
		ret = ret + treat_char_0(ap, length);
	else
		ret = ret + treat_char_1(ap, length);
	return (ret);
}
