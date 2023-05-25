# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 11:27:24 by ylachhab          #+#    #+#              #
#    Updated: 2023/05/25 15:55:48 by ylachhab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

FLAGS  = -Wall -Wextra -Werror  #-g -fsanitize=thread

CC = cc

RM = rm -f

SRC =	philo_bonus.c \
		ft_itoa.c \
		philo_utils_bonus.c \
		philo_utils_1_bonus.c \
		philo_utils_2_bonus.c \
		philo_utils_3_bonus.c \
		philo_utils_4_bonus.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS)  -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: