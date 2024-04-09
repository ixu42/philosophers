# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 16:32:21 by ixu               #+#    #+#              #
#    Updated: 2024/04/09 21:52:27 by ixu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME := philo

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Color scheme
BRIGHT_YELLOW := \033[0;93m
YELLOW := \033[0;33m
COLOR_END := \033[0m

# Directories
OBJS_DIR := objs/

# Source file names
SRCS := main.c \
		validate.c \
		utils.c \
		ft_atol.c \
		init.c \
		simulate.c \
		monitor.c \
		print.c \
		safe_funcs.c

# Object files with paths
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@cc -o $(NAME) $(OBJS)
	@echo "$(BRIGHT_YELLOW)Built $(NAME)$(COLOR_END)"

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@echo "$(YELLOW)Built object directory$(COLOR_END)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Built $@$(COLOR_END)"

clean:
	@rm -fr $(OBJS_DIR)
	@echo "$(YELLOW)Removed $(OBJS_DIR) directory and object files$(COLOR_END)"
 
fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Removed $(NAME)$(COLOR_END)"

re: fclean all