/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:45:35 by hahadiou          #+#    #+#             */
/*   Updated: 2023/03/15 18:12:42 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
#include "utils.h"

typedef struct s_executer	t_executer;
typedef struct s_parser 	t_parser;
typedef struct s_pipex		t_pipex;

struct s_parser
{
	int		in;
	int		out;
	char	*path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
	int		heredoc;
};

struct s_executer
{
	pid_t	pid;
	int		prev_pipe;
	int		pfds[2];
	int		cmd_idx;
};

struct s_pipex
{
	t_parser	parse;
	t_executer	execute;
};

void    init(t_pipex *pipex, int ac, char **av, char **envp);
void    init_args(t_pipex *pipex, int ac, char **av, bool out);
char	*get_cmd(char **paths, char *cmd);
int		check_cmd(char *cmd);
void	is_valid_cmd(t_pipex *pipex, bool child);
void    start(t_pipex *pipex, int ac, char **av, char **envp);

#endif
