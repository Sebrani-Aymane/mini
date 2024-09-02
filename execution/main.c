/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:59:01 by asebrani          #+#    #+#             */
/*   Updated: 2024/09/02 16:53:44 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int main(int ac, char **argv, char **envp) {

//   env_vars *list;
//   int i;

//   list = list_init(envp);
//   (void)ac;
//   (void)argv;
//   char **av = NULL;
//   while (1)
//   {
//     i = 1;
//     char *cmd = readline("minishell $ ");
//     if (cmd)
//       add_history(cmd);
//     av = split(cmd, ' ');
//     if (!av || !(*av))
//       return (0);
//     execute_the_thing(av,envp,list);
//   }
//   return (0);
// }
