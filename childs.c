/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:57:42 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/17 21:36:49 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
// int main(int ac, char **av, char **envp){
// 	t_pipex pipex;
// 	pipex.paths = getenv("PATH");
// 	printf("paths value :%s\n", pipex.paths);
// 	pipex.cmd_paths = ft_split(pipex.paths, ':');
// 	printf("%s\n", pipex.paths);
// 	printf("%s", get_cmd(pipex.cmd_paths, "cat"));
// 	return 0;
// }
void	first_child(t_pipex pipex, char *av[], char *envp[])
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmds_args = ft_split(av[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'c');
		ft_dprintf(2, "Pipex: command not found: %s\n", pipex.cmds_args[0]);
		exit(0);
	}
	execve(pipex.cmd, pipex.cmds_args, envp);
	exit(127);
}

void	second_child(t_pipex pipex, char *av[], char *envp[])
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmds_args = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmds_args[0]);
	if (!pipex.cmd)
	{
		ft_free(&pipex, 'c');
		ft_dprintf(2, "Pipex: command not found: %s\n", pipex.cmds_args[0]);
		exit(0);
	}
	execve(pipex.cmd, pipex.cmds_args, envp);
	exit(127);
}
