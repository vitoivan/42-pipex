/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:40:36 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 09:35:24 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

int	is_child(int pid)
{
	return (pid == 0);
}

char	**get_path(char **envp)
{
	char	**output;
	char	**cursor;

	cursor = envp;
	while (*cursor)
	{
		if (ft_strncmp(*cursor, "PATH=", 5) == 0)
		{
			output = ft_split(*cursor + 5, ':');
		}
		cursor++;
	}
	return (output);
}

char	*get_binary_path(char *cmd, char **envp)
{
	char	**path;
	char	*binary;
	char	*tmp;
	char	**cursor;

	path = get_path(envp);
	cursor = path;
	while (*cursor)
	{
		tmp = ft_strjoin(*cursor, "/");
		binary = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(binary, F_OK) == 0)
		{
			free_path(path);
			return (binary);
		}
		free(binary);
		cursor++;
	}
	free_path(path);
	return (NULL);
}
