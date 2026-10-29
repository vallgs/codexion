/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:03:52 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/29 12:56:57 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

void	do_compile(t_coder *coder)
{
	if (!take_dongles(coder))
		return ;
	pthread_mutex_lock(&coder->state_mutex);
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->state_mutex);
	print_log(coder, "is compiling");
	ft_sleep(coder->data, coder->data->time_to_compile);
	pthread_mutex_lock(&coder->state_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->state_mutex);
	print_log(coder, "is debugging");
	release_dongles(coder);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = arg;
	if (coder->id % 2 == 0)
		ft_sleep(coder->data, coder->data->time_to_compile / 2);
	if (coder->left == coder->right)
		return (single_coder(coder));
	while (!is_stopped(coder->data))
	{
		do_compile(coder);
		ft_sleep(coder->data, coder->data->time_to_debug);
		print_log(coder, "is refactoring");
		ft_sleep(coder->data, coder->data->time_to_refactor);
	}
	return (NULL);
}

void *single_coder(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->mutex);
	print_log(coder, "has taken a dongle");
	ft_sleep(coder->data, coder->data->time_to_burnout + 100);
	pthread_mutex_unlock(&coder->left->mutex);
	return (NULL);
}
