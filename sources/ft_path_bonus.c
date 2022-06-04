/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 04:57:13 by lunovill          #+#    #+#             */
/*   Updated: 2022/06/01 04:57:22 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**tab_path(char *cmd, char *env[])
{
	unsigned int	i;
	char			**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) && env[i])
		i++;
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return (NULL);
	i = 0;
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		return (ft_ftab(path), NULL);
	while (path[i])
	{
		path[i] = ft_strjoinf(path[i], cmd, 1);
		i++;
	}
	free(cmd);
	return (path);
}

char	*ft_path(char *cmd, char *env[])
{
	unsigned int	i;
	char			*s;
	char			**path;

	if (access(cmd, F_OK) != -1)
		return (ft_strdup(cmd));
	i = 0;
	path = tab_path(cmd, env);
	while (path[i])
	{
		if (access(path[i++], F_OK) == 0)
		{
			s = ft_strdup(path[--i]);
			ft_ftab(path);
			return (s);
		}
	}
	if (path)
		ft_ftab(path);
	return (NULL);
}
