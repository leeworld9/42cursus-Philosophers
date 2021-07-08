# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohelee <dohelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 21:56:59 by dohelee           #+#    #+#              #
#    Updated: 2021/07/08 12:27:06 by dohelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = philo
SRCS_DIR = ./src
SRCS_NAME = init.c philo.c thread.c time.c output.c utils.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME)) 
OBJS = $(SRCS:.c=.o)

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCS_DIR) -c $^ -o $@
	
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread 

all	: $(NAME)

clean :
	rm -rf $(OBJS) 
	
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
