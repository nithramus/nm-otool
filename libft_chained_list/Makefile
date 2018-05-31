# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: bandre <bandre@student.42.fr>			  +#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2016/12/07 16:17:12 by bandre			#+#	#+#			  #
#	Updated: 2018/04/12 19:01:27 by bandre		   ###   ########.fr		#
#																			  #
# **************************************************************************** #

NAME = libft_chained_list.a

SRC_PATH = libft_chained_list_src

OBJ_PATH = libft_chained_list_obj

SRC = add_back_maillon.o\
 	  add_front_maillon.o\
	  create_maillon.o\
	  delete_chained_list.o\
	  ft_puterror.o\
	  function_on_chained_list.o\
	  remove_maillon.o\
	  swap_maillon.o\

CC = gcc

FLAG = -Wall -Wextra -Werror -O -g

SRC_O = $(addprefix $(OBJ_PATH)/,$(SRC))

all: $(NAME)

$(NAME): $(SRC_O)
	ar rc $(NAME) $(SRC_O)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) -c $< -o $@ $(FLAG)

clean:
	rm -f $(addprefix $(OBJ_PATH)/,$(SRC))

fclean: clean
	rm -f $(NAME)

re: fclean all

flag: $(SRC)
	$(CC) $(NAME) $(LIB) -o $(NAME)

do: all
	./malloc

.PHONY: $(NAME) all %.o clean fclean re flag EXEC
