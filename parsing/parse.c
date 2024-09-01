/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:20:30 by cbajji            #+#    #+#             */
/*   Updated: 2024/09/01 16:36:19 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
word 1
built 2
heredoc 3
infile 4
outfile 5
*/

void	redirections_classifier(t_node **lst_token)
{
	t_node	*current;

	current = *lst_token;
	while (current)
	{
		if (current->type == 4 && !strcmp(current->content, "<")
			&& current->next != NULL && strcmp(current->next->content, ">"))
			current->next->type = 4;
		else if (current->type == 5 && (!strcmp(current->content, ">")
				|| !strcmp(current->content, ">>")) && current->next != NULL)
			current->next->type = 5;
		else if (current->type == 3 && (!strcmp(current->content, "<<"))
			&& current->next != NULL)
			current->next->type = 3;
		current = current->next;
	}
}

void giving_type(t_node *token)
{
    t_node *current;
    current = token;
    while (current)
    {
        if (!strcmp(current->content, "<"))
            current->type = 4;
        else if (!strcmp(current->content, ">") || !strcmp(current->content, ">>"))
            current->type = 5;
        else if (!strcmp(current->content, "<<"))
            current->type = 3;
        else if (!strcmp(current->content, "echo") || !strcmp(current->content, "cd") || !strcmp(current->content, "pwd") || !strcmp(current->content, "export")
                || !strcmp(current->content, "unset") || !strcmp(current->content, "env") || !strcmp(current->content, "exit"))
            current->type = 2;
        else 
            current->type = 1;
        current = current->next;
    }
}

t_line *create_line(t_node *node)
{
    t_line *line;
    t_node *current = node;
    t_node *first = NULL;
    t_node *last = NULL;

    line = malloc(sizeof(t_line));
    if (!line)
        return NULL;
    line->tokens = NULL;
    
    while (current && strcmp(current->content, "|") != 0)
    {
        t_node *new_node = malloc(sizeof(t_node));
        if (!new_node)
            return NULL;
        new_node->content = current->content; // Copy the content
        new_node->type = current->type;       // Copy the type
        new_node->next = NULL;                // Initialize next to NULL
        
        if (!first)
        {
            first = new_node;
            line->tokens = first;
        }
        else
        {
            last->next = new_node;
        }
        
        last = new_node;
        current = current->next;
    }
    
    line->next = NULL;
    redirections_classifier(&line->tokens);
    return line;
}


t_line *tokens_to_lines(t_node *tokens)
{
    t_line *first_line = NULL;
    t_line *last_line = NULL;
    t_line *line;

    giving_type(tokens);
    // t_node *cpy = tokens;
    // while (cpy)
    // {
    //     printf("%s\n", cpy->content);
    //     cpy = cpy->next;
    // }
    // t_node *cpy_two;
    while (tokens)
    {
        line = create_line(tokens);
    //     cpy_two = tokens;
    //     while (cpy_two)
    // {
    //     printf("%s\n", cpy_two->content);
    //     cpy_two = cpy_two->next;
    // }
        if (!first_line)
            first_line = line;
        else
            last_line->next = line;
        last_line = line;
        while (tokens && strcmp(tokens->content, "|") != 0)
        {
            
            // printf("%s\n", tokens->content);
            tokens = tokens->next;
            
        }
        // printf("%s\n", tokens->content);
        
        if (tokens && strcmp(tokens->content, "|") == 0)
        {
            tokens = tokens->next;
            // printf("///////////////\n");
        }
    }
    return first_line;
}
// t_line *create_line(t_node *node)
// {
//     t_line *line;
//     t_node *current = node;
//     t_node *first = NULL;
//     t_node *last = NULL;
//     t_node *cpy = node;

//     line = malloc(sizeof(t_line));
//     if (!line)
//         return NULL;
//     line->tokens = NULL;
//     while (current && strcmp(current->content, "|") != 0)
//     {
//         if (!first)
//         {
//             first = current;
//             line->tokens = first;
//         }
//         else
//             last->next = current;
//         last = current;
//         current = current->next;
//     }
//     if (last)
//         last->next = NULL;
//     line->next = NULL;
//     redirections_classifier(&line->tokens);
//     return line;
// }