/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:32 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/12 09:06:25 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

char	*print_hex(int i, const char *s, int k);
int		ft_printf(const char *s, ...);
int		flags_string(va_list ap, const char *s, int i);
int		flags_else(va_list ap, const char *s, int i);
int		width_no_asterisk(va_list ap, const char *s, int i);
int		flags_hex(size_t space, int value, const char *s, int i);
int		flags_char(size_t space, int value, const char *s, int i);
int		flags_numbers(size_t space, int value, const char *s, int i);
int		print(const char *s, int i, va_list ap);

#endif
