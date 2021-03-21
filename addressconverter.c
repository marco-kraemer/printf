/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addressconverter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:43:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 14:07:31 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_address_null(int precision)
{
	char	*ret;

	ret = malloc(3);
	ret[0] = '0';
	ret[1] = 'x';
	if (precision >= 0)
		ret[2] = '\0';
	else
		ret[2] = '0';
	ret[3] = '\0';
	return (ret);
}

char	*reverse_address(char hex[100], int j)
{
	char	*reverse;
	int		i;

	i = 0;
	while (hex[i])
		i++;
	if (!(reverse = malloc((i + 2) * sizeof(char))))
		return (NULL);
	j--;
	i = 2;
	reverse[0] = '0';
	reverse[1] = 'x';
	while (j >= 0)
		reverse[i++] = hex[j--];
	reverse[i] = '\0';
	return (reverse);
}

char	*get_address(unsigned long long i, int precision)
{
	int		j;
	int		temp;
	char	hex[100];

	if (i == '\0')
		return (get_address_null(precision));
	j = 0;
	while (i != 0)
	{
		temp = i % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 87;
		hex[j++] = temp;
		i = i / 16;
	}
	return (reverse_address(hex, j));
}
