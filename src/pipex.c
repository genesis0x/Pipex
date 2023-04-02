/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:48:26 by hahadiou          #+#    #+#             */
/*   Updated: 2023/01/11 10:30:21 by hahadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex[1];

	if (ac < 4)
	{
		ft_dprintf(2, "Enter A Valid Number of Arguments.\n");
		return (1);
	}
	init(pipex, ac, av, envp);
	start(pipex, ac, av, envp);
	return (0);
}
