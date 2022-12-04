/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:08:31 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/04 02:19:49 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(t_pipex *pipex, char *command, char **envp)
{
	int		i;
	char	*tmp;
	char	*exec_cmd;

	i = 0;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		exec_cmd = ft_strjoin(tmp, command);
		free(tmp);
		if (access(exec_cmd, F_OK | X_OK) == 0)
			return (exec_cmd);
		free(exec_cmd);
		i++;
	}
	return (command);
}

void	ft_parent(char *outfile, int *fd, char **envp, t_pipex *pipex)
{
	int		file;
	char	*path;

	file = ft_open(outfile, READ);
	close(fd[1]);
	dup2(file, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	path = ft_find_path(pipex, pipex->s_cmd2[0], envp);
	ft_exe(path, *pipex, envp, 1);
}
