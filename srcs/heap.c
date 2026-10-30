/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 11:55:42 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/30 12:19:33 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

bool	request_before(t_request *a, t_request *b)
{
	if (a->key != b->key)
		return (a->key < b->key);
	return (a->ticket < b->ticket);
}

void	swap_request(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heap_push(t_dongle *d, t_request request)
{
	int	i;

	i = d->size;
	d->queue[i] = request;
	d->size++;
	while (i > 0 && request_before(&d->queue[i], &d->queue[(i - 1) / 2]))
	{
		swap_request(&d->queue[i], &d->queue[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void	heap_pop(t_dongle *d)
{
	if (d->size == 0)
		return ;
	d->size--;
	d->queue[0] = d->queue[d->size];
	if (d->size == 2 && request_before(&d->queue[1], &d->queue[0]))
		swap_request(&d->queue[0], &d->queue[1]);
}

bool	is_my_turn(t_coder *coder, t_dongle *d)
{
	return (d->size > 0 && d->queue[0].coder == coder
		&& !d->taken && get_time_ms() >= d->available_at);
}
