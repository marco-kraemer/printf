/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:16:26 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 17:27:24 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_precision_asterisk(int ret, char *saved)
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
			if (old_saved[k] == '.')
			{
				*(saved + j) = '\0';
				break ;
			}
			*(saved + j) = *(old_saved + k);
			j++;
			k++;
		}
		free(old_saved);
		return (-1);
	}
	return (ret);
}

int		get_precision_1(char *saved, int j, int i)
{
	char	*precision;
	int		k;

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

int		get_precision(va_list ap, char *saved)
{
	int		ret;
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
	{
		ret = va_arg(ap, int);
		return (get_precision_asterisk(ret, saved));
	}
	j = i;
	return (get_precision_1(saved, j, i));
}
