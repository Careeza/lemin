# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prastoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 11:13:09 by prastoin          #+#    #+#              #
#    Updated: 2019/02/19 21:45:57 by prastoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

include srcs.mk

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

LIB = libft/libft.a

INC = -Ilibft/includes -Iincludes

all: $(NAME)

$(OBJ) : Makefile srcs.mk

$(NAME): $(OBJ) $(LIB)
		gcc $(FLAG) $(INC) -o $(NAME) $(OBJ) $(LIB)

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
