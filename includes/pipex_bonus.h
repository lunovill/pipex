/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 07:16:32 by lunovill          #+#    #+#             */
/*   Updated: 2022/06/01 05:07:01 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_arg	t_arg;
struct					s_arg
{
	int		path;
	int		doc;
	char	*limit;
	char	*infile;
	char	*outfile;
	char	**cmds;
	char	**env;
	size_t	size;
};

char	*ft_path(char *cmd, char *env[]);
char	**ft_ppsplit(const char *s);
int		chk_args(t_arg arg, unsigned int i);
int		ft_error(char *error);
int		pid_father(t_arg arg, int *prevfd, int pipefd[2], unsigned int i);
int		pid_child(t_arg arg, int prevfd, int pipefd[2], unsigned int i);
int		pipex(t_arg arg);

#endif
