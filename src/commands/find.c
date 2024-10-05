#include "../utils/headers/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char *get_path_env(char **envp)
{
    int i = 0;

    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}

char	*get_full_path(char **paths, char *cmd, int i, char **full_path)
{
	*full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
	if (!*full_path)
		exit_with_error("malloc", 1);
	strcpy(*full_path, paths[i]);
	strcat(*full_path, "/");
	strcat(*full_path, cmd);
	return (*full_path);
}

char	*find_command(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	char	*path_env;
	int		i;

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		get_full_path(paths, cmd, i, &full_path);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}
