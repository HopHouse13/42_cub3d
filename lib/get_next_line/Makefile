# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 15:02:25 by tjacquel          #+#    #+#              #
#    Updated: 2025/09/11 15:40:43 by tjacquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
NAME_BONUS = get_next_line_bonus.a

SRCS = get_next_line.c get_next_line_utils.c
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

# Object organization
OBJS_DIR = objs/
OBJS_SRCS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(BONUS_SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
MKDIR = mkdir -p

all: $(NAME)

# Create objects directory
$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(NAME): $(OBJS_SRCS)
	@ar rcs $(NAME) $(OBJS_SRCS)
	@echo "✅ $(NAME) created successfully!"


# Bonus creates a separate library file
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@ar rcs $(NAME_BONUS) $(OBJS_BONUS)
	@echo "✅ $(NAME_BONUS) created successfully!"


# Single pattern rule - headers are included in source files
$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re


# The rule format is fundamental to Make- it tells Make
# 	"to create TARGET, you need PREREQUISITES,
# 	and here's the COMMAND to do it."

# target: prerequisites
# 	command
# 	command

# target: The file you want to create
# prerequisites: Files that the target depends on
# command: What to do to create the target (must be indented with a TAB)

# One colon (:) separates targets from prerequisites
# Pipe (|) indicates order-only prerequisites (directory must exist)
# Commands must start with a TAB character
# Pattern rules use % for matching
