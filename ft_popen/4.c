/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:21:08 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/26 14:28:22 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	ft_popen(const char *file, char const *argv[], int type)
{
	int		fd[2];
	pid_t	pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close (fd[1]);
		close (fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], 1) < 0)
				exit (-1);
		}
		else
		{
			if (dup2(fd[0], 0) < 0)
				exit (-1);
		}
		close (fd[0]);
		close (fd[1]);
		execvp(file, argv);
		exit (-1);
	}
	if (type == 'r')
	{
		close (fd[1]);
		return (fd[0]);
	}
	else
	{
		close (fd[0]);
		return (fd[1]);
	}
}
