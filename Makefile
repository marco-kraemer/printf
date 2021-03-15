# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 11:24:10 by maraurel          #+#    #+#              #
#    Updated: 2021/03/15 15:16:51 by maraurel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a


SRC = ft_printf.c \
	hexconverter.c \
	string.c \
	integer.c

HEADER = printflibft.h

OBJS = $(SRC:.c=.o)

all: $(NAME) run

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