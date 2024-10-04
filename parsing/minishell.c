/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:20 by cbajji            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/03 05:17:20 by asebrani         ###   ########.fr       */
=======
/*   Updated: 2024/10/02 17:27:28 by cbajji           ###   ########.fr       */
>>>>>>> 4c1a846ae99dcd020b6ebf8e27f9ba90b9807f89
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
	shell.shlvl = get_shlvl(shell.env);
	set_shlvl(shell);
	handle_signals();
	display_prompt(shell, shell.env, list_env);
	c_malloc(0, 0);
}
// unset PATH PWD SHLVL _if (final_size > 1)