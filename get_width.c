/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:26:12 by marco             #+#    #+#             */
/*   Updated: 2021/03/21 17:27:28 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_length_asterisk(int ret, char *saved, int i)
{
	char	*old_saved;
	int		j;
	int		k;

	if (ret < 0)
	{
		old_saved = ft_strdup(saved);
		j = 0;
		k = 0;
		while (old_saved[k])
		{
			if (j == i)
			{
				*(saved + j) = '-';
				j++;
			}
			*(saved + j) = *(old_saved + k);
			j++;
			k++;
		}
		free(old_saved);
		ret = ret * (-1);
	}
	return (ret);
}

int		get_length_1(char *saved, int i)
{
	int		j;
	char	*length;

	j = 0;
	while (ft_isdigit(saved[j]))
		j++;
	length = malloc((j + 1) * sizeof(char));
	j = 0;
	while (ft_isdigit(saved[i]))
		*(length + j++) = *(saved + i++);
	*(length + j++) = '\0';
	j = ft_atoi(length);
	free(length);
	return (j);
}

int		get_length(va_list ap, char *saved)
{
	int		ret;
	int		i;

	i = 0;
	if (is_flag(saved, i) == 2
	|| (is_flag(saved, i) == 1 && is_flag(saved, i + 1) == 2))
		return (-1);
	while (is_flag(saved, i) != 0)
		i++;
	if (saved[i] == '*')
	{
		ret = va_arg(ap, int);
		return (get_length_asterisk(ret, saved, i));
	}
	return (get_length_1(saved, i));
}
