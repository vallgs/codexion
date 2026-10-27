/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:17:17 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/27 12:38:06 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codex.h"

int	main(int ac, char **av)
{
	t_data	i;

	if (ac != 9)
	{
		fprintf(stderr, "expected 8 arguments\n");
		return (1);
	}
	if (parse_arg(av) != 1 || parse_last_arg(av) != 1)
		return (1);
	if (init_data_struct(&i, av) == 0)
	{
		fprintf(stderr, "value must be > 0\n");
		return (1);
	}
	if (init_simulation(&i) == 0)
	{
		fprintf(stderr, "init failed\n");
		return (1);
	}
	cleanup(&i);
	return (0);
}
