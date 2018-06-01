# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bandre <bandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/07 16:17:12 by bandre            #+#    #+#              #
#    Updated: 2018/06/01 14:29:21 by bandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

OTOOL = ft_otool

NM_SRC_PATH = nm_src

OTOOL_SRC_PATH = otool_src

NM_OBJ_PATH = nm_obj

OTOOL_OBJ_PATH = otool_obj

NM_SRC = nm.o\
	  parse_arg.o\
	  reverse.o\
	  create_symbol_list.o\
	  parse_header.o\
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

NM_SRC_O = $(addprefix $(NM_OBJ_PATH)/,$(NM_SRC))

OTOOL_SRC_O = $(addprefix $(OTOOL_OBJ_PATH)/,$(NM_SRC))

all: EXEC $(NAME) $(OTOOL)

$(NAME): $(NM_SRC_O) 
	$(CC) $(FLAG) -o $(NAME) $(NM_SRC_O) $(LIB) -Inm_src

$(NM_OBJ_PATH)/%.o:$(NM_SRC_PATH)/%.c
	$(CC) -c $< -o $@ $(FLAG)

$(OTOOL_OBJ_PATH)/%.o:$(OTOOL_SRC_PATH)/%.c
	$(CC) -c $< -o $@ $(FLAG)

$(OTOOL): $(OTOOL_SRC_O)
	$(CC) $(FLAG) -o $(OTOOL) $(OTOOL_SRC_O) $(LIB) -Inm_src
EXEC:
	make -C libft/
	make -C libft_chained_list/

clean:
	rm -f $(addprefix $(NM_OBJ_PATH)/,$(NM_SRC))
	rm -f $(addprefix $(OTOOL_OBJ_PATH)/,$(NM_SRC))
	make -C libft clean
	make -C libft_chained_list clean
	

fclean: clean
	rm -f $(NAME)
	rm -f $(OTOOL)
	make -C libft fclean
	make -C libft_chained_list fclean


re: fclean all

flag: $(NM_SRC)
	$(CC) $(NAME) $(LIB) -o $(NAME)

do: all
	./malloc

.PHONY: $(NAME) all %.o clean fclean re flag EXEC
