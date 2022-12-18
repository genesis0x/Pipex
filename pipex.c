/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:26 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/18 07:18:00 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/fcntl.h>
#include <sys/unistd.h>


void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int	status;

	if (ac != 5)
	{
		ft_dprintf(2, "Usage: infile cmd1 cmd2 outfile");
		exit(1);
	}
	// if (access(av[1], F_OK) < 0)
	// {
	// 	//ft_dprintf(2, "pipex: %s: No such file or directory\n", av[1]);
	// 	exit(0);
	// }
	pipex.infile = open(av[1], O_RDWR | O_CREAT, 0644);
	// if (access(av[1], F_OK) < 0){
	// 	ft_dprintf(2, "pipex: %s: No such file or directory\n", av[1]);
	// 	exit(0);
	// }
	if (access(av[1], R_OK | W_OK) < 0)
	{
	 	ft_dprintf(2, "pipex: %s: permission denied\n", av[1]);
	 	exit(0);
	}
	pipex.outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (access(av[4], W_OK) < 0)
	{
		ft_dprintf(2, "pipex: %s: permission denied\n", av[4]);
		exit(0);
	}
	if (pipe(pipex.tube) < 0)
		ft_dprintf(2, "Pipe");
	if ((pipex.paths = getenv("PATH")) == NULL) {
		//dprintf(2, "None\n");
        exit(0);
    }
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	if ((pipex.pid1 = fork()) < 0)
		exit(0);
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	else
		second_child(pipex, av, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	ft_free(&pipex, 'p');
	return (0);
}
