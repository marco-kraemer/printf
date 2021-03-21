/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:26:09 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 17:29:12 by maraurel         ###   ########.fr       */
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

int		conversions(const char *s, int i)
{
	if (s[i] == 's' || s[i] == 'c' || s[i] == 'p' || s[i] == 'd'
	|| s[i] == 'i' || s[i] == 'u' || s[i] == 'x' || s[i] == 'X' || s[i] == '%')
		return (1);
	return (0);
}

int		is_length(const char *s, int i)
{
	if (s[i] == 'l' || s[i] == 'h' || s[i] == 'f' || s[i] == 'L')
		return (0);
	return (1);
}
