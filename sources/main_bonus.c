/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <lunovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:45:04 by lunovill          #+#    #+#             */
/*   Updated: 2022/06/02 21:25:00 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	here_doc(char *limit)
{
	int		fd;
	char	*tmp;

	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_error("open"), -1);
	ft_putchar_fd('>', STDIN_FILENO);
	tmp = NULL;
	if (get_next_line(STDIN_FILENO, &tmp, 1) == -1)
		return (-1);
	while (ft_strncmp(limit, tmp, ft_strlen(limit)))
	{
		ft_putstr_fd(tmp, fd);
		ft_putchar_fd('\n', fd);
		free(tmp);
		ft_putchar_fd('>', STDIN_FILENO);
		if (get_next_line(STDIN_FILENO, &tmp, 1) == -1)
			return (-1);
	}
	get_next_line(STDIN_FILENO, &tmp, 0);
	free(tmp);
	close (fd);
	return (0);
}

static t_arg	arg_init(int argc, char **argv, char **env)
{
	t_arg	arg;

	arg.limit = NULL;
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

static t_arg	arg_init_hd(int argc, char **argv, char **env)
{
	t_arg	arg;

	arg.limit = argv[2];
	if (here_doc(arg.limit) == -1)
		exit (127);
	arg.infile = "/tmp/here_doc";
	arg.outfile = argv[argc - 1];
	if (ft_strcmp(arg.outfile, "") == 0)
	{
		ft_putstr_fd("pipex: no such file or directory:\n", 2);
		arg.outfile = NULL;
	}
	if (!arg.infile && !arg.outfile)
		exit (1);
	arg.cmds = argv + 3;
	arg.env = env;
	arg.size = argc - 4;
	return (arg);
}

int	main(int argc, char *argv[], char *env[])
{
	t_arg			arg;
	unsigned int	i;

	if (argc < 5)
		return (ft_putstr_fd("usage :\t./pipex [here_doc [LIMITER] | infile]",
				2), ft_putstr_fd(" cmd1 cmd2 ... outfile\n", 2), -1);
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
		return (ft_putstr_fd("usage :\t./pipex here_doc LIMITER", 2),
			ft_putstr_fd(" cmd1 cmd2 ... outfile\n", 2), -1);
	if (!env[0])
		return (0);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (ft_strcmp(argv[1], "here_doc") == 0)
		arg = arg_init_hd(argc, argv, env);
	else
		arg = arg_init(argc, argv, env);
	if (!env[i])
		arg.path = -1;
	else
		arg.path = 0;
	return (pipex(arg));
}
