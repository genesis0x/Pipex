/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:35:59 by hahadiou          #+#    #+#             */
/*   Updated: 2023/03/29 21:36:00 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_args(t_pipex *pipex, int ac, char **av, bool out)
{
	if (out)
	{
		pipex->parse.in = open(av[pipex->execute.cmd_idx - 1], O_RDONLY);
		if (access(av[pipex->execute.cmd_idx - 1], F_OK) < 0)
		{
			ft_dprintf(2, "pipex: %s: No such file or directory\n",
					av[pipex->execute.cmd_idx - 1]);
			exit(0);
		}
		if (access(av[pipex->execute.cmd_idx - 1], R_OK) < 0)
		{
			ft_dprintf(2, "pipex: %s: permission denied\n",
					av[pipex->execute.cmd_idx - 1]);
			exit(1);
		}
		dup2(pipex->parse.in, 0);
	}
	pipex->parse.out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(av[ac - 1], W_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[4]);
		exit(1);
	}
	dup2(pipex->parse.out, 1);
}

static char	*find_path(char **env)
{
	char	*path;

	path = strdup("/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.");
	if (*env == NULL || strncmp("PATH", *env, 4))
		return (path);
	while (strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

static void	init_paths(t_pipex *pipex, char **envp)
{
	pipex->parse.path = find_path(envp);
	pipex->parse.cmd_path = ft_split(pipex->parse.path, ':');
}

void	init(t_pipex *pipex, int ac, char **av, char **envp)
{
	init_args(pipex, ac, av, false);
	init_paths(pipex, envp);
	pipex->execute.cmd_idx = 1;
	pipex->execute.prev_pipe = 0;
}
