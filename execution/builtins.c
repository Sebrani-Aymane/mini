/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:28 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/01 16:36:24 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <errno.h>
#include <stdio.h>

void echoo(char **av)
{
    int i = 1;         
    int newline = 1; 

    while (av[i] && strcmp(av[i], "-n") == 0)
	{
        newline = 0;
        i++; 
    }
    while (av[i])
	{
        printf("%s", av[i]);
        if (av[i + 1])
		{ 
            printf(" ");
        }
        i++;
	}
    if (newline)
	{
        printf("\n");
    }
}

#include <errno.h>
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
		if(list->var_value)
			printf("=%s\n",list->var_value);
		else
			printf("\n");
		list = list->next;
	}
	return(tmp);
}

int	chdirr(char **env,char **av)
{
	int res =-1;

	if(!av[1])
		res = chdir(get_path(env,"HOME="));
	else
		res = chdir(av[1]);
	return(res);
}