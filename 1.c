/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:10:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/13 16:20:31 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_string(va_list ap, const char *saved)
{
	char	*tmp;
	char	*print;
	int		i;

	print = va_arg(ap, char*);
	if (ft_strlen(saved) == 0)
	{
		//ft_putstr_fd(print, 1);
		//return (ft_strlen(print));
	}
	tmp = malloc(25 * sizeof(char));
	i = 0;
	while (i < 25)
	{
		*(tmp + i) = '0';
		i++;
	}
	ft_strlcat(tmp, print, 60);
	//tmp[28] = '\0';
	ft_putstr_fd(tmp, 1);
	return (ft_strlen(tmp));
}