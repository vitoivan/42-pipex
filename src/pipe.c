/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:59:41 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 16:05:05 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	init_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		error("Error creating pipe\n", 1);
}

int	wait_pipes(t_pipex *pipex)
{
	waitpid(pipex->pid[0], &pipex->status, 0);
	if (WIFEXITED(pipex->status))
		pipex->status = WEXITSTATUS(pipex->status);
	waitpid(pipex->pid[1], &pipex->status, 0);
	if (WIFEXITED(pipex->status))
		pipex->status = WEXITSTATUS(pipex->status);
	return (pipex->status);
}
