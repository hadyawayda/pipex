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
	int		i;

	args = ft_split(cmd, ' ');
	if (execve(args[0], args, envp) == -1)
	{
		perror("execve");
		i = 0;
		while (args[i])
        	free(args[i++]);
    	free(args);
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

char *find_command(char *cmd, char **envp)
{
    char *path_env = NULL;
    char **paths;
    char *full_path;
    int i = 0;

    // Find PATH in envp
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5; // Skip "PATH=" prefix
            break;
        }
        i++;
    }

    if (!path_env)
        return NULL;

    paths = ft_split(path_env, ':'); // Split PATH into individual directories

    i = 0;
    while (paths[i])
    {
        full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2); // Allocate memory for the full path
        if (!full_path)
            error_exit("malloc");

        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        // Check if the command is executable
        if (access(full_path, X_OK) == 0)
        {
            // Free the paths array before returning
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return full_path;
        }
        free(full_path);
        i++;
    }

    // Free paths array if command is not found
    for (int j = 0; paths[j]; j++)
        free(paths[j]);
    free(paths);

    return NULL; // Command not found in any directory
}

void execute_command(char *cmd, char **envp)
{
    char **args;
    char *command_path;

    args = ft_split(cmd, ' ');
    if (!args)
        error_exit("ft_split");

    // Find the command path using PATH from envp
    command_path = find_command(args[0], envp);
    if (!command_path)
    {
        fprintf(stderr, "Command not found: %s\n", args[0]);
        for (int i = 0; args[i]; i++)
            free(args[i]);
        free(args);
        exit(EXIT_FAILURE);
    }

    // Execute the command
    if (execve(command_path, args, envp) == -1)
    {
        perror("execve");
        free(command_path);
        for (int i = 0; args[i]; i++)
            free(args[i]);
        free(args);
        exit(EXIT_FAILURE);
    }
}
