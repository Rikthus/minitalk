/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 22:47:15 by tulipe            #+#    #+#             */
/*   Updated: 2022/04/18 03:17:31 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void    handler(int sigtype)
{
    static  char    *str;
    static  int     i = 0;
    
    if (i < 8)
    {
        if (sigtype == SIGUSR1)
        {

        }
        else if (sigtype == SIGUSR2)
        {

        }
        i++;
    }
    else
        i = 0;
    if (str[i] == '\0')
        write(1, str, ft_strlen(str));
}

int main(int argc, char **argv)
{
    pid_t               pid;
    struct sigaction    action;

    pid = getpid();
    ft_printf("%d\n", pid);
    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
        sleep(42);
}