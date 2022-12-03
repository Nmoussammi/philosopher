# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 14:03:43 by nmoussam          #+#    #+#              #
#    Updated: 2022/12/03 21:21:46 by nmoussam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
INC  = philo.h
SRCS = 	main.c ft_check_args.c forks.c start_lunch.c routine.c time.c init_mutex.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc
RM = rm -rf

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all