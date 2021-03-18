/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:26:09 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/18 12:02:24 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_flag(const char *saved, int i)
{
	if (saved[i] == '-')
		return (1);
	if (saved[i] == '.')
		return (2);
	if (saved[i] == '0')
		return (3);
	return (0);
}

int		get_length(va_list ap, const char *saved)
{
	char	*length;
	int		ret;
	int		i;
	int		j;

	i = 0;
	if (is_flag(saved, i) == 2 
	|| (is_flag(saved, i) == 1 && is_flag(saved, i + 1) == 2))
		return (-1);
	while (is_flag(saved, i) != 0)
		i++;
	if (saved[i] == '*')
		return (va_arg(ap, int));
	j = 0;
	while (ft_isdigit(saved[j]))
		j++;
	length = malloc((j + 1) * sizeof(char));
	j = 0;
	while (ft_isdigit(saved[i]))
		*(length + j++) = *(saved + i++);
	*(length + j++) = '\0';
	ret = ft_atoi(length);
	free(length);
	return (ret);
}

int		get_precision(va_list ap, const char *saved)
{
	char	*precision;
	int		k;
	int		i;
	int		j;

	i = 0;
	while (is_flag(saved, i) != 2 && saved[i])
		i++;
	if (is_flag(saved, i) == 2)
		i++;
	else
		return (-1);
	if (saved[i] == '*')
		return (va_arg(ap, int));
	j = i;
	k = 0;
	while (ft_isdigit(saved[j]))
	{	
		j++;
		k++;
	}
	precision = malloc((k + 1) * sizeof(char));
	j = i;
	i = 0;
	while (ft_isdigit(saved[j]))
		*(precision + i++) = *(saved + j++);
	*(precision + i) = '\0';
	k = ft_atoi(precision);
	free(precision);
	return (k);
}
