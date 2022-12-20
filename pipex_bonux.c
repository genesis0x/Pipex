/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:38:52 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/20 16:13:46 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonux.h"

/*void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}*/

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

void    create_pipes(t_pipex pipex)
{
    int i;

    i = 0;
    while (i < pipex.cmds_nb)
    {
        pipe(pipex.pipe);
        i++;
    }
}

void    close_pipes(t_pipex pipex)
{
    int i;

    i = 0;
    while (i < pipex.cmds_nb)
    {
        close(pipex.pipe[i]);
        i++;
    }
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (ac != 5)
	{
		ft_dprintf(2, "Bad Usage");
		return (1);
	}
	pipex.outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    pipex.cmds_nb = ac - 3;
    pipex.pipes_nb = 2 * (pipex.cmds_nb - 1);
    pipex.pipe = (int*)malloc(sizeof(int) * pipex.pipes_nb);
	create_pipes(pipex);
    /*if (pipe(pipex.pipe) < 0)
	{
		ft_dprintf(2, "Pipe failed");
		return (1);
	}*/
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	child(pipex, av, envp);
    /*if (ft_fork(pipex, av, envp) < 0)
	{
		ft_dprintf(2, "Fork failed");
		return (1);
	}*/
	close_pipes(pipex);
	waitpid(-1, &status, 0);
	//ft_free(&pipex, 'p');
	return (0);
}
