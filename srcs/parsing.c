// av a mettre number_of_coders time_to_burnout time_to_compile time_to_debug
//time_to_refactor number_of_compiles_required dongle_cooldown scheduler

#include "../includes/codex.h"

int	parse_arg(char **arg)
{
	int	i;

	i = 1;
	while (arg[i] && i <= 7)
	{
		if (ft_is_valid_number(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	parse_last_arg(char **arg)
{
	int	i;

	i = 8;
	if (ft_strcmp(arg[i], "fifo") == 0 || ft_strcmp(arg[i], "edf") == 0)
		return (1);
	return (0);
}
