# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prastoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 11:13:09 by prastoin          #+#    #+#              #
#    Updated: 2019/02/21 01:21:33 by prastoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

NAMEV = visu

NAMES = data

include srcs.mk

OBJ = $(SRC:.c=.o)

OBJV = $(SRCV:.c=.o)

SRCS = data.c

OBJS = data.o

FLAG = -Wall -Wextra -Werror

LIB = libft/libft.a

INC = -Ilibft/includes -Iincludes

all: $(NAME) $(NAMEV)

$(OBJ) : Makefile srcs.mk

$(OBJV) : Makefile srcs.mk

$(NAME): $(OBJ) includes/lem_in.h
		make -C libft libft.a
		gcc $(FLAG) $(INC) -o $(NAME) $(OBJ) $(LIB)

$(NAMEV): $(OBJV) includes/visu.h
		gcc -lmlx -framework OpenGL -framework AppKit $(FLAG) $(INC) \
			-o $(NAMEV) $(OBJV) $(LIB)

$(NAMES): $(OBJS)
		gcc $(FLAG) -Ilibft/includes $(LIB) $(SRCS) -o $(NAMES)

%.o: %.c
		gcc $(FLAG) $(INC) -o $@ -c $<

clean:
		make -C libft/ clean
			rm -rf $(OBJ)
			rm -rf $(OBJV)
			rm -rf $(OBJS)

fclean: clean
		make -C libft/ fclean
			rm -rf $(NAME)
			rm -rf $(NAMEV)
			rm -rf $(NAMES)

re: fclean all

.PHONY: clean fclean re all
