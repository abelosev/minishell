NAME    = minishell

CC      = cc
CF  	= -Wall -Wextra -Werror -MMD -MP $(DPSDIR)/$*.d #-fsanitize=address
INC		= -I inc/ -I $(LIBFT_DIR)

SRC_F	= src/exec/exec_builtin.c \
			src/exec/exec_outils.c \
			src/exec/ft_cd.c \
			src/exec/ft_echo.c \
			src/exec/ft_env.c \
			src/exec/ft_exit.c \
			src/exec/ft_export.c \
			src/exec/ft_pwd.c \
			src/exec/ft_unset.c \
			src/exec/main.c \
			src/pars/cmd_check_outils.c \
			src/pars/cmd_check.c \
			src/pars/envp_get_list.c \
			src/pars/envp_get_tab.c \
			src/pars/expand_tokenizer.c \
			src/pars/expand.c \
			src/pars/ft_split1.c \
			src/pars/get_files_outils.c \
			src/pars/get_files.c \
			src/pars/group_list.c \
			src/pars/group_outils.c \
			src/pars/outils_envp.c \
			src/pars/outils_expand.c \
			src/pars/outils_free.c \
			src/pars/outils_print.c \
			src/pars/parser_outils.c \
			src/pars/parser.c \
			src/pars/quotes_expand.c \
			src/pars/quotes_ok.c \
			src/pars/quotes_outils.c \
			src/pars/quotes_remove.c \
			src/pars/quotes_spaces.c \
			src/pars/syntax_pb.c \
			src/pars/token_list.c \

SRCDIR 	= src
OBJDIR  = obj
DPSDIR  = deps

LIBFT   = libft/libft.a
LIBFT_DIR = libft

OBJ_F   = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_F))
DPS_F		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d,$(SRC_F))

all: $(LIBFT) $(NAME)

$(NAME):	$(SRC_F)
	@$(CC) -fsanitize=address -g -o $(NAME) $(SRC_F) -L $(LIBFT_DIR) -lreadline -lft $(INC)
	@echo "minishell is up to date"

-include $(DPS_F)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) $(DPSDIR)
	@$(CC) $(CF) $(INC) -c $< -o $@

$(LIBFT):
	@make  --no-print-directory -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR) $(DPSDIR)
	@make --no-print-directory -C libft fclean

fclean: clean
	rm -rf $(NAME)
	@make --no-print-directory -C libft fclean

valgrind: all
	valgrind --suppressions=$(PWD)/ignore_readline --trace-children=yes \
	--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
	./$(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind

-include $(wildcard $(DPSDIR)/*.d)
