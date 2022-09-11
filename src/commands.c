/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:17:31 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 08:38:44 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_command(char **argv, int pipe_fd[2], char **envp)
{
	char	*binary_path;
	char	**cmd;
	int		filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error("Error opening file\n");
	dup2(filein, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	cmd = ft_split(argv[2], ' ');
	binary_path = get_binary_path(cmd[0], envp);
	if (!binary_path)
		error("Error: command not found\n");
	execve(binary_path, cmd, envp);
}

void	second_command(char **argv, int pipe_fd[2], char **envp)
{
	char	*binary_path;
	char	**cmd;
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error("Error opening file\n");
	dup2(fileout, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	cmd = ft_split(argv[3], ' ');
	binary_path = get_binary_path(cmd[0], envp);
	if (!binary_path)
		error("Error: command not found\n");
	execve(binary_path, cmd, envp);
}
