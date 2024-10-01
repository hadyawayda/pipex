#include "../utils/headers/pipex.h"

char	*find_command(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	char	*path_env;
	int		i;

	path_env = NULL;
	i = 0;
	// Find PATH in envp
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5; // Skip "PATH=" prefix
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':'); // Split PATH into individual directories
	i = 0;
	while (paths[i])
	{
		full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
		// Allocate memory for the full path
		if (!full_path)
			exit_with_error("malloc", 1);
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
			return (full_path);
		}
		free(full_path);
		i++;
	}
	// Free paths array if command is not found
	for (int j = 0; paths[j]; j++)
		free(paths[j]);
	free(paths);
	return (NULL); // Command not found in any directory
}
