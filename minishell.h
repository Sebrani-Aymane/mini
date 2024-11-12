/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:20:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/12 18:41:46 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SET 1
# define GET 2
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>

typedef struct s_token
{
	char	*content;
	int		need_expand;
	int		divide_space;
	int		expanded;
}	t_token;

typedef struct s_list
{
	t_token	**tokens;
	char	**env;
	int		shlvl;
}	t_list;

typedef struct s_heredoc
{
	int		fd[2];
	char	*delimiter;
	int		expand_vars;
}	t_heredoc;

typedef struct s_node
{
	char			*content;
	int				type;
	int				delimeter_inside_quotes;
	int				inside_quotes;
	int				need_expand;
	struct s_node	*next;
}	t_node;

typedef struct s_line
{
	t_node			*tokens;
	int				fd_in;
	int				fd_out;
	int				default_in;
	int				default_out;
	struct s_line	*next;
}	t_line;

typedef struct env_vars_t
{
	char				*vars;
	char				*var_value;
	char				**env;
	char				*pwd;
	struct env_vars_t	*next;
}	t_env_vars;

typedef struct shell
{
	char	**argv;
	char	**env;
	int		fd_in;
	int		fd_out;
}	t_shell;

typedef struct s_coll
{
	void			*ptr;
	struct s_coll	*next;
}	t_coll;

typedef struct s_heredoc_params
{
	t_line			*final;
	t_env_vars		*list_env;
	struct termios	*stats;
	t_heredoc		*heredocs;
	int				count;
	int				pid;
}	t_heredoc_params;

struct s_handle_attr
{
	int	pid;
	int	i;
	int	pipes_count;
	int	fd[2];
	int	ret;
	int	fd_in;
	int	status;
} ;

