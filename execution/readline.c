/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:21:00 by asebrani          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/30 05:24:30 by asebrani         ###   ########.fr       */
=======
/*   Updated: 2024/09/29 21:37:00 by cbajji           ###   ########.fr       */
>>>>>>> 2895ddd58827979b40343654befb524a65a3adf0
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

int	execute_blts(char *blt, t_line *final,
						env_vars *list, char **env)
{
	int	ret;
	char *pwd;

	ret = 0;
	handle_redirections(final);
	if (strcmp(blt, "echo") == 0)
		echoo(final);
	else if (strcmp(blt, "pwd") == 0)
		{
			fprintf(stderr, "in pwd build in blt = [%s]\n", blt);
			pwd = pwdd(list);
			printf("%s\n",pwd);
			// free(pwd);
		}
	else if (strcmp(blt, "export") == 0)
	{
		if (!(final->tokens->next))
			envpp_export(list);
		else
			ret = export_all(list, final);
	}
	else if (strcmp(blt, "env") == 0)
		envpp(list);
	else if (strcmp(blt, "cd") == 0)
	{
		ret = chdirr(env, final, list);
		if (ret == -1)
		{
			ret = 1;
			exit_status(1, -1);
			printf("minishell: cd: %s no such file or directory\n",final->tokens->next->content);
		}
	}
	else if (strcmp(blt, "unset") == 0)
	{
		ret = unset(list, final);
	}
	else if (strcmp(blt, "exit") == 0)
		exitt(list, final);
	return (ret);
}


char **create_av(t_node *tokens)
{
	t_node *current = tokens;
	int count = 0;
	char **av;
	int i = 0;

	while (current)
	{
		if ((current->type == 1 || current->type == 2))
			count++;
		current = current->next;
	}
	av = malloc (sizeof(char *) * (count+1));
	current = tokens;
	while (current)
	{
		if ((current->type == 1 || current->type == 2))
		{
			av[i] = strdup(current->content);
			i++;
		}
		current = current->next;
	}
	av[i] = NULL;
	return av;
}
void print_it(t_line *final)
{
	t_node *cmd = final->tokens;
	while(cmd)
	{
		printf("--|%s|\n",cmd->content);
		cmd = cmd->next;
	}
}
int excutefilepath(t_line *final,env_vars *list,char **env)
{
	char *to_do;
	int ret = 2;
	(void)list;

	char **av = create_av(final->tokens);
	if (!av || !*av)
		return(0);
	execve(av[0], av, env);
	if (!check_file_path(final))
	{
		to_do = find_executable(final,list,av);
		if (to_do)
		{
			exit_status(1, 0);
			ret = execve(to_do, av, env);
		}
		if (!to_do && get_path_from_list(list,"PATH"))
		{
			write(2,"minishell: ",11);
			write(2,str_joiner(av[0]," :command not found\n"),ft_strlenn(av[0]) + 20);
			exit(127);
		}
		if (!to_do && !get_path_from_list(list,"PATH"))
			exit_status(1,127);
			free_double(av);
<<<<<<< HEAD
=======
			c_malloc(0, 0);
			exit(127);
>>>>>>> 2895ddd58827979b40343654befb524a65a3adf0
	}
	else
		help_execute_files(final,env,av);
	return ret;
}

void free_double(char **str)
{
	int j;

	j = 0;
	while (str[j])
		free(str[j++]);
	free(str);
}