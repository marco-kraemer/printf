# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 11:24:10 by maraurel          #+#    #+#              #
#    Updated: 2021/03/21 17:26:49 by maraurel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a


SRC = ft_printf.c \
	hexconverter.c \
	treat_string.c \
	treat_integer.c \
	ft_printf_utils.c \
	treat_hex.c \
	treat_char.c \
	treat_address.c \
	treat_integer_utils.c \
	treat_percent.c \
	treat_unsigned.c \
	addressconverter.c \
	ft_itoa_unsigned.c \
	get_precision.c \
	get_width.c

HEADER = printflibft.h

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): lib
	@gcc -Wall -Wextra -Werror -c $(SRC)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)

lib:
	@$(MAKE) -C libft

clean: cleanlibft
	@$(RM) $(OBJS)

cleanlibft:
	@$(MAKE) clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) a.out
	@$(MAKE) fclean -C libft


re: fclean all

run:
	@clear
	@gcc main.c $(NAME)
	@./a.out

git:
	git add .
	git commit -m "Update"
	git push