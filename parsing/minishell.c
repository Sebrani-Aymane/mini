#include "../minishell.h"

void sigint_handler(int signal)
{
    (void)signal;
    write(1, "\nminishell$  ", 13);
}
void handle_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
int main(int ac, char **av, char **env)
{
    t_list shell;

    (void)av;
    (void)ac;
    shell.env_var = copy_env(env);
   shell.shlvl = get_shlvl(shell.env_var);
   set_shlvl(shell);
    handle_signals();
    display_prompt(shell, env);
}
