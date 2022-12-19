/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:26 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/19 10:51:12 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <sys/fcntl.h>
#include <sys/unistd.h>


void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

char	*find_path(char **env)
{
	if (*env == NULL)
		return ("/Users/hahadiou/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/hahadiou/.fzf/bin");
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int	status;

	if (ac != 5)
	{
		ft_dprintf(2, "Bad Usage");
		return (1);
	}
	if (pipe(pipex.pipe) < 0)
		return 1;
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
		//return (1);
	if (pipex.pid1 == 0)
		child(pipex, av, envp);
	else
		parent(pipex, av, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, &status, 0);
	ft_free(&pipex, 'p');
	return (0);
}
