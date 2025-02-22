/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:09:58 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 17:15:17 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "minishell.h"

/* structure */

typedef struct s_pipes
{
	char	**environnement;
	t_btree	*tree;
	int		**fd;
	int		nb_pipes;
	int		fd_infile;
	int		fd_outfile;
	int		pid_last_parent;
}	t_pipes;

/* prototypes */

//pipes
void	pipes(t_pipes *p_data);
void	first_parent(t_pipes *p_data);
void	last_parent(t_pipes *p_data);
void	infinite_parent(t_pipes *p_data);

//execute commands
void	execute_command(char **envp, t_btree *arbrebidon);

//pipes utilisation
int		count_pipes(t_btree	*arbre);
void	init_p_data(t_pipes *p_data, t_btree *tree, char **envp);
void	free_fds(int **fd, int len);


#endif
