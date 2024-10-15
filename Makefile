CC = cc
FLAGS =  # -Wall -Wextra -Werror -fsanitize=address -g 
RFLAGS = -lreadline -lncurses
NAME = minishell
SRC = ./parsing/check_errors.c ./parsing/init_shell.c ./parsing/minishell.c ./parsing/tokenize.c ./parsing/helpers.c ./parsing/expand.c ./parsing/expand_home.c ./parsing/deep_tokenize.c ./parsing/libft_functions.c ./parsing/parse.c ./parsing/open_files.c ./parsing/allocate_free.c\
./execution/pipes.c ./execution/builtins.c  ./execution/path_check.c ./execution/tools.c ./execution/pipe_tools.c ./execution/echo_check.c ./execution/split.c ./execution/readline.c ./execution/stack_init.c ./execution/heredoc.c ./execution/stack_tools.c ./execution/enogh.c ./execution/export.c ./execution/export_help.c ./execution/unset.c
OBJ = $(SRC:.c=.o)

all         : $(NAME)

$(NAME)     : $(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(RFLAGS)

%.o			:	%.c minishell.h
			$(CC) $(FLAGS)  -c $< -o $@

clean       :
			@rm -f $(OBJ)

fclean      : clean
			@rm -f $(NAME)

re          : fclean all

.PHONY      : clean
