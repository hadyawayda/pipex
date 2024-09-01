/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 05:35:18 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/01 05:37:17 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/headers/pipex.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (execve(args[0], args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	close_everything(int pipe_fd[2], pid_t pid1, pid_t pid2)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
