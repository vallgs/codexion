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

int	start_simulation(t_data *data)
{
	int	k;

	init_start_times(data);
	k = 0;
	while (k < data->number_of_coder)
	{
		pthread_create(&data->coders[k].thread, NULL,
			coder_routine, &data->coders[k]);
		k++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	k = 0;
	while (k < data->number_of_coder)
	{
		pthread_join(data->coders[k].thread, NULL);
		k++;
	}
	pthread_join(data->monitor, NULL);
	return (1);
}


