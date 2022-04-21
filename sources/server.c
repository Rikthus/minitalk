/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 22:47:15 by tulipe            #+#    #+#             */
/*   Updated: 2022/04/21 09:28:55 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*msg_str = "\0";

static	char	*ft_str_join(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*join));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	if (*s1 != '\0')
		free(s1);
	ft_printf("%s\n", join);
	return (join);
}

void	handler(int sigtype)
{
	static	char	c = '\0';
	static	int		i = 0;

	if (i < 8)
	{
		c = (int)c << 1;
		if (sigtype == SIGUSR1)
			c = c^0;
		else if (sigtype == SIGUSR2)
			c = c^1;
		i++;
	}
	else
	{

		msg_str = ft_str_join(msg_str, &c);
		if (!msg_str)
			return ;
		c = (int)c >> 7;
		if (i == 8 && c == '\0')
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
