# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prastoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 11:13:09 by prastoin          #+#    #+#              #
#    Updated: 2019/02/04 15:35:46 by prastoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = main.c struct_tools.c parser.c tools.c algo.c display.c power.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -g -fsanitize=address

LIB = libft/libft.a

INC = -I./libft/ -I/usr/local/include

DOT = lem_in.h

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(DOT)
		gcc $(FLAG) $(LIB) $(LIB2) $(INC) $(OBJ) $(LIBX) -o $(NAME)

$(LIB):
		make -C libft/ fclean
			make -C ./libft/

%.o: %.c
		gcc $(FLAG) $(INC) -o $@ -c $<

clean:
		make -C libft/ clean
			rm -rf $(OBJ)

fclean: clean
		make -C libft/ fclean
			rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
