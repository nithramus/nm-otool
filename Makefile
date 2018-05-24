# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bandre <bandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/07 16:17:12 by bandre            #+#    #+#              #
#    Updated: 2018/05/24 18:43:34 by bandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm

SRC_PATH = nm_src

OBJ_PATH = nm_obj

SRC = nm.o\
	  parse_arg.o\
	  reverse.o\
	  create_symbol_list.o\
	  parse_header.o\
	  quit_clean.o\
	  get_sections.o\
	  show_symbols.o\
	  order_symbol.o\
	  get_type.o\
  	  archive.o\
	  order_files.o\
	  fat.o\


CC = gcc -g

FLAG = -Wall -Wextra -O -Werror

LIB = libft/libftprintf.a libft_chained_list/libft_chained_list.a

SRC_O = $(addprefix $(OBJ_PATH)/,$(SRC))

all: EXEC $(NAME)

$(NAME): $(SRC_O)
	$(CC) $(FLAG) -o $(NAME) $(SRC_O) $(LIB)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) -c $< -o $@ $(FLAG)

EXEC:
	make -C libft/
	make -C libft_chained_list/

clean:
	rm -f $(addprefix $(OBJ_PATH)/,$(SRC))
	make -C libft clean
	make -C libft_chained_list clean
	

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C libft_chained_list fclean


re: fclean all

flag: $(SRC)
	$(CC) $(NAME) $(LIB) -o $(NAME)

do: all
	./malloc

.PHONY: $(NAME) all %.o clean fclean re flag EXEC
