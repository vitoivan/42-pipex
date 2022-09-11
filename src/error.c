/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:17:26 by vivan-de          #+#    #+#             */
/*   Updated: 2022/09/11 10:37:15 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error(char *message, int exit_code)
{
	char	*output;

	output = ft_strjoin(message, "\n");
	ft_putstr_fd((char *) output, 2);
	free(message);
	free(output);
	exit(exit_code);
}
