/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:53:47 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/20 16:13:23 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonux.h"
#include <stdio.h>
#include <unistd.h>

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	// if (c == 'p')
	// 	close_pipes(t_pipex);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

int	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) < 0)
	{
		ft_dprintf(2, "No Such file: %s\n", cmd);
		exit(126);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_dprintf(2, "Permissions: %s\n", cmd);
		exit(126);
	}
	return (1);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd[0] == '.')
		if (check_cmd(cmd) == 1)
			return (cmd);
	if (cmd[0] == '/')
	{
		cmd = ft_strrchr(cmd, '/');
		if (ft_strrchr(cmd, '/') == NULL)
			return (0);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	get_infile(t_pipex pipex, char **av)
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

void	get_outfile(t_pipex pipex, char **av)
{
	pipex.outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(av[4], W_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[4]);
		exit(1);
	}
}

void	ft_dup2(int i, int j)
{
	dup2(i, 1);
	dup2(j, 0);
}

void	child(t_pipex pipex, char **av, char **env)
{
	get_infile(pipex, av);
	get_outfile(pipex, av);
	pipex.pid = fork();
	if (!pipex.pid)
	{
		if (pipex.i == 0)
			ft_dup2(pipex.infile, pipex.pipe[1]);
		else if (pipex.i == pipex.cmds_nb - 1)
			ft_dup2(pipex.pipe[2 * pipex.i - 2], pipex.outfile);
		else
		 	ft_dup2(pipex.pipe[2 * pipex.i - 2], pipex.pipe[2 * pipex.i + 1]);
		close_pipes(pipex);
		pipex.cmds_args = ft_split(av[2], ' ');
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
		if (!pipex.cmd)
		{
			ft_free(&pipex);
			ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
			exit(127);
		}
		execve(pipex.cmd, pipex.cmds_args, env);
		exit(1);
	}
}

void	parent(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	pipex.cmds_args = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex);
		ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmds_args, env);
	exit(1);
}
