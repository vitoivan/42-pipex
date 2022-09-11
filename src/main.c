/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:35:51 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 08:28:10 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->filein = argv[1];
	pipex->fileout = argv[4];
	pipex->envp = envp;
}

static void	close_pipes(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	init_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		error("Error creating pipe\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, argv, envp);
	if (argc != 5)
		error("Wrong number of arguments\n"
			"Expected: ./pipex file1 cmd1 cmd2 file2\n");
	init_pipe(pipex.pipe);
	pipex.pid[0] = fork();
	if (is_child(pipex.pid[0]))
	{
		close(pipex.pipe[0]);
		first_command(argv, pipex.pipe, envp);
	}
	else
	{
		pipex.pid[1] = fork();
		if (is_child(pipex.pid[1]))
		{
			close(pipex.pipe[1]);
			second_command(argv, pipex.pipe, envp);
		}
		else
			close_pipes(pipex.pipe);
	}
	return (0);
}
