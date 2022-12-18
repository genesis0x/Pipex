/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:30 by hahadiou          #+#    #+#             */
/*   Updated: 2022/12/18 08:27:34 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./dprintf/ft_dprintf.h"
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmds_args;
	char	*cmd;
}			t_pipex;

void		ft_free(t_pipex *pipex, char c);
char		*find_path(char **envp);
void		close_pipes(t_pipex *pipex);
char		*get_cmd(char **paths, char *cmd);
void		first_child(t_pipex pipex, char **av, char **envp);
void		second_child(t_pipex pipex, char **av, char **envp);
int			execute_cmd(t_pipex pipex, char **envp);

#endif
