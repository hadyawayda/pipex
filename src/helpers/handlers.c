/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 05:35:18 by hawayda           #+#    #+#             */
/*   Updated: 2024/10/06 18:01:56 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/headers/pipex.h"


void	exit_with_error(char *msg, int code)
{
	perror(msg);
	exit(code);
}

void	close_everything(int pipe_fd[2], pid_t pid1, pid_t pid2)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	close_files(int infile, int outfile)
{
	close(infile);
	close(outfile);
}