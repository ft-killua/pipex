/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:21:18 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/08 22:49:39 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# define CHILD 0
# define WRITE 0
# define READ 1
# define HERE_DOC 2
# define RED "\033[1;31m"
# define RESET "\033[0m"

typedef struct s_pipex
{
	char	**env;
	char	**splited_cmd;
	int		fd[2];
	char	*paths_line;
	char	**paths;
}	t_pipex;

int		ft_error(char *message);
int		ft_open(char *av, int i);
char	**ft_split(char *s, char c);
void	ft_init(t_pipex *pipex, char *cmd, char **env);
char	*ft_get_paths_line(char **env);
char	*ft_strjoin(char *s1, char *s2);
void	ft_exe(char *path, t_pipex pipex, char **envp);
char	*ft_find_path(t_pipex *pipex, char *command, char **envp);
int		ft_strcmp(char *s1, char *s2);
void	get_next_line(char **line);
void	ft_putstr_fd(char *str, int fd);
#endif