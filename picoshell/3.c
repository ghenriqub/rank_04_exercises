/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:19:51 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/26 13:23:17 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{
	int		fd[2];
	pid_t	pid;
	int		i = 0;
	int		in = 0;
	int		ret = 0;
	int		status;

	while (cmds[i])
	{

	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ret = 1;
		else if (!WIFEXITED(status))
			ret = 1;
	}
	return (ret);
}
