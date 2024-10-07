/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:49:08 by hle-roi           #+#    #+#             */
/*   Updated: 2024/08/05 14:04:14 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->fork)
		return (1);
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
			return (1);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	int	mutex;

	mutex = 1;
	data->end = 0;
	data->nbr_death = 0;
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = 0;
	if (argv[5])
	{
		data->nbr_eat = ft_atoi(argv[5]);
		if (data->nbr_eat <= 0)
			return (1);
	}
	else
		data->nbr_eat = -1;
	if (data->nbr_philo > 0)
		mutex = init_mutex(data);
	return (mutex || data->nbr_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| data->nbr_eat == 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 5 || argc == 6) || init_data(&data, argv))
	{
		printf("invalid arguments\n");
		return (-1);
	}
	if (philo(&data))
		return (free(data.fork), -1);
	return (0);
}
