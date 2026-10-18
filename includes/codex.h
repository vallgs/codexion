/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallangl <vallangl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:20:29 by vallangl          #+#    #+#             */
/*   Updated: 2026/10/18 18:54:18 by vallangl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;

struct s_data
{
	int		number_of_coder;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		time_to_burnout;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
};

struct s_coder
{
	pthread_t	thread;
	int			id;
	pthread_mutex_t		*dongle_tab;
	pthread_mutex_t		message;
	pthread_mutex_t		burnout_mutex;
	int					burnout;
	pthread_mutex_t		monitor;
};

typedef enum e_state
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNOUT
}	t_state;

//utils
int	ft_is_digit(char arg);
int	ft_atoi(const char *str);
int	ft_strcmp(char *c1, char *c2);
int	ft_limit(const char *n);
int	ft_is_valid_number(char *s);

//parsing
int	parse_arg(char **arg);
int	parse_last_arg(char **arg);

//init
int	init_data_struct(t_data *dt, char **arg);
