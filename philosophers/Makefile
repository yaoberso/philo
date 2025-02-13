# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 10:21:02 by marvin            #+#    #+#              #
#    Updated: 2024/10/06 10:21:02 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror -Iprintf -g -pthread
CC		= gcc
OBJS 	= $(SRCS:.c=.o)

# FICHIERS SOURCES
SRCS	=	main.c \
			utils.c \
			check.c \
			etat.c \
			routine.c \
			init.c \

# REGLES
all: $(NAME)

# COMPILATION DE L'EXECUTABLE
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# COMPILATION DES FICHIERS .c EN .o
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

# NETTOYAGE DES FICHIERS OBJETS
clean:
	rm -f $(OBJS)

# NETTOYAGE COMPLET
fclean: clean
	rm -f $(NAME)

# RECONSTRUCTION COMPLETE
re: fclean all

.PHONY: all clean fclean re


