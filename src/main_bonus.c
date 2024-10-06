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

void do_pipe(char *cmd, char **envp)
{
    int pipe_fd[2];
    pid_t pid;

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

int handle_here_doc(char *limiter)
{
    char *line;
    size_t len;
    ssize_t nread;
    int pipe_fd[2];

	line = NULL;
	len = 0;
    if (pipe(pipe_fd) == -1)
        exit_with_error("pipe", 1);
    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);
        nread = getline(&line, &len, stdin);
        if (nread == -1)
            exit_with_error("getline", 1);
        line[nread - 1] = '\0';
        if (strcmp(line, limiter) == 0)
            break;
        write(pipe_fd[1], line, nread);
    }
    free(line);
    close(pipe_fd[1]);
    return pipe_fd[0];
}

// relay file name in infile or outfile error
int main(int argc, char **argv, char **envp)
{
    int infile;
	int outfile;
	int	i;

    if (argc < 5)
        exit_with_error("Usage: ./pipex infile cmd1 [cmd2 ... cmdN] outfile", 1);
	if (strcmp(argv[1], "here_doc") == 0)
    {
        if (argc < 6)
            exit_with_error("Usage: ./pipex here_doc LIMITER cmd1 [cmd2 ... cmdN] outfile", 1);
        infile = handle_here_doc(argv[2]);
        outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (outfile < 0)
            exit_with_error("Error opening output file", 1);
        i = 3;
    }
    else
    {
        infile = open(argv[1], O_RDONLY);
        if (infile < 0)
            exit_with_error("Error opening input file", 1);
        outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile < 0)
            exit_with_error("Error opening output file", 1);
        dup2(infile, STDIN_FILENO);
        close(infile);
        i = 2;
    }
    while (i < argc - 2)
        do_pipe(argv[i++], envp);
    dup2(outfile, STDOUT_FILENO);
    close(outfile);
    execute_command(argv[argc - 2], envp);
    return (0);
}
