# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 12:08:01 by ixu               #+#    #+#              #
#    Updated: 2024/04/11 12:08:02 by ixu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME := philo_bonus

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror
DEBUG := -fsanitize=thread

# Color scheme
BRIGHT_YELLOW := \033[0;93m
YELLOW := \033[0;33m
COLOR_END := \033[0m

# Directories
OBJS_DIR := objs_bonus/

# Source file names
SRCS := main_bonus.c

# Object files with paths
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@cc -o $(NAME) $(OBJS)
	@echo "$(BRIGHT_YELLOW)Built $(NAME)$(COLOR_END)"

bonus: .bonus

.bonus: $(OBJS_DIR) $(OBJS)
	@cc -o $(NAME) $(OBJS)
	@echo "$(BRIGHT_YELLOW)Built $(NAME)$(COLOR_END)"
	@touch .bonus

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@echo "$(YELLOW)Built object directory$(COLOR_END)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Built $@$(COLOR_END)"

clean:
	@rm -fr $(OBJS_DIR) .bonus
	@echo "$(YELLOW)Removed $(OBJS_DIR) directory and object files$(COLOR_END)"
 
fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Removed $(NAME)$(COLOR_END)"

re: fclean all