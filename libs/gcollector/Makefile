# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 16:26:07 by agaougao          #+#    #+#              #
#    Updated: 2024/06/13 22:17:49 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= gcollector.a

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror

SRCS	= src/gc_append.c src/gc_free.c src/gc_last.c src/gc_malloc.c

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)

%.o: %.c
	$(CC) -I include/ $(CFLAGS) -c $< -o $@
	ar -crs $(NAME) $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
