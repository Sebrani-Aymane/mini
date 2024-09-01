#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_token
{
    char *content;
    int need_expand;
} t_token;

typedef struct s_list
{
    char **env_var;
    t_token **tokens;
} t_list;

typedef struct s_node
{
    char *content;
    int type;
    struct s_node *next;
} t_node;

typedef struct s_line
{
    t_node *tokens;
    int redic;
    struct s_line *next;
} t_line;

// argv
// argc
// fd_in
// fd_out
// rede
// 
void display_prompt(t_list shell);
char **copy_env(char **env);
int check_unclosed_quotes(char *input);
t_token **into_tokens(char *input);
int check_prohibited_char(char *input);
int is_redirection_op(char c);
int skip_spaces(char *input, int i);
int validate_redirection_syntax(char *input);
int tokens_number(char *input);
int more_than_op(char *input);
void check_token_dollar(t_token **token);
int ft_strlen(char *str);
void expand(t_token **tokens, t_list shell);
char *get_value(char **env_vars, int len, char *name);
char *replace_value(char *token, char *value, char *name);
void expand_home(t_token **tokens, t_list shell);
int ft_strchr(char *s, int c);
t_node *search_token(t_token **tokens);
t_line *tokens_to_lines(t_node *tokens);

//libft
t_node	*ft_lstnew(char *content);
void	ft_lstadd_back(t_node **lst, t_node *neew);
#endif