/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:26 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/17 22:01:27 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	while (strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_dprintf(2, "Usage: inFile cmd1 cmd2 outFile");
		exit(127);
	}
	// if (access(av[1], F_OK) < 0)
	// {
	// 	ft_dprintf(2, "Pipex: no such file or directory: %s\n", av[1]);
	// 	exit(0);
	// }
	pipex.infile = open(av[1], O_RDONLY);
	// if (access(av[1], R_OK) < 0)
	// {
	// 	ft_dprintf(2, "Pipex: permission denied: %s\n", av[1]);
	// 	exit(127);
	// }
	pipex.outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(av[4], W_OK) < 0)
	{
		ft_dprintf(2, "Pipex: permission denied: %s\n", av[4]);
		exit(127);
	}
	if (pipe(pipex.tube) < 0)
		ft_dprintf(2, "Pipe");
	pipex.paths = getenv("PATH");
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	if((pipex.pid1 = fork()) < 0)
		exit(1);
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	if((pipex.pid2 = fork()) < 0)
		exit(1);
	if (pipex.pid2 == 0)
		second_child(pipex, av, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_free(&pipex, 'p');
	return (0);
}
