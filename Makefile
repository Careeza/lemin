# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prastoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 11:13:09 by prastoin          #+#    #+#              #
#    Updated: 2019/02/11 11:44:50 by prastoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = main.c struct_tools.c parser.c tools.c display.c free.c power.c \
	  ft_best_path.c cycle_detector.c ft_print_ant_path.c ft_strsplitlem.c \
	  ft_strsublem.c parser_2.c tools2.c debug.c

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
