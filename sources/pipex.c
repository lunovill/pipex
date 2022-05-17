/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:31:46 by lunovill          #+#    #+#             */
/*   Updated: 2022/05/14 02:03:35 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	error_pipe(int prevfd)
{
	if (prevfd)
		close(prevfd);
	return (ft_error("pipe"));
}

static int	error_pid(int prevfd, int pipefd[2])
{
	if (prevfd)
		close(prevfd);
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (ft_error("fork"));
}

static void	error_arg(t_arg arg, unsigned int i)
{
	char	**cmd;

	if (!arg.cmds[i] || ft_strcmp(arg.cmds[i], "") == 0)
	{
		if (!arg.infile && i == 0)
			return ;
		ft_putstr_fd("pipex: permission denied: \n", 2);
		if (i == arg.size - 1)
			exit (127);
	}
	else if (chk_args(arg, i) == -1)
	{
		cmd = ft_ppsplit(arg.cmds[i]);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		ft_ftab(cmd);
	}
}

int	pipex(t_arg arg)
{
	unsigned int	i;
	int				pipefd[2];
	int				prevfd;
	int				pid;
	int				status;

	i = -1;
	while (++i < arg.size)
	{
		if (i != arg.size - 1 && pipe(pipefd) == -1)
			return (error_pipe(prevfd));
		error_arg(arg, i);
		pid = fork();
		if (pid == -1)
			return (error_pid(prevfd, pipefd));
		else if (pid == 0)
			pid_child(arg, prevfd, pipefd, i);
		else if (pid_father(arg, &prevfd, pipefd, i) == -1)
			return (-1);
	}
	while (wait(&status) != -1)
		;
	return (WEXITSTATUS(status));
}
