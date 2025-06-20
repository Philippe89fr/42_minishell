# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 15:05:53 by lbenatar          #+#    #+#              #
#    Updated: 2025/06/20 18:00:59 by prambaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET  = $(shell printf "\33[0m")
GREEN  = $(shell printf "\33[32m")

SRC	= ./src/parsing/fill_lst_token.c \
	./src/parsing/lst_token_take_cmd.c \
	./src/parsing/files_management.c \
	./src/parsing/def_token_type.c \
	./src/parsing/lst_token_utils.c \
	./src/parsing/lst_cmd_utils.c \
	./src/parsing/fill_lst_cmd.c \
	./src/parsing/get_path.c \
	./src/parsing/init_pipex_struc.c \
	./src/parsing/init_pipex_struc2.c \
	./src/parsing/fill_lst_cmd_files.c \
	./src/parsing/fill_lst_cmd_utils.c \
	./src/parsing/access_check.c \
	./src/pipex/pipex.c \
	./src/pipex/get_next_line_utils.c \
	./src/pipex/get_next_line.c \
	./src/pipex/get_here_doc_input.c \
	./src/pipex/fill_lst_cmd_here_doc.c \
	./src/pipex/built_in_fonctions.c \
	./src/pipex/ft_echo.c \
	./src/pipex/ft_export.c \
	./src/pipex/ft_export_utils.c \
	./src/pipex/ft_export_env.c \
	./src/pipex/ft_unset.c \
	./src/pipex/ft_cd.c \
	./src/pipex/ft_cd_utils.c \
	./src/pipex/open_files.c \
	./src/pipex/str_join.c \
	./src/pipex/family_life_catho.c \
	./src/pipex/family_life_fille_unique.c \
	./src/error_and_free/liberator_god.c \
	./src/error_and_free/error_management.c \
	./src/error_and_free/error_management2.c \
	./src/error_and_free/error_management3.c \
	./src/error_and_free/mini_liberators.c \
	./src/signaux.c \
	./src/main_bis.c \
	./src/parsing_brackets/double_quote_management2.c \
	./src/parsing_brackets/double_quote_management.c \
	./src/parsing_brackets/parsing_dollars_without_brackets2.c \
	./src/parsing_brackets/utils.c \
	./src/parsing_brackets/double_quote_management3.c \
	./src/parsing_brackets/parsing_brackets_management.c \
	./src/parsing_brackets/parsing_dollars_without_brackets.c \
	./src/parsing_brackets/replace_status.c \
	./src/parsing_brackets/replace_status2.c \
	./src/parsing_utils/pipe_management.c \
	./src/parsing_utils/one_pipe_management.c \
	./src/parsing_utils/one_pipe_management2.c 

LIBFT	= ./libft/libft.a

CFLAGS	= -Wall -Wextra -Werror -g

NAME = minishell.a

NAME_EXE = minishell

OBJ	= $(SRC:.c=.o)

.c.o	:
		cc ${CFLAGS} -c $< -o ${<:.c=.o}

all : ${NAME} libft

${NAME} : $(LIBFT) ${OBJ}
		@cp $(LIBFT) $(NAME)
		@ar rcs ${NAME} ${OBJ}
		cc ${CFLAGS} -lreadline ./src/main.c -L. ${NAME} -o ${NAME_EXE}
		@echo "$(GREEN)$(NAME_EXE) successfully created!$(RESET)"

$(LIBFT):
			@make --silent -C ./libft
			@echo "$(GREEN)LIBFT successfully compiled!$(RESET)"

clean :
		@rm -f ${OBJ}
		@rm -rf ./src/*.o
		@rm -rf ./src_bonus/*.o
		@make --silent -C ./libft clean
		@echo "$(GREEN)Successfully cleaned!$(RESET)"

fclean : clean
		@rm -f ${NAME}
		@rm -f ${NAME_EXE}
		@make --silent -C ./libft fclean
		@echo "$(GREEN)Successfully fcleaned!$(RESET)"

re : fclean all

.PHONY:	all clean fclean re libft
