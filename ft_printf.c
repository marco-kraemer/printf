/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:24 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/13 15:43:49 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int		conversions(const char *s, int i)
{
	if (s[i] == 's' || s[i] == 'c' || s[i] == 'p' || s[i] == 'd' || s[i] == 'i' || s[i] == 'u' || s[i] == 'x' || s[i] == 'X')
		return (1);
	return (0);
}

int		get_size(const char *s, int i)
{
	int		j;

	j = 0;
	while (s[i] && conversions(s, i) == 0)
	{
		i++;
		j++;
	}
	return (j);
}

int		determine_type(va_list ap, const char *saved, char type)
{
	int		ret;

	ret = 0;
	if (type == 's')
		ret = ret + print_string(ap, saved);
	return (ret);
}

int		word_snippet(va_list ap, const char *s, int i)
{
	char	*saved;
	char	type;
	int		j;
	int		ret;

	j = 0;
	ret = 0;
	saved = malloc(get_size(s, i) * sizeof(char));
	while (s[i] && conversions(s, i) == 0)
	{
		*(saved + j) = *(s + i);
		i++;
		j++;
	}
	//*(saved + j) = *(s + i);
	type = s[i];
	ret = ret + determine_type(ap, saved,type);
	free(saved);
	return (ret);
}

int		ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	va_start(ap, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			ret = ret + word_snippet(ap, s, i);
			while (s[i] && conversions(s, i) == 0)
				i++;
			i++;
		}
		write(1, &s[i], 1);
		i++;
		ret++;
	}
	va_end(ap);
	return (ret);
}
