/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:36:06 by hahadiou          #+#    #+#             */
/*   Updated: 2023/03/29 21:36:07 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) < 0)
	{
		ft_dprintf(2, "No Such file: %s\n", cmd);
		exit(126);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_dprintf(2, "Permissions: %s\n", cmd);
		exit(126);
	}
	return (1);
}

void	is_valid_cmd(t_pipex *pipex, bool child)
{
	if (child)
	{
		if (!(pipex->parse.cmd))
		{
			// should clean all allocated memory before exit
			ft_dprintf(2, "pipex: %s: command not found\n",
					pipex->parse.cmd_args[0]);
			exit(0);
		}
	}
	else
	{
		if (!(pipex->parse.cmd))
		{
			// should clean all allocated memory before exit
			ft_dprintf(2, "pipex: %s: command not found\n",
					pipex->parse.cmd_args[0]);
			exit(127);
		}
	}
}