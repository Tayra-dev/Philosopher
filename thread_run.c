/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:26:57 by hle-roi           #+#    #+#             */
/*   Updated: 2024/08/05 14:00:33 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	print_log(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_log(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_log(philo, FORK);
	pthread_mutex_lock(&philo->data->eat_lock);
	print_log(philo, EAT);
	philo->nbr_meal++;
	philo->last_meal = get_time(philo->data);
	pthread_mutex_unlock(&philo->data->eat_lock);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*thread_run(void *param)
{
	t_philo			*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
		ft_usleep(60, philo->data);
	while (1)
	{
		print_log(philo, THINK);
		eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
