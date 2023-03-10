/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:18:49 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 11:12:56 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		pipe[2];
	int		in;
	int		out;
	char	*paths;
	char	**cmds_paths;
	char	**cmds_args;
	char	*cmd;
	int		i;
	int		cmds_idx;
	int		heredoc;
}			t_pipex;

void		ft_free(t_pipex *pipex, char c);
void		close_pipes(t_pipex *pipex);
void		child(t_pipex pipex, char **av, char **envp);
void		parent(t_pipex pipex, int ac, char **av, char **envp);
void		heredoc(char *delimiter);
void		args(int ac, char **av);

#endif
