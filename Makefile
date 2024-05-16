NAME 	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP -g3 -I. -MF $(DPSDIR)/$*.d #-fsanitize=adress
CLIBS	= -lreadline

SRCDIRP	= ./src/src_pars
SRCDIRE	= ./src/src_exec
OBJDIR	= ./obj
DPSDIR	= ./deps

SRCP 	= 	$(wildcard $(SRCDIRP)/*.c)
SRCE	=	$(wildcard $(SRCDIRE)/*.c)

OBJ 	= 	$(patsubst $(SRCDIRP)/%.c, $(OBJDIR)/%.o, $(SRCP)) \
			$(patsubst $(SRCDIRE)/%.c, $(OBJDIR)/%.o, $(SRCE))

$(NAME): $(OBJDIR) $(OBJ) $(DPSDIR)
		$(CC) $(CFLAGS) $(OBJ) $(CLIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIRP)/%.c | $(DPSDIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIRE)/%.c | $(DPSDIR)
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
		valgrind --suppressions=$(PWD)/ignore_readline --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
    	./minishell

re: fclean all

.PHONY: all clean fclean re

-include $(wildcard $(DPSDIR)/*.d)