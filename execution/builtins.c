/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:28 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/27 16:22:03 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void	echoo(t_line *final)
{
	int newline = 1;

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
		if ((current->type == 1 || current->type == 2))
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
	if (a == 0)
	{
	pwd = getcwd(NULL,0);
	if(pwd)
		printf("%s\n",pwd);
	else
		write(2,"getcwd faild\n",14);
	} 
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
		if(list->var_value && *(list->var_value) != '\0')
			printf("=%s\n",list->var_value);
		else
			printf("\n");
		list = list->next;
	}
	return(tmp);
}

int	chdirr(char **env,t_line *final,env_vars *list)
{
	char *home;
	int res;
	char *pwd_aftr_cd;
	char *pwd_bfr_cd;
	env_vars *temp;
	
	res = 0;
	pwd_bfr_cd = get_path_from_list(list, "PWD");
	if (!final->tokens->next)
	{
		home = get_path(env,"HOME=");
		if (!home)
			return(free(home),fprintf(stderr,"minishell: cd: HOME not set"),0);
		res = chdir(home);
		free(home);
	}
	else
	{
		res = chdir(final->tokens->next->content);
		pwd_aftr_cd = getcwd(NULL, 0);
		if (!pwd_aftr_cd)
		{
			chdiir_help(final,list,pwd_bfr_cd);
			return(free(pwd_bfr_cd),res);
		}
		free(pwd_aftr_cd);
	}
	temp = list;
	while (list)
	{
		if (!ft_strcmp(list->vars,"OLDPWD") || !ft_strcmp(list->vars,"PWD"))
		{
			if (strcmp(list->vars,"PWD"))
				list->var_value = pwd_bfr_cd;
			if (strcmp(list->vars,"OLDPWD"))
				list->var_value = getcwd(NULL, 0);
		}
		list = list ->next;
	}
	list = temp;
	return(res);
}