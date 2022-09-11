/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:58:33 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 16:00:13 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->filein = argv[1];
	pipex->fileout = argv[4];
	pipex->envp = envp;
	pipex->status = 0;
}
