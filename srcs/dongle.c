/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:11:45 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/30 12:20:16 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

void	order_dongles(t_coder *coder, t_dongle **first, t_dongle **second)
{
	*first = coder->left;
	*second = coder->right;
	if (coder->right < coder->left)
	{
		*first = coder->right;
		*second = coder->left;
	}
}

void	request_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	t_request	req;

	order_dongles(coder, &first, &second);
	req.coder = coder;
	req.key = 0;
	if (coder->data->scheduler == EDF)
		req.key = coder->last_compile_start + coder->data->time_to_burnout;
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	req.ticket = first->next_ticket++;
	heap_push(first, req);
	req.ticket = second->next_ticket++;
	heap_push(second, req);
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
}

bool	take_dongles(t_coder *coder)
{
	request_dongles(coder);
	while (!try_take(coder))
	{
		if (is_stopped(coder->data))
			return (false);
		usleep(100);
	}
	print_log(coder, "has taken a dongle");
	print_log(coder, "has taken a dongle");
	return (true);
}

void	release_dongles(t_coder *coder)
{
	long	now;

	now = get_time_ms();
	pthread_mutex_lock(&coder->left->mutex);
	coder->left->taken = false;
	coder->left->available_at = now + coder->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_lock(&coder->right->mutex);
	coder->right->taken = false;
	coder->right->available_at = now + coder->data->dongle_cooldown;
	pthread_mutex_unlock(&coder->right->mutex);
}

bool	try_take(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	bool		ok;

	order_dongles(coder, &first, &second);
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	ok = is_my_turn(coder, first) && is_my_turn(coder, second);
	if (ok)
	{
		heap_pop(first);
		heap_pop(second);
		first->taken = true;
		second->taken = true;
	}
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	return (ok);
}
