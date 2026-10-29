/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 12:21:42 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/29 14:54:41 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

void	cleanup(t_data *data)
{
	int	k;

	k = 0;
	while (k < data->number_of_coder)
	{
		pthread_mutex_destroy(&data->dongles[k].mutex);
		pthread_mutex_destroy(&data->coders[k].state_mutex);
		k++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->dongles);
	free(data->coders);
}
