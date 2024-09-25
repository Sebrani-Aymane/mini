#include "../minishell.h"

void printrrr(t_line *final)
{

	while (final->tokens)
	{
		fprintf(stderr,"%s\n",final->tokens->content);
		final->tokens =final->tokens->next; 
	}
}