/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:35:50 by hahadiou          #+#    #+#             */
/*   Updated: 2023/03/29 21:35:51 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd[0] == '.')
		if (check_cmd(cmd) == 1)
			return (cmd);
	if (cmd[0] == '/')
	{
		cmd = ft_strchr(cmd, '/');
		if (strrchr(cmd, '/') == NULL)
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

static void    init_cmd(t_pipex *pipex, char **av, int cmd_idx)
{
    pipex->parse.cmd_args = ft_split(av[cmd_idx], ' ');
    pipex->parse.cmd = get_cmd(pipex->parse.cmd_path, pipex->parse.cmd_args[0]);
}

static void    execute_cmd(t_pipex *pipex, int ac, char **av, char **envp)
{
    is_valid_cmd(pipex, true);
    if (pipex->execute.cmd_idx == 2)
        init_args(pipex, ac, av, true);
    if (pipex->execute.prev_pipe != 0)
    {
        dup2(pipex->execute.prev_pipe, 0);
        close(pipex->execute.prev_pipe);
    }
    dup2(pipex->execute.pfds[1], 1);
    close(pipex->execute.pfds[1]);
    execve(pipex->parse.cmd, pipex->parse.cmd_args, envp);
    ft_dprintf(2, "Execve Failed.\n");
    exit (1);
}

void    start(t_pipex *pipex, int ac, char **av, char **envp)
{
    int i;

    i = -1;
    while (++i < ac - 4)
    {
        pipe(pipex->execute.pfds);
        init_cmd(pipex, av, ++pipex->execute.cmd_idx);
        pipex->execute.pid = fork();
        if (!(pipex->execute.pid))
            execute_cmd(pipex, ac, av, envp);
        close(pipex->execute.prev_pipe);
        close(pipex->execute.pfds[1]);
        pipex->execute.prev_pipe = pipex->execute.pfds[0];
    }
    wait(NULL);
    if (pipex->execute.prev_pipe != 0)
    {
        dup2(pipex->execute.prev_pipe, 0);
        close(pipex->execute.prev_pipe);
    }
    init_cmd(pipex, av, ac - 2);
    is_valid_cmd(pipex, false);
    execve(pipex->parse.cmd, pipex->parse.cmd_args, envp);
    ft_dprintf(2, "Execve Failed.\n");
    exit (1);
}
