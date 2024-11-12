CC = cc
FLAGS =   -Wall -Wextra -Werror # -g -fsanitize=address
NAME = minishell
SRC = ./parsing/check_errors1.c ./parsing/check_errors2.c ./parsing/init_shell.c ./parsing/minishell.c ./parsing/tokenize.c ./parsing/helpers1.c ./parsing/helpers2.c ./parsing/helpers3.c ./parsing/expand1.c ./parsing/expand2.c ./parsing/deep_tokenize.c ./parsing/libft_functions1.c ./parsing/libft_functions2.c ./parsing/parse.c ./parsing/open_files.c ./parsing/allocate_free.c ./parsing/analyze_input1.c ./parsing/analyze_input2.c ./parsing/analyze_input3.c ./parsing/remove_quotes.c\
./execution/pipes.c ./execution/pipes2_tools.c ./execution/signals.c ./execution/builtins_helpers.c ./execution/heredoc_helpers.c ./execution/builtins.c ./execution/helpers_exec.c ./execution/execution.c ./execution/path_check.c ./execution/tools.c ./execution/pipe_tools.c ./execution/echo_check.c ./execution/split.c ./execution/readline.c ./execution/stack_init.c ./execution/heredoc.c ./execution/stack_tools.c ./execution/enogh.c ./execution/export.c ./execution/export_help.c ./execution/unset.c
OBJ = $(SRC:.c=.o)

all         : $(NAME)

$(NAME)     : $(OBJ)
			$(CC) $(FLAGS) -lreadline -o $(NAME) $(OBJ) $(RFLAGS)

%.o			:	%.c minishell.h
			$(CC) $(FLAGS)  -c $< -o $@

clean       :
			@rm -f $(OBJ)

fclean      : clean
			@rm -f $(NAME)

re          : fclean all

.PHONY      : clean
