#include "includes/minitalk.h"

void	handler(int sigtype)
{
	static	char	c = '\0';
	static	int		i = 0;

	if (i < 8)
	{
		if (i > 0)
			c = (int)c << 7;
		else
			c = (int)c >> 1;
		if (sigtype == SIGUSR1)
			c = c^0;
		else if (sigtype == SIGUSR2)
			c = c^1;
		i++;
	}
	if (i == 8)
	{
		write(1, &c, 1);
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
	printf("%d\n", pid);
	action.sa_handler = handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1);
}
