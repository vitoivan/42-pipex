/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:09:43 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 16:12:18 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	is_quote(char *str)
{
	if (ft_strcmp(str, "'") == 0)
		return (0);
	else if (ft_strcmp(str, "\"") == 0)
		return (0);
	else if (ft_strcmp(str, "`") == 0)
		return (0);
	return (1);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

size_t	len_cmd(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i++);
}

char	**get_cmd(char *cmd)
{
	char	**old_cmd;
	char	**new_cmd;
	size_t	cmd_len;
	size_t	n_i;
	size_t	o_i;

	old_cmd = ft_split(cmd, ' ');
	cmd_len = len_cmd(old_cmd);
	new_cmd = (char **)malloc(sizeof(char *) * (cmd_len + 1));
	n_i = 0;
	o_i = 0;
	while (old_cmd[n_i])
	{
		if (is_quote(old_cmd[n_i]) == 0 && is_quote(old_cmd[n_i + 1]) == 0)
		{
			new_cmd[o_i++] = ft_strdup("' '");
			n_i += 2;
			continue ;
		}
		new_cmd[o_i++] = ft_strdup(old_cmd[n_i++]);
	}
	new_cmd[o_i] = NULL;
	n_i = 0;
	free_cmd(old_cmd);
	return (new_cmd);
}

void	free_cmd_and_path(char **cmd, char *path)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	free(path);
}
