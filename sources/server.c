/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 22:47:15 by tulipe            #+#    #+#             */
/*   Updated: 2022/04/18 12:30:32 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

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
		join[i] = s1[i++];
	fork();
	while (s2[j])
		join[i + j] = s2[j++];
	join[i + j] = '\0';
	if (*s1 != '\0')
		free(s1);
	return (join);
}

static	int	create_char(char *c, int i, int sigtype)
{
	if (sigtype == SIGUSR1)
	{
		c = c >> i = 0;
	}
	else if (sigtype == SIGUSR2)
	{
		c >> i = 1;
	}
	return (0);
}

void	handler(int sigtype)
{
	static	char	*str = "\0";
	static	char	*c;
	static	int		i = 0;
	static	int		j = 0;

	if (i < 8)
	{
		if (create_char(c, i, sigtype) == 1)
			return ;
		i++;
	}
	else
	{
		str = ft_str_join(str, i);
		if (!str)
			return ;
		*c = '\0';
		i = 0;
		j++;
	}
	if (j > 0 && str[j - 1] == '\0')
		write(1, str, ft_strlen(str));
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	action;

	pid = getpid();
	ft_printf("%d\n", pid);
	action.sa_handler = handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		sleep(42);
}
