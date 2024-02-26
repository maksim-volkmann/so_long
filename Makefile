# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 16:31:03 by mvolkman          #+#    #+#              #
#    Updated: 2024/02/26 13:16:13 by mvolkman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files for so_long
SRC = so_long.c
    #   helper.c \
    #   movements.c \
    #   move_helper.c \
    #   conversions.c \
    #   window.c \
    #   info_display.c \
    #   textures.c \
    #   initializers.c \
    #   map_parser.c \
    #   map_helper.c \
    #   map_checks.c

# Object files
OBJ = $(SRC:.c=.o)

# Library directories and flags for libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Library directories and flags for libmlx42
LIBMLX42_DIR = ./MLX42
LIBMLX42 = $(LIBMLX42_DIR)/build/libmlx42.a

# Include directories for libft and libmlx42
INCLUDES = -I$(LIBFT_DIR)/include \
           -I$(LIBMLX42_DIR)/include \
           -I./include

# Output executable name
NAME = so_long

# Colors used for terminal output.
GREEN = \033[0;32m
BLUE = \033[0;34m
ORANGE = \033[38;5;214m
RED = \033[0;31m
YELLOW = \033[0;33m
WHITE = \033[0;37m

# Rules
all: $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(WHITE)"

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX42)
	@echo "$(BLUE)Building $(NAME)$(WHITE)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LIBMLX42) -Iinclude -lglfw
	@echo "$(GREEN)$(NAME) created successfully!$(WHITE)"

$(LIBFT):
	@echo "$(BLUE)Building $(LIBFT)$(WHITE)"
	make -C $(LIBFT_DIR)

$(LIBMLX42):
	@echo "$(BLUE)Building $(LIBMLX42)$(WHITE)"
	cd $(LIBMLX42_DIR) && cmake -B build && cmake --build build -j4

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "$(GREEN)Compiled $< successfully!$(WHITE)"

clean:
	@echo "$(RED)Cleaning object files...$(WHITE)"
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning binaries...$(WHITE)"
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
