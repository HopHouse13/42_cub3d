# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 17:50:01 by tjacquel          #+#    #+#              #
#    Updated: 2025/09/10 13:33:12 by tjacquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
	ft_printf_dgt_functions.c ft_printf_txt_functions.c ft_printf.c

CFLAGS = -Wall -Wextra -Werror
HEADER = -I libft.h
OBJS = ${SRCS:.c=.o}
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@ar -rcs ${NAME} ${OBJS}

%.o: %.c
	@${CC} ${CFLAGS} ${HEADER} -c -o $@ $<

clean:
	@rm -f ${OBJS} ${BONUS_OBJS}

fclean : clean
	@rm -f ${NAME}

re: fclean all

bonus: all ${BONUS_OBJS}
	@ar -rcs ${NAME} ${BONUS_OBJS}

.PHONY: all clean fclean re bonus
