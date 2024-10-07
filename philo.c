/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:26:00 by hle-roi           #+#    #+#             */
/*   Updated: 2024/08/05 14:06:32 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		philo[i].nbr_meal = 0;
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].left_fork = &data->fork[i];
		if (i)
			philo[i].right_fork = philo[i - 1].left_fork;
		philo[i].last_meal = 0;
	}
	philo[0].right_fork = philo[i - 1].left_fork;
	return (0);
}

void	clear_thread(t_data *data, t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->eat_lock);
	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
	}
	free(philo);
	free(data->fork);
}

int	philo(t_data *data)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!philo || init_philo(philo, data))
		return (-1);
	i = -1;
	data->start_time = get_time(data);
	while (++i < data->nbr_philo)
	{
		philo->last_meal = get_time(philo->data);
		if (pthread_create(&philo[i].thread_id, NULL,
				thread_run, &philo[i]) == -1)
			return (-1);
	}
	check_thread(philo);
	clear_thread(data, philo);
	return (0);
}
