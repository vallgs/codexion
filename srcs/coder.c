/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:03:52 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/27 13:13:22 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codex.h"

void	take_dongles(t_coder *coder)
{
	t_dongle *first;
	t_dongle *second;

	if (coder->left < coder->right)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	pthread_mutex_lock(&first->mutex);
	print_log(coder, "has taken a dongle");
	pthread_mutex_lock(&second->mutex);
	print_log(coder, "has taken a dongle");
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_unlock(&coder->right->mutex);
}

void	do_compile(t_coder *coder)
{
	take_dongles(coder);
	pthread_mutex_lock(&coder->???);
	coder->last_compile_start = ???;
	pthread_mutex_unlock(&coder->???);
	print_log(coder, "is compiling");
	ft_sleep(coder->data, coder->data->???);
	pthread_mutex_lock(&coder->???);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->???);
	release_dongles(coder);
}
