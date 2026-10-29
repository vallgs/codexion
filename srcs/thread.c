/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:56:20 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/28 13:36:50 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

void	init_start_times(t_data *data)
{
	int	k;

	data->start_time = get_time_ms();
	k = 0;
	while (k < data->number_of_coder)
	{
		data->coders[k].last_compile_start = data->start_time;
		k++;
	}
}

void	join_coders(t_data *data, int count)
{
	int	k;

	k = 0;
	while (k < count)
	{
		pthread_join(data->coders[k].thread, NULL);
		k++;
	}
}

int	abort_simulation(t_data *data, int count)
{
	set_stop(data);
	join_coders(data, count);
	fprintf(stderr, "thread creation failed\n");
	return (0);
}

int	start_simulation(t_data *data)
{
	int	k;

	init_start_times(data);
	k = 0;
	while (k < data->number_of_coder)
	{
		if (pthread_create(&data->coders[k].thread, NULL,
				coder_routine, &data->coders[k]) != 0)
			return (abort_simulation(data, k));
		k++;
	}
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
		return (abort_simulation(data, data->number_of_coder));
	join_coders(data, data->number_of_coder);
	pthread_join(data->monitor, NULL);
	return (1);
}


