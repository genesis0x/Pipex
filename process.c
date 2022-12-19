/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:57:42 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/19 12:16:22 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(t_pipex *pipex, char c)
{
	int	i;

	i = 0;
	if (c == 'p')
		close_pipes(pipex);
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
	return 1;
}
char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = -1;
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (cmd[0] == '.')
		{
			if (check_cmd(cmd) == 1)
				return (cmd);
		}
		else
		{
			cmd = ft_strrchr(cmd, '/');
			if (ft_strrchr(cmd, '/') == NULL)
				return (0);
		}
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

void	child(t_pipex pipex, char **av, char **env)
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
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	dup2(pipex.infile, 0);
	pipex.cmds_args = ft_split(av[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'c');
		ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmds_args, env);
	exit(1);
}

void	parent(t_pipex pipex, char **av, char **env)
{
	pipex.outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(av[4], W_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[4]);
		exit(1);
	}
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	pipex.cmds_args = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'p');
		ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmds_args, env);
	exit(1);
}
