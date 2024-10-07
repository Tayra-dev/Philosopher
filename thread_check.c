/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:28:08 by hle-roi           #+#    #+#             */
/*   Updated: 2024/08/04 15:24:19 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_complete(t_philo *philo)
{
	int	complete;
	int	i;

	complete = 1;
	i = -1;
	if (philo[0].data->nbr_eat == -1)
		return (0);
	while (++i < philo[0].data->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].data->eat_lock);
		if (philo[i].nbr_meal < philo[0].data->nbr_eat)
			complete = 0;
		pthread_mutex_unlock(&philo[i].data->eat_lock);
	}
	return (complete);
}

int	check_death(t_philo *philo)
{
	long int	time;
	int			i;

	i = -1;
	while (++i < philo[0].data->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].data->eat_lock);
		time = get_time(philo[i].data) - philo[i].last_meal;
		if (time >= philo[i].data->time_to_die)
		{
			pthread_mutex_lock(&philo[i].data->write);
			printf("%ld %d died\n", get_time(philo[i].data), philo[i].id);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].data->eat_lock);
	}
	return (0);
}

void	check_thread(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo) || check_complete(philo))
			break ;
	}
}
