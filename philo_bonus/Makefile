# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 12:08:01 by ixu               #+#    #+#              #
#    Updated: 2024/04/16 15:17:24 by ixu              ###   ########.fr        #
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
RESET := \033[0m

# Directories
OBJS_DIR := objs_bonus/

# Source file names
SRCS := $(addsuffix _bonus.c, main utils ft_atol init simulate \
			eat monitor print getters setters safe_funcs)

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

bonus: .bonus

.bonus: $(OBJS_DIR) $(OBJS)
	@cc -o $(NAME) $(OBJS)
	@echo "$(BRIGHT_YELLOW)Built $(NAME)$(RESET)"
	@touch .bonus

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@echo "$(YELLOW)Built object directory$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Built $@$(RESET)"

clean:
	@rm -fr $(OBJS_DIR) .bonus .debug
	@echo "$(YELLOW)Removed $(OBJS_DIR) directory and object files$(RESET)"
 
fclean: clean
	@rm -f $(NAME) philo_debug
	@echo "$(YELLOW)Removed executable(s)$(RESET)"

re: fclean all