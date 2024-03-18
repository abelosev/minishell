NAME 	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP -g3 -I. -MF $(DPSDIR)/$*.d #-fsanitize=adress
CLIBS	= -lreadline

SRCDIR	= ./src
OBJDIR	= ./obj
DPSDIR	= ./deps

SRC 	= $(wildcard $(SRCDIR)/*.c)
OBJ 	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))


$(NAME): $(OBJDIR) $(OBJ) $(DPSDIR)
		$(CC) $(CFLAGS) $(CLIBS) $(OBJ) -o $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(DPSDIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(DPSDIR)/%.d: ;

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DPSDIR):
	mkdir -p $(DPSDIR)

all: $(NAME)

clean:
	rm -rf $(OBJDIR) $(DPSDIR)

fclean: clean
	rm -rf $(NAME)

valgrind: all
		valgrind -q --suppressions=$(PWD)/ignore_readline --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
    	./minishell

re: fclean all

.PHONY: all clean fclean re

-include $(wildcard $(DPSDIR)/*.d)