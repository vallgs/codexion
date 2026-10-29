/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 14:57:15 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/29 11:52:37 by vallangl         ###   ########.fr       */
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

int init_alloc(t_data *data)
{
	data->dongles = malloc(sizeof(t_dongle) * data->number_of_coder);
	if (data->dongles == NULL)
		return (0);
	data->coders = malloc(sizeof(t_coder) * data->number_of_coder);
	if (data->coders == NULL)
	{
		free(data->dongles);
		return (0);
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	data->stop = false;
	return (1);
}

int	init_dongles(t_data *data)
{
	int	k;

	k = 0;
	while (k < data->number_of_coder)
	{
		pthread_mutex_init(&data->dongles[k].mutex, NULL);
		data->dongles[k].available_at = 0;
		data->dongles[k].taken = false;
		data->dongles[k].next_ticket = 0;
		data->dongles[k].size = 0;
		k++;
	}
	return (1);
}

int init_coders(t_data *data)
{
	int k;

	k = 0;
	while (k < data->number_of_coder)
	{
		data->coders[k].id = k + 1;
		data->coders[k].compile_count = 0;
		data->coders[k].last_compile_start = 0;
		data->coders[k].data = data;
		data->coders[k].left = &data->dongles[k];
		data->coders[k].right = &data->dongles[(k + 1) % data->number_of_coder];
		pthread_mutex_init(&data->coders[k].state_mutex, NULL);
		k++;
	}
	return (1);
}

int init_simulation(t_data *data)
{
	if (init_alloc(data) == 0)
		return (0);
	if (init_dongles(data) == 0)
		return (0);
	if (init_coders(data) == 0)
		return (0);
	return (1);
}