# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 21:03:54 by gvynogra          #+#    #+#              #
#    Updated: 2018/10/07 21:03:57 by gvynogra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=./ft_retro
SRCS	=./srcs/AShip.cpp \
		./srcs/Controller.cpp \
		./srcs/Enemy.cpp \
		./srcs/Player.cpp \
		./srcs/View.cpp \
		./srcs/main.cpp
OBJS	= $(SRCS:.cpp=.o)
CC		= clang++
FLAGS	= -Wall -Wextra -Werror -lncurses 

DIR_SRC = srcs
DIR_INCLUDE = include/

all: $(NAME) $(OBJS)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -I $(DIR_INCLUDE)

$(DIR_SRC)/%.o: $(DIR_SRC)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -I $(DIR_INCLUDE)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
