/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexconverter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:43:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 14:12:01 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_hex_null(void)
{
	char	*ret;

	ret = malloc(1);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

char	*reverse_hex(char hex[100], int j)
{
	char	*reverse;
	int		i;

	i = 0;
	while (hex[i])
		i++;
	if (!(reverse = malloc((i + 2) * sizeof(char))))
		return (NULL);
	j--;
	i = 0;
	while (j >= 0)
		reverse[i++] = hex[j--];
	reverse[i] = '\0';
	return (reverse);
}

char	*get_hex(unsigned int i, char type)
{
	int		j;
	int		temp;
	char	hex[100];

	if (i == '\0')
		return (get_hex_null());
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
	return (reverse_hex(hex, j));
}
