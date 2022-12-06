/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:08:31 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/06 23:02:36 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_exe(char *path, t_pipex pipex, char **envp)
{
	int		ret;

	ret = execve(path, pipex.splited_cmd, envp);
	if (ret == -1)
	{
		ft_error("pipex: command not found: ");
		ft_error(pipex.splited_cmd[0]);
		exit(ft_error("\n"));
	}
}
