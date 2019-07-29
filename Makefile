#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashypilo <ashypilo@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 15:44:58 by ashypilo          #+#    #+#              #
#    Updated: 2019/07/24 18:58:06 by ashypilo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= lem-in
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
SRC			=  main.c start_ants.c search_the_way.c ft_lem_in.c list_rooms.c\
swap_roads.c superposition_bhandary.c search_link.c room_busy.c\
getting_connections.c start_ants_on_the_roads.c coord_minus.c coord_plus.c\
search_roads_bhandary.c malloc_arrays.c sorting_roads.c swap_dubl_roads.c\
write_new_road.c search_room_in_line.c best_road.c
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC_DIR		= ./src/
OBJ_DIR		= ./obj/
SRC_DIR		= ./src/
FT			= ./libft/
FT_LIB		= $(addprefix $(FT), libft.a)
FT_INC		= -I $(FT)
FT_LNK		= -L $(FT) -lft

all: obj $(FT_LIB) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(FT_LIB):
	@make -C $(FT)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<
	@echo "(+) $@"

$(NAME):$(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(FT_LNK) -I $(INC_DIR)\
	-lm -o $(NAME)
	@echo "$(NAME) ready to win!"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(FT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(FT) fclean

re: fclean all
.PHONY: all re clean fclean