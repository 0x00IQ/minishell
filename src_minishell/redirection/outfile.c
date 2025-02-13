/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:46:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/12 14:43:53 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static int	check_outfile_access(t_pipes *p_data, t_btree *cmdn)
{
	int	fd_outfile;

	if (access(p_data->name_outfile, F_OK) == 0)
	{
		if (access(p_data->name_outfile, R_OK) == -1)
		{
			ft_putstr_fd("permission denied: ", 2);
			ft_putendl_fd(p_data->name_outfile, 2);
			unlink_hd(p_data);
			free_fd(&p_data->fd, p_data->nb_pipes);
			p_data->ms_data->last_error_code = EXIT_FAILURE;
			return (1);
		}
	}
	else
	{
		fd_outfile = open(((t_node2 *)(cmdn->item))->file, p_data->flags, 0644);
		if (fd_outfile == -1)
		{
			perror("open");
			unlink_hd(p_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
		close(fd_outfile);
	}
	return (0);
}

int	get_outfile(t_pipes *p_data)
{
	t_btree *cmdn;

	cmdn = p_data->ms_data->ast;
	while (((t_node2 *)(cmdn->item))->type == PIPE_TOKEN)
		cmdn = cmdn->right;
	while (cmdn->right != NULL)
	{
		cmdn = cmdn->right;
		p_data->name_outfile = ((t_node2 *)(cmdn->item))->file;
		if (((t_node2 *)(cmdn->item))->type == TRUNCATE)
			p_data->flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (((t_node2 *)(cmdn->item))->type == APPEND)
			p_data->flags = O_WRONLY | O_CREAT | O_APPEND;
		if (check_outfile_access(p_data, cmdn) == 1)
			return (1);
	}
	return (0);
}
