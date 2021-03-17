/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:32 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/16 22:34:10 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

int		ft_printf(const char *s, ...);
int		print_string(va_list ap, const char *saved);
int		print_integer(va_list ap, const char *saved);
int		print_hex(va_list ap, const char *saved, char type);
int		get_precision(va_list ap, const char *saved);
int		get_length(va_list ap, const char *saved);
int		is_flag(const char *saved, int i);
char	*get_hex(unsigned int i, char type);

#endif
