/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 22:47:15 by tulipe            #+#    #+#             */
/*   Updated: 2022/04/21 11:37:59 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*msg_str = NULL;

static	char	make_char(int *byte)
{
	int		i;
	char	c;

	i = 7;
	c = 0;
	if (byte[0] == 1)
		c = 1;
	while (i > 0)
	{
		c += 2 * (2 * i);
		i--;
	}
	return (c);
}

static	char	*ft_str_join(char *s1, int *byte)
{
	char	*join;
	int		i;

	join = malloc((ft_strlen(s1) + 2) * sizeof(*join));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = make_char(byte);
	i++;
	join[i] = '\0';
	free(s1);
	return (join);
}

void	handler(int sigtype)
{
	static	int	byte[8] = {0};
	static	int	i = 0;

	if (i < 8)
	{
		if (sigtype == SIGUSR1)
			byte[i] = 0;
		else if (sigtype == SIGUSR2)
			byte[i] = 1;
		i++;
	}
	else
	{
		msg_str = ft_str_join(msg_str, byte);
		if (!msg_str)
			return ;
		if (!make_char(byte))
		{
			write(1, msg_str, ft_strlen(msg_str));
			msg_str = ft_bzero(msg_str, ft_strlen(msg_str));
		}
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	action;

	(void)argc;
	(void)argv;
	pid = getpid();
	ft_printf("%d\n", pid);
	action.sa_handler = handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1);
}
