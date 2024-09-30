/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:20 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/30 21:42:00 by asebrani         ###   ########.fr       */
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
}

// void fn() {
// 	system("leaks minishell");
// }

// void shell(int ac, char **av, char **env) {
// 	t_list		shell;
// 	env_vars	*list_env;
// 	(void)av;
// 	(void)ac;
// 	if (!*env)
// 		env = fake_env();
// 	shell.env = copy_env(env);
// 	list_env = list_init(shell.env);
// 	list_env->shlvl = get_shlvl(list_env);
// 	set_shlvl(list_env);
// 	handle_signals();
// 	display_prompt(shell, shell.env, list_env);
// }

int	main(int ac, char **av, char **env)
{
	// atexit(fn);
	// shell(ac, av, env);
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
	c_malloc(0, 0);
}
