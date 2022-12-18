/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:26 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/18 16:34:44 by hahadiou         ###   ########.fr       */
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
		return (1);
	}
	pipe(pipex.tube);
		//ft_dprintf(2, "Pipe");
	if ((pipex.paths = getenv("PATH")) == NULL) {
		pipex.paths = "/Users/hahadiou/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/hahadiou/.fzf/bin";
    }
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
		//return (1);
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
