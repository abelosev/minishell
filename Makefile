NAME 	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP -g3 -I. -MF $(DPSDIR)/$*.d #-fsanitize=adress
CLIBS	= -lreadline
LIBFT	= libft/libft.a
LIBFT_DIR	= libft
SRCDIRP	= ./src/parsing
SRCDIRE	= ./src/exec
OBJDIR	= ./obj
DPSDIR	= ./deps

SRCP 	= 	$(wildcard $(SRCDIRP)/*.c)
SRCE	=	$(wildcard $(SRCDIRE)/*.c)

OBJ 	= 	$(patsubst $(SRCDIRP)/%.c, $(OBJDIR)/%.o, $(SRCP)) \
			$(patsubst $(SRCDIRE)/%.c, $(OBJDIR)/%.o, $(SRCE))

$(NAME): $(OBJDIR) $(OBJ) $(DPSDIR) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) $(CLIBS) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIRP)/%.c | $(DPSDIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIRE)/%.c | $(DPSDIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(DPSDIR)/%.d: ;

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DPSDIR):
	mkdir -p $(DPSDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJDIR) $(DPSDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

valgrind: all
		valgrind --suppressions=$(PWD)/ignore_readline --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
    	./$(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(wildcard $(DPSDIR)/*.d)