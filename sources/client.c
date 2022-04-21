/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:29:48 by tulipe            #+#    #+#             */
/*   Updated: 2022/04/21 14:30:14 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_signal(pid_t server_pid, char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (j < 8)
		{
			kill(server_pid, SIGUSR1 + ((str[i] >> j) & 1));
			j++;
			usleep(100);
		}
		i++;
	}
	j = 0;
	while (j < 8)
	{
		kill(server_pid, SIGUSR1);
		usleep(100);
		j++;
	}
}

int main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	send_signal(ft_atoi(argv[1]), argv[2]);
}
