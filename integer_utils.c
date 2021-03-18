/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:03:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/17 17:04:46 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*malloc_print_integer(size_t length, char *tmp, int precision, int function)
{
	char	*print;

	if (function == 0)
	{
		if (length > ft_strlen(tmp) && (int)length > precision)
			print = malloc(length * sizeof(char));
		else if (precision > (int)ft_strlen(tmp) && precision > (int)length)
			print = malloc(precision * sizeof(char));
		else
			print = malloc(ft_strlen(tmp) * sizeof(char));
	}
	else
	{
		if (length > ft_strlen(tmp) && (int)length > precision)
			print = malloc(length * sizeof(char));
		else if (precision > (int)ft_strlen(tmp) && precision > (int)length)
			print = malloc(precision * sizeof(char));
		else
			print = malloc(ft_strlen(tmp) * sizeof(char));
	}
	return (print);
}

char	*is_negative(char *tmp, int j)
{
	char	*tmp1;

	if (j == 1)
	{
		tmp1 = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		free(tmp);
		j = 1;
		tmp = ft_strdup(tmp1);
		free(tmp1);
	}
	return (tmp);
}