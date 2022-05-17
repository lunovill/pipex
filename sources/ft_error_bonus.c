/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:40 by lunovill          #+#    #+#             */
/*   Updated: 2022/05/16 20:04:45 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_error(char *error)
{
	if (ft_strcmp(error, "pipex") == 0)
		ft_putstr_fd("pipex: command not found: ", 2);
	else
		perror(error);
	return (-1);
}
