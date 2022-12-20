/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonux.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:55:41 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/20 16:11:24 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUX_H
# define PIPEX_BONUX_H

# include "dprintf/ft_dprintf.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/_types/_pid_t.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		*pipe;
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmds_args;
	char	*cmd;
	int		pipes_nb;
	int		cmds_nb;
	int		i;
}			t_pipex;

void		ft_free(t_pipex *pipex);
char		*find_path(char **env);
void		close_pipes(t_pipex pipex);
char		*get_cmd(char **paths, char *cmd);
void		parent(t_pipex pipex, char **av, char **envp);
void		child(t_pipex pipex, char **av, char **envp);

#endif