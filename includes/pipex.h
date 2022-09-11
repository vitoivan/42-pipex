/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:35:45 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 16:10:49 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*cmd1;
	char	*cmd2;
	char	*filein;
	char	*fileout;
	char	**envp;
	int		pipe[2];
	int		pid[2];
	int		status;
}			t_pipex;

int			is_child(int pid);
void		error(char *message, int exit_code);
void		first_command(t_pipex *pipex, char **envp);
void		second_command(t_pipex *pipex, char **envp);
char		**get_path(char **envp);
char		*get_binary_path(char *cmd, char **envp);
void		close_pipes(int pipe_fd[2]);
void		init_pipe(int pipe_fd[2]);
void		init_pipex(t_pipex *pipex, char **argv, char **envp);
int			wait_pipes(t_pipex *pipex);
int			is_quote(char *str);
void		free_cmd(char **cmd);
size_t		len_cmd(char **cmd);
char		**get_cmd(char *cmd);
void		free_cmd_and_path(char **cmd, char *path);

#endif