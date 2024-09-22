#include "../minishell.h"

void printrrr(t_line *final)
{

	while (final->tokens)
	{
		printf("%p\n",final->tokens->content);
		fprintf(stderr,"%s\n",final->tokens->content);
		final->tokens =final->tokens->next; 
	}
}