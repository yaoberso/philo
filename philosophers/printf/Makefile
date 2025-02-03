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

NAME	= libftprintf.a
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
OBJS 	= $(SRCS:.c=.o)

#FICHIERS SOURCES
SRCS	=	ft_printf.c \
			ft_putchar.c \
			ft_puthex_lower.c \
			ft_puthex_upper.c \
			ft_putnbr.c \
			ft_putpointer.c \
			ft_putstr.c \
			ft_putunsint.c \

#REGLES
all: $(NAME)

#COMPILATION DE LA BIBLIOTHEQUE
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

#COMPILATION DES FICHIERS .c EN .o
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

#NETTOYAGE DES FICHIERS OBJETS
clean:
	rm -f $(OBJS)

#NETTOYAGE COMPLET
fclean: clean
	rm -f $(NAME)

#RECONSTRUCTION COMPLETE
re: fclean all

.PHONY: all clean fclean re

