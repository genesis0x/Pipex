/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:57:42 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 10:30:12 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_free(t_pipex *pipex, char c)
{
	int	i;

	i = 0;
	if (c == 'p')
		close_pipes(pipex);
	while (pipex->cmds_paths[i])
	{
		free(pipex->cmds_paths[i]);
		i++;
	}
	free(pipex->cmds_paths);
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

void	child(t_pipex pipex, char **av, char **env)
{
	pipex.in = open(av[1], O_RDONLY | O_CREAT, 0644);
	if (access(av[1], F_OK) < 0)
	{
		dprintf(2, "pipex: %s: No such file or directory\n", av[1]);
		exit(0);
	}
	if (access(av[1], R_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[1]);
		exit(0);
	}
	pipex.cmds_idx = 3;
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	dup2(pipex.in, 0);
	pipex.cmds_args = ft_split(av[pipex.cmds_idx++], ' ');
	pipex.cmd = get_cmd(pipex.cmds_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'c');
		ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmds_args, env);
	exit(1);
}

void	parent(t_pipex pipex, int ac, char **av, char **env)
{
	pipex.out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(av[ac - 1], W_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[ac - 1]);
		exit(1);
	}
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.out, 1);
	pipex.cmds_args = ft_split(av[ac - 2], ' ');
	if (pipex.cmds_args[0] == NULL)
		exit(1);
	pipex.cmd = get_cmd(pipex.cmds_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'p');
		ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmds_args, env);
	exit(1);
}
