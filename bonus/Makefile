# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmoussam <nmoussam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 17:15:44 by nmoussam          #+#    #+#              #
#    Updated: 2022/12/06 00:54:01 by nmoussam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
INC = philo_bonus.h
SRCS_B = main.c \
		check_bonus.c \
		ft_itoa.c \
		ft_strjoin.c \
		utils_bonus.c \
		philo_bonus.c \
		lifetime_bonus.c \
		forks_bonus.c

OBJS_B = $(SRCS_B:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror -lpthread
CC = cc
RM = rm -f

all:$(NAME)

$(NAME): $(OBJS_B)
	@$(CC) $(CFLAGS) -o $(NAME) $^ 


%.o: %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS_B)

fclean : clean
	@$(RM) $(NAME)

re : fclean all