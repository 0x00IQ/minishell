/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:09:58 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 17:59:41 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

#include "minishell.h"

/* Pipes structure */

typedef struct s_pipes
{
	int		**fd;  //malloced
	int		nb_pipes;
	char	*name_infile;
	char	*name_outfile;
	bool	is_hd;
	char	*cmd;
	int		flags;
	int		pid_last_parent;
	t_config	*ms_data;
}	t_pipes;

/* prototypes */

/* Pipes */
void	pipes(t_config *ms_data);
void	simple_command(t_pipes *p_data);
void	first_parent(t_pipes *p_data);
void	infinite_parent(t_pipes *p_data);
void	last_parent(t_pipes *p_data);
void	check_children(t_pipes *data);

/* Execution */
void	execute_command(t_pipes *p_data);

/* Utilisation */
void	init_p_data(t_pipes *p_data, t_config *ms_data);
void	free_fd(int ***fd, int len);

/* Redirection */
void	get_infile(t_btree *cmd1, t_pipes *p_data);
void	get_outfile(t_btree *cmdn, t_pipes *p_data);

#endif
