/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:20:24 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 10:30:01 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	heredoc(char *delimiter)
{
	t_pipex	pipex;
	char	*line;
	int		status;

	pipe(pipex.pipe);
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		while (1)
		{
			ft_dprintf(0, "heredoc> ");
			line = get_next_line(0);
			if (ft_strnstr(line, delimiter, ft_strlen(delimiter)))
				exit(0);
			ft_dprintf(pipex.pipe[1], line, ft_strlen(line));
		}
	}
	else
	{
		dup2(pipex.pipe[0], 0);
		waitpid(pipex.pid, &status, 0);
	}
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
}

void	args(int ac, char **av)
{
	if (ac < 5)
	{
		ft_dprintf(2, "Bad Usage");
		exit(1);
	}
	if (!(ft_strncmp(av[1], "here_doc", 8)))
		heredoc(av[2]);
}
