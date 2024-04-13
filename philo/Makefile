# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 16:32:21 by ixu               #+#    #+#              #
#    Updated: 2024/04/13 14:57:06 by ixu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME := philo

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror
DEBUG := -fsanitize=thread

# Color scheme
BRIGHT_YELLOW := \033[0;93m
YELLOW := \033[0;33m
RESET := \033[0m

# Directories
OBJS_DIR := objs/

# Source file names
SRCS := main.c \
		utils.c \
		ft_atol.c \
		init_data.c \
		init_mutex.c \
		simulate.c \
		eat.c \
		monitor.c \
		print.c \
		getters_1.c \
		getters_2.c \
		setters.c \
		safe_funcs.c \
		debug_utils.c

# Object files with paths
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@cc -o $(NAME) $(OBJS)
	@echo "$(BRIGHT_YELLOW)Built $(NAME)$(RESET)"

debug: .debug

.debug: $(OBJS_DIR) $(OBJS)
	@cc -o philo_debug $(OBJS) $(DEBUG)
	@echo "$(BRIGHT_YELLOW)Built philo_debug$(RESET)"
	@touch .debug

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@echo "$(YELLOW)Built object directory$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Built $@$(RESET)"

clean:
	@rm -fr $(OBJS_DIR) .debug
	@echo "$(YELLOW)Removed $(OBJS_DIR) directory and object files$(RESET)"
 
fclean: clean
	@rm -f $(NAME) philo_debug
	@echo "$(YELLOW)Removed executable(s)$(RESET)"

re: fclean all