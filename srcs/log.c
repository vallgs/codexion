/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:17:41 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/26 12:37:29 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

bool	is_stopped(t_data *data)
{
	bool	stopped;

	pthread_mutex_lock(&data->stop_mutex);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stopped);
}

void	print_log(t_coder *coder, char *msg)
{
	t_data	*data;

	data = coder->data;
	pthread_mutex_lock(&data->print_mutex);
	if (!is_stopped(data))
		printf("%ld %d %s\n", get_time_ms() - data->start_time, coder->id,
			msg);
	pthread_mutex_unlock(&data->print_mutex);
}