# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/27 14:53:03 by mkristie          #+#    #+#              #
#    Updated: 2020/10/14 23:41:09 by lhelper          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -O2 -g#-Wall -Wextra -Werror

INCLUDES = -Iincludes/ -Iget_next_line/ -Ilibft/

LIBFT = -L./libft -lft
LIBFT_DIR = ./libft

GNL = get_next_line.c \
		get_next_line_utils.c \

PARSE_SRC = parse.c \
			split_by_char.c \
			split_by_commands.c 
			
			
UTILS_SRC = ft_alloc_check.c \
			ft_bell.c \
			compare_kv.c \
			get_envar.c \
			count_2d_lines.c \
			exit_error_message.c \
			ft_trim_2d.c \
			print_2d_array.c 

ENGINE_SRC = engine_start.c \

BUILTIN = builtin.c\
			other_cmd.c\

SRC = $(addprefix engine/, $(ENGINE_SRC))
SRC += $(addprefix parser/, $(PARSE_SRC))
SRC += $(addprefix utils/, $(UTILS_SRC))
SRC += $(addprefix get_next_line/, $(GNL))
SRC += $(addprefix builtin/, $(BUILTIN))

OBJ = $(SRC:.c=.o)

%.o : %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

sh: all
	rm -f $(OBJ)
	./minishell

resh: re
	rm -f $(OBJ)
	./minishell

re: fclean all

.PHONY: all clean fclean sh resh re