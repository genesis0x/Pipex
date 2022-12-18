/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:57:42 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/18 11:54:16 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	ft_free(t_pipex *pipex, char c)
{
	int	i;

	i = 0;
	if (c == 'p')
	{
		close(pipex->infile);
		close(pipex->outfile);
	}
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int i = -1;

	while (cmd[++i]){
		if (cmd[i] == '/')
			cmd = ft_strrchr(cmd, '/');
		if (ft_strrchr(cmd, '/') == NULL)
			break;
	}
	while (*paths)
	{
		//printf("paths value :%s\n", *paths);
		tmp = ft_strjoin(*paths, "/");
		//printf("tmp value: %s\n", tmp);
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}
// int main(int ac, char **av, char **envp){
// 	t_pipex pipex;
// 	pipex.paths = getenv("PATH");
// 	pipex.cmds_args = ft_split("awk '{count++} END {print count}'", ' ');
// 	printf("pipex.cmds_args: %s\n", *pipex.cmds_args);
// 	printf("paths value :%s\n", pipex.paths);
// 	pipex.cmd_paths = ft_split(pipex.paths, ':');
// 	//printf("%s\n", pipex.paths);
// 	printf("%s", get_cmd(pipex.cmd_paths, pipex.cmds_args[0]));
// 	return (0);
// }

void	first_child(t_pipex pipex, char **av, char **envp)
{
	pipex.infile = open(av[1], O_RDONLY);
	if (access(av[1], F_OK) < 0){
		ft_dprintf(2, "pipex: %s: No such file or directory\n", av[1]);
		exit(0);
	}
	if (access(av[1], R_OK) < 0)
	{
	 	ft_dprintf(2, "pipex: %s: permission denied\n", av[1]);
	 	exit(126);
	}
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmds_args = ft_split(av[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'c');
		ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmds_args, envp);
		printf("%s\n", strerror(errno));
	exit(127);
}

void	second_child(t_pipex pipex, char **av, char **envp)
{
	pipex.outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (access(av[4], W_OK | R_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[4]);
		exit(127);
	}
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmds_args = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'p');
		ft_dprintf(2, "pipex: %s: command not found\n", pipex.cmds_args[0]);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmds_args, envp);
		//printf("%s\n", strerror(errno));
	exit(127);
}
