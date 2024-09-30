/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:19:12 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/29 18:03:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/headers/pipex.h"

void	handle_child_process(int infile, int outfile, int *pipe_fd,
		int is_first_child)
{
	if (is_first_child)
	{
		dup2(infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	setup_pipes_and_forks(int infile, int outfile, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
		return (exit_with_error("pipe"));
	pid1 = fork();
	if (pid1 < 0)
		return (exit_with_error("fork"));
	if (pid1 == 0)
	{
		handle_child_process(infile, outfile, pipe_fd, 1);
		execute_command(argv[2], envp);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (exit_with_error("fork"));
	if (pid2 == 0)
	{
		handle_child_process(infile, outfile, pipe_fd, 0);
		execute_command(argv[3], envp);
	}
	close_everything(pipe_fd, pid1, pid2);
	close_files(infile, outfile);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (exit_with_error("pipe"));
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return (exit_with_error("open infile"));
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return (exit_with_error("open outfile"));
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
		return (exit_with_error("One or both commands are missing"));
	return (setup_pipes_and_forks(infile, outfile, argv, envp));
}
