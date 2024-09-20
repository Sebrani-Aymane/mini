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
    env_vars *list_env;
    (void)av;
    (void)ac;
    shell.env = copy_env(env);
    list_env = list_init(env);
    list_env->shlvl = get_shlvl(list_env);
    set_shlvl(list_env);
    handle_signals();
    display_prompt(shell, env,list_env);
}
