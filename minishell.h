/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:20:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/08 16:07:50 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#define GET 1
#define SET 2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>

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
    int fd_in;
	int fd_out;
    struct s_line *next;
} t_line;


typedef struct env_vars_t{
	char *vars;
	char *var_value;
	char **env;
	struct env_vars_t *next;
}  env_vars;



typedef struct shell{
	char **argv;
	char **env;
	int fd_in;
	int fd_out;
}t_shell;

void	clear_strss(char **strs, int n);
int execute_the_thing(t_line *final,char **env,env_vars *list);
void 	export_with_plus(char *av,env_vars *env);
int ft_strcmp(char *str,char *str1);
env_vars *execute_builtins(char* builtin, t_line *final, env_vars *list,char **env);
void valid_to_add(env_vars *env,char *str);
char *get_till(char *str, char c);
void piipe(env_vars *list,char **av,char **env);
void exitt(env_vars *env, t_line *final);
void first_in(char *str,env_vars *env);
int	ft_isalpha(int c);
void unset(env_vars *env, t_line *final);
void valid_to_add_plus(env_vars *env,char *str);
env_vars *export_if_plus(char **input,env_vars *list);
void add_to_list(env_vars **head,env_vars *newe);
int	ft_isalnum(int c);
int check_key(char *str);
void echoo(t_line *final);
void pwdd(int a);
env_vars *envpp(env_vars *list);
void export_all(env_vars *env, t_line *final);
int	ft_strlen(char *str);
void export_it(env_vars *env, char *str);
char	*get_path(char **envp,char *str);
int	count_words(char *str, char c);
char	*return_word(char *str, char c);
char **joker(env_vars *list);
void	ft_lstadd_front(env_vars **lst, env_vars *next);
char *ret(char *in);
void excutefilepath(t_line *final,env_vars *list,char **env);
int	ft_listsize(t_line *lst);
env_vars *append_to_list(env_vars *list,char **temp);
char	**split(char *str, char sep);
env_vars *exportt_plus(char **av,env_vars *list);
void	clear_strss(char **strs, int n);
env_vars *list_init(char **variables);
env_vars *exportt_plus(char **av,env_vars *list);
void free_double(char **str);
void	copy_it(char *dest, char *src);
char	*str_joiner(char *s1, char *s2);
int already_var(env_vars *list, char *str);

char** split_by_first_occurrence(char *str, char delimiter);
int already_vars(env_vars *list, char *str);
env_vars *update_value(env_vars **list,char **str);
char *ret(char *in);
int	chdirr(char **env, t_line *final);
int handle_pipe(t_line *final,char **env,env_vars *list);
int check_eccho(t_node *final);
char *get_path_from_list(env_vars *list);
int exit_status(int type, int value);
//////////////////*PARSING*//////////////////////////


void display_prompt(t_list shell, char **env);
char **copy_env(char **env);
int check_unclosed_quotes(char *input);
t_token **into_tokens(char *input);
int check_prohibited_char(char *input);
int is_redirection_op(char c);
int skip_spaces(char *input, int i);
void	ft_lstadd_back(t_node **lst, t_node *neew);
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
t_node  *ft_lstnew(char *content);
int	ft_lstsize(t_node *lst);
int pipe_syntax(char *input);
void open_files(t_line *lines);
int	ft_atoi(const char *str);
int dollar_inside_quotes_alone(char *content);
#endif
