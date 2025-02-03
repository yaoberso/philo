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

NAME	= pushswap
CFLAGS	= -Wall -Wextra -Werror -Iprintf -g
CC		= gcc
OBJS 	= $(SRCS:.c=.o)

# FICHIERS SOURCES
SRCS	=	printf/ft_printf.c \
			printf/ft_putchar.c \
			printf/ft_puthex_lower.c \
			printf/ft_puthex_upper.c \
			printf/ft_putnbr.c \
			printf/ft_putpointer.c \
			printf/ft_putstr.c \
			printf/ft_putunsint.c \
			main.c \
			utils.c \

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


