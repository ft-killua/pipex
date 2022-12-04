/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:23:30 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/04 21:03:20 by hidhmmou         ###   ########.fr       */
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
		if (pid == 0)
			ft_child(av[1], pipex.fd, envp, &pipex);
		ft_parent(av[4], pipex.fd, envp, &pipex);
	}
}

// int main(int ac, char **av, char **envp)
// {
// 	t_pipex	pipex;
// 	int i;
// 	i = 0;
// 	ft_init(&pipex, av, envp);
// 	printf("paths : \n");
// 	while (pipex.paths[i])
// 	{
// 		printf("%s\n", pipex.paths[i]);
// 		i++;
// 	}
// 	printf("cmd 1 : %s\n", pipex.cmd1);
// 	printf("cmd 2 : %s\n", pipex.cmd2);
// }