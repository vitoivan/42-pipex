/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:35:51 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/12 19:27:43 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	validate_args(int argc, char **argv)
{
	char	*error_message;

	error_message = ft_strjoin("Invalid number of arguments\n",
			"Usage: ./pipex filein cmd1 cmd2 fileout");
	if (argc != 5)
		error(error_message, 1);
	else if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[2]) == 0
		|| ft_strlen(argv[3]) == 0 || ft_strlen(argv[4]) == 0)
		error(error_message, 1);
	free(error_message);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	validate_args(argc, argv);
	init_pipex(&pipex, argv, envp);
	init_pipe(pipex.pipe);
	pipex.pid[0] = fork();
	if (is_child(pipex.pid[0]))
		first_command(&pipex, envp);
	else
	{
		pipex.pid[1] = fork();
		if (is_child(pipex.pid[1]))
			second_command(&pipex, envp);
		else
		{
			close_pipes(pipex.pipe);
			return (wait_pipes(&pipex));
		}
	}
	return (0);
}
