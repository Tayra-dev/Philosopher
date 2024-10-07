/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:46:22 by hle-roi           #+#    #+#             */
/*   Updated: 2024/08/04 15:37:15 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# define EAT	" is eating"
# define SLEEP	" is sleeping"
# define FORK	" has taken a fork"
# define THINK	" is thinking"

typedef struct s_data
{
	int				end;
	int				nbr_death;
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_eat;
	long int		start_time;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				nbr_meal;
	long int		last_meal;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
}	t_philo;

int			ft_atoi(const char *str);
int			philo(t_data *data);
void		*thread_run(void *param);
long int	get_time(t_data *data);
void		print_log(t_philo *philo, char *msg);
void		ft_usleep(size_t num, t_data *data);
void		check_thread(t_philo *philo);

#endif