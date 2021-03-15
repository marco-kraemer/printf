/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:16:19 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/15 15:20:16 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_length(va_list ap, const char *saved)
{
	char	*length;
	int		ret;
	int		i;
	int		j;

	i = 0;
	if (is_flag(saved, i) == 2 
	|| (is_flag(saved, i) == 1 && is_flag(saved, i + 1) == 2))
		return (-1);
	while (is_flag(saved, i) != 0)
		i++;
	if (saved[i] == '*')
		return (va_arg(ap, int));
	j = 0;
	while (ft_isdigit(saved[j]))
		j++;
	length = malloc(j * sizeof(char));
	j = 0;
	while (ft_isdigit(saved[i]))
		*(length + j++) = *(saved + i++);
	ret = ft_atoi(length);
	free(length);
	return (ret);
}

int		get_precision(va_list ap, const char *saved)
{
	char	*precision;
	int		ret;
	int		i;
	int		j;

	i = 0;
	while (is_flag(saved, i) != 2 && saved[i])
		i++;
	if (is_flag(saved, i) == 2)
		i++;
	else
		return (-1);
	if (saved[i] == '*')
		return (va_arg(ap, int));
	j = i;
	while (ft_isdigit(saved[j]))
		j++;
	precision = malloc(j * sizeof(char));
	j = i;
	i = 0;
	while (ft_isdigit(saved[j]))
		*(precision + i++) = *(saved + j++);
	ret = ft_atoi(precision);
	free(precision);
	return (ret);
}

int		print_integer(va_list ap, const char *saved)
{
	char	*print;
	size_t	precision;
	size_t	length;
	int		i;
	int		ret;

	if (ft_strlen(saved) == 0)
	{
		print = va_arg(ap, char*);
		if (print == NULL)
			print = "(null)";
		ft_putstr_fd(print, 1);
		return (ft_strlen(print));
	}
	ret = 0;
	length = get_length(ap, saved);
	precision = get_precision(ap, saved);
	printf("\n%i\n%i", length, precision);
	/*i = 0;
	if (is_flag(saved, i) == 0 || is_flag(saved, i) == 3)
		ret = ret + treat_case_0(ap, length, precision);
	else
		ret = ret + treat_case_1(ap, length, precision);
	return (ret); */
}
