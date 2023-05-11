# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 11:27:24 by ylachhab          #+#    #+#              #
#    Updated: 2023/05/10 18:32:09 by ylachhab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS  = -Wall -Wextra -Werror # -fsanitize=thread
CC = cc

RM = rm -f

SRC =	philo.c \
		philo_utils.c \
		philo_utils_1.c \
		philo_utils_2.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

philo/%.o : philo/%.c philo/philo.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS)  -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: