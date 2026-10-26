/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 14:57:15 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/23 13:59:13 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ft_strcmp(arg[8], "edf") == 0)
		dt->scheduler = EDF;
	else if (ft_strcmp(arg[8], "fifo") == 0)
		dt->scheduler = FIFO;
	if (dt->number_of_coder < 1 || dt->time_to_burnout < 1 ||
		dt->time_to_compile < 1 || dt->time_to_debug < 1 ||
		dt->time_to_refactor < 1 || dt->number_of_compiles_required < 1 ||
		dt->dongle_cooldown < 0)
		return (0);
	return (1);
}
