/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:32 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/19 08:57:44 by maraurel         ###   ########.fr       */
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
int		print_char(va_list ap, const char *saved);
int		print_address(va_list ap, const char *saved);
int		print_percent(void);
char	*malloc_print_integer(size_t length, char *tmp, int precision, int function);
char	*is_negative(char *tmp, int j);
char	*get_hex(unsigned int i, char type);
char	*get_address(unsigned int i, char type);
char	*get_address2(unsigned int i, char type);

#endif
