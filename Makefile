# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prastoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 11:13:09 by prastoin          #+#    #+#              #
#    Updated: 2019/02/20 18:29:10 by prastoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

NAMEV = visu

include srcs.mk

OBJ = $(SRC:.c=.o)

OBJV = $(SRCV:.c=.o)

FLAG = -Wall -Wextra -Werror -g -fsanitize=address

LIB = libft/libft.a

INC = -Ilibft/includes -Iincludes

all: $(NAME) $(NAMEV)

$(OBJ) : Makefile srcs.mk

$(OBJV) : Makefile srcs.mk

$(NAME): $(OBJ) includes/lem_in.h
		make -C libft libft.a
		gcc $(FLAG) $(INC) -o $(NAME) $(OBJ) $(LIB)

$(NAMEV): $(OBJV) includes/visu.h
		gcc -lmlx -framework OpenGL -framework AppKit $(FLAG) $(INC) -o $(NAMEV) $(OBJV) $(LIB)

%.o: %.c
		gcc $(FLAG) $(INC) -o $@ -c $<

clean:
		make -C libft/ clean
			rm -rf $(OBJ)
			rm -rf $(OBJV)

fclean: clean
		make -C libft/ fclean
			rm -rf $(NAME)
			rm -rf $(NAMEV)

re: fclean all

.PHONY: clean fclean re all
