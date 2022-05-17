/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:25:27 by lunovill          #+#    #+#             */
/*   Updated: 2022/04/29 07:25:34 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *error)
{
	if (ft_strcmp(error, "pipex") == 0)
		ft_putstr_fd("pipex: command not found: ", 2);
	else
		perror(error);
	return (-1);
}
