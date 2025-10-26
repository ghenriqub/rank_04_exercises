/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:51:59 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/19 16:59:52 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allowed functions: pipe, fork, dup2, execvp, close, exit

write the following function:

	int	ft_popen(const char file, charconst argv[], char type)

The function must launch the executable file with the arguments argv (using execvp).
If the type if 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

example:

int main()
{
int main() {
    int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');

    charline;
    while(line = get_next_line(fd))
        ft_putstr(line);
}

Hint: Do not leak file descriptors!
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	ft_popen(const char *file, char const *argv[], int type)
{
	int	fd[2];
	pid_t	pid;

	if(!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				exit (-1);
		}
		else
		{
			if (dup2(fd[0], STDIN_FILENO) < 0)
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
