/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/25 17:17:42 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	write(1, "\nminishell$  ", 13);
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_list		shell;
	env_vars	*list_env;

	(void)av;
	(void)ac;
	shell.env = copy_env(env);
	list_env = list_init(env);
	list_env->shlvl = get_shlvl(list_env);
	set_shlvl(list_env);
	handle_signals();
	display_prompt(shell, env, list_env);
}
