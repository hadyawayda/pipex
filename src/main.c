/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:19:12 by hawayda           #+#    #+#             */
/*   Updated: 2025/01/10 03:36:24 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/headers/pipex.h"

void	do_pipe(char *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		exit_with_error("pipe", 1);
	pid = fork();
	if (pid == -1)
		exit_with_error("fork", 1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_command(cmd, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

int	handle_files(char **argv, char **envp, int infile, int outfile)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	dup2(infile, STDIN_FILENO);
	do_pipe(argv[2], envp);
	dup2(outfile, STDOUT_FILENO);
	execute_command(argv[3], envp);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	exit_code;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		exit_with_error("pipe", 1);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		perror("-bash: infile");
		return (EXIT_FAILURE);
	}
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		exit_with_error("-bash: outfile", 1);
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
		exit_with_error("One or both commands are missing", 1);
	exit_code = handle_files(argv, envp, infile, outfile);
	close_files(infile, outfile);
	return (exit_code);
}
