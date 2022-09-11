/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:35:51 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 11:51:52 by vivan-de         ###   ########.fr       */
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
	pipex->status = 0;
}

static void	close_pipes(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	init_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		error("Error creating pipe\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error(ft_strjoin("\nError: Wrong number of arguments\n",
				"Expected: ./pipex file1 cmd1 cmd2 file2\n"), 1);
	init_pipex(&pipex, argv, envp);
	init_pipe(pipex.pipe);
	pipex.pid[0] = fork();
	if (is_child(pipex.pid[0]))
	{
		close(pipex.pipe[0]);
		first_command(&pipex, envp);
	}
	else
	{
		pipex.pid[1] = fork();
		if (is_child(pipex.pid[1]))
		{
			close(pipex.pipe[1]);
			second_command(&pipex, envp);
		}
		else
		{
			close_pipes(pipex.pipe);
			waitpid(pipex.pid[0], &pipex.status, 0);
			if (WIFEXITED(pipex.status))
				pipex.status = WEXITSTATUS(pipex.status);
			waitpid(pipex.pid[1], &pipex.status, 0);
			if (WIFEXITED(pipex.status))
				pipex.status = WEXITSTATUS(pipex.status);
			return (pipex.status);
		}
	}
	return (0);
}
