#include "../includes/codex.h"

int	init_data_struct(t_data *dt, char **arg)
{
	dt->number_of_coder = ft_atoi(arg[1]);
	dt->time_to_burnout = ft_atoi(arg[2]);
	dt->time_to_compile = ft_atoi(arg[3]);
	dt->time_to_debug = ft_atoi(arg[4]);
	dt->time_to_refactor = ft_atoi(arg[5]);
	dt->number_of_compiles_required = ft_atoi(arg[6]);
	dt->dongle_cooldown = ft_atoi(arg[7]);
	dt->scheduler = arg[8];
	if (dt->number_of_coder < 1 || dt->time_to_burnout < 1 ||
		dt->time_to_compile < 1 || dt->time_to_debug < 1 ||
		dt->time_to_refactor < 1 || dt->number_of_compiles_required < 1 ||
		dt->dongle_cooldown < 1)
		return (0);
	return (1);
}




