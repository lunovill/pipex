/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_father_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:29:54 by lunovill          #+#    #+#             */
/*   Updated: 2022/05/16 20:03:12 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pid_father(t_arg arg, int *prevfd, int pipefd[2], unsigned int i)
{
	if (i == 0)
	{
		*prevfd = dup(pipefd[0]);
		close (pipefd[0]);
		close(pipefd[1]);
		if (*prevfd == -1)
			return (ft_error("dup"));
	}
	else if (i == arg.size - 1)
		close(*prevfd);
	else
	{
		close(*prevfd);
		*prevfd = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		if (*prevfd == -1)
			return (ft_error("dup"));
	}
	return (0);
}
