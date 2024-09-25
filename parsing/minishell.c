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
int returnnn(char **env)
{
    int ret=0;
    while (env[ret])
        ret++;
    return(ret);
}
int main(int ac, char **av, char **env)
{
    t_list shell;
    env_vars *list_env;

    (void)av;
    (void)ac;
    if(returnnn(env) == 0)
    {
        shell.env =  fake_env();
    }
    shell.env = copy_env(env);
    list_env = list_init(shell.env);
    list_env->shlvl = get_shlvl(list_env);
    set_shlvl(list_env);
    handle_signals();
    display_prompt(shell, shell.env,list_env);
}
