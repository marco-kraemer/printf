/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:26:09 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 09:38:36 by maraurel         ###   ########.fr       */
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

int		get_length(va_list ap, char *saved)
{
	char	*length;
	char	*old_saved;
	int		ret;
	int		i;
	int		j;
	int		k;

	i = 0;
	if (is_flag(saved, i) == 2 
	|| (is_flag(saved, i) == 1 && is_flag(saved, i + 1) == 2))
		return (-1);
	while (is_flag(saved, i) != 0)
		i++;
	if (saved[i] == '*')
	{
		ret = va_arg(ap, int);
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

int		get_precision(va_list ap, char *saved)
{
	char	*precision;
	char	*old_saved;
	int		ret;
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
	{
		ret = va_arg(ap, int);
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
				//	j++;
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
