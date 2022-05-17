/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <lunovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:45:04 by lunovill          #+#    #+#             */
/*   Updated: 2022/05/16 21:45:52 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_arg	arg_init(int argc, char **argv, char **env)
{
	t_arg	arg;

	arg.infile = argv[1];
	if (access(argv[1], F_OK))
	{
		ft_putstr_fd("pipex: no such file or directory:", 2);
		ft_putstr_fd(arg.infile, 2);
		ft_putchar_fd('\n', 2);
		arg.infile = NULL;
	}
	arg.outfile = argv[argc - 1];
	if (ft_strcmp(arg.outfile, "") == 0)
	{
		ft_putstr_fd("pipex: no such file or directory:\n", 2);
		arg.outfile = NULL;
	}
	if (!arg.infile && !arg.outfile)
		exit (1);
	arg.cmds = argv + 2;
	arg.env = env;
	arg.size = argc - 3;
	return (arg);
}

int	main(int argc, char *argv[], char *env[])
{
	t_arg			arg;
	unsigned int	i;

	if (argc != 5)
	{
		ft_putstr_fd("usage :\t./pipex infile cmd1 cmd2 outfile\n", 2);
		return (-1);
	}
	if (!env[0])
		return (0);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	arg = arg_init(argc, argv, env);
	if (!env[i])
		arg.path = -1;
	else
		arg.path = 0;
	return (pipex(arg));
}
