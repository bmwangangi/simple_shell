#include "shell.h"

int main(void)
{
    char *insert_line;
    char **arguments;
    int exit_sts = 0;

    signal(SIGINT, handle_signal);
    signal(SIGTSTP, SIG_IGN);

    while (!exit_sts)
    {
        display_prompt();
        insert_line = read_input();
        arguments = tokenize_input(insert_line);

        if (arguments[0] != NULL)
        {
            if (is_builtin_command(arguments))
            {
                execute_command(arguments, &exit_sts);
            }
            else
            {
                execute_command(arguments, &exit_sts);
            }
        }

        free(insert_line);
        free(arguments);
    }

    return (0);
}

