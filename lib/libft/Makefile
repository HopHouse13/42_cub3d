# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 17:50:01 by tjacquel          #+#    #+#              #
#    Updated: 2025/09/11 14:52:00 by tjacquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstmap.c\

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c

CFLAGS = -Wall -Wextra -Werror
HEADER = -I libft.h
CC = cc
RM = rm -rf
MKDIR = mkdir -p

# Object organization
OBJS_DIR = objs/
OBJS_SRCS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(BONUS_SRCS:.c=.o))

all: ${NAME}

# Create objects directory
$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

# Pattern rule for object compilation
$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

${NAME}: ${OBJS_SRCS}
	@ar -rcs ${NAME} ${OBJS_SRCS}

clean:
	@$(RM) ${OBJS_DIR}

fclean : clean
	@$(RM) ${NAME}

re: fclean all

bonus: all ${OBJS_BONUS}
	@ar -rcs ${NAME} ${OBJS_BONUS}

.PHONY: all clean fclean re bonus
