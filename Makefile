# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/27 14:53:03 by mkristie          #+#    #+#              #
#    Updated: 2020/10/30 20:24:02 by lhelper          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -O2 -g#-Wall -Wextra -Werror

INCLUDES = -Iincludes/ -Ilibft/

INC = builtin_mshell.h \
			engine_mshell.h \
			get_next_line.h \
			minishell.h \
			parse_mshell.h \
			structs_mshell.h \
			utils_nshell.h

HEADERS = $(addprefix includes/, $(INC))
HEADERS += libft/libft.h

LIBFT = -L./libft -lft
LIBFT_DIR = ./libft

GNL = get_next_line.c \
		get_next_line_utils.c \
		get_next_line_utils_2.c \

PARSER_SRC = alloc_pipe_list.c \
			alloc_token_list.c \
			check_syntax.c \
			check_syntax2.c \
			check_tokens_syntax.c \
			get_sh_list.c \
			handle_dollar.c \
			open_quotes.c \
			open_quotes2.c \
			open_quotes_utils.c \
            parse.c \
            parse_env.c \
			split_by_char.c \
			split_by_commands.c \
			split_by_commands_utils.c \

UTILS_SRC = alloc_and_check.c \
			alloc_and_check2.c \
			check_numeric.c \
			chr_join.c \
			compare_kv.c \
            count_2d_lines.c \
            dlst_pipe.c \
            dlst_sh.c \
            exit_error_message.c \
            free_all_lists.c \
            free_and_null.c \
            ft_alloc_check.c \
			ft_atoll.c \
			ft_atoull.c \
			ft_lstnew_kv.c \
			ft_trim_2d.c \
			get_envar.c \
			is_str.c \
			print_2d_array.c \
			print_error.c \
			print_everything.c \
			print_token.c \
			reset_newlines.c \
			set_heads.c \
			set_states.c \
			signal.c \
			states.c \
			states_first_lvl.c \
			status.c \
			token.c \

ENGINE_SRC = engine_start.c \
				exec.c \
				process.c \

BUILTIN = 	builtin_utils.c \
			other_cmd.c\
			ft_cd.c \
            ft_exit.c \
			ft_env.c \
			ft_echo.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \

SRC = $(addprefix engine/, $(ENGINE_SRC))
SRC += $(addprefix parser/, $(PARSER_SRC))
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
	rm -f get_next_line/*.d
	rm -f parser/*.d
	rm -f utils/*.d
	rm -f builtin/*.d
	rm -f engine/*.d

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

sh: all
	#rm -f libft/libft.a
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)
	#./minishell

resh: re
	rm -f $(OBJ)
	./minishell

re: fclean all

.PHONY: all clean fclean sh resh re