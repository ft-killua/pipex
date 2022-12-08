/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:23:30 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/08 23:26:45 by hidhmmou         ###   ########.fr       */
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
		close(pipex.fd[0]);//close read end of the pipe
		dup2(pipex.fd[1], STDOUT_FILENO);//reroute standard output of the process to the write end of the pipe	
		path = ft_find_path(&pipex, pipex.splited_cmd[0], envp);//find the right path
		ft_exe(path, pipex, envp);//execute commande
	}
	else
	{
		close(pipex.fd[1]);//close write end of the pipe
		dup2(pipex.fd[0], STDIN_FILENO);//reroute standard input of the process (main one) to the read end of the pipe
		waitpid(pid, NULL, 0);//wait to the child process to end 
	}
}

void	ft_exec_multi_pipes(int ac, char **av, char **envp, int flag)
{
	int		i;
	char	*path;
	t_pipex	pipex;
	int		last_cmd;

	i = 2 + flag;
	last_cmd = ac - 2;
	ft_init(&pipex, av[last_cmd], envp);
	if (!flag)
	{
		pipex.fd[0] = ft_open(av[1], READ);
		dup2(pipex.fd[0], STDIN_FILENO);
		close(pipex.fd[0]);
	}
	pipex.fd[1] = ft_open(av[ac - 1], WRITE);
	while (i < last_cmd)
		ft_child(av[i++], envp);
	dup2(pipex.fd[1], STDOUT_FILENO);
	close(pipex.fd[1]);
	path = ft_find_path(&pipex, pipex.splited_cmd[0], envp);
	ft_exe(path, pipex, envp);
}

void	ft_heredoc(int ac, char *limiter)
{
	char	*line;
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		exit(ft_error("pipe error !"));
	pid = fork();
	if (pid == -1)
		exit(ft_error("could'nt fork process !"));
	if (pid == CHILD)
	{
		close(fd[0]);
		while (1)
		{
			ft_putstr_fd("heredoc> ", 1);
			get_next_line(&line);
			if (!ft_strcmp(limiter, line))
				exit(EXIT_SUCCESS);
			ft_putstr_fd(line, fd[1]);
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	flag;

	flag = 0;
	if (ac >= 6)
	{
		if (!ft_strcmp("here_doc", av[1]))
		{
			flag = 1;
			ft_heredoc(ac, ft_strjoin(av[2],"\n"));
		}
	}
	if (ac >= 5)
	{
		ft_exec_multi_pipes(ac, av, envp, flag);
	}
		
}
