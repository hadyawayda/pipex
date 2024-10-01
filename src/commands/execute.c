#include "../utils/headers/pipex.h"

// void	execute_command(char *cmd, char **envp)
// {
// 	char	**args;
// 	int		i;

// 	args = ft_split(cmd, ' ');
// 	if (execve(args[0], args, envp) == -1)
// 	{
// 		i = 0;
// 		while (args[i])
// 			free(args[i++]);
// 		free(args);
// 		perror("execve");
// 	}
// }

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*command_path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit_with_error("ft_split", 1);
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
