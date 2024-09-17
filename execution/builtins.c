/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:28 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/17 16:01:51 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <errno.h>
#include <stdio.h>

void	echoo(t_line *final)
{
	int newline = 1;
	int i =0;
	t_node *current;
	t_node* tmp;
	if (final->tokens->next)
	{
		current = final->tokens->next;
		tmp = current;
	}
	else 
		current = NULL;
	if (check_eccho(current))
    {
		while(check_eccho(current))
			current = current ->next;
		tmp = current;
		newline = 0;
	}
	current = tmp;
    while (current)
	{
		if (current->content[i] && (current->type == 1 || current->type == 2))
		{
       		printf("%s", current->content);
        	if (current->next)
			{ 
        	    printf(" ");
        	}
		}
        current = current->next;
	}
    if (newline)
	{
        printf("\n");
    }
}

void pwdd(int a)
{
	char *pwd = NULL;
	(void) a;
	pwd = getcwd(NULL,0);
	if(pwd)
		printf("%s\n",pwd);
	else
		write(2,"getcwd faild\n",14);
}

env_vars *envpp(env_vars *list)
{
	env_vars *tmp;

	tmp = list;
	if (!list)
		return(NULL);
	while (list)
	{
		printf("%s",list->vars);
		if(*(list->var_value) != '\0')
			printf("=%s\n",list->var_value);
		else
			printf("\n");
		list = list->next;
	}
	return(tmp);
}

int	chdirr(char **env,t_line *final)
{
	int res = -1;
	char *path;

	path = get_path(env,"HOME=");
	if(!final->tokens->next)
	{
		res = chdir(path);
		free (path);
	}
	else
		res = chdir(final->tokens->content);
	return(res);
}