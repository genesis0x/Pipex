/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:26 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/08 17:34:06 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

char	*find_path(char **env)
{
	char	*path;

	path = "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.";
	if (*env == NULL)
		return (path);
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	ft_fork(t_pipex pipex, int ac, char **av, char **envp)
{
	int	status;

	if ((pipex.pid = fork()) > -1)
	{
		if (pipex.pid == 0)
			child(pipex, av, envp);
		else
		{
			wait(&status);
			parent(pipex, ac, av, envp);
		}
	}
	else
	{
		ft_dprintf(2, "Fork failed");
		exit(1);
	}
}

void	ft_open(t_pipex pipex, char **av)
{
	pipex.infile = open(av[1], O_RDONLY);
	if (access(av[1], F_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: No such file or directory\n", av[1]);
		exit(0);
	}
	if (access(av[1], R_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[1]);
		exit(0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
	{
		ft_dprintf(2, "Bad Usage");
		return (1);
	}
	if (pipe(pipex.pipe) < 0)
	{
		ft_dprintf(2, "Pipe failed");
		return (1);
	}
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.i = 0;
	ft_open(pipex, av);
	while (++(pipex.i) < ac - 3)
		ft_fork(pipex, ac, av, envp);
	close_pipes(&pipex);
	ft_free(&pipex, 'p');
	return (0);
}
