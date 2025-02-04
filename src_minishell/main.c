/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:57:19 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 16:51:21 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_minishell/minishell.h"

void	print_env(t_config *minishell)
{

	t_list		*tmp;

	tmp = minishell->environnement;
	while (tmp)
	{
		printf("%s=%s\n", ((t_envvar *)tmp->content)->name, ((t_envvar *)tmp->content)->value);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_config	*minishell;
	char	*cmd;

	init_signals();
	minishell = init(ac, av, env);
	if (!minishell)
		return (1);
	t_btree	*arbrebidon = arbre_bidon();
	// printf("mid=%s\n", (char *)arbrebidon->item);
	// printf("left=%s\n", (char *)arbrebidon->left->item);

	t_pipes	p_data;

	init_p_data(&p_data, arbrebidon, env);
	// printf("%s\n", p_data.environnement[30]);
	printf("right=%s\n", (char *)arbrebidon->left->item);
	pipes(&p_data);
	
	while (1)
	{
		cmd = readline(minishell->prompt);
		if (!cmd)
			return (printf("exit\n"), clear_minishell(minishell), 1);
		if (ft_strncmp("env", cmd, ft_strlen("env")) == 0)
			print_env(minishell);
		else if (ft_strncmp("exit", cmd, ft_strlen("exit")) == 0)
		{
			free(cmd);
			clear_minishell(minishell);
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}
	clear_minishell(minishell);
	(void)arbrebidon;
	return (0);
}
