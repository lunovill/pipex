/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_child_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:27:58 by lunovill          #+#    #+#             */
/*   Updated: 2022/05/16 20:02:54 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	excmd_first(t_arg arg, int pipefd[2])
{
	int		fd;
	char	**cmd;
	char	*path;

	close(pipefd[0]);
	fd = open(arg.infile, O_RDONLY);
	if (fd == -1)
		return (close(pipefd[1]), ft_error("open"));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(pipefd[1]), close(fd), ft_error("dup2"));
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (close(pipefd[1]), ft_error("dup2"));
	close(pipefd[1]);
	cmd = ft_ppsplit(arg.cmds[0]);
	path = ft_path(cmd[0], arg.env);
	if (execve(path, cmd, arg.env) == -1)
		return (free(path), ft_ftab(cmd), ft_error("execve"));
	return (0);
}

static int	excmd_between(t_arg arg, int prevfd, int pipefd[2], unsigned int i)
{
	char	**cmd;
	char	*path;

	close(pipefd[0]);
	if (dup2(prevfd, STDIN_FILENO) == -1)
		return (close(prevfd), close(pipefd[1]), ft_error("dup2"));
	close(prevfd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (close(pipefd[1]), ft_error("dup2"));
	close(pipefd[1]);
	cmd = ft_ppsplit(arg.cmds[i]);
	path = ft_path(cmd[0], arg.env);
	if (execve(path, cmd, arg.env) == -1)
		return (free(path), ft_ftab(cmd), ft_error("execve"));
	return (0);
}

static int	excmd_last(t_arg arg, int prevfd)
{
	int		fd;
	char	**cmd;
	char	*path;

	fd = open(arg.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (close(prevfd), -1);
	if (dup2(prevfd, STDIN_FILENO) == -1)
		return (close(prevfd), close(fd), ft_error("dup2"));
	close(prevfd);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ft_error("dup2"));
	close(fd);
	cmd = ft_ppsplit(arg.cmds[arg.size - 1]);
	path = ft_path(cmd[0], arg.env);
	if (execve(path, cmd, arg.env) == -1)
		return (free(path), ft_ftab(cmd), ft_error("execve"));
	return (0);
}

int	pid_child(t_arg arg, int prevfd, int pipefd[2], unsigned int i)
{
	if (i == 0)
	{
		if (chk_args(arg, i) == -1)
			return (close(pipefd[0]), close(pipefd[1]), exit(127), -1);
		excmd_first(arg, pipefd);
		exit (127);
	}
	else if (i == arg.size - 1)
	{
		if (chk_args(arg, i) == -1)
			return (close(prevfd), exit (127), -1);
		excmd_last(arg, prevfd);
		exit (127);
	}
	else
	{
		if (chk_args(arg, i) == -1)
			return (close(prevfd), close(pipefd[0]),
				close(pipefd[1]), exit(127), -1);
		excmd_between(arg, prevfd, pipefd, i);
		exit (127);
	}
}
