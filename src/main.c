/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:19:12 by hawayda           #+#    #+#             */
/*   Updated: 2024/08/31 05:43:30 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/headers/pipex.h"

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

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (EXIT_FAILURE);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exit("open infile");
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error_exit("open outfile");
	if (pipe(pipe_fd) == -1)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 < 0)
		error_exit("fork");
	if (pid1 == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(argv[2], envp);
	}
	pid2 = fork();
	if (pid2 < 0)
		error_exit("fork");
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execute_command(argv[3], envp);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}
