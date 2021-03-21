/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addressconverter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 09:43:11 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 10:08:09 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*treat_base(unsigned long long ull_save, int base,
char *rtn, int count)
{
	while (ull_save != 0)
	{
		if ((ull_save % base) < 10)
			rtn[count - 1] = (ull_save % base) + 48;
		else
			rtn[count - 1] = (ull_save % base) + 55;
		ull_save /= base;
		count--;
	}
	return (rtn);
}

char		*get_address(unsigned int ull, int base)
{
	char				*rtn;
	unsigned long long	ull_save;
	int					count;

	rtn = 0;
	count = 0;
	ull_save = ull;
	if (ull == 0)
		return (ft_strdup("0"));
	while (ull != 0)
	{
		ull /= base;
		count++;
	}
	if (!(rtn = malloc(sizeof(char) * (count + 1))))
		return (0);
	rtn[count] = '\0';
	rtn = treat_base(ull_save, base, rtn, count);
	return (rtn);
}