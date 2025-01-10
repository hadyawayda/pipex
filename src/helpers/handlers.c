/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 05:35:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/01/10 03:43:05 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/headers/pipex.h"

void	exit_with_error(char *msg, int code)
{
	perror(msg);
	exit(code);
}
void	close_files(int infile, int outfile)
{
	close(infile);
	close(outfile);
}
