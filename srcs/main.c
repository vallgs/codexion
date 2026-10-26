/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:17:17 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/26 12:36:55 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codex.h"

int	main(int ac, char **av)
{
	t_data	i;
	t_coder	coder;

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
	pthread_mutex_init(&i.print_mutex, NULL);   // un mutex doit être initialisé avant usage
	pthread_mutex_init(&i.stop_mutex, NULL);
	i.stop = false;                              // sinon stop contient n'importe quoi
	i.start_time = get_time_ms();                // le « temps 0 » de la simulation
	coder.id = 1;
	coder.data = &i;                             // le coder pointe vers LA struct de main
	print_log(&coder, "is compiling");
	usleep(200000);                              // 200 000 µs = 200 ms
	print_log(&coder, "is debugging");
	pthread_mutex_destroy(&i.print_mutex);      // tout mutex initialisé doit être détruit
	pthread_mutex_destroy(&i.stop_mutex);

	return (0);
}
