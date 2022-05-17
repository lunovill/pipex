/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_args_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:18 by lunovill          #+#    #+#             */
/*   Updated: 2022/05/16 20:04:22 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
