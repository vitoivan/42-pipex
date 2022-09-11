/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:17:31 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 11:50:46 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	free_cmd_and_path(char **cmd, char *path)
{	
	int	i;

	i = 0;
	while(cmd[i])
		free(cmd[i++]);
	free(cmd);
	free(path);
}

void	first_command(t_pipex *pipex, char **envp)
{
	char	*binary_path;
	char	**cmd;
	int		filein;

	filein = open(pipex->filein, O_RDONLY);
	if (filein == -1)
		error(ft_strjoin("Error opening file: ", pipex->filein), 1);
	dup2(filein, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	cmd = ft_split(pipex->cmd1, ' ');
	binary_path = get_binary_path(cmd[0], envp);
	if (!binary_path)
	{
		free_cmd_and_path(cmd, binary_path);
		error(ft_strjoin("Error: Command not found: ", pipex->cmd1), 127);
	}
	execve(binary_path, cmd, envp);
}

void	second_command(t_pipex *pipex, char **envp)
{
	char	*binary_path;
	char	**cmd;
	int		fileout;

	fileout = open(pipex->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fileout == -1)
		error(ft_strjoin("Error opening file: ", pipex->fileout), 1);
	dup2(fileout, STDOUT_FILENO);
	dup2(pipex->pipe[0], STDIN_FILENO);
	cmd = ft_split(pipex->cmd2, ' ');
	binary_path = get_binary_path(cmd[0], envp);
	if (!binary_path)
	{
		free_cmd_and_path(cmd, binary_path);
		error(ft_strjoin("Error: Command not found: ", pipex->cmd1), 127);
	}
	execve(binary_path, cmd, envp);
}
