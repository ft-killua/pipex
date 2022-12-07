/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:23:30 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/07 19:56:44 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_child(char *cmd, char **envp)
{
	int		id;
	int		pid;
	t_pipex	pipex;
	char	*path;

	id = pipe(pipex.fd);
	if (id == -1)
		exit(ft_error("pipe error !"));
	ft_init(&pipex, cmd, envp);
	pid = fork();
	if (pid < 0)
		exit(ft_error("could'nt fork process !"));
	if (pid == CHILD)
	{
		close(pipex.fd[0]);
		dup2(pipex.fd[1], STDOUT_FILENO);
		path = ft_find_path(&pipex, pipex.splited_cmd[0], envp);
		ft_exe(path, pipex, envp);
	}
	else
	{
		close(pipex.fd[1]);
		dup2(pipex.fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	*path;
	t_pipex	pipex;
	int		last_cmd;

	if (ac >= 5)
	{
		i = 2;
		last_cmd = ac - 2;
		ft_init(&pipex, av[last_cmd], envp);
		pipex.fd[0] = ft_open(av[1], READ);
		pipex.fd[1] = ft_open(av[ac - 1], WRITE);
		dup2(pipex.fd[0], STDIN_FILENO);
		close(pipex.fd[0]);
		while (i < last_cmd)
			ft_child(av[i++], envp);
		dup2(pipex.fd[1], STDOUT_FILENO);
		close(pipex.fd[1]);
		path = ft_find_path(&pipex, pipex.splited_cmd[0], envp);
		ft_exe(path, pipex, envp);
	}
}
