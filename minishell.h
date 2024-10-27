/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:20:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/10/26 18:40:50 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#define SET 1
#define GET 2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>

int glob_var;
typedef struct s_token
{
    char *content;
    int need_expand;
    int divide_space;
} t_token;

typedef struct s_list
{
    t_token **tokens;
    char **env;
    int shlvl;
} t_list;

typedef struct s_heredoc {
    int fd[2];
    char *delimiter;
    int expand_vars;
} t_heredoc;


typedef struct s_node
{
    char *content;
    int type;
    int delimeter_inside_quotes;
    struct s_node *next;
} t_node;

typedef struct s_line
{
    t_node *tokens;
    int fd_in;
	int fd_out;
    int default_in;
    int default_out;
    struct s_line *next;
} t_line;


typedef struct env_vars_t{
	char *vars;
	char *var_value;
	char **env;
	struct env_vars_t *next;
    int exit;
}  env_vars;



typedef struct shell{
	char **argv;
	char **env;
	int fd_in;
	int fd_out;
}t_shell;

typedef struct s_coll{
    void *ptr;
    struct s_coll *next;
} t_coll;

void	clear_strss(char **strs, int n);
int execute_the_thing(t_line *final,char **env,env_vars *list);
int 	export_with_plus(char *av,env_vars *env);
int ft_strcmp(char *str,char *str1);
int execute_blts(char* builtin, t_line *final, env_vars *list, char **env);
int valid_to_add(env_vars *env,char *str);
char *get_till(char *str, char c);
void exitt(env_vars *env, t_line *final);
int first_in(char *str,env_vars *env);
int	ft_isalpha(int c);
int unset(env_vars *env, t_line *final);
int valid_to_add_plus(env_vars *env,char *str);
void add_to_list(env_vars **head,env_vars *newe);
int ft_isalnum(int c);
int check_key(char *str);
void echoo(t_line *final);
char* pwdd(env_vars *list);
int	ft_strncmp(char *s1, char *s2, int	n);
env_vars *envpp(env_vars *list);
int export_all(env_vars *env, t_line *final);
int ft_strlenn(char *str);
int export_it(env_vars *env, char *str);
char	*get_path(char **envp,char *str);
int	ft_isdigit(int c);
int	count_words(char *str, char c);
char	*return_word(char *str, char c);
int  excutefilepath(t_line *final,env_vars *list,char **env);
int	ft_listsize(t_line *lst);
env_vars *append_to_list(env_vars *list,char **temp);
char	**split(char *str, char sep);
int handle_single_pipe(t_line *final, char **env, env_vars *list, int pipes_count, int i);
int	is_space(char *str);
void handle_child_fds(t_line *final);
env_vars *list_init(char **variables);
void free_double(char **str);
void	copy_it(char *dest, char *src);
int handle_parent_process(int fd[2], int pipes_count);
char	*str_joiner(char *s1, char *s2);
int check_builtin(t_line *final, env_vars *list,char **env);
int handle_child_processs(t_line *final, char **env, env_vars *list, int fd[2], int pipes_count, int i);
int get_nodee(env_vars *list);
int	chdirr(char **env, t_line *final,env_vars *list);
int handle_pipe(t_line *final,char **env,env_vars *list);
int check_eccho(t_node *final);
char *get_path_from_list(env_vars *list,char *str);
int exit_status(int type, int value);
void handle_redirections(t_line *final);
int check_file_path(t_line *final);
void handle_herdoc(t_line *final, env_vars *list_env);
env_vars *envpp_export(env_vars *list);
int	ft_atoii(char *value);
void chdiir_help(t_line *final,env_vars *list,char *pwd);
char **create_av(t_node *tokens);
int help_execute_files(t_line *final,char **env,char **av);
char *find_executable(t_line  *final,env_vars *list,char **av);
void    when_not_blt(t_line *final, char **env, env_vars *list);
char **fake_env(void);
long long ft_atoll(char *str);
void	ft_putstr(char *s, int fd);
int handle_one_blt(t_line *final,char **env,env_vars *list);
int is_dir(char *parth);
void handle_heredoc(t_line *final, env_vars *list_env);
void chdiir_help2(t_line *final,env_vars *list,char *pwd);
void check_echo_flags(t_line *final, t_node **current, int *newline);
int	cd_helper(t_line *final, env_vars *list, char **env);
char	*ft_strchrr(const char *s, int c);
void	process_heredoc(t_heredoc *heredoc, env_vars *list_env);
int	is_valid_number(char *str);
int get_delim_expand_pipe(t_line *final, t_heredoc	*heredocs, int *len);
void	writing_heredoc(t_token **hered_tokens, t_heredoc *heredoc, env_vars *list);
void	child_heredoc(t_heredoc *heredocs, env_vars *list, int count);
char	*ft_strdupp(char *s1);
//////////////////*PARSING*//////////////////////////


void display_prompt(t_list shell, char **env, env_vars *list);
char **copy_env(char **env);
int		check_unclosed_quotes(char *input, int i , int inside_d, int inside_s);
t_token **into_tokens(char *input, int i, int start);
int check_prohibited_char(char *input);
int is_redirection_op(char c);
int skip_spaces(char *input, int i);
void	ft_lstadd_back(t_node **lst, t_node *neew);
int validate_redirection_syntax(char *input);
int tokens_number(char *input, int i, int count, int inside_d);
int more_than_op(char *input);
void check_token_dollar(t_token **token);
int ft_strlen(char *str);
char	*cat_token(char *input, int start, int end);
void expand(t_token **tokens, env_vars *list_env);
char *get_value(env_vars *list_env, char *name, char *value, int j);
char *replace_value(char *token, char *value, char *name);
void expand_home(t_token **tokens, env_vars *list_env);
int ft_strchr(char *s, int c);
t_node *search_token(t_token **tokens);
t_line *tokens_to_lines(t_node *tokens);
t_node  *ft_lstnew(char *content);
int	ft_lstsize(t_node *lst);
int pipe_syntax(char *input, int i, int in_quotes);
int open_files(t_line *lines);
void    *c_malloc(size_t size, int flag);
int	ft_atoi(const char *str);
int dollar_inside_quotes_alone(char *content);
int get_shlvl(char **env);
void set_shlvl(t_list shell);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void check_for_delimeter(t_node *tokens);
int ft_is_space(char *input);
int check_for_and(char *input);
int check_edge_case(char *content);
char *pass_dollar(char *content);
char	*ft_strdup(char *s1);
t_node	*ft_lstlast(t_node *lst);
void last_command(env_vars *list, t_line *final);
char	*copy_str(char *dest, char *src);
void sigint_hand_heredoc(int signal);
void	sigint_handler(int signal);
#endif
