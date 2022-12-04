/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:23:30 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/04 23:34:19 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	new_pipe(char *cmd, char **envp)
{
	int		id;
	int		pid;
	t_pipex pipex;
	char	*path;

	id = pipe(pipex.fd);
	if (id == -1)
		exit(ft_error("pipe error"));
	ft_init(&pipex, cmd, envp);
	pid = fork();
	if (pid < 0)
		exit(ft_error("could'nt fork process !"));
	if (pid == CHILD)
	{
		dup2(pipex.fd[1], STDOUT_FILENO);
		close(pipex.fd[0]);
		path = ft_find_path(&pipex, pipex.s_cmd1[0], envp);
		ft_exe(path, pipex, envp, 0);
	}
	else
	{
		close(pipex.fd[1]);
		dup2(pipex.fd[0], STDIN_FILENO);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;

	i = 2;
	if (ac > 5)
	{
		while (i < ac - 2)
		{
			new_pipe(av[i], envp);
			i++;
		}
	}
}
