#include "../utils/headers/pipex.h"

// relay exit status to main using a return value
// fix double free when command is not found
void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*command_path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit_with_error("ft_split", 1);

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		command_path = strdup(args[0]);
		if (!command_path)
		{
			for (int i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			exit_with_error("strdup", 1);
		}
	}
	else
	{
		command_path = find_command(args[0], envp);
		if (!command_path)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			for (int i = 0; args[i]; i++)
				free(args[i]);
			// free(args);
			// free(command_path);
			exit_with_error("strdup", 127);
		}
	}
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
