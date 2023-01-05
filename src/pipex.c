/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:23:30 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/01/05 23:00:16 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		id;
	int		pid;
	t_pipex	pipex;

	if (ac == 5)
	{
		id = pipe(pipex.fd);
		if (id == -1)
			exit(ft_error("pipe error"));
		ft_init(&pipex, av, envp);
		pid = fork();
		if (pid < 0)
			exit(ft_error("could'nt fork process !"));
		if (pid == CHILD)
			ft_child(av[1], pipex.fd, envp, &pipex);
		ft_parent(av[4], pipex.fd, envp, &pipex);
		wait(NULL);
		wait(NULL);
	}
	else
		exit(ft_error("usage : ./pipex infile cmd_1 cmd_2 outfile\n"));
}
