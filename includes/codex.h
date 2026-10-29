/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:20:29 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/29 14:38:31 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEX_H
# define CODEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data		t_data;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_request	t_request;

typedef enum e_sched
{
	FIFO,
	EDF
}	t_sched;

struct s_data
{
	int				number_of_coder;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				time_to_burnout;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_sched			scheduler;
	long			start_time;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		monitor;
	pthread_mutex_t	print_mutex;
};

struct s_coder
{
	pthread_t		thread;
	int				id;
	t_dongle		*left;
	t_dongle		*right;
	long			last_compile_start;
	int				compile_count;
	pthread_mutex_t	state_mutex;
	t_data			*data;
};

struct s_request
{
	t_coder	*coder;
	long	key;
	long	ticket;
};

struct s_dongle
{
	pthread_mutex_t	mutex;
	long			available_at;
	bool			taken;
	long			next_ticket;
	t_request		queue[2];
	int				size;
};

//utils
int		ft_is_digit(char arg);
int		ft_atoi(const char *str);
int		ft_strcmp(char *c1, char *c2);
int		ft_limit(const char *n);
int		ft_is_valid_number(char *s);

//time
long	get_time_ms(void);
void	ft_sleep(t_data *data, long ms);

//log
bool	is_stopped(t_data *data);
void	print_log(t_coder *coder, char *msg);

//parsing
int		parse_arg(char **arg);
int		parse_last_arg(char **arg);

//init
int		init_data_struct(t_data *dt, char **arg);
int		init_alloc(t_data *data);
int		init_dongles(t_data *data);
int		init_coders(t_data *data);
int		init_simulation(t_data *data);

//thread
void	init_start_times(t_data *data);
void	join_coders(t_data *data, int count);
int		abort_simulation(t_data *data, int count);
int		start_simulation(t_data *data);

//clean
void	cleanup(t_data *data);

//coder
void	do_compile(t_coder *coder);
void	*single_coder(t_coder *coder);
void	*coder_routine(void *arg);

//monitor
void	set_stop(t_data *data);
bool	check_burnout(t_data *data);
bool	check_all_done(t_data *data);
void	*monitor_routine(void *arg);

//heap
bool	request_before(t_request *a, t_request *b);
void	swap_request(t_request *a, t_request *b);
void	heap_push(t_dongle *d, t_request request);
void	heap_pop(t_dongle *d);
bool	is_my_turn(t_coder *coder, t_dongle *d);

//dongle
void	order_dongles(t_coder *coder, t_dongle **first, t_dongle **second);
void	request_dongles(t_coder *coder);
bool	try_take(t_coder *coder);
bool	take_dongles(t_coder *coder);
void	release_dongles(t_coder *coder);

#endif
