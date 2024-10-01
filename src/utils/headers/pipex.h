/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:35:39 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/29 18:07:18 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int		exit_with_error(char *msg, int code);

void	close_everything(int pipe_fd[2], pid_t pid1, pid_t pid2);
void	close_files(int infile, int outfile);
void	execute_command(char *cmd, char **envp);

char	*find_command(char *cmd, char **envp);

#endif