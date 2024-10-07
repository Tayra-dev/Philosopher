/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:02:22 by hle-roi           #+#    #+#             */
/*   Updated: 2024/08/05 10:13:39 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (((tv.tv_usec / 1000) + (tv.tv_sec * 1000)) - data->start_time);
}

void	print_log(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%ld %d %s\n", get_time(philo->data), philo->id, msg);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_usleep(size_t num, t_data *data)
{
	size_t	start;

	start = get_time(data);
	while ((get_time(data) - start) < num)
		usleep(500);
}
