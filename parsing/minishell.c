#include "../minishell.h"

int main(int ac, char **av, char **env)
{
    t_list shell;

    (void)av;
    (void)ac;
    shell.env_var = copy_env(env);
    display_prompt(shell, env);
    
    

    
}
