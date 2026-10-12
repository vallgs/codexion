#include "../includes/codex.h"

int main(int ac, char **av)
{
    if (ac != 9)
    {
        printf("expected 8 arguments");
        return (0);
    }
    else
    {
        if (parse_arg(av) == 1 && parse_last_arg(av) == 1)
            printf("ok");
    }
    return (0);
}