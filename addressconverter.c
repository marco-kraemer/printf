/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addressconverter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:43:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/18 12:39:51 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_address(unsigned int i, char type)
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
	reverse[0] = '0';
	reverse[1] = 'x';
	i = 2;
	while (j >= 0)
		reverse[i++] = hex[j--];
	reverse[i] = '\0';
	if (!(ret = malloc(i * sizeof(char))))
		return (NULL);
	i = 0;
	while (reverse[i])
	{
		*(ret + i) = reverse[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}