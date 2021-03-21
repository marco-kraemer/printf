/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:24:32 by maraurel          #+#    #+#             */
/*   Updated: 2021/03/21 18:47:05 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct		s_flags
{
	int			width;
	int			precision;
	int			k;
}					t_flags;

int					ft_printf(const char *s, ...);
int					print_string(va_list ap, char *saved);
int					print_integer(va_list ap, char *saved);
int					print_hex(va_list ap, char *saved, char type);
int					get_precision(va_list ap, char *saved);
int					get_length(va_list ap, char *saved);
int					is_flag(const char *saved, int i);
int					print_char(va_list ap, char *saved);
int					print_address(va_list ap, char *saved);
int					print_percent(va_list ap, char *saved);
int					print_unsigned(va_list ap, char *saved);
int					conversions(const char *s, int i);
int					is_length(const char *s, int i);
int					treat_int_0_negative(char *tmp, char *print,
		t_flags flags, int i);

char				*ft_itoa_unsigned(unsigned int n);
char				*malloc_print_integer(size_t length, char *tmp,
		int precision, int function);
char				*is_negative(char *tmp, int j);
char				*get_hex(unsigned int i, char type);
char				*get_address(unsigned long long i, int function);

#endif
