/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/28 03:56:08 by asebrani         ###   ########.fr       */
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
	if (!*env)
		env = fake_env();
	shell.env = copy_env(env);
	list_env = list_init(shell.env);
	list_env->shlvl = get_shlvl(list_env);
	set_shlvl(list_env);
	handle_signals();
	display_prompt(shell, shell.env, list_env);
}
