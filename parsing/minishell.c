/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/11/01 20:17:15 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(char *input_rl)
{
	if (input_rl == NULL)
	{
		c_malloc(0, 0);
		rl_clear_history();
		printf("exit\n");
		exit(0);
	}
}

void	sigint_hand_heredoc(int signal)
{
	(void)signal;
	printf("\n");
	exit(100);
}

void	sigint_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_list			shell;
	env_vars		*list_env;
	struct termios	stats;

	(void)av;
	(void)ac;
	if (!isatty(STDIN_FILENO))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	if (!*env)
		env = fake_env();
	shell.env = copy_env(env);
	list_env = list_init(shell.env);
	shell.shlvl = get_shlvl(shell.env, 0, 0);
	set_shlvl(shell);
	handle_signals();
	if (tcgetattr(STDIN_FILENO, &stats) < 0)
		perror("terminal error ");
	display_prompt(shell, shell.env, list_env, &stats);
	c_malloc(0, 0);
}
