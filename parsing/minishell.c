/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/21 15:05:01 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
void	sigint_handler(int signal)
{
	(void)signal;
	write(1, "\nminishell$  ", 13);
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	//chi l3ibat dread line
}

int	main(int ac, char **av, char **env)
{
	t_list		shell;
	env_vars	*list_env;
	(void)av;
	(void)ac;
	// rl_catch_signal = 0;
	if (!*env)
		env = fake_env();
	shell.env = copy_env(env);
	list_env = list_init(shell.env);
	shell.shlvl = get_shlvl(shell.env);
	set_shlvl(shell);
	handle_signals();
	display_prompt(shell, shell.env, list_env);
	c_malloc(0, 0);
}
// unset PATH PWD SHLVL _if (final_size > 1)