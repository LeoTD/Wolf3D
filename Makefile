# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 19:18:37 by ltanenba          #+#    #+#              #
#    Updated: 2018/05/06 19:15:22 by ltanenba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= wolf3d

INCLUDES	= libft/includes/libft.h \
			  includes/wolf3d.h

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra 
INC_FLAGS	= -I libft/includes -I includes -I minilibx_macos
MLX_FLAGS	= -framework OpenGL -framework AppKit

# Cosmetics Section:

OK_COLOR	= \033[38;5;105;1m
OBJ_COLOR	= \033[38;5;208m
COM_COLOR	= \033[38;5;200m
LIB_COLOR	= \033[1;32m
NO_COLOR    = \033[m

COM_STRING	= "Compiling:"

# End Cosmetics.

LIBFT		= libft/libft.a
MINI_LIB	= minilibx_macos/libmlx.a

LIBS		= $(LIBFT) $(MINI_LIB)

WOLF_SRC	= wolf3d.c \
			  drawing_functions.c \
			  image_functions.c \
			  map.c \
			  raycasting.c \
			  events.c

SRC			= $(addprefix src/, $(WOLF_SRC))
OBJ			= $(addprefix obj/, $(WOLF_SRC:.c=.o))

# ---------------------------------------------------------------------------- #

all: $(NAME)

$(NAME): $(LIBFT) $(MINI_LIB) $(SRC)
	@printf "%b" "$(LIB_COLOR)Compiling: $(OK_COLOR)$@\n$(NO_COLOR)"
	@$(CC) -g $(CFLAGS) $(INC_FLAGS) $(MLX_FLAGS) -o $(NAME) $(SRC) $(LIBS)

$(LIBFT):
	@make -C libft

$(MINI_LIB):
	@printf "%b" "$(LIB_COLOR)Compiling: $(OK_COLOR)$(MINI_LIB)\n$(NO_COLOR)"
	@make -C minilibx_macos

clean:
	@printf "Cleaning up $(NAME)...\n"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@make -C minilibx_macos clean

obj:
	@printf "Creating obj/ directory...\n"
	@mkdir obj/

obj/%.o: $(SRC) | obj
	@printf "%b" "$(COM_COLOR)  $(COM_STRING) $(OBJ_COLOR)$@\n$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

norm:
	@printf "%b" "$(LIB_COLOR)Checking Norm...\n$(NO_COLOR)"
	@norminette $(SRC) $(INCLUDES)

test: $(NAME)
	@printf "%b" "$(OK_COLOR)Building...\n$(NO_COLOR)"
	@printf "%b" "$(OK_COLOR)Running...\n$(NO_COLOR)"
	@./$(NAME)

.PHONY: clean fclean all re
