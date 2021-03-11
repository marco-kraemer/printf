/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexconverter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:43:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/10 10:15:22 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_hex(int i, const char *s, int k)
{
	int		j;
	int		temp;
	char	hex[100];
	char	reverse[100];
	char	*ret;

	if (i < 0)
		i = i * (-1);
	j = 0;
	while (i != 0)
	{
		temp = i % 16;
		if (temp < 10)
			temp = temp + 48;
		else
		{
			if (s[k] == 'X')
				temp = temp + 55;
			else
				temp = temp + 87;
		}
		hex[j++] = temp;
		i = i / 16;
	}
	i = 0;
	j--;
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
	return (ret);
}