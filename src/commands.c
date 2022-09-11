/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:17:31 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 16:10:12 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_command(t_pipex *pipex, char **envp)
{
	char	*binary_path;
	char	**cmd;
	int		filein;

	close(pipex->pipe[0]);
	filein = open(pipex->filein, O_RDONLY);
	if (filein == -1)
		error(ft_strjoin("Error opening file: ", pipex->filein), 1);
	dup2(filein, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	cmd = get_cmd(pipex->cmd1);
	binary_path = get_binary_path(cmd[0], envp);
	if (!binary_path)
	{
		free_cmd_and_path(cmd, binary_path);
		error(ft_strjoin("Error: Command not found: ", pipex->cmd1), 127);
	}
	if (execve(binary_path, cmd, envp) == -1)
	{
		free_cmd_and_path(cmd, binary_path);
		error(ft_strjoin("Error executing command\n", pipex->cmd1), 127);
	}
}

void	second_command(t_pipex *pipex, char **envp)
{
	char	*binary_path;
	char	**cmd;
	int		fileout;

	close(pipex->pipe[1]);
	fileout = open(pipex->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fileout == -1)
		error(ft_strjoin("Error opening file: ", pipex->fileout), 1);
	dup2(fileout, STDOUT_FILENO);
	dup2(pipex->pipe[0], STDIN_FILENO);
	cmd = get_cmd(pipex->cmd2);
	binary_path = get_binary_path(cmd[0], envp);
	if (!binary_path)
	{
		free_cmd_and_path(cmd, binary_path);
		error(ft_strjoin("Error: Command not found: ", pipex->cmd1), 127);
	}
	if (execve(binary_path, cmd, envp) == -1)
	{
		free_cmd_and_path(cmd, binary_path);
		error(ft_strjoin("Error executing command\n", pipex->cmd1), 127);
	}
}
