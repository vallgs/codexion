/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 13:12:11 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/30 12:18:00 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = true;
	pthread_mutex_unlock(&data->stop_mutex);
}

bool	check_burnout(t_data *data)
{
	int		k;
	long	last;

	k = 0;
	while (k < data->number_of_coder)
	{
		pthread_mutex_lock(&data->coders[k].state_mutex);
		last = data->coders[k].last_compile_start;
		pthread_mutex_unlock(&data->coders[k].state_mutex);
		if (get_time_ms() - last > data->time_to_burnout)
		{
			pthread_mutex_lock(&data->print_mutex);
			set_stop(data);
			printf("%ld %d burned out\n",
				get_time_ms() - data->start_time, data->coders[k].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (true);
		}
		k++;
	}
	return (false);
}

bool	check_all_done(t_data *data)
{
	int		k;
	int		count;

	k = 0;
	while (k < data->number_of_coder)
	{
		pthread_mutex_lock(&data->coders[k].state_mutex);
		count = data->coders[k].compile_count;
		pthread_mutex_unlock(&data->coders[k].state_mutex);
		if (count < data->number_of_compiles_required)
			return (false);
		k++;
	}
	set_stop(data);
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = arg;
	while (1)
	{
		if (check_burnout(data) || check_all_done(data))
			return (NULL);
		usleep(1000);
	}
}
