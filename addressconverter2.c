/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addressconverter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:43:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/19 09:08:12 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_address2(unsigned int i, char type)
{
	int		j;
	int		temp;
	char	hex[100];
	char	reverse[100];
	char	*ret;

	if (i == 0)
		return (NULL);
	if (i == 0)
	{
		ret = malloc(1);
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	j = 0;
	while (i != 0)
	{
		temp = i % 16;
		if (temp < 10)
			temp = temp + 48;
		else
		{
			if (type == 'X')
				temp = temp + 55;
			else
				temp = temp + 87;
		}
		hex[j++] = temp;
		i = i / 16;
	}
	j--;
	i = 0;
	while (j >= 0)
	{
		if (i == 0)
		{
			reverse[i] = '1';
			i++;
			reverse[i] = '0';
			i++;
		}
		reverse[i++] = hex[j--];
	}
	reverse[i] = '\0';
	if (!(ret = malloc((i + 2) * sizeof(char))))
		return (NULL);
	j = 0;
	while (reverse[j])
	{
		*(ret + j) = reverse[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}