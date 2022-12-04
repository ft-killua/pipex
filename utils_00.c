/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:32:56 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/04 02:25:13 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

void	ft_error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(message, 1);
	ft_putstr_fd(RESET, 2);
	exit(1);
}

int		ft_open(char *av, int x)
{
	int fd;

	fd = 0;
	if (x == WRITE)
		fd = open(av, O_RDONLY, 0777);
	else if (x == READ)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		ft_error("could'nt open the file !");
	return (fd);
}

char	*ft_get_paths_line(char **env)
{
	int		i;

	i = 0;
	while(env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T' && env[i][3] == 'H')
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void    ft_init(t_pipex *pipex, char **av, char **env)
{
	pipex->cmd1 = av[2];
	pipex->s_cmd1 = ft_split(pipex->cmd1, ' ');
	pipex->cmd2 = av[3];
	pipex->s_cmd2 = ft_split(pipex->cmd2, ' ');
	pipex->paths_line = ft_get_paths_line(env);
	pipex->paths = ft_split(pipex->paths_line, ':');
}

void    ft_child(char *infile, int *fd, char **envp, t_pipex *pipex)
{
	int 	file;
	char	*path;

	file = ft_open(infile, READ);
	close(fd[0]);
	dup2(file, STDIN_FILENO);
	//close(file);
	dup2(fd[1], STDOUT_FILENO);
	//close(fd[1]);
	path = ft_find_path(pipex, pipex->s_cmd1[0], envp);
	ft_exe(path, *pipex, envp, 0);
}

void    ft_exe(char *path, t_pipex pipex, char **envp, int flag)
{
	char	**splited_cmd;
	int		ret;

	if (!flag)
		splited_cmd = pipex.s_cmd1;
	else
		splited_cmd = pipex.s_cmd2;
	ret = execve(path, splited_cmd, envp);
	if (ret == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(splited_cmd[0], 2);
		exit (0);
	}
}
