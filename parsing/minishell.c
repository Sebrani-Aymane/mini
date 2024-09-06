#include "../minishell.h"
void handle_signals(void)
{
    signal(SIGQUIT, SIG_IGN);

}
int main(int ac, char **av, char **env)
{
    t_list shell;

    (void)av;
    (void)ac;
    shell.env_var = copy_env(env);
    handle_signals();
    display_prompt(shell, env);
    
    

    
}
