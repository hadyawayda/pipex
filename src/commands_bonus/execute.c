#include "../utils/headers/pipex.h"

void	check_command(char **args, char **envp, char **command_path)
{
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		*command_path = strdup(args[0]);
		if (!*command_path)
		{
			free_array(args);
			exit_with_error("strdup", 1);
		}
	}
	else
	{
		*command_path = find_command(args[0], envp);
		if (!*command_path)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			free_array(args);
			exit(127);
		}
	}
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*command_path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit_with_error("ft_split", 1);
	check_command(args, envp, &command_path);
	if (execve(command_path, args, envp) == -1)
	{
		free(command_path);
		free_array(args);
		exit_with_error("execve", 1);
	}
}
