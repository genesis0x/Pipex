/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:26 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/19 17:47:29 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	if (ac != 5)
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
	pipex.pid = fork();
    if (pipex.pid < 0)
    {
        ft_dprintf(2, "Fork failed");
        return (1);
    }
	if (pipex.pid == 0)
		child(pipex, av, envp);
	else
		parent(pipex, av, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid, &status, 0);
	ft_free(&pipex, 'p');
	return (0);
}
