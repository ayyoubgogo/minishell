# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 16:26:07 by agaougao          #+#    #+#              #
#    Updated: 2024/05/24 19:55:27 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= libft.a

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror


 SRCS	=	ft_isalpha.c    ft_memcmp.c     ft_putendl_fd.c ft_striteri.c   ft_strncmp.c    ft_strmapi.c \
			ft_alnum.c      ft_isascii.c    ft_memcpy.c     ft_putnbr_fd.c  ft_strjoin.c    ft_strnstr.c \
			ft_atoi.c       ft_isdigit.c    ft_memmove.c    ft_putstr_fd.c  ft_strlcat.c    ft_strrchr.c \
			ft_bzero.c      ft_isprint.c    ft_memset.c     ft_strchr.c     ft_strlcpy.c    ft_tolower.c \
			ft_calloc.c     ft_memchr.c     ft_putchar_fd.c ft_strdup.c     ft_strlen.c     ft_toupper.c \
			ft_substr.c 	ft_strtrim.c  	ft_split.c  	ft_itoa.c 	ft_lstadd_back_bonus.c	ft_lstadd_front_bonus.c	\
			ft_lstsize_bonus.c	ft_lstclear_bonus.c ft_lstiter_bonus.c	 ft_lstdelone_bonus.c	ft_lstnew_bonus.c	ft_lstlast_bonus.c
			
OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	ar -crs $(NAME) $@

	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all
