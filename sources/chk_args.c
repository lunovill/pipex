/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:24:24 by lunovill          #+#    #+#             */
/*   Updated: 2022/04/29 07:24:47 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	chk_args(t_arg arg, unsigned int i)
{
	char	**cmd;
	char	*path;

	if (arg.path == -1)
		return (-1);
	cmd = ft_ppsplit(arg.cmds[i]);
	path = ft_path(cmd[0], arg.env);
	if (!path)
		return (ft_ftab(cmd), -1);
	ft_ftab(cmd);
	free(path);
	return (0);
}
