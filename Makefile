# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 18:25:12 by jo-tan            #+#    #+#              #
#    Updated: 2024/01/04 15:23:43 by jo-tan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# Sources
S_FILES		= src/main.c \
				src/init_utils.c \
				src/init_envp.c \
				src/check_valid_input.c \
				src/check_quote_pair.c \
				src/read_cmd.c \
				src/parsing_utils.c \
				src/parsing_token_type.c \
				src/parsing.c \
				src/parsing_quote_utils.c \
				src/parsing_expansion_utils1.c \
				src/parsing_expansion_utils2.c \
				src/check_print.c \
				src/token_list.c \
				src/cmd_list.c \
				src/cmd_list2.c \
				src/token_to_cmd.c \
				src/buildin_cd.c \
				src/buildin_echo.c \
				src/buildin_env.c \
				src/buildin_export.c \
				src/buildin_pwd.c \
				src/buildin_unset.c \
				src/buildin_exit.c \
				src/buildin.c \
				src/execution.c \
				src/exec_utils.c \
				src/exec_args.c \
				src/exec_path.c \
				src/exec_pipeline.c \
				src/exec_set_io.c \
				src/exec_set_io_utils.c \
				src/hd_expansion.c \
				src/env_utils.c \
				src/env_utils2.c \
				src/signal.c \
				src/check_syntax.c \
				src/utils_find_char.c
S_DIR		= src

LIBFT		= libft/libft.a
LIBFT_DIR	= libft

# Objects
O_DIR		= obj

O_FILES		= $(patsubst $(S_DIR)/%.c,$(O_DIR)/%.o,$(S_FILES))
D_FILES		= $(patsubst $(S_DIR)/%.c,$(O_DIR)/%.d,$(S_FILES))

# Compilation
CC			= cc
CF			= -Wall -Wextra -Werror #-MMD -MP
INC			= -I inc/ -I $(LIBFT_DIR)

# Cleaning
RM			= rm -rf

all:		$(LIBFT) $(NAME)

$(NAME):	$(O_FILES)
	@$(CC) -fsanitize=address -g -o $(NAME) $(O_FILES) -L $(LIBFT_DIR) -lreadline -lft $(INC)
	@echo " [ ok ] | minishell is ready!"

-include $(D_FILES)

$(O_DIR)/%.o: $(S_DIR)/%.c
	@echo "Compiling $<"
	@mkdir -p $(O_DIR) $(D_DIR)
	@$(CC) $(CF) $(INC) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "libft is ready."

clean:
	@$(RM) $(O_DIR)
	@make --no-print-directory -C libft fclean
	@echo "Objects and dependend files removed."

fclean:	clean
	@$(RM) $(NAME)
	@make --no-print-directory -C libft fclean
	@echo "Binary files removed."

re:		fclean all

.PHONY:	all clean fclean re