char		*ft_strdup(char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*str_joiner(char *s1, char *s2);
int			ft_strcmp(char *str, char *str1);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_strlen(char *str);
int			ft_strlenn(char *str);
char		*ft_strchrr(const char *s, int c);
void		copy_it(char *dest, char *src);
char		*copy_str(char *dest, char *src);
void		ft_putstr(char *s, int fd);
int			ft_strchr(char *s, int c);

/* Character checks */
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			is_space(char *str);
int			ft_is_space(char *input);
int			ft_listsizeee(t_line *lst);

/* Number utilities */
long long	ft_atoll(char *str);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
int			is_valid_number(char *str);

/* Memory management */
void		*c_malloc(size_t size, int flag);
void		free_double(char **str);
void		clear_strss(char **strs, int n);

/* Environment variables */
t_env_vars	*list_init(char **variables);
t_env_vars	*envpp(t_env_vars *list);
t_env_vars	*envpp_export(t_env_vars *list);
t_env_vars	*append_to_list(t_env_vars *list, char **temp);
void		add_to_list(t_env_vars **head, t_env_vars *newe);
int			valid_to_add(t_env_vars *env, char *str);
int			valid_to_add_plus(t_env_vars *env, char *str);
int			first_in(char *str, t_env_vars *env);
int			check_key(char *str);
char		*get_path(char **envp, char *str);
char		*get_path_from_list(t_env_vars *list, char *str);
char		**fake_env(void);
char		**copy_env(char **env);
void		set_shlvl(t_list shell);
int			get_shlvl(char **env, int notif, int i);

/* Builtin commands */
void		echoo(t_node *current);
char		*pwdd(t_env_vars *list);
int			check_key_un(char *str);
int			export_all(t_env_vars *env, t_line *final);
int			export_it(t_env_vars *env, char *str);
int			export_with_plus(char *av, t_env_vars *env);
void		exitt(t_line *final);
int			unset(t_env_vars *env, t_line *final);
int			chdirr(char **env, t_line *final, t_env_vars *list);
void		chdiir_help(t_line *final, t_env_vars *list, char *pwd);
void		chdiir_help2(t_line *final, t_env_vars *list, char *pwd);
int			cd_helper(t_line *final, t_env_vars *list, char **env);

/* Command execution */
int			execute_the_thing(t_line *final, char **env, t_env_vars *list);
int			execute_blts(char *builtin, t_line *final, t_env_vars *list,
				char **env);
int			executefilepath(t_line *final, char **env, t_env_vars *list);
int			check_builtin(t_line *final, t_env_vars *list, char **env);
int			handle_one_blt(t_line *final, char **env, t_env_vars *list);
void		when_not_blt(t_line *final, char **env, t_env_vars *list);
int			help_execute_files(t_line *final, char **env, char **av);
char		*find_executable(t_line *final, t_env_vars *list, char **av);
int			is_dir(char *path);

/* Pipe handling */
int			handle_pipe(t_line *final, char **env, t_env_vars *list);
int			setup_pipe(struct s_handle_attr *attr);
int			create_child_process(struct s_handle_attr *attr);
void		wait_for_children(struct s_handle_attr *attr);
void		cleanup_pipe_handler(struct s_handle_attr *attr);
int			handle_single_builtin(struct s_handle_attr *attr, t_line *final,
				char **env, t_env_vars *list);

/* Heredoc handling */
int			handle_heredoc(t_line *final, t_env_vars *list_env,
				struct termios *stats);
void		process_heredoc(t_heredoc *heredoc, t_env_vars *list_env);
void		child_heredoc(t_heredoc *heredocs, t_env_vars *list,
				int count, int *sig_var);
int			get_delim_expand_pipe(t_line *final, t_heredoc *heredocs, int *len);
void		writing_heredoc(t_token **hered_tokens, t_heredoc *heredoc,
				t_env_vars *list);
void		init_pipe_attr(struct s_handle_attr *attr, t_line *final);
void		handle_child_signals(int status);
int			parent_process(struct s_handle_attr *attr);
int			child_process(struct s_handle_attr *attr, t_line *final,
				char **env, t_env_vars *list);
void		restore_file_descriptors(t_line *final);
int			handle_child_redirections(struct s_handle_attr *attr);

/* Signal handling */
void		signals_ignore(void);
void		signals_allow(void);
void		sigint_hand_heredoc(int signal);
void		sigint_handler(int signal);
void		sig_handler(char *input_rl);

/* Parser utilities */
int			count_words(char *str, char c);
char		*return_word(char *str, char c);
int			ft_strrncmp(char *s1, char *s2, int n);
char		**split(char *str, char sep);
char		*get_till(char *str, char c);
int			get_nodee(t_env_vars *list);
int			ft_listsize(t_line *lst);
int			exit_status(int type, int value);
void		handle_redirections(t_line *final);
int			check_file_path(t_line *final);
char		**create_av(t_node *tokens, int i);
void		conf_inside_quotes(t_node *tokens);

/* Token handling */
void		ft_lstadd_back(t_node **lst, t_node *neew);
t_node		*ft_lstnew(char *content);
int			ft_lstsize(t_node *lst);
t_node		*ft_lstlast(t_node *lst);
void		add_node(t_node **list, char *content, int need_expand);
void		add_token(t_node **list, t_token *tokens, int start, int end);

/* Parser functions */
void		display_prompt(t_list shell, char **env, t_env_vars *list_env,
				struct termios *stats);
int			check_unclosed_quotes(char *input, int i, int inside_d,
				int inside_s);
t_token		**into_tokens(char *input, int i, int start, int count);
int			is_redirection_op(char c);
int			skip_spaces(char *input, int i);
int			validate_redirection_syntax(char *input);
int			tokens_number(char *input, int i, int count, int inside_d);
int			more_than_op(char *input);
void		check_token_dollar(t_token **token);
char		*cat_token(char *input, int start, int end);
int			check_for_and(char *input);
int			pass_spaces(char *input);
int			pass_spaces_end(char *input);
void		copy_without_spaces(char *dst, char *src);
int			inside_quotes(char *str);
int			contains_only_symbol(char *str);
int			contains_symbol(char *str);
int			can_expand(char *input);
int			check_edge_case(char *content);
int			dollars_number(char *content, int need_exp, char where);
int			find_var_end(char *input, int *start);
char		*variable_name(char *input, int *start);
char		*exp_exit_status(char *num);
char		*get_value(t_env_vars *list_env, char *name, char *value, int j);
int			check_input(char *input);
void		check_quotes(char *input, int *inside_d, int *inside_s, int i);
void		quotes_handle(char *input, int *inside_q, int *q_type, int i);
int			print_error_message(int i, char *input);
int			handle_redirec_edge_cases(char *input);
void		final_tokens(t_node *token);
char		*replace_value(char *token, char *value, char *name);
char		*ft_strncpy(char *dest, char *src, unsigned int n);

/* Expansion handling */
int			expand(t_token **tokens, t_env_vars *list_env, int notif,
				char where);
void		expand_home(t_token **tokens, t_env_vars *list_env);
char		*pass_dollar(char *content);
int			dollar_inside_quotes_alone(char *content);
char		*join_tokens(t_list *shell);
char		*check_value(char *value, char *name, t_token *temp);

/* Line handling */
t_node		*search_token(t_token **tokens);
t_line		*tokens_to_lines(t_node *tokens);
void		last_command(t_env_vars *list, t_line *final, int final_size,
				t_node *curr);
int			pipe_syntax(char *input, int i, int in_quotes);
int			open_files(t_line *lines, t_node *curr_node, int in, int out);
void		check_for_delimeter(t_node *tokens);
void		check_echo_flags(t_node **current, int *newline);
int			check_eccho(t_node *final);
char		*ft_strstr(const char *s1, const char *s2);
char		*ft_strcat(char *dest, char *src);

#endif