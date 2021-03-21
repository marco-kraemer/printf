/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:02:09 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/20 21:00:05 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_digits1(unsigned int n)
{
	int		i;

	i = 1;
	while (i > 0)
	{
		n = n / 10;
		if (n < 1)
			break ;
		i++;
	}
	return (i);
}

char	*reverse1(char *p, char *tmp, unsigned int i, unsigned int n)
{
	unsigned int		j;
	unsigned int		c;

	c = count_digits1(n);
	j = 0;
	while (j < c)
	{
		p[j] = tmp[i - 1];
		j++;
		i--;
	}
	p[j] = '\0';
	return (p);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char	*p;
	char	tmp[count_digits1(n)];
	unsigned int	i;
	unsigned int	c;
	unsigned int	cpy;

	c = count_digits1(n);
	i = 0;
	if (!(p = (char *)malloc(c + 1)))
		return (NULL);
	cpy = n;
	while (i++ < c)
	{
		tmp[i] = (cpy % 10) + '0';
		cpy = cpy / 10;
	}
	return (reverse1(p, tmp, i, n));
}
