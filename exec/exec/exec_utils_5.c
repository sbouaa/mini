/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:48:50 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/28 17:27:10 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shell_do(char *arg, char **env)
{
	char	*sh[3];

	sh[0] = "/bin/sh";
	sh[1] = arg;
	sh[2] = NULL;
	execve("/bin/sh", sh, env);
	exit(check_file(arg));
}

int	clean(t_pipe *p)
{
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if (p->fd[0] != -1)
		close(p->fd[0]);
	if (p->fd[1] != -1)
		close(p->fd[1]);
	return (1);
}